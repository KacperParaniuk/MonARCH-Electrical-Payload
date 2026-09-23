/*
 * uart_driver.c
 *
 *  Created on: Feb 24, 2026
 *      Author: Kacper Paraniuk
 */


#include "uart_handler.h"
#include "usart.h"          // gives access to huart2
#include <stdio.h>
#include <stdarg.h>

#include "data_log.h"


void Serial_Print(const char *message){ // need pointer b/c messages will be stored in READ ONLY flash memory
	char buf[128];
	int len = sprintf(buf, "%s\r\n", message); // string print formatted
	HAL_UART_Transmit(&huart3, (uint8_t*)buf, len, 1000);
}

void Serial_Printf(const char *format, ...){ // used for Serial_Printf("Temperature: %d C\r\n", temp")
	char buf[128];
	va_list args; // defines container for ... arguments
	va_start(args, format); // start collecting after 'format' indicates when to start taking "unknown" variables
	int len = vsnprintf(buf, sizeof(buf), format, args); // formats the string
	va_end(args);
	HAL_UART_Transmit(&huart3, (uint8_t *)buf, len, 1000);
}



//%d      // integer          → 42
//%f      // float            → 3.140000
//%.2f    // float 2 decimals → 3.14
//%s      // string           → "hello"
//%c      // single char      → 'A'
//%X      // hex uppercase    → 2A
//%02X    // hex padded       → 0B  (useful for printing command bytes)


uint8_t cmd_is_safety(uint8_t rx_cmd){

	// change CMD_SAFETY_BEGIN val to appropriate starting position of safety cmds
	if(rx_cmd - CMD_SAFETY_BEGIN >= 0){
		return 1;
	}
	else{
		return 0;
	}



}




void printPacketJSON(const struct Data_Log *packet){

	// execute code for printing over UART


    char buff[1024];
    int len = sprintf(buff,"{\"type\": \"data\", \"value\": {\"temperature_1\": %f, \"temperature_2\": %f, \"temperature_3\": %f, \"temperature_4\": %f, \"temperature_5\": %f, \"cj_temperature_1\": %f, \"cj_temperature_2\": %f, \"cj_temperature_3\": %f, \"cj_temperature_4\": %f, \"cj_temperature_5\": %f, \"pressure_1\": %f, \"pressure_2\": %f, \"pressure_3\": %f, \"pressure_4\": %f, \"pressure_5\": %f, \"pressure_6\": %f, \"pressure_7\": %f, \"pressure_8\": %f, \"valve_1\": %d, \"valve_2\": %d, \"valve_3\": %d, \"valve_4\": %d, \"valve_5\": %d, \"valve_6\": %d, \"valve_7\": %d, \"valve_8\": %d, \"valve_9\": %d, \"valve_10\": %d, \"valve_11\": %d, \"valve_12\": %d, \"valve_13\": %d, \"valve_14\": %d, \"valve_15\": %d, \"valve_16\": %d, \"valve_17\": %d, \"valve_18\": %d}}"
    		,packet->tc1.tc_temp,packet->tc2.tc_temp,packet->tc3.tc_temp,packet->tc4.tc_temp,packet->tc5.tc_temp,packet->tc1.cj_temp,packet->tc2.cj_temp,packet->tc3.cj_temp,packet->tc4.cj_temp,packet->tc5.cj_temp,packet->pressure_1.pressure,packet->pressure_2.pressure,packet->pressure_3.pressure,packet->pressure_4.pressure,packet->pressure_5.pressure,packet->pressure_6.pressure,packet->pressure_7.pressure,packet->pressure_8.pressure, packet->valve_states.valve_1, packet->valve_states.valve_2,packet->valve_states.valve_3,packet->valve_states.valve_4,packet->valve_states.valve_5,packet->valve_states.valve_6,packet->valve_states.valve_7,packet->valve_states.valve_8,packet->valve_states.valve_9,packet->valve_states.valve_10,packet->valve_states.valve_11,packet->valve_states.valve_12,packet->valve_states.valve_13,packet->valve_states.valve_14,packet->valve_states.valve_15,packet->valve_states.valve_16,packet->valve_states.valve_17,packet->valve_states.valve_18);


    HAL_UART_Transmit(&huart3, (uint8_t *)buff, len, 1000);




}
