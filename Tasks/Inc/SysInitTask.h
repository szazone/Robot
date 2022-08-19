/**
  ******************************************************************************
  * @file    SysainitTask.h
  * @author  szazone
  * @version V0.0.1
  * @date    03-August-2022
  * @brief   RTOS SysInitTask head file.
  *
  ******************************************************************************
  */ 

#ifndef __SYSINITTASK_H__
#define __SYSINITTASK_H__

#ifdef __cplusplus
	extern "C" {
#endif
/* Includes ------------------------------------------------------------------*/
// STD C
#include "stdbool.h"

extern bool SYSInit_finish;

void StartTaskSYSInit(void *argument);

#ifdef __cplusplus
	}
#endif

#endif	// __SYSINITTASK_H__
