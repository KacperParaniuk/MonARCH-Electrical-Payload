/*
 * sensors.c
 *
 *  Created on: Sep 21, 2026
 *      Author: Kacper Paraniuk
 */

#include "sensors.h"

extern max31856_t max31856T1;
extern max31856_t max31856T2;
extern max31856_t max31856T3;
extern max31856_t max31856T4;
extern max31856_t max31856T5;



void update_voltage_data(Payload_System *Payload_Sys){

	float value;


	value = display_channel_sample(CH_12VA_VB,VOLTAGE);

	Payload_Sys->data_log._12VA_VB.voltage = value;

	value = display_channel_sample(CH_12VA_VA,VOLTAGE);

	Payload_Sys->data_log._12VA_VA.voltage = value;

	value = display_channel_sample(CH_3V3_VB,VOLTAGE);

	Payload_Sys->data_log._3V3_VB.voltage = value;

	value = display_channel_sample(CH_3V3_VA,VOLTAGE);

	Payload_Sys->data_log._3V3_VA.voltage = value;

    value = display_channel_sample(CH_VBAT_VA,VOLTAGE);

	Payload_Sys->data_log._VBAT_VA.voltage = value;

	value = display_channel_sample(CH_VBAT_VB,VOLTAGE);

	Payload_Sys->data_log._VBAT_VB.voltage = value;

	value = display_channel_sample(CH_12VB_VA,VOLTAGE);

	Payload_Sys->data_log._12VB_VA.voltage = value;

	value = display_channel_sample(CH_12VB_VB,VOLTAGE);

	Payload_Sys->data_log._12VB_VB.voltage = value;

// Read PC104 Currents

	value = ad7124_read_channel_current_pc104(CH_12VA_VB);

	Payload_Sys->data_log._12VA_VB.current = value;

	value = ad7124_read_channel_current_pc104(CH_12VA_VA);

	Payload_Sys->data_log._12VA_VA.current = value;


	value = ad7124_read_channel_current_pc104(CH_3V3_VB);

	Payload_Sys->data_log._3V3_VB.current = value;


	value = ad7124_read_channel_current_pc104(CH_3V3_VA);

	Payload_Sys->data_log._3V3_VA.current = value;


	value = ad7124_read_channel_current_pc104(CH_VBAT_VA);

	Payload_Sys->data_log._VBAT_VA.current = value;


	value = ad7124_read_channel_current_pc104(CH_VBAT_VB);

	Payload_Sys->data_log._VBAT_VB.current = value;


	value = ad7124_read_channel_current_pc104(CH_12VB_VA);

	Payload_Sys->data_log._12VB_VA.current = value;


	value = ad7124_read_channel_current_pc104(CH_12VB_VB);

	Payload_Sys->data_log._12VB_VB.current = value;

}


void update_pressure_data(Payload_System *Payload_Sys){


//
//	case CMD_READ_PT1:
//		value =  0; // ad7124_read_pressure(CH_P0);
//		// will need to convert the voltage value to a current / temp reading function eventually in ad7124.h
//		Serial_Printf("Pressure Reading PT 1: %d \r\n", value);
//	break;
//	case CMD_READ_PT2:
//		value = 0; // ad7124_read_pressure(CH_P1);
//		Serial_Printf("Pressure Reading PT 2: %d \r\n", value);
//	break;
//	case CMD_READ_PT3:
//		value = 0; // ad7124_read_pressure(CH_P2);
//		Serial_Printf("Pressure Reading PT 3: %d \r\n", value);
//	break;
//	case CMD_READ_PT4:
//		value = 0; // ad7124_read_pressure(CH_P3);
//		Serial_Printf("Pressure Reading PT 4: %d \r\n", value);
//	break;
//	case CMD_READ_PT5:
//		value = 0; // ad7124_read_pressure(CH_P4);
//		Serial_Printf("Pressure Reading PT 5: %d \r\n", value);
//	break;
//	case CMD_READ_PT6:
//		value = 0; // ad7124_read_pressure(CH_P5);
//		Serial_Printf("Pressure Reading PT 6: %d \r\n", value);
//	break;
//	case CMD_READ_PT7:
//		value = 0; // ad7124_read_pressure(CH_P6);
//		Serial_Printf("Pressure Reading PT 7: %d \r\n", value);
//	break;
//	case CMD_READ_PT8:
//		value = 0; // ad7124_read_pressure(CH_P7);
//		Serial_Printf("Pressure Reading PT 8: %d \r\n", value);
//	break;




}



void update_temperature_data(Payload_System *Payload_Sys){

	float temperature;

	// cold junction temperatures


	temperature = max31856_read_CJ_temp(&max31856T1);

	Payload_Sys->data_log.tc1.cj_temp = temperature;

	temperature = max31856_read_CJ_temp(&max31856T2);

	Payload_Sys->data_log.tc2.cj_temp = temperature;

	temperature = max31856_read_CJ_temp(&max31856T3);

	Payload_Sys->data_log.tc3.cj_temp = temperature;

	temperature = max31856_read_CJ_temp(&max31856T4);

	Payload_Sys->data_log.tc4.cj_temp = temperature;

	temperature = max31856_read_CJ_temp(&max31856T5);

	Payload_Sys->data_log.tc5.cj_temp = temperature;


	// Read MAX31856 Temperatures

	temperature = max31856_read_TC_temp(&max31856T1); // compensates already for cold junction reading

	Payload_Sys->data_log.tc1.tc_temp = temperature;
	// max31856_read_fault(&max31856T1);

	// Serial_Printf("TC Read Fail ERROR TC1 #: %d \n", max31856T1.sr.val);
	//print_errors(max31856T1.sr.val); // test functionality of error discerning

	temperature = max31856_read_TC_temp(&max31856T2); // compensates already for cold junction reading

	Payload_Sys->data_log.tc2.tc_temp = temperature;

	temperature = max31856_read_TC_temp(&max31856T3); // compensates already for cold junction reading

	Payload_Sys->data_log.tc3.tc_temp = temperature;

	temperature = max31856_read_TC_temp(&max31856T4); // compensates already for cold junction reading

	Payload_Sys->data_log.tc4.tc_temp = temperature;

	temperature = max31856_read_TC_temp(&max31856T5); // compensates already for cold junction reading

	Payload_Sys->data_log.tc5.tc_temp = temperature;

}



void update_valve_states(Payload_System *Payload_Sys){ // pointer so we can reference the global struct
	uint8_t pinState = 0;

	pinState = HAL_GPIO_ReadPin(valve1_GPIO_Port, valve1_Pin);
	Payload_Sys->data_log.valve_states.valve_1 = pinState;

	pinState = HAL_GPIO_ReadPin(valve2_GPIO_Port, valve2_Pin);
	Payload_Sys->data_log.valve_states.valve_2 = pinState;

	pinState = HAL_GPIO_ReadPin(valve3_GPIO_Port, valve3_Pin);
	Payload_Sys->data_log.valve_states.valve_3 = pinState;

	pinState = HAL_GPIO_ReadPin(TIM8_CH1_VALVE4_GPIO_Port, TIM8_CH1_VALVE4_Pin);
	Payload_Sys->data_log.valve_states.valve_4.state = pinState;

	pinState = HAL_GPIO_ReadPin(valve5_GPIO_Port, valve5_Pin);
	Payload_Sys->data_log.valve_states.valve_5 = pinState;

	pinState = HAL_GPIO_ReadPin(TIM3_CH3_VALVE6_GPIO_Port, TIM3_CH3_VALVE6_Pin);
	Payload_Sys->data_log.valve_states.valve_6.state = pinState;

	pinState = HAL_GPIO_ReadPin(valve7_GPIO_Port, valve7_Pin);
	Payload_Sys->data_log.valve_states.valve_7 = pinState;

	pinState = HAL_GPIO_ReadPin(valve8_GPIO_Port, valve8_Pin);
	Payload_Sys->data_log.valve_states.valve_8 = pinState;

	pinState = HAL_GPIO_ReadPin(valve9_GPIO_Port, valve9_Pin);
	Payload_Sys->data_log.valve_states.valve_9 = pinState;

	pinState = HAL_GPIO_ReadPin(valve10_GPIO_Port, valve10_Pin);
	Payload_Sys->data_log.valve_states.valve_10 = pinState;

	pinState = HAL_GPIO_ReadPin(valve11_GPIO_Port, valve11_Pin);
	Payload_Sys->data_log.valve_states.valve_11 = pinState;

	pinState = HAL_GPIO_ReadPin(valve12_GPIO_Port, valve12_Pin);
	Payload_Sys->data_log.valve_states.valve_12 = pinState;

	pinState = HAL_GPIO_ReadPin(valve13_GPIO_Port, valve13_Pin);
	Payload_Sys->data_log.valve_states.valve_13 = pinState;

	pinState = HAL_GPIO_ReadPin(valve14_GPIO_Port, valve14_Pin);
	Payload_Sys->data_log.valve_states.valve_14 = pinState;

	pinState = HAL_GPIO_ReadPin(valve15_GPIO_Port, valve15_Pin);
	Payload_Sys->data_log.valve_states.valve_15 = pinState;

	pinState = HAL_GPIO_ReadPin(valve16_GPIO_Port, valve16_Pin);
	Payload_Sys->data_log.valve_states.valve_16 = pinState;

	pinState = HAL_GPIO_ReadPin(valve17_GPIO_Port, valve17_Pin);
	Payload_Sys->data_log.valve_states.valve_17 = pinState;

	pinState = HAL_GPIO_ReadPin(valve18_GPIO_Port, valve18_Pin);
	Payload_Sys->data_log.valve_states.valve_18 = pinState;

}
