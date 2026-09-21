/*
 * mosfet_ctrl.h
 *
 *  Created on: Feb 28, 2026
 *      Author: Kacper Paraniuk
 */

#ifndef INC_MOSFET_CTRL_H_
#define INC_MOSFET_CTRL_H_


#include "gpio_driver.h"
#include <stdbool.h>




void mosfet_enable(GPIO_PinConfig_t *MOSFET);
void mosfet_disbale(GPIO_PinConfig_t *MOSFET);
void mosfet_set_duty(GPIO_PinConfig_t *MOSFET);


struct SOL_State_PWM {
    uint8_t state; 
    uint8_t duty_cyle; 
};

struct Feed_System {
    uint8_t valve_1; 
    uint8_t valve_2;
    uint8_t valve_3;
    struct SOL_State_PWM valve_4;
    uint8_t valve_5; 
    struct SOL_State_PWM valve_6;
    uint8_t valve_7;
    uint8_t valve_8;
    uint8_t valve_9; 
    uint8_t valve_10;
    uint8_t valve_11;
    uint8_t valve_12;
    uint8_t valve_13; 
    uint8_t valve_14;
    uint8_t valve_15;
    uint8_t valve_16;
    uint8_t valve_17;
    uint8_t valve_18;
};


#endif /* INC_MOSFET_CTRL_H_ */
