/**
  ******************************************************************************
  * @file    CANOpenObjDictConfig.c
  * @author  Zhenglin R&D Driver Software Team
  * @version V1.0.0
  * @date    26/04/2015
  * @brief   This file is CANOpenObjDictConfig file.
  ******************************************************************************
  */
	
/* Includes ------------------------------------------------------------------*/
#include "CANOpenObjDictConfig.h"
//#include "can_stm32.h" //20190408 FreeRTOS ÒÆÖ² CANopen
#include "canFestival_can_STM32_FreeRTOS.h"
#include "canFestival_timer_STM32_FreeRTOS.h"
#include "tim.h"
#include "SEGGER_RTT.h"
#include "TestMaster.h"
#include "ObjDict.h"
#include "GlobalVar.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/*Froward declaration*/

/**
  * @brief  Master_heartbeatError.
  * @param  d:CANOpen object dictionary. heartbeatID:Node id
  * @retval None
  */
void Master_heartbeatError(CO_Data* d, UNS8 heartbeatID)
{
	SEGGER_RTT_printf(0, "Master_heartbeatError %d\n", heartbeatID);
}

/**
  * @brief  Master_initialisation.
  * @param  d:CANOpen object dictionary.
  * @retval None
  */
void Master_initialisation(CO_Data* d)
{
	UNS32 RPDO1_COBID = 0x0181; //NODEID3+0X180H
	UNS32 RPDO2_COBID = 0x0281;//NODEID+0X200H
	UNS32 RPDO3_COBID = 0x0182; 
	UNS32 RPDO4_COBID = 0x0282;
	UNS32 size = sizeof(UNS32); 
	UNS8 unsize = sizeof(unsize); 
	UNS8  TpdoTransmissionType = 0;//receiving is synchronous, process after next reception of SYNC object
	
	TpdoTransmissionType = TpdoTransmissionType;
	SEGGER_RTT_printf(0, "Master_initialisation\n");

	/*****************************************
	 * Define RPDOs to match slave ID=1 TPDOs*
	 *****************************************/
	writeLocalDict( d, /*CO_Data* d*/
			0x1400, /*UNS16 index*/
			0x01, /*UNS8 subind*/ 
			&RPDO3_COBID, /*void * pSourceData,*/ 
			&size, /* UNS8 * pExpectedSize*/
			RW);  /* UNS8 checkAccess */
	TpdoTransmissionType = TRANS_EVERY_N_SYNC(1);	
	writeLocalDict( d, /*CO_Data* d*/
			0x1400, /*UNS16 index*/
			0x02, /*UNS8 subind*/ 
			&TpdoTransmissionType, /*void * pSourceData,*/ 
			(UNS32*)&unsize, /* UNS8 * pExpectedSize*/
			RW);  /* UNS8 checkAccess */
			
	writeLocalDict( d, /*CO_Data* d*/
			0x1401, /*UNS16 index*/
			0x01, /*UNS8 subind*/ 
			&RPDO4_COBID, /*void * pSourceData,*/ 
			&size, /* UNS8 * pExpectedSize*/
			RW);  /* UNS8 checkAccess */
	TpdoTransmissionType = TRANS_EVERY_N_SYNC(1);	
	writeLocalDict( d, /*CO_Data* d*/
			0x1401, /*UNS16 index*/
			0x02, /*UNS8 subind*/ 
			&TpdoTransmissionType, /*void * pSourceData,*/ 
			(UNS32*)&unsize, /* UNS8 * pExpectedSize*/
			RW);  /* UNS8 checkAccess */
	
	/*****************************************
	 * Define RPDOs to match slave ID=2 TPDOs*
	 *****************************************/
	writeLocalDict( d, /*CO_Data* d*/
			0x1400, /*UNS16 index*/
			0x01, /*UNS8 subind*/ 
			&RPDO1_COBID, /*void * pSourceData,*/ 
			&size, /* UNS8 * pExpectedSize*/
			RW);  /* UNS8 checkAccess */
	TpdoTransmissionType = TRANS_EVERY_N_SYNC(1);	
	writeLocalDict( d, /*CO_Data* d*/
			0x1400, /*UNS16 index*/
			0x02, /*UNS8 subind*/ 
			&TpdoTransmissionType, /*void * pSourceData,*/ 
			(UNS32*)&unsize, /* UNS8 * pExpectedSize*/
			RW);  /* UNS8 checkAccess */
			
	writeLocalDict( d, /*CO_Data* d*/
			0x1401, /*UNS16 index*/
			0x01, /*UNS8 subind*/ 
			&RPDO2_COBID, /*void * pSourceData,*/ 
			&size, /* UNS8 * pExpectedSize*/
			RW);  /* UNS8 checkAccess */
	TpdoTransmissionType = TRANS_EVERY_N_SYNC(1);	
	writeLocalDict( d, /*CO_Data* d*/
			0x1401, /*UNS16 index*/
			0x02, /*UNS8 subind*/ 
			&TpdoTransmissionType, /*void * pSourceData,*/ 
			(UNS32*)&unsize, /* UNS8 * pExpectedSize*/
			RW);  /* UNS8 checkAccess */
			
//	writeLocalDict( d, /*CO_Data* d*/
//			0x1800, /*UNS16 index*/
//			0x01, /*UNS8 subind*/ 
//			&TPDO1_COBID, /*void * pSourceData,*/ 
//			&size, /* UNS8 * pExpectedSize*/
//			RW);  /* UNS8 checkAccess */
//	TpdoTransmissionType = TRANS_EVERY_N_SYNC(1);	
//	writeLocalDict( d, /*CO_Data* d*/
//			0x1800, /*UNS16 index*/
//			0x02, /*UNS8 subind*/ 
//			&TpdoTransmissionType, /*void * pSourceData,*/ 
//			(UNS32*)&unsize, /* UNS8 * pExpectedSize*/
//			RW);  /* UNS8 checkAccess */
//			
//	writeLocalDict( d, /*CO_Data* d*/
//			0x1801, /*UNS16 index*/
//			0x01, /*UNS8 subind*/ 
//			&TPDO2_COBID, /*void * pSourceData,*/ 
//			&size, /* UNS8 * pExpectedSize*/
//			RW);  /* UNS8 checkAccess */
//	TpdoTransmissionType = TRANS_EVERY_N_SYNC(1);	
//	writeLocalDict( d, /*CO_Data* d*/
//			0x1801, /*UNS16 index*/
//			0x02, /*UNS8 subind*/ 
//			&TpdoTransmissionType, /*void * pSourceData,*/ 
//			(UNS32*)&unsize, /* UNS8 * pExpectedSize*/
//			RW);  /* UNS8 checkAccess */
					
}
/**
  * @brief  Master_preOperational.
  * @param  d:CANOpen object dictionary.
  * @retval None
  */
void Master_preOperational(CO_Data* d)
{
	SEGGER_RTT_printf(0, "Master_preOperational\n");
}
/**
  * @brief  Master_preOperational.
  * @param  d:CANOpen object dictionary.
  * @retval None
  */
void Master_operational(CO_Data* d)
{
	UNS32 SyncTimePeriod = 2000;
	UNS32 size = sizeof(SyncTimePeriod);
	
	writeLocalDict( d, /*CO_Data* d*/
			0x1006, /*UNS16 index*/
			0x00, /*UNS8 subind*/ 
			&SyncTimePeriod, /*void * pSourceData,*/ 
			&size, /* UNS8 * pExpectedSize*/
			RW);  /* UNS8 checkAccess */
	stopSYNC(d);
	startSYNC(d);
	setTimer(100);
//	TIM_Cmd(TIM4, ENABLE); //20190408 FreeRTOS ÒÆÖ² CANopen
	HAL_TIM_Base_Start_IT(&htim4);
	SEGGER_RTT_printf(0, "Master_operational\n");
}
/**
  * @brief  Master_stopped.
  * @param  d:CANOpen object dictionary.
  * @retval None
  */
void Master_stopped(CO_Data* d)
{
	SEGGER_RTT_printf(0, "Master_stopped\n");
}

/**
  * @brief  Master_post_sync.
  * @param  d:CANOpen object dictionary.
  * @retval None
  */
void Master_post_sync(CO_Data* d)
{

	ControlWordAxis1 = 0x0f;
	InterpolationDataAxis1 = 100;
	
	ControlWordAxis2 = 0x0f;
	InterpolationDataAxis2 = 100;
	SEGGER_RTT_printf(0, "Master_post_sync\n");
}
/**
  * @brief  Master_post_emcy.
  * @param  d:CANOpen object dictionary.
  * @retval None
  */
void Master_post_emcy(CO_Data* d, UNS8 nodeID, UNS16 errCode, UNS8 errReg)
{
	SEGGER_RTT_printf(0, "Master received EMCY message. Node: %2.2x  ErrorCode: %4.4x  ErrorRegister: %2.2x\n", nodeID, errCode, errReg);
}
/**
  * @brief  Master_post_TPDO.
  * @param  d:CANOpen object dictionary.
  * @retval None
  */
void Master_post_TPDO(CO_Data* d)
{

}
/**
  * @brief  Master_post_SlaveBootup.
  * @param  d:CANOpen object dictionary.nodeId:Node id
  * @retval None
  */
void Master_post_SlaveBootup(CO_Data* d, UNS8 nodeid)
{
		masterSendNMTstateChange (d, nodeid, NMT_Start_Node);
		SEGGER_RTT_printf(0, "Master_post_SlaveBootup %x\n", nodeid);
}
/**
  * @brief  Master_post_SlaveBootup.
  * @param  d:CANOpen object dictionary.nodeId:Node id newNodeState:Slave change state
  * @retval None
  */
void Master_post_SlaveStateChange(CO_Data* d, UNS8 nodeId, e_nodeState newNodeState)
{
		static UNS8 NodeIdNum = 0;
		if (newNodeState == Operational)
		{
				NodeIdNum++;
				if (NodeIdNum == MAX_CAN_BUS_ID)
				{
						NodeIdNum = 0;
						setState(d, Operational);
				}
		}
}
/**
  * @brief  CANOpenMasterInit.
  * @param  d:CANOpen object dictionary..
  * @retval None
  */
void CANOpenMasterInit(CO_Data* d)
{
	d->heartbeatError = Master_heartbeatError;
	d->initialisation = Master_initialisation;
	d->preOperational = Master_preOperational;
	d->operational = Master_operational;
	d->stopped = Master_stopped;
	d->post_sync = Master_post_sync;
	d->post_TPDO = Master_post_TPDO;
	d->post_emcy = Master_post_emcy;
	d->post_SlaveBootup = Master_post_SlaveBootup;
	d->post_SlaveStateChange = Master_post_SlaveStateChange;
}
/**
  * @brief  CanopenInit
  * @param  NONE
  * @retval NONE
  */
void CanopenInit(void)
{
	UNS32 i;
	
	initTimer();   
	CANOpenMasterObject->canHandle = CAN1;
	CANOpenMasterInit(CANOpenMasterObject);
	setState(CANOpenMasterObject,Initialisation);
	setNodeId (CANOpenMasterObject, 127);
//	canInit(CAN1,CAN_BAUD_1M);      
	canInit(); //20190408 FreeRTOS ÒÆÖ² CANopen	
	for(i=0; i<65536; i++);
	for(i=0; i<65536; i++);
	for(i=0; i<65536; i++);
	for(i=0; i<65536; i++);
	for(i=0; i<65536; i++);

}
/******************* (C) COPYRIGHT 2015 Personal Electronics *****END OF FILE****/

