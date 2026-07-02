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



// ---------------- DEFINES --------------------- \\


//#define AD7124
//#define FDC2213
//#define MAX31856


#ifdef AD7124

// Sensor Includes
#include "ad7124.h"

#include "ad7124_config.h"


#endif

// OLD #include "ad7124_regs.h"
// OLD #include "ad7124_sensor.h"

#ifdef MAX31856

#include "max31856.h"

#endif


#ifdef FDC2214

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

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

// OLD struct ad7124_dev *ad7124;  // device handle (Defined Globally)
// OLD struct ad7124_dev *ad7124_pc104;  // device handle (Defined Globally)



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


//   // UART Inits
//   uint8_t RX_CMD= 0; // single byte for all UART commands.
//   uint8_t TX_Buffer[] = "Hello, World!\r\n";
//   // "\r" move cursor to start of line
//   // "\n" new line



//  GPIO_PinConfig_t LED_BLINK = {
//	  .port = LED_PIN_GPIO_Port,
//	  .pin = LED_PIN_Pin,
//	  .mode = GPIO_MODE_OUTPUT_PP,
//	  .pull = GPIO_NOPULL,
//	  .speed = GPIO_SPEED_FREQ_LOW
//  };



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
  MX_TIM1_Init();
  MX_TIM8_Init();
  /* USER CODE BEGIN 2 */

  HAL_GPIO_WritePin(LED_PIN_GPIO_Port, LED_PIN_Pin, GPIO_PIN_SET);

  //    DEACTIVATE ALL SPI2 ICs


//  HAL_GPIO_WritePin(T1_EN_GPIO_Port, T1_EN_Pin, GPIO_PIN_SET);
//  HAL_GPIO_WritePin(T2_EN_GPIO_Port, T2_EN_Pin, GPIO_PIN_SET);
//  HAL_GPIO_WritePin(T3_EN_GPIO_Port, T3_EN_Pin, GPIO_PIN_SET);
//  HAL_GPIO_WritePin(T4_EN_GPIO_Port, T4_EN_Pin, GPIO_PIN_SET);
//  HAL_GPIO_WritePin(T5_EN_GPIO_Port, T5_EN_Pin, GPIO_PIN_SET);
//
//  HAL_GPIO_WritePin(PT_EN_GPIO_Port, PT_EN_Pin, GPIO_PIN_SET);




//  HAL_GPIO_WritePin(valve3_GPIO_Port, valve3_Pin, GPIO_PIN_SET);


//

//  // External driver structures and buffers

#ifdef AD7124

  extern AD7124_ConfigTypeDef AD7124_Handler;
  extern uint32_t AD7124_ChannelSamples[AD7124_ENABLED_CHANNELS];
  extern AD7124_RegisterTypeDef configA;

////   Status array for tracking return values from driver functions
   AD7124_StatusTypeDef status[3U];
////
//////  // Flag for DOUT/RDY interrupt
//////  volatile uint8_t ad7124_rdy_flag = 0U;
//////
//////  // Variables for error status, voltage, and temperature calculation
  int32_t ad7124_error = 0U;
//  double voltage;
//  float temperature;
  float voltage1;
  float voltage2;
  uint32_t val;
//////
////
////  /* Configure AD7124 handler structure */
  AD7124_Handler.SPIx = &hspi2;        // SPI peripheral used
  AD7124_Handler.csPort = PT_EN_GPIO_Port;       // GPIO port for CS
  AD7124_Handler.csPin = PT_EN_Pin;  // GPIO pin for CS
  AD7124_Handler.IRQn = EXTI9_5_IRQn;  // External interrupt line connected to DOUT/RDY

  HAL_NVIC_DisableIRQ(AD7124_Handler.IRQn);  // Disable IRQ during initial config
  status[0U] = AD7124_Config(&AD7124_Handler, &configA);  // Initialize and configure the AD7124

//   let's try without interrupt
//  HAL_NVIC_EnableIRQ(AD7124_Handler.IRQn);   // Re-enable interrupt after initialization

//


#endif


  // ADC7124 || PT Readings Init
//
//   int32_t value;		/* Stores raw value read from the ADC */
////   float temp; /* stores value for any TC */
////   float capacitance;  /* stores value from FDC2214 capacitance reading */
////   uint8_t level; /* stores the level of a given accumulator from the FDC2214 */
//   int32_t ret = 0;	/* Return value */
//
//   float c1;

//

   // OLD

//   struct ad7124_init_param ad7124_init_param = {
// 	  .hspi = &hspi2,
//       .cs_port = PT_EN_GPIO_Port,            // ← pt en pointer
//       .cs_pin = PT_EN_Pin,       //
//       .regs = ad7124_regs,         // these are register values of the ad7124
//       .spi_rdy_poll_cnt = 25000,
//
// 	  .mode = AD7124_SINGLE, // continuous equals IC constantly converting || single equal we tell it when to convert / read otherwise the chip is powered down.
// 	  .active_device = ID_AD7124_8,
// 	  .ref_en = false, // 2.5 internal reference (not using) b/c reading might go over this.
// 	  .power_mode = AD7124_LOW_POWER, // << What are the differences?
//
// 	  .setups[0] = {
// 		  .bi_unipolar = false,  // unipolar (don't have differential pairs)
// 		  .burnout = AD7124_BURNOUT_OFF,
// 		  .ref_source = AVDD_AVSS, // reference source is important and what we are doing calculations in REFERENCE to... 3.3v
// 		  .ain_buff = true, // buffers analog input to present high impedance (strengthens signal integrity)
// 		  .ref_buff = false, // sets reference source for high impedance
// 		  .pga = AD7124_PGA_1, // amplification of input signal.
// 	  },
//
// 	  // channel map
//
// 	  .chan_map[0] = { .ain = {.ainp = AD7124_AIN0, .ainm = AD7124_AVDD_AVSS_M}, .setup_sel = 0, .channel_enable = false },
// 	  .chan_map[1] = { .ain = {.ainp = AD7124_AIN1, .ainm = AD7124_AVDD_AVSS_M}, .setup_sel = 0, .channel_enable = true },
// 	  .chan_map[2] = { .ain = {.ainp = AD7124_AIN2, .ainm = AD7124_AVDD_AVSS_M}, .setup_sel = 0, .channel_enable = true },
// 	  .chan_map[3] = { .ain = {.ainp = AD7124_AIN3, .ainm = AD7124_AVDD_AVSS_M}, .setup_sel = 0, .channel_enable =  true },
// 	  .chan_map[4] = { .ain = {.ainp = AD7124_AIN4, .ainm = AD7124_AVDD_AVSS_M}, .setup_sel = 0, .channel_enable = true },
// 	  .chan_map[5] = { .ain = {.ainp = AD7124_AIN5, .ainm = AD7124_AVDD_AVSS_M}, .setup_sel = 0, .channel_enable = true },
// 	  .chan_map[6] = { .ain = {.ainp = AD7124_AIN6, .ainm = AD7124_AVDD_AVSS_M}, .setup_sel = 0, .channel_enable = false },
// 	  .chan_map[7] = { .ain = {.ainp = AD7124_AIN7, .ainm = AD7124_AVDD_AVSS_M}, .setup_sel = 0, .channel_enable = false },
// 	  .chan_map[8] = { .ain = {.ainp = AD7124_AIN8, .ainm = AD7124_AVDD_AVSS_M}, .setup_sel = 0, .channel_enable = false },
// 	  .chan_map[9] = { .ain = {.ainp = AD7124_AIN9, .ainm = AD7124_AVDD_AVSS_M}, .setup_sel = 0, .channel_enable = false },
// 	  .chan_map[10] = { .ain = {.ainp = AD7124_AIN10, .ainm = AD7124_AVDD_AVSS_M}, .setup_sel = 0, .channel_enable = false },
// 	  .chan_map[11] = { .ain = {.ainp = AD7124_AIN11, .ainm = AD7124_AVDD_AVSS_M}, .setup_sel = 0, .channel_enable = true },
// 	  .chan_map[12] = { .ain = {.ainp = AD7124_AIN12, .ainm = AD7124_AVDD_AVSS_M}, .setup_sel = 0, .channel_enable = true },
// 	  .chan_map[13] = { .ain = {.ainp = AD7124_AIN13, .ainm = AD7124_AVDD_AVSS_M}, .setup_sel = 0, .channel_enable = true },
//
//   };
//
//   ret = ad7124_setup(&ad7124, &ad7124_init_param);
//   if (ret != 0){
//	   printf("Error: ADC Setup");
//   }
//




//     // ADC7124 || Voltage Readings Init PC104 Stack

   // OLD

//    struct ad7124_init_param ad7124_init_param_pc104 = {
//   	 .hspi = &hspi1, // PC104 Stack AD7124 is on this SPI line.
//        .cs_port = ADC_EN_GPIO_Port,            // ← pt en pointer
//        .cs_pin = ADC_EN_Pin,       //
//        .regs = ad7124_regs,         // these are register values of the ad7124
//        .spi_rdy_poll_cnt = 25000,
//
//   	 .mode = AD7124_SINGLE, // continuous equals IC constantly converting || single equal we tell it when to convert / read otherwise the chip is powered down.
//   	 .active_device = ID_AD7124_8,
//   	 .ref_en = false, // 2.5 internal reference (not using) b/c reading might go over this.
//   	 .power_mode = AD7124_LOW_POWER, // << What are the differences?
//
//   	 .setups[0] = {
//   		  .bi_unipolar = false,  // unipolar (don't have differential pairs) NEED TO LOOK INTO THIS FOR THIS VOLTAGE READING
//   		  .burnout = AD7124_BURNOUT_OFF,
//   		  .ref_source = AVDD_AVSS, // reference source is important and what we are doing calculations in REFERENCE to... 3.3v
//   		  .ain_buff = true, // buffers analog input to present high impedance (strengthens signal integrity)
//   		  .ref_buff = false, // sets reference source for high impedance
//   		  .pga = AD7124_PGA_1, // amplification of input signal.
//   	 },
//
//
//   	  // channel map SET UP THESE CHANEELS.
//
//   	 .chan_map[0] = { .ain = {.ainp = AD7124_AIN0, .ainm = AD7124_AVDD_AVSS_M}, .setup_sel = 0, .channel_enable = true },
//   	 .chan_map[1] = { .ain = {.ainp = AD7124_AIN1, .ainm = AD7124_AVDD_AVSS_M}, .setup_sel = 0, .channel_enable = true },
//   	 .chan_map[2] = { .ain = {.ainp = AD7124_AIN2, .ainm = AD7124_AVDD_AVSS_M}, .setup_sel = 0, .channel_enable = true },
//   	 .chan_map[3] = { .ain = {.ainp = AD7124_AIN3, .ainm = AD7124_AVDD_AVSS_M}, .setup_sel = 0, .channel_enable =  true },
//   	 .chan_map[4] = { .ain = {.ainp = AD7124_AIN4, .ainm = AD7124_AVDD_AVSS_M}, .setup_sel = 0, .channel_enable = true },
//   	 .chan_map[5] = { .ain = {.ainp = AD7124_AIN5, .ainm = AD7124_AVDD_AVSS_M}, .setup_sel = 0, .channel_enable = true },
//   	 .chan_map[6] = { .ain = {.ainp = AD7124_AIN6, .ainm = AD7124_AVDD_AVSS_M}, .setup_sel = 0, .channel_enable = true },
//   	 .chan_map[7] = { .ain = {.ainp = AD7124_AIN7, .ainm = AD7124_AVDD_AVSS_M}, .setup_sel = 0, .channel_enable = true },
//   	 .chan_map[8] = { .ain = {.ainp = AD7124_AIN8, .ainm = AD7124_AVDD_AVSS_M}, .setup_sel = 0, .channel_enable = false },
//   	 .chan_map[9] = { .ain = {.ainp = AD7124_AIN9, .ainm = AD7124_AVDD_AVSS_M}, .setup_sel = 0, .channel_enable = false },
//   	 .chan_map[10] = { .ain = {.ainp = AD7124_AIN10, .ainm = AD7124_AVDD_AVSS_M}, .setup_sel = 0, .channel_enable = false },
//   	 .chan_map[11] = { .ain = {.ainp = AD7124_AIN11, .ainm = AD7124_AVDD_AVSS_M}, .setup_sel = 0, .channel_enable = false },
//   	 .chan_map[12] = { .ain = {.ainp = AD7124_AIN12, .ainm = AD7124_AVDD_AVSS_M}, .setup_sel = 0, .channel_enable = false },
//   	 .chan_map[13] = { .ain = {.ainp = AD7124_AIN13, .ainm = AD7124_AVDD_AVSS_M}, .setup_sel = 0, .channel_enable = false },
//
//     };
//
//     ret = ad7124_setup(&ad7124_pc104, &ad7124_init_param_pc104);
//     	if (ret != 0)
//     		printf("ERROR AD7124: %b ", ret);
//     		return ret;
//


//   	// MAX31856 Setup || Temp K-Type Thermocouples Readings INIT


//   	// T1
//
//   	max31856_gpio_t max31856T1PIN = {
//   	    .gpio_port = T1_EN_GPIO_Port,
//   	    .gpio_pin  = T1_EN_Pin
//   	};
//
//   	max31856_t max31856T1 = {
//   			.spi_handle = &hspi2,
// 			.cs_pin = max31856T1PIN
//
//   	};
//
//
//
//   	max31856_init(&max31856T1);
//
//   	max31856_set_noise_filter(&max31856T1, CR0_FILTER_OUT_60Hz); // Noise filter is for filtering out EMI in very long wires
//   	max31856_set_cold_junction_enable(&max31856T1, CR0_CJ_ENABLED); // External Sensor which measures the cold junction and references
//   	max31856_set_thermocouple_type(&max31856T1, CR1_TC_TYPE_K); // K - type thermocouple
//   	max31856_set_average_samples(&max31856T1, CR1_AVG_TC_SAMPLES_2);
//   	max31856_set_open_circuit_fault_detection(&max31856T1, CR0_OC_DETECT_ENABLED_TC_LESS_2ms);
//   	max31856_set_conversion_mode(&max31856T1, CR0_CJ_DISABLED); // need to disable for single we don't have access to the DRDY pins thus we have to estimate polling time.
//


//   	// T2

//   	max31856_gpio_t max31856T2PIN = {
//   			.gpio_port = T2_EN_GPIO_Port,
// 			.gpio_pin  = T2_EN_Pin
//   	  	};
//
//   	max31856_t max31856T2 = {
//   			.spi_handle = &hspi2,
//   			.cs_pin = max31856T2PIN
//   	};
//
// 	max31856_init(&max31856T2);
//
//   	max31856_set_noise_filter(&max31856T2, CR0_FILTER_OUT_60Hz);
//   	max31856_set_cold_junction_enable(&max31856T2, CR0_CJ_ENABLED); // External Sensor which measures the cold junction and references
//   	max31856_set_thermocouple_type(&max31856T2, CR1_TC_TYPE_K); // K - type thermocouple
//   	max31856_set_average_samples(&max31856T2, CR1_AVG_TC_SAMPLES_2);
//   	max31856_set_open_circuit_fault_detection(&max31856T2, CR0_OC_DETECT_ENABLED_TC_LESS_2ms);
//   	max31856_set_conversion_mode(&max31856T2, CR0_CONV_CONTINUOUS); // continous mode for testing


//   	// T3

//   	max31856_gpio_t max31856T3PIN = {
//   		.gpio_port = T3_EN_GPIO_Port,
// 		.gpio_pin  = T3_EN_Pin
//   	};

//   	max31856_t max31856T3 = {
//   			.spi_handle = &hspi2,
//   			.cs_pin = max31856T3PIN
//   	};

// 	max31856_init(&max31856T3);

//   	max31856_set_noise_filter(&max31856T3, CR0_FILTER_OUT_60Hz);
//   	max31856_set_cold_junction_enable(&max31856T3, CR0_CJ_ENABLED);
//   	max31856_set_thermocouple_type(&max31856T3, CR1_TC_TYPE_K);
//   	max31856_set_average_samples(&max31856T3, CR1_AVG_TC_SAMPLES_2);
//   	max31856_set_open_circuit_fault_detection(&max31856T3, CR0_OC_DETECT_ENABLED_TC_LESS_2ms);
//   	max31856_set_conversion_mode(&max31856T3, CR0_CONV_CONTINUOUS);




//   	// T4
//
//   	max31856_gpio_t max31856T4PIN = {
//   		.gpio_port = T4_EN_GPIO_Port,
// 		.gpio_pin  = T4_EN_Pin
//   	};
//
//   	max31856_t max31856T4 = {
//   			.spi_handle = &hspi2,
//   			.cs_pin = max31856T4PIN
//   	};
//
// 	max31856_init(&max31856T4);
//
//   	max31856_set_noise_filter(&max31856T4, CR0_FILTER_OUT_60Hz);
//   	max31856_set_cold_junction_enable(&max31856T4, CR0_CJ_ENABLED);
//   	max31856_set_thermocouple_type(&max31856T4, CR1_TC_TYPE_K);
//   	max31856_set_average_samples(&max31856T4, CR1_AVG_TC_SAMPLES_2);
//   	max31856_set_open_circuit_fault_detection(&max31856T4, CR0_OC_DETECT_ENABLED_TC_LESS_2ms);
//   	max31856_set_conversion_mode(&max31856T4, CR0_CONV_CONTINUOUS);
//


//   	// T5

//   	max31856_gpio_t max31856T5PIN = {
//   		.gpio_port = T5_EN_GPIO_Port,
// 		.gpio_pin = T5_EN_Pin
//   	};

//   	max31856_t max31856T5 = {
//   			.spi_handle = &hspi2,
//   			.cs_pin = max31856T5PIN
//   	};

// 	max31856_init(&max31856T5);

//   	max31856_set_noise_filter(&max31856T5, CR0_FILTER_OUT_60Hz);
//   	max31856_set_cold_junction_enable(&max31856T5, CR0_CJ_ENABLED);
//   	max31856_set_thermocouple_type(&max31856T5, CR1_TC_TYPE_K);
//   	max31856_set_average_samples(&max31856T5, CR1_AVG_TC_SAMPLES_2);
//   	max31856_set_open_circuit_fault_detection(&max31856T5, CR0_OC_DETECT_ENABLED_TC_LESS_2ms);
//   	max31856_set_conversion_mode(&max31856T5, CR0_CONV_CONTINUOUS);





//   	// FDC2214 SETUP

//   	// Reset Registers in Device.
//
//   	reset_fdc2214();
//
////   	// Init FDC2214 ALL FOUR CHANNELS w/ config AND adequate register settings
//
//   	FDC2214_Init();
//











  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	  HAL_GPIO_TogglePin(LED_PIN_GPIO_Port, LED_PIN_Pin);

	  HAL_Delay(200);
//	  printf("We made it 1 ");





//	  HAL_UART_Transmit(&huart3,TX_Buffer,sizeof(TX_Buffer),1000); // "Hello World!" // UART Direct Test

//	  printf("Actuation of Valve 15 Starting... in 15 seconds");

//	  HAL_GPIO_WritePin(valve1_GPIO_Port, valve1_Pin, GPIO_PIN_SET);

//	  HAL_Delay(5000);



//	  HAL_Delay(5000);
//
//	  printf("Actuation of Valve 15 Starting... in 10 seconds");
//
//
//	  HAL_Delay(5000);
//
//	  printf("Actuation of Valve 15 Starting... in 5 seconds");
//
//	  HAL_Delay(5000);
//
//
//	  HAL_GPIO_WritePin(valve15_GPIO_Port, valve15_Pin, GPIO_PIN_SET);
//
//	  printf("Valve 15 Actuated");



//

#ifdef AD7124
//	  printf("We made it 2 ");
	  status[2U] = AD7124_ReadRegister(&AD7124_Handler, AD7124_ID_REG, 1, &val);

	  if(status[2U]){
		  printf("failed to read device id: check spi \n");
		  printf("Error: %d", status[2U]);
	  }
	  else{
		  device_id = val & 0xF0;
		  printf("Device ID: %ld", device_id);
		  if(device_id == 16){


			  printf("SUCCESS: Status of AD2214: %d \n", status[0]);


			  /* Optional: check for errors */
			  status[1U] = AD7124_ErrorCheck(&AD7124_Handler, &ad7124_error);

			  printf("Error Check of AD2214: %d \n", status[1]);
			  printf("Error #: %ld \n", ad7124_error);



			  /* Read conversion results from ADC */
			  status[2U] = AD7124_ReadSampleData(&AD7124_Handler);

			  printf("Read Sample AD2214 Result: %d \n", status[2]);

			  if (AD7124_ChannelSamples[2] && AD7124_ChannelSamples[3])
			  {
			  // Convert raw ADC data from channel 0 to millivolts (example scaling)
		//	      voltage = ( ( (double)(AD7124_ChannelSamples[0U] / 8388608.0) - 1.0) * 2.5) * 1000.0;

				  printf("Channel Sample 1 %ld", AD7124_ChannelSamples[2U]);
				  printf("Channel Sample 2 %ld", AD7124_ChannelSamples[3U]);


			  // Convert raw ADC data from channel to voltage
				voltage1 = (AD7124_ChannelSamples[2U] * 3.3) / 16777216;

				voltage2 = (AD7124_ChannelSamples[2U] * 3.3) / 16777216;


				printf("Voltage 1:  %f", voltage1);

				printf("Voltage 2:  %f", voltage2);

			  }
		  }
	  }

#endif



//	  Serial_Print("Transmitting"); // Serial_Print custom function test.

//	   Serial_Printf("Temperature Test %d C\r\n", 100); // Serial_Print custom formatted print function


	  // TEST READS...

	//   Serial_Print("Test IC Reads"); // Serial_Print custom function test.

	  // For Repo Branch...


	  // polling method -> Blocks CPU until UART receive is done.
// 	  while(HAL_UART_Receive(&huart3, &RX_CMD, 8,1000)){ // uart receive block will continously try to fetch.


// 		  // Polling for Seperate Pressure Sensors.

// 		switch(RX_CMD){

// 		  // Read AD7124

// // Read PT Valves
// 			case CMD_READ_PT1:
// 				value = ad7124_read_channel_voltage(ad7124, CH_READ_PT0);
// 				// will need to convert the voltage value to a current / temp reading function eventually in ad7124.h
// 				Serial_Printf("Pressure Reading PT 1: %d \r\n", value);
// 			case CMD_READ_PT2:
// 				value = ad7124_read_channel_voltage(ad7124, CH_READ_PT1);
// 				Serial_Printf("Pressure Reading PT 2: %d \r\n", value);
// 			case CMD_READ_PT3:
// 				value = ad7124_read_channel_voltage(ad7124, CH_READ_PT2);
// 				Serial_Printf("Pressure Reading PT 3: %d \r\n", value);
// 			case CMD_READ_PT4:
// 				value = ad7124_read_channel_voltage(ad7124, CH_READ_PT3);
// 				Serial_Printf("Pressure Reading PT 4: %d \r\n", value);
// 			case CMD_READ_PT5:
// 				value = ad7124_read_channel_voltage(ad7124, CH_READ_PT4);
// 				Serial_Printf("Pressure Reading PT 5: %d \r\n", value);
// 			case CMD_READ_PT6:
// 				value = ad7124_read_channel_voltage(ad7124, CH_READ_PT5);
// 				Serial_Printf("Pressure Reading PT 6: %d \r\n", value);
// 			case CMD_READ_PT7:
// 				value = ad7124_read_channel_voltage(ad7124, CH_READ_PT6);
// 				Serial_Printf("Pressure Reading PT 7: %d \r\n", value);
// 			case CMD_READ_PT8:
// 				value = ad7124_read_channel_voltage(ad7124, CH_READ_PT7);
// 				Serial_Printf("Pressure Reading PT 8: %d \r\n", value);


// // Read TC Valves
// 			case CMD_READ_TC1:

// 				max31856_trigger_one_shot(&max31856T1);
// 				HAL_Delay(200); // Wait until single is ready
// 				temp = max31856_read_TC_temp(&max31856T1); // compensates already for cold junction reading
// 				max31856_read_fault(&max31856T1);
// 				  	if (max31856T1.sr.val) {
// 				  	  Serial_Print("TC1 Read Fail");
// 				  	}
// 				Serial_Printf("Temperature Reading TC1: %f \r\n", temp);


// 			case CMD_READ_TC2:
// 				temp = max31856_read_TC_temp(&max31856T2);
// 				max31856_read_fault(&max31856T2);
// 				if (max31856T2.sr.val) {
// 					Serial_Print("TC2 Read Fail");
// 				}
// 				Serial_Printf("Temperature Reading TC2: %f \r\n", temp);

// 			case CMD_READ_TC3:
// 				temp = max31856_read_TC_temp(&max31856T3);
// 				max31856_read_fault(&max31856T3);
// 				if (max31856T3.sr.val) {
// 					Serial_Print("TC3 Read Fail");
// 			    }
// 				Serial_Printf("Temperature Reading TC3: %f \r\n", temp);


// 			case CMD_READ_TC4:
// 				temp = max31856_read_TC_temp(&max31856T4);
// 				max31856_read_fault(&max31856T4);
// 				if (max31856T4.sr.val) {
// 					Serial_Print("TC4 Read Fail");
// 			    }
// 				Serial_Printf("Temperature Reading TC4: %f \r\n", temp);


// 			case CMD_READ_TC5:
// 				temp = max31856_read_TC_temp(&max31856T5);
// 				max31856_read_fault(&max31856T5);
// 				if (max31856T5.sr.val) {
// 					Serial_Print("TC5 Read Fail");
// 			    }
// 				Serial_Printf("Temperature Reading TC5: %f \r\n", temp);


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

// 			case CMD_READ_VBAT_VA:
// 				value = ad7124_read_channel_voltage(ad7124_pc104, CH_READ_VBAT_VA);
// 				Serial_Printf("PC104 Voltage Reading VBAT_VA: %d \r\n", value);
// 			case CMD_READ_VBAT_VB:
// 				value = ad7124_read_channel_voltage(ad7124_pc104, CH_READ_VBAT_VB);
// 				Serial_Printf("PC104 Voltage Reading VBAT_VB: %d \r\n", value);

// 			case CMD_READ_12VB_VA:
// 				value = ad7124_read_channel_voltage(ad7124_pc104, CH_READ_12VB_VA);
// 				Serial_Printf("PC104 Voltage Reading 12VB_VA: %d \r\n", value);

// 			case CMD_READ_12VB_VB:
// 				value = ad7124_read_channel_voltage(ad7124_pc104, CH_READ_12VB_VB);
// 				Serial_Printf("PC104 Voltage Reading 12VB_VB: %d \r\n", value);

// // Read PC104 Currents
// 			case CMD_READ_12VA_VB_CURRENT:
// 				value = ad7124_read_channel_current_pc104(ad7124_pc104, CH_READ_12VA_VB);
// 				Serial_Printf("PC104 Current Reading 12VA_VB: %d \r\n", value);

// 			case CMD_READ_12VA_VA_CURRENT:
// 				value = ad7124_read_channel_current_pc104(ad7124_pc104, CH_READ_12VA_VA);
// 				Serial_Printf("PC104 Current Reading 12VA_VA: %d \r\n", value);

// 			case CMD_READ_3V3_VB_CURRENT:
// 				value = ad7124_read_channel_current_pc104(ad7124_pc104, CH_READ_3V3_VB);
// 				Serial_Printf("PC104 Current Reading 3V3_VB : %d \r\n", value);

// 			case CMD_READ_3V3_VA_CURRENT:
// 				value = ad7124_read_channel_current_pc104(ad7124_pc104, CH_READ_3V3_VA);
// 				Serial_Printf("PC104 Current Reading 3V3_VA : %d \r\n", value);

// 			case CMD_READ_VBAT_VA_CURRENT:
// 				value = ad7124_read_channel_current_pc104(ad7124_pc104, CH_READ_VBAT_VA);
// 				Serial_Printf("PC104 Current Reading VBAT_VA : %d \r\n", value);

// 			case CMD_READ_VBAT_VB_CURRENT:
// 				value = ad7124_read_channel_current_pc104(ad7124_pc104, CH_READ_VBAT_VB);
// 				Serial_Printf("PC104 Current Reading VBAT_VB : %d \r\n", value);

// 			case CMD_READ_12VB_VA_CURRENT:
// 				value = ad7124_read_channel_current_pc104(ad7124_pc104, CH_READ_12VB_VA);
// 				Serial_Printf("PC104 Current Reading 12VB_VA: %d \r\n",  value);

// 			case CMD_READ_12VB_VB_CURRENT:
// 				value = ad7124_read_channel_current_pc104(ad7124_pc104, CH_READ_12VB_VB);
// 				Serial_Printf("PC104 Current Reading 12VB_VB: %d \r\n", value);


// // Open Solenoids (ON/OFF)

// 			case CMD_OPEN_SOL1:
// 				HAL_GPIO_WritePin(valve1_GPIO_Port, valve1_Pin, GPIO_PIN_SET);

// 			case CMD_OPEN_SOL2:
// 				HAL_GPIO_WritePin(valve2_GPIO_Port, valve2_Pin, GPIO_PIN_SET);

// 			case CMD_OPEN_SOL3:
// 				HAL_GPIO_WritePin(valve3_GPIO_Port, valve3_Pin, GPIO_PIN_SET);

// 			case CMD_OPEN_SOL4: // IEP VALVE (PWM)
// 				HAL_GPIO_WritePin(TIM8_CH1_VALVE4_GPIO_Port, TIM8_CH1_VALVE4_Pin, GPIO_PIN_SET);

// 			case CMD_OPEN_SOL5:
// 				HAL_GPIO_WritePin(valve5_GPIO_Port, valve5_Pin, GPIO_PIN_SET);

// 			case CMD_OPEN_SOL6: // IEP VALVE (PWM)
// 				HAL_GPIO_WritePin(TIM__CH1_VALVE6_GPIO_Port, TIM__CH1_VALVE6_Pin, GPIO_PIN_SET);

// 			case CMD_OPEN_SOL7:
// 				HAL_GPIO_WritePin(valve7_GPIO_Port, valve7_Pin, GPIO_PIN_SET);

// 			case CMD_OPEN_SOL8:
// 				HAL_GPIO_WritePin(valve8_GPIO_Port, valve8_Pin, GPIO_PIN_SET);

// 			case CMD_OPEN_SOL9:
// 				HAL_GPIO_WritePin(valve9_GPIO_Port, valve9_Pin, GPIO_PIN_SET);

// 			case CMD_OPEN_SOL10:
// 				HAL_GPIO_WritePin(valve10_GPIO_Port, valve10_Pin, GPIO_PIN_SET);

// 			case CMD_OPEN_SOL11:
// 				HAL_GPIO_WritePin(valve11_GPIO_Port, valve11_Pin, GPIO_PIN_SET);

// 			case CMD_OPEN_SOL12:
// 				HAL_GPIO_WritePin(valve12_GPIO_Port, valve12_Pin, GPIO_PIN_SET);

// 			case CMD_OPEN_SOL13:
// 				HAL_GPIO_WritePin(valve13_GPIO_Port, valve13_Pin, GPIO_PIN_SET);

// 			case CMD_OPEN_SOL14:
// 				HAL_GPIO_WritePin(valve14_GPIO_Port, valve14_Pin, GPIO_PIN_SET);

// 			case CMD_OPEN_SOL15:
// 				HAL_GPIO_WritePin(valve15_GPIO_Port, valve15_Pin, GPIO_PIN_SET);

// 			case CMD_OPEN_SOL16:
// 				HAL_GPIO_WritePin(valve16_GPIO_Port, valve16_Pin, GPIO_PIN_SET);

// 			case CMD_OPEN_SOL17:
// 				HAL_GPIO_WritePin(valve17_GPIO_Port, valve17_Pin, GPIO_PIN_SET);

// // Close Valves
// 			case CMD_CLOSE_SOL1:
// 				HAL_GPIO_WritePin(valve1_GPIO_Port, valve1_Pin, GPIO_PIN_RESET);

// 			case CMD_CLOSE_SOL2:
// 				HAL_GPIO_WritePin(valve2_GPIO_Port, valve2_Pin, GPIO_PIN_RESET);

// 			case CMD_CLOSE_SOL3:
// 				HAL_GPIO_WritePin(valve3_GPIO_Port, valve3_Pin, GPIO_PIN_RESET);

// 			case CMD_CLOSE_SOL4: // IEP VALVE 4
// 				HAL_GPIO_WritePin(TIM8_CH1_VALVE4_GPIO_Port, TIM8_CH1_VALVE4_Pin, GPIO_PIN_RESET);

// 			case CMD_CLOSE_SOL5:
// 				HAL_GPIO_WritePin(valve5_GPIO_Port, valve5_Pin, GPIO_PIN_RESET);

// 			case CMD_CLOSE_SOL6: // IEP VALVE 6
// 				HAL_GPIO_WritePin(TIM__CH1_VALVE6_GPIO_Port, TIM__CH1_VALVE6_Pin, GPIO_PIN_RESET);

// 			case CMD_CLOSE_SOL7:
// 				HAL_GPIO_WritePin(valve7_GPIO_Port, valve7_Pin, GPIO_PIN_RESET);

// 			case CMD_CLOSE_SOL8:
// 				HAL_GPIO_WritePin(valve8_GPIO_Port, valve8_Pin, GPIO_PIN_RESET);

// 			case CMD_CLOSE_SOL9:
// 				HAL_GPIO_WritePin(valve9_GPIO_Port, valve9_Pin, GPIO_PIN_RESET);

// 			case CMD_CLOSE_SOL10:
// 				HAL_GPIO_WritePin(valve10_GPIO_Port, valve10_Pin, GPIO_PIN_RESET);

// 			case CMD_CLOSE_SOL11:
// 				HAL_GPIO_WritePin(valve11_GPIO_Port, valve11_Pin, GPIO_PIN_RESET);

// 			case CMD_CLOSE_SOL12:
// 				HAL_GPIO_WritePin(valve12_GPIO_Port, valve12_Pin, GPIO_PIN_RESET);

// 			case CMD_CLOSE_SOL13:
// 				HAL_GPIO_WritePin(valve13_GPIO_Port, valve13_Pin, GPIO_PIN_RESET);

// 			case CMD_CLOSE_SOL14:
// 				HAL_GPIO_WritePin(valve14_GPIO_Port, valve14_Pin, GPIO_PIN_RESET);

// 			case CMD_CLOSE_SOL15:
// 				HAL_GPIO_WritePin(valve15_GPIO_Port, valve15_Pin, GPIO_PIN_RESET);

// 			case CMD_CLOSE_SOL16:
// 				HAL_GPIO_WritePin(valve16_GPIO_Port, valve16_Pin, GPIO_PIN_RESET);

// 			case CMD_CLOSE_SOL17:
// 				HAL_GPIO_WritePin(valve17_GPIO_Port, valve17_Pin, GPIO_PIN_RESET);

// // READ FDC2214 Capacitance Measurements.

// 			case READ_CAPACITANCE_A1:
// 				capacitance = FDC2214_read_differential_capacitance(1);
// 				Serial_Printf("Differential Capacitance Reading FDC2214 A1: %f \r\n", capacitance);
// 			case READ_CAPACITANCE_A2:
// 				capacitance = FDC2214_read_differential_capacitance(2);
// 				Serial_Printf("Differential Capacitance Reading FDC2214 A2: %f \r\n", capacitance);
// 			case READ_CATALYST_LEVEL_A1:
// 				level = FDC2214_read_accumulator_height(1);
// 				Serial_Printf("Catalyst Height Reading FDC2214 A1: %d \r\n", level);
// 			case READ_CATALYST_LEVEL_A2:
// 				level = FDC2214_read_accumulator_height(2);
// 				Serial_Printf("Catalyst Height Reading FDC2214 A2: %d \r\n", level);



// 		}
// 	  }


//
//	   max31856_trigger_one_shot(&max31856T1);
//	   HAL_Delay(200); // Wait until single is ready
//	   temperature = max31856_read_CJ_temp(&max31856T1); // compensates already for cold junction reading
//	   max31856_read_fault(&max31856T1);
//	   if (max31856T1.sr.val) {
//	   		printf("TC Read Fail ");
//	   		printf("ERROR TC1 #: %d ",max31856T1.sr.val);
//
//	   }
//	   printf("Temperature Reading TC1: %f \r\n", temperature);
//
//
//	   temperature = max31856_read_TC_temp(&max31856T1); // compensates already for cold junction reading
//	   if (max31856T1.sr.val) {
//	   	   	printf("TC TEMP Read Fail ");
//	   	   	printf("ERROR TC1 #: %d ",max31856T1.sr.val);
//
//	   }
//	   printf("Temperature Reading TC1: %f \r\n", temperature);

// 	  // TESTING DEBUG PURPOSES w/ ST-LINK
//
// 	  printf("TESTING DEBUG PURPOSES LOADING... \n");
//
// 	  printf("Reading Device ID's... \n");
//
// 	  bool val = FDC2214_Check_Device_ID();
// 	  if(val){
// 		  printf("FDC NOMINAL \n");
// 	  }
// 	  else{
// 		  printf("FDC FAIL \n");
// 	  }
// 	  printf("FDC2214 Device Read: %d\n", val);
//
// 	  FDC2214_Device_ID(device_id);
// 	  printf("FDC2214 Device ID: %d\n", device_id);
//
//
//// 	  The float formatting support is not enabled, check your MCU Settings from "Project Properties >
// 	  // C/C++ Build > Settings > Tool Settings", or add manually "-u _printf_float" in linker flags.
//
//
// 	for(int i =0; i<4; i++){
//
// 		uint64_t raw = FDC2214_read_data(i);
// 		double f_sensor;
//
// 		f_sensor = (((float) raw) / ((float)(1UL << 28))) * FDC2214_F_REF; // datasheet equation
//
// 		double omega = 2.0f * 3.14159265f * f_sensor;
// 		double total_c = (1.0f/(FDC2214_L_HENRY * omega * omega));
//
// 		// 	 capacitance = FDC2214_read_capacitance(3, &c1);
// 		// 	 capacitance = FDC2214_read_capacitance(3, &c2);
// 		printf("Channel: %d \n", i);
// 		printf("F_Sensor: %lf \r\n", f_sensor);
// 		printf("Omega: %lf \r\n", omega);
// 		printf("total_c: %lf \r\n", total_c);


// 	}



// 	  ad7124_read_register(ad7124, &ad7124->regs[AD7124_ID_REG]);
// 	  printf("Pressure ADC7124 Device ID: %d\n", (int) ad7124->regs[AD7124_ID_REG].value);
//

// 	  ad7124_read_register(ad7124_pc104, &ad7124_pc104->regs[AD7124_ID_REG]);
// 	  printf("PC104 Stack Voltage ADC7124 Device ID: 0x %X\n", (int) ad7124_pc104->regs[AD7124_ID_REG].value);
//
//
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


// Retarget __io_putchar(*ptr++) to a specific hardware function for printf to work.

int _write(int file, char *ptr, int len)
{
  (void)file;
  int DataIdx;

  for (DataIdx = 0; DataIdx < len; DataIdx++)
  {
    ITM_SendChar(*ptr++);
  }
  return len;
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
