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



struct SOL_State {
    bool state; 
};

struct SOL_State_PWM {
    bool state; 
    uint8_t duty_cyle; 
};

struct Feed_System {
    struct SOL_State valve_1; 
    struct SOL_State valve_2;
    struct SOL_State valve_3;
    struct SOL_State_PWM valve_4;
    struct SOL_State valve_5; 
    struct SOL_State_PWM valve_6;
    struct SOL_State valve_7;
    struct SOL_State valve_8;
    struct SOL_State valve_9; 
    struct SOL_State valve_10;
    struct SOL_State valve_11;
    struct SOL_State valve_12;
    struct SOL_State valve_13; 
    struct SOL_State valve_14;
    struct SOL_State valve_15;
    struct SOL_State valve_16;
    struct SOL_State valve_17;
    struct SOL_State valve_18;
};


#endif /* INC_MOSFET_CTRL_H_ */
