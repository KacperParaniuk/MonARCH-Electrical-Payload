/*
 * LED.h
 *
 *  Created on: Feb 13, 2026
 *      Author: Kacper Paraniuk
 */

#ifndef LED_H_
#define LED_H_

#include "stm32h745xx.h"
#include "stm32h7xx_hal.h"

class LED {
public:
	GPIO_TypeDef* GPIOx;
	uint16_t GPIO_Pin;
	LED(GPIO_TypeDef* gp, uint16_t gp_pin);
	virtual ~LED();
	void On();
	void Off();
	void Toggle();

};

#endif /* LED_H_ */
