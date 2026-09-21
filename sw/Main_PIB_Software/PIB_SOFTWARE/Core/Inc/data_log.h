/*
 * data_log.h
 *
 *  Created on: Sep 21, 2026
 *      Author: Kacper Paraniuk
 */

#ifndef INC_DATA_LOG_H_
#define INC_DATA_LOG_H_






#include "ad7124_console_app.h"
#include "ad7124.h"
#include "max31856.h"
#include "FDC2214.h"

// include all the sensors // inside of the sensor .h files are defined sensor structs

#include "mosfet_ctrl.h"





struct Data_Log {
    // structs of data from sensors

    // K-Type Thermocouples
    struct TC_Data tc1;
    struct TC_Data tc2;
    struct TC_Data tc3;
    struct TC_Data tc4;
    struct TC_Data tc5;

    // Capacitance Measurement

    struct CAP_Data cap;

    // Pressure Measurements

    struct PT_Data pressure_1;
	struct PT_Data pressure_2;
	struct PT_Data pressure_3;
	struct PT_Data pressure_4;
	struct PT_Data pressure_5;
	struct PT_Data pressure_6;
	struct PT_Data pressure_7;
	struct PT_Data pressure_8;


    // Voltage Measurements

    struct ADC_CH_Data _12VA_VB;
	struct ADC_CH_Data _12VA_VA;
	struct ADC_CH_Data _3V3_VB;
	struct ADC_CH_Data _3V3_VA;
	struct ADC_CH_Data _VBAT_VA;
	struct ADC_CH_Data _VBAT_VB;
	struct ADC_CH_Data _12VB_VA;
	struct ADC_CH_Data _12VB_VB;


    // Accelerometer Chip




    // Plume Measurement




    // Valve States

    struct Feed_System valve_states;


};



#endif /* INC_DATA_LOG_H_ */
