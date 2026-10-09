/*
 * pwm.h
 *
 *  Created on: Oct 7, 2026
 *      Author: Kacper Paraniuk
 */

#ifndef INC_PWM_H_
#define INC_PWM_H_



#include <stdint.h>
#include "stm32l4xx_hal.h"   // swap f4 for your family: g0, g4, l4, h7, ...


//uint32_t TIM_CLK_HZ = 80000000;

void pwm_set(TIM_HandleTypeDef *htim, uint32_t channel,
             uint32_t freq_hz, uint32_t duty_pct);



#endif /* INC_PWM_H_ */
