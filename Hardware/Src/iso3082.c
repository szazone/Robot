/**
  ******************************************************************************
  * @file    iso3082.c
  * @author  szazone
  * @version V0.0.1
  * @date    03-August-2022
  * @brief   ISO3082 Isolated 5-V Full- and Half-Duplex RS-485 Transceivers 
  * 		 Board Support Package source file.
  *
  ******************************************************************************
  */ 

/* Includes ------------------------------------------------------------------*/
#include "iso3082.h"

// Application/MDK-ARM
#include "main.h"
// Drivers/STM32F4xx_HAL_Driver
#include "stm32f4xx_hal_gpio.h"


void ISO3082_Direction(unsigned char dir)
{
	if (dir) {
		HAL_GPIO_WritePin(MCU485_DRE_GPIO_Port, MCU485_DRE_Pin, GPIO_PIN_SET);
	} else {
		HAL_GPIO_WritePin(MCU485_DRE_GPIO_Port, MCU485_DRE_Pin, GPIO_PIN_RESET);
	}
}
