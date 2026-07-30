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

#include "uart_handler.h"

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

