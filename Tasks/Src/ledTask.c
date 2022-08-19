/**
  ******************************************************************************
  * @file    ledTask.c
  * @author  szazone
  * @version V0.0.1
  * @date    03-August-2022
  * @brief   RTOS ledtasks source file.
  *
  ******************************************************************************
  */ 

/* Includes ------------------------------------------------------------------*/
#include "ledTask.h"

// Middlewares/FreeRTOS
#include "cmsis_os2.h"
// Hardware
#include "led.h"
#include "debugSerial.h"


void StartTaskLed(void *argument)
{
	DebugSerial_printf("ledTask has started.\r\n");
	
	while (1) {
		LED_RUNControl(-1);
		osDelay(250);
	}
}
