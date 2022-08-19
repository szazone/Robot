/**
  ******************************************************************************
  * @file    canOpen.c
  * @author  szazone
  * @version V0.0.1
  * @date    03-August-2022
  * @brief   CAN Open source file.
  *
  ******************************************************************************
  */ 

/* Includes ------------------------------------------------------------------*/
#include "canOpen.h"

// Middlewares/FreeRTOS
#include "cmsis_os2.h"
#include "FreeRTOS.h"
#include "queue.h"
// CanOpen
#include "def.h"

extern osMessageQueueId_t CAN1TxQueueHandle;
extern volatile unsigned long  ulHighFrequencyTimerTicks;

CanOpen_OD_t CANOpen_DeviceType = {0x1000,0x00,4,0x00};
CanOpen_OD_t CANOpen_ErrorRegister = {0x1001,0x00,1,0x00};
CanOpen_OD_t CANOpen_ManufacturerStatusRegister = {0x1002,0x00,1,0x00};
CanOpen_OD_t CANOpen_PreDefinedErrorField_Num = {0x1003,0x00,1,0x01};
CanOpen_OD_t CANOpen_PreDefinedErrorField_Value[CANOpen_PreDefinedErrorField_Num_MAX] = {
	{0x1003,0x01,4,0x00},
};
CanOpen_OD_t CANOpen_COBIDSYNCMessage = {0x1005,0x00,4,0x00};
CanOpen_OD_t CANOpen_CommunicationCyclePeriod = {0x1006,0x00,4,0x00};
CanOpen_OD_t CANOpen_SynchronousWindowLength = {0x1007,0x00,4,0x00};
CanOpen_OD_t CANOpen_ManufacturerDeviceName = {0x1008,0x00,4,0x00};
CanOpen_OD_t CANOpen_ManufacturerHardwareVersion = {0x1009,0x00,4,0x00};
CanOpen_OD_t CANOpen_ManufacturerSoftwareVersion = {0x100A,0x00,4,0x00};
CanOpen_OD_t CANOpen_GuardTime = {0x100C,0x00,4,0x00};
CanOpen_OD_t CANOpen_ProducerHeartbeatTime = {0x1017,0x00,2,0x00};
CanOpen_OD_t CANOpen_IdentityObject_Num = {0x1018,0x00,1,0x04};
CanOpen_OD_t CANOpen_IdentityObject_VendorID = {0x1018,0x01,4,0x00};
CanOpen_OD_t CANOpen_IdentityObject_ProductCode = {0x1018,0x02,4,0x00};
CanOpen_OD_t CANOpen_IdentityObject_RevisionNumber = {0x1018,0x03,4,0x00};
CanOpen_OD_t CANOpen_IdentityObject_SerialNumber = {0x1018,0x04,4,0x00};
CanOpen_OD_t CANOpen_SynchronousCounterOverflowValue = {0x1019,0x00,1,0x00};
CanOpen_OD_t CANOpen_VerifyConfiguration_Num = {0x1020,0x00,1,0x02};
CanOpen_OD_t CANOpen_VerifyConfiguration_ConfigurationDate = {0x1020,0x01,4,0x00};
CanOpen_OD_t CANOpen_VerifyConfiguration_ConfigurationTime = {0x1020,0x02,4,0x00};
CanOpen_OD_t CANOpen_StoreEDS = {0x1021,0x00,4,0x00};
CanOpen_OD_t CANOpen_StoreFormat = {0x1022,0x00,2,0x00};
CanOpen_OD_t CANOpen_OSCommand_Num = {0x1023,0x00,1,0x03};
CanOpen_OD_t CANOpen_OSCommand_Command = {0x1023,0x01,4,0x00};
CanOpen_OD_t CANOpen_OSCommand_Status = {0x1023,0x02,1,0x00};
CanOpen_OD_t CANOpen_OSCommand_Reply = {0x1023,0x03,4,0x00};
CanOpen_OD_t CANOpen_OSCommandMode = {0x1024,0x00,1,0x00};
CanOpen_OD_t CANOpen_OSDebuggerInterface_Num = {0x1025,0x00,1,0x03};
CanOpen_OD_t CANOpen_OSDebuggerInterface_Command = {0x1025,0x01,4,0x00};
CanOpen_OD_t CANOpen_OSDebuggerInterface_Status = {0x1025,0x02,4,0x00};
CanOpen_OD_t CANOpen_OSDebuggerInterface_Reply = {0x1025,0x03,4,0x00};
CanOpen_OD_t CANOpen_OSDebuggerPrompt_Num = {0x1026,0x00,1,0x03};
CanOpen_OD_t CANOpen_OSDebuggerPrompt_StdIn = {0x1026,0x01,1,0x00};
CanOpen_OD_t CANOpen_OSDebuggerPrompt_StdOut = {0x1026,0x02,1,0x00};
CanOpen_OD_t CANOpen_OSDebuggerPrompt_StdErr = {0x1026,0x03,1,0x00};
CanOpen_OD_t CANOpen_ModuleList_Num = {0x1027,0x00,1,0x01};
CanOpen_OD_t CANOpen_ModuleList_Value[CANOpen_ModuleList_Num_MAX] = {
	{0x1027,0x01,2,0x00},
};
CanOpen_OD_t CANOpen_EmergencyConsumerObject = {0x1028,0x00,2,0x00};
CanOpen_OD_t CANOpen_EmergencyBehaviorObject_Num = {0x1029,0x00,1,0x01};
CanOpen_OD_t CANOpen_EmergencyBehaviorObject_Value[CANOpen_EmergencyBehaviorObject_Num_MAX] = {
	{0x1029,0x01,1,0x00},
};
unsigned short CANOpen_SDOServerParameter_Num = 1;
CanOpen_OD_t CANOpen_SDOServerParameter_Value[CANOpen_SDOServerParameter_Num_MAX][4] = {
	{
		{0x1200,0x00,1,0x03},	// Highest sub-index supported
		{0x1200,0x01,4,0x600},	// COB-ID client -> server (rx)
		{0x1200,0x02,4,0x580},	// COB-ID server -> client (tx)
		{0x1200,0x03,4,0x00},	// Node-ID of the SDO client
	},
};
unsigned short CANOpen_SDOClientParameter_Num = 1;
CanOpen_OD_t CANOpen_SDOClientParameter_Value[CANOpen_SDOServerParameter_Num_MAX][4] = {
	{
		{0x1280,0x00,1,0x03},	// Highest sub-index supported
		{0x1280,0x01,4,0x00},	// COB-ID client -> server (tx)
		{0x1280,0x02,4,0x00},	// COB-ID server -> client (rx)
		{0x1280,0x03,4,0x00},	// Node-ID of the SDO server
	},
};
unsigned short CANOpen_RPDOCommunicationParameter_Num = 1;
CanOpen_OD_t CANOpen_RPDOCommunicationParameter_Value[CANOpen_RPDOCommunicationParameter_Num_MAX][7] = {
	{
		{0x1400,0x00,1,0x06},	// Highest sub-index supported
		{0x1400,0x01,4,0x200},	// COB-ID used by RPDO
		{0x1400,0x02,4,0x00},	// transmission type
		{0x1400,0x03,4,0x00},	// inhibit time
		{0x1400,0x04,4,0x00},	// reserved
		{0x1400,0x05,4,0x00},	// event-timer
		{0x1400,0x06,4,0x00},	// SYNC start value
	},
};
unsigned short CANOpen_RPDOMappingParameter_Num = 1;
CanOpen_OD_t CANOpen_RPDOMappingParameter_Value[CANOpen_RPDOCommunicationParameter_Num_MAX][CANOpen_RPDOMappingParameter_Num_MAX+1] = {
	{
		{0x1600,0x00,1,CANOpen_RPDOMappingParameter_Num_MAX},	// Highest sub-index supported
		{0x1600,0x01,4,0x00},	// 1st application object
	},
};
unsigned short CANOpen_TPDOCommunicationParameter_Num = 1;
CanOpen_OD_t CANOpen_TPDOCommunicationParameter_Value[CANOpen_TPDOCommunicationParameter_Num_MAX][7] = {
	{
		{0x1800,0x00,1,0x06},	// Highest sub-index supported
		{0x1800,0x01,4,0x180},	// COB-ID used by TPDO
		{0x1800,0x02,1,0x00},	// transmission type
		{0x1800,0x03,4,0x00},	// inhibit time
		{0x1800,0x04,4,0x00},	// reserved
		{0x1800,0x05,4,0x00},	// event-timer
		{0x1400,0x06,4,0x00},	// SYNC start value
	},
};
unsigned short CANOpen_TPDOMappingParameter_Num = 1;
CanOpen_OD_t CANOpen_TPDOMappingParameter_Value[CANOpen_TPDOCommunicationParameter_Num_MAX][CANOpen_TPDOMappingParameter_Num_MAX+1] = {
	{
		{0x1A00,0x00,1,CANOpen_TPDOMappingParameter_Num_MAX},	// Highest sub-index supported
		{0x1A00,0x01,4,0x00},	// 1st application object
	},
};

// Functions
void CANOpen_initSTDOD(void)
{
	int i,j;
	CanOpen_OD_t od;
	
	if (CANOpen_PreDefinedErrorField_Num.data.dataValue > CANOpen_PreDefinedErrorField_Num_MAX) {
		CANOpen_PreDefinedErrorField_Num.data.dataValue = CANOpen_PreDefinedErrorField_Num_MAX;
	}
	od.index = 0x1003;
	od.length = 4;
	od.data.dataValue = 0x00;
	for (i=1; i<=CANOpen_PreDefinedErrorField_Num.data.dataValue; ++i) {
		od.subindex = i;
		CANOpen_PreDefinedErrorField_Value[i-1] = od;
	}
	
	if (CANOpen_ModuleList_Num.data.dataValue > CANOpen_ModuleList_Num_MAX) {
		CANOpen_ModuleList_Num.data.dataValue = CANOpen_ModuleList_Num_MAX;
	}
	od.index = 0x1026;
	od.length = 4;
	od.data.dataValue = 0x00;
	for (i=1; i<=CANOpen_ModuleList_Num.data.dataValue; ++i) {
		od.subindex = i;
		CANOpen_ModuleList_Value[i-1] = od;
	}
	
	if (CANOpen_EmergencyBehaviorObject_Num.data.dataValue <= CANOpen_EmergencyBehaviorObject_Num_MAX) {
		CANOpen_EmergencyBehaviorObject_Num.data.dataValue = CANOpen_EmergencyBehaviorObject_Num_MAX;
	}
	od.index = 0x1026;
	od.length = 4;
	od.data.dataValue = 0x00;
	for (i=1; i<=CANOpen_EmergencyBehaviorObject_Num.data.dataValue; ++i) {
		od.subindex = i;
		CANOpen_EmergencyBehaviorObject_Value[i-1] = od;
	}
	
	if (CANOpen_SDOServerParameter_Num > CANOpen_SDOServerParameter_Num_MAX) {
		CANOpen_SDOServerParameter_Num = CANOpen_SDOServerParameter_Num_MAX;
	}
	for (j=1; j<=CANOpen_SDOServerParameter_Num; ++j) {
		od.index = 0x1200+j;
		od.length = 1;
		od.subindex = 0x00;
		od.data.dataValue = 0x200;
		CANOpen_SDOServerParameter_Value[j][0] = od;
		
		od.length = 4;
		od.data.dataValue = 0x00;
		for (i=1; i<=3; ++i) {
			od.subindex = i;
			CANOpen_SDOServerParameter_Value[j][i] = od;
		}
	}
	
	if (CANOpen_SDOClientParameter_Num > CANOpen_SDOClientParameter_Num_MAX) {
		CANOpen_SDOClientParameter_Num = CANOpen_SDOClientParameter_Num_MAX;
	}
	for (j=0; j<=CANOpen_SDOClientParameter_Num-1; ++j) {
		od.index = 0x1280+j;
		od.length = 1;
		od.subindex = 0x00;
		od.data.dataValue = 0x03;
		CANOpen_SDOClientParameter_Value[j][0] = od;
		
		od.length = 4;
		od.data.dataValue = 0x00;
		for (i=1; i<=3; ++i) {
			od.subindex = i;
			CANOpen_SDOClientParameter_Value[j][i] = od;
		}
	}
	
	if (CANOpen_RPDOCommunicationParameter_Num > CANOpen_RPDOCommunicationParameter_Num_MAX) {
		CANOpen_RPDOCommunicationParameter_Num = CANOpen_RPDOCommunicationParameter_Num_MAX;
	}
	for (j=0; j<=CANOpen_RPDOCommunicationParameter_Num-1; ++j) {
		od.index = 0x1400+j;
		od.length = 4;
		od.data.dataValue = 0x00;
		for (i=1; i<=6; ++i) {
			od.subindex = i;
			CANOpen_RPDOCommunicationParameter_Value[j][i] = od;
		}
	}
	
	if (CANOpen_RPDOMappingParameter_Num > CANOpen_RPDOMappingParameter_Num_MAX) {
		CANOpen_RPDOMappingParameter_Num = CANOpen_RPDOMappingParameter_Num_MAX;
	}
	for (j=0; j<=CANOpen_RPDOCommunicationParameter_Num-1; ++j) {
		od.index = 0x1600+j;
		od.length = 1;
		od.subindex = 0x00;
		od.data.dataValue = 0x00;
		CANOpen_RPDOMappingParameter_Value[j][0] = od;
		
		od.length = 4;
		od.data.dataValue = 0x00;
		for (i=1; i<=CANOpen_RPDOMappingParameter_Num_MAX; ++i) {
			od.subindex = i;
			CANOpen_RPDOMappingParameter_Value[j][i] = od;
		}
	}
	
	if (CANOpen_TPDOCommunicationParameter_Num > CANOpen_SDOServerParameter_Num_MAX) {
		CANOpen_TPDOCommunicationParameter_Num = CANOpen_SDOServerParameter_Num_MAX;
	}
	for (j=0; j<=CANOpen_TPDOCommunicationParameter_Num-1; ++j) {
		od.index = 0x1800+j;
		od.length = 4;
		od.data.dataValue = 0x00;
		for (i=1; i<=6; ++i) {
			od.subindex = i;
			CANOpen_TPDOCommunicationParameter_Value[j][i] = od;
		}
	}
	
	if (CANOpen_TPDOMappingParameter_Num > CANOpen_TPDOMappingParameter_Num_MAX) {
		CANOpen_TPDOMappingParameter_Num = CANOpen_TPDOMappingParameter_Num_MAX;
	}
	for (j=0; j<=CANOpen_TPDOCommunicationParameter_Num-1; ++j) {
		od.index = 0x1A00+j;
		od.length = 1;
		od.subindex = 0x00;
		od.data.dataValue = 0x00;
		CANOpen_TPDOMappingParameter_Value[j][0] = od;
		
		od.length = 4;
		od.data.dataValue = 0x00;
		for (i=1; i<=CANOpen_TPDOMappingParameter_Num_MAX; ++i) {
			od.subindex = i;
			CANOpen_TPDOMappingParameter_Value[j][i] = od;
		}
	}
}

void CANOpen_MasterWriteOD2Message(unsigned short nodeId, CanOpen_OD_t od, Message *message)
{
	message->cob_id = 0x600+nodeId;
	message->rtr = CAN_RTR_DATA;
	message->len = 8;
	
	if (od.length == 0) {
		message->data[0] = 0x60;
	} else if (od.length == 1) {
		message->data[0] = 0x2F;
		message->data[4] = od.data.dataByte[0];
		message->data[5] = 0;
		message->data[6] = 0;
		message->data[7] = 0;
	} else if (od.length == 2) {
		message->data[0] = 0x2B;
		message->data[4] = od.data.dataByte[0];
		message->data[5] = od.data.dataByte[1];
		message->data[6] = 0;
		message->data[7] = 0;
	} else if (od.length == 3) {
		message->data[0] = 0x27;
		message->data[4] = od.data.dataByte[0];
		message->data[5] = od.data.dataByte[1];
		message->data[6] = od.data.dataByte[2];
		message->data[7] = 0;
	} else if (od.length == 4) {
		message->data[0] = 0x23;
		message->data[4] = od.data.dataByte[0];
		message->data[5] = od.data.dataByte[1];
		message->data[6] = od.data.dataByte[2];
		message->data[7] = od.data.dataByte[3];
	} else;
	
	message->data[1] = (unsigned char)(od.index&0x00FF);
	message->data[2] = (unsigned char)((od.index&0xFF00)>>8);
	message->data[3] = od.subindex;
}

void CANOpen_MasterReadOD2Message(unsigned short nodeId, CanOpen_OD_t od, Message *message)
{
	message->cob_id = 0x600+nodeId;
	message->rtr = CAN_RTR_DATA;
	message->len = 8;
	
	if (od.length == 0) message->data[0] = 0x40;
	else if (od.length == 1) message->data[0] = 0x4F;
	else if (od.length == 2) message->data[0] = 0x4B;
	else if (od.length == 3) message->data[0] = 0x47;
	else if (od.length == 4) message->data[0] = 0x43;
	else;
	
	message->data[1] = (unsigned char)(od.index&0x00FF);
	message->data[2] = (unsigned char)((od.index&0xFF00)>>8);
	message->data[3] = od.subindex;
	message->data[4] = 0x00;
	message->data[5] = 0x00;
	message->data[6] = 0x00;
	message->data[7] = 0x00;
}

void CANOpen_MasterSYNC(Message *m)
{
	m->cob_id = 0x080; /*(NMT) << 7*/
	m->rtr = CAN_RTR_DATA;
	m->len = 0;
}

void CANOpen_NMTManagement(unsigned char nodeId, unsigned char state,Message *m)
{
	m->cob_id = 0x000; /*(NMT) << 7*/
	m->rtr = CAN_RTR_DATA;
	m->len = 2;
	m->data[0] = state;
	m->data[1] = nodeId;
}
