/*
 * gpio_driver.h
 *
 *  Created on: Feb 24, 2026
 *      Author: Kacper Paraniuk
 */

#ifndef INC_GPIO_DRIVER_H_
#define INC_GPIO_DRIVER_H_


#include "main.h"


// Struct for Pin Config
typedef struct{
	GPIO_TypeDef *port;
	uint16_t pin;
	uint32_t mode;
	uint32_t pull;
	uint32_t speed;
}GPIO_PinConfig_t;



// Functions for GPIO Pin Driving

void GPIO_Driver_Init(GPIO_PinConfig_t *config);
void GPIO_Driver_Read(GPIO_TypeDef *port, uint16_t pin);
void GPIO_Driver_Write(GPIO_TypeDef *port, uint16_t pin, GPIO_PinState state);
void GPIO_Driver_Toggle(GPIO_TypeDef *port, uint16_t pin);





#endif /* INC_GPIO_DRIVER_H_ */
