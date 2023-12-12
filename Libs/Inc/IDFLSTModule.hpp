/*
 * IDFLSTModule.hpp
 *
 * Created: 2019/11/12 13:00:18
 * Author: cp
*/ 

#ifndef __IDFLSTMODULE_HPP
#define __IDFLSTMODULE_HPP

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "IDFLSTComm.hpp"
#include "IDFLSTBasicTools.hpp"

/* Definitions ---------------------------------------------------------------*/
#define ADDR_BROADCAST 0xBC

#define FC_QUERY 0x01

#define NOTHING_TO_WAITING	0x00
#define FB_ANSWER						0xF1
#define FB_ACK 							0x06
#define FB_NAK							0x15

#define RETRY 	0
#define TIMEOUT	300
#define ERR_FB_TIMEOUT 0xE0


class IDFLSTModule
{
	private:
	uint8_t m_moduleAddress;
	uint8_t anserBack[FUNCTION_CODE_SIZE];
	void (*pf_WaitingWork)(void);
	
	public:
	uint8_t myStatus[FUNCTION_CODE_SIZE];
	uint8_t waitingStatus;
	uint8_t fb_FuncCode;
	
	IDFLSTComm* m_Comm;
	
	IDFLSTModule(IDFLSTComm* comm);
	void PortOpen(void);
	void module_Init(uint8_t moduleAddress);
	
	void broadcast_CommSend(uint8_t functionCode, uint8_t parameterCode = 0x00, const char dataCode[] = "");
	void command_Send_WithoutFB(uint8_t functionCode,uint8_t parameterCode = 0x00, const char dataCode[] = "");
	uint8_t command_Send(uint8_t functionCode, uint8_t parameterCode = 0x00, uint8_t Expected_FB = FB_ACK, const char dataCode[] = "");
	void feed_Back(uint8_t functionCode, uint8_t parameterCode = 0x00, const char dataCode[] = "");
	uint8_t status_Query(void);
	void answer_Status(const char dataCode[] = "");
	uint8_t* get_AnserBackCode(uint8_t functionCode, uint8_t parameterCode = 0x00);
	
	void set_WaitingWork_Callback(void (*pf)(void));
	void WaitingWork_Call(void);
};

#endif /* __IDFLSTMODULE_HPP */
