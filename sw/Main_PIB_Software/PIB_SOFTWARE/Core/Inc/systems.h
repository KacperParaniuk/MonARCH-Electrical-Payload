/*
 * system.h
 *
 *  Created on: Sep 21, 2026
 *      Author: Kacper Paraniuk
 */

#ifndef INC_SYSTEMS_H_
#define INC_SYSTEMS_H_


#include "flags.h"
#include "fsm_states.h"
#include "data_log.h"


typedef struct {
    // main struct that will be passed into everything
    enum FSMState fsm_state;  // current sys fsm state
    struct system_flags sys_flags;   // sys flags for allowing and rejecting commands
    struct error_flags err_flags;  // error flags polled throughout the system
    struct Data_Log data_log; // all of payload data

} Payload_System;



#endif /* INC_SYSTEMS_H_ */
