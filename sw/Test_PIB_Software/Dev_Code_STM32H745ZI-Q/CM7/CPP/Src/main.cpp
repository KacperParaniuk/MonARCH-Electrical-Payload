/*
 * main.cpp
 *
 *  Created on: Feb 13, 2026
 *      Author: Kacper Paraniuk
 */


#include "main.h"
#include "LED.h"




void CppMain(){

	// main cpp code

//
	LED RED_LED(LED_PIN_GPIO_Port, LED_PIN_Pin);
//	LED GREEN_LED(GPIOB, 0);
//	LED YELLOW_LED(GPIOE, 1);
	RED_LED.On();



	while(1){

		RED_LED.Toggle();
		HAL_Delay(200);









	}








}
