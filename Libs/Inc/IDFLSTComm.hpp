/*
 * IDFLSTComm.hpp
 *
 * Created: 2019/5/14 12:11:38
 * Author: cp
*/ 

#ifndef __IDFLSTCOMM_HPP
#define __IDFLSTCOMM_HPP

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "string.h"
#include <stdio.h>
#include "IDFLSTSerial.hpp"

/* Definitions ---------------------------------------------------------------*/

#define FUNCTION_CODE_SIZE 10
#define CMD_DATA_BUFFER_SIZE 1024

#define ADDRESS___0 0
#define FUNCTION__1 1
#define PARAMETER_2 2
#define STATUS1___3 3
#define STATUS2___4 4
#define ERRORCODE_5 5
#define SENSOR____6	6
#define RESERVE1__7 7
#define RESERVE2__8 8	
#define LRC_CODE__9 9

#define STX 0x02
#define ETX 0x03

#define HIGH_BIT 0x1
#define LOW__BIT 0x0

class IDFLSTComm
{
	private:
	volatile bool m_cmdReady;
	volatile bool m_receiveing;
	volatile int m_recvCounter;
	volatile int m_dataCounter;
	volatile uint8_t m_tempHigh;
	// volatile int m_baud_rate;
	volatile bool	m_haveTxEnablePin;
	
	GPIO_TypeDef* m_txEnablePort;
	uint16_t m_txEnablePin;
	
	uint8_t encode(const uint8_t chr, bool lOrH);
	uint8_t decode(const uint8_t h, const uint8_t l);
	void cmdFuncClear();
	void cmdDataClear();
	void recvStatusReset();
	
	public:
	uint8_t cmdFunc[FUNCTION_CODE_SIZE];
	char cmdData[CMD_DATA_BUFFER_SIZE];
	
	IDFLSTSerial* m_serial;
	
	IDFLSTComm(IDFLSTSerial* Serial);
	IDFLSTComm(IDFLSTSerial* Serial, GPIO_TypeDef* txEnablePort, uint16_t txEnablePin);
	void set_EnablePin(GPIO_TypeDef* txEnablePort, uint16_t txEnablePin);
	void PortOpen();
	size_t commSend(const uint8_t * funcCode, const char dataCode[]);
	size_t send(const char str[]);
	void sendFromPSTR(const char str[]);
	void setToSend();
	void setToRecv();
	void receive();
	bool getCmdReady();
	void cmdComplete();
	int getDataCounter();
	
};

#endif /* __IDFLSTCOMM_HPP */
