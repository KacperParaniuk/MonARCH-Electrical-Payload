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

extern SPI_HandleTypeDef hspi1;
extern SPI_HandleTypeDef hspi2;

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
#define T4_EN_Pin GPIO_PIN_2
#define T4_EN_GPIO_Port GPIOE
#define T2_EN_Pin GPIO_PIN_3
#define T2_EN_GPIO_Port GPIOE
#define PT_EN_Pin GPIO_PIN_4
#define PT_EN_GPIO_Port GPIOE
#define TIM3_CH3_VALVE6_Pin GPIO_PIN_5
#define TIM3_CH3_VALVE6_GPIO_Port GPIOE
#define POW12_EN_Pin GPIO_PIN_0
#define POW12_EN_GPIO_Port GPIOH
#define UART4_TX_PPU_Pin GPIO_PIN_0
#define UART4_TX_PPU_GPIO_Port GPIOA
#define UART4_RX_PPU_Pin GPIO_PIN_1
#define UART4_RX_PPU_GPIO_Port GPIOA
#define ADC_EN_Pin GPIO_PIN_4
#define ADC_EN_GPIO_Port GPIOA
#define SPI1_SCK_BAT_Pin GPIO_PIN_5
#define SPI1_SCK_BAT_GPIO_Port GPIOA
#define SPI1_MISO_BAT_Pin GPIO_PIN_6
#define SPI1_MISO_BAT_GPIO_Port GPIOA
#define SPI1_MOSI_BAT_Pin GPIO_PIN_7
#define SPI1_MOSI_BAT_GPIO_Port GPIOA
#define USART3_TX_OBC_Pin GPIO_PIN_4
#define USART3_TX_OBC_GPIO_Port GPIOC
#define USART3_RX_OBC_Pin GPIO_PIN_5
#define USART3_RX_OBC_GPIO_Port GPIOC
#define LED_PIN_AMBER_Pin GPIO_PIN_13
#define LED_PIN_AMBER_GPIO_Port GPIOE
#define LED_PIN_GREEN_Pin GPIO_PIN_14
#define LED_PIN_GREEN_GPIO_Port GPIOE
#define LED_PIN_RED_Pin GPIO_PIN_15
#define LED_PIN_RED_GPIO_Port GPIOE
#define I2C4_SCL_BREAKOUT_Pin GPIO_PIN_10
#define I2C4_SCL_BREAKOUT_GPIO_Port GPIOB
#define I2C4_SDA_BREAKOUT_Pin GPIO_PIN_11
#define I2C4_SDA_BREAKOUT_GPIO_Port GPIOB
#define valve1_Pin GPIO_PIN_12
#define valve1_GPIO_Port GPIOB
#define valve2_Pin GPIO_PIN_13
#define valve2_GPIO_Port GPIOB
#define valve3_Pin GPIO_PIN_14
#define valve3_GPIO_Port GPIOB
#define valve5_Pin GPIO_PIN_15
#define valve5_GPIO_Port GPIOB
#define valve7_Pin GPIO_PIN_8
#define valve7_GPIO_Port GPIOD
#define valve8_Pin GPIO_PIN_9
#define valve8_GPIO_Port GPIOD
#define TIM8_CH1_VALVE4_Pin GPIO_PIN_6
#define TIM8_CH1_VALVE4_GPIO_Port GPIOC
#define valve9_Pin GPIO_PIN_7
#define valve9_GPIO_Port GPIOC
#define valve10_Pin GPIO_PIN_8
#define valve10_GPIO_Port GPIOC
#define valve11_Pin GPIO_PIN_9
#define valve11_GPIO_Port GPIOC
#define valve12_Pin GPIO_PIN_8
#define valve12_GPIO_Port GPIOA
#define heater_en_Pin GPIO_PIN_10
#define heater_en_GPIO_Port GPIOA
#define valve18_Pin GPIO_PIN_11
#define valve18_GPIO_Port GPIOA
#define valve13_Pin GPIO_PIN_10
#define valve13_GPIO_Port GPIOC
#define valve14_Pin GPIO_PIN_11
#define valve14_GPIO_Port GPIOC
#define valve16_Pin GPIO_PIN_12
#define valve16_GPIO_Port GPIOC
#define valve17_Pin GPIO_PIN_0
#define valve17_GPIO_Port GPIOD
#define TC_SPI2_SCK_Pin GPIO_PIN_1
#define TC_SPI2_SCK_GPIO_Port GPIOD
#define valve15_Pin GPIO_PIN_2
#define valve15_GPIO_Port GPIOD
#define TC_SPI2_MISO_Pin GPIO_PIN_3
#define TC_SPI2_MISO_GPIO_Port GPIOD
#define TC_SPI2_MOSI_Pin GPIO_PIN_4
#define TC_SPI2_MOSI_GPIO_Port GPIOD
#define T1_EN_Pin GPIO_PIN_9
#define T1_EN_GPIO_Port GPIOB
#define T3_EN_Pin GPIO_PIN_0
#define T3_EN_GPIO_Port GPIOE
#define T5_EN_Pin GPIO_PIN_1
#define T5_EN_GPIO_Port GPIOE

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
