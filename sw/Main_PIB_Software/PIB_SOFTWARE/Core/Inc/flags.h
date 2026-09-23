#include "stdbool.h"
#include "errors.h"

struct system_flags { // aka command flags that prevent or allow certain commands to be set...
    bool exceed_temp_flag;
    bool exceed_pressure_flag;
    bool heat_experiment;

};


struct error_flags {

    // need to look into how to do error flags and what I want these to hold
    // I want them to hold the different errors the system encounters
    // can I pair this with the errors.h struct??
    
    

};
