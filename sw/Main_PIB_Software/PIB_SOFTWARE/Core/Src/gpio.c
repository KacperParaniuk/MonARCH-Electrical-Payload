/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    gpio.c
  * @brief   This file provides code for the configuration
  *          of all used GPIO pins.
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
#include "gpio.h"

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/*----------------------------------------------------------------------------*/
/* Configure GPIO                                                             */
/*----------------------------------------------------------------------------*/
/* USER CODE BEGIN 1 */

/* USER CODE END 1 */

/** Configure pins
*/
void MX_GPIO_Init(void)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOE, T4_EN_Pin|T2_EN_Pin|PT_EN_Pin|valve6_Pin
                          |LED_PIN_Pin|T3_EN_Pin|T5_EN_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(POW12_EN_GPIO_Port, POW12_EN_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, ADC_EN_Pin|valve12_Pin|heater_en_Pin|valve18_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, valve1_Pin|valve2_Pin|valve3_Pin|valve5_Pin
                          |T1_EN_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOD, valve7_Pin|valve8_Pin|valve17_Pin|valve15_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, valve4_Pin|valve9_Pin|valve10_Pin|valve11_Pin
                          |valve13_Pin|valve14_Pin|valve16_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : T4_EN_Pin T2_EN_Pin PT_EN_Pin valve6_Pin
                           LED_PIN_Pin T3_EN_Pin T5_EN_Pin */
  GPIO_InitStruct.Pin = T4_EN_Pin|T2_EN_Pin|PT_EN_Pin|valve6_Pin
                          |LED_PIN_Pin|T3_EN_Pin|T5_EN_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  /*Configure GPIO pin : POW12_EN_Pin */
  GPIO_InitStruct.Pin = POW12_EN_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(POW12_EN_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : ADC_EN_Pin valve12_Pin heater_en_Pin valve18_Pin */
  GPIO_InitStruct.Pin = ADC_EN_Pin|valve12_Pin|heater_en_Pin|valve18_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : valve1_Pin valve2_Pin valve3_Pin valve5_Pin
                           T1_EN_Pin */
  GPIO_InitStruct.Pin = valve1_Pin|valve2_Pin|valve3_Pin|valve5_Pin
                          |T1_EN_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : valve7_Pin valve8_Pin valve17_Pin valve15_Pin */
  GPIO_InitStruct.Pin = valve7_Pin|valve8_Pin|valve17_Pin|valve15_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

  /*Configure GPIO pins : valve4_Pin valve9_Pin valve10_Pin valve11_Pin
                           valve13_Pin valve14_Pin valve16_Pin */
  GPIO_InitStruct.Pin = valve4_Pin|valve9_Pin|valve10_Pin|valve11_Pin
                          |valve13_Pin|valve14_Pin|valve16_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

}

/* USER CODE BEGIN 2 */

/* USER CODE END 2 */
