/**
  ******************************************************************************
  * @file    canTask.h
  * @author  szazone
  * @version V0.0.1
  * @date    03-August-2022
  * @brief   RTOS motionTask head file.
  *
  ******************************************************************************
  */ 

#ifndef __CANTASK_H__
#define __CANTASK_H__

#ifdef __cplusplus
	extern "C" {
#endif
/* Includes ------------------------------------------------------------------*/
// Application/User/Core
#include "can.h"

extern Message *Can_Msg_SYNCMY_p;

void StartTaskCan(void *argument);
void canTask_analysisMessage(Message * RxMSG);

#ifdef __cplusplus
	}
#endif

#endif	// __CANTASK_H__
