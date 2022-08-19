/**
  ******************************************************************************
  * @file    CNG_MGS_160N.c
  * @author  szazone
  * @version V0.0.1
  * @date    03-August-2022
  * @brief   HINSON CNG_MGS_160N magnetic sensor source file.
  *
  ******************************************************************************
  */ 

/* Includes ------------------------------------------------------------------*/
#include "CNG_MGS_160N.h"

// Application/User/Core
#include "main.h"
// CanOpen
#include "def.h"
// Hardware
#include "canOpen.h"
#include "Hinson_CNS_MGS.h"
// Middlewares/FreeRTOS
#include "cmsis_os2.h"
#include "FreeRTOS.h"
#include "queue.h"
// STD C
#include "stdio.h"

extern osMessageQueueId_t CAN1TxQueueHandle;

void CNG_MGS_160N_init(unsigned char nodeId)
{
	CANOpen_NMTManagement(nodeId, NMT_Reset_Node);
	osDelay(5);
	CANOpen_NMTManagement(nodeId, NMT_Enter_PreOperational);
	osDelay(5);
	CNG_MGS_160N_config(nodeId);
	CANOpen_NMTManagement(nodeId, NMT_Start_Node);
	osDelay(5);
}

void CNG_MGS_160N_config(unsigned char nodeId)
{
	Message *m;
	
	Hinson_CNS_MGS_MinPointNumber.data.data = 1;	// 最小感应点数
	CANOpen_MasterWriteOD2Message(nodeId,Hinson_CNS_MGS_MinPointNumber, m);
	xQueueSend(CAN1TxQueueHandle, m, 100);
	osDelay(5);
	
	Hinson_CNS_MGS_MaxPointNumber.data.data = 16;	// 最大感应点数
	CANOpen_MasterWriteOD2Message(nodeId,Hinson_CNS_MGS_MaxPointNumber, m);
	xQueueSend(CAN1TxQueueHandle, m, 100);
	osDelay(5);
	
	Hinson_CNS_MGS_WriteCommand.data.data = 0;	// 参数写入
	CANOpen_MasterWriteOD2Message(nodeId,Hinson_CNS_MGS_WriteCommand, m);
	xQueueSend(CAN1TxQueueHandle, m, 100);
	osDelay(5);
	
	Hinson_CNS_MGS_RebootSensor.data.data = 0;	// 重启传感器
	CANOpen_MasterWriteOD2Message(nodeId,Hinson_CNS_MGS_RebootSensor, m);
	xQueueSend(CAN1TxQueueHandle, m, 100);
	osDelay(5);
}
