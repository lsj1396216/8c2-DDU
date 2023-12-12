/*
 * IDFLST_BSP_Object.hpp
 *
 * Created: 2021/12/22 13:34:18
 * Author: cp
*/ 

#ifndef __IDFLST_BSP_OBJECT_HPP
#define __IDFLST_BSP_OBJECT_HPP

/* Includes ------------------------------------------------------------------*/
#include "IDFLSTSerial.hpp"
#include "IDFLSTStep.hpp"
#include "IDFLSTComm.hpp"
#include "IDFLSTLed.hpp"
#include "IDFLSTDcm.hpp"
#include "IDFLSTModule.hpp"

extern IDFLSTComm myCom232;  // RS232
extern IDFLSTComm myCom485;

extern IDFLSTLed myLed_1;
extern IDFLSTLed myLed_2;

extern IDFLSTDcm myDcm_1;
extern IDFLSTDcm myDcm_2;
extern IDFLSTDcm myDcm_3;


#endif /* __IDFLST_BSP_OBJECT_HPP */


