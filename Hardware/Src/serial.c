/**
  ******************************************************************************
  * @file    serial.c
  * @author  szazone
  * @version V0.0.1
  * @date    03-August-2022
  * @brief	 Serial ports source file.
  *
  ******************************************************************************
  */ 

/* Includes ------------------------------------------------------------------*/
#include "serial.h"

// Application/User/Core
#include "usart.h"
// Drivers/STM32F4xx_HAL_Driver
#include "stm32f4xx_hal_uart.h"
// Middlewares/FreeRTOS
#include "cmsis_os2.h"
#include "FreeRTOS.h"
#include "queue.h"
#include "portmacro.h"
// Hardware
#include "debugSerial.h"

extern osMessageQueueId_t USART1RxQueueHandle;

USART_RECEIVE_T UartReceivebuff[UART_MAX];
USART_RECEIVE_T *UartReceiveData[UART_MAX] = {&UartReceivebuff[0],&UartReceivebuff[1],&UartReceivebuff[2],&UartReceivebuff[3],&UartReceivebuff[4],&UartReceivebuff[5]};

USART_SEND_T UartSendbuff[UART_MAX];
USART_SEND_T *UartSendData[UART_MAX] = {&UartSendbuff[0],&UartSendbuff[1],&UartSendbuff[2],&UartSendbuff[3],&UartSendbuff[4],&UartSendbuff[5]};


HAL_StatusTypeDef Serial_Receive_DMA_EN(UART_HandleTypeDef *huart)
{

    HAL_StatusTypeDef status;

    /* 清除串口空闲中断标志 */
    __HAL_UART_CLEAR_IDLEFLAG(huart);
    
    /* 配置非阻塞模式下串口 DMA接收 */
    if(huart->Instance==USART1)
       status = HAL_UART_Receive_DMA(huart,UartReceiveData[0]->RX_pData,RX_LEN);
    else if(huart->Instance==USART2)
       status = HAL_UART_Receive_DMA(huart,UartReceiveData[1]->RX_pData,RX_LEN);
    else if(huart->Instance==UART4)
       status = HAL_UART_Receive_DMA(huart,UartReceiveData[3]->RX_pData,RX_LEN);
    else if(huart->Instance==UART5)
       status = HAL_UART_Receive_DMA(huart,UartReceiveData[4]->RX_pData,RX_LEN);
    else if(huart->Instance==USART6)
       status = HAL_UART_Receive_DMA(huart,UartReceiveData[5]->RX_pData,RX_LEN);
    
    /* 使能串口空闲中断 */
    __HAL_UART_ENABLE_IT(huart, UART_IT_IDLE);

    return status;	
}

void Serial_init(void)
{
    /* 串口初始化 */
    if (Serial_Receive_DMA_EN(&huart1) == HAL_OK)
        DebugSerial_printf("[OK] USART1 init sucessed.\r\n");
    else
        DebugSerial_printf("[ERROR] USART1 init failed.\r\n");
    if (Serial_Receive_DMA_EN(&huart2) == HAL_OK)
        DebugSerial_printf("[OK] USART2 init sucessed.\r\n");
    else
        DebugSerial_printf("[ERROR] USART2 init failed.\r\n");
    if (Serial_Receive_DMA_EN(&huart4) == HAL_OK)
        DebugSerial_printf("[OK] UART4 init sucessed.\r\n");
    else
        DebugSerial_printf("[ERROR] UART4 init failed.\r\n");
    if (Serial_Receive_DMA_EN(&huart5) == HAL_OK)
        DebugSerial_printf("[OK] UART5 init sucessed.\r\n");
    else
        DebugSerial_printf("[ERROR] UART5 init failed.\r\n");
    if (Serial_Receive_DMA_EN(&huart6) == HAL_OK)
        DebugSerial_printf("[OK] USART6 init sucessed.\r\n");
    else
        DebugSerial_printf("[ERROR] USART6 init failed.\r\n");
	
}

void Serial_IDLE(UART_HandleTypeDef *huart)
{  
    unsigned int temp;  
    BaseType_t pxHigherPriorityTaskWoken;

    if ((__HAL_UART_GET_FLAG(huart,UART_FLAG_IDLE) != RESET)) {   
        __HAL_UART_CLEAR_IDLEFLAG(huart);  
        HAL_UART_DMAStop(huart);  
        temp = (*huart).hdmarx->Instance->NDTR;
        if (huart->Instance==USART1) {
			UartReceiveData[0]->RX_Size = RX_LEN - temp;
			UartReceiveData[0]->RX_flag = 1; 
            xQueueSendFromISR(USART1RxQueueHandle, (unsigned int*)&UartReceiveData[0], &pxHigherPriorityTaskWoken);
			portYIELD_FROM_ISR(pxHigherPriorityTaskWoken);
			HAL_UART_Receive_DMA(huart,UartReceiveData[0]->RX_pData,RX_LEN);
        } else if(huart->Instance==USART2) {
			
        } else if (huart->Instance==USART3) {

        } else if (huart->Instance==UART4) {
           
		} else if (huart->Instance==UART5) {
			
        } else if (huart->Instance==USART6) {
			
        }  
    } 
 
}
