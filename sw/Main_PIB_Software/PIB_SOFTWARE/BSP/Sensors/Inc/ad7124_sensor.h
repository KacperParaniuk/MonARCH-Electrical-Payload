/*
 * ad7124_sensor.h
 *
 *  Created on: Mar 17, 2026
 *      Author: Kacper Paraniuk
 */

#ifndef INC_AD7124_SENSOR_H_
#define INC_AD7124_SENSOR_H_


#include "ad7124.h"


extern struct ad7124_dev *ad7124;        // defined in main.c


#define CH_READ_PT0    0x0B
#define CH_READ_PT1    0x0C
#define CH_READ_PT2    0x0D
#define CH_READ_PT3    0x03
#define CH_READ_PT4    0x04
#define CH_READ_PT5    0x05
#define CH_READ_PT6    0x01
#define CH_READ_PT7    0x02


// Read a specific channel voltage
float ad7124_read_channel_voltage(uint8_t channel);




#endif /* INC_AD7124_SENSOR_H_ */
