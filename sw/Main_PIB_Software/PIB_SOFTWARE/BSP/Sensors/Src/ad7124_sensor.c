/*
 * ad7124_sensor.c
 *
 *  Created on: Mar 17, 2026
 *      Author: Kacper Paraniuk
 */



#include "ad7124_sensor.h"





float ad7124_read_channel_voltage(uint8_t channel){

	int32_t sample;

	for(int i=0; i < 8; i++){
        ad7124_set_channel_status(ad7124, i, false);
	} // disable all channels.


	ad7124_set_channel_status(ad7124, channel, true); // set channel want to read from.

	ad7124_set_adc_mode(ad7124, AD7124_SINGLE);

	 // wait for conv to complete
	if (ad7124_wait_for_conv_ready(ad7124, 25000) != 0)
	    return -1.0f;  // timeout

	 // read the result
	if (ad7124_read_data(ad7124, &sample) != 0)
	    return -1.0f;  // read error

	 // adc powers down after conversion.

	 return ((float)sample/16777216.0f) * 3.3f; // GAIN = 1

}
