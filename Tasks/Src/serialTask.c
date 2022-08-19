/**
  ******************************************************************************
  * @file    serialTask.c
  * @author  szazone
  * @version V0.0.1
  * @date    03-August-2022
  * @brief   RTOS ledtasks source file.
  *
  ******************************************************************************
  */ 

/* Includes ------------------------------------------------------------------*/
#include "serialTask.h"

// Application/User/Core
#include "usart.h"
// Middlewares/FreeRTOS
#include "cmsis_os2.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
// Hardware
#include "debugSerial.h"
#include "serial.h"

extern osMessageQueueId_t USART1RxQueueHandle;


void StartTaskSerial(void *argument)
{
	Serial_init();
	
	DebugSerial_printf("[OK] serialTask has started.\r\n");
	
	while (1) {
		if (xQueueReceive(USART1RxQueueHandle,&DebugSerial_data_p,100) == pdTRUE) {
			DebugSerial_analysisMessage((char*)DebugSerial_data_p->RX_pData, DebugSerial_data_p->RX_Size);
			
		}
	}
}
