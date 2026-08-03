/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "i2c.h"
#include "spi.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

#include "gpio_driver.h"
#include "uart_handler.h"
#include "uart_protocol.h"




// ---------------- DEFINES ---------------------



//#define AD7124
//#define AD7124_SINGLE_MODE
//#define AD7124_CONTINOUS_MODE
//#define FDC2214_S
//#define MAX31856
//#define MAX31856_T1
//#define MAX31856_T2
//#define MAX31856_T3
//#define MAX31856_T4
//#define MAX31856_T5
//#define B2B_ARDUINO
//#define VALVE_TEST
//#define I2C_SCANNER
//#define HEATER
//#define PWM_VALVE_6




// ----------------- HARDWARE TESTS -----------------------

#ifdef AD7124

// Sensor Includes

#include "ad7124_console_app.h"
#include "ad7124.h"


#endif


#ifdef MAX31856

#include "max31856.h"

#endif


#ifdef FDC2214_S

#include "fdc2214.h"

#endif


// Serial Interface For Debugging || Serial wire JTAG debug port (SWJ-DP)
#include <stdio.h>



/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

uint8_t rx_cmd[1]; // single byte for all UART commands.
uint8_t tx_cmd[1];
char uart_buffer[64];

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

// struct max31856_t *max31856;


/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */




  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */




  // Device ID's

//   uint32_t device_id;

#ifdef B2B_ARDUINO
   // UART Inits
//   uint8_t rx_cmd[1]; // single byte for all UART commands.
//   uint8_t TX_Buffer[] = "Hello, World!\r\n";
   // "\r" move cursor to start of line
   // "\n" new line

#endif




  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

//  GPIO_Driver_Init(&LED_BLINK);


  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_I2C4_Init();
  MX_SPI1_Init();
  MX_SPI2_Init();
  MX_UART4_Init();
  MX_USART3_UART_Init();
  MX_TIM8_Init();
  MX_TIM3_Init();
  /* USER CODE BEGIN 2 */

//  HAL_GPIO_WritePin(LED_PIN_RED_GPIO_Port, LED_PIN_RED_Pin, GPIO_PIN_SET);


  // blocking no work
//  HAL_UART_Receive(&huart3, rx_cmd, 1,0xFFFF);
//  HAL_UART_Transmit(&huart3, rx_cmd, 1, 0xFFFF);

  // start receiving UART commands.

  HAL_UART_Receive_IT(&huart3, rx_cmd, 1);


// DEACTIVATE ALL SPI2 ICs

// (NOT CS) So if a pin is pulled low the chip will be selected.


  // SPI 2 BUS
  HAL_GPIO_WritePin(T1_EN_GPIO_Port, T1_EN_Pin, GPIO_PIN_SET);
  HAL_GPIO_WritePin(T2_EN_GPIO_Port, T2_EN_Pin, GPIO_PIN_SET);
  HAL_GPIO_WritePin(T3_EN_GPIO_Port, T3_EN_Pin, GPIO_PIN_SET);
  HAL_GPIO_WritePin(T4_EN_GPIO_Port, T4_EN_Pin, GPIO_PIN_SET);
  HAL_GPIO_WritePin(T5_EN_GPIO_Port, T5_EN_Pin, GPIO_PIN_SET);
  HAL_GPIO_WritePin(PT_EN_GPIO_Port, PT_EN_Pin, GPIO_PIN_SET);

  // SPI 1 BUS

  HAL_GPIO_WritePin(ADC_EN_GPIO_Port, ADC_EN_Pin, GPIO_PIN_SET);


// External driver structures and buffers


// ADC7124 || PT Readings Init


#ifdef AD7124



/* Initialize the AD7124 application before the main loop */

  // this setup will be for POWER
  // added param for cs -> CS = 0 = AD7124 POWER      |
  				//       CS = 1 = AD7124 PRESSURE   | for measuring

  int32_t setupResult;
  uint32_t device_id;


  if ((setupResult = ad7124_app_initialize(AD7124_CONFIG_A,1)) < 0) {
		// Handle error setting up AD7124 here
	  printf("Failed to init ad7124 pressure \n");
//	  HAL_GPIO_WritePin(LED_PIN_RED_GPIO_Port, LED_PIN_RED_Pin, GPIO_PIN_SET);

  }

  printf("Setup Result: %ld", setupResult);
//  HAL_GPIO_WritePin(LED_PIN_RED_GPIO_Port, LED_PIN_RED_Pin, GPIO_PIN_SET);




//  float voltage1;
//  float voltage2;
//  uint32_t val;


#endif


#ifdef MAX31856

float temperature;

#endif


// MAX31856 Setup || Temperature Reading K-Type Thermocouples Readings INIT

// T1

#ifdef MAX31856_T1
   	max31856_gpio_t max31856T1PIN = {
   	    .gpio_port = T1_EN_GPIO_Port,
   	    .gpio_pin  = T1_EN_Pin
   	};

   	max31856_t max31856T1 = {
   			.spi_handle = &hspi2,
 			.cs_pin = max31856T1PIN

   	};


   	max31856_init(&max31856T1);

   	max31856_set_noise_filter(&max31856T1, CR0_FILTER_OUT_60Hz); // Noise filter is for filtering out EMI in very long wires
   	max31856_set_cold_junction_enable(&max31856T1, CR0_CJ_ENABLED); // External Sensor which measures the cold junction and references
   	max31856_set_thermocouple_type(&max31856T1, CR1_TC_TYPE_K); // K - type thermocouple
   	max31856_set_average_samples(&max31856T1, CR1_AVG_TC_SAMPLES_2);
   	max31856_set_open_circuit_fault_detection(&max31856T1, CR0_OC_DETECT_ENABLED_TC_LESS_2ms);
   	max31856_set_conversion_mode(&max31856T1, CR0_CJ_DISABLED); // need to disable for single we don't have access to the DRDY pins thus we have to estimate polling time.

#endif

//   	// T2

#ifdef MAX31856_T2

   	max31856_gpio_t max31856T2PIN = {
   			.gpio_port = T2_EN_GPIO_Port,
 			.gpio_pin  = T2_EN_Pin
   	  	};

   	max31856_t max31856T2 = {
   			.spi_handle = &hspi2,
   			.cs_pin = max31856T2PIN
   	};

 	max31856_init(&max31856T2);

   	max31856_set_noise_filter(&max31856T2, CR0_FILTER_OUT_60Hz);
   	max31856_set_cold_junction_enable(&max31856T2, CR0_CJ_ENABLED); // External Sensor which measures the cold junction and references
   	max31856_set_thermocouple_type(&max31856T2, CR1_TC_TYPE_K); // K - type thermocouple
   	max31856_set_average_samples(&max31856T2, CR1_AVG_TC_SAMPLES_2);
   	max31856_set_open_circuit_fault_detection(&max31856T2, CR0_OC_DETECT_ENABLED_TC_LESS_2ms);
   	max31856_set_conversion_mode(&max31856T2, CR0_CONV_CONTINUOUS); // continous mode for testing


   	// T3

#endif

#ifdef MAX31856_T3

   	max31856_gpio_t max31856T3PIN = {
   		.gpio_port = T3_EN_GPIO_Port,
 		.gpio_pin  = T3_EN_Pin
   	};

   	max31856_t max31856T3 = {
   			.spi_handle = &hspi2,
   			.cs_pin = max31856T3PIN
   	};

 	max31856_init(&max31856T3);

   	max31856_set_noise_filter(&max31856T3, CR0_FILTER_OUT_60Hz);
   	max31856_set_cold_junction_enable(&max31856T3, CR0_CJ_ENABLED);
   	max31856_set_thermocouple_type(&max31856T3, CR1_TC_TYPE_K);
   	max31856_set_average_samples(&max31856T3, CR1_AVG_TC_SAMPLES_2);
   	max31856_set_open_circuit_fault_detection(&max31856T3, CR0_OC_DETECT_ENABLED_TC_LESS_2ms);
   	max31856_set_conversion_mode(&max31856T3, CR0_CONV_CONTINUOUS);

#endif

#ifdef MAX31856_T4


   	// T4

   	max31856_gpio_t max31856T4PIN = {
   		.gpio_port = T4_EN_GPIO_Port,
 		.gpio_pin  = T4_EN_Pin
   	};

   	max31856_t max31856T4 = {
   			.spi_handle = &hspi2,
   			.cs_pin = max31856T4PIN
   	};

 	max31856_init(&max31856T4);

   	max31856_set_noise_filter(&max31856T4, CR0_FILTER_OUT_60Hz);
   	max31856_set_cold_junction_enable(&max31856T4, CR0_CJ_ENABLED);
   	max31856_set_thermocouple_type(&max31856T4, CR1_TC_TYPE_K);
   	max31856_set_average_samples(&max31856T4, CR1_AVG_TC_SAMPLES_2);
   	max31856_set_open_circuit_fault_detection(&max31856T4, CR0_OC_DETECT_ENABLED_TC_LESS_2ms);
   	max31856_set_conversion_mode(&max31856T4, CR0_CONV_CONTINUOUS);


#endif

//   	// T5

#ifdef MAX31856_T5

   	max31856_gpio_t max31856T5PIN = {
   		.gpio_port = T5_EN_GPIO_Port,
 		.gpio_pin = T5_EN_Pin
   	};

   	max31856_t max31856T5 = {
   			.spi_handle = &hspi2,
   			.cs_pin = max31856T5PIN
   	};

 	max31856_init(&max31856T5);

   	max31856_set_noise_filter(&max31856T5, CR0_FILTER_OUT_60Hz);
   	max31856_set_cold_junction_enable(&max31856T5, CR0_CJ_ENABLED);
   	max31856_set_thermocouple_type(&max31856T5, CR1_TC_TYPE_K);
   	max31856_set_average_samples(&max31856T5, CR1_AVG_TC_SAMPLES_2);
   	max31856_set_open_circuit_fault_detection(&max31856T5, CR0_OC_DETECT_ENABLED_TC_LESS_2ms);
   	max31856_set_conversion_mode(&max31856T5, CR0_CONV_CONTINUOUS);



#endif

//   	// FDC2214 SETUP

//   	// Reset Registers in Device.

#ifdef FDC2214_S
   	uint8_t ret;




   	ret = FDC2214_Begin();
   	if(ret != 0){
   		printf("Failed to communicate with FDCC2214");
   		reset_fdc2214();
   		printf("Try Again");
   		FDC2214_Begin();
   	}
   	else{

   	   	// set default FDC2214 configurations
   	   	FDC2214_configure_defaults();

   	   	// toggle channel

   	   	FDC2214_set_active_channel(FDC2214_CH0);
   	   	FDC2214_setAutoscan(0); // false
   	   	FDC2214_wakeup();

   	}


#endif




  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {

//
//	  HAL_GPIO_TogglePin(LED_PIN_RED_GPIO_Port, LED_PIN_RED_Pin);
//
//
//	  HAL_Delay(200);

#ifdef B2B

//	  HAL_UART_Transmit(&huart3,TX_Buffer,sizeof(TX_Buffer),1000); // "Hello World!" // UART Direct Test


#endif


#ifdef VALVE_TEST


	  printf("Actuation of Valve 2 Starting... in 15 seconds \n");


	  HAL_Delay(5000);


	  HAL_Delay(5000);



	  printf("Actuation of Valve 2 Starting... in 10 seconds \n");


	  HAL_Delay(5000);

	  printf("Actuation of Valve 2 Starting... in 5 seconds \n");

	  HAL_Delay(5000);


	  HAL_GPIO_WritePin(valve2_GPIO_Port, valve2_Pin, GPIO_PIN_SET);

	  printf("Valve 2 Actuated \n");

	  HAL_Delay(2000);

	  HAL_GPIO_WritePin(valve2_GPIO_Port, valve2_Pin, GPIO_PIN_RESET);

	  printf("Valve 2 Closed \n");



#endif


#ifdef HEATER


	  printf("Heater starting in 5 seconds");
	  HAL_Delay(5000);

	  HAL_GPIO_WritePin(heater_en_GPIO_Port, heater_en_Pin, GPIO_PIN_SET);


	  printf("Heating for 10 seconds");
	  HAL_Delay(10000);


	  HAL_GPIO_WritePin(heater_en_GPIO_Port, heater_en_Pin, GPIO_PIN_RESET);


#endif


#ifdef I2C_SCANNER

//	  0x3054 Device ID (FDC2112, FDC2114 only)
//	  0x3055 Device ID (FDC2212, FDC2214 only)

	  // 0x7F


	  // take a look at obsidian for tutorial




#endif

#ifdef AD7124

	  // read device id.

	  device_id = ad7124_read_device_id();

	  printf("AD7124 Device ID: %ld ", device_id);
	  if(device_id == 20){ // device id for dataversion E || https://ez.analog.com/data_converters/precision_adcs/f/q-a/574494/ad7124-8-device-id-question

		  printf("|| SUCCESS \n");
		  HAL_GPIO_WritePin(LED_PIN_GREEN_GPIO_Port, LED_PIN_GREEN_Pin, GPIO_PIN_SET);
		  read_status_register();

#ifdef AD7124_SINGLE_MODE
		  /* Read all enabled channels on ADC in single conversion mode */
		  menu_single_conversion();

#endif


#ifdef AD7124_CONTINOUS_MODE

		 /* Continously Read all enabled channels on ADC for 10 iterations (change to desire / add functionality for commanding) */

		 do_continuous_conversion(DISPLAY_DATA_TABULAR);

#endif

	  }
	  else{
		  // read error register;
		  read_error_register();
		  // check status of chip
		  read_status_register();

//		  HAL_GPIO_WritePin(LED_PIN_RED_GPIO_Port, LED_PIN_RED_Pin, GPIO_PIN_SET);

	  }

#endif


#ifdef B2B_ARDUINO
//	  Serial_Print("Transmitting"); // Serial_Print custom function test.
//
//	   Serial_Printf("Temperature Test %d C\r\n", 100); // Serial_Print custom formatted print function


//	   TEST READS...

//	   Serial_Print("Test IC Reads"); // Serial_Print custom function test.

//	   For Repo Branch...


//	   polling method -> Blocks CPU until UART receive is done.
 	  // uart receive block will continously try to fetch.
 		  // Polling for Seperate Pressure Sensors.

//	  HAL_GPIO_TogglePin(LED_PIN_RED_GPIO_Port, LED_PIN_RED_Pin);
//	  HAL_Delay(500);
//
//
//	if(*rx_cmd == CMD_TOGGLE_LED_RED){
//		  HAL_GPIO_TogglePin(LED_PIN_RED_GPIO_Port, LED_PIN_RED_Pin);

//		  HAL_Delay(2000);

//	}





// testing
//	char uart_buffer[64];
//	uint32_t sensor_value = 42; // Replace with actual sensor reading
//
//	int len = snprintf(uart_buffer, sizeof(uart_buffer), "Sensor: %lu\r\n", sensor_value);
//
//	HAL_UART_Transmit(&huart3, (uint8_t *)uart_buffer, len, 100);
//	HAL_Delay(1000);


 	switch(rx_cmd[0]){


 		  // Read AD7124

// // Read PT Valves
 		case CMD_OPEN_SOL1:
 			HAL_GPIO_WritePin(valve1_GPIO_Port, valve1_Pin, GPIO_PIN_SET);

 		case CMD_OPEN_SOL2:
 			HAL_GPIO_WritePin(valve2_GPIO_Port, valve2_Pin, GPIO_PIN_SET);

 		case CMD_OPEN_SOL3:
 		 	HAL_GPIO_WritePin(valve3_GPIO_Port, valve3_Pin, GPIO_PIN_SET);

 		case CMD_OPEN_SOL4: // IEP VALVE (PWM)



 		 	HAL_GPIO_WritePin(TIM8_CH1_VALVE4_GPIO_Port, TIM8_CH1_VALVE4_Pin, GPIO_PIN_SET);

 		case CMD_OPEN_SOL5:
 		 	HAL_GPIO_WritePin(valve5_GPIO_Port, valve5_Pin, GPIO_PIN_SET);





 		case CMD_OPEN_SOL6: // IEP VALVE (PWM)
 		 	HAL_GPIO_WritePin(TIM__CH1_VALVE6_GPIO_Port, TIM__CH1_VALVE6_Pin, GPIO_PIN_SET);





 		case CMD_OPEN_SOL7:
 		    HAL_GPIO_WritePin(valve7_GPIO_Port, valve7_Pin, GPIO_PIN_SET);

 		case CMD_OPEN_SOL8:
 		 	HAL_GPIO_WritePin(valve8_GPIO_Port, valve8_Pin, GPIO_PIN_SET);

 		case CMD_OPEN_SOL9:
 		    HAL_GPIO_WritePin(valve9_GPIO_Port, valve9_Pin, GPIO_PIN_SET);

 		case CMD_OPEN_SOL10:
 		    HAL_GPIO_WritePin(valve10_GPIO_Port, valve10_Pin, GPIO_PIN_SET);

 		case CMD_OPEN_SOL11:
 		    HAL_GPIO_WritePin(valve11_GPIO_Port, valve11_Pin, GPIO_PIN_SET);

 		case CMD_OPEN_SOL12:
 		 	HAL_GPIO_WritePin(valve12_GPIO_Port, valve12_Pin, GPIO_PIN_SET);

 		case CMD_OPEN_SOL13:
 		    HAL_GPIO_WritePin(valve13_GPIO_Port, valve13_Pin, GPIO_PIN_SET);

 		case CMD_OPEN_SOL14:
 		    HAL_GPIO_WritePin(valve14_GPIO_Port, valve14_Pin, GPIO_PIN_SET);

 		case CMD_OPEN_SOL15:
 		 	HAL_GPIO_WritePin(valve15_GPIO_Port, valve15_Pin, GPIO_PIN_SET);

 		case CMD_OPEN_SOL16:
 		    HAL_GPIO_WritePin(valve16_GPIO_Port, valve16_Pin, GPIO_PIN_SET);

 		case CMD_OPEN_SOL17:
 		 	HAL_GPIO_WritePin(valve17_GPIO_Port, valve17_Pin, GPIO_PIN_SET);

 	    case CMD_TOGGLE_LED_RED:
 		    HAL_GPIO_TogglePin(LED_PIN_RED_GPIO_Port, LED_PIN_RED_Pin);
 			HAL_Delay(2000);



 	    case CMD_READ_TC1:
 		   temperature = max31856_read_CJ_temp(&max31856T1);

 		   // we may need to add if there's ever an error...


 		   int len = snprintf(uart_buffer, sizeof(uart_buffer), "Cold Junction Temperature Reading TC1: %f\r\n", temperature);
 	 	   HAL_UART_Transmit(&huart3, (uint8_t *)uart_buffer, len, 100);





 		rx_cmd[0]=0;

 		break;
 	}



#endif
#ifdef ARDUNIO
 			case CMD_READ_PT1:
 				value = display_channel_sample(CH_READ_PT0);
 				// will need to convert the voltage value to a current / temp reading function eventually in ad7124.h
 				Serial_Printf("Pressure Reading PT 1: %d \r\n", value);
 			case CMD_READ_PT2:
 				value = display_channel_sample(CH_READ_PT1);
 				Serial_Printf("Pressure Reading PT 2: %d \r\n", value);
 			case CMD_READ_PT3:
 				value = display_channel_sample(CH_READ_PT2);
 				Serial_Printf("Pressure Reading PT 3: %d \r\n", value);
 			case CMD_READ_PT4:
 				value = display_channel_sample(CH_READ_PT3);
 				Serial_Printf("Pressure Reading PT 4: %d \r\n", value);
 			case CMD_READ_PT5:
 				value = display_channel_sample(CH_READ_PT4);
 				Serial_Printf("Pressure Reading PT 5: %d \r\n", value);
 			case CMD_READ_PT6:
 				value = display_channel_sample(CH_READ_PT5);
 				Serial_Printf("Pressure Reading PT 6: %d \r\n", value);
 			case CMD_READ_PT7:
 				value = display_channel_sample(CH_READ_PT6);
 				Serial_Printf("Pressure Reading PT 7: %d \r\n", value);
 			case CMD_READ_PT8:
 				value = display_channel_sample(CH_READ_PT7);
 				Serial_Printf("Pressure Reading PT 8: %d \r\n", value);



// // Read TC Valves
 			case CMD_READ_TC1:

 				max31856_trigger_one_shot(&max31856T1);
 				HAL_Delay(200); // Wait until single is ready
 				temp = max31856_read_TC_temp(&max31856T1); // compensates already for cold junction reading
 				max31856_read_fault(&max31856T1);
 				  	if (max31856T1.sr.val) {
 				  	  Serial_Print("TC1 Read Fail");
 				  	}
 				Serial_Printf("Temperature Reading TC1: %f \r\n", temp);


 			case CMD_READ_TC2:
 				temp = max31856_read_TC_temp(&max31856T2);
 				max31856_read_fault(&max31856T2);
 				if (max31856T2.sr.val) {
 					Serial_Print("TC2 Read Fail");
 				}
 				Serial_Printf("Temperature Reading TC2: %f \r\n", temp);

 			case CMD_READ_TC3:
 				temp = max31856_read_TC_temp(&max31856T3);
 				max31856_read_fault(&max31856T3);
 				if (max31856T3.sr.val) {
 					Serial_Print("TC3 Read Fail");
 			    }
 				Serial_Printf("Temperature Reading TC3: %f \r\n", temp);


 			case CMD_READ_TC4:
 				temp = max31856_read_TC_temp(&max31856T4);
 				max31856_read_fault(&max31856T4);
 				if (max31856T4.sr.val) {
 					Serial_Print("TC4 Read Fail");
 			    }
 				Serial_Printf("Temperature Reading TC4: %f \r\n", temp);


 			case CMD_READ_TC5:
 				temp = max31856_read_TC_temp(&max31856T5);
 				max31856_read_fault(&max31856T5);
 				if (max31856T5.sr.val) {
 					Serial_Print("TC5 Read Fail");
 			    }
 				Serial_Printf("Temperature Reading TC5: %f \r\n", temp);


// // Read PC104 Voltages

// 			case CMD_READ_12VA_VB:
// 				value = ad7124_read_channel_voltage(ad7124_pc104, CH_READ_12VA_VB);
// 				Serial_Printf("PC104 Voltage Reading 12VA_VB: %d \r\n", value);
// 			case CMD_READ_12VA_VA:
// 				value = ad7124_read_channel_voltage(ad7124_pc104, CH_READ_12VA_VA);
// 				Serial_Printf("PC104 Voltage Reading 12VA_VA: %d \r\n", value);
// 			case CMD_READ_3V3_VB:
// 				value = ad7124_read_channel_voltage(ad7124_pc104, CH_READ_3V3_VB);
// 				Serial_Printf("PC104 Voltage Reading 3V3_VB: %d \r\n", value);
// 			case CMD_READ_3V3_VA:
// 				value = ad7124_read_channel_voltage(ad7124_pc104, CH_READ_3V3_VA);
// 				Serial_Printf("PC104 Voltage Reading 3V3_VA: %d \r\n", value);
//
// 			case CMD_READ_VBAT_VA:
// 				value = ad7124_read_channel_voltage(ad7124_pc104, CH_READ_VBAT_VA);
// 				Serial_Printf("PC104 Voltage Reading VBAT_VA: %d \r\n", value);
// 			case CMD_READ_VBAT_VB:
// 				value = ad7124_read_channel_voltage(ad7124_pc104, CH_READ_VBAT_VB);
// 				Serial_Printf("PC104 Voltage Reading VBAT_VB: %d \r\n", value);
//
// 			case CMD_READ_12VB_VA:
// 				value = ad7124_read_channel_voltage(ad7124_pc104, CH_READ_12VB_VA);
// 				Serial_Printf("PC104 Voltage Reading 12VB_VA: %d \r\n", value);
//
// 			case CMD_READ_12VB_VB:
// 				value = ad7124_read_channel_voltage(ad7124_pc104, CH_READ_12VB_VB);
// 				Serial_Printf("PC104 Voltage Reading 12VB_VB: %d \r\n", value);
//
//// // Read PC104 Currents
// 			case CMD_READ_12VA_VB_CURRENT:
// 				value = ad7124_read_channel_current_pc104(ad7124_pc104, CH_READ_12VA_VB);
// 				Serial_Printf("PC104 Current Reading 12VA_VB: %d \r\n", value);
//
// 			case CMD_READ_12VA_VA_CURRENT:
// 				value = ad7124_read_channel_current_pc104(ad7124_pc104, CH_READ_12VA_VA);
// 				Serial_Printf("PC104 Current Reading 12VA_VA: %d \r\n", value);
//
// 			case CMD_READ_3V3_VB_CURRENT:
// 				value = ad7124_read_channel_current_pc104(ad7124_pc104, CH_READ_3V3_VB);
// 				Serial_Printf("PC104 Current Reading 3V3_VB : %d \r\n", value);
//
// 			case CMD_READ_3V3_VA_CURRENT:
// 				value = ad7124_read_channel_current_pc104(ad7124_pc104, CH_READ_3V3_VA);
// 				Serial_Printf("PC104 Current Reading 3V3_VA : %d \r\n", value);
//
// 			case CMD_READ_VBAT_VA_CURRENT:
// 				value = ad7124_read_channel_current_pc104(ad7124_pc104, CH_READ_VBAT_VA);
// 				Serial_Printf("PC104 Current Reading VBAT_VA : %d \r\n", value);
//
// 			case CMD_READ_VBAT_VB_CURRENT:
// 				value = ad7124_read_channel_current_pc104(ad7124_pc104, CH_READ_VBAT_VB);
// 				Serial_Printf("PC104 Current Reading VBAT_VB : %d \r\n", value);
//
// 			case CMD_READ_12VB_VA_CURRENT:
// 				value = ad7124_read_channel_current_pc104(ad7124_pc104, CH_READ_12VB_VA);
// 				Serial_Printf("PC104 Current Reading 12VB_VA: %d \r\n",  value);
//
// 			case CMD_READ_12VB_VB_CURRENT:
// 				value = ad7124_read_channel_current_pc104(ad7124_pc104, CH_READ_12VB_VB);
// 				Serial_Printf("PC104 Current Reading 12VB_VB: %d \r\n", value);


// // Open Solenoids (ON/OFF)

 			case CMD_OPEN_SOL1:
 				HAL_GPIO_WritePin(valve1_GPIO_Port, valve1_Pin, GPIO_PIN_SET);

 			case CMD_OPEN_SOL2:
 				HAL_GPIO_WritePin(valve2_GPIO_Port, valve2_Pin, GPIO_PIN_SET);

 			case CMD_OPEN_SOL3:
 				HAL_GPIO_WritePin(valve3_GPIO_Port, valve3_Pin, GPIO_PIN_SET);

 			case CMD_OPEN_SOL4: // IEP VALVE (PWM)
 				HAL_GPIO_WritePin(TIM8_CH1_VALVE4_GPIO_Port, TIM8_CH1_VALVE4_Pin, GPIO_PIN_SET);

 			case CMD_OPEN_SOL5:
 				HAL_GPIO_WritePin(valve5_GPIO_Port, valve5_Pin, GPIO_PIN_SET);

 			case CMD_OPEN_SOL6: // IEP VALVE (PWM)
 				HAL_GPIO_WritePin(TIM__CH1_VALVE6_GPIO_Port, TIM__CH1_VALVE6_Pin, GPIO_PIN_SET);

 			case CMD_OPEN_SOL7:
 				HAL_GPIO_WritePin(valve7_GPIO_Port, valve7_Pin, GPIO_PIN_SET);

 			case CMD_OPEN_SOL8:
 				HAL_GPIO_WritePin(valve8_GPIO_Port, valve8_Pin, GPIO_PIN_SET);

 			case CMD_OPEN_SOL9:
 				HAL_GPIO_WritePin(valve9_GPIO_Port, valve9_Pin, GPIO_PIN_SET);

 			case CMD_OPEN_SOL10:
 				HAL_GPIO_WritePin(valve10_GPIO_Port, valve10_Pin, GPIO_PIN_SET);

 			case CMD_OPEN_SOL11:
 				HAL_GPIO_WritePin(valve11_GPIO_Port, valve11_Pin, GPIO_PIN_SET);

 			case CMD_OPEN_SOL12:
 				HAL_GPIO_WritePin(valve12_GPIO_Port, valve12_Pin, GPIO_PIN_SET);

 			case CMD_OPEN_SOL13:
 				HAL_GPIO_WritePin(valve13_GPIO_Port, valve13_Pin, GPIO_PIN_SET);

 			case CMD_OPEN_SOL14:
 				HAL_GPIO_WritePin(valve14_GPIO_Port, valve14_Pin, GPIO_PIN_SET);

 			case CMD_OPEN_SOL15:
 				HAL_GPIO_WritePin(valve15_GPIO_Port, valve15_Pin, GPIO_PIN_SET);

 			case CMD_OPEN_SOL16:
 				HAL_GPIO_WritePin(valve16_GPIO_Port, valve16_Pin, GPIO_PIN_SET);

 			case CMD_OPEN_SOL17:
 				HAL_GPIO_WritePin(valve17_GPIO_Port, valve17_Pin, GPIO_PIN_SET);

// // Close Valves

 			case CMD_CLOSE_SOL1:
 				HAL_GPIO_WritePin(valve1_GPIO_Port, valve1_Pin, GPIO_PIN_RESET);

 			case CMD_CLOSE_SOL2:
 				HAL_GPIO_WritePin(valve2_GPIO_Port, valve2_Pin, GPIO_PIN_RESET);

 			case CMD_CLOSE_SOL3:
 				HAL_GPIO_WritePin(valve3_GPIO_Port, valve3_Pin, GPIO_PIN_RESET);

 			case CMD_CLOSE_SOL4: // IEP VALVE 4
 				HAL_GPIO_WritePin(TIM8_CH1_VALVE4_GPIO_Port, TIM8_CH1_VALVE4_Pin, GPIO_PIN_RESET);

 			case CMD_CLOSE_SOL5:
 				HAL_GPIO_WritePin(valve5_GPIO_Port, valve5_Pin, GPIO_PIN_RESET);

 			case CMD_CLOSE_SOL6: // IEP VALVE 6
 				HAL_GPIO_WritePin(TIM__CH1_VALVE6_GPIO_Port, TIM__CH1_VALVE6_Pin, GPIO_PIN_RESET);

 			case CMD_CLOSE_SOL7:
 				HAL_GPIO_WritePin(valve7_GPIO_Port, valve7_Pin, GPIO_PIN_RESET);

 			case CMD_CLOSE_SOL8:
 				HAL_GPIO_WritePin(valve8_GPIO_Port, valve8_Pin, GPIO_PIN_RESET);

 			case CMD_CLOSE_SOL9:
 				HAL_GPIO_WritePin(valve9_GPIO_Port, valve9_Pin, GPIO_PIN_RESET);

 			case CMD_CLOSE_SOL10:
 				HAL_GPIO_WritePin(valve10_GPIO_Port, valve10_Pin, GPIO_PIN_RESET);

 			case CMD_CLOSE_SOL11:
 				HAL_GPIO_WritePin(valve11_GPIO_Port, valve11_Pin, GPIO_PIN_RESET);

 			case CMD_CLOSE_SOL12:
 				HAL_GPIO_WritePin(valve12_GPIO_Port, valve12_Pin, GPIO_PIN_RESET);

 			case CMD_CLOSE_SOL13:
 				HAL_GPIO_WritePin(valve13_GPIO_Port, valve13_Pin, GPIO_PIN_RESET);

 			case CMD_CLOSE_SOL14:
 				HAL_GPIO_WritePin(valve14_GPIO_Port, valve14_Pin, GPIO_PIN_RESET);

 			case CMD_CLOSE_SOL15:
 				HAL_GPIO_WritePin(valve15_GPIO_Port, valve15_Pin, GPIO_PIN_RESET);

 			case CMD_CLOSE_SOL16:
 				HAL_GPIO_WritePin(valve16_GPIO_Port, valve16_Pin, GPIO_PIN_RESET);

 			case CMD_CLOSE_SOL17:
 				HAL_GPIO_WritePin(valve17_GPIO_Port, valve17_Pin, GPIO_PIN_RESET);

// // READ FDC2214 Capacitance Measurements.

 			case READ_CAPACITANCE_A1:
 				capacitance = FDC2214_read_differential_capacitance(1);
 				Serial_Printf("Differential Capacitance Reading FDC2214 A1: %f \r\n", capacitance);
 			case READ_CAPACITANCE_A2:
 				capacitance = FDC2214_read_differential_capacitance(2);
 				Serial_Printf("Differential Capacitance Reading FDC2214 A2: %f \r\n", capacitance);
 			case READ_CATALYST_LEVEL_A1:
 				level = FDC2214_read_accumulator_height(1);
 				Serial_Printf("Catalyst Height Reading FDC2214 A1: %d \r\n", level);
 			case READ_CATALYST_LEVEL_A2:
 				level = FDC2214_read_accumulator_height(2);
 				Serial_Printf("Catalyst Height Reading FDC2214 A2: %d \r\n", level);

 		}
 	  }

#endif

#ifdef MAX31856_T1

//	   max31856_trigger_one_shot(&max31856T1);
//	   HAL_Delay(200); // Wait until single is ready
	   temperature = max31856_read_CJ_temp(&max31856T1);
	   max31856_read_fault(&max31856T1);
	   if (max31856T1.sr.val) {
	   		printf("TC Read Fail ");
	   		printf("ERROR TC1 #: %d ",max31856T1.sr.val);

	   }
	   printf("Cold Junction Temperature Reading TC1: %f \r\n", temperature);

	   temperature = max31856_read_TC_temp(&max31856T1); // compensates already for cold junction reading
	   if (max31856T1.sr.val) {
	   	   	printf("TC TEMP Read Fail ");
	   	   	printf("ERROR TC1 #: %d ",max31856T1.sr.val);
	   	   	print_errors(max31856T1.sr.val); // test functionality of error discerning

	   }
	   printf("Temperature Reading TC1: %f \r\n", temperature);

#endif

// 	  // TESTING DEBUG PURPOSES w/ ST-LINK
//

#ifdef FDC2214
 	  printf("TESTING DEBUG PURPOSES LOADING... \n");

 	  printf("Reading Device ID's... \n");

 	  if(isConnected()==0){
 		  printf("FDC NOMINAL \n");

 		 // READ DATA FROM CH0
 		 if(FDC2214_is_data_ready(FDC2214_CH0)){
 		 float f_hz = FDC2214_readFrequencyHz(FDC2214_CH0);
 		 float c_pf = FDC2214_readCapacitancePf(FDC2214_CH0, FDC2214_L_HENRY);

 		 printf("hertz %f", f_hz / 1.0e6f);
 		// 	        printf('\t');
 		 printf("Capacitance (pF): %f", c_pf);
 		 }
 	  }
 	  else{
 		  printf("FDC FAIL IS NOT CONNECTED \n");
 	  }




#endif


#ifdef PWM_VALVE_6


 	 HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_3);

 	 // see duty cycle and if does not look good uncomment the bottom code. This is for testing.

// 	  // change duty cycle to 50 %
// 	 int duty = 50
// 	 __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, duty);  // TIM1->CCR1 = duty;
// 	  HAL_Delay(500);  // Wait 500ms before changing duty cycle
//








#endif


//
//// 	  // MAX31856 Error Reading
//
//
//// 	  printf("Reading PC104 Voltages...");
//
// 	  value = ad7124_read_channel_voltage(ad7124_pc104, CH_READ_12VA_VB);
// 	  printf("PC104 Voltage Reading 12VA_VB: %d \r\n", (int)value);
// 	  value = ad7124_read_channel_voltage(ad7124_pc104, CH_READ_12VA_VA);
// 	  printf("PC104 Voltage Reading 12VA_VA: %d \r\n", (int)value);
// 	  value = ad7124_read_channel_voltage(ad7124_pc104, CH_READ_3V3_VB);
// 	  printf("PC104 Voltage Reading 3V3_VB: %d \r\n", (int)value);
// 	  value = ad7124_read_channel_voltage(ad7124_pc104, CH_READ_3V3_VA);
// 	  printf("PC104 Voltage Reading 3V3_VA: %d \r\n", (int)value);
// 	  value = ad7124_read_channel_voltage(ad7124_pc104, CH_READ_VBAT_VA);
// 	  printf("PC104 Voltage Reading VBAT_VA: %d \r\n", (int)value);
// 	  value = ad7124_read_channel_voltage(ad7124_pc104, CH_READ_VBAT_VB);
// 	  printf("PC104 Voltage Reading VBAT_VB: %d \r\n", (int)value);
// 	  value = ad7124_read_channel_voltage(ad7124_pc104, CH_READ_12VB_VA);
// 	  printf("PC104 Voltage Reading 12VB_VA: %d \r\n", (int)value);
// 	  value = ad7124_read_channel_voltage(ad7124_pc104, CH_READ_12VB_VB);
// 	  printf("PC104 Voltage Reading 12VB_VB: %d \r\n", (int)value);


// 	  printf("Reading PC104 Currents...");


// 	  value = ad7124_read_channel_current_pc104(ad7124_pc104, CH_READ_12VA_VB);
// 	  printf("PC104 Current Reading 12VA_VB: %d \r\n", (int)value);
// 	  value = ad7124_read_channel_current_pc104(ad7124_pc104, CH_READ_12VA_VA);
// 	  printf("PC104 Current Reading 12VA_VA: %d \r\n", (int)value);
// 	  value = ad7124_read_channel_current_pc104(ad7124_pc104, CH_READ_3V3_VB);
// 	  printf("PC104 Current Reading 3V3_VB : %d \r\n", (int)value);
// 	  value = ad7124_read_channel_current_pc104(ad7124_pc104, CH_READ_3V3_VA);
// 	  printf("PC104 Current Reading 3V3_VA : %d \r\n", (int)value);
// 	  value = ad7124_read_channel_current_pc104(ad7124_pc104, CH_READ_VBAT_VA);
// 	  printf("PC104 Current Reading VBAT_VA : %d \r\n", (int)value);
// 	  value = ad7124_read_channel_current_pc104(ad7124_pc104, CH_READ_VBAT_VB);
// 	  printf("PC104 Current Reading VBAT_VB : %d \r\n", (int)value);
// 	  value = ad7124_read_channel_current_pc104(ad7124_pc104, CH_READ_12VB_VA);
// 	  printf("PC104 Current Reading 12VB_VA: %d \r\n", (int)value);
// 	  value = ad7124_read_channel_current_pc104(ad7124_pc104, CH_READ_12VB_VB);
// 	  printf("PC104 Current Reading 12VB_VB: %d \r\n", (int)value);



// 	  printf("Reading Pressure Voltage Readings... \n");

// 	  value = ad7124_read_channel_voltage(ad7124, CH_READ_PT0);
// 	  printf("Pressure Reading PT 1: %d \r\n", (int)value);
// 	  value = ad7124_read_channel_voltage(ad7124, CH_READ_PT1);
// 	  printf("Pressure Reading PT 2: %d \r\n", (int)value);
// 	  value = ad7124_read_channel_voltage(ad7124, CH_READ_PT2);
// 	  printf("Pressure Reading PT 3: %d \r\n", (int)value);
// 	  value = ad7124_read_channel_voltage(ad7124, CH_READ_PT3);
// 	  printf("Pressure Reading PT 4: %d \r\n", (int)value);
// 	  value = ad7124_read_channel_voltage(ad7124, CH_READ_PT4);
// 	  printf("Pressure Reading PT 5: %d \r\n", (int)value);
// 	  value = ad7124_read_channel_voltage(ad7124, CH_READ_PT5);
// 	  printf("Pressure Reading PT 6: %d \r\n", (int)value);
// 	  value = ad7124_read_channel_voltage(ad7124, CH_READ_PT6);
// 	  printf("Pressure Reading PT 7: %d \r\n", (int)value);
// 	  value = ad7124_read_channel_voltage(ad7124, CH_READ_PT7);
// 	  printf("Pressure Reading PT 8: %d \r\n", (int)value);


// 	  printf("Reading Temperature Voltage Readings... \n");











    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  if (HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_MSI;
  RCC_OscInitStruct.MSIState = RCC_MSI_ON;
  RCC_OscInitStruct.MSICalibrationValue = 0;
  RCC_OscInitStruct.MSIClockRange = RCC_MSIRANGE_6;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_MSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE BEGIN 4 */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
	HAL_UART_Receive_IT(&huart3, rx_cmd, 1);
	printf("Value %d \r\n", rx_cmd[0]);

}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}
#ifdef USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
