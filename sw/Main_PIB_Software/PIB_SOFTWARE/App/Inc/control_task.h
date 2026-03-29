/*
 * contro_task.h
 *
 *  Created on: Mar 28, 2026
 *      Author: Kacper Paraniuk
 */

#ifndef INC_CONTROL_TASK_H_
#define INC_CONTROL_TASK_H_


#include "main.h"


void open_solenoid(GPIO_TypeDef* GPIO_port, uint16_t GPIO_Pin);
void close_solenoid(GPIO_TypeDef* GPIO_port, uint16_t GPIO_Pin);





#endif /* INC_CONTROL_TASK_H_ */
