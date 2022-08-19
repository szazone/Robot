/**
  ******************************************************************************
  * @file    led.c
  * @author  szazone
  * @version V0.0.1
  * @date    03-August-2022
  * @brief   LED interface Board Support Package source file.
  *
  ******************************************************************************
  */ 

/* Includes ------------------------------------------------------------------*/
#include "led.h"

// Application/User/Core
#include "main.h"
// Drivers/STM32F4xx_HAL_Driver
#include "stm32f4xx_hal_gpio.h"

void LED_RUNControl(signed char state)
{
	if (state > 0) HAL_GPIO_WritePin(LED_RUN_GPIO_Port, LED_RUN_Pin, GPIO_PIN_SET);
	else if (state == 0) HAL_GPIO_WritePin(LED_RUN_GPIO_Port, LED_RUN_Pin, GPIO_PIN_RESET);
	else HAL_GPIO_TogglePin(LED_RUN_GPIO_Port, LED_RUN_Pin);
}

void LED_ALARMControl(signed char state)
{
	if (state > 0) HAL_GPIO_WritePin(LED_ALARM_GPIO_Port, LED_ALARM_Pin, GPIO_PIN_SET);
	else if (state == 0) HAL_GPIO_WritePin(LED_ALARM_GPIO_Port, LED_ALARM_Pin, GPIO_PIN_RESET);
	else HAL_GPIO_TogglePin(LED_ALARM_GPIO_Port, LED_ALARM_Pin);
}

void LED_ERRORControl(signed char state)
{
	if (state > 0) HAL_GPIO_WritePin(LED_ERROR_GPIO_Port, LED_ERROR_Pin, GPIO_PIN_SET);
	else if (state == 0) HAL_GPIO_WritePin(LED_ERROR_GPIO_Port, LED_ERROR_Pin, GPIO_PIN_RESET);
	else HAL_GPIO_TogglePin(LED_ERROR_GPIO_Port, LED_ERROR_Pin);
}
