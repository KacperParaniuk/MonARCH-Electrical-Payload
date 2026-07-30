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
