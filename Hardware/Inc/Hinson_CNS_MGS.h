/**
  ******************************************************************************
  * @file    Hinson_CNS_MGS.h
  * @author  szazone
  * @version V0.0.1
  * @date    03-August-2022
  * @brief   Hinson CNS_MGS series magnetic sensor head file.
  *
  ******************************************************************************
  */ 

#ifndef __HINSON_CNS_MGS_H__
#define __HINSON_CNS_MGS_H__

#ifdef __cplusplus
	extern "C" {
#endif
/* Includes ------------------------------------------------------------------*/
// Drivers/STM32F4xx_HAL_Driver
#include "stm32f4xx.h"
// Hardware
#include "canOpen.h"

extern CanOpen_OD_t Hinson_CNS_MGS_MagSwitch;
extern CanOpen_OD_t Hinson_CNS_MGS_MagSensorData;
extern CanOpen_OD_t Hinson_CNS_MGS_FaultStatus;
extern CanOpen_OD_t Hinson_CNS_MGS_MagPoisStatus;
extern CanOpen_OD_t Hinson_CNS_MGS_ForkSelect;
extern CanOpen_OD_t Hinson_CNS_MGS_SelectPoistion;
extern CanOpen_OD_t Hinson_CNS_MGS_SelectStrength;
extern CanOpen_OD_t Hinson_CNS_MGS_SelectPointNum;
extern CanOpen_OD_t Hinson_CNS_MGS_LeftPoistion;
extern CanOpen_OD_t Hinson_CNS_MGS_MiddPosition;
extern CanOpen_OD_t Hinson_CNS_MGS_RightPosition;
extern CanOpen_OD_t Hinson_CNS_MGS_LeftStrength;
extern CanOpen_OD_t Hinson_CNS_MGS_MiddStrength;
extern CanOpen_OD_t Hinson_CNS_MGS_RightStrength;
extern CanOpen_OD_t Hinson_CNS_MGS_LeftPointNum;
extern CanOpen_OD_t Hinson_CNS_MGS_MiddPointNum;
extern CanOpen_OD_t Hinson_CNS_MGS_RightPointNum;
extern CanOpen_OD_t Hinson_CNS_MGS_SensorPolarity;
extern CanOpen_OD_t Hinson_CNS_MGS_MinPointNumber;
extern CanOpen_OD_t Hinson_CNS_MGS_MaxPointNumber;
extern CanOpen_OD_t Hinson_CNS_MGS_PointDifference;
extern CanOpen_OD_t Hinson_CNS_MGS_SensorSensitivity;
extern CanOpen_OD_t Hinson_CNS_MGS_MiddCenterPostion;
extern CanOpen_OD_t Hinson_CNS_MGS_CanIDAddress;
extern CanOpen_OD_t Hinson_CNS_MGS_CanBaudRate;
extern CanOpen_OD_t Hinson_CNS_MGS_WriteCommand;
extern CanOpen_OD_t Hinson_CNS_MGS_RebootSensor;

#ifdef __cplusplus
	}
#endif

#endif	// __HINSON_CNS_MGS_H__
