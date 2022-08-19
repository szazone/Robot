/**
  ******************************************************************************
  * @file    max823.h
  * @author  szazone
  * @version V0.0.1
  * @date    03-August-2022
  * @brief   MAX823 5-Pin Microprocessor Supervisory Circuits With Watchdog Timer
  *			 and Manual Reset Board Support Package source file.
  *
  ******************************************************************************
  */ 

#ifndef __WATCHDOG_H__
#define __WATCHDOG_H__

#ifdef __cplusplus
	extern "C" {
#endif
/* Includes ------------------------------------------------------------------*/
// Drivers/STM32F4xx_HAL_Driver
#include "stm32f4xx.h"

void Watchdog_feed(void);
void Watchdog_reset(void);

#ifdef __cplusplus
	}
#endif

#endif	// __WATCHDOG_H__
