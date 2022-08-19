/**
  ******************************************************************************
  * @file    motionTask.h
  * @author  szazone
  * @version V0.0.1
  * @date    03-August-2022
  * @brief   RTOS motionTask head file.
  *
  ******************************************************************************
  */ 

#ifndef __MOTIONTASK_H__
#define __MOTIONTASK_H__

#ifdef __cplusplus
	extern "C" {
#endif
/* Includes ------------------------------------------------------------------*/

typedef struct{
	double limit;		//输出限幅
	double target;		//目标输出量
	double feedback;		//实际输出量	
	double Kp;	
	double Ki;	
	double Kd;	
	double e_0;			//当前误差
	double e_1;			//上一次误差
	double e_2;			//上上次误差
} PID;

void StartTaskMotion(void *argument);

#ifdef __cplusplus
	}
#endif

#endif	// __MOTIONTASK_H__
