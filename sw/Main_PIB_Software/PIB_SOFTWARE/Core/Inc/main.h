/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32l4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define valve9_Pin GPIO_PIN_2
#define valve9_GPIO_Port GPIOE
#define valve10_Pin GPIO_PIN_3
#define valve10_GPIO_Port GPIOE
#define valve11_Pin GPIO_PIN_4
#define valve11_GPIO_Port GPIOE
#define valve12_Pin GPIO_PIN_5
#define valve12_GPIO_Port GPIOE
#define valve13_Pin GPIO_PIN_6
#define valve13_GPIO_Port GPIOE
#define valve14_Pin GPIO_PIN_1
#define valve14_GPIO_Port GPIOA
#define valve15_Pin GPIO_PIN_2
#define valve15_GPIO_Port GPIOA
#define T1_CS_Pin GPIO_PIN_10
#define T1_CS_GPIO_Port GPIOE
#define valve_1_Pin GPIO_PIN_12
#define valve_1_GPIO_Port GPIOB
#define valve2_Pin GPIO_PIN_14
#define valve2_GPIO_Port GPIOD
#define valve3_Pin GPIO_PIN_15
#define valve3_GPIO_Port GPIOD
#define valve6_Pin GPIO_PIN_6
#define valve6_GPIO_Port GPIOC
#define valve5_Pin GPIO_PIN_7
#define valve5_GPIO_Port GPIOC
#define valve7_Pin GPIO_PIN_8
#define valve7_GPIO_Port GPIOC
#define valve8_Pin GPIO_PIN_9
#define valve8_GPIO_Port GPIOC
#define valve4_Pin GPIO_PIN_8
#define valve4_GPIO_Port GPIOA
#define valve18_Pin GPIO_PIN_10
#define valve18_GPIO_Port GPIOA
#define valve16_Pin GPIO_PIN_11
#define valve16_GPIO_Port GPIOA
#define valve17_Pin GPIO_PIN_12
#define valve17_GPIO_Port GPIOA
#define LED_PIN_Pin GPIO_PIN_0
#define LED_PIN_GPIO_Port GPIOD

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
