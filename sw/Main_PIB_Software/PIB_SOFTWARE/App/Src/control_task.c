/*
 * control_task.c
 *
 *  Created on: Feb 24, 2026
 *      Author: Kacper Paraniuk
 */



#include "control_task.h"


// Solenoid Valve Control Tasks

void open_solenoid(GPIO_TypeDef* GPIO_port, uint16_t GPIO_Pin){
	HAL_GPIO_WritePin(GPIO_port, GPIO_Pin, GPIO_PIN_SET);
}


void close_solenoid(GPIO_TypeDef* GPIO_port, uint16_t GPIO_Pin){
	HAL_GPIO_WritePin(GPIO_port, GPIO_Pin, GPIO_PIN_RESET);
}






void fill_accumulators(){

}






