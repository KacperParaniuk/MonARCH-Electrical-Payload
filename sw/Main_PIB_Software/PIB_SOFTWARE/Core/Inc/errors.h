/*
 * error.h
 *
 *  Created on: Sep 21, 2026
 *      Author: Kacper Paraniuk
 */

#ifndef INC_ERRORS_H_
#define INC_ERRORS_H_

enum ErrorCode {
    ERROR_NONE = 0,
    AD7124_VOLTAGE_SENSOR_ERROR_CRC, // how descriptive do want these? ,
    AD7124_VOLTAGE_SENSOR_ERROR_SPI_READ, //
    AD7124_PRESSURE_SENSOR_ERROR,
};



#endif /* INC_ERRORS_H_ */
