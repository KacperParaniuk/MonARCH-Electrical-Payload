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

#include <cmsis_os.h>
#include <cmsis_os2.h>
#include <main.h>
#include <stdio.h>
#include <stm32l4xx_hal.h>
#include <stm32l4xx_hal_gpio.h>
#include <sys/_stdint.h>
#include <uart_handler.h>
#include <uart_protocol.h>


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
/* USER CODE BEGIN Variables */

extern uint8_t rx_cmd[];
extern char uart_buffer[];

float temperature;


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
  .stack_size = 500 * 4,
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

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

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
	HAL_GPIO_TogglePin(LED_PIN_GREEN_GPIO_Port, LED_PIN_GREEN_Pin);
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

		// decipher the rx_cmd - safety or normal command
		if(cmd_is_safety(rx_cmd[0])){
			// add cmds to queue so that either safety_cmd can execute or normal in task_experiment
			osMessageQueuePut(q_safety_cmdsHandle, &rx_cmd[0], 0, 0);
		}
		else{

			osMessageQueuePut(q_normal_cmdsHandle, &rx_cmd[0], 0, 0);
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

	  if(osMessageQueueGet(q_safety_cmdsHandle, &rx_cmd[0], NULL, osWaitForever)==osOK){

		  printf("SAFETY COMMAND");





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
  for(;;)
  {

	  // experiment / normal cmd task

	  // block until cmd gets pushed onto queue.

	  if(osMessageQueueGet(q_normal_cmdsHandle, &rx_cmd[0], NULL, osWaitForever)==osOK){

		  printf("Normal CMD Received");

		  // fsm integration here?
		 	switch(rx_cmd[0]){

		 		// decode command and execute

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
		 		 	HAL_GPIO_WritePin(TIM3_CH3_VALVE6_GPIO_Port, TIM3_CH3_VALVE6_Pin, GPIO_PIN_SET);

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

		 	    	// until we get two AD7124's wqrking at once.
//		 		   temperature = max31856_read_CJ_temp(&max31856T1);
//
//		 		   // we may need to add if there's ever an error...
//		 		   int len = snprintf(uart_buffer, sizeof(uart_buffer), "Cold Junction Temperature Reading TC1: %f\r\n", temperature);
//		 	 	   HAL_UART_Transmit(&huart3, (uint8_t *)uart_buffer, len, 100);



		 		rx_cmd[0]=0;

		 		break;
		 	}










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
    osDelay(1);
  }
  /* USER CODE END StartTask06 */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

