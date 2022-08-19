/**
  ******************************************************************************
  * @file    rs485Task.h
  * @author  szazone
  * @version V0.0.1
  * @date    03-August-2022
  * @brief   RTOS rs485Tasks head file.
  *
  ******************************************************************************
  */ 

#ifndef __RS485TASK_H__
#define __RS485TASK_H__

#ifdef __cplusplus
	extern "C" {
#endif
/* Includes ------------------------------------------------------------------*/
// Hardware
#include "iso3082.h"

#define RS485_RX_BUFFER_SIZE 64
#define RS485_TX_BUFFER_SIZE 64

#define RS485TXEN() ISO3082_Direction(1)
#define RS485RXEN() ISO3082_Direction(0)

void StartTaskRS485(void *argument);

#ifdef __cplusplus
	}
#endif

#endif	// __RS485TASK_H__
