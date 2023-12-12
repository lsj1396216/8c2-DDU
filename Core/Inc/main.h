/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
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
#include "stm32f4xx_hal.h"

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
#define SENSOR_13_Pin GPIO_PIN_13
#define SENSOR_13_GPIO_Port GPIOC
#define SENSOR_14_Pin GPIO_PIN_14
#define SENSOR_14_GPIO_Port GPIOC
#define SENSOR_15_Pin GPIO_PIN_15
#define SENSOR_15_GPIO_Port GPIOC
#define SENSOR_0_Pin GPIO_PIN_0
#define SENSOR_0_GPIO_Port GPIOC
#define SENSOR_1_Pin GPIO_PIN_1
#define SENSOR_1_GPIO_Port GPIOC
#define SENSOR_2_Pin GPIO_PIN_2
#define SENSOR_2_GPIO_Port GPIOC
#define SENSOR_3_Pin GPIO_PIN_3
#define SENSOR_3_GPIO_Port GPIOC
#define SENSOR_4_Pin GPIO_PIN_0
#define SENSOR_4_GPIO_Port GPIOA
#define SENSOR_5_Pin GPIO_PIN_1
#define SENSOR_5_GPIO_Port GPIOA
#define SENSOR_9_Pin GPIO_PIN_4
#define SENSOR_9_GPIO_Port GPIOA
#define ADD_SW1_Pin GPIO_PIN_5
#define ADD_SW1_GPIO_Port GPIOA
#define ADD_SW2_Pin GPIO_PIN_6
#define ADD_SW2_GPIO_Port GPIOA
#define ADD_SW3_Pin GPIO_PIN_7
#define ADD_SW3_GPIO_Port GPIOA
#define ADD_SW4_Pin GPIO_PIN_4
#define ADD_SW4_GPIO_Port GPIOC
#define SENSOR_6_Pin GPIO_PIN_5
#define SENSOR_6_GPIO_Port GPIOC
#define LED_2_Pin GPIO_PIN_0
#define LED_2_GPIO_Port GPIOB
#define USART1_RTS_OUT_Pin GPIO_PIN_1
#define USART1_RTS_OUT_GPIO_Port GPIOB
#define SENSOR_10_Pin GPIO_PIN_2
#define SENSOR_10_GPIO_Port GPIOB
#define LED_1_Pin GPIO_PIN_10
#define LED_1_GPIO_Port GPIOB
#define SENSOR_11_Pin GPIO_PIN_11
#define SENSOR_11_GPIO_Port GPIOB
#define SENSOR_12_Pin GPIO_PIN_12
#define SENSOR_12_GPIO_Port GPIOB
#define EX_STEP_EN_Pin GPIO_PIN_13
#define EX_STEP_EN_GPIO_Port GPIOB
#define EX_STEP_DIR_Pin GPIO_PIN_14
#define EX_STEP_DIR_GPIO_Port GPIOB
#define EX_STEP_PLUS_Pin GPIO_PIN_15
#define EX_STEP_PLUS_GPIO_Port GPIOB
#define DCM1_IN2_Pin GPIO_PIN_6
#define DCM1_IN2_GPIO_Port GPIOC
#define STEP_DIR_Pin GPIO_PIN_7
#define STEP_DIR_GPIO_Port GPIOC
#define STEP_PULS_Pin GPIO_PIN_8
#define STEP_PULS_GPIO_Port GPIOC
#define STEP_EN_Pin GPIO_PIN_9
#define STEP_EN_GPIO_Port GPIOC
#define RS485_EN_Pin GPIO_PIN_8
#define RS485_EN_GPIO_Port GPIOA
#define SENSOR_8_Pin GPIO_PIN_11
#define SENSOR_8_GPIO_Port GPIOA
#define SENSOR_7_Pin GPIO_PIN_12
#define SENSOR_7_GPIO_Port GPIOA
#define SOLENOID_1_Pin GPIO_PIN_10
#define SOLENOID_1_GPIO_Port GPIOC
#define SOLENOID_2_Pin GPIO_PIN_11
#define SOLENOID_2_GPIO_Port GPIOC
#define LD2_Pin GPIO_PIN_12
#define LD2_GPIO_Port GPIOC
#define USART1_DTR_OUT_Pin GPIO_PIN_2
#define USART1_DTR_OUT_GPIO_Port GPIOD
#define DCM1_IN1_Pin GPIO_PIN_5
#define DCM1_IN1_GPIO_Port GPIOB
#define DCM2_IN2_Pin GPIO_PIN_6
#define DCM2_IN2_GPIO_Port GPIOB
#define DCM2_IN1_Pin GPIO_PIN_7
#define DCM2_IN1_GPIO_Port GPIOB
#define DCM3_IN2_Pin GPIO_PIN_8
#define DCM3_IN2_GPIO_Port GPIOB
#define DCM3_IN1_Pin GPIO_PIN_9
#define DCM3_IN1_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
