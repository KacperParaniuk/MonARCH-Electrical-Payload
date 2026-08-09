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
#include "cmsis_os.h"
#include "i2c.h"
#include "spi.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */


/* Native FreeRTOS — needed for ISR-safe functions */
#include "FreeRTOS.h"
#include "semphr.h"


extern osSemaphoreId_t s_rx_semaphoreHandle;


// ----------------- Sensor Includes -----------------------

#include "ad7124_console_app.h"
#include "ad7124.h"
#include "max31856.h"
#include "fdc2214.h"



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

int32_t setupResult;
uint32_t device_id;
uint8_t rx_cmd[1]; // single byte for all UART commands.
uint8_t tx_cmd[1];
char uart_buffer[64]; // used for sending data across uart3
float temperature;
float value;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
void MX_FREERTOS_Init(void);
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

 // create a setup function for all sensors and turn red_led if fails to setup / read from device id's of all sensors

    // RED = MAX31856 Fail
    // AMBER = ADC2214
    // RED + AMBER = FDC2214
    // Green = Everything Setup Correctly

// ------------------ SET-UP SENSORS -------------------- \\

// ADC7124 || PT Readings Init

  /* Initialize the AD7124 application before the FreeRTOS takes over  */

    // this setup will be for POWER
    // added param for cs -> CS = 0 = AD7124 VOLTAGE      |
    				//       CS = 1 = AD7124 PRESSURE   | for measuring

// Setup pressure ADC

    if ((setupResult = ad7124_app_initialize(AD7124_CONFIG_A,PRESSURE)) < 0) {
  		// Handle error setting up AD7124 here
  	  printf("Failed to init ad7124 pressure \n");
  	  HAL_GPIO_WritePin(LED_PIN_RED_GPIO_Port, LED_PIN_RED_Pin, GPIO_PIN_SET);
    }
    printf("Setup Pressure Result: %ld", setupResult);

// Setup Voltage ADC

    if ((setupResult = ad7124_app_initialize(AD7124_CONFIG_A,VOLTAGE)) < 0) {
  		// Handle error setting up AD7124 here
  	  printf("Failed to init ad7124 voltage \n");
  	  HAL_GPIO_WritePin(LED_PIN_RED_GPIO_Port, LED_PIN_RED_Pin, GPIO_PIN_SET);

    }

    printf("Setup voltage Result: %ld", setupResult);


// MAX31856 Setup || Temperature Reading K-Type Thermocouples Readings INIT

// T1


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
   	max31856_set_conversion_mode(&max31856T1, CR0_CONV_CONTINUOUS);


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


   	setupResult = FDC2214_Begin();
   	if(setupResult != 0){

   		// need to figure out what to do if an iniit fails in flight
   		Serial_Printf("Failed to communicate with FDCC2214");
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






  /* USER CODE END 2 */

  /* Init scheduler */
  osKernelInitialize();  /* Call init function for freertos objects (in cmsis_os2.c) */
  MX_FREERTOS_Init();

  /* Start scheduler */
  osKernelStart();

  /* We should never get here as control is now taken by the scheduler */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {

//
//	  HAL_GPIO_TogglePin(LED_PIN_RED_GPIO_Port, LED_PIN_RED_Pin);
//
//
//	  HAL_Delay(200);





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





#ifdef ARDUNIO


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



// 	 HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_3);
//
// 	 // see duty cycle and if does not look good uncomment the bottom code. This is for testing.
//
//// 	  // change duty cycle to 50 %
//// 	 int duty = 50
//// 	 __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, duty);  // TIM1->CCR1 = duty;
//// 	  HAL_Delay(500);  // Wait 500ms before changing duty cycle
///






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
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 1;
  RCC_OscInitStruct.PLL.PLLN = 10;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = RCC_PLLQ_DIV2;
  RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE BEGIN 4 */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {

    if (huart->Instance != USART3) return;  // protect against any other UART commands

	HAL_UART_Receive_IT(&huart3, rx_cmd, 1);
	printf("Value %d \r\n", rx_cmd[0]); // print value to stm console


	if(rx_cmd[0]>0 && rx_cmd[0]<255){
		// release semaphore so that the UART task can decipher.
		BaseType_t xWoken = pdFALSE; // used to directly go to the UART_RX task rather than go back to what was previously going on in the program before the ISR and then seeing the semaphore
		xSemaphoreGiveFromISR(s_rx_semaphoreHandle, &xWoken); // FreeRTOS will set xWoken if there's a task waiting on this semaphore
		portYIELD_FROM_ISR(xWoken);
	}


}
/* USER CODE END 4 */

/**
  * @brief  Period elapsed callback in non blocking mode
  * @note   This function is called  when TIM6 interrupt took place, inside
  * HAL_TIM_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
  * a global variable "uwTick" used as application time base.
  * @param  htim : TIM handle
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  /* USER CODE BEGIN Callback 0 */

  /* USER CODE END Callback 0 */
  if (htim->Instance == TIM6)
  {
    HAL_IncTick();
  }
  /* USER CODE BEGIN Callback 1 */

  /* USER CODE END Callback 1 */
}

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
