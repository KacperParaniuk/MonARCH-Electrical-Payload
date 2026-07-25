/*
 * mosfet_ctrl.h
 *
 *  Created on: Feb 28, 2026
 *      Author: Kacper Paraniuk
 */

#ifndef INC_MOSFET_CTRL_H_
#define INC_MOSFET_CTRL_H_


#include "gpio_driver.h"




void mosfet_enable(GPIO_PinConfig_t *MOSFET);
void mosfet_disbale(GPIO_PinConfig_t *MOSFET);
void mosfet_set_duty(GPIO_PinConfig_t *MOSFET);


#endif /* INC_MOSFET_CTRL_H_ */
