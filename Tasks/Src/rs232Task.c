/**
  ******************************************************************************
  * @file    rs232Task.c
  * @author  szazone
  * @version V0.0.1
  * @date    03-August-2022
  * @brief   RTOS rs232Task source file.
  *
  ******************************************************************************
  */ 

/* Includes ------------------------------------------------------------------*/
#include "rs232Task.h"

// Middlewares/FreeRTOS
#include "cmsis_os2.h"
// Hardware
#include "debugSerial.h"
// STD C
#include "stdio.h"

void StartTaskRS232(void *argument)
{
	DebugSerial_printf("rs232Task has started.\r\n");
	
	while (1) {
		osDelay(1);
	}
}
