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



// WAIT TO IMPLEMENT - Until we speak about HAL_DELAY and test out functions.

void pressurize_lines(){


}


void fill_accumulators(){

	// Sequence:

	open_solenoid(valve5_GPIO_Port, valve5_Pin);
	open_solenoid(TIM__CH1_VALVE6_GPIO_Port, TIM__CH1_VALVE6_Pin);
	HAL_Delay(1000); // 1 second delay
	open_solenoid(valve7_GPIO_Port, valve7_Pin);
	HAL_Delay(1000); // 1 second delay
	close_solenoid(valve7_GPIO_Port, valve7_Pin);
	open_solenoid(valve11_GPIO_Port, valve11_Pin);
	HAL_Delay(1000); // 1 second delay
	open_solenoid(valve13_GPIO_Port, valve13_Pin);
	HAL_Delay(1000); // 1 second delay
	open_solenoid(valve1_GPIO_Port, valve1_Pin);
	open_solenoid(valve2_GPIO_Port, valve2_Pin);
	close_solenoid(TIM__CH1_VALVE6_GPIO_Port, TIM__CH1_VALVE6_Pin);
	close_solenoid(valve13_GPIO_Port, valve13_Pin);
	close_solenoid(valve11_GPIO_Port, valve11_Pin);


	HAL_Delay(5000); // wait 5 seconds

	// close all valves still open
	close_solenoid(valve1_GPIO_Port, valve1_Pin);
	close_solenoid(valve2_GPIO_Port, valve2_Pin);
	close_solenoid(valve5_GPIO_Port, valve5_Pin);




}


void fill_espray(){


}

void toggle_nominal_espray_run(){


	// communicate through UART to PPU.


}

void run_chemical_thruster(){


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






