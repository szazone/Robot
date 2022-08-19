/**
  ******************************************************************************
  * @file    canFestival_timer_STM32_FreeRTOS.c
  * @author  szazone
  * @version V0.0.1
  * @date    03-August-2022
  * @brief   CANFestival STM32 FreeRTOS timer compatible source file.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "canFestival_timer_STM32_FreeRTOS.h"

// Application/User/Core
#include "tim.h"
// Middlewares/FreeRTOS
#include "cmsis_os2.h"
#include "FreeRTOS.h"
#include "queue.h"
// Bsp
#include "motor.h"
// CanOpen
#include "canfestival.h"
// Hardware
#include "canOpen.h"
#include "debugSerial.h"
// STD C
#include <stdbool.h>
#include <stdio.h>
// Tasks
#include "canTask.h"
#include "SysInitTask.h"

extern volatile unsigned long  ulHighFrequencyTimerTicks;
extern osMessageQueueId_t RS485TxQueueHandle;
extern osMessageQueueId_t RS485TxQueueHandle;
extern osMessageQueueId_t USART1TxQueueHandle;
extern osMessageQueueId_t USART1RxQueueHandle;
extern osMessageQueueId_t CAN1TxQueueHandle;

// Store the last timer value to calculate the elapsed time
static TIMEVAL last_time_set = TIMEVAL_MAX;

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
  * @brief  setTimer
  * @param  value:Set time value 0x0000-0xffff
  * @retval NONE
  */
void setTimer(TIMEVAL value)
{
	__HAL_TIM_SetAutoreload(&htim4, value);
}
/**
  * @brief  getElapsedTime
  * @param  NONE
	* @retval TIMEVAL:Return current timer value
  */
TIMEVAL getElapsedTime(void)
{
	uint16_t timer = __HAL_TIM_GetCounter(&htim4);
	return timer > last_time_set ? timer - last_time_set : last_time_set - timer; 	
}

/**
  * @brief  TIM4_start
  * @param  NONE
  * @retval NONE
  */
void TIM4_start(void)
{
	MX_TIM4_Init();
	HAL_TIM_IC_Start_IT(&htim4, TIM_CHANNEL_1);
}
/**
  * @brief  initTimer
  * @param  NONE
  * @retval NONE
  */
void initTimer(void)
{
	TIM4_start();
}


void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
	static uint16_t cnt = 0;	
	if(htim==(&htim4))//
	{
		cnt++;
		last_time_set = __HAL_TIM_GET_COUNTER(htim);
		TimeDispatch();
	}
}

void HAL_TIM4_IRQHandler(void)
{

}

HAL_StatusTypeDef Timer_Init(void)
{
    HAL_StatusTypeDef status[2];

    status[0] = HAL_TIM_Base_Start_IT(&htim5);
	if(status[0] == HAL_OK)
		DebugSerial_printf("[OK] htim5 init sucessed.\r\n");
	else
		DebugSerial_printf("[ERROR] htim5 init failed.\r\n");
	
	status[1] = HAL_TIM_Base_Start_IT(&htim2);
	if(status[1] == HAL_OK)
		DebugSerial_printf("[OK] htim2 init sucessed.\r\n");
	else
		DebugSerial_printf("[ERROR] htim2 init failed.\r\n");
    return (HAL_StatusTypeDef)(status[0]+status[1]);
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	BaseType_t pxHigherPriorityTaskWoken;
	
	if(htim==(&htim2))//定时器2定时10us时间到
	{
		ulHighFrequencyTimerTicks++;
	}
	if(htim==(&htim5)&&SYSInit_finish)//定时器5定时10ms时间到
	{
		Motor_sendRPDO();
		xQueueSendFromISR(CAN1TxQueueHandle, &Can_Msg_SYNCMY_p, &pxHigherPriorityTaskWoken);
		portYIELD_FROM_ISR(pxHigherPriorityTaskWoken);
    }
}
