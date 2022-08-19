/**
  ******************************************************************************
  * @file    debugSerial.h
  * @author  szazone
  * @version V0.0.1
  * @date    03-August-2022
  * @brief   FT232R Isolated 5-V Full- and Half-Duplex RS-485 Transceivers 
  * 		 Board Support Package head file.
  *
  ******************************************************************************
  */ 

#ifndef __DEBUGSERIAL_H__
#define __DEBUGSERIAL_H__

#ifdef __cplusplus
	extern "C" {
#endif
/* Includes ------------------------------------------------------------------*/
// STD C
#include "stdio.h"	
#include  <stdarg.h>
#include  <stdlib.h>
// Drivers/STM32F4xx_HAL_Driver
#include "stm32f4xx.h"
// Hardware
#include "serial.h"

#define DebugSerial_cmdMaxLength	20

extern USART_RECEIVE_T  DebugSerial_data[450];
extern USART_RECEIVE_T* DebugSerial_data_p;

void DebugSerial_printf(char *format, ...);
void DebugSerial_analysisMessage(char* data, unsigned short size);

unsigned int DebugSerial_readAddr(unsigned int addr);
void DebugSerial_writeAddr(unsigned int addr,unsigned int val);

#ifdef __cplusplus
	}
#endif

#endif	// __DEBUGSERIAL_H__
