/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */
volatile unsigned long ulHighFrequencyTimerTicks;
/* USER CODE END Variables */
/* Definitions for TaskSysInit */
osThreadId_t TaskSysInitHandle;
const osThreadAttr_t TaskSysInit_attributes = {
  .name = "TaskSysInit",
  .stack_size = 512 * 4,
  .priority = (osPriority_t) osPriorityHigh,
};
/* Definitions for ledTask */
osThreadId_t ledTaskHandle;
const osThreadAttr_t ledTask_attributes = {
  .name = "ledTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for canTask */
osThreadId_t canTaskHandle;
const osThreadAttr_t canTask_attributes = {
  .name = "canTask",
  .stack_size = 512 * 4,
  .priority = (osPriority_t) osPriorityHigh,
};
/* Definitions for watchdogTask */
osThreadId_t watchdogTaskHandle;
const osThreadAttr_t watchdogTask_attributes = {
  .name = "watchdogTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for rs232Task */
osThreadId_t rs232TaskHandle;
const osThreadAttr_t rs232Task_attributes = {
  .name = "rs232Task",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for rs485Task */
osThreadId_t rs485TaskHandle;
const osThreadAttr_t rs485Task_attributes = {
  .name = "rs485Task",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for serialTask */
osThreadId_t serialTaskHandle;
const osThreadAttr_t serialTask_attributes = {
  .name = "serialTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for motionTask */
osThreadId_t motionTaskHandle;
const osThreadAttr_t motionTask_attributes = {
  .name = "motionTask",
  .stack_size = 512 * 4,
  .priority = (osPriority_t) osPriorityRealtime,
};
/* Definitions for RS485TxQueue */
osMessageQueueId_t RS485TxQueueHandle;
const osMessageQueueAttr_t RS485TxQueue_attributes = {
  .name = "RS485TxQueue"
};
/* Definitions for RS485RxQueue */
osMessageQueueId_t RS485RxQueueHandle;
const osMessageQueueAttr_t RS485RxQueue_attributes = {
  .name = "RS485RxQueue"
};
/* Definitions for USART1TxQueue */
osMessageQueueId_t USART1TxQueueHandle;
const osMessageQueueAttr_t USART1TxQueue_attributes = {
  .name = "USART1TxQueue"
};
/* Definitions for USART1RxQueue */
osMessageQueueId_t USART1RxQueueHandle;
const osMessageQueueAttr_t USART1RxQueue_attributes = {
  .name = "USART1RxQueue"
};
/* Definitions for USART2TxQueue */
osMessageQueueId_t USART2TxQueueHandle;
const osMessageQueueAttr_t USART2TxQueue_attributes = {
  .name = "USART2TxQueue"
};
/* Definitions for USART4TxQueue */
osMessageQueueId_t USART4TxQueueHandle;
const osMessageQueueAttr_t USART4TxQueue_attributes = {
  .name = "USART4TxQueue"
};
/* Definitions for USART4RxQueue */
osMessageQueueId_t USART4RxQueueHandle;
const osMessageQueueAttr_t USART4RxQueue_attributes = {
  .name = "USART4RxQueue"
};
/* Definitions for USART6TxQueue */
osMessageQueueId_t USART6TxQueueHandle;
const osMessageQueueAttr_t USART6TxQueue_attributes = {
  .name = "USART6TxQueue"
};
/* Definitions for USART6RxQueue */
osMessageQueueId_t USART6RxQueueHandle;
const osMessageQueueAttr_t USART6RxQueue_attributes = {
  .name = "USART6RxQueue"
};
/* Definitions for USART2RxQueue */
osMessageQueueId_t USART2RxQueueHandle;
const osMessageQueueAttr_t USART2RxQueue_attributes = {
  .name = "USART2RxQueue"
};
/* Definitions for CAN1TxQueue */
osMessageQueueId_t CAN1TxQueueHandle;
const osMessageQueueAttr_t CAN1TxQueue_attributes = {
  .name = "CAN1TxQueue"
};
/* Definitions for AppPrintfMutex */
osMutexId_t AppPrintfMutexHandle;
const osMutexAttr_t AppPrintfMutex_attributes = {
  .name = "AppPrintfMutex"
};
/* Definitions for AppVelocityMutex */
osMutexId_t AppVelocityMutexHandle;
const osMutexAttr_t AppVelocityMutex_attributes = {
  .name = "AppVelocityMutex"
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */
osMessageQueueId_t SysErrorQueueHandle;
const osMessageQueueAttr_t SysErrorQueue_attributes = {
  .name = "SysErrorQueue"
};
/* USER CODE END FunctionPrototypes */

void StartTaskSYSInit(void *argument);
void StartTaskLed(void *argument);
void StartTaskCan(void *argument);
void StartTaskWatchdog(void *argument);
void StartTaskRS232(void *argument);
void StartTaskRS485(void *argument);
void StartTaskSerial(void *argument);
void StartTaskMotion(void *argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */
  /* Create the mutex(es) */
  /* creation of AppPrintfMutex */
  AppPrintfMutexHandle = osMutexNew(&AppPrintfMutex_attributes);

  /* creation of AppVelocityMutex */
  AppVelocityMutexHandle = osMutexNew(&AppVelocityMutex_attributes);

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* Create the queue(s) */
  /* creation of RS485TxQueue */
  RS485TxQueueHandle = osMessageQueueNew (10, sizeof(uint32_t), &RS485TxQueue_attributes);

  /* creation of RS485RxQueue */
  RS485RxQueueHandle = osMessageQueueNew (10, sizeof(uint32_t), &RS485RxQueue_attributes);

  /* creation of USART1TxQueue */
  USART1TxQueueHandle = osMessageQueueNew (10, sizeof(uint32_t), &USART1TxQueue_attributes);

  /* creation of USART1RxQueue */
  USART1RxQueueHandle = osMessageQueueNew (10, sizeof(uint32_t), &USART1RxQueue_attributes);

  /* creation of USART2TxQueue */
  USART2TxQueueHandle = osMessageQueueNew (10, sizeof(uint32_t), &USART2TxQueue_attributes);

  /* creation of USART4TxQueue */
  USART4TxQueueHandle = osMessageQueueNew (10, sizeof(uint32_t), &USART4TxQueue_attributes);

  /* creation of USART4RxQueue */
  USART4RxQueueHandle = osMessageQueueNew (10, sizeof(uint32_t), &USART4RxQueue_attributes);

  /* creation of USART6TxQueue */
  USART6TxQueueHandle = osMessageQueueNew (10, sizeof(uint32_t), &USART6TxQueue_attributes);

  /* creation of USART6RxQueue */
  USART6RxQueueHandle = osMessageQueueNew (10, sizeof(uint32_t), &USART6RxQueue_attributes);

  /* creation of USART2RxQueue */
  USART2RxQueueHandle = osMessageQueueNew (10, sizeof(uint32_t), &USART2RxQueue_attributes);

  /* creation of CAN1TxQueue */
  CAN1TxQueueHandle = osMessageQueueNew (10, sizeof(uint32_t), &CAN1TxQueue_attributes);

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  SysErrorQueueHandle = osMessageQueueNew (10, sizeof(uint32_t), &SysErrorQueue_attributes);
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of TaskSysInit */
  TaskSysInitHandle = osThreadNew(StartTaskSYSInit, NULL, &TaskSysInit_attributes);

  /* creation of ledTask */
  ledTaskHandle = osThreadNew(StartTaskLed, NULL, &ledTask_attributes);

  /* creation of canTask */
  canTaskHandle = osThreadNew(StartTaskCan, NULL, &canTask_attributes);

  /* creation of watchdogTask */
  watchdogTaskHandle = osThreadNew(StartTaskWatchdog, NULL, &watchdogTask_attributes);

  /* creation of rs232Task */
  rs232TaskHandle = osThreadNew(StartTaskRS232, NULL, &rs232Task_attributes);

  /* creation of rs485Task */
  rs485TaskHandle = osThreadNew(StartTaskRS485, NULL, &rs485Task_attributes);

  /* creation of serialTask */
  serialTaskHandle = osThreadNew(StartTaskSerial, NULL, &serialTask_attributes);

  /* creation of motionTask */
  motionTaskHandle = osThreadNew(StartTaskMotion, NULL, &motionTask_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

}

/* USER CODE BEGIN Header_StartTaskSYSInit */
/**
  * @brief  Function implementing the TaskSysInit thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartTaskSYSInit */
__weak void StartTaskSYSInit(void *argument)
{
  /* USER CODE BEGIN StartTaskSYSInit */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END StartTaskSYSInit */
}

/* USER CODE BEGIN Header_StartTaskLed */
/**
* @brief Function implementing the ledTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartTaskLed */
__weak void StartTaskLed(void *argument)
{
  /* USER CODE BEGIN StartTaskLed */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END StartTaskLed */
}

/* USER CODE BEGIN Header_StartTaskCan */
/**
* @brief Function implementing the canTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartTaskCan */
__weak void StartTaskCan(void *argument)
{
  /* USER CODE BEGIN StartTaskCan */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END StartTaskCan */
}

/* USER CODE BEGIN Header_StartTaskWatchdog */
/**
* @brief Function implementing the watchdogTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartTaskWatchdog */
__weak void StartTaskWatchdog(void *argument)
{
  /* USER CODE BEGIN StartTaskWatchdog */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END StartTaskWatchdog */
}

/* USER CODE BEGIN Header_StartTaskRS232 */
/**
* @brief Function implementing the rs232Task thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartTaskRS232 */
__weak void StartTaskRS232(void *argument)
{
  /* USER CODE BEGIN StartTaskRS232 */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END StartTaskRS232 */
}

/* USER CODE BEGIN Header_StartTaskRS485 */
/**
* @brief Function implementing the rs485Task thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartTaskRS485 */
__weak void StartTaskRS485(void *argument)
{
  /* USER CODE BEGIN StartTaskRS485 */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END StartTaskRS485 */
}

/* USER CODE BEGIN Header_StartTaskSerial */
/**
* @brief Function implementing the serialTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartTaskSerial */
__weak void StartTaskSerial(void *argument)
{
  /* USER CODE BEGIN StartTaskSerial */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END StartTaskSerial */
}

/* USER CODE BEGIN Header_StartTaskMotion */
/**
* @brief Function implementing the motionTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartTaskMotion */
__weak void StartTaskMotion(void *argument)
{
  /* USER CODE BEGIN StartTaskMotion */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END StartTaskMotion */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

