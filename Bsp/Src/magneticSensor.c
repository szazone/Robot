/**
  ******************************************************************************
  * @file    magneticSensor.c
  * @author  szazone
  * @version V0.0.1
  * @date    03-August-2022
  * @brief   Magnetic Sensor source file.
  *
  ******************************************************************************
  */ 

/* Includes ------------------------------------------------------------------*/
#include "magneticSensor.h"

// Middlewares/FreeRTOS
#include "cmsis_os2.h"
#include "FreeRTOS.h"
#include "queue.h"
// CanOpen
#include "def.h"
// Hardware
#include "canOpen.h"
#include "debugSerial.h"
#include "Hinson_CNS_MGS.h"
#include "led.h"
// STD C
#include "stdbool.h"

extern osMessageQueueId_t CAN1TxQueueHandle;

const unsigned char MagneticSensor_nodeId[MagneticSensor_Num] = {0x03,0x04};
short MagneticSensor_leftPointNum[MagneticSensor_Num];
short MagneticSensor_middPointNum[MagneticSensor_Num];
short MagneticSensor_rightPointNum[MagneticSensor_Num];
unsigned char MagneticSensor_faultStatus[MagneticSensor_Num];
unsigned char MagneticSensor_magPoisStatus[MagneticSensor_Num];

// 配置
Message  MagneticSensor_NMT_Reset_Node[MagneticSensor_Num];
Message* MagneticSensor_NMT_Reset_Node_p[MagneticSensor_Num];
Message  MagneticSensor_NMT_Enter_PreOperational[MagneticSensor_Num];
Message* MagneticSensor_NMT_Enter_PreOperational_p[MagneticSensor_Num];
Message  MagneticSensor_NMT_Start_Node[MagneticSensor_Num];
Message* MagneticSensor_NMT_Start_Node_p[MagneticSensor_Num];

Message  MagneticSensor_MinPointNumber[MagneticSensor_Num];	// 最小感应点数
Message* MagneticSensor_MinPointNumber_p[MagneticSensor_Num];
Message  MagneticSensor_MaxPointNumber[MagneticSensor_Num];	// 最大感应点数
Message* MagneticSensor_MaxPointNumber_p[MagneticSensor_Num];
Message  MagneticSensor_SensorPolarity[MagneticSensor_Num];	// 磁条感应极性
Message* MagneticSensor_SensorPolarity_p[MagneticSensor_Num];
Message  MagneticSensor_WriteCommand[MagneticSensor_Num];	// 写入参数
Message* MagneticSensor_WriteCommand_p[MagneticSensor_Num];
Message  MagneticSensor_RebootSensor[MagneticSensor_Num];	// 重启传感器
Message* MagneticSensor_RebootSensor_p[MagneticSensor_Num];

Message  MagneticSensor_TPDO1Disable[MagneticSensor_Num];	// 关闭 TPDO1
Message* MagneticSensor_TPDO1Disable_p[MagneticSensor_Num];
Message  MagneticSensor_TPDO2Disable[MagneticSensor_Num];	// 关闭 TPDO2
Message* MagneticSensor_TPDO2Disable_p[MagneticSensor_Num];
Message  MagneticSensor_TPDO3Disable[MagneticSensor_Num];	// 关闭 TPDO3
Message* MagneticSensor_TPDO3Disable_p[MagneticSensor_Num];
Message  MagneticSensor_TPDO4Disable[MagneticSensor_Num];	// 关闭 TPDO4
Message* MagneticSensor_TPDO4Disable_p[MagneticSensor_Num];
Message  MagneticSensor_TPDO1MP0[MagneticSensor_Num];		// TPDO1 子索引个数置 0
Message* MagneticSensor_TPDO1MP0_p[MagneticSensor_Num];
Message  MagneticSensor_TPDO1TransmissionType[MagneticSensor_Num];	// TPDO1 transmission type
Message* MagneticSensor_TPDO1TransmissionType_p[MagneticSensor_Num];
Message  MagneticSensor_TPDO1MPO1[MagneticSensor_Num];		// TPDO1 子索引 1 映射对象
Message* MagneticSensor_TPDO1MPO1_p[MagneticSensor_Num];
Message  MagneticSensor_TPDO1MPO2[MagneticSensor_Num];		// TPDO1 子索引 2 映射对象
Message* MagneticSensor_TPDO1MPO2_p[MagneticSensor_Num];
Message  MagneticSensor_TPDO1MPO3[MagneticSensor_Num];		// TPDO1 子索引 3 映射对象
Message* MagneticSensor_TPDO1MPO3_p[MagneticSensor_Num];
Message  MagneticSensor_TPDO1MPO4[MagneticSensor_Num];		// TPDO1 子索引 4 映射对象
Message* MagneticSensor_TPDO1MPO4_p[MagneticSensor_Num];
Message  MagneticSensor_TPDO1MPO5[MagneticSensor_Num];		// TPDO1 子索引 5 映射对象
Message* MagneticSensor_TPDO1MPO5_p[MagneticSensor_Num];
Message  MagneticSensor_TPDO1COBID[MagneticSensor_Num];		// TPDO1 开启及设置 COB-ID
Message* MagneticSensor_TPDO1COBID_p[MagneticSensor_Num];
Message  MagneticSensor_TPDO1MP5[MagneticSensor_Num];		// TPDO1 子索引个数置 5
Message* MagneticSensor_TPDO1MP5_p[MagneticSensor_Num];

static void MagneticSensor_dataInit(void){
	for (int i=0; i<MagneticSensor_Num; ++i) {
		MagneticSensor_NMT_Reset_Node_p[i] = &MagneticSensor_NMT_Reset_Node[i];
		MagneticSensor_NMT_Enter_PreOperational_p[i] = &MagneticSensor_NMT_Enter_PreOperational[i];
		
		MagneticSensor_MinPointNumber_p[i] = &MagneticSensor_MinPointNumber[i];
		MagneticSensor_MaxPointNumber_p[i] = &MagneticSensor_MaxPointNumber[i];
		MagneticSensor_SensorPolarity_p[i] = &MagneticSensor_SensorPolarity[i];
		MagneticSensor_WriteCommand_p[i] = &MagneticSensor_WriteCommand[i];
		MagneticSensor_RebootSensor_p[i] = &MagneticSensor_RebootSensor[i];		
		
		MagneticSensor_TPDO1Disable_p[i] = &MagneticSensor_TPDO1Disable[i];
		MagneticSensor_TPDO2Disable_p[i] = &MagneticSensor_TPDO2Disable[i];
		MagneticSensor_TPDO3Disable_p[i] = &MagneticSensor_TPDO3Disable[i];
		MagneticSensor_TPDO4Disable_p[i] = &MagneticSensor_TPDO4Disable[i];
		MagneticSensor_TPDO1MP0_p[i] = &MagneticSensor_TPDO1MP0[i];
		MagneticSensor_TPDO1TransmissionType_p[i] = &MagneticSensor_TPDO1TransmissionType[i];
		
		MagneticSensor_TPDO1MPO1_p[i] = &MagneticSensor_TPDO1MPO1[i];
		MagneticSensor_TPDO1MPO2_p[i] = &MagneticSensor_TPDO1MPO2[i];
		MagneticSensor_TPDO1MPO3_p[i] = &MagneticSensor_TPDO1MPO3[i];
		MagneticSensor_TPDO1MPO4_p[i] = &MagneticSensor_TPDO1MPO4[i];
		MagneticSensor_TPDO1MPO5_p[i] = &MagneticSensor_TPDO1MPO5[i];
		
		MagneticSensor_TPDO1MP5_p[i] = &MagneticSensor_TPDO1MP5[i];
		MagneticSensor_TPDO1COBID_p[i] = &MagneticSensor_TPDO1COBID[i];
		
		MagneticSensor_NMT_Start_Node_p[i] = &MagneticSensor_NMT_Start_Node[i];
	}
}

static void MagneticSensor_config(unsigned int i)
{	
	CanOpen_OD_t od;
	od = Hinson_CNS_MGS_MinPointNumber;		// 最小感应点数
	od.data.dataValue = 1;
	CANOpen_MasterWriteOD2Message(MagneticSensor_nodeId[i],od,&MagneticSensor_MinPointNumber[i]);
	xQueueSend(CAN1TxQueueHandle,&MagneticSensor_MinPointNumber_p[i], 50);
	osDelay(10);
	od = Hinson_CNS_MGS_MaxPointNumber;	// 最大感应点数
	od.data.dataValue = 4;
	CANOpen_MasterWriteOD2Message(MagneticSensor_nodeId[i],od,&MagneticSensor_MaxPointNumber[i]);
	xQueueSend(CAN1TxQueueHandle,&MagneticSensor_MaxPointNumber_p[i], 50);
	osDelay(10);
	od = Hinson_CNS_MGS_SensorPolarity;	// 磁条感应极性 N
	od.data.dataValue = 0;
	CANOpen_MasterWriteOD2Message(MagneticSensor_nodeId[i],od,&MagneticSensor_SensorPolarity[i]);
	xQueueSend(CAN1TxQueueHandle,&MagneticSensor_SensorPolarity_p[i], 50);
	osDelay(10);
	od = Hinson_CNS_MGS_WriteCommand;	// 写入参数
	od.data.dataValue = 0;
	CANOpen_MasterWriteOD2Message(MagneticSensor_nodeId[i],od,&MagneticSensor_WriteCommand[i]);
	xQueueSend(CAN1TxQueueHandle,&MagneticSensor_WriteCommand_p[i], 50);
	osDelay(10);	
	od = Hinson_CNS_MGS_RebootSensor;	// 重启传感器
	od.data.dataValue = 0;
	CANOpen_MasterWriteOD2Message(MagneticSensor_nodeId[i],od,&MagneticSensor_RebootSensor[i]);
	xQueueSend(CAN1TxQueueHandle,&MagneticSensor_RebootSensor_p[i], 50);
	osDelay(10);
	osDelay(1000);
	
	// PDO 配置
	od.index=0x1800; 									// TPDO1 Communication Parameter
	od.subindex=0x01; od.length=4;						// 关闭 TPDO1 COB-ID used by TPDO
	od.data.dataValue = 0x80000180;						// 0x80000180
	CANOpen_MasterWriteOD2Message(MagneticSensor_nodeId[i],od,&MagneticSensor_TPDO1Disable[i]);
	xQueueSend(CAN1TxQueueHandle,&MagneticSensor_TPDO1Disable_p[i], 50);
	osDelay(10);
	od.subindex=0x02; od.length=1;						// TPDO1 transmission type
	od.data.dataValue = 1;								// 每 1 次同步报文后发送
	CANOpen_MasterWriteOD2Message(MagneticSensor_nodeId[i],od,&MagneticSensor_TPDO1TransmissionType[i]);
	xQueueSend(CAN1TxQueueHandle,&MagneticSensor_TPDO1TransmissionType_p[i], 50);
	osDelay(10);
	od.index=0x1A00;									// TPDO1 Mapping Parameter
	od.subindex=0x00; od.length=1;						// TPDO1 Max Sub-index Support
	od.data.dataValue = 0;								// TPDO1 子索引个数置 0
	CANOpen_MasterWriteOD2Message(MagneticSensor_nodeId[i],od,&MagneticSensor_TPDO1MP0[i]);
	xQueueSend(CAN1TxQueueHandle,&MagneticSensor_TPDO1MP0_p[i], 50);
	osDelay(10);
	od.subindex=0x01; od.length=4;						// TPDO1 子索引 1 映射对象
	od.data.dataValue = 0x20080010;						// 左侧磁条位置
	CANOpen_MasterWriteOD2Message(MagneticSensor_nodeId[i],od,&MagneticSensor_TPDO1MPO1[i]);
	xQueueSend(CAN1TxQueueHandle,&MagneticSensor_TPDO1MPO1_p[i], 50);
	osDelay(10);
	od.subindex=0x02; od.length=4;						// TPDO1 子索引 2 映射对象
	od.data.dataValue = 0x20090010;						// 中间磁条位置
	CANOpen_MasterWriteOD2Message(MagneticSensor_nodeId[i],od,&MagneticSensor_TPDO1MPO2[i]);
	xQueueSend(CAN1TxQueueHandle,&MagneticSensor_TPDO1MPO2_p[i], 50);
	osDelay(10);
	od.subindex=0x03; od.length=4;						// TPDO1 子索引 2 映射对象
	od.data.dataValue = 0x200A0010;						// 右侧磁条位置
	CANOpen_MasterWriteOD2Message(MagneticSensor_nodeId[i],od,&MagneticSensor_TPDO1MPO3[i]);
	xQueueSend(CAN1TxQueueHandle,&MagneticSensor_TPDO1MPO3_p[i], 50);
	osDelay(10);
	od.subindex=0x04; od.length=4;						// TPDO1 子索引 4 映射对象
	od.data.dataValue = 0x20020008;						// 传感器状态
	CANOpen_MasterWriteOD2Message(MagneticSensor_nodeId[i],od,&MagneticSensor_TPDO1MPO4[i]);
	xQueueSend(CAN1TxQueueHandle,&MagneticSensor_TPDO1MPO4_p[i], 50);
	osDelay(10);
	od.subindex=0x05; od.length=4;						// TPDO1 子索引 5 映射对象
	od.data.dataValue = 0x20030008;						// 磁条感应状态
	CANOpen_MasterWriteOD2Message(MagneticSensor_nodeId[i],od,&MagneticSensor_TPDO1MPO5[i]);
	xQueueSend(CAN1TxQueueHandle,&MagneticSensor_TPDO1MPO5_p[i], 50);
	osDelay(10);
	od.subindex=0x00; od.length=1;						// TPDO1 Max Sub-index Support
	od.data.dataValue = 5;								// TPDO1 子索引个数置 5
	CANOpen_MasterWriteOD2Message(MagneticSensor_nodeId[i],od,&MagneticSensor_TPDO1MP5[i]);
	xQueueSend(CAN1TxQueueHandle,&MagneticSensor_TPDO1MP5_p[i], 50);
	osDelay(10);
	od.index=0x1800; 									// TPDO1 Communication Parameter
	od.subindex=0x01; od.length=4;						// TPDO1 开启及设置 COB-ID
	od.data.dataValue = 0x180+MagneticSensor_nodeId[i];	// 0x180 + nodeId
	CANOpen_MasterWriteOD2Message(MagneticSensor_nodeId[i],od,&MagneticSensor_TPDO1COBID[i]);
	xQueueSend(CAN1TxQueueHandle,&MagneticSensor_TPDO1COBID_p[i], 50);
	osDelay(10);
		
	od.index=0x1801; 									// TPDO2 Communication Parameter
	od.subindex=0x01; od.length=4;						// 关闭 TPDO1 COB-ID used by TPDO
	od.data.dataValue = 0x80000280;						// 0x80000280
	CANOpen_MasterWriteOD2Message(MagneticSensor_nodeId[i],od,&MagneticSensor_TPDO2Disable[i]);
	xQueueSend(CAN1TxQueueHandle,&MagneticSensor_TPDO2Disable_p[i], 50);
	osDelay(10);
	od.index=0x1802; 									// TPDO3 Communication Parameter
	od.subindex=0x01; od.length=4;						// 关闭 TPDO1 COB-ID used by TPDO
	od.data.dataValue = 0x80000280;						// 0x80000380
	CANOpen_MasterWriteOD2Message(MagneticSensor_nodeId[i],od,&MagneticSensor_TPDO3Disable[i]);
	xQueueSend(CAN1TxQueueHandle,&MagneticSensor_TPDO3Disable_p[i], 50);
	osDelay(10);
	od.index=0x1803; 									// TPDO4 Communication Parameter
	od.subindex=0x01; od.length=4;						// 关闭 TPDO1 COB-ID used by TPDO
	od.data.dataValue = 0x80000480;						// 0x80000480
	CANOpen_MasterWriteOD2Message(MagneticSensor_nodeId[i],od,&MagneticSensor_TPDO4Disable[i]);
	xQueueSend(CAN1TxQueueHandle,&MagneticSensor_TPDO4Disable_p[i], 50);
	osDelay(10);
}

void MagneticSensor_init(void)
{
	MagneticSensor_dataInit();
	for (int i=0; i<MagneticSensor_Num; ++i) {
		CANOpen_NMTManagement(MagneticSensor_nodeId[i],NMT_Reset_Node,&MagneticSensor_NMT_Reset_Node[i]);
		xQueueSend(CAN1TxQueueHandle,&MagneticSensor_NMT_Reset_Node_p[i], 50);
		osDelay(10);
		CANOpen_NMTManagement(MagneticSensor_nodeId[i],NMT_Enter_PreOperational,&MagneticSensor_NMT_Enter_PreOperational[i]);
		xQueueSend(CAN1TxQueueHandle,&MagneticSensor_NMT_Enter_PreOperational_p[i], 50);
		osDelay(10);
		
		MagneticSensor_config(i);
		
		CANOpen_NMTManagement(MagneticSensor_nodeId[i], NMT_Start_Node,&MagneticSensor_NMT_Start_Node[i]);		
		xQueueSend(CAN1TxQueueHandle,&MagneticSensor_NMT_Start_Node_p[i], 50);
		osDelay(10);
	}
}

void MagneticSensor_analysisMessage(Message *m)
{
	unsigned char nodeId;
	unsigned char PDONum;
	unsigned char sensorNum;
	bool isPDO = false;
	
	if (m->cob_id>=0x180 && m->cob_id<=0x1FF) {	// RPDO1
		nodeId = m->cob_id - 0x180;
		isPDO = true;
		PDONum = 1;
	} else if (m->cob_id>=0x280 && m->cob_id<=0x2FF) {	// RPDO2
		nodeId = m->cob_id - 0x280;
		isPDO = true;
		PDONum = 2;
	} else if (m->cob_id>=0x380 && m->cob_id<=0x3FF) {	// RPDO3
		nodeId = m->cob_id - 0x380;
		isPDO = true;
		PDONum = 3;
	} else if (m->cob_id>=0x480 && m->cob_id<=0x4FF) {	// RPDO4
		nodeId = m->cob_id - 0x480;
		isPDO = true;
		PDONum = 4;
	} else if (m->cob_id>=0x581 && m->cob_id<=0x5FF) {	// SDO
		nodeId = m->cob_id - 0x580;
	} else;
	
	for (int i=0; i<MagneticSensor_Num; ++i) {
		if (nodeId == MagneticSensor_nodeId[i]) {
			sensorNum = i;
			break;
		}
	}
	
	if (isPDO) {
		switch (PDONum) {
			case 1:
				MagneticSensor_leftPointNum[sensorNum] = (short)((m->data[1]<<8)|m->data[0]);
				MagneticSensor_middPointNum[sensorNum] = (short)((m->data[3]<<8)|m->data[2]);
				MagneticSensor_rightPointNum[sensorNum] = (short)((m->data[5]<<8)|m->data[4]);
				MagneticSensor_faultStatus[sensorNum] = m->data[6];
				MagneticSensor_magPoisStatus[sensorNum] = m->data[7];
				
//				DebugSerial_printf("[INFO] MagneticSensor: %d left: %03d midd: %03d right: %03d\r\n",
//					sensorNum,MagneticSensor_leftPointNum[sensorNum],MagneticSensor_middPointNum[sensorNum],MagneticSensor_rightPointNum[sensorNum]);
				if (MagneticSensor_faultStatus[sensorNum] != 0x00) {
					DebugSerial_printf("[WARNING] Magnetic Sensor: %d, Error: %02X!\r\n",sensorNum,MagneticSensor_faultStatus[sensorNum]);
					LED_ALARMControl(1);
				} else {
					LED_ALARMControl(0);
				}
				
				break;
			
			case 2:
				break;
			
			case 3:
				break;
			
			case 4:
				break;
			
			default: break;
		}
	} else {
		unsigned short index = (unsigned short)(m->data[2]<<8)+m->data[1];
		unsigned char subindex = m->data[3];
	}
}
