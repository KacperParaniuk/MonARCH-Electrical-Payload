/*
 * uart_handler.h
 *
 *  Created on: Mar 14, 2026
 *      Author: Kacper Paraniuk
 */

#ifndef INC_UART_HANDLER_H_
#define INC_UART_HANDLER_H_


#include <stdint.h>
#include <stdarg.h>
#include "stm32l4xx_hal.h"
#include "uart_protocol.h"

void Serial_Print(const char *message);
void Serial_Printf(const char *format, ...);

uint8_t cmd_is_safety(uint8_t cmd);


#endif /* INC_UART_HANDLER_H_ */
