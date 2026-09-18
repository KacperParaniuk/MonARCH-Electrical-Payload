



#include "fsm_states.h"
#include "stdbool.h"
#include "systems.h"




// takes data from payload and determines the state based on it.
FSM_State fsm_tick(Payload_System sys);


// for commands to directly change the state the system is in.
bool fsm_switch(Payload_System sys, FSM_State state);
