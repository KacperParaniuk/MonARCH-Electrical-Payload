/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
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
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

#include "systems.h"

#include "ad7124_console_app.h"
#include "ad7124.h"
#include "max31856.h"
#include "fdc2214.h"

#include "control_task.h"



/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
typedef StaticSemaphore_t osStaticMutexDef_t;
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */

extern uint8_t rx_cmd[];
extern uint8_t rx_cmd_copy[];
extern char uart_buffer[];
extern uint32_t device_id;
extern int32_t setupResult;
extern float temperature;
extern float value;

extern uint8_t duty_cycle;

extern max31856_t max31856T1;
extern max31856_t max31856T2;
extern max31856_t max31856T3;
extern max31856_t max31856T4;
extern max31856_t max31856T5;


extern GPIO_PinState pinState;

extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim8;




/* USER CODE END Variables */
/* Definitions for heart_beat */
osThreadId_t heart_beatHandle;
const osThreadAttr_t heart_beat_attributes = {
  .name = "heart_beat",
  .stack_size = 500 * 4,
  .priority = (osPriority_t) osPriorityLow,
};
/* Definitions for Task_UART_RX */
osThreadId_t Task_UART_RXHandle;
const osThreadAttr_t Task_UART_RX_attributes = {
  .name = "Task_UART_RX",
  .stack_size = 500 * 4,
  .priority = (osPriority_t) osPriorityHigh,
};
/* Definitions for Task_Safety */
osThreadId_t Task_SafetyHandle;
const osThreadAttr_t Task_Safety_attributes = {
  .name = "Task_Safety",
  .stack_size = 500 * 4,
  .priority = (osPriority_t) osPriorityHigh,
};
/* Definitions for Task_Experiment */
osThreadId_t Task_ExperimentHandle;
const osThreadAttr_t Task_Experiment_attributes = {
  .name = "Task_Experiment",
  .stack_size = 900 * 4,
  .priority = (osPriority_t) osPriorityAboveNormal,
};
/* Definitions for Task_UART_TX */
osThreadId_t Task_UART_TXHandle;
const osThreadAttr_t Task_UART_TX_attributes = {
  .name = "Task_UART_TX",
  .stack_size = 500 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for Task_Data */
osThreadId_t Task_DataHandle;
const osThreadAttr_t Task_Data_attributes = {
  .name = "Task_Data",
  .stack_size = 500 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for Task_FSM */
osThreadId_t Task_FSMHandle;
const osThreadAttr_t Task_FSM_attributes = {
  .name = "Task_FSM",
  .stack_size = 500 * 4,
  .priority = (osPriority_t) osPriorityHigh,
};
/* Definitions for q_safety_cmds */
osMessageQueueId_t q_safety_cmdsHandle;
const osMessageQueueAttr_t q_safety_cmds_attributes = {
  .name = "q_safety_cmds"
};
/* Definitions for q_normal_cmds */
osMessageQueueId_t q_normal_cmdsHandle;
const osMessageQueueAttr_t q_normal_cmds_attributes = {
  .name = "q_normal_cmds"
};
/* Definitions for fsm_mutex */
osMutexId_t fsm_mutexHandle;
osStaticMutexDef_t myMutex01ControlBlock;
const osMutexAttr_t fsm_mutex_attributes = {
  .name = "fsm_mutex",
  .cb_mem = &myMutex01ControlBlock,
  .cb_size = sizeof(myMutex01ControlBlock),
};
/* Definitions for spi_mutex */
osMutexId_t spi_mutexHandle;
const osMutexAttr_t spi_mutex_attributes = {
  .name = "spi_mutex"
};
/* Definitions for i2c_mutex */
osMutexId_t i2c_mutexHandle;
const osMutexAttr_t i2c_mutex_attributes = {
  .name = "i2c_mutex"
};
/* Definitions for command_flags_mutex */
osMutexId_t command_flags_mutexHandle;
const osMutexAttr_t command_flags_mutex_attributes = {
  .name = "command_flags_mutex"
};
/* Definitions for data_mutex */
osMutexId_t data_mutexHandle;
const osMutexAttr_t data_mutex_attributes = {
  .name = "data_mutex"
};
/* Definitions for error_flag_mutex */
osMutexId_t error_flag_mutexHandle;
const osMutexAttr_t error_flag_mutex_attributes = {
  .name = "error_flag_mutex"
};
/* Definitions for s_rx_semaphore */
osSemaphoreId_t s_rx_semaphoreHandle;
const osSemaphoreAttr_t s_rx_semaphore_attributes = {
  .name = "s_rx_semaphore"
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void *argument);
void StartTask02(void *argument);
void StartTask03(void *argument);
void StartTask04(void *argument);
void StartTask05(void *argument);
void StartTask06(void *argument);
void StartTask07(void *argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */
  /* Create the mutex(es) */
  /* creation of fsm_mutex */
  fsm_mutexHandle = osMutexNew(&fsm_mutex_attributes);

  /* creation of spi_mutex */
  spi_mutexHandle = osMutexNew(&spi_mutex_attributes);

  /* creation of i2c_mutex */
  i2c_mutexHandle = osMutexNew(&i2c_mutex_attributes);

  /* creation of command_flags_mutex */
  command_flags_mutexHandle = osMutexNew(&command_flags_mutex_attributes);

  /* creation of data_mutex */
  data_mutexHandle = osMutexNew(&data_mutex_attributes);

  /* creation of error_flag_mutex */
  error_flag_mutexHandle = osMutexNew(&error_flag_mutex_attributes);

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* Create the semaphores(s) */
  /* creation of s_rx_semaphore */
  s_rx_semaphoreHandle = osSemaphoreNew(1, 0, &s_rx_semaphore_attributes);

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* Create the queue(s) */
  /* creation of q_safety_cmds */
  q_safety_cmdsHandle = osMessageQueueNew (10, sizeof(uint8_t), &q_safety_cmds_attributes);

  /* creation of q_normal_cmds */
  q_normal_cmdsHandle = osMessageQueueNew (10, sizeof(uint8_t), &q_normal_cmds_attributes);

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of heart_beat */
  heart_beatHandle = osThreadNew(StartDefaultTask, NULL, &heart_beat_attributes);

  /* creation of Task_UART_RX */
  Task_UART_RXHandle = osThreadNew(StartTask02, NULL, &Task_UART_RX_attributes);

  /* creation of Task_Safety */
  Task_SafetyHandle = osThreadNew(StartTask03, NULL, &Task_Safety_attributes);

  /* creation of Task_Experiment */
  Task_ExperimentHandle = osThreadNew(StartTask04, NULL, &Task_Experiment_attributes);

  /* creation of Task_UART_TX */
  Task_UART_TXHandle = osThreadNew(StartTask05, NULL, &Task_UART_TX_attributes);

  /* creation of Task_Data */
  Task_DataHandle = osThreadNew(StartTask06, NULL, &Task_Data_attributes);

  /* creation of Task_FSM */
  Task_FSMHandle = osThreadNew(StartTask07, NULL, &Task_FSM_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

}

/* USER CODE BEGIN Header_StartDefaultTask */
/**
  * @brief  Function implementing the heart_beat thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void *argument)
{
  /* USER CODE BEGIN StartDefaultTask */
  /* Infinite loop */
  for(;;)
  {

	// the lowest priority task the heart beat of the program.
	HAL_GPIO_TogglePin(LED_PIN_RED_GPIO_Port, LED_PIN_RED_Pin);
    osDelay(500);

  }
  /* USER CODE END StartDefaultTask */
}

/* USER CODE BEGIN Header_StartTask02 */
/**
* @brief Function implementing the Task_UART_RX thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartTask02 */
void StartTask02(void *argument)
{
  /* USER CODE BEGIN StartTask02 */
  /* Infinite loop */
  for(;;)
  {

	 // wait for semaphore to be released. This means the interrupt fired.


	if(osSemaphoreAcquire(s_rx_semaphoreHandle, osWaitForever)== osOK){

		UART_Frame_t rx_frame = {
			.cmd = rx_cmd_copy[0],
			.arg = rx_cmd_copy[1]
		};
		
		// decipher the rx_cmd - safety or normal command
		if(cmd_is_safety(rx_frame.cmd)){
			// add cmds to queue so that either safety_cmd can execute or normal in task_experiment
			osMessageQueuePut(q_safety_cmdsHandle, &rx_frame, 0, 0);
		}
		else{

			osMessageQueuePut(q_normal_cmdsHandle, &rx_frame, 0, 0);
		}

	}



    osDelay(1);
  }
  /* USER CODE END StartTask02 */
}

/* USER CODE BEGIN Header_StartTask03 */
/**
* @brief Function implementing the Task_Safety thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartTask03 */
void StartTask03(void *argument)
{
  /* USER CODE BEGIN StartTask03 */
  /* Infinite loop */
  for(;;)
  {

	  // SAFETY TASK
	  UART_Frame_t frame; // create an instance of the struct to store into

	  if(osMessageQueueGet(q_safety_cmdsHandle, &frame, NULL, osWaitForever)==osOK){

//		  printf("SAFETY COMMAND");





	  }





    osDelay(1);
  }
  /* USER CODE END StartTask03 */
}

/* USER CODE BEGIN Header_StartTask04 */
/**
* @brief Function implementing the Task_Experiment thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartTask04 */
void StartTask04(void *argument)
{
  /* USER CODE BEGIN StartTask04 */
  /* Infinite loop */
  UART_Frame_t frame; // create an instance of the struct to store into

  for(;;)
  {

	  // experiment / normal cmd task


	  // block until cmd gets pushed onto queue.

	  if(osMessageQueueGet(q_normal_cmdsHandle, &frame, NULL, osWaitForever)==osOK){

//		  printf("Normal CMD Received");

		  // fsm integration here?





		  switch(frame.cmd){ // decode command and execute
// Open Solenoid Valve Commands



		 		case CMD_OPEN_SOL1:
		 			HAL_GPIO_WritePin(valve1_GPIO_Port, valve1_Pin, GPIO_PIN_SET); break;
		 		case CMD_OPEN_SOL2:
		 			HAL_GPIO_WritePin(valve2_GPIO_Port, valve2_Pin, GPIO_PIN_SET); break;
		 		case CMD_OPEN_SOL3:
		 		 	HAL_GPIO_WritePin(valve3_GPIO_Port, valve3_Pin, GPIO_PIN_SET); break;
		 		case CMD_OPEN_SOL4: // IEP VALVE (PWM)
		 		 	HAL_GPIO_WritePin(TIM8_CH1_VALVE4_GPIO_Port, TIM8_CH1_VALVE4_Pin, GPIO_PIN_SET); break;
		 		case CMD_OPEN_SOL5:
		 		 	HAL_GPIO_WritePin(valve5_GPIO_Port, valve5_Pin, GPIO_PIN_SET); break;
		 		case CMD_OPEN_SOL6: // IEP VALVE (PWM)
		 		 	HAL_GPIO_WritePin(TIM3_CH3_VALVE6_GPIO_Port, TIM3_CH3_VALVE6_Pin, GPIO_PIN_SET); break;
		 		case CMD_OPEN_SOL7:
		 		    HAL_GPIO_WritePin(valve7_GPIO_Port, valve7_Pin, GPIO_PIN_SET); break;
		 		case CMD_OPEN_SOL8:
		 		 	HAL_GPIO_WritePin(valve8_GPIO_Port, valve8_Pin, GPIO_PIN_SET); break;
		 		case CMD_OPEN_SOL9:
		 		    HAL_GPIO_WritePin(valve9_GPIO_Port, valve9_Pin, GPIO_PIN_SET); break;
		 		case CMD_OPEN_SOL10:
		 		    HAL_GPIO_WritePin(valve10_GPIO_Port, valve10_Pin, GPIO_PIN_SET); break;
		 		case CMD_OPEN_SOL11:
		 		    HAL_GPIO_WritePin(valve11_GPIO_Port, valve11_Pin, GPIO_PIN_SET); break;
		 		case CMD_OPEN_SOL12:
		 		    HAL_GPIO_WritePin(valve12_GPIO_Port, valve12_Pin, GPIO_PIN_SET); break;
		 		case CMD_OPEN_SOL13:
		 		    HAL_GPIO_WritePin(valve13_GPIO_Port, valve13_Pin, GPIO_PIN_SET); break;
		 		case CMD_OPEN_SOL14:
		 		    HAL_GPIO_WritePin(valve14_GPIO_Port, valve14_Pin, GPIO_PIN_SET); break;
		 		case CMD_OPEN_SOL15:
		 		    HAL_GPIO_WritePin(valve15_GPIO_Port, valve15_Pin, GPIO_PIN_SET); break;
		 		case CMD_OPEN_SOL16:
		 		    HAL_GPIO_WritePin(valve16_GPIO_Port, valve16_Pin, GPIO_PIN_SET); break;
		 		case CMD_OPEN_SOL17:
		 		    HAL_GPIO_WritePin(valve17_GPIO_Port, valve17_Pin, GPIO_PIN_SET); break;
		 		case CMD_OPEN_SOL18:
		 		    HAL_GPIO_WritePin(valve18_GPIO_Port, valve18_Pin, GPIO_PIN_SET); break;

// Close Solenoid Valve Commands

		 		case CMD_CLOSE_SOL1:
		 			HAL_GPIO_WritePin(valve1_GPIO_Port, valve1_Pin, GPIO_PIN_RESET); break;
		 		case CMD_CLOSE_SOL2:
		 			HAL_GPIO_WritePin(valve2_GPIO_Port, valve2_Pin, GPIO_PIN_RESET); break;
		 		case CMD_CLOSE_SOL3:
		 		 	HAL_GPIO_WritePin(valve3_GPIO_Port, valve3_Pin, GPIO_PIN_RESET); break;
		 		case CMD_CLOSE_SOL4: // IEP VALVE (PWM)
		 		 	HAL_GPIO_WritePin(TIM8_CH1_VALVE4_GPIO_Port, TIM8_CH1_VALVE4_Pin, GPIO_PIN_RESET); break;
		 		case CMD_CLOSE_SOL5:
		 		 	HAL_GPIO_WritePin(valve5_GPIO_Port, valve5_Pin, GPIO_PIN_RESET); break;
		 		case CMD_CLOSE_SOL6: // IEP VALVE (PWM)
		 		 	HAL_GPIO_WritePin(TIM3_CH3_VALVE6_GPIO_Port, TIM3_CH3_VALVE6_Pin, GPIO_PIN_RESET); break;
		 		case CMD_CLOSE_SOL7:
		 		    HAL_GPIO_WritePin(valve7_GPIO_Port, valve7_Pin, GPIO_PIN_RESET); break;
		 		case CMD_CLOSE_SOL8:
		 		 	HAL_GPIO_WritePin(valve8_GPIO_Port, valve8_Pin, GPIO_PIN_RESET); break;
		 		case CMD_CLOSE_SOL9:
		 		    HAL_GPIO_WritePin(valve9_GPIO_Port, valve9_Pin, GPIO_PIN_RESET); break;
		 		case CMD_CLOSE_SOL10:
		 		    HAL_GPIO_WritePin(valve10_GPIO_Port, valve10_Pin, GPIO_PIN_RESET); break;
		 		case CMD_CLOSE_SOL11:
		 		    HAL_GPIO_WritePin(valve11_GPIO_Port, valve11_Pin, GPIO_PIN_RESET); break;
		 		case CMD_CLOSE_SOL12:
		 		 	HAL_GPIO_WritePin(valve12_GPIO_Port, valve12_Pin, GPIO_PIN_RESET); break;
		 		case CMD_CLOSE_SOL13:
		 		    HAL_GPIO_WritePin(valve13_GPIO_Port, valve13_Pin, GPIO_PIN_RESET); break;
		 		case CMD_CLOSE_SOL14:
		 		    HAL_GPIO_WritePin(valve14_GPIO_Port, valve14_Pin, GPIO_PIN_RESET); break;
		 		case CMD_CLOSE_SOL15:
		 		 	HAL_GPIO_WritePin(valve15_GPIO_Port, valve15_Pin, GPIO_PIN_RESET); break;
		 		case CMD_CLOSE_SOL16:
		 		    HAL_GPIO_WritePin(valve16_GPIO_Port, valve16_Pin, GPIO_PIN_RESET); break;
		 		case CMD_CLOSE_SOL17:
		 		 	HAL_GPIO_WritePin(valve17_GPIO_Port, valve17_Pin, GPIO_PIN_RESET); break;
		 		case CMD_CLOSE_SOL18:
		 	        HAL_GPIO_WritePin(valve18_GPIO_Port, valve18_Pin, GPIO_PIN_RESET); break;

          		 	    	// until we get two AD7124's wqrking at once.

// read device id's

		 		case CMD_READ_ID_PT:
		 		    device_id = ad7124_read_device_id(PRESSURE);
		 			Serial_Printf("AD7124 Device ID: %ld \n", device_id);
		 			if(device_id == 20 || device_id == 23){ // device id for dataversion E || https://ez.analog.com/data_converters/precision_adcs/f/q-a/574494/ad7124-8-device-id-question
		 				 printf("|| SUCCESS \n");
		 				 HAL_GPIO_WritePin(LED_PIN_GREEN_GPIO_Port, LED_PIN_GREEN_Pin, GPIO_PIN_SET);
//		 				 read_status_register(); potentially integrate for error checking / sending status back
		 			}
					break;
		 		case CMD_READ_ID_V:
		 			 device_id = ad7124_read_device_id(VOLTAGE);
		 			 Serial_Printf("AD7124 Device ID: %ld \n", device_id);
		 			 if(device_id == 20 || device_id == 23){ // device id for dataversion E || https://ez.analog.com/data_converters/precision_adcs/f/q-a/574494/ad7124-8-device-id-question
		 				printf("|| SUCCESS \n");
		 				 HAL_GPIO_WritePin(LED_PIN_GREEN_GPIO_Port, LED_PIN_GREEN_Pin, GPIO_PIN_SET);
		 		//		 				 read_status_register();
		 			 }
		 			 else{
		 				printf("Fail Read Voltage AD7124 \n");
		 			 }
					 break;
		 		case CMD_READ_ID_FDC:
		 		 	  if(isConnected()==0){
		 		 		printf("FDC NOMINAL \n");
			 			HAL_GPIO_WritePin(LED_PIN_GREEN_GPIO_Port, LED_PIN_GREEN_Pin, GPIO_PIN_SET);

		 		 	  }
		 		 	  else{
		 		 		printf("FDC FAIL IS NOT CONNECTED \n");
		 		 	  }


		 		 	  device_id = FDC2214_get_device_id();
			 		  Serial_Printf("FDC2214 Device ID: %ld \n", device_id);
					  break;

// READ PC104 ADC CHANNELS

				case CMD_READ_12VA_VB:
					value = display_channel_sample(CH_12VA_VB,VOLTAGE);
					Serial_Printf("PC104 Voltage Reading 12VA_VB: %d \r\n", value);

					// Resistor Values = |------ 510K ----- 100K ------|>

					// need to input conversions here.
					break;

				case CMD_READ_12VA_VA:
					value = display_channel_sample(CH_12VA_VA,VOLTAGE);
					Serial_Printf("PC104 Voltage Reading 12VA_VA: %d \r\n", value);
					break;
				case CMD_READ_3V3_VB:
					value = display_channel_sample(CH_3V3_VB,VOLTAGE);
					Serial_Printf("PC104 Voltage Reading 3V3_VB: %d \r\n", value);
					break;
				case CMD_READ_3V3_VA:
					value = display_channel_sample(CH_3V3_VA,VOLTAGE);
					Serial_Printf("PC104 Voltage Reading 3V3_VA: %d \r\n", value);
					break;
				case CMD_READ_VBAT_VA:
					value = display_channel_sample(CH_VBAT_VA,VOLTAGE);
					Serial_Printf("PC104 Voltage Reading VBAT_VA: %d \r\n", value);
					break;
				case CMD_READ_VBAT_VB:
					value = display_channel_sample(CH_VBAT_VB,VOLTAGE);
					Serial_Printf("PC104 Voltage Reading VBAT_VB: %d \r\n", value);
					break;
				case CMD_READ_12VB_VA:
					value = display_channel_sample(CH_VBAT_VA,VOLTAGE);
					Serial_Printf("PC104 Voltage Reading 12VB_VA: %d \r\n", value);
					break;
				case CMD_READ_12VB_VB:
					value = display_channel_sample(CH_VBAT_VB,VOLTAGE);
					Serial_Printf("PC104 Voltage Reading 12VB_VB: %d \r\n", value);
					break;

// Read PC104 Currents
				case CMD_READ_12VA_VB_CURRENT:
					value = ad7124_read_channel_current_pc104(CH_12VA_VB);
					Serial_Printf("PC104 Current Reading 12VA_VB: %d \r\n", value);
					break;
				case CMD_READ_12VA_VA_CURRENT:
					value = ad7124_read_channel_current_pc104(CH_12VA_VA);
					Serial_Printf("PC104 Current Reading 12VA_VA: %d \r\n", value);
					break;
				case CMD_READ_3V3_VB_CURRENT:
					value = ad7124_read_channel_current_pc104(CH_3V3_VB);
					Serial_Printf("PC104 Current Reading 3V3_VB : %d \r\n", value);
					break;
				case CMD_READ_3V3_VA_CURRENT:
					value = ad7124_read_channel_current_pc104(CH_3V3_VA);
					Serial_Printf("PC104 Current Reading 3V3_VA : %d \r\n", value);
					break;
				case CMD_READ_VBAT_VA_CURRENT:
					value = ad7124_read_channel_current_pc104(CH_VBAT_VA);
					Serial_Printf("PC104 Current Reading VBAT_VA : %d \r\n", value);
					break;
				case CMD_READ_VBAT_VB_CURRENT:
					value = ad7124_read_channel_current_pc104(CH_VBAT_VB);
					Serial_Printf("PC104 Current Reading VBAT_VB : %d \r\n", value);
					break;
				case CMD_READ_12VB_VA_CURRENT:
					value = ad7124_read_channel_current_pc104(CH_12VB_VA);
					Serial_Printf("PC104 Current Reading 12VB_VA: %d \r\n",  value);
					break;
				case CMD_READ_12VB_VB_CURRENT:
					value = ad7124_read_channel_current_pc104(CH_12VB_VB);
					Serial_Printf("PC104 Current Reading 12VB_VB: %d \r\n", value);
					break;
// Read Pressure Sensors

	 			case CMD_READ_PT1:
	 				value =  0; // ad7124_read_pressure(CH_P0);
	 				// will need to convert the voltage value to a current / temp reading function eventually in ad7124.h
	 				Serial_Printf("Pressure Reading PT 1: %d \r\n", value);
					break;
	 			case CMD_READ_PT2:
	 				value = 0; // ad7124_read_pressure(CH_P1);
	 				Serial_Printf("Pressure Reading PT 2: %d \r\n", value);
					break;
	 			case CMD_READ_PT3:
	 				value = 0; // ad7124_read_pressure(CH_P2);
	 				Serial_Printf("Pressure Reading PT 3: %d \r\n", value);
					break;
	 			case CMD_READ_PT4:
	 				value = 0; // ad7124_read_pressure(CH_P3);
	 				Serial_Printf("Pressure Reading PT 4: %d \r\n", value);
					break;
	 			case CMD_READ_PT5:
	 				value = 0; // ad7124_read_pressure(CH_P4);
	 				Serial_Printf("Pressure Reading PT 5: %d \r\n", value);
					break;
	 			case CMD_READ_PT6:
	 				value = 0; // ad7124_read_pressure(CH_P5);
	 				Serial_Printf("Pressure Reading PT 6: %d \r\n", value);
					break;
	 			case CMD_READ_PT7:
	 				value = 0; // ad7124_read_pressure(CH_P6);
	 				Serial_Printf("Pressure Reading PT 7: %d \r\n", value);
					break;
	 			case CMD_READ_PT8:
	 				value = 0; // ad7124_read_pressure(CH_P7);
	 				Serial_Printf("Pressure Reading PT 8: %d \r\n", value);
					break;


// Read Valve States
	 			case CMD_READ_VALVE_STATE1:
	 				pinState = HAL_GPIO_ReadPin(valve1_GPIO_Port, valve1_Pin);
	 				if (pinState == GPIO_PIN_SET){
		 				Serial_Print("Valve ON \n");

	 				}
	 				else{
		 				Serial_Print("Valve OFF \n");
	 				}
					break;
	 			case CMD_READ_VALVE_STATE2:
	 				 pinState = HAL_GPIO_ReadPin(valve2_GPIO_Port, valve2_Pin);
	 				 if (pinState == GPIO_PIN_SET){
	 					Serial_Print("Valve ON \n");
	 				 }
	 				 else{
	 					Serial_Print("Valve OFF \n");
	 				 }
					 break;

	 			case CMD_READ_VALVE_STATE3:
	 				pinState = HAL_GPIO_ReadPin(valve3_GPIO_Port, valve3_Pin);
	 				if (pinState == GPIO_PIN_SET){
		 				Serial_Print("Valve ON \n");

	 				}
	 				else{
		 				Serial_Print("Valve OFF \n");
	 				}
					break;
	 			case CMD_READ_VALVE_STATE4:
	 				 pinState = HAL_GPIO_ReadPin(TIM8_CH1_VALVE4_GPIO_Port, TIM8_CH1_VALVE4_Pin);
	 				 if (pinState == GPIO_PIN_SET){
	 					Serial_Print("Valve ON \n");
	 				 }
	 				 else{
	 					Serial_Print("Valve OFF \n");
	 				 }
					 break;

	 			case CMD_READ_VALVE_STATE5:
	 				pinState = HAL_GPIO_ReadPin(valve5_GPIO_Port, valve5_Pin);
	 				if (pinState == GPIO_PIN_SET){
		 				Serial_Print("Valve ON \n");

	 				}
	 				else{
		 				Serial_Print("Valve OFF \n");
	 				}
					break;
	 			case CMD_READ_VALVE_STATE6:
	 				pinState = HAL_GPIO_ReadPin(TIM3_CH3_VALVE6_GPIO_Port, TIM3_CH3_VALVE6_Pin);
	 				if (pinState == GPIO_PIN_SET){
	 					Serial_Print("Valve ON \n");
	 				}
	 				else{
	 					Serial_Print("Valve OFF \n");
	 				}
					break;
	 			case CMD_READ_VALVE_STATE7:
	 				pinState = HAL_GPIO_ReadPin(valve7_GPIO_Port, valve7_Pin);
	 				if (pinState == GPIO_PIN_SET){
		 				Serial_Print("Valve ON \n");

	 				}
	 				else{
		 				Serial_Print("Valve OFF \n");
	 				}
					break;
	 			case CMD_READ_VALVE_STATE8:
	 				pinState = HAL_GPIO_ReadPin(valve8_GPIO_Port, valve8_Pin);
	 				if (pinState == GPIO_PIN_SET){
	 					Serial_Print("Valve ON \n");
	 				}
	 				else{
	 					Serial_Print("Valve OFF \n");
	 				}
					break;
	 			case CMD_READ_VALVE_STATE9:
	 				pinState = HAL_GPIO_ReadPin(valve9_GPIO_Port, valve9_Pin);
	 				if (pinState == GPIO_PIN_SET){
		 				Serial_Print("Valve ON \n");

	 				}
	 				else{
		 				Serial_Print("Valve OFF \n");
	 				}
					break;
	 			case CMD_READ_VALVE_STATE10:
	 				pinState = HAL_GPIO_ReadPin(valve10_GPIO_Port, valve10_Pin);
	 				if (pinState == GPIO_PIN_SET){
	 					Serial_Print("Valve ON \n");
	 				}
	 				else{
	 					Serial_Print("Valve OFF \n");
	 				}
					break;
	 			case CMD_READ_VALVE_STATE11:
	 				pinState = HAL_GPIO_ReadPin(valve11_GPIO_Port, valve11_Pin);
	 				if (pinState == GPIO_PIN_SET){
		 				Serial_Print("Valve ON \n");

	 				}
	 				else{
		 				Serial_Print("Valve OFF \n");
	 				}
					break;
	 			case CMD_READ_VALVE_STATE12:
	 				pinState = HAL_GPIO_ReadPin(valve12_GPIO_Port, valve12_Pin);
	 				if (pinState == GPIO_PIN_SET){
	 					Serial_Print("Valve ON \n");
	 				}
	 				else{
	 					Serial_Print("Valve OFF \n");
	 				}
					break;
	 			case CMD_READ_VALVE_STATE13:
	 				pinState = HAL_GPIO_ReadPin(valve13_GPIO_Port, valve13_Pin);
	 				if (pinState == GPIO_PIN_SET){
		 				Serial_Print("Valve ON \n");

	 				}
	 				else{
		 				Serial_Print("Valve OFF \n");
	 				}
					break;
	 			case CMD_READ_VALVE_STATE14:
	 				pinState = HAL_GPIO_ReadPin(valve14_GPIO_Port, valve14_Pin);
	 				if (pinState == GPIO_PIN_SET){
	 					Serial_Print("Valve ON \n");
	 				}
	 				else{
	 					Serial_Print("Valve OFF \n");
	 				}
					break;
	 			case CMD_READ_VALVE_STATE15:
	 				pinState = HAL_GPIO_ReadPin(valve15_GPIO_Port, valve15_Pin);
	 				if (pinState == GPIO_PIN_SET){
		 				Serial_Print("Valve ON \n");

	 				}
	 				else{
		 				Serial_Print("Valve OFF \n");
	 				}
					break;
	 			case CMD_READ_VALVE_STATE16:
	 				pinState = HAL_GPIO_ReadPin(valve16_GPIO_Port, valve16_Pin);
	 				if (pinState == GPIO_PIN_SET){
	 					Serial_Print("Valve ON \n");
	 				}
	 				else{
	 					Serial_Print("Valve OFF \n");
	 				}
					break;
	 			case CMD_READ_VALVE_STATE17:
	 				pinState = HAL_GPIO_ReadPin(valve17_GPIO_Port, valve17_Pin);
	 				if (pinState == GPIO_PIN_SET){
		 				Serial_Print("Valve ON \n");

	 				}
	 				else{
		 				Serial_Print("Valve OFF \n");
	 				}
					break;
	 			case CMD_READ_VALVE_STATE18:
	 				 pinState = HAL_GPIO_ReadPin(valve18_GPIO_Port, valve18_Pin);
	 				 if (pinState == GPIO_PIN_SET){
	 					Serial_Print("Valve ON \n");
	 				 }
	 				 else{
	 					Serial_Print("Valve OFF \n");
	 				 }
					 break;

// Read MAX31856 Temperatures

		 	    case CMD_READ_TC1:
		 	    	temperature = max31856_read_TC_temp(&max31856T1); // compensates already for cold junction reading
	 				max31856_read_fault(&max31856T1);
		 		    if (max31856T1.sr.val) {
						Serial_Printf("TC Read Fail ERROR TC1 #: %d \n", max31856T1.sr.val);
		 		   	   	print_errors(max31856T1.sr.val); // test functionality of error discerning

		 		    }
		 		    else{
			 		    Serial_Printf("Temperature Reading TC1: %f \r\n", temperature);
		 		    }
					break;

		 	    case CMD_READ_TC2:
		 	    	temperature = max31856_read_TC_temp(&max31856T2);
		 	    	max31856_read_fault(&max31856T2);
		 		    if (max31856T2.sr.val) {
						Serial_Printf("TC Read Fail ERROR TC2 #: %d \n", max31856T2.sr.val);
		 		   	   	print_errors(max31856T2.sr.val);

		 		    }
		 		    else{
			 		    Serial_Printf("Temperature Reading TC2: %f \r\n", temperature);
		 		    }
					break;
		 	    case CMD_READ_TC3:
		 	    	temperature = max31856_read_TC_temp(&max31856T3);
					Serial_Printf("Temperature Reading TC3: %f \r\n", temperature);
		 	    	max31856_read_fault(&max31856T3); // it willk read a fault because no k-type thermo connected .
		 		    // if (max31856T3.sr.val) {
					// 	Serial_Printf("TC Read Fail ERROR TC3 #: %d \n", max31856T3.sr.val);
		 		   	//    	print_errors(max31856T3.sr.val);

		 		    // }
		 		    // else{
			 		//     Serial_Printf("Temperature Reading TC3: %f \r\n", temperature);
		 		    // }
					break;
		 	    case CMD_READ_TC4:
		 	    	temperature = max31856_read_TC_temp(&max31856T4);
		 	    	max31856_read_fault(&max31856T4);
		 		    if (max31856T4.sr.val) {
						Serial_Printf("TC Read Fail ERROR TC4 #: %d \n", max31856T4.sr.val);
		 		   	   	print_errors(max31856T4.sr.val);

		 		    }
		 		    else{
			 		    Serial_Printf("Temperature Reading TC4: %f \r\n", temperature);
		 		    }
					break;
		 	    case CMD_READ_TC5:
		 	    	temperature = max31856_read_TC_temp(&max31856T5);
		 	    	max31856_read_fault(&max31856T5);
		 		    if (max31856T5.sr.val) {
						Serial_Printf("TC Read Fail ERROR TC5 #: %d \n", max31856T5.sr.val);
		 		   	   	print_errors(max31856T5.sr.val); // need to test during hardware test

		 		    }
		 		    else{
			 		    Serial_Printf("Temperature Reading TC5: %f \r\n", temperature);
		 		    }
					break;


// Read MAX31856 Cold-Junction Temperatures || reading cold junction temps (MAX31856 chip does NOT have a device id thus this is the next best way to see if the chip is responding.)


		 	    case CMD_READ_TC1_CJ:
		 		   temperature = max31856_read_CJ_temp(&max31856T1);
<<<<<<< HEAD
		 		   // max31856_read_fault(&max31856T1);
			 	   Serial_Printf("Cold Junction Temperature Reading TC1: %f \r\n", temperature);
				   break; 
=======
		 		   max31856_read_fault(&max31856T1);
		 		   if (max31856T1.sr.val) {
					   Serial_Printf("TC Read Fail ERROR TC1 #: %d \n", max31856T1.sr.val);
		 		   }
		 		   else{
			 		   Serial_Printf("Cold Junction Temperature Reading TC1: %f \r\n", temperature);
		 		   }
				   break;
>>>>>>> 5ae7089c1da40de279deba5f5fa63f725172f515
		 	    case CMD_READ_TC2_CJ:
			 	   temperature = max31856_read_CJ_temp(&max31856T2);
			 	//    max31856_read_fault(&max31856T2);
			 	//    if (max31856T2.sr.val) {
				// 	   Serial_Printf("TC Read Fail ERROR TC2 #: %d \n", max31856T2.sr.val);
			 	//    }
			 	//    else{
			 	   Serial_Printf("Cold Junction Temperature Reading TC2: %f \r\n", temperature);

<<<<<<< HEAD
	
			 	//    }
				   break; 
=======

			 	   }
				   break;
>>>>>>> 5ae7089c1da40de279deba5f5fa63f725172f515
		 	    case CMD_READ_TC3_CJ:
				   temperature = max31856_read_CJ_temp(&max31856T3);
				   // max31856_read_fault(&max31856T3);
				//    if (max31856T3.sr.val) {
				// 	   Serial_Printf("TC Read Fail ERROR TC3 #: %d \n", max31856T3.sr.val);
				//    }
				//    else{
			 	// 	   Serial_Printf("Cold Junction Temperature Reading TC3: %f \r\n", temperature);

<<<<<<< HEAD
				//    }
				   Serial_Printf("Cold Junction Temperature Reading TC3: %f \r\n", temperature);
				   break; 
		 	    case CMD_READ_TC4_CJ:
				   temperature = max31856_read_CJ_temp(&max31856T4);
				//    max31856_read_fault(&max31856T4);
				//    if (max31856T4.sr.val) {
				// 	   Serial_Printf("TC Read Fail ERROR TC4 #: %d \n", max31856T4.sr.val);
				//    }
				//    else{
			 	// 	   Serial_Printf("Cold Junction Temperature Reading TC4: %f \r\n", temperature);
				//    }
				   Serial_Printf("Cold Junction Temperature Reading TC4: %f \r\n", temperature);
				   break; 
		 	    case CMD_READ_TC5_CJ:
				   temperature = max31856_read_CJ_temp(&max31856T5);
				//    max31856_read_fault(&max31856T5);
			    //    if (max31856T5.sr.val) {
				// 	   Serial_Printf("TC Read Fail ERROR TC5 #: %d \n", max31856T5.sr.val);
				//    }
			    //    else{
			    //  	   Serial_Printf("Cold Junction Temperature Reading TC5: %f \r\n", temperature);
			    //    }
				   Serial_Printf("Cold Junction Temperature Reading TC5: %f \r\n", temperature);
				   break; 
=======
				   }
				   break;
		 	    case CMD_READ_TC4_CJ:
				   temperature = max31856_read_CJ_temp(&max31856T4);
				   max31856_read_fault(&max31856T4);
				   if (max31856T4.sr.val) {
					   Serial_Printf("TC Read Fail ERROR TC4 #: %d \n", max31856T4.sr.val);
				   }
				   else{
			 		   Serial_Printf("Cold Junction Temperature Reading TC4: %f \r\n", temperature);
				   }
				   break;
		 	    case CMD_READ_TC5_CJ:
				   temperature = max31856_read_CJ_temp(&max31856T5);
				   max31856_read_fault(&max31856T5);
			       if (max31856T5.sr.val) {
					   Serial_Printf("TC Read Fail ERROR TC5 #: %d \n", max31856T5.sr.val);
				   }
			       else{
			     	   Serial_Printf("Cold Junction Temperature Reading TC5: %f \r\n", temperature);
			       }
				   break;
>>>>>>> 5ae7089c1da40de279deba5f5fa63f725172f515

// FDC2214 Reads
		 	    case READ_CAPACITANCE_A1:
		 	    	// test both when testing, should return the same value.
		 	 		if(FDC2214_is_data_ready(FDC2214_CH0)){
		 	 	 		 float c_pf = FDC2214_readCapacitancePf(FDC2214_CH0, FDC2214_L_HENRY);
		 	 	 		 Serial_Printf("Capacitance (pF): %f \n", c_pf);
		 	 		}
					break;
//					value = FDC2214_read_differential_capacitance(1);
//	 				Serial_Printf("Differential Capacitance Reading FDC2214 A1: %f \r\n", capacitance);
		 	    case READ_CAPACITANCE_A2:
					value = FDC2214_read_differential_capacitance(2);
	 				Serial_Printf("Differential Capacitance Reading FDC2214 A2: %f \r\n", value);
					break;
	 			case READ_PROPELLANT_LEVEL_A1:
	 				value = FDC2214_read_accumulator_height(1);
	 				Serial_Printf("Catalyst Height Reading FDC2214 A1: %d \r\n", value);
					break;
	 			case READ_PROPELLANT_LEVEL_A2:
	 				value = FDC2214_read_accumulator_height(2);
	 				Serial_Printf("Catalyst Height Reading FDC2214 A2: %d \r\n", value);
					break;

// Miscellaneous Commands

		 		case CMD_TOGGLE_LED_RED:
		 		     HAL_GPIO_TogglePin(LED_PIN_RED_GPIO_Port, LED_PIN_RED_Pin); break; 
		 		case CMD_TOGGLE_LED_GREEN:
		 		     HAL_GPIO_TogglePin(LED_PIN_GREEN_GPIO_Port, LED_PIN_GREEN_Pin); break; 
		 		case CMD_TOGGLE_LED_AMBER:
		 		     HAL_GPIO_TogglePin(LED_PIN_AMBER_GPIO_Port, LED_PIN_AMBER_Pin); break; 


// Events

		 		case HEAT_CATALYST:
		 			heat_catalyst();
					break;
		 		case CMD_MANUAL_HEATER_TURN_ON:
		 		    HAL_GPIO_WritePin(heater_en_GPIO_Port, heater_en_Pin, GPIO_PIN_SET);
					break;
		 		case CMD_MANUAL_HEATER_TURN_OFF:
		 		    HAL_GPIO_WritePin(heater_en_GPIO_Port, heater_en_Pin, GPIO_PIN_RESET);
					break;

				case REGULATE_PRESSURE_INPUT_VALUE: // valve 4
					duty_cycle = frame.arg; // obtain duty cycle argument
					HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_3); // start pwm on timer 3 channel 3 for valve 4
					__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_3, duty_cycle); // set the duty cycle for valve 4
					break;

				case REGULATE_PRESSURE_2_INPUT_VALUE: // valve 6
					duty_cycle = frame.arg; // obtain duty cycle argument
					HAL_TIM_PWM_Start(&htim8, TIM_CHANNEL_1);
					__HAL_TIM_SET_COMPARE(&htim8, TIM_CHANNEL_1, duty_cycle); // set the duty cycle for valve 6
					break;
					// let's see if it works!

				case REGULATE_PRESSURE_1_STOP: // valve 4
					HAL_TIM_PWM_Stop(&htim3, TIM_CHANNEL_3);
					break;
				case REGULATE_PRESSURE_2_STOP: // valve 6
					HAL_TIM_PWM_Stop(&htim8, TIM_CHANNEL_1);
					break;
				default:
					break;

	
					// reset the received command so it does not execute more than once.	

		 	}
//	 	 	HAL_GPIO_TogglePin(LED_PIN_GREEN_GPIO_Port, LED_PIN_GREEN_Pin);

			  // reset received command so it does not execute more than once.
			// test to see if this works 

		 	//		 		   // we may need to add if there's ever an error...
		 	//		 		   int len = snprintf(uart_buffer, sizeof(uart_buffer), "Cold Junction Temperature Reading TC1: %f\r\n", temperature);
		 	//		 	 	   HAL_UART_Transmit(&huart3, (uint8_t *)uart_buffer, len, 100);


	  }










    osDelay(1);
  }
  /* USER CODE END StartTask04 */
}

/* USER CODE BEGIN Header_StartTask05 */
/**
* @brief Function implementing the Task_UART_TX thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartTask05 */
void StartTask05(void *argument)
{
  /* USER CODE BEGIN StartTask05 */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);

    // TX UART Task (waits for queue to get pushed to)


    // SEND MESSAGE OVER UART



    //




  }
  /* USER CODE END StartTask05 */
}

/* USER CODE BEGIN Header_StartTask06 */
/**
* @brief Function implementing the Task_Data thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartTask06 */
void StartTask06(void *argument)
{
  /* USER CODE BEGIN StartTask06 */
  /* Infinite loop */
  for(;;)
  {
	// task data acquistion 

	// take data mutex 


	
	// poll from sensors and store in global data_log attached to Payload_System 


	// take/release spi/i2c mutex





	// push data_log onto the queue for UART_TX to send it over UART to the PC104 



	// release data mutex





    osDelay(1000); // poll data every second depends how much we want 
  }
  /* USER CODE END StartTask06 */
}

/* USER CODE BEGIN Header_StartTask07 */


/**
* @brief Function implementing the Task_FSM thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartTask07 */
void StartTask07(void *argument)
{
  /* USER CODE BEGIN StartTask07 */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);


    // fsm task.


    // create fsm_tick struct and fetch data





    // execute fsm_tick function (returns the state)





    // commit fsm state and change Payload_Systems->FSM_State






  }
  /* USER CODE END StartTask07 */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

