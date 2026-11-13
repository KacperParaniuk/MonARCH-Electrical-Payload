/*
* ad7176.h
* Driver for the AD7177-2 24-bit sigma-delta ADC on the plume measurement board
*
* Target: STM32L4A6 (STM32 HAL)
*
* SPI settings required in the .ioc:
*/

#ifndef AD7177_H
#define AD7177_H

#include "stm32l4xx_hal.h"
#include <stdint.h>

/*---------------------Register addresses---------------*/
#define AD7177_REG_STATUS	0x00
#define AD7177_REG_ADCMODE	0x01
#define AD7177_REG_IFMODE	0x02
#define AD7177_REG_REGCHECK	0x03
#define AD7177_REG_DATA		0x04
#define AD7177_REG_GPIOCON	0x06
#define AD7177_REG_ID		0x07
#define AD7177_REG_CH(n)	(0x10+ (n))  // n =0..3
#define AD7177_REG_SETUPCON(n)	(0x20+ (n))
#define AD7177_REG_FILICON(n)	(0x28+ (n))
#define AD7177_REG_OFFSET(n)	(0x30 + (n))
#define AD7177_REG_GAIN(n)	(0x38+ (n))

// communication register
#define AD7177_COMMS_READ	0x40

// ID register: AD7177-2 reads 0x4FD0
#define AD7177_ID_MASK		0xFFF0
#define AD7177_ID_VALUE		0x4FD0

//STATUS register bits
#define AD7177_STATUS_RDY_N	0x80	// 0 = new conversion ready
#define AD7177_STATUS_ADC_ERR	0x40
#define AD7177_STATUS_CRC_ERR	0x20
#define AD7177_STATUS_REG_ERR	0x10
#define AD7177_STATUS_CH_MASK	0x03

// ADCMODE register fields
#define AD7177_ADCMODE_REF_EN		(1u<<15)
#define AD7177_ADCMODE_SING_CYC		(1u<<13)
#define AD7177_ADCMODE_MODE(x)		(((uint32_t)(x) & 0x3u)<<4)
#define AD7177_ADCMODE_MODE_MASK	(0x7u <<4)
#define AD7177_ADCMODE_CLOCKSEL(x)	(((uint32_t)(x) & 0x3u) <<2)

// CHx register fields
#define AD7177_CH_EN			(1u <<15)
#define AD7177_CH_SEL(x)		(((uint32_t)(x) & 0x3u)<<12)
#define AD7177_CH_AINPOS(x)		(((uint32_t)(x) & 0x1Fu) <<5)
#define AD7177_CH_AINNEG(x)		((uint32_t)(x) & 0x1Fu)

// SETUPCONx register fields (Includes AD7177 true rail-to-rail buffer controls)
#define AD7177_SETUP_BIPOLAR		(1u << 12)
#define AD7177_SETUP_AIN_BUF(x)		(((uint32_t)(x) & 0x3u) << 8)
#define AD7177_SETUP_REF_BUF(x)		(((uint32_t)(x) & 0x3u) << 6)
#define AD7177_SETUP_REF_SEL(x)		(((uint32_t)(x) & 0x3u) << 4)

//FILTCONx register fields
#define AD7177_FILT_ORDER(x)		(((uint32_t)(x) & 0x3u) <<5)
#define AD7177_FILT_ODR(x)		((uint32_t)(x)	& 0x1FU)

/* Output data rate codes for AD7177-2 (Max 10 kSPS) */
#define AD7177_ODR_10000	0x05
#define AD7177_ODR_2500		0x08
#define AD7177_ODR_1000		0x0A
#define AD7177_ODR_100		0x0E
#define AD7177_ODR_10		0x13

typedef enum {
	AD7177_MODE_CONTINUOUS		= 0,
	AD7177_MODE_SINGLE		= 1,
	AD7177_MODE_STANDBY		= 2,
	AD7177_MODE_POWER_DOWN		= 3,
	AD7177_MODE_INT_OFFSET_CAL	= 4,
	AD7177_MODE_SYS_OFFSET_CAL	= 6,
	AD7177_MODE_SYS_GAIN_CAL	= 7
} AD7177_Mode;

typedef enum {
	AD7177_AIN0	= 0,
	AD7177_AIN1	= 1,
	AD7177_AIN2	= 2,
	AD7177_AIN3	= 3,
	AD7177_AIN4	= 4,
	AD7177_TEMP_P	= 17,
	AD7177_TEMP_N	= 18,
	AD7177_REF_P	= 21,
	AD7177_REF_N	= 22
} AD7177_Input;


typedef enum {
	AD7177_REF_EXTERNAL = 0,	/* REF+ / REF- pins */
	AD7177_REF_INTERNAL = 2,	/* internal 2.5 V */
	AD7177_REF_AVDD     = 3		/* AVDD1 - AVSS */
} AD7177_RefSel;

// One handle per chip
// Each chip keeps its own SPI handle, CS ping, and cinfig.
typedef struct{
	SPI_HandleTypeDef *hspi;
	GPIO_TypeDef	  *cs_port;
	uint16_t	   cs_pin;

	AD7177_Input	   ain_pos;
	AD7177_Input	   ain_neg;
	AD7177_RefSel	   ref_sel;
	uint8_t		   bipolar; // 1 = bipolar, 0 = unipolar
	uint8_t		   odr;	    // AD7177_ODR_xxx
	float		   vref;    // reference voltage in volts
} AD7177_Handle;

// Low level
uint8_t		  AD7177_RegSize(uint8_t reg);
HAL_StatusTypeDef AD7177_ReadReg(AD7177_Handle *dev, uint8_t reg, uint32_t *value);
HAL_StatusTypeDef AD7177_WriteReg(AD7177_Handle *dev, uint8_t reg, uint32_t value);
HAL_StatusTypeDef AD7177_Reset(AD7177_Handle *dev);

// Setup
HAL_StatusTypeDef AD7177_Init(AD7177_Handle *dev);
HAL_StatusTypeDef AD7177_ReadID(AD7177_Handle *dev, uint16_t *id);
HAL_StatusTypeDef AD7177_SetMode(AD7177_Handle *dev, AD7177_Mode mode);

// Conversions (32-bit result handling)
HAL_StatusTypeDef AD7177_WaitReady(AD7177_Handle *dev, uint32_t timeout_ms);
HAL_StatusTypeDef AD7177_ReadData(AD7177_Handle *dev, uint32_t *code, uint32_t timeout_ms);
HAL_StatusTypeDef AD7177_ReadSingle(AD7177_Handle *dev, uint32_t *code, uint32_t timeout_ms);
float		  AD7177_CodeToVolts(const AD7177_Handle *dev, uint32_t code);

#endif /* AD7177_H */
