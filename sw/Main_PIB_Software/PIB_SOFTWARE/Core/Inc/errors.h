#include "main.h"



enum ErrorCode {
    ERROR_NONE = 0, 
    AD7124_VOLTAGE_SENSOR_ERROR_CRC, // how descriptive do want these? , 
    AD7124_VOLTAGE_SENSOR_ERROR_SPI_READ, // 
    AD7124_PRESSURE_SENSOR_ERROR,
};


