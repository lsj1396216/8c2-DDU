/*
 * IDFLST_BSP_Config.hpp
 *
 * Created: 2021/12/21 13:34:18
 * Author: cp
*/ 

#ifndef __IDFLST_BSP_CONFIG_HPP
#define __IDFLST_BSP_CONFIG_HPP

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "tim.h"

/* Definitions ---------------------------------------------------------------*/
#define ADDRESS_BITS 4

#define NO_ADC 		0xFFFF
#define NO_PWM		0xFFFF
#define NO_EXTI   0xFFFF

// Direction of stepper motor and DC Motor movement
#define CW  0 
#define CCW 1

#define LOW  GPIO_PIN_RESET
#define HIGH GPIO_PIN_SET

#define LD2_ON  HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, HIGH)
#define LD2_OFF HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, LOW)
#define LD2_TOGGLE HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin)

#define SOLENOID1_ON HAL_GPIO_WritePin(SOLENOID_1_GPIO_Port, SOLENOID_1_Pin, HIGH)
#define SOLENOID1_OFF HAL_GPIO_WritePin(SOLENOID_1_GPIO_Port, SOLENOID_1_Pin, LOW)
#define SOLENOID2_ON HAL_GPIO_WritePin(SOLENOID_2_GPIO_Port, SOLENOID_2_Pin, HIGH)
#define SOLENOID2_OFF HAL_GPIO_WritePin(SOLENOID_2_GPIO_Port, SOLENOID_2_Pin, LOW)

/* Typedef -------------------------------------------------------------------*/
typedef struct _PortPinMap
{
	GPIO_TypeDef *GPIOx_Port;
	uint32_t GPIO_Pin;
	
//	ADC_HandleTypeDef *ADCx;
//  uint32_t  adc_channel;

  TIM_HandleTypeDef *TIMx;
  uint32_t  timerChannel;
	uint32_t  extiChannel;
} PinPortMap;

typedef enum 
{
	NULL_PIN = 0U,
	
	SENSOR_0,
	SENSOR_1,
	SENSOR_2,
	SENSOR_3,
	SENSOR_4,
	SENSOR_5,
	
	SENSOR_6,
	SENSOR_7,
	SENSOR_8,
	SENSOR_9,
	SENSOR_10,
	SENSOR_11,
	SENSOR_12,
	SENSOR_13,
	SENSOR_14,
	SENSOR_15,
	
	ADD_SW1,
	ADD_SW2,
	ADD_SW3,
	ADD_SW4,
	
	STEP_PULS,
	STEP_DIR,
	STEP_EN,
	
	EX_STEP_PLUS,
	EX_STEP_DIR,
	EX_STEP_EN,
	
	LED_1,
	LED_2,
	
	DCM1_IN1,
	DCM1_IN2,
	DCM2_IN1,
	DCM2_IN2,
	DCM3_IN1,
	DCM3_IN2
	
//	NULL_PIN = 0U,
//	
//	SENSOR_0,
//	SENSOR_1,
//	SENSOR_2,
//	SENSOR_3,
//	SENSOR_4,
//	SENSOR_5,
//	
//	ADD_SW1,
//	ADD_SW2,
//	ADD_SW3,
//	ADD_SW4,
//	
//	STEP_PULS,
//	STEP_DIR,
//	STEP_EN,
//	
//	EX_STEP_PLUS,
//	EX_STEP_DIR,
//	EX_STEP_EN,
//	
//	LED_1,
//	LED_2,
//	
//	DCM1_IN1,
//	DCM1_IN2,
//	DCM2_IN1,
//	DCM2_IN2,
//	DCM3_IN1,
//	DCM3_IN2
	
} IDFLST_Pin;


extern const PinPortMap IDFLST_Pins[];

#endif /* __IDFLST_BSP_CONFIG_HPP */
