#include "main.h"



enum FSMState {
    STATE_IDLE = 0,
    STATE_BOOT,
    STATE_SETUP, 
    STATE_READ_VOLTAGE,   // fill in states do we really need these? 
    STATE_READ_PRESSURE,
    STATE_READ_TEMPERATURE,
    STATE_ERROR
};

