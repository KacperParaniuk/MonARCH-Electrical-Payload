/*
 * ad7124_sensor.c
 *
 *  Created on: Mar 17, 2026
 *      Author: Kacper Paraniuk
 */



#include "ad7124_sensor.h"





float ad7124_read_channel_voltage(struct ad7124_dev *device, uint8_t channel){

	int32_t sample;

	for(int i=0; i < 8; i++){
        ad7124_set_channel_status(device, i, false);
	} // disable all channels.


	ad7124_set_channel_status(device, channel, true); // set channel want to read from.

	ad7124_set_adc_mode(device, AD7124_SINGLE);

	 // wait for conv to complete
	if (ad7124_wait_for_conv_ready(device, 25000) != 0)
	    return -1.0f;  // timeout

	 // read the result
	if (ad7124_read_data(device, &sample) != 0)
	    return -1.0f;  // read error

	 // adc powers down after conversion.

	 return ((float)sample/16777216.0f) * 3.3f; // GAIN = 1

}


float ad7124_read_channel_current_pc104(struct ad7124_dev *device, uint8_t channel){

	float v_meas;
	uint8_t voltage_divider = 0.242; // 100k / (312.5k + 100k)
	uint32_t v_shunt;

	v_meas = ad7124_read_channel_voltage(device, channel);
	v_shunt = v_meas/voltage_divider;

	// 1L000 = 0.001 Ω

	return v_shunt / .001; // Current Reading



}



