/*
 * IDFLSTSerial.hpp
 *
 * Created: 2019/5/15 10:47:38
 * Author: cp
*/ 

#ifndef __IDFLSTSERIAL_HPP
#define __IDFLSTSERIAL_HPP

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "usart.h"
#include "string.h"

/* Definitions ---------------------------------------------------------------*/
#define SERIAL_RX_BUFFER_SIZE 1024

/* Typedef -------------------------------------------------------------------*/
typedef uint16_t rx_buffer_index_t;

/* Define --------------------------------------------------------------------*/

/* Macro ---------------------------------------------------------------------*/

/* Variables -----------------------------------------------------------------*/

/* Function prototypes -------------------------------------------------------*/

class IDFLSTSerial
{
	protected:
	
	volatile rx_buffer_index_t _rx_buffer_head;
	volatile rx_buffer_index_t _rx_buffer_tail;
	
	unsigned char _rx_buffer[SERIAL_RX_BUFFER_SIZE];
	
	public:
	UART_HandleTypeDef* _uartHandle;
	unsigned char _RxChar;
	
	IDFLSTSerial(UART_HandleTypeDef* uartHandle);
	
	void portOpen(void);
	int available(void);
	int read(void);
	size_t write(uint8_t c);
	size_t write(const char *str);
	
	// Interrupt handlers - Not intended to be called externally
  inline void _rx_complete_irq(void);
	
};

extern IDFLSTSerial Serial232;
extern IDFLSTSerial Serial485;

#endif /* __IDFLSTSERIAL_HPP */








