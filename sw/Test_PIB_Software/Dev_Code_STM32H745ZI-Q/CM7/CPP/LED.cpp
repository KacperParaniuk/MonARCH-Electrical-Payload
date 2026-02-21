/*
 * LED.cpp
 *
 *  Created on: Feb 13, 2026
 *      Author: Kacper Paraniuk
 */

#include "LED.h"



LED::LED(GPIO_TypeDef* gp, uint16_t gp_pin) {
	// TODO Auto-generated constructor stub
	GPIOx = gp;
	GPIO_Pin = gp_pin;



}

LED::~LED() {
	// TODO Auto-generated destructor stub
}

void LED::On(){

	HAL_GPIO_WritePin(GPIOx, GPIO_Pin, GPIO_PIN_SET);

}


void LED::Off(){
	HAL_GPIO_WritePin(GPIOx, GPIO_Pin, GPIO_PIN_RESET);

}

void LED::Toggle(){
	HAL_GPIO_TogglePin(GPIOx, GPIO_Pin);

}
