/**
  ******************************************************************************
  * @file    rs485Task.c
  * @author  szazone
  * @version V0.0.1
  * @date    03-August-2022
  * @brief   RTOS rs485Task source file.
  *
  ******************************************************************************
  */ 

/* Includes ------------------------------------------------------------------*/
#include "rs485Task.h"

// Application/User/Core
#include "usart.h"
// Drivers/STM32F4xx_HAL_Driver
#include "stm32f4xx_hal_uart.h"
// Middlewares/FreeRTOS
#include "cmsis_os2.h"
#include "FreeRTOS.h"
#include "queue.h"
// Hardware
#include "debugSerial.h"
#include "serial.h"
// STD C
#include "stdio.h"

extern osMessageQueueId_t RS485TxQueueHandle;

UART_HandleTypeDef *RS485_huart;								// RS485 使用的串口
unsigned char RS485_rx_buffer[RS485_RX_BUFFER_SIZE];			// 串口通信-485 报文接收
unsigned char RS485_tx_buffer[RS485_TX_BUFFER_SIZE];			// 串口通信-485 报文发送

USART_SEND_T TxDataInit[3];
USART_SEND_T * RS485SendMsg = &TxDataInit[2];

USART_RECEIVE_T RS485Receivebuff;

void rs485Task_init(void)
{
	RS485_huart = &huart5;
	
	__HAL_UART_CLEAR_IDLEFLAG(RS485_huart);									//使能IDLE中断	
	HAL_UART_Receive_DMA(RS485_huart,RS485_rx_buffer,RS485_RX_BUFFER_SIZE);	// 打开dma接收，收据存入 RS485_rx_buffer
	__HAL_UART_ENABLE_IT(RS485_huart, UART_IT_IDLE);
}

unsigned char RS485_Transmit(uint8_t *pData, uint16_t Size)
{
	HAL_StatusTypeDef ret;
    /* RS485发送使能 */
    RS485TXEN();

    taskENTER_CRITICAL();
	ret = HAL_UART_Transmit(RS485_huart, pData, Size,0XFFFF);   
    taskEXIT_CRITICAL();
	RS485RXEN();
    return ret; 
}

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
    /* RS485串口发送完成后重新进行接收使能 */
	if (huart->Instance == RS485_huart->Instance) {
	    RS485RXEN();
	}
    huart->gState = HAL_UART_STATE_READY;
}

void StartTaskRS485(void *argument)
{
	rs485Task_init();
	DebugSerial_printf("rs485Task has started.\r\n");
	
	while (1) {
		if (xQueueReceive(RS485TxQueueHandle,&RS485SendMsg,200) == pdPASS) {
			RS485_Transmit(RS485SendMsg->TX_pData, RS485SendMsg->TX_Size);
		}
	}
}

