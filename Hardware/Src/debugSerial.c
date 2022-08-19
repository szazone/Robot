/**
  ******************************************************************************
  * @file    debugSerial.c
  * @author  szazone
  * @version V0.0.1
  * @date    03-August-2022
  * @brief	 Debug serial port (USART1) source file.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "debugSerial.h"

// Application/User/Core
#include "usart.h"
// Middlewares/FreeRTOS
#include "cmsis_os2.h"
#include "FreeRTOS.h"
#include "task.h"
// Bsp
#include "motor.h"
// STD C
#include "string.h"

extern osMutexId_t AppPrintfMutexHandle;
char DebugSerial_printf_buf[450];

char DebugSerial_currentCmd[DebugSerial_cmdMaxLength];
USART_RECEIVE_T  DebugSerial_data[450];
USART_RECEIVE_T* DebugSerial_data_p = DebugSerial_data;

#pragma import(__use_no_semihosting)
//标准库需要的支持函数
struct __FILE
{
	int handle;
};
FILE __stdout;
//定义_sys_exit()以避免使用半主机模式
void _sys_exit(int x)
{
	x = x;
}

// 实现DebugSerial_DebugSerial_printf函数重定向到串口1，即支持DebugSerial_DebugSerial_printf信息到USART1
int fputc(int ch, FILE* f)
{
	while ((USART1->SR & 0X40) == 0); //循环发送,直到发送完毕
	USART1->DR = (unsigned char)ch;
	return ch;
}

void DebugSerial_printf(char* format, ...)
{
	va_list ap;

	va_start(ap, format);
	vsprintf(DebugSerial_printf_buf, format, ap);
	va_end(ap);

	/* 互斥操作 */
	osMutexAcquire(AppPrintfMutexHandle, osWaitForever);
	printf("%s", DebugSerial_printf_buf);
	osMutexRelease(AppPrintfMutexHandle);
}

unsigned int DebugSerial_readAddr(unsigned int addr)
{
	return *(unsigned int*)addr;//	
}
//在指定地址写入指定的值		 
void DebugSerial_writeAddr(unsigned int addr,unsigned int val)
{
	*(unsigned int*)addr=val; 	
}

void DebugSerial_analysisMessage(char* data, unsigned short size)
{
	unsigned char cmdLen=0;
	for(int i=0; i<size; ++i) {
		if (data[i] == ' ') {
			cmdLen = i-1;
			break;
		}
	}
	strncpy(DebugSerial_currentCmd,data,cmdLen);
}
