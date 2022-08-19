/**
  ******************************************************************************
  * @file    canFestival_timer_STM32_FreeRTOS.h
  * @author  szazone
  * @version V0.0.1
  * @date    03-August-2022
  * @brief   CANFestival STM32 FreeRTOS CAN Hardware compatible head file.
  *
  ******************************************************************************
  */ 

#ifndef __CANFESTIVAL_CAN_STM32_FREERTOS_H__
#define __CANFESTIVAL_CAN_STM32_FREERTOS_H__

#ifdef __cplusplus
	extern "C" {
#endif
/* Includes ------------------------------------------------------------------*/
// CanOpen
#include "canfestival.h" 
#include "timer.h"
// Drivers/STM32F4xx_HAL_Driver
#include "stm32f4xx.h"
// Middlewares/FreeRTOS
#include "cmsis_os2.h"

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim);
HAL_StatusTypeDef Timer_Init(void);
void initTimer(void);

#ifdef __cplusplus
	}
#endif

#endif	// __CANFESTIVAL_CAN_STM32_FREERTOS_H__
