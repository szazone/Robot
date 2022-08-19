/**
  ******************************************************************************
  * @file    watchdogTask.c
  * @author  szazone
  * @version V0.0.1
  * @date    03-August-2022
  * @brief   RTOS watchdogTask source file.
  *
  ******************************************************************************
  */ 

/* Includes ------------------------------------------------------------------*/
#include "watchdog.h"

// Middlewares/FreeRTOS
#include "cmsis_os2.h"
// Hardware
#include "debugSerial.h"
#include "watchdog.h"
// STD C
#include "stdio.h"

void StartTaskWatchdog(void *argument)
{
	DebugSerial_printf("watchDogTask has started.\r\n");
	
	while (1) {
		Watchdog_feed();
		osDelay(90);
	}
}
