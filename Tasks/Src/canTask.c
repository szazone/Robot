/**
  ******************************************************************************
  * @file    canTask.c
  * @author  szazone
  * @version V0.0.1
  * @date    03-August-2022
  * @brief   RTOS canTasks source file.
  *
  ******************************************************************************
  */ 

/* Includes ------------------------------------------------------------------*/
#include "canTask.h"

// Middlewares/FreeRTOS
#include "cmsis_os2.h"
#include "FreeRTOS.h"
#include "queue.h"
// Bsp
#include "magneticSensor.h"
#include "motor.h"
// CanOpen
#include "canFestival_can_STM32_FreeRTOS.h"
#include "canFestival_timer_STM32_FreeRTOS.h"
// Hardware
#include "canOpen.h"
#include "debugSerial.h"
// STD C
#include "stdio.h"

Message Can_Msg_SYNCMY;
Message *Can_Msg_SYNCMY_p = &Can_Msg_SYNCMY;

Message Can1_TxMsgInit = {0};
Message *Can1_TxMsg = &Can1_TxMsgInit;

CAN_HandleTypeDef *CANOpen_hcan;
extern osMessageQueueId_t CAN1TxQueueHandle;

void canTask_init(void)
{
	CANOpen_hcan = &hcan1;
	
	Timer_Init();
	initTimer();
	CANOpenMasterObject->canHandle = CANOpen_hcan->Instance;
	setState(CANOpenMasterObject,Initialisation);
	setNodeId (CANOpenMasterObject, 127);
	canInit();
	CANOpen_initSTDOD();	
	CANOpen_MasterSYNC(Can_Msg_SYNCMY_p);	// 同步报文
	
	
	DebugSerial_printf("canTask init sucessed.\r\n");
}

void StartTaskCan(void *argument)
{
	canTask_init();
	DebugSerial_printf("canTask has started.\r\n");
	
	while (1) {
		if (xQueueReceive(CAN1TxQueueHandle,&Can1_TxMsg,10) == pdPASS) {
			canSend(CANOpen_hcan, Can1_TxMsg);
		}
	}
}

void canTask_analysisMessage(Message * RxMSG)
{	
//	DebugSerial_printf("CAN RX STDID: %03X, data: %02X %02X %02X %02X %02X %02X %02X %02X\r\n",
//		RxMSG->cob_id,RxMSG->data[0],RxMSG->data[1],RxMSG->data[2],RxMSG->data[3],RxMSG->data[4],RxMSG->data[5],RxMSG->data[6],RxMSG->data[7]);
	
	if (RxMSG->cob_id == 0x000) {	// NMT
		
	} else if (RxMSG->cob_id == 0x080) {	// SYNC
		
	} else if (RxMSG->cob_id>=0x081 && RxMSG->cob_id<=0x0FF) {	// EMCY
		
	} else if (RxMSG->cob_id == 0x100) {	// TIME
		
	} else if (RxMSG->cob_id>=0x700 && RxMSG->cob_id<=0x77F) {	// NMT error contro
		
	} else {
		unsigned char nodeId;
		
		if (RxMSG->cob_id>=0x180 && RxMSG->cob_id<=0x1FF) nodeId = RxMSG->cob_id - 0x180;		// PDO1
		else if (RxMSG->cob_id>=0x280 && RxMSG->cob_id<=0x2FF) nodeId = RxMSG->cob_id - 0x280;	// PDO2
		else if (RxMSG->cob_id>=0x380 && RxMSG->cob_id<=0x3FF) nodeId = RxMSG->cob_id - 0x280;	// PDO3
		else if (RxMSG->cob_id>=0x480 && RxMSG->cob_id<=0x4FF) nodeId = RxMSG->cob_id - 0x480;	// PDO4
		else if (RxMSG->cob_id>=0x581 && RxMSG->cob_id<=0x5FF) nodeId = RxMSG->cob_id - 0x580;	// SDO
		else nodeId =0;
		
		if (nodeId == Motor_nodeId[0] || nodeId == Motor_nodeId[1]) {
			Motor_analysisMessage(RxMSG);
		} else if (nodeId == MagneticSensor_nodeId[0]
			|| nodeId == MagneticSensor_nodeId[1])
		{
			MagneticSensor_analysisMessage(RxMSG);
		} 
//		else if (nodeId == RFIDSensor_nodeId[0])
//		{
//			RFIDSensor_analysisMessage(RxMSG);
//		}
	}
}
