/*
 * mosfet_ctrl.c
 *
 *  Created on: Feb 24, 2026
 *      Author: Kacper Paraniuk
 */

#include "mosfet_ctrl.h"


void mosfet_enable(GPIO_PinConfig_t *MOSFET){
	GPIO_Driver_Write(MOSFET->port, MOSFET->pin,GPIO_PIN_SET);
}


void mosfet_disable(GPIO_PinConfig_t *MOSFET){
	GPIO_Driver_Write(MOSFET->port, MOSFET->pin, GPIO_PIN_RESET);

}

void mosfet_set_duty(GPIO_PinConfig_t *MOSFET){
	// implement the duty cycle. PWM driver
}





