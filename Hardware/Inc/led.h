/**
  ******************************************************************************
  * @file    led.h
  * @author  szazone
  * @version V0.0.1
  * @date    03-August-2022
  * @brief   LED Board Support Package head file.
  *
  ******************************************************************************
  */ 

#ifndef __LED_H__
#define __LED_H__

#ifdef __cplusplus
	extern "C" {
#endif
/* Includes ------------------------------------------------------------------*/
// Drivers/STM32F4xx_HAL_Driver
#include "stm32f4xx.h"

void LED_RUNControl(signed char state);
void LED_ALARMControl(signed char state);
void LED_ERRORControl(signed char state);

#ifdef __cplusplus
	}
#endif

#endif	// __LED_H__
