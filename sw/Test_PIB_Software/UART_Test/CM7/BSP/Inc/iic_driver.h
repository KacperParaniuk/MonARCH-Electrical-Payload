/*
 * iic_driver.h
 *
 *  Created on: Feb 26, 2026
 *      Author: Kacper Paraniuk
 */

#ifndef INC_IIC_DRIVER_H_
#define INC_IIC_DRIVER_H_

#include "main.h"




// read write address (8 Bit)

int iic_write_reg8(I2C_HandleTypeDef *hi2c, uint8_t addr, uint8_t reg, uint8_t *buf, uint16_t len);


// write read address (8 Bit)

int iic_read_reg8(I2C_HandleTypeDef *hi2c, uint8_t addr, uint8_t reg, uint8_t *buf, uint16_t len);


// read write address (16 Bit)

int iic_write_reg16(I2C_HandleTypeDef *hi2c, uint8_t addr, uint8_t reg, uint8_t *buf, uint16_t len);


// write read address (16 Bit)

int iic_read_reg16(I2C_HandleTypeDef *hi2c, uint8_t addr, uint8_t reg, uint8_t *buf, uint16_t len);







#endif /* INC_IIC_DRIVER_H_ */
