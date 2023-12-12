/*
 * IDFLSTStep.hpp
 *
 * Created: 2019/11/14 16:34:18
 * Author: cp
*/ 

#ifndef __IDFLSTSTEP_HPP
#define __IDFLSTSTEP_HPP

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "tim.h"
#include "math.h"
#include "IDFLSTBasicTools.hpp"

/* Definitions ---------------------------------------------------------------*/
// Speed ramp states
#define STOP  0
#define ACCEL 1
#define DECEL 2
#define RUN   3

// How long time after the motor stops disable the driver, to avoid overshooting due to inertia.
#define STOP_LOCK_TIME 25	

// Pulse Timer running on 72MHz / 36 = 2MHz (0.5uS)(for STM32F103RC). (T1-FREQ 2000000)
#define T1_FREQ 2000000

// Number of steps per round on stepper motor in use.
#define SPR m_spr

// Maths constants. To simplify maths when calculating in speed_cntr_Move().
#define ALPHA (2*3.1415926/SPR)
#define A_T_x100 ((long)(ALPHA*T1_FREQ*100))
#define T1_FREQ_148 ((long)((T1_FREQ*0.676)/100))
#define A_SQ (long)(ALPHA*2*10000000000)
#define A_x20000 (long)(ALPHA*20000)

typedef struct{
	// What part of the speed ramp we are in.
	// unsigned char run_state;
	uint8_t run_state;
	// Direction stepper motor should move.
	// unsigned char dir;
	bool dir;
	// Peroid of next timer delay. At start this value set the accelration rate.
	// unsigned int step_delay;
	int32_t step_delay;
	// What step_pos to start deceleration?
	// unsigned long decel_start;
	uint32_t decel_start;
	// Sets deceleration rate.
	// signed long decel_val;
	int32_t decel_val;
	// Minimum time delay (max speed)
	//signed long min_delay;
	int32_t min_delay;
	// Counter used when accelerateing/decelerateing to calculate step_delay.
	//signed long accel_count;
	int32_t accel_count;
} speedRampData;

class IDFLSTStep
{
	private:
	IDFLST_Pin m_pulsePin;
	IDFLST_Pin m_directionPin;
	IDFLST_Pin m_enablePin;
	
	// Number of steps per round on stepper motor in use.
	uint32_t m_spr;
	
	bool m_haveEnablePin;
	bool m_enableLevel;
	bool m_stopHold;
	
	speedRampData m_srd;
	
	// Destination control
	volatile bool	m_haveDest;
	volatile GPIO_PinState m_destType;
	volatile bool	m_arriveDest;
	volatile uint32_t	m_overShoot;
	volatile uint32_t	m_overShootCount;
	volatile bool	m_started;
	IDFLST_Pin m_sensorPin;
	
	// Step Running flag
	bool stepRunning;
	
	// Default Running parameter
	int32_t m_accel;
	int32_t m_decel;
	int32_t m_motorspeed;
	
	// To flag is Move or MoveTo
	bool isMove;
	
	// Position of stepper motor (relative to starting position as zero)
	int32_t m_stepPosition;
	// Logic position
	int32_t m_logicPosition;
	
	void (*pf_Before_running)(void);
	void (*pf_running)(void);
	void (*pf_After_running)(void);
	
	// private methods
	inline void sm_driver_StepCounter(bool dir) __attribute__((__always_inline__));
	inline void step_Proc(void) __attribute__((__always_inline__));
	inline void step_Pin_Recover(void) __attribute__((__always_inline__));
	
	public:
	TIM_HandleTypeDef* m_pulseTimHandle;
	TIM_HandleTypeDef* m_pinRecoverTimHandle;
	
	IDFLSTStep(IDFLST_Pin pulsePin, IDFLST_Pin directionPin, TIM_HandleTypeDef* pulseTimHandle, TIM_HandleTypeDef* pinRecoverTimHandle, uint32_t spr = 3200);
	
	void set_EnablePin(IDFLST_Pin enablePin, bool enableLevel = HIGH, bool stopHold = false);
	void timer_Init(void);
	void setToHold(void);
	void setToUnHold(void);
	
	void set_Destination(IDFLST_Pin sensorPin, GPIO_PinState destType, uint32_t overShoot);
	
	/*  Gets the status of the arrival sensor
	 *	Return True: it reaches the target sensor before the scheduled steps are finished.
	 *	Return False: after running the scheduled steps, the target sensor can not be reached (that is, the rush to the sensor timeout); or the target sensor is not set before running.
	 */
	bool get_Arrive_Status(void);
	
	/*! \brief Move the stepper motor a given number of steps.
	*
	*  Makes the stepper motor move the given number of steps.
	*  It accelrate with given accelration up to maximum speed and decelerate
	*  with given deceleration so it stops at the given step.
	*  If accel/decel is to small and steps to move is to few, speed might not
	*  reach the max speed limit before deceleration starts.
	*
	*  \param step  Number of steps to move (pos - CW, neg - CCW).
	*  \param accel  Accelration to use, in 0.01*rad/sec^2.
	*  \param decel  Decelration to use, in 0.01*rad/sec^2.
	*  \param speed  Max speed, in 0.01*rad/sec.
	*/
	void speed_cntr_Move(int32_t steps, int32_t accel, int32_t decel, int32_t motorspeed);
	
	void Move(int32_t steps);
	void Move(int32_t steps, int32_t accel, int32_t decel, int32_t motorspeed);
	bool MoveTo(int32_t steps, IDFLST_Pin sensorPin, GPIO_PinState destType, uint32_t overShoot);
	bool MoveTo(int32_t steps, IDFLST_Pin sensorPin, GPIO_PinState destType, uint32_t overShoot, int32_t accel, int32_t decel, int32_t motorspeed);
	
	void set_Move_Parameter(int32_t accel, int32_t decel, int32_t motorspeed);
	
	bool isRunning(void);
	void stop(void);
	
	int32_t get_Step_Position(void);
	void step_Position_clear(void);
	int32_t get_Logic_Position(void);
	void logic_Position_clear(void);
	
	void set_Before_Running_Callback(void (*pf)(void));
	void set_Running_Callback(void (*pf)(void));
	void set_After_Running_Callback(void (*pf)(void));
	
	void before_Running_Call(void);
	void running_Call(void);
	void after_Running_Call(void);
	
	// public only for easy access by interrupt handlers
	inline void handle_pulseTim_interrupt(void) __attribute__((__always_inline__));
	inline void handle_pinRecoverTim_interrupt(void) __attribute__((__always_inline__));
};

extern IDFLSTStep myStep;
extern IDFLSTStep myExStep;

#endif /* __IDFLSTSTEP_HPP */
