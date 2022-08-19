/**
  ******************************************************************************
  * @file    canOpen.h
  * @author  szazone
  * @version V0.0.1
  * @date    03-August-2022
  * @brief   HINSON CNG_MGS_160N magnetic sensor source file.
  *
  ******************************************************************************
  */ 

#ifndef __CANOPEN_H__
#define __CANOPEN_H__

#ifdef __cplusplus
	extern "C" {
#endif
/* Includes ------------------------------------------------------------------*/
// Application/User/Core
#include "can.h"

typedef struct {
	unsigned short index;
	unsigned char subindex;
	unsigned char length;
	union {
		unsigned int dataValue;
		unsigned char dataByte[4];
	} data;
} CanOpen_OD_t;

#define CANOpen_PreDefinedErrorField_Num_MAX		0x01
#define CANOpen_ModuleList_Num_MAX					0x01
#define CANOpen_EmergencyBehaviorObject_Num_MAX 	0x01
#define CANOpen_SDOServerParameter_Num_MAX			0x02
#define CANOpen_SDOClientParameter_Num_MAX			0x02
#define CANOpen_RPDOCommunicationParameter_Num_MAX	0x04
#define CANOpen_RPDOMappingParameter_Num_MAX		0x04
#define CANOpen_TPDOCommunicationParameter_Num_MAX	0x04
#define CANOpen_TPDOMappingParameter_Num_MAX		0x04

extern CanOpen_OD_t CANOpen_DeviceType;
extern CanOpen_OD_t CANOpen_ErrorRegister;
extern CanOpen_OD_t CANOpen_ManufacturerStatusRegister;
extern CanOpen_OD_t CANOpen_PreDefinedErrorField_Num;
extern CanOpen_OD_t CANOpen_PreDefinedErrorField_Value[CANOpen_PreDefinedErrorField_Num_MAX ];
extern CanOpen_OD_t CANOpen_COBIDSYNCMessage;
extern CanOpen_OD_t CANOpen_CommunicationCyclePeriod;
extern CanOpen_OD_t CANOpen_SynchronousWindowLength;
extern CanOpen_OD_t CANOpen_ManufacturerDeviceName;
extern CanOpen_OD_t CANOpen_ManufacturerHardwareVersion;
extern CanOpen_OD_t CANOpen_ManufacturerSoftwareVersion;
extern CanOpen_OD_t CANOpen_GuardTime;
extern CanOpen_OD_t CANOpen_ProducerHeartbeatTime;
extern CanOpen_OD_t CANOpen_IdentityObject_Num;
extern CanOpen_OD_t CANOpen_IdentityObject_VendorID;
extern CanOpen_OD_t CANOpen_IdentityObject_ProductCode;
extern CanOpen_OD_t CANOpen_IdentityObject_RevisionNumber;
extern CanOpen_OD_t CANOpen_SynchronousCounterOverflowValue;
extern CanOpen_OD_t CANOpen_VerifyConfiguration_Num;
extern CanOpen_OD_t CANOpen_VerifyConfiguration_ConfigurationDate;
extern CanOpen_OD_t CANOpen_VerifyConfiguration_ConfigurationTime;
extern CanOpen_OD_t CANOpen_StoreEDS;
extern CanOpen_OD_t CANOpen_StoreFormat;
extern CanOpen_OD_t CANOpen_OSCommand_Num;
extern CanOpen_OD_t CANOpen_OSCommand_Command;
extern CanOpen_OD_t CANOpen_OSCommand_Status;
extern CanOpen_OD_t CANOpen_OSCommand_Reply;
extern CanOpen_OD_t CANOpen_OSCommandMode;
extern CanOpen_OD_t CANOpen_OSDebuggerInterface_Num;
extern CanOpen_OD_t CANOpen_OSDebuggerInterface_Command;
extern CanOpen_OD_t CANOpen_OSDebuggerInterface_Status;
extern CanOpen_OD_t CANOpen_OSDebuggerInterface_Reply;
extern CanOpen_OD_t CANOpen_OSDebuggerPrompt_Num;
extern CanOpen_OD_t CANOpen_OSDebuggerPrompt_StdIn;
extern CanOpen_OD_t CANOpen_OSDebuggerPrompt_StdOut;
extern CanOpen_OD_t CANOpen_OSDebuggerPrompt_StdErr;
extern CanOpen_OD_t CANOpen_ModuleList_Num;
extern CanOpen_OD_t CANOpen_ModuleList_Value[CANOpen_ModuleList_Num_MAX];
extern CanOpen_OD_t CANOpen_EmergencyConsumerObject;
extern CanOpen_OD_t CANOpen_EmergencyBehaviorObject_Num;
extern CanOpen_OD_t CANOpen_EmergencyBehaviorObject_Value[CANOpen_EmergencyBehaviorObject_Num_MAX];
extern unsigned short CANOpen_SDOServerParameter_Num;
extern CanOpen_OD_t CANOpen_SDOServerParameter_Value[CANOpen_SDOServerParameter_Num_MAX][4];
extern unsigned short CANOpen_SDOClientParameter_Num;
extern CanOpen_OD_t CANOpen_SDOClientParameter_Value[CANOpen_SDOServerParameter_Num_MAX][4];
extern unsigned short CANOpen_RPDOCommunicationParameter_Num;
extern CanOpen_OD_t CANOpen_RPDOCommunicationParameter_Value[CANOpen_RPDOCommunicationParameter_Num_MAX][7];
extern unsigned short CANOpen_RPDOMappingParameter_Num;
extern CanOpen_OD_t CANOpen_RPDOMappingParameter_Value[CANOpen_RPDOCommunicationParameter_Num_MAX][CANOpen_RPDOMappingParameter_Num_MAX+1];
extern unsigned short CANOpen_TPDOCommunicationParameter_Num;
extern CanOpen_OD_t CANOpen_TPDOCommunicationParameter_Value[CANOpen_TPDOCommunicationParameter_Num_MAX][7];
extern unsigned short CANOpen_TPDOMappingParameter_Num;
extern CanOpen_OD_t CANOpen_TPDOMappingParameter_Value[CANOpen_TPDOCommunicationParameter_Num_MAX][CANOpen_TPDOMappingParameter_Num_MAX+1];

void CANOpen_initSTDOD(void);
void CANOpen_MasterWriteOD2Message(unsigned short nodeId, CanOpen_OD_t od, Message *message);
void CANOpen_MasterReadOD2Message(unsigned short nodeId, CanOpen_OD_t od, Message *message);
void CANOpen_MasterSYNC(Message *m);
void CANOpen_NMTManagement(unsigned char nodeId, unsigned char state,Message *m);

#ifdef __cplusplus
	}
#endif

#endif	// __CANOPEN_H__
