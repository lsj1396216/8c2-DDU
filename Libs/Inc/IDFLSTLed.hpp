/*
 * IDFLSTLed.hpp
 *
 * Created: 2019/11/22 17:46:18
 * Author: cp
*/ 

#ifndef __IDFLSTLED_HPP
#define __IDFLSTLED_HPP

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "IDFLSTBasicTools.hpp"

class IDFLSTLed
{
	private:
	IDFLST_Pin m_ledPin;
	
	public:
	IDFLSTLed(IDFLST_Pin pulsePin);
	
	void timer_Init(void);
	void on(void);
	void off(void);
	void set_Brightness(int32_t brightness);
};

#endif /* __IDFLSTLED_HPP */
