/**
  ******************************************************************************
  * @file    ledTask.h
  * @author  szazone
  * @version V0.0.1
  * @date    03-August-2022
  * @brief   RTOS ledTask head file.
  *
  ******************************************************************************
  */ 

#ifndef __LEDTASK_H__
#define __LEDTASK_H__

#ifdef __cplusplus
	extern "C" {
#endif
/* Includes ------------------------------------------------------------------*/

void StartTaskLed(void *argument);

#ifdef __cplusplus
	}
#endif

#endif	// __LEDTASK_H__
