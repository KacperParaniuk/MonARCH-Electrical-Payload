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
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

#include "gpio_driver.h"
#include "uart_handler.h"
#include "uart_protocol.h"

#include "ad7124.h"
#include "ad7124_regs.h"
#include "ad7124_sensor.h"

#include "max31856.h"


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

struct ad7124_dev *ad7124;  // device handle (Defined Globally)


struct max31856_t *max31856;


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




  uint8_t RX_CMD= 0; // single byte for all UART commands.


  uint8_t TX_Buffer[] = "Hello, World!\r\n";
  // "\r" move cursor to start of line
  // "\n" new line


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
  /* USER CODE BEGIN 2 */


  // ADC7124 || PT Readings Init

  int32_t value;		/* Stores raw value read from the ADC */
  float temp; /* stores value for any TC */
  int32_t ret = 0;	/* Return value */


  struct ad7124_init_param ad7124_init_param = {
	  .hspi = &hspi2,
      .cs_port = PT_EN_GPIO_Port,            // ← pt en pointer
      .cs_pin = PT_EN_Pin,       //
      .regs = ad7124_regs,         // these are register values of the ad7124
      .spi_rdy_poll_cnt = 25000,

	  .mode = AD7124_SINGLE, // continuous equals IC constantly converting || single equal we tell it when to convert / read otherwise the chip is powered down.
	  .active_device = ID_AD7124_8,
	  .ref_en = false, // 2.5 internal reference (not using) b/c reading might go over this.
	  .power_mode = AD7124_LOW_POWER, // << What are the differences?

	  .setups[0] = {
		  .bi_unipolar = false,  // unipolar (don't have differential pairs)
		  .burnout = AD7124_BURNOUT_OFF,
		  .ref_source = AVDD_AVSS, // reference source is important and what we are doing calculations in REFERENCE to... 3.3v
		  .ain_buff = true, // buffers analog input to present high impedance (strengthens signal integrity)
		  .ref_buff = false, // sets reference source for high impedance
		  .pga = AD7124_PGA_1, // amplification of input signal.
	  },

	  // channel map

	  .chan_map[0] = { .ain = {.ainp = AD7124_AIN0, .ainm = AD7124_AVDD_AVSS_M}, .setup_sel = 0, .channel_enable = false },
	  .chan_map[1] = { .ain = {.ainp = AD7124_AIN1, .ainm = AD7124_AVDD_AVSS_M}, .setup_sel = 0, .channel_enable = true },
	  .chan_map[2] = { .ain = {.ainp = AD7124_AIN2, .ainm = AD7124_AVDD_AVSS_M}, .setup_sel = 0, .channel_enable = true },
	  .chan_map[3] = { .ain = {.ainp = AD7124_AIN3, .ainm = AD7124_AVDD_AVSS_M}, .setup_sel = 0, .channel_enable =  true },
	  .chan_map[4] = { .ain = {.ainp = AD7124_AIN4, .ainm = AD7124_AVDD_AVSS_M}, .setup_sel = 0, .channel_enable = true },
	  .chan_map[5] = { .ain = {.ainp = AD7124_AIN5, .ainm = AD7124_AVDD_AVSS_M}, .setup_sel = 0, .channel_enable = true },
	  .chan_map[6] = { .ain = {.ainp = AD7124_AIN6, .ainm = AD7124_AVDD_AVSS_M}, .setup_sel = 0, .channel_enable = false },
	  .chan_map[7] = { .ain = {.ainp = AD7124_AIN7, .ainm = AD7124_AVDD_AVSS_M}, .setup_sel = 0, .channel_enable = false },
	  .chan_map[8] = { .ain = {.ainp = AD7124_AIN8, .ainm = AD7124_AVDD_AVSS_M}, .setup_sel = 0, .channel_enable = false },
	  .chan_map[9] = { .ain = {.ainp = AD7124_AIN9, .ainm = AD7124_AVDD_AVSS_M}, .setup_sel = 0, .channel_enable = false },
	  .chan_map[10] = { .ain = {.ainp = AD7124_AIN10, .ainm = AD7124_AVDD_AVSS_M}, .setup_sel = 0, .channel_enable = false },
	  .chan_map[11] = { .ain = {.ainp = AD7124_AIN11, .ainm = AD7124_AVDD_AVSS_M}, .setup_sel = 0, .channel_enable = true },
	  .chan_map[12] = { .ain = {.ainp = AD7124_AIN12, .ainm = AD7124_AVDD_AVSS_M}, .setup_sel = 0, .channel_enable = true },
	  .chan_map[13] = { .ain = {.ainp = AD7124_AIN13, .ainm = AD7124_AVDD_AVSS_M}, .setup_sel = 0, .channel_enable = true },

  };

  ret = ad7124_setup(&ad7124, &ad7124_init_param);
  	if (ret != 0)
  		return ret;

  	// MAX31856 Setup || Temp K-Type Thermocouples Readings INIT


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
  	max31856_set_conversion_mode(&max31856T1, CR0_CJ_DISABLED); // need to disable for single we don't have access to the DRDY pins thus we have to estimate polling time.



  	// T2

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



  	// T5

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




  	//

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	  HAL_GPIO_TogglePin(LED_PIN_GPIO_Port, LED_PIN_Pin);

	  HAL_UART_Transmit(&huart3,TX_Buffer,sizeof(TX_Buffer),1000); // "Hello World!" // UART Direct Test

	  HAL_Delay(200);

	  Serial_Print("Transmitting"); // Serial_Print custom function test.

	  Serial_Printf("Temperature Test %d C\r\n", 100); // Serial_Print custom formatted print function


	  HAL_GPIO_TogglePin(LED_PIN_GPIO_Port, LED_PIN_Pin);

	  HAL_Delay(200);

	  // TEST READS...

	  Serial_Print("Test IC Reads"); // Serial_Print custom function test.

	  // For Repo Branch...


	  // polling method -> Blocks CPU until UART receive is done.
	  while(HAL_UART_Receive(&huart3, &RX_CMD, 8,1000)){ // uart receive block will continously try to fetch.


		  // Polling for Seperate Pressure Sensors.


		switch(RX_CMD){

		  // Read AD7124

			case CMD_READ_PT1:
				value = ad7124_read_channel_voltage(CH_READ_PT0);

				// will need to convert the voltage value to a current / temp reading function eventually in ad7124.h

				Serial_Printf("Pressure Reading PT 1: %d \r\n", value);
			case CMD_READ_PT2:
				value = ad7124_read_channel_voltage(CH_READ_PT1);
				Serial_Printf("Pressure Reading PT 2: %d \r\n", value);
			case CMD_READ_PT3:
				value = ad7124_read_channel_voltage(CH_READ_PT2);
				Serial_Printf("Pressure Reading PT 3: %d \r\n", value);
			case CMD_READ_PT4:
				value = ad7124_read_channel_voltage(CH_READ_PT3);
				Serial_Printf("Pressure Reading PT 4: %d \r\n", value);
			case CMD_READ_PT5:
				value = ad7124_read_channel_voltage(CH_READ_PT4);
				Serial_Printf("Pressure Reading PT 5: %d \r\n", value);
			case CMD_READ_PT6:
				value = ad7124_read_channel_voltage(CH_READ_PT5);
				Serial_Printf("Pressure Reading PT 6: %d \r\n", value);
			case CMD_READ_PT7:
				value = ad7124_read_channel_voltage(CH_READ_PT6);
				Serial_Printf("Pressure Reading PT 7: %d \r\n", value);
			case CMD_READ_PT8:
				value = ad7124_read_channel_voltage(CH_READ_PT7);
				Serial_Printf("Pressure Reading PT 8: %d \r\n", value);


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



			}











	  }
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
