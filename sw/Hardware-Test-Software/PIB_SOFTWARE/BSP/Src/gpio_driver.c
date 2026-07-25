/*
 * gpio_driver.c
 *
 *  Created on: Feb 24, 2026
 *      Author: Kacper Paraniuk
 */


#include "gpio_driver.h"



void GPIO_Driver_Init(GPIO_PinConfig_t *config){

	 GPIO_InitTypeDef GPIO_InitStruct = {0};

	 GPIO_InitStruct.Pin = config->pin;
	 GPIO_InitStruct.Mode = config->mode;
	 GPIO_InitStruct.Pull = config->pull;
	 GPIO_InitStruct.Speed = config->speed;

	 HAL_GPIO_Init(config->port, &GPIO_InitStruct);
}



void GPIO_Driver_Read(GPIO_TypeDef *port, uint16_t pin){
	HAL_GPIO_ReadPin(port, pin);
}


void GPIO_Driver_Write(GPIO_TypeDef *port, uint16_t pin, GPIO_PinState state){
	HAL_GPIO_WritePin(port, pin, state);
}


void GPIO_Driver_Toggle(GPIO_TypeDef *port, uint16_t pin){
	HAL_GPIO_TogglePin(port, pin);
}
