/**
  ******************************************************************************
  * @file    watchdogTask.h
  * @author  szazone
  * @version V0.0.1
  * @date    03-August-2022
  * @brief   RTOS watchdogTask head file.
  *
  ******************************************************************************
  */ 

#ifndef __WATCHDOGTASK_H__
#define __WATCHDOGTASK_H__

#ifdef __cplusplus
	extern "C" {
#endif
/* Includes ------------------------------------------------------------------*/

void StartTaskWatchdog(void *argument);

#ifdef __cplusplus
	}
#endif

#endif	// __WATCHDOGTASK_H__
