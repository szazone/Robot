/**
  ******************************************************************************
  * @file    max823.c
  * @author  szazone
  * @version V0.0.1
  * @date    03-August-2022
  * @brief   MAX823 5-Pin Microprocessor Supervisory Circuits With Watchdog Timer
  *			 and Manual Reset Board Support Package source file.
  *
  ******************************************************************************
  */ 

/* Includes ------------------------------------------------------------------*/
#include "watchdog.h"

// Application/User/Core
#include "main.h"
// Drivers/STM32F4xx_HAL_Driver
#include "stm32f4xx_hal_gpio.h"
#include "stm32f4xx_hal_gpio_ex.h"
// Middlewares/FreeRTOS
#include "cmsis_os2.h"

void Watchdog_feed(void)
{
	HAL_GPIO_TogglePin(WDI_GPIO_Port, WDI_Pin);
	osDelay(5);
	HAL_GPIO_TogglePin(WDI_GPIO_Port, WDI_Pin);
	osDelay(5);
}

void Watchdog_reset(void)
{
//	HAL_GPIO_WritePin(MAX823_Structure->MR_GPIOx, MAX823_Structure->MR_PIN, GPIO_PIN_RESET);
//	osDelay(50);
//	HAL_GPIO_WritePin(MAX823_Structure->MR_GPIOx, MAX823_Structure->MR_PIN, GPIO_PIN_SET);
}
