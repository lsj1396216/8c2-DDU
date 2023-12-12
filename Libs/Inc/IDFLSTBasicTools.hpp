/*
 * IDFLSTBasicTools.hpp
 *
 * Created: 2019/11/13 13:34:18
 * Author: cp
*/ 

#ifndef __IDFLSTBASICTOOLS_HPP
#define __IDFLSTBASICTOOLS_HPP

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "IDFLST_BSP_Config.hpp"

/* Definitions ---------------------------------------------------------------*/
#define BIT(n) (1 << n)
#define BIT_ISTRUE(x,mask)  (((x) & (mask)) != 0)
#define BIT_ISFALSE(x,mask) (((x) & (mask)) == 0)

/* Function prototypes -------------------------------------------------------*/
uint8_t GetModuleAdd(void);
GPIO_PinState Sensor_Read(IDFLST_Pin Pin);

#endif /* __IDFLSTBASICTOOLS_HPP */
