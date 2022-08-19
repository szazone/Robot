/**
  ******************************************************************************
  * @file    serial.h
  * @author  szazone
  * @version V0.0.1
  * @date    03-August-2022
  * @brief   RTOS rs485Tasks head file.
  *
  ******************************************************************************
  */ 

#ifndef __SERIAL_H__
#define __SERIAL_H__

#ifdef __cplusplus
	extern "C" {
#endif
/* Includes ------------------------------------------------------------------*/
// Drivers/STM32F4xx_HAL_Driver
#include "stm32f4xx.h"
// Hardware
#include "iso3082.h"

#define RX_LEN 100
#define TX_LEN 100

#define UART_MAX 6 

typedef struct  
{  
    uint8_t  RX_flag:1;        //IDLE receive flag
    uint8_t  TX_flag:1;        //IDLE send flag
    uint16_t RX_Size;          //receive length
    uint8_t  RX_pData[RX_LEN]; //DMA receive buffer
}USART_RECEIVE_T; 

typedef struct
{  
    uint16_t TX_Size;          //receive length
    uint8_t  TX_pData[TX_LEN]; //DMA receive buffer
}USART_SEND_T;

void Serial_init(void);
void Serial_IDLE(UART_HandleTypeDef *huart);

#ifdef __cplusplus
	}
#endif

#endif	// __SERIAL_H__
