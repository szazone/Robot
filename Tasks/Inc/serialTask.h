/**
  ******************************************************************************
  * @file    serialTask.h
  * @author  szazone
  * @version V0.0.1
  * @date    03-August-2022
  * @brief   RTOS serialTask head file.
  *
  ******************************************************************************
  */ 

#ifndef __SERIALTASK_H__
#define __SERIALTASK_H__

#ifdef __cplusplus
	extern "C" {
#endif
/* Includes ------------------------------------------------------------------*/
// Drivers/STM32F4xx_HAL_Driver
#include "stm32f4xx.h"
#include "stm32f4xx_hal_uart.h"

void StartTaskSerial(void *argument);

#ifdef __cplusplus
	}
#endif

#endif	// __SERIALTASK_H__
