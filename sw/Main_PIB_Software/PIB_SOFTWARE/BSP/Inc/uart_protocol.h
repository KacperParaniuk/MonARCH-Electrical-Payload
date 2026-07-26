/*
 * uart_protocol.h
 *
 *  Created on: Mar 16, 2026
 *      Author: Kacper Paraniuk
 */

#ifndef INC_UART_PROTOCOL_H_
#define INC_UART_PROTOCOL_H_


// UART Commands for ADC7124 PT Readings.

#define CMD_READ_PT1    0x01
#define CMD_READ_PT2    0x02
#define CMD_READ_PT3    0x03
#define CMD_READ_PT4    0x04
#define CMD_READ_PT5    0x05
#define CMD_READ_PT6    0x06
#define CMD_READ_PT7    0x07
#define CMD_READ_PT8    0x08


// UART Commands for ADC7124 PC104 Stack Readings

#define CMD_READ_12VA_VB 0x33
#define CMD_READ_12VA_VA 0x34 // Valves
#define CMD_READ_3V3_VB 0x35
#define CMD_READ_3V3_VA 0x36
#define CMD_READ_VBAT_VA 0x42
#define CMD_READ_VBAT_VB 0x43
#define CMD_READ_12VB_VA 0x44
#define CMD_READ_12VB_VB 0x45

#define CMD_READ_12VA_VB_CURRENT 0x46
#define CMD_READ_12VA_VA_CURRENT 0x47 // Valves
#define CMD_READ_3V3_VB_CURRENT 0x48
#define CMD_READ_3V3_VA_CURRENT 0x49
#define CMD_READ_VBAT_VA_CURRENT 0x4A
#define CMD_READ_VBAT_VB_CURRENT 0x4B
#define CMD_READ_12VB_VA_CURRENT 0x4C
#define CMD_READ_12VB_VB_CURRENT 0x4D


// UART Commands for MAX31856 TC Readings

#define CMD_READ_TC1    0x09
#define CMD_READ_TC2	0x0A
#define CMD_READ_TC3	0x0B
#define CMD_READ_TC4	0x0C
#define CMD_READ_TC5	0x0D


// UART Commands for Solenoid Valves

#define CMD_OPEN_SOL1  0x0E
#define CMD_OPEN_SOL2  0x0F
#define CMD_OPEN_SOL3  0x11
#define CMD_OPEN_SOL4  0x12
#define CMD_OPEN_SOL5  0x13
#define CMD_OPEN_SOL6  0x14
#define CMD_OPEN_SOL7  0x15
#define CMD_OPEN_SOL8  0x16
#define CMD_OPEN_SOL9  0x17
#define CMD_OPEN_SOL10  0x18
#define CMD_OPEN_SOL11  0x19
#define CMD_OPEN_SOL12  0x1A
#define CMD_OPEN_SOL13  0x1B
#define CMD_OPEN_SOL14  0x1C
#define CMD_OPEN_SOL15  0x1D
#define CMD_OPEN_SOL16  0x1E
#define CMD_OPEN_SOL17  0x1F
#define CMD_OPEN_SOL18  0x20


#define CMD_CLOSE_SOL1  0x21
#define CMD_CLOSE_SOL2  0x22
#define CMD_CLOSE_SOL3   0x23
#define CMD_CLOSE_SOL4  0x24
#define CMD_CLOSE_SOL5  0x25
#define CMD_CLOSE_SOL6  0x26
#define CMD_CLOSE_SOL7  0x27
#define CMD_CLOSE_SOL8  0x28
#define CMD_CLOSE_SOL9  0x29
#define CMD_CLOSE_SOL10  0x2A
#define CMD_CLOSE_SOL11  0x2B
#define CMD_CLOSE_SOL12  0x2C
#define CMD_CLOSE_SOL13  0x2D
#define CMD_CLOSE_SOL14  0x2E
#define CMD_CLOSE_SOL15  0x2F
#define CMD_CLOSE_SOL16  0x30
#define CMD_CLOSE_SOL17  0x31
#define CMD_CLOSE_SOL18  0x32


// UART Commands for FDC2214

#define READ_CAPACITANCE_A1 0X37
#define READ_CAPACITANCE_A2 0X38
#define READ_CATALYST_LEVEL_A1 0X39
#define READ_CATALYST_LEVEL_A2 0X3A


// UART Command for heater

#define HEAT_CATALYST 0X3B


// UART Commands for Pressure Regulation (PWM / PID)

#define REGULATE_PRESSURE_INPUT_VALUE 0X3C
#define REGULATE_PRESSURE_2_INPUT_VALUE 0X3D


// UART Commands for PPU Control (OBC -> PIB)

#define PPU_CURRENT_READ_1 0X3E
#define PPU_CURRENT_READ_2 0X3F
#define PPU_ON 0X40
#define PPU_OFF 0X41




// CMDS (PIB -> PPU)


#define PIB_PPU_ON 0X00
#define PIB_PPU_OFF 0X01
#define PIB_PPU_CURRENT_READ_1 0X02
#define PIB_PPU_CURRENT_READ_2 0X03




#define CMD_TOGGLE_LED_RED 0x4E








#endif /* INC_UART_PROTOCOL_H_ */
