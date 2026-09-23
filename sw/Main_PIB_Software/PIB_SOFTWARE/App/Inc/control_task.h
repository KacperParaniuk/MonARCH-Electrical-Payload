/*
 * contro_task.h
 *
 *  Created on: Mar 28, 2026
 *      Author: Kacper Paraniuk
 */

#ifndef INC_CONTROL_TASK_H_
#define INC_CONTROL_TASK_H_


#include <stdbool.h>
#include "max31856.h"
#include "main.h"

#define THRESHOLD_TEMP 60.0f // need to set correct threshold temperature value based on the readings we are getting.
int heat_catalyst(); // input a parameter into here to adjust the duty cycle of pwm signal. / the temperature




#endif /* INC_CONTROL_TASK_H_ */
