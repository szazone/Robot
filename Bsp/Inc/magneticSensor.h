/**
  ******************************************************************************
  * @file    magneticSensor.h
  * @author  szazone
  * @version V0.0.1
  * @date    03-August-2022
  * @brief   Magnetic Sensor head file.
  *
  ******************************************************************************
  */ 

#ifndef __MAGNETICSENSOR_H__
#define __MAGNETICSENSOR_H__

#ifdef __cplusplus
	extern "C" {
#endif
/* Includes ------------------------------------------------------------------*/
// Application/User/Core
#include "can.h"

#define MagneticSensor_Num 2

extern const unsigned char MagneticSensor_nodeId[MagneticSensor_Num];
extern short MagneticSensor_leftPointNum[MagneticSensor_Num];
extern short MagneticSensor_middPointNum[MagneticSensor_Num];
extern short MagneticSensor_rightPointNum[MagneticSensor_Num];
extern unsigned char MagneticSensor_faultStatus[MagneticSensor_Num];
extern unsigned char MagneticSensor_magPoisStatus[MagneticSensor_Num];

void MagneticSensor_init(void);
void MagneticSensor_analysisMessage(Message *m);

#ifdef __cplusplus
	}
#endif

#endif	// __MAGNETICSENSOR_H__
