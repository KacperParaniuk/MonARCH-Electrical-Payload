/*
 * iic_driver.c
 *
 *  Created on: Feb 26, 2026
 *      Author: Kacper Paraniuk
 */


// includes - provides essential uint




#include "iic_driver.h"


// addr -> Address of peripheral
// reg -> Register of peripheral
// buf -> Buf which stores data and is a pointer so it can be written to
// len -> Size of read/write in bytes


int iic_read_8BIT(I2C_HandleTypeDef *hi2c, uint8_t addr, uint8_t reg, uint8_t *buf, uint16_t len){


	HAL_StatusTypeDef status;

	status = HAL_I2C_Mem_Read(hi2c, addr, reg, I2C_MEMADD_SIZE_8BIT, buf, len, 100);

	// specific function for writing to a specific device addr, and then the register value, then reading to buf


    return (status==HAL_OK) ? 0 : 1;
}


int iic_write_8BIT(I2C_HandleTypeDef *hi2c, uint8_t addr, uint8_t reg, uint8_t *buf, uint16_t len){


	HAL_StatusTypeDef status;

	status = HAL_I2C_Mem_Write(hi2c, addr, reg, I2C_MEMADD_SIZE_8BIT , buf, len, 100);
	// specific function for writing to a specific device addr, and then the register value, and then writing buf value

    return (status==HAL_OK) ? 0 : 1;
}


int iic_read_16BIT(I2C_HandleTypeDef *hi2c, uint8_t addr, uint8_t reg, uint8_t *buf, uint16_t len){

	HAL_StatusTypeDef status;

	status = HAL_I2C_Mem_Read(hi2c, addr, reg, I2C_MEMADD_SIZE_16BIT, buf, len, 100);


    return (status==HAL_OK) ? 0 : 1;
}


int iic_write_16BIT(I2C_HandleTypeDef *hi2c, uint8_t addr, uint8_t reg, uint8_t *buf, uint16_t len){


	HAL_StatusTypeDef status;

	status = HAL_I2C_Mem_Write(hi2c, addr, reg, I2C_MEMADD_SIZE_16BIT , buf, len, 100);


    return (status==HAL_OK) ? 0 : 1;
}
