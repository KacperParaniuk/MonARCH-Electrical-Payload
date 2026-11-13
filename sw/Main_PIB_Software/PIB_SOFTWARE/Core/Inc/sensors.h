/*
 * sensors.h
 *
 *  Created on: Sep 21, 2026
 *      Author: Kacper Paraniuk
 */

#ifndef INC_SENSORS_H_
#define INC_SENSORS_H_



#include "systems.h"

void update_voltage_data(Payload_System *Payload_Sys);
void update_pressure_data(Payload_System *Payload_Sys);
void update_temperature_data(Payload_System *Payload_Sys);
void update_valve_states(Payload_System *Payload_Sys);







#endif /* INC_SENSORS_H_ */


