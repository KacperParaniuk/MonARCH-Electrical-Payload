/***************************************************************************//**
*   @file    ad7124.c
*   @brief   AD7124 implementation file.
*   	     Devices: AD7124-4, AD7124-8
*
********************************************************************************
* Copyright 2015-2019, 2023(c) Analog Devices, Inc.
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions are met:
*
* 1. Redistributions of source code must retain the above copyright notice,
*    this list of conditions and the following disclaimer.
*
* 2. Redistributions in binary form must reproduce the above copyright notice,
*    this list of conditions and the following disclaimer in the documentation
*    and/or other materials provided with the distribution.
*
* 3. Neither the name of Analog Devices, Inc. nor the names of its
*    contributors may be used to endorse or promote products derived from this
*    software without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY ANALOG DEVICES, INC. “AS IS” AND ANY EXPRESS OR
* IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
* MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO
* EVENT SHALL ANALOG DEVICES, INC. BE LIABLE FOR ANY DIRECT, INDIRECT,
* INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
* LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
* OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
* LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
* NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
* EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.******************************************************************************/

#include <stdlib.h>
#include <stdbool.h>
#include "ad7124.h"
#include "errno.h"


//#include "no_os_delay.h"
//#include "no_os_alloc.h"
//#include "no_os_error.h"

/*
 * Post reset delay required to ensure all internal config done
 * A time of 2ms should be enough based on the data sheet, but 4ms
 * chosen to provide enough margin, in case mdelay is not accurate.
 */
#define AD7124_POST_RESET_DELAY	4
#define	EINVAL 22 // INVALID ARGUMENT.
#define	ENOMEM 12	/* Not enough space */
#define EBADMSG 77



/***************************************************************************//**
 * @brief Reads the value of the specified register without checking if the
 *        device is ready to accept user requests.
 * @param dev   - The handler of the instance of the driver.
 * @param p_reg - Pointer to the register structure holding info about the
 * 	l
 * 	l
 * 	l
 * 	lll
 * 	ll
 *               register to be read. The read value is stored inside the
 *               register structure.
 * @return Returns 0 for success or negative error code otherwise.
*******************************************************************************/

// Edited by Kacper Paraniuk


int32_t ad7124_no_check_read_register(struct ad7124_dev *dev,
				      struct ad7124_st_reg* p_reg)
{
//	int32_t ret = 0;

	uint8_t buffer[8] = { 0 };
	uint8_t i = 0;
	uint8_t check8 = 0, add_status_length = 0;
	uint8_t msg_buf[8] = { 0 };

	if (!dev || !p_reg)
		return -EINVAL;

	/* Build the Command word */
	buffer[0] = AD7124_COMM_REG_WEN | AD7124_COMM_REG_RD |
		    AD7124_COMM_REG_RA(p_reg->addr);

	/*
	 * If this is an AD7124_DATA register read, and the DATA_STATUS bit is set
	 * in ADC_CONTROL, need to read 4, not 3 bytes for DATA with STATUS
	 */
	if ((p_reg->addr == AD7124_DATA_REG) &&
	    (dev->regs[AD7124_ADC_Control].value & AD7124_ADC_CTRL_REG_DATA_STATUS))
		add_status_length = 1;

	/* Read data from the device */
//
//	ret = no_os_spi_write_and_read(dev->spi_desc,
//				       buffer,
//				       ((dev->use_crc != AD7124_DISABLE_CRC) ? p_reg->size + 1
//					: p_reg->size) + 1 + add_status_length);

	// replaced with

	uint8_t transfer_size = ((dev->use_crc != AD7124_DISABLE_CRC) ? p_reg->size + 1 // different bytes for different registers.
	                        : p_reg->size) + 1 + add_status_length;

	HAL_GPIO_WritePin(dev->cs_port, dev->cs_pin, GPIO_PIN_RESET);
	if (HAL_SPI_TransmitReceive(dev->hspi, buffer, buffer, transfer_size, 100) != HAL_OK)
		    return -EIO;
	HAL_GPIO_Writ ePin(dev->cs_port, dev->cs_pin, GPIO_PIN_SET);


	/* Check the CRC */
	if (dev->use_crc == AD7124_USE_CRC) {
		msg_buf[0] = AD7124_COMM_REG_WEN | AD7124_COMM_REG_RD |
			     AD7124_COMM_REG_RA(p_reg->addr);
		for (i = 1; i < p_reg->size + 2 + add_status_length; ++i)
			msg_buf[i] = buffer[i];
		check8 = ad7124_compute_crc8(msg_buf, p_reg->size + 2 + add_status_length);
	}

	if (check8)
		/* ReadRegister checksum failed. */
		return -EBADMSG;

	/*
	 * if reading Data with 4 bytes, need to copy the status byte to the STATUS
	 * register struct value member
	 */

	if (add_status_length)
		dev->regs[AD7124_Status].value = buffer[p_reg->size + 1];

	/* Build the result */
	p_reg->value = 0;
	for (i = 1; i < p_reg->size + 1; i++) {
		p_reg->value <<= 8;
		p_reg->value += buffer[i];
	}

	return 0;
}

/***************************************************************************//**
 * @brief Writes the value of the specified register without checking if the
 *        device is ready to accept user requests.
 * @param dev - The handler of the instance of the driver.
 * @param reg - Register structure holding info about the register to be written
 * @return Returns 0 for success or negative error code otherwise.
*******************************************************************************/
int32_t ad7124_no_check_write_register(struct ad7124_dev *dev,
				       struct ad7124_st_reg reg)
{
	int32_t reg_value = 0;
	uint8_t wr_buf[8] = { 0 };
	uint8_t i = 0;
	uint8_t crc8 = 0;

	if (!dev)
		return -EINVAL;

	/* Build the Command word */
	wr_buf[0] = AD7124_COMM_REG_WEN | AD7124_COMM_REG_WR |
		    AD7124_COMM_REG_RA(reg.addr);

	/* Fill the write buffer */
	reg_value = reg.value;
	for (i = 0; i < reg.size; i++) {
		wr_buf[reg.size - i] = reg_value & 0xFF;
		reg_value >>= 8;
	}

	/* Compute the CRC */
	if (dev->use_crc != AD7124_DISABLE_CRC) {
		crc8 = ad7124_compute_crc8(wr_buf, reg.size + 1);
		wr_buf[reg.size + 1] = crc8;
	}

	uint8_t size = (dev->use_crc != AD7124_DISABLE_CRC) ? reg.size + 2
			: reg.size + 1;

	HAL_GPIO_WritePin(dev->cs_port, dev->cs_pin, GPIO_PIN_RESET);
	if (HAL_SPI_TransmitReceive(dev->hspi, wr_buf, wr_buf, size, 100)
			!= HAL_OK)
		return -EIO;
	HAL_GPIO_WritePin(dev->cs_port, dev->cs_pin, GPIO_PIN_SET);


//
//		no_os_spi_write_and_read(dev->spi_desc,
//						wr_buf,
//						(dev->use_crc != AD7124_DISABLE_CRC) ? reg.size + 2
//						: reg.size + 1);

	return 0;
}



/***************************************************************************//**
 * @brief Reads the value of the specified register only when the device is ready
 *        to accept user requests. If the device ready flag is deactivated the
 *        read operation will be executed without checking the device state.
 *        DEPRECATED, use ad7124_read_register2.
 * @param dev   - The handler of the instance of the driver.
 * @param p_reg - Pointer to the register structure holding info about the
 *               register to be read. The read value is stored inside the
 *               register structure.
 * @return Returns 0 for success or negative error code otherwise.
*******************************************************************************/
int32_t ad7124_read_register(struct ad7124_dev *dev,
			     struct ad7124_st_reg* p_reg)
{
	int32_t ret;

	if (p_reg->addr != AD7124_ERR_REG && dev->check_ready) {
		ret = ad7124_wait_for_spi_ready(dev,
						dev->spi_rdy_poll_cnt);
		if (ret)
			return ret;
	}

	return ad7124_no_check_read_register(dev,
					     p_reg);
}

/***************************************************************************//**
 * @brief Wrap the read register function to give it a modern signature.
 * @param [in] dev - Driver handler pointer.
 * @param [in] reg - Address of the register to be read.
 * @param [out] readval - Pointer to the register value.
 * @return Returns 0 for success or negative error code otherwise.
***************************************************************************/
int32_t ad7124_read_register2(struct ad7124_dev *dev,
			      uint32_t reg,
			      uint32_t *readval)
{
	int32_t ret;

	ret = ad7124_read_register(dev, &dev->regs[reg]);
	if (ret)
		return ret;

	*readval = dev->regs[reg].value;

	return 0;
}

/**
 * @brief Writes data to a specified register of the AD7124-4 ADC via SPI.
 *
 * Performs an SPI transaction to write `dataSize` bytes of `regValue` to the AD7124 register specified by `regAddr`.
 *
 * @param[in] pADC      Pointer to the AD7124-4 configuration structure containing SPI settings and communication parameters.
 * @param[in] regAddr   8-bit address of the register to write to.
 * @param[in] dataSize  Number of bytes to write to the register.
 * @param[in] regValue  Value to write into the register.
 *
 * @retval AD7124_OK     Register write completed successfully.
 * @retval AD7124_ERROR  Communication failure, CRC mismatch, or invalid parameters.
 */
AD7124_StatusTypeDef AD7124_WriteRegister(const AD7124_ConfigTypeDef *pADC, uint8_t regAddr, uint8_t dataSize, uint32_t regValue)
{
    AD7124_StatusTypeDef status = AD7124_ERROR;
    uint8_t tx_buf[8U] = {0U};
    uint8_t crc = 0U;
    
    if ( (pADC == NULL) || (dataSize == 0U) )
    {
        status = AD7124_ERROR;  
    }
    else
    {
        // Build the Command word
        tx_buf[0U] = (uint8_t)(regAddr & 0x3FU);
        
        // Fill the write buffer
        for (uint8_t i = 0U; i < dataSize; i++)
        {
            tx_buf[i + 1U] = (uint8_t)( (regValue >> (8U * (dataSize - 1U - i) ) ) & 0xFFU);
        }
        
        // Compute the CRC
        crc = AD7124_ComputeCRC8(tx_buf, (uint8_t)(dataSize + 1U));  
        tx_buf[dataSize + 1U] = crc;  
        
        // SPI write transaction
        HAL_GPIO_WritePin(pADC->csPort, pADC->csPin, GPIO_PIN_RESET);
        status = (AD7124_StatusTypeDef) HAL_SPI_Transmit(pADC->SPIx, tx_buf, (dataSize + 2U), AD7124_MAX_DELAY);
        HAL_GPIO_WritePin(pADC->csPort, pADC->csPin, GPIO_PIN_SET);
    }
    
    return status;
}

/**
 * @brief Performs a hardware reset of the AD7124-4 ADC via SPI.
 *
 * Sends the predefined reset sequence over SPI to the AD7124 ADC, restoring all registers to their default reset values.
 *
 * @param[in] pADC     Pointer to the AD7124-4 configuration structure containing SPI settings and communication parameters.
 * @param[in] timeout  Maximum time (in milliseconds) to wait for the reset operation to complete.
 *
 * @retval AD7124_OK      Reset completed successfully.
 * @retval AD7124_ERROR   Communication failure, CRC mismatch, or invalid parameters.
 * @retval AD7124_TIMEOUT The reset operation timed out before completion.
 */
AD7124_StatusTypeDef AD7124_Reset(const AD7124_ConfigTypeDef *pADC, uint32_t timeout)
{  
    AD7124_StatusTypeDef status = AD7124_ERROR;
    const uint8_t reset_sequence[8U] = {0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU};  
    uint32_t start_time   = 0U;
    uint32_t status_value = 0U;        
    
    if ( (pADC == NULL) || (timeout == 0U) )
    {
        status = AD7124_ERROR; 
    }
    else
    { 
        // SPI write transaction
        HAL_GPIO_WritePin(pADC->csPort, pADC->csPin, GPIO_PIN_RESET);
        status = (AD7124_StatusTypeDef) HAL_SPI_Transmit(pADC->SPIx, reset_sequence, 8U, AD7124_MAX_DELAY);
        HAL_GPIO_WritePin(pADC->csPort, pADC->csPin, GPIO_PIN_SET);

        if (status == AD7124_OK)
        {           
            start_time = HAL_GetTick();        
            do 
            {
                // Wait for STATUS register until RDY bit is cleared or timeout expires
                if (AD7124_ReadRegister(pADC, AD7124_STATUS_REG, 1U, &status_value) != AD7124_OK)
                {
                    status = AD7124_ERROR;
                    break;
                }
            } while ( ( (status_value & 0x10U) != 0U) && ( (HAL_GetTick() - start_time) < timeout) );

            if ( (status_value & 0x10U) != 0U)
            {
                status = AD7124_TIMEOUT; 
            }
            else
            {               
                HAL_Delay(4U);  // Allow ADC stabilization               
                status = AD7124_WriteRegister(pADC, AD7124_ERREN_REG, 3U, 0x00004U);  // Enable CRC error detection
            }
        }      
    }
    
    return status;
}

/**
 * @brief Initializes and configures the AD7124-4 ADC registers.
 *
 * Writes predefined settings to the ADC's channel mapping, configuration,
 * and filter registers to prepare the device for data acquisition.
 *
 * @param[in] pADC     Pointer to the AD7124-4 configuration structure containing SPI settings and communication parameters.
 * @param[in] pConfig  Pointer to the AD7124-4 register configuration structure specifying
 *                    the desired settings for channels, filters, and configurations.
 *
 * @retval AD7124_OK     Registers configured successfully.
 * @retval AD7124_ERROR  Communication failure, CRC mismatch, or invalid parameters.
 */
AD7124_StatusTypeDef AD7124_Config(const AD7124_ConfigTypeDef *pADC, AD7124_RegisterTypeDef *pConfig)
{
    AD7124_StatusTypeDef status = AD7124_OK;
    
    static const uint8_t channelRegs[16U] = // changed to 16
    {
        AD7124_CH0_MAP_REG, AD7124_CH1_MAP_REG, AD7124_CH2_MAP_REG,
        AD7124_CH3_MAP_REG, AD7124_CH4_MAP_REG, AD7124_CH5_MAP_REG,
        AD7124_CH6_MAP_REG, AD7124_CH7_MAP_REG, AD7124_CH8_MAP_REG,
		AD7124_CH9_MAP_REG, AD7124_CH10_MAP_REG, AD7124_CH11_MAP_REG,
		AD7124_CH12_MAP_REG, AD7124_CH13_MAP_REG, AD7124_CH14_MAP_REG,
		AD7124_CH15_MAP_REG
    };

    static const uint8_t configRegs[8U] =
    {
        AD7124_CFG0_REG, AD7124_CFG1_REG, AD7124_CFG2_REG,
        AD7124_CFG3_REG, AD7124_CFG4_REG, AD7124_CFG5_REG,
        AD7124_CFG6_REG, AD7124_CFG7_REG
    };
    
    static const uint8_t filterRegs[8U] =
    {
        AD7124_FILT0_REG, AD7124_FILT1_REG, AD7124_FILT2_REG,
        AD7124_FILT3_REG, AD7124_FILT4_REG, AD7124_FILT5_REG,
        AD7124_FILT6_REG, AD7124_FILT7_REG
    };
    
    if ( (pADC == NULL) || (pConfig == NULL) )
    {
        status = AD7124_ERROR;
    }
    else
    {
        for (int8_t i = AD7124_CHANNEL_COUNT-1; i >= 0; i--)
        {
            if (AD7124_WriteRegister(pADC, channelRegs[i], 2U, pConfig->channels[i]) != AD7124_OK)
            {
                status = AD7124_ERROR;
                break;
            }
        }

        for (int8_t i = 7; i >= 0; i--)
        {
            if (AD7124_WriteRegister(pADC, configRegs[i],  2U, pConfig->configs[i])  != AD7124_OK ||
                AD7124_WriteRegister(pADC, filterRegs[i],  3U, pConfig->filters[i])  != AD7124_OK)
            {
                status = AD7124_ERROR;
                break;
            }
        }
        if (status == AD7124_OK)
        {
            if (AD7124_WriteRegister(pADC, AD7124_CONTROL_REG,  2U, pConfig->adc_control)  != AD7124_OK ||
                AD7124_WriteRegister(pADC, AD7124_IO_CTRL1_REG, 3U, pConfig->io_control_1) != AD7124_OK ||
                AD7124_WriteRegister(pADC, AD7124_IO_CTRL2_REG, 2U, pConfig->io_control_2) != AD7124_OK ||
                AD7124_WriteRegister(pADC, AD7124_ERREN_REG,    3U, pConfig->error_enable) != AD7124_OK)
            {
                status = AD7124_ERROR;
            }
        }
    }
    
    return status;
}

/**
 * @brief Reads ADC conversion data from the AD7124-4 and updates the channel samples array.
 *
 * Retrieves the latest conversion result from the AD7124-4 over SPI and stores the sample
 * value in the corresponding element of the external `AD7124_ChannelSamples` array.
 * Supports reading from multiple enabled and configured ADC channels.
 *
 * @param[in] pADC  Pointer to the AD7124 configuration structure containing SPI settings and communication parameters.
 *
 * @retval AD7124_OK     Sample data read successfully.
 * @retval AD7124_ERROR  Communication failure, CRC mismatch, or invalid parameters.
 *
 * @note The `AD7124_ChannelSamples` array must be defined and managed by the user.
 */
AD7124_StatusTypeDef AD7124_ReadSampleData(const AD7124_ConfigTypeDef *pADC)
{
    AD7124_StatusTypeDef status = AD7124_OK;
    uint32_t  sample_data  = 0U;
    uint32_t  status_reg   = 0U;
    uint8_t active_channel = 0U;
    
    if (pADC == NULL)
    {
        status = AD7124_ERROR;
    }
    else
    {
        // Read samples for the number of enabled channels
        for (uint8_t i = 0U; i < AD7124_ENABLED_CHANNELS; i++)
        {
            // Read ADC data and status registers
            if ( (AD7124_ReadRegister(pADC, AD7124_DATA_REG, 3U, &sample_data) != AD7124_OK) || 
                 (AD7124_ReadRegister(pADC, AD7124_STATUS_REG, 1U, &status_reg) != AD7124_OK) )
            {
                status = AD7124_ERROR;
                break;
            }
            
            // Extract active channel index (lower 4 bits)
            active_channel = (uint8_t)(status_reg & 0x0FU);
            
            // Store sample if channel index is valid
            if (active_channel < AD7124_ENABLED_CHANNELS)
            {
                AD7124_ChannelSamples[active_channel] = sample_data;
            }
        }
    }

    return status;
}

/**
 * @brief Checks the AD7124-4 ADC error status by reading the error register.
 *
 * Reads the error register of the AD7124-4 via SPI to detect any ADC errors.
 * The error status is stored at the location pointed to by `pErrorReg`.
 * If the read operation fails, `*pErrorReg` is set to -1 to indicate failure.
 *
 * @param[in]  pADC       Pointer to the AD7124 configuration structure containing SPI settings and communication parameters.
 * @param[out] pErrorReg  Pointer to an integer where the error register value will be stored.
 *
 * @retval AD7124_OK      Error register read successfully.
 * @retval AD7124_ERROR   Communication failure, CRC mismatch, or invalid parameters.
 */
AD7124_StatusTypeDef AD7124_ErrorCheck(const AD7124_ConfigTypeDef *pADC, int32_t *pErrorReg)
{
    AD7124_StatusTypeDef status = AD7124_ERROR;
    uint32_t data = 0U;
    
    if (pADC == NULL)
    {
//        status = AD7124_ERROR;
    	status = 10;
    }
    else
    {     
        if (AD7124_ReadRegister(pADC, AD7124_ERR_REG, 3U, &data) == AD7124_OK)
        {
            *pErrorReg = (int32_t)data;
            status = AD7124_OK;
        }
        else
        {
            *pErrorReg = -1;
//            status = AD7124_ERROR;
            status = 11;
        }
    }
    
    return status;
}

/**
 * @brief Performs gain and offset calibration on the AD7124-4 ADC.
 *
 * Executes internal full-scale and zero-scale calibrations to improve accuracy of the AD7124.
 * Reads the updated gain and offset coefficients from the device and updates the provided
 * configuration structure accordingly. After calibration, the ADC settings are restored to
 * their default operational values.
 *
 * @param[in]     pADC     Pointer to the AD7124-4 configuration structure
 *                        containing SPI settings and communication parameters.
 * @param[in,out] pConfig  Pointer to the register configuration structure, which will be
 *                        updated with calibrated gain and offset values upon success.
 * @param[in]     timeout  Maximum time (in ticks) to wait for each calibration step to complete.
 *
 * @retval AD7124_OK       Calibration completed successfully.
 * @retval AD7124_ERROR    Communication failure, CRC mismatch, or invalid parameters.
 * @retval AD7124_TIMEOUT  Calibration timed out before completion.
 */
AD7124_StatusTypeDef AD7124_Calibration(const AD7124_ConfigTypeDef *pADC, AD7124_RegisterTypeDef *pConfig, uint32_t timeout)
{
    AD7124_StatusTypeDef status = AD7124_OK;
    uint16_t default_config = pConfig->adc_control; 
    uint32_t start_tick = 0U;
    uint32_t  data      = 0U;
       
    if ( (pADC == NULL) || (pConfig == NULL) || (timeout == 0U) )
    {
        status = AD7124_ERROR;
    }
    else
    {    
        // Internal full-scale (gain) calibration
        pConfig->adc_control = (pConfig->adc_control & ~AD7124_CONTROL_MODE_MASK) | AD7124_CONTROL_CAL_GAIN;       
        if (AD7124_WriteRegister(pADC, AD7124_CONTROL_REG, 2U, pConfig->adc_control) != AD7124_OK)
        {
            status = AD7124_ERROR;
        }
        else
        {
            start_tick = HAL_GetTick();           
            // Wait until calibration completes or timeout occurs
            do
            {
                if (AD7124_ReadRegister(pADC, AD7124_STATUS_REG, 1U, &data) != AD7124_OK)
                {
                    status = AD7124_ERROR;
                    break;
                }
                if ( (HAL_GetTick() - start_tick) >= timeout)
                {
                    status = AD7124_TIMEOUT;
                    break;
                }
            } while ( (data & 0x80U) != 0U);
        }

        if (status == AD7124_OK)
        {
            // Internal zero-scale (offset) calibration
            pConfig->adc_control = (pConfig->adc_control & ~AD7124_CONTROL_MODE_MASK) | AD7124_CONTROL_CAL_OFFSET;
            if (AD7124_WriteRegister(pADC, AD7124_CONTROL_REG, 2U, pConfig->adc_control) != AD7124_OK)
            {
                status = AD7124_ERROR;
            }
            else
            {
                start_tick = HAL_GetTick();              
                // Wait until calibration completes or timeout occurs
                do
                {
                    if (AD7124_ReadRegister(pADC, AD7124_STATUS_REG, 1U, &data) != AD7124_OK)
                    {
                        status = AD7124_ERROR;
                        break;
                    }
                    if ((HAL_GetTick() - start_tick) >= timeout)
                    {
                        status = AD7124_TIMEOUT;
                        break;
                    }
                } while ( (data & 0x80U) != 0U);
            }
        }

        if (status == AD7124_OK)
        {
            // Standby mode to read/write calibration coefficients
            pConfig->adc_control = (pConfig->adc_control & ~AD7124_CONTROL_MODE_MASK) | AD7124_CONTROL_STANDBY;
            if (AD7124_WriteRegister(pADC, AD7124_CONTROL_REG, 2U, pConfig->adc_control) != AD7124_OK)
            {
                status = AD7124_ERROR;
            }
        }

        if (status == AD7124_OK)
        {
            // Read gain coefficients after calibration
            for (uint8_t i = 0U; i < 8U; i++)
            {
                if (AD7124_ReadRegister(pADC, AD7124_GAIN0_REG + i, 3U, &pConfig->gains[i]) != AD7124_OK)
                {
                    status = AD7124_ERROR;
                    break;
                }
            }
        }

        if (status == AD7124_OK)
        {
            // Read offset coefficients after calibration
            for (uint8_t i = 0U; i < 8U; i++)
            {
                if (AD7124_ReadRegister(pADC, AD7124_OFFS0_REG + i, 3U, &pConfig->offsets[i]) != AD7124_OK)
                {
                    status = AD7124_ERROR;
                    break;
                }
            }
        }

        if (status == AD7124_OK)
        {
            // Write calibrated gain coefficients
            for (uint8_t i = 0U; i < 8U; i++)
            {
                if (AD7124_WriteRegister(pADC, AD7124_GAIN0_REG + i, 3U, pConfig->gains[i]) != AD7124_OK)
                {
                    status = AD7124_ERROR;
                    break;
                }
            }
        }

        if (status == AD7124_OK)
        {
            // Write calibrated offset coefficients
            for (uint8_t i = 0U; i < 8U; i++)
            {
                if (AD7124_WriteRegister(pADC, AD7124_OFFS0_REG + i, 3U, pConfig->offsets[i]) != AD7124_OK)
                {
                    status = AD7124_ERROR;
                    break;
                }
            }
        }

        if (status == AD7124_OK)
        {
            // Restore original ADC control configuration
            if (AD7124_WriteRegister(pADC, AD7124_CONTROL_REG, 2U, default_config) != AD7124_OK)
            {
                status = AD7124_ERROR;
            }
        }
    } 

    return status; 
}


/* ad7124.c */
