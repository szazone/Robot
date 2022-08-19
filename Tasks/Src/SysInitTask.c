/**
  ******************************************************************************
  * @file    SysInitTask.c
  * @author  szazone
  * @version V0.0.1
  * @date    03-August-2022
  * @brief   RTOS SysInitTask source file.
  *
  ******************************************************************************
  */ 

/* Includes ------------------------------------------------------------------*/
#include "SysInitTask.h"

// Middlewares/FreeRTOS
#include "cmsis_os2.h"
// Bsp
#include "magneticSensor.h"
#include "motor.h"
// Hardware
#include "debugSerial.h"
#include "led.h"
#include "watchdog.h"
// STD C
#include "stdbool.h"
#include "stdio.h"

extern osThreadId_t TaskSysInitHandle;

bool SYSInit_finish = false;

void StartTaskSYSInit(void *argument)
{
	Motor_init();
	MagneticSensor_init();
	
	Motor_setSpeed(0,0);
	Motor_setSpeed(1,0);
	
	SYSInit_finish = true;
	DebugSerial_printf("SYSInit has completed.\r\n");
	osThreadTerminate(TaskSysInitHandle);
}
