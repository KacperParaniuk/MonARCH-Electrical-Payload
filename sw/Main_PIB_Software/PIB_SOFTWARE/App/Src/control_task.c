/*
 * control_task.c
 *
 *  Created on: Feb 24, 2026
 *      Author: Kacper Paraniuk
 */



#include "control_task.h"

extern float temp;
extern max31856_t max31856T4;


// Solenoid Valve Control/Sequence Tasks

void open_solenoid(GPIO_TypeDef* GPIO_port, uint16_t GPIO_Pin){
	HAL_GPIO_WritePin(GPIO_port, GPIO_Pin, GPIO_PIN_SET);
}


void close_solenoid(GPIO_TypeDef* GPIO_port, uint16_t GPIO_Pin){
	HAL_GPIO_WritePin(GPIO_port, GPIO_Pin, GPIO_PIN_RESET);
}



void fill_accumulators(){

}



// Heater

int heat_catalyst(){

	bool acquired = false;

	HAL_GPIO_WritePin(heater_en_GPIO_Port, heater_en_Pin, GPIO_PIN_SET);

	// or

    //	HAL_Delay(18000000); // wait 3 minutes.

	while(!acquired){
		//  need to select correct TC before testing.
		temp = max31856_read_TC_temp(&max31856T4);
		max31856_read_fault(&max31856T4);
		if (max31856T4.sr.val) {
			return -1;
		}

		if(temp > THRESHOLD_TEMP){ // need to set correct threshold temperature value based on the readings we are getting.
			acquired = true;
		}




	}

	HAL_GPIO_WritePin(heater_en_GPIO_Port, heater_en_Pin, GPIO_PIN_RESET);


	return 1;




}






