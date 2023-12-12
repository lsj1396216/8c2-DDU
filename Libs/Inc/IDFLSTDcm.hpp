/*
 * IDFLSTDcm.hpp
 *
 * Created: 2019/11/26 9:43:18
 * Author: cp
*/ 

#ifndef __IDFLSTDCM_HPP
#define __IDFLSTDCM_HPP

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "IDFLSTBasicTools.hpp"

class IDFLSTDcm
{
	private:
	IDFLST_Pin m_in1Pin;
	IDFLST_Pin m_in2Pin;
	
	bool m_dcmRunning;
	
	void (*pf_running)(void);
	
	public:
	IDFLSTDcm(IDFLST_Pin in1Pin, IDFLST_Pin in2Pin);
	void timer_Init(void);
	
	void start(bool dir);
	void start(bool dir, int32_t speed);
	void stop(void);
	void stop_WithoutBrakes(void);
	
	void Move(bool dir,  uint32_t ms);
	void Move(bool dir,  uint32_t ms, int32_t speed);
	bool MoveTo(bool dir, uint32_t ms, IDFLST_Pin sensorPin, GPIO_PinState destType, uint32_t overShoot);
	bool MoveTo(bool dir, uint32_t ms, IDFLST_Pin sensorPin, GPIO_PinState destType, uint32_t overShoot, int32_t speed);
	
	bool isRunning(void);
	void set_Running_Callback(void (*pf)(void));
	void running_Call(void);
};

#endif /* __IDFLSTDCM_HPP */
