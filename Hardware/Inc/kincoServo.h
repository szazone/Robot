/**
  ******************************************************************************
  * @file    kincoServo.h
  * @author  szazone
  * @version V0.0.1
  * @date    03-August-2022
  * @brief   KincoServo CANOpen protocol head file.
  *
  ******************************************************************************
  */ 

#ifndef __KINCOSERVO_H__
#define __KINCOSERVO_H__

#ifdef __cplusplus
	extern "C" {
#endif
/* Includes ------------------------------------------------------------------*/
// Application/User/Core
#include "can.h"
// Hardware
#include "canOpen.h"

#define KincoServo_DigitalInAndOutput_Num_MAX 0x06

extern CanOpen_OD_t KincoServo_DigitalInAndOutput_Num;
extern CanOpen_OD_t KincoServo_DigitalInAndOutput[KincoServo_DigitalInAndOutput_Num_MAX];


void KincoServo_init(void);

#ifdef __cplusplus
	}
#endif

#endif	// __KINCOSERVO_H__
