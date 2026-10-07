/*
* ad7176.c
* Driver for the AD7177-2 32-bit sigma-delta ADC on the plume measuremnent board
# Target: STM32L4A6 (STM32 HAL).
*/
#include "ad7177.h"
#include <string.h>

#define AD7177_SPI_TIMEOUT_MS	10

// Chip select

static void AD7177_CS_Low(AD7177_Handle *dev)
{
	HAL_GPIO_WritePin(dev->cs_port, dev->cs_pin, GPIO_PIN_RESET);
}

static void AD7177_CS_High(AD7177_Handle *dev)
{
	HAL_GPIO_WritePin(dev->cs_port, dev->cs_pin, GPIO_PIN_SET);
}

uint8_t AD7177_RegSize(uint8_t reg)
{
	if(reg == AD7177_REG_STATUS)
		return 1;
	if(reg == AD7177_REG_REGCHECK)
		return 3;
	if(reg == AD7177_REG_DATA)
		return 4; // AD7177-2 uses a 32-bit (4-byte) data register
	if(reg >= AD7177_REG_OFFSET(0) && reg <= AD7177_REG_GAIN(3))
		return 3;
	return 2;
}


HAL_StatusTypeDef AD7177_ReadReg(AD7177_Handle *dev, uint8_t reg, uint32_t *value)
{
	uint8_t size = AD7177_RegSize(reg);
	// Accommodate up to 4 bytes payload + 1 command byte
	uint8_t tx[5] = { (uint8_t)(AD7177_COMMS_READ | (reg & 0x3F)), 0x00, 0x00, 0x00, 0x00 };
	uint8_t rx[5] = { 0 };
	HAL_StatusTypeDef st;

	AD7177_CS_Low(dev);
	st = HAL_SPI_TransmitReceive(dev->hspi, tx, rx, size + 1, AD7177_SPI_TIMEOUT_MS);
	AD7177_CS_High(dev);

	if(st != HAL_OK)
		return st;

	uint32_t v = 0;
	for (uint8_t i = 1; i <= size; ++i)
		v = (v << 8) | rx[i];
	*value = v;
	return HAL_OK;
}


HAL_StatusTypeDef AD7177_WriteReg(AD7177_Handle *dev, uint8_t reg, uint32_t value)
{
	uint8_t size = AD7177_RegSize(reg);
	uint8_t tx[5];
	HAL_StatusTypeDef st;

	tx[0] = (uint8_t)(reg & 0x3F);	// Write: R/W bit = 0
	for (uint8_t i = 0; i < size; ++i)
		tx[1 + i] = (uint8_t)(value >> (8 * (size - 1 - i)));

	AD7177_CS_Low(dev);
	st = HAL_SPI_Transmit(dev->hspi, tx, size + 1, AD7177_SPI_TIMEOUT_MS);
	AD7177_CS_High(dev);

	return st;
}

// 64 clocks with DIN high resets the serial interface and all registers
HAL_StatusTypeDef AD7177_Reset(AD7177_Handle *dev)
{
	uint8_t ones[8];
	HAL_StatusTypeDef st;
	
	memset(ones, 0xFF, sizeof(ones));

	AD7177_CS_Low(dev);
	st = HAL_SPI_Transmit(dev->hspi, ones, sizeof(ones), AD7177_SPI_TIMEOUT_MS);
	AD7177_CS_High(dev);

	HAL_Delay(1); // Datasheet: wait 500 us after reset
	return st;
}

HAL_StatusTypeDef AD7177_ReadID(AD7177_Handle *dev, uint16_t *id)
{
	uint32_t v;
	HAL_StatusTypeDef st = AD7177_ReadReg(dev, AD7177_REG_ID, &v);
	if(st == HAL_OK)
		*id = (uint16_t)v;

	return st;
}

HAL_StatusTypeDef AD7177_Init(AD7177_Handle *dev)
{
	HAL_StatusTypeDef st;
	uint16_t id;
	uint32_t reg;

	AD7177_CS_High(dev);

	st = AD7177_Reset(dev);
	if(st != HAL_OK)
		return st;

	// Confirm the chip responds and is an AD7177-2
	st = AD7177_ReadID(dev, &id);
	if(st != HAL_OK)
		return st;
	if((id & AD7177_ID_MASK) != AD7177_ID_VALUE)
		return HAL_ERROR;

	// Setup 0: polarity, reference, and input/reference buffers
	reg = AD7177_SETUP_REF_SEL(dev->ref_sel);
	if(dev->bipolar)
		reg |= AD7177_SETUP_BIPOLAR;

	// Enable input and reference buffers for robust operation on AD7177
	reg |= AD7177_SETUP_AIN_BUF(3) | AD7177_SETUP_REF_BUF(3);

	st = AD7177_WriteReg(dev, AD7177_REG_SETUPCON(0), reg);
	if(st != HAL_OK)
		return st;

	// Setup 0 filter: order and ODR
	reg = AD7177_FILT_ORDER(0) | AD7177_FILT_ODR(dev->odr);
	st = AD7177_WriteReg(dev, AD7177_REG_FILICON(0), reg);
	if(st != HAL_OK)
	    return st;

	// Channel 0: enabled, uses setup 0, selected inputs
	reg = AD7177_CH_EN
	    | AD7177_CH_SEL(0)
	    | AD7177_CH_AINPOS(dev->ain_pos)
	    | AD7177_CH_AINNEG(dev->ain_neg);
	st = AD7177_WriteReg(dev, AD7177_REG_CH(0), reg);
	if(st != HAL_OK)
		return st;

	// ADC mode: continuous conversion, internal oscillator
	reg = AD7177_ADCMODE_MODE(AD7177_MODE_CONTINUOUS) | AD7177_ADCMODE_CLOCKSEL(0);
	if(dev->ref_sel == AD7177_REF_INTERNAL)
		reg |= AD7177_ADCMODE_REF_EN;
	st = AD7177_WriteReg(dev, AD7177_REG_ADCMODE, reg);
	if(st != HAL_OK)
		return st;

	// Read back channel 0 to confirm the writes landed
	st = AD7177_ReadReg(dev, AD7177_REG_CH(0), &reg);
	if(st != HAL_OK)
		return st;
	if((reg & AD7177_CH_EN) == 0)
		return HAL_ERROR;

	return HAL_OK;
}

// conversions

HAL_StatusTypeDef AD7177_SetMode(AD7177_Handle *dev, AD7177_Mode mode)
{
	uint32_t reg;
	HAL_StatusTypeDef st = AD7177_ReadReg(dev, AD7177_REG_ADCMODE, &reg);
	if(st != HAL_OK)
		return st;
	reg &= ~AD7177_ADCMODE_MODE_MASK;
	reg |= AD7177_ADCMODE_MODE(mode);
	return AD7177_WriteReg(dev, AD7177_REG_ADCMODE, reg);
}

// Conversions

// Poll STATUS until RDY goes low
HAL_StatusTypeDef AD7177_WaitReady(AD7177_Handle *dev, uint32_t timeout_ms)
{
	uint32_t start = HAL_GetTick();
	uint32_t status;
	HAL_StatusTypeDef st;

	do {
		st = AD7177_ReadReg(dev, AD7177_REG_STATUS, &status);
		if(st != HAL_OK) return st;
		if((status & AD7177_STATUS_RDY_N) == 0) {
			if(status & AD7177_STATUS_ADC_ERR) return HAL_ERROR;
			return HAL_OK;
		}
	} while ((HAL_GetTick() - start) < timeout_ms);

	return HAL_TIMEOUT;
}

HAL_StatusTypeDef AD7177_ReadData(AD7177_Handle *dev, uint32_t *code, uint32_t timeout_ms)
{
	HAL_StatusTypeDef st = AD7177_WaitReady(dev, timeout_ms);
	if(st != HAL_OK)
		return st;
	return AD7177_ReadReg(dev, AD7177_REG_DATA, code);
}

// Start one conversion, wait, read the result. ADC returns to standby afterward
HAL_StatusTypeDef AD7177_ReadSingle(AD7177_Handle *dev, uint32_t *code, uint32_t timeout_ms)
{
	HAL_StatusTypeDef st = AD7177_SetMode(dev, AD7177_MODE_SINGLE);
	if(st != HAL_OK)
		return st;
	return AD7177_ReadData(dev, code, timeout_ms);
}

float AD7177_CodeToVolts(const AD7177_Handle *dev, uint32_t code)
{
	if(dev->bipolar){
		// 32-bit bipolar offset binary conversion:
		// 0x00000000 = -Vref, 0x80000000 = 0 V, 0xFFFFFFFF = +Vref
		return (((float)code / 2147483648.0f) - 1.0f) * dev->vref;
	}

	// 32-bit unipolar conversion:
	// 0x00000000 = 0 V, 0xFFFFFFFF = +Vref
	return ((float)code / 4294967296.0f) * dev->vref;
}
