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
#include "canFestival_can_STM32_FreeRTOS.h"

// CanFestival
#include "canfestival.h"
#include "timer.h"
// Drivers/STM32F4xx_HAL_Driver
#include "stm32f4xx.h"
// Hardware
#include "debugSerial.h"
// Tasks
#include "canTask.h"

/* CAN1发送与接收数据帧头 */
CAN_TxHeaderTypeDef				CAN1_TxHeaderMessage;
CAN_RxHeaderTypeDef				CAN1_RxHeaderMessage;

/* CAN1发送与接收实际数据 */
CAN_Msgdata can1_tx_msg;
CAN_Msgdata can1_rx_msg;

Message Can1_rxMsg;

unsigned char canInit(void)
{
	CAN_Filter_Init();
	return 0;
}
void CAN_Filter_Init(void)
{
	CAN_FilterTypeDef CAN_FilterInitStructure;

	CAN_FilterInitStructure.FilterActivation       	= ENABLE; 
	CAN_FilterInitStructure.FilterBank				= 0;
	CAN_FilterInitStructure.FilterFIFOAssignment   	= CAN_FILTER_FIFO0;
	CAN_FilterInitStructure.FilterIdHigh           	= 0x0000;
	CAN_FilterInitStructure.FilterIdLow           	= 0x0000;
	CAN_FilterInitStructure.FilterMaskIdHigh        = 0x0000;
	CAN_FilterInitStructure.FilterMaskIdLow         = 0x0000;
	CAN_FilterInitStructure.FilterMode				= CAN_FILTERMODE_IDMASK;
	CAN_FilterInitStructure.FilterScale            	= CAN_FILTERSCALE_32BIT;
	CAN_FilterInitStructure.SlaveStartFilterBank	= 14;
	
	if(HAL_CAN_ConfigFilter(&hcan1, &CAN_FilterInitStructure) != HAL_OK)
	{
		DebugSerial_printf("[ERROR] File: %s Line: %d \r\n",__FILE__, __LINE__);
	}
	if(HAL_CAN_Start(&hcan1) != HAL_OK)
	{
		DebugSerial_printf("[ERROR] File: %s Line: %d \r\n",__FILE__, __LINE__);
	}
	if(HAL_CAN_ActivateNotification(&hcan1, CAN_IT_RX_FIFO0_MSG_PENDING) != HAL_OK)
	{
		DebugSerial_printf("[ERROR] File: %s Line: %d \r\n",__FILE__, __LINE__);
	}
	
}

unsigned char canSend(CAN_HandleTypeDef *hcan,Message *m)
{
	unsigned char i;
	CAN_TxHeaderTypeDef TxMessage;
	uint32_t pTxMailbox;			  	
	 
	if (hcan->Instance == CAN1) {
        TxMessage.RTR = m->rtr; 							  
        TxMessage.IDE = CAN_ID_STD; 	
        TxMessage.StdId = (uint32_t)(m->cob_id);
		TxMessage.ExtId = 0x00;
        TxMessage.DLC = m->len;
		
//		DebugSerial_printf("CAN TX STDID: %03X, data: %02X %02X %02X %02X %02X %02X %02X %02X\r\n",
//						m->cob_id,m->data[0],m->data[1],m->data[2],m->data[3],m->data[4],m->data[5],m->data[6],m->data[7]);
		
		for (i=0;i<m->len;i++) {
			can1_tx_msg.Data[i] = m->data[i];
		}
		
		if (HAL_CAN_AddTxMessage(hcan, &TxMessage, can1_tx_msg.Data, (uint32_t*)&pTxMailbox) != HAL_OK) {
			DebugSerial_printf("[ERROR] CAN1 canSend() StdId:0x%x\r\n",TxMessage.StdId);
			return 1;
		}
	} else if(hcan->Instance == CAN2) {

	}
	return 0;
}
void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan)
{
	if (hcan->Instance == CAN1) {
		/* 得到can接收数据 */
		HAL_CAN_GetRxMessage(hcan,CAN_RX_FIFO0, &CAN1_RxHeaderMessage, can1_rx_msg.Data);
		
		/* 处理can接收数据按照 canDispatch函数要求的数据格式*/
		Can1_rxMsg.cob_id = CAN1_RxHeaderMessage.StdId;
		Can1_rxMsg.len = CAN1_RxHeaderMessage.DLC;
		Can1_rxMsg.rtr = CAN1_RxHeaderMessage.RTR;

		memcpy(Can1_rxMsg.data,can1_rx_msg.Data,CAN1_RxHeaderMessage.DLC);
		canTask_analysisMessage(&Can1_rxMsg);

		canDispatch(CANOpenMasterObject, &(Can1_rxMsg));

	} else if(hcan->Instance == CAN2) {
		
	}
}
