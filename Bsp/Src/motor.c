/**
  ******************************************************************************
  * @file    motor.c
  * @author  szazone
  * @version V0.0.1
  * @date    03-August-2022
  * @brief   motor source file.
  *
  ******************************************************************************
  */ 

/* Includes ------------------------------------------------------------------*/
#include "motor.h"

// Middlewares/FreeRTOS
#include "cmsis_os2.h"
#include "FreeRTOS.h"
#include "queue.h"
// CanOpen
#include "def.h"
// Hardware
#include "canOpen.h"
#include "debugSerial.h"
#include "led.h"
// STD C
#include "stdbool.h"

extern osMessageQueueId_t CAN1TxQueueHandle;

const unsigned char Motor_nodeId[Motor_Num] = {0x01,0x02};	// nodeId
int Motor_Value_PositionActualValue[Motor_Num];				// 实际位置
int Motor_Value_SpeedReal[Motor_Num];						// 实际速度
short Motor_Value_Statusword[Motor_Num];					// 状态字
short Motor_Value_ErrorCodeForDS301[Motor_Num];				// 错误代码
short Motor_Value_ErrorStatus2[Motor_Num];					// 错误状态2
short Motor_Value_Iq[Motor_Num];							// 实际电流

// 配置
Message  Motor_NMT_Reset_Node[Motor_Num];
Message* Motor_NMT_Reset_Node_p[Motor_Num];
Message  Motor_NMT_Enter_PreOperational[Motor_Num];
Message* Motor_NMT_Enter_PreOperational_p[Motor_Num];
Message  Motor_NMT_Start_Node[Motor_Num];
Message* Motor_NMT_Start_Node_p[Motor_Num];

Message  Motor_PositionActualValue[Motor_Num];	// 实际位置
Message* Motor_PositionActualValue_p[Motor_Num];
Message  Motor_SpeedReal[Motor_Num];		// 实际速度
Message* Motor_SpeedReal_p[Motor_Num];
Message  Motor_Statusword[Motor_Num];		// 状态字
Message* Motor_Statusword_p[Motor_Num];
Message  Motor_ErrorCodeForDS301[Motor_Num];// 错误代码
Message* Motor_ErrorCodeForDS301_p[Motor_Num];
Message  Motor_ErrorStatus2[Motor_Num];		// 错误状态2
Message* Motor_ErrorStatus2_p[Motor_Num];
Message  Motor_Iq[Motor_Num];				// 实际电流
Message* Motor_Iq_p[Motor_Num];

Message  Motor_TPDO1Disable[Motor_Num];		// 关闭 TPDO1
Message* Motor_TPDO1Disable_p[Motor_Num]={&Motor_TPDO1Disable[0],&Motor_TPDO1Disable[1]};
Message  Motor_TPDO2Disable[Motor_Num];		// 关闭 TPDO2
Message* Motor_TPDO2Disable_p[Motor_Num];
Message  Motor_TPDO3Disable[Motor_Num];		// 关闭 TPDO3
Message* Motor_TPDO3Disable_p[Motor_Num];
Message  Motor_TPDO4Disable[Motor_Num];		// 关闭 TPDO4
Message* Motor_TPDO4Disable_p[Motor_Num];

Message  Motor_TPDO1MPDisable[Motor_Num];	// TPDO1 子索引个数置 0
Message* Motor_TPDO1MPDisable_p[Motor_Num];
Message  Motor_TPDO1TransmissionType[Motor_Num];	// TPDO1 transmission type
Message* Motor_TPDO1TransmissionType_p[Motor_Num];
Message  Motor_TPDO1MPO1[Motor_Num];		// TPDO1 子索引 1 映射对象
Message* Motor_TPDO1MPO1_p[Motor_Num];
Message  Motor_TPDO1MPO2[Motor_Num];		// TPDO1 子索引 2 映射对象
Message* Motor_TPDO1MPO2_p[Motor_Num];
Message  Motor_TPDO1MPEnable[Motor_Num];	// TPDO1 子索引个数置 2
Message* Motor_TPDO1MPEnable_p[Motor_Num];
Message  Motor_TPDO1COBID[Motor_Num];		// TPDO1 开启及设置 COB-ID
Message* Motor_TPDO1COBID_p[Motor_Num];

Message  Motor_TPDO2MPDisable[Motor_Num];	// TPDO2 子索引个数置 0
Message* Motor_TPDO2MPDisable_p[Motor_Num];
Message  Motor_TPDO2TransmissionType[Motor_Num];	// TPDO2 transmission type
Message* Motor_TPDO2TransmissionType_p[Motor_Num];
Message  Motor_TPDO2MPO1[Motor_Num];		// TPDO2 子索引 1 映射对象
Message* Motor_TPDO2MPO1_p[Motor_Num];
Message  Motor_TPDO2MPO2[Motor_Num];		// TPDO2 子索引 2 映射对象
Message* Motor_TPDO2MPO2_p[Motor_Num];
Message  Motor_TPDO2MPO3[Motor_Num];		// TPDO2 子索引 3 映射对象
Message* Motor_TPDO2MPO3_p[Motor_Num];
Message  Motor_TPDO2MPO4[Motor_Num];		// TPDO2 子索引 4 映射对象
Message* Motor_TPDO2MPO4_p[Motor_Num];
Message  Motor_TPDO2MPEnable[Motor_Num];	// TPDO2 子索引个数置 4
Message* Motor_TPDO2MPEnable_p[Motor_Num];
Message  Motor_TPDO2COBID[Motor_Num];		// TPDO2 开启及设置 COB-ID
Message* Motor_TPDO2COBID_p[Motor_Num];

Message  Motor_RPDO1Disable[Motor_Num];		// 关闭 RPDO1
Message* Motor_RPDO1Disable_p[Motor_Num]={&Motor_RPDO1Disable[0],&Motor_RPDO1Disable[1]};
Message  Motor_RPDO1MPDisable[Motor_Num];	// RPDO1 子索引个数置 0
Message* Motor_RPDO1MPDisable_p[Motor_Num];
Message  Motor_RPDO1TransmissionType[Motor_Num];	// RPDO1 transmission type
Message* Motor_RPDO1TransmissionType_p[Motor_Num];
Message  Motor_RPDO1MPO1[Motor_Num];		// RPDO1 子索引 1 映射对象
Message* Motor_RPDO1MPO1_p[Motor_Num]={&Motor_RPDO1MPO1[0],&Motor_RPDO1MPO1[1]};;
Message  Motor_RPDO1MPEnable[Motor_Num];	// RPDO1 子索引个数置 4
Message* Motor_RPDO1MPEnable_p[Motor_Num];
Message  Motor_RPDO1COBID[Motor_Num];		// RPDO1 开启及设置 COB-ID
Message* Motor_RPDO1COBID_p[Motor_Num];

Message  Motor_Controlword[Motor_Num];		// 控制字
Message* Motor_Controlword_p[Motor_Num];
Message  Motor_ModesOfOperation[Motor_Num];	// 工作模式
Message* Motor_ModesOfOperation_p[Motor_Num];

Message  Motor_speed[Motor_Num] = {
	{0x201,0,8,{0x55,0x15,0x02,0x00,0x00,0x00,0x00,0x00}},
	{0x202,0,8,{0x55,0x15,0x02,0x00,0x00,0x00,0x00,0x00}}
};
Message* Motor_speed_p[Motor_Num] = {
	&Motor_speed[0], &Motor_speed[1]
};

void Motor_setSpeed(unsigned char motorNum,double rpm)
{
	int dec = (int)((rpm*512*10000)/1875);
	unsigned char data[4];
	data[0] = (unsigned char)(dec&0xFF);
	data[1] = (unsigned char)((dec>>8)&0xFF);
	data[2] = (unsigned char)((dec>>16)&0xFF);
	data[3] = (unsigned char)((dec>>24)&0xFF);
	
	for (int i=0; i<4; ++i) {
		Motor_speed[motorNum].data[i] = data[i];
	}
}

double Motor_getSpeed(unsigned char motorNum)
{
	return (double)(Motor_Value_SpeedReal[motorNum]*1875.0/512/10000);
}

void Motor_sendRPDO(void)
{
	BaseType_t pxHigherPriorityTaskWoken;
	
	for (int i=0; i<Motor_Num; ++i) {
		xQueueSendFromISR(CAN1TxQueueHandle,&Motor_speed_p[i],&pxHigherPriorityTaskWoken);
	}
}

void Motor_DebugSetSpeed(void)
{
	Motor_setSpeed(0,50);
	Motor_setSpeed(1,50);
}

static void Motor_dataInit(void){
	for (int i=0; i<Motor_Num; ++i) {
		Motor_NMT_Reset_Node_p[i] = &Motor_NMT_Reset_Node[i];
		Motor_NMT_Enter_PreOperational_p[i] = &Motor_NMT_Enter_PreOperational[i];
		
		Motor_PositionActualValue_p[i] = &Motor_PositionActualValue[i];
		Motor_SpeedReal_p[i] = &Motor_SpeedReal[i];
		Motor_Statusword_p[i] = &Motor_Statusword[i];
		Motor_ErrorCodeForDS301_p[i] = &Motor_ErrorCodeForDS301[i];
		Motor_ErrorStatus2_p[i] = &Motor_ErrorStatus2[i];	
		Motor_Iq_p[i] = &Motor_Iq[i];
		
		Motor_TPDO1Disable_p[i] = &Motor_TPDO1Disable[i];
		Motor_TPDO2Disable_p[i] = &Motor_TPDO2Disable[i];
		Motor_TPDO3Disable_p[i] = &Motor_TPDO3Disable[i];
		Motor_TPDO4Disable_p[i] = &Motor_TPDO4Disable[i];

		Motor_TPDO1MPDisable_p[i] = &Motor_TPDO1MPDisable[i];
		Motor_TPDO1TransmissionType_p[i] = &Motor_TPDO1TransmissionType[i];		
		Motor_TPDO1MPO1_p[i] = &Motor_TPDO1MPO1[i];
		Motor_TPDO1MPO2_p[i] = &Motor_TPDO1MPO2[i];
		Motor_TPDO1MPEnable_p[i] = &Motor_TPDO1MPEnable[i];
		Motor_TPDO1COBID_p[i] = &Motor_TPDO1COBID[i];
		
		Motor_TPDO2MPDisable_p[i] = &Motor_TPDO2MPDisable[i];
		Motor_TPDO2TransmissionType_p[i] = &Motor_TPDO2TransmissionType[i];
		Motor_TPDO2MPO1_p[i] = &Motor_TPDO2MPO1[i];
		Motor_TPDO2MPO2_p[i] = &Motor_TPDO2MPO2[i];
		Motor_TPDO2MPO3_p[i] = &Motor_TPDO2MPO3[i];
		Motor_TPDO2MPO4_p[i] = &Motor_TPDO2MPO4[i];
		Motor_TPDO2MPEnable_p[i] = &Motor_TPDO2MPEnable[i];
		Motor_TPDO2COBID_p[i] = &Motor_TPDO2COBID[i];
		
		Motor_RPDO1Disable_p[i] = &Motor_RPDO1Disable[i];
		Motor_RPDO1MPDisable_p[i] = &Motor_RPDO1MPDisable[i];
		Motor_RPDO1TransmissionType_p[i] = &Motor_RPDO1TransmissionType[i];
		Motor_RPDO1MPO1_p[i] = &Motor_RPDO1MPO1[i];
		Motor_RPDO1MPEnable_p[i] = &Motor_RPDO1MPEnable[i];
		Motor_RPDO1COBID_p[i] = &Motor_RPDO1COBID[i];
		
		Motor_Controlword_p[i] = &Motor_Controlword[i];
		Motor_ModesOfOperation_p[i] = &Motor_ModesOfOperation[i];
		
		Motor_NMT_Start_Node_p[i] = &Motor_NMT_Start_Node[i];
	}
}

static void Motor_config(unsigned int i)
{	
	CanOpen_OD_t od;
	
	// PDO 配置
	od.index=0x1800; 									// TPDO1 Communication Parameter
	od.subindex=0x01; od.length=4;						// 关闭 TPDO1
	od.data.dataValue = 0x80000180;						// 0x80000180
	CANOpen_MasterWriteOD2Message(Motor_nodeId[i],od,&Motor_TPDO1Disable[i]);
	xQueueSend(CAN1TxQueueHandle,&Motor_TPDO1Disable_p[i], 50);
	osDelay(10);
	od.subindex=0x02; od.length=1;						// TPDO1 transmission type
	od.data.dataValue = 1;								// 每 1 次同步报文后发送
	CANOpen_MasterWriteOD2Message(Motor_nodeId[i],od,&Motor_TPDO1TransmissionType[i]);
	xQueueSend(CAN1TxQueueHandle,&Motor_TPDO1TransmissionType_p[i], 50);
	osDelay(10);
	od.index=0x1A00;									// TPDO1 Mapping Parameter
	od.subindex=0x00; od.length=1;						// TPDO1 Max Sub-index Support
	od.data.dataValue = 0;								// TPDO1 子索引个数置 0
	CANOpen_MasterWriteOD2Message(Motor_nodeId[i],od,&Motor_TPDO1MPDisable[i]);
	xQueueSend(CAN1TxQueueHandle,&Motor_TPDO1MPDisable_p[i], 50);
	osDelay(10);
	od.subindex=0x01; od.length=4;						// TPDO1 子索引 1 映射对象
	od.data.dataValue = 0x60640020;						// 实际位置
	CANOpen_MasterWriteOD2Message(Motor_nodeId[i],od,&Motor_TPDO1MPO1[i]);
	xQueueSend(CAN1TxQueueHandle,&Motor_TPDO1MPO1_p[i], 50);
	osDelay(10);
	od.subindex=0x02; od.length=4;						// TPDO1 子索引 2 映射对象
	od.data.dataValue = 0x606C0020;						// 实际速度
	CANOpen_MasterWriteOD2Message(Motor_nodeId[i],od,&Motor_TPDO1MPO2[i]);
	xQueueSend(CAN1TxQueueHandle,&Motor_TPDO1MPO2_p[i], 50);
	osDelay(10);
	od.subindex=0x00; od.length=1;						// TPDO1 Max Sub-index Support
	od.data.dataValue = 2;								// TPDO1 子索引个数置 2
	CANOpen_MasterWriteOD2Message(Motor_nodeId[i],od,&Motor_TPDO1MPEnable[i]);
	xQueueSend(CAN1TxQueueHandle,&Motor_TPDO1MPEnable_p[i], 50);
	osDelay(10);
	od.index=0x1800; 									// TPDO1 Communication Parameter
	od.subindex=0x01; od.length=4;						// TPDO1 开启及设置 COB-ID
	od.data.dataValue = 0x180+Motor_nodeId[i];			// 0x180 + nodeId
	CANOpen_MasterWriteOD2Message(Motor_nodeId[i],od,&Motor_TPDO1COBID[i]);
	xQueueSend(CAN1TxQueueHandle,&Motor_TPDO1COBID_p[i], 50);
	osDelay(10);
	
	od.index=0x1801; 									// TPDO2 Communication Parameter
	od.subindex=0x01; od.length=4;						// 关闭 TPDO2
	od.data.dataValue = 0x80000280;						// 0x80000280
	CANOpen_MasterWriteOD2Message(Motor_nodeId[i],od,&Motor_TPDO2Disable[i]);
	xQueueSend(CAN1TxQueueHandle,&Motor_TPDO2Disable_p[i], 50);
	osDelay(10);									
	od.subindex=0x02; od.length=1;						// TPDO2 transmission type
	od.data.dataValue = 5;								// 每 5 次同步报文后发送
	CANOpen_MasterWriteOD2Message(Motor_nodeId[i],od,&Motor_TPDO2TransmissionType[i]);
	xQueueSend(CAN1TxQueueHandle,&Motor_TPDO2TransmissionType_p[i], 50);
	osDelay(10);
	od.index=0x1A01;									// TPDO2 Mapping Parameter
	od.subindex=0x00; od.length=1;						// TPDO2 Max Sub-index Support
	od.data.dataValue = 0;								// TPDO2 子索引个数置 0
	CANOpen_MasterWriteOD2Message(Motor_nodeId[i],od,&Motor_TPDO2MPDisable[i]);
	xQueueSend(CAN1TxQueueHandle,&Motor_TPDO2MPDisable_p[i], 50);
	osDelay(10);
	od.subindex=0x01; od.length=4;						// TPDO2 子索引 1 映射对象
	od.data.dataValue = 0x60410010;						// 状态字
	CANOpen_MasterWriteOD2Message(Motor_nodeId[i],od,&Motor_TPDO2MPO1[i]);
	xQueueSend(CAN1TxQueueHandle,&Motor_TPDO2MPO1_p[i], 50);
	osDelay(10);
	od.subindex=0x02; od.length=4;						// TPDO2 子索引 2 映射对象
	od.data.dataValue = 0x603F0010;						// 错误代码
	CANOpen_MasterWriteOD2Message(Motor_nodeId[i],od,&Motor_TPDO2MPO2[i]);
	xQueueSend(CAN1TxQueueHandle,&Motor_TPDO2MPO2_p[i], 50);
	osDelay(10);
	od.subindex=0x03; od.length=4;						// TPDO2 子索引 3 映射对象
	od.data.dataValue = 0x26020010;						// 错误状态2
	CANOpen_MasterWriteOD2Message(Motor_nodeId[i],od,&Motor_TPDO2MPO3[i]);
	xQueueSend(CAN1TxQueueHandle,&Motor_TPDO2MPO3_p[i], 50);
	osDelay(10);
	od.subindex=0x04; od.length=4;						// TPDO2 子索引 4 映射对象
	od.data.dataValue = 0x60780010;						// 实际电流
	CANOpen_MasterWriteOD2Message(Motor_nodeId[i],od,&Motor_TPDO2MPO4[i]);
	xQueueSend(CAN1TxQueueHandle,&Motor_TPDO2MPO4_p[i], 50);
	osDelay(10);
	od.subindex=0x00; od.length=1;						// TPDO2 Max Sub-index Support
	od.data.dataValue = 4;								// TPDO2 子索引个数置 4
	CANOpen_MasterWriteOD2Message(Motor_nodeId[i],od,&Motor_TPDO2MPEnable[i]);
	xQueueSend(CAN1TxQueueHandle,&Motor_TPDO2MPEnable_p[i], 50);
	osDelay(10);
	od.index=0x1801; 									// TPDO2 Communication Parameter
	od.subindex=0x01; od.length=4;						// TPDO2 开启及设置 COB-ID
	od.data.dataValue = 0x280+Motor_nodeId[i];			// 0x180 + nodeId
	CANOpen_MasterWriteOD2Message(Motor_nodeId[i],od,&Motor_TPDO2COBID[i]);
	xQueueSend(CAN1TxQueueHandle,&Motor_TPDO2COBID_p[i], 50);
	osDelay(10);
	
	od.index=0x1802; 									// TPDO3 Communication Parameter
	od.subindex=0x01; od.length=4;						// 关闭 TPDO3
	od.data.dataValue = 0x80000380;						// 0x80000380
	CANOpen_MasterWriteOD2Message(Motor_nodeId[i],od,&Motor_TPDO3Disable[i]);
	xQueueSend(CAN1TxQueueHandle,&Motor_TPDO3Disable_p[i], 50);
	osDelay(10);
	od.index=0x1803; 									// TPDO4 Communication Parameter
	od.subindex=0x01; od.length=4;						// 关闭 TPDO4
	od.data.dataValue = 0x80000480;						// 0x80000480
	CANOpen_MasterWriteOD2Message(Motor_nodeId[i],od,&Motor_TPDO4Disable[i]);
	xQueueSend(CAN1TxQueueHandle,&Motor_TPDO4Disable_p[i], 50);
	osDelay(10);
	
	od.index=0x1400; 									// RPDO1 Communication Parameter
	od.subindex=0x01; od.length=4;						// 关闭 RPDO1
	od.data.dataValue = 0x80000200;						// 0x80000200
	CANOpen_MasterWriteOD2Message(Motor_nodeId[i],od,&Motor_RPDO1Disable[i]);
	xQueueSend(CAN1TxQueueHandle,&Motor_RPDO1Disable_p[i], 50);
	osDelay(10);
	od.subindex=0x02; od.length=1;						// RPDO1 transmission type
	od.data.dataValue = 1;								// 每 1 次同步报文后发送
	CANOpen_MasterWriteOD2Message(Motor_nodeId[i],od,&Motor_RPDO1TransmissionType[i]);
	xQueueSend(CAN1TxQueueHandle,&Motor_RPDO1TransmissionType_p[i], 50);
	osDelay(10);
	od.index=0x1600;									// RPDO1 Mapping Parameter
	od.subindex=0x00; od.length=1;						// RPDO1 Max Sub-index Support
	od.data.dataValue = 0;								// RPDO1 子索引个数置 0
	CANOpen_MasterWriteOD2Message(Motor_nodeId[i],od,&Motor_RPDO1MPDisable[i]);
	xQueueSend(CAN1TxQueueHandle,&Motor_RPDO1MPDisable_p[i], 50);
	osDelay(10);
	od.subindex=0x01; od.length=4;						// RPDO1 子索引 1 映射对象
	od.data.dataValue = 0x60FF0020;						// 目标速度
	CANOpen_MasterWriteOD2Message(Motor_nodeId[i],od,&Motor_RPDO1MPO1[i]);
	xQueueSend(CAN1TxQueueHandle,&Motor_RPDO1MPO1_p[i], 50);
	osDelay(10);
	od.subindex=0x00; od.length=1;						// RPDO1 Max Sub-index Support
	od.data.dataValue = 2;								// RPDO1 子索引个数置 2
	CANOpen_MasterWriteOD2Message(Motor_nodeId[i],od,&Motor_RPDO1MPEnable[i]);
	xQueueSend(CAN1TxQueueHandle,&Motor_RPDO1MPEnable_p[i], 50);
	osDelay(10);
	od.index=0x1400; 									// RPDO1 Communication Parameter
	od.subindex=0x01; od.length=4;						// RPDO1 开启及设置 COB-ID
	od.data.dataValue = 0x200+Motor_nodeId[i];			// 0x200 + nodeId
	CANOpen_MasterWriteOD2Message(Motor_nodeId[i],od,&Motor_RPDO1COBID[i]);
	xQueueSend(CAN1TxQueueHandle,&Motor_RPDO1COBID_p[i], 50);
	osDelay(10);
	
	od.index=0x6040;									// 控制字
	od.subindex=0x00; od.length=2;						// 控制字
	od.data.dataValue = 0x000F;							// 电机上电
	CANOpen_MasterWriteOD2Message(Motor_nodeId[i],od,&Motor_Controlword[i]);
	xQueueSend(CAN1TxQueueHandle,&Motor_Controlword_p[i], 50);
	osDelay(10);
	od.index=0x6060;									// 工作模式
	od.subindex=0x00; od.length=1;						// 工作模式
	od.data.dataValue = 0x03;							// 速度模式
	CANOpen_MasterWriteOD2Message(Motor_nodeId[i],od,&Motor_ModesOfOperation[i]);
	xQueueSend(CAN1TxQueueHandle,&Motor_ModesOfOperation_p[i], 50);
	osDelay(10);
}

void Motor_init(void)
{
	Motor_dataInit();
	for (int i=0; i<Motor_Num; ++i) {
		CANOpen_NMTManagement(Motor_nodeId[i],NMT_Reset_Node,&Motor_NMT_Reset_Node[i]);
		xQueueSend(CAN1TxQueueHandle,&Motor_NMT_Reset_Node_p[i], 50);
		osDelay(10);
		CANOpen_NMTManagement(Motor_nodeId[i],NMT_Enter_PreOperational,&Motor_NMT_Enter_PreOperational[i]);
		xQueueSend(CAN1TxQueueHandle,&Motor_NMT_Enter_PreOperational_p[i], 50);
		osDelay(10);
		
		Motor_config(i);
		
		CANOpen_NMTManagement(Motor_nodeId[i], NMT_Start_Node,&Motor_NMT_Start_Node[i]);		
		xQueueSend(CAN1TxQueueHandle,&Motor_NMT_Start_Node_p[i], 50);
		osDelay(10);
	}
}

void Motor_analysisMessage(Message *m)
{
	unsigned char nodeId;
	unsigned char PDONum;
	unsigned char motorNum;
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
	
	for (int i=0; i<Motor_Num; ++i) {
		if (nodeId == Motor_nodeId[i]) {
			motorNum = i;
			break;
		}
	}
	
	if (isPDO) {
		switch (PDONum) {
			case 1:
				Motor_Value_PositionActualValue[motorNum] = (int)((m->data[3]<<24)|(m->data[2]<<16)|(m->data[1]<<8)|m->data[0]);
				Motor_Value_SpeedReal[motorNum] = (int)((m->data[7]<<24)|(m->data[6]<<16)|(m->data[5]<<8)|m->data[4]);
				break;
			
			case 2:
				Motor_Value_Statusword[motorNum] = (short)((m->data[1]<<8)|m->data[0]);
				Motor_Value_ErrorCodeForDS301[motorNum] = (short)((m->data[3]<<8)|m->data[2]);
				Motor_Value_ErrorStatus2[motorNum] = (short)((m->data[5]<<8)|m->data[4]);
				Motor_Value_Iq[motorNum] = (short)((m->data[7]<<8)|m->data[6]);
				
				if (Motor_Value_Statusword[motorNum]&0x0008) {
					DebugSerial_printf("[ERROR] Motor: %d Statusword Fault: [ErrorCodeForDS301: 0x%04X] [ErrorStatus2: 0x%04X]\r\n",
						motorNum,Motor_Value_ErrorCodeForDS301[motorNum],Motor_Value_ErrorStatus2[motorNum]);
					LED_ERRORControl(1);
				} else {
					LED_ERRORControl(0);
				}
				if (Motor_Value_Statusword[motorNum]&0x0080) {
					DebugSerial_printf("[WARNING] Motor: %d, Statusword Warning\r\n",motorNum);
					LED_ALARMControl(1);
				} else {
					LED_ALARMControl(0);
				}
				break;
			
			case 3:
				break;
			
			case 4:
				break;
			
			default: break;
		}
//		DebugSerial_printf("[INFO] Motor: %d Position: %08d Speed: %08d Current: %05d Statusword: 0x%04X\r\n",
//			motorNum,Motor_Value_PositionActualValue[motorNum],Motor_Value_SpeedReal[motorNum]*1875/512/10000,
//			Motor_Value_Iq[motorNum],Motor_Value_Statusword[motorNum]);
	} else {
		unsigned short index = (unsigned short)(m->data[1]<<8)+m->data[0];
		unsigned char subindex = m->data[3];
	}
}
