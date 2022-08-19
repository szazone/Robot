/**
  ******************************************************************************
  * @file    motor.h
  * @author  szazone
  * @version V0.0.1
  * @date    03-August-2022
  * @brief   Motor head file.
  *
  ******************************************************************************
  */ 

#ifndef __MOTOR_H__
#define __MOTOR_H__

#ifdef __cplusplus
	extern "C" {
#endif
/* Includes ------------------------------------------------------------------*/
// Application/User/Core
#include "can.h"

#define Motor_Num 2

extern const unsigned char Motor_nodeId[Motor_Num];		// nodeId
extern int Motor_Value_PositionActualValue[Motor_Num];	// 实际位置
extern int Motor_Value_SpeedReal[Motor_Num];			// 实际速度
extern short Motor_Value_Statusword[Motor_Num];			// 状态字
extern short Motor_Value_ErrorCodeForDS301[Motor_Num];	// 错误代码
extern short Motor_Value_ErrorStatus2[Motor_Num];		// 错误状态2
extern short Motor_Value_Iq[Motor_Num];					// 实际电流

void Motor_DebugSetSpeed(void);

void Motor_init(void);
void Motor_analysisMessage(Message *m);
double Motor_getSpeed(unsigned char motorNum);
void Motor_setSpeed(unsigned char motorNum,double rpm);
void Motor_sendRPDO(void);

#ifdef __cplusplus
	}
#endif

#endif	// __MOTOR_H__
