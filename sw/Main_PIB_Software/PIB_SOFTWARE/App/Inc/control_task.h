/*
 * contro_task.h
 *
 *  Created on: Mar 28, 2026
 *      Author: Kacper Paraniuk
 */

#ifndef INC_CONTROL_TASK_H_
#define INC_CONTROL_TASK_H_


#include "main.h"
#include <stdbool.h>
#include "max31856.h"


#define THRESHOLD_TEMP 60.0f // need to set correct threshold temperature value based on the readings we are getting.

void open_solenoid(GPIO_TypeDef* GPIO_port, uint16_t GPIO_Pin);
void close_solenoid(GPIO_TypeDef* GPIO_port, uint16_t GPIO_Pin);


int heat_catalyst(); // input a parameter into here to adjust the duty cycle of pwm signal. / the temperature


// for setting pwm valves

// ------ DUTY CYCLE SETTING -------- \\
// 	 HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_3);
//
// 	 // see duty cycle and if does not look good uncomment the bottom code. This is for testing.
//
//// 	  // change duty cycle to 50 %
//// 	 int duty = 50
//// 	 __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, duty);  // TIM1->CCR1 = duty;
//// 	  HAL_Delay(500);  // Wait 500ms before changing duty cycle
///


#endif /* INC_CONTROL_TASK_H_ */
