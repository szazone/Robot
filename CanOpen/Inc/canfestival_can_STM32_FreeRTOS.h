/**
  ******************************************************************************
  * @file    canFestival_timer_STM32_FreeRTOS.h
  * @author  szazone
  * @version V0.0.1
  * @date    03-August-2022
  * @brief   CANFestival STM32 FreeRTOS timer compatible head file.
  *
  ******************************************************************************
  */ 

#ifndef __CANFESTIVAL_TIMER_STM32_FREERTOS_H__
#define __CANFESTIVAL_TIMER_STM32_FREERTOS_H__

#ifdef __cplusplus
	extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
// CanFestival
#include "canfestival.h"

typedef struct
{
	uint8_t Data[8];
}CAN_Msgdata;


unsigned char canInit(void);
unsigned char canSend(CAN_HandleTypeDef *hcan,Message *m);
void CAN_Filter_Init(void);
void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan);

#ifdef __cplusplus
	}
#endif

#endif	// __CANFESTIVAL_TIMER_STM32_FREERTOS_H__
