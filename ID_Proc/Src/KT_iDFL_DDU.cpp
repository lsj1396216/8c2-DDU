/*
 * KT_iDFL_DDU.cpp
 *
 * Created: 2021/12/23 12:32:18
 * Author: cp
*/

/* Includes ------------------------------------------------------------------*/
#include "KT_iDFL_DDU.hpp"
#include "IDFLST_BSP_Object.hpp"

/* Definitions ---------------------------------------------------------------*/
#define DDU_SENSOR_BAR_PHASE	SENSOR_3
#define DDU_SENSOR_BAR_ZERO		SENSOR_2
#define DDU_SENSOR_TAIL				SENSOR_1
#define DDU_SENSOR_TUBE_1			SENSOR_6
#define DDU_SENSOR_TUBE_2			SENSOR_7

// Status1 bit map
#define STATUS1_BUSY________7 BIT(7)jjjj
#define STATUS1_TUBE_READY__6 BIT(6)
#define STATUS1_INITIALIZED_0 BIT(0)

// Status2 bit map
#define STATUS2_TUBE_DIR________7 BIT(7)
#define STATUS2_IS_WORKING______6 BIT(6)
#define STATUS2_WORK_REQUEST____2 BIT(2)
#define STATUS2_PREPARE_REQUEST_1 BIT(1)
#define STATUS2_INIT_REQUEST____0 BIT(0)

// ERRORCODE_5 bit map
#define ERROR_WORK_MOTOR_TIMEOUT	BIT(2)
#define ERROR_PREPARE_TUBELOST		BIT(1)
#define ERROR_INIT_MOTOR_TIMEOUT  BIT(0)

// Command define
#define FC_WORK    0x02
#define FC_PREPARE 0x03
#define FC_ 0x04
#define FC_INIT    0x08

/* Function prototypes -------------------------------------------------------*/
void system_Init(void);
void init_Proc(void);
void main_Job(void);
void command_Proc(void);

void com_Proc(void);
void com_Proc_485(void);
void command_Event_485(const uint8_t * cmdfuncCode, const char cmddataCode[]);
void com_Proc_232(void);
void command_Event_232(const uint8_t * cmdfuncCode, const char cmddataCode[]);

void hard_Work(void);
void hw_Delay(uint32_t);

/* Variables -----------------------------------------------------------------*/
IDFLSTModule module_DDU(&myCom485);
IDFLSTDcm myDcm(DCM1_IN1, DCM1_IN2);

/* Application ---------------------------------------------------------------*/
void KT_iDFL_DDU_setup(void)
{
	module_DDU.PortOpen();
	module_DDU.set_WaitingWork_Callback(hard_Work);
	
	myDcm.timer_Init();
	myDcm.set_Running_Callback(hard_Work);
	
	myStep.set_EnablePin(STEP_EN);
	myStep.timer_Init();
	myStep.set_Running_Callback(hard_Work);
	
	myExStep.set_EnablePin(EX_STEP_EN);
	myExStep.timer_Init();
	myExStep.set_Running_Callback(hard_Work);
	
}

void KT_iDFL_DDU_loop(void)
{
	system_Init();
	
	init_Proc();
	
	for(;;)
	{
		main_Job();
		command_Proc();
		com_Proc();
	}
}

void system_Init(void)
{
	module_DDU.module_Init(GetModuleAdd());
	
}

void init_Proc(void)
{
	
}

void main_Job(void)
{
	
}

void command_Proc(void)
{
	//////////////////////// Initialization ///////////////////////////////
	if(BIT_ISTRUE(module_DDU.myStatus[STATUS2___4], STATUS2_INIT_REQUEST____0))
	{
		CLEAR_BIT(module_DDU.myStatus[STATUS1___3], STATUS1_INITIALIZED_0);
		
		if(Sensor_Read(DDU_SENSOR_BAR_PHASE) == LOW)
		{
			if(myStep.MoveTo(3600/2, DDU_SENSOR_BAR_PHASE, HIGH, 0, 3000, 3000, 1256))
			{
				// Reach the target position
			}
			else
			{
				// Timeout
				SET_BIT(module_DDU.myStatus[ERRORCODE_5], ERROR_INIT_MOTOR_TIMEOUT);
				
				CLEAR_BIT(module_DDU.myStatus[STATUS2___4], STATUS2_INIT_REQUEST____0);
				module_DDU.myStatus[STATUS1___3] = 0x00;
				return;
			}
		}
		else
		{
			if(myStep.MoveTo(-3600/2, DDU_SENSOR_BAR_PHASE, LOW, 0, 3000, 3000, 1256))
			{
				// Reach the target position
			}
			else
			{
				// Timeout
				SET_BIT(module_DDU.myStatus[ERRORCODE_5], ERROR_INIT_MOTOR_TIMEOUT);
				
				CLEAR_BIT(module_DDU.myStatus[STATUS2___4], STATUS2_INIT_REQUEST____0);
				module_DDU.myStatus[STATUS1___3] = 0x00;
				return;
			}
		}
		
		hw_Delay(200);
		
		if(myStep.MoveTo(-800/2, DDU_SENSOR_BAR_ZERO, LOW, 10, 3000, 3000, 50))
		{
			// Reach the target position
		}
		else
		{
			// Timeout
			SET_BIT(module_DDU.myStatus[ERRORCODE_5], ERROR_INIT_MOTOR_TIMEOUT);
			
			CLEAR_BIT(module_DDU.myStatus[STATUS2___4], STATUS2_INIT_REQUEST____0);
			module_DDU.myStatus[STATUS1___3] = 0x00;
			return;
		}
		
		module_DDU.myStatus[STATUS1___3] = 0x00;
		module_DDU.myStatus[STATUS2___4] = 0x00;
		module_DDU.myStatus[ERRORCODE_5] = 0x00;
		
		SET_BIT(module_DDU.myStatus[STATUS1___3], STATUS1_INITIALIZED_0);
				
		CLEAR_BIT(module_DDU.myStatus[STATUS2___4], STATUS2_INIT_REQUEST____0);
		CLEAR_BIT(module_DDU.myStatus[STATUS1___3], STATUS1_BUSY________7);
	}
	
	//////////////////////// Tube preparation ///////////////////////////////
	if(BIT_ISTRUE(module_DDU.myStatus[STATUS2___4], STATUS2_PREPARE_REQUEST_1))
	{
		// if(myDcm.MoveTo(CCW, 1200, DDU_SENSOR_TUBE_1, LOW ,0))
		if(myExStep.MoveTo(18000, DDU_SENSOR_TUBE_1, LOW, 0, 30000, 30000, 4500))
		{
			// Detect the tube
		}
		else
		{
			// Timeout, the test tube on the belt disappeared (no test tube or stuck tube)
			SET_BIT(module_DDU.myStatus[ERRORCODE_5], ERROR_PREPARE_TUBELOST);
			
			CLEAR_BIT(module_DDU.myStatus[STATUS2___4], STATUS2_PREPARE_REQUEST_1);
			module_DDU.myStatus[STATUS1___3] = 0x00;
			return;
		}
		
		if(myExStep.MoveTo(4000, DDU_SENSOR_TAIL, HIGH, 100, 30000, 30000, 4500))
		{
			CLEAR_BIT(module_DDU.myStatus[STATUS2___4], STATUS2_TUBE_DIR________7);
			
		}
		else
		{
			SET_BIT(module_DDU.myStatus[STATUS2___4], STATUS2_TUBE_DIR________7);
		}
		
		SET_BIT(module_DDU.myStatus[STATUS1___3], STATUS1_TUBE_READY__6);
		
//		if(myDcm.MoveTo(CCW, 1200, DDU_SENSOR_TUBE_1, LOW ,0))
//		{
//			// Detect the tube
//		}
//		else
//		{
//			// Timeout, the test tube on the belt disappeared (no test tube or stuck tube)
//			SET_BIT(module_DDU.myStatus[ERRORCODE_5], ERROR_PREPARE_TUBELOST);
//			
//			CLEAR_BIT(module_DDU.myStatus[STATUS2___4], STATUS2_PREPARE_REQUEST_1);
//			module_DDU.myStatus[STATUS1___3] = 0x00;
//			return;
//		}
//		
//		myDcm.start(CCW);
//		hw_Delay(300);
//		if(Sensor_Read(DDU_SENSOR_TAIL))
//		{
//			SET_BIT(module_DDU.myStatus[STATUS2___4], STATUS2_TUBE_DIR________7);
//		}
//		else
//		{
//			CLEAR_BIT(module_DDU.myStatus[STATUS2___4], STATUS2_TUBE_DIR________7);
//		}
//		hw_Delay(50);
//		myDcm.stop();
//		hw_Delay(20);
//		
//		myDcm.Move(CW, 1000);
//		
//		SET_BIT(module_DDU.myStatus[STATUS1___3], STATUS1_TUBE_READY__6);
		
		CLEAR_BIT(module_DDU.myStatus[STATUS2___4], STATUS2_PREPARE_REQUEST_1);
		CLEAR_BIT(module_DDU.myStatus[STATUS1___3], STATUS1_BUSY________7);
	}
	
	//////////////////////// Tube Processing ///////////////////////////////
	if(BIT_ISTRUE(module_DDU.myStatus[STATUS2___4], STATUS2_WORK_REQUEST____2))
	{
		if(BIT_ISFALSE(module_DDU.myStatus[STATUS2___4], STATUS2_TUBE_DIR________7))
		{
			// When preparing the test tube, the tail was detected
			myStep.Move(-3200/2, 10000, 10000, 3600);
			hw_Delay(200);                                                                                                                                                                                                                                                                                                                                                                                                                           
			CLEAR_BIT(module_DDU.myStatus[STATUS2___4], STATUS2_IS_WORKING______6);
			if(myStep.MoveTo(3400/2, DDU_SENSOR_BAR_PHASE, HIGH, 0, 10000, 10000, 3600))
			{
				// Arrive
			}
			else
			{
				// Timeout
				SET_BIT(module_DDU.myStatus[ERRORCODE_5], ERROR_WORK_MOTOR_TIMEOUT);
				
				CLEAR_BIT(module_DDU.myStatus[STATUS2___4], STATUS2_TUBE_DIR________7);
				CLEAR_BIT(module_DDU.myStatus[STATUS2___4], STATUS2_WORK_REQUEST____2);
				module_DDU.myStatus[STATUS1___3] = 0x00;
				return;
			}
			if(myStep.MoveTo(-200/2, DDU_SENSOR_BAR_ZERO, LOW, 0, 3000, 3000, 800))
			{
				// Arrive
			}
			else
			{
				// Timeout
				SET_BIT(module_DDU.myStatus[ERRORCODE_5], ERROR_WORK_MOTOR_TIMEOUT);
				
				CLEAR_BIT(module_DDU.myStatus[STATUS2___4], STATUS2_TUBE_DIR________7);
				CLEAR_BIT(module_DDU.myStatus[STATUS2___4], STATUS2_WORK_REQUEST____2);
				module_DDU.myStatus[STATUS1___3] = 0x00;
				return;
			}
		}
		else
		{
			// No tail was detected when preparing the test tube
			myStep.Move(3200/2, 10000, 10000, 3600);
			hw_Delay(200);
			CLEAR_BIT(module_DDU.myStatus[STATUS2___4], STATUS2_IS_WORKING______6);
			if(myStep.MoveTo(-3200/2, DDU_SENSOR_BAR_PHASE, LOW, 0, 10000, 10000, 3600))
			{
				// Arrive
			}
			else
			{
				// Timeout
				SET_BIT(module_DDU.myStatus[ERRORCODE_5], ERROR_WORK_MOTOR_TIMEOUT);
				
				CLEAR_BIT(module_DDU.myStatus[STATUS2___4], STATUS2_TUBE_DIR________7);
				CLEAR_BIT(module_DDU.myStatus[STATUS2___4], STATUS2_WORK_REQUEST____2);
				module_DDU.myStatus[STATUS1___3] = 0x00;
				return;
			}
			if(myStep.MoveTo(-200/2, DDU_SENSOR_BAR_ZERO, LOW, 0, 3000, 3000, 800))
			{
				// Arrive
			}
			else
			{
				// Timeout
				SET_BIT(module_DDU.myStatus[ERRORCODE_5], ERROR_WORK_MOTOR_TIMEOUT);
				
				CLEAR_BIT(module_DDU.myStatus[STATUS2___4], STATUS2_TUBE_DIR________7);
				CLEAR_BIT(module_DDU.myStatus[STATUS2___4], STATUS2_WORK_REQUEST____2);
				module_DDU.myStatus[STATUS1___3] = 0x00;
				return;
			}
		}
		
		CLEAR_BIT(module_DDU.myStatus[STATUS2___4], STATUS2_TUBE_DIR________7);
		CLEAR_BIT(module_DDU.myStatus[STATUS1___3], STATUS1_TUBE_READY__6);
				
		CLEAR_BIT(module_DDU.myStatus[STATUS2___4], STATUS2_WORK_REQUEST____2);
		CLEAR_BIT(module_DDU.myStatus[STATUS1___3], STATUS1_BUSY________7);
	}
}

void com_Proc(void)
{
	com_Proc_485();
	com_Proc_232();
}

void com_Proc_485(void)
{
	myCom485.receive();
	if(myCom485.getCmdReady())
	{
		command_Event_485(myCom485.cmdFunc, myCom485.cmdData);
		myCom485.cmdComplete();
	}
}

void command_Event_485(const uint8_t * cmdfuncCode, const char cmddataCode[])
{
	if(cmdfuncCode[ADDRESS___0] == module_DDU.myStatus[ADDRESS___0])
	{
		// Received my command.
		
		//////////////////////// Status Query //////////////////////////
		if(cmdfuncCode[FUNCTION__1] == FC_QUERY)
		{
			module_DDU.answer_Status();
		}
		
		/////////////////////// Initialization request ///////////////////////
		if(cmdfuncCode[FUNCTION__1] == FC_INIT)
		{
			if(BIT_ISFALSE(module_DDU.myStatus[STATUS1___3], STATUS1_BUSY________7))
			{
				// Not Busy
				SET_BIT(module_DDU.myStatus[STATUS1___3], STATUS1_BUSY________7);
				SET_BIT(module_DDU.myStatus[STATUS2___4], STATUS2_INIT_REQUEST____0);
				module_DDU.feed_Back(FB_ACK);
			}
			else
			{
				// Busy
				module_DDU.feed_Back(FB_NAK);
			}
		}
		
		/////////////////////// Tube preparation request ///////////////////////
		if(cmdfuncCode[FUNCTION__1] == FC_PREPARE)
		{
			if(BIT_ISTRUE(module_DDU.myStatus[STATUS1___3], STATUS1_INITIALIZED_0))
			{
				// INITIALIZED
				if(BIT_ISFALSE(module_DDU.myStatus[STATUS1___3], STATUS1_BUSY________7))
				{
					// Not Busy
					if(BIT_ISFALSE(module_DDU.myStatus[STATUS1___3], STATUS1_TUBE_READY__6))
					{
						// There's just no test tube ready
						SET_BIT(module_DDU.myStatus[STATUS1___3], STATUS1_BUSY________7);
						SET_BIT(module_DDU.myStatus[STATUS2___4], STATUS2_PREPARE_REQUEST_1);
						module_DDU.feed_Back(FB_ACK);
					}
					else
					{
						// There are already prepared test tubes. This command is not suitable for repeated execution.
						module_DDU.feed_Back(FB_NAK);
					}
				}
				else
				{
					// Busyfffffffffffffffffffffffffffffffffffffff
					module_DDU.feed_Back(FB_NAK);
				}//ggggggggggggggggggggggggggggggggggggggggggggggggg
			}//ggggggggggggggggggggggggggggggggggggggggggggggg
			else
			{
				// Uninitialized
				module_DDU.feed_Back(FB_NAK);
			}//hjgjghjhjjjjjjjjjjjjjjjj
		}
		
		/////////////////////// Process Tube requests ///////////////////////
		if(cmdfuncCode[FUNCTION__1] == FC_WORK)
		{
			if(BIT_ISTRUE(module_DDU.myStatus[STATUS1___3], STATUS1_INITIALIZED_0))
			{
				// INITIALIZED
				if(BIT_ISFALSE(module_DDU.myStatus[STATUS1___3], STATUS1_BUSY________7))
				{
					// Not Busy
					if(BIT_ISTRUE(module_DDU.myStatus[STATUS1___3], STATUS1_TUBE_READY__6))
					{
						// A test tube is ready
						SET_BIT(module_DDU.myStatus[STATUS1___3], STATUS1_BUSY________7);
						SET_BIT(module_DDU.myStatus[STATUS2___4], STATUS2_IS_WORKING______6);
						SET_BIT(module_DDU.myStatus[STATUS2___4], STATUS2_WORK_REQUEST____2);
						module_DDU.feed_Back(FB_ACK);
					}
					else
					{
						// No test tube ready
						module_DDU.feed_Back(FB_NAK);
					}
				}
				else
				{
					// Busy
					module_DDU.feed_Back(FB_NAK);
				}
			}
			else
			{
				// Uninitialized
				module_DDU.feed_Back(FB_NAK);
			}
		}
		
	}
	else
	{
		// It's not my business.
	}
}

void com_Proc_232(void)
{
	
}

void command_Event_232(const uint8_t * cmdfuncCode, const char cmddataCode[])
{
	
}

void hard_Work(void)
{
	com_Proc();
}

// hardworking_delay
void hw_Delay(uint32_t ms)
{
	volatile uint32_t now;
	now = HAL_GetTick();
	while((HAL_GetTick() - now) < ms)
	{
		com_Proc();
	}
}









