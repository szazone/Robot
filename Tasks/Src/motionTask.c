/**
  ******************************************************************************
  * @file    motionTask.c
  * @author  szazone
  * @version V0.0.1
  * @date    03-August-2022
  * @brief   RTOS motionTask source file.
  *
  ******************************************************************************
  */ 

/* Includes ------------------------------------------------------------------*/
#include "motionTask.h"

// Middlewares/FreeRTOS
#include "cmsis_os2.h"
// Bsp
#include "magneticSensor.h"
#include "motor.h"
// Hardware
#include "debugSerial.h"
// STD C
#include "math.h"

static PID Motion_dirPID;
static double adj;

void motionTask_init(void)
{
	Motion_dirPID.limit = 300;
	Motion_dirPID.target = 0;
	Motion_dirPID.feedback = 0;
	Motion_dirPID.Kp = 1;
	Motion_dirPID.Ki = 0.5;
	Motion_dirPID.Kd = 0.1;
	Motion_dirPID.e_0 = 0;
	Motion_dirPID.e_1 = 0;
	Motion_dirPID.e_2 = 0;
}

double Motion_pidCalc(PID *pid)
{
	double out;
	double ep, ei, ed;
	
	pid->e_0 = pid->target - pid->feedback;
	ep = pid->e_0  - pid->e_1;
	ei = pid->e_0;
	ed = pid->e_0 - 2*pid->e_1 + pid->e_2;
	out = pid->Kp*ep + pid->Ki*ei + pid->Kd*ed;
	out = fmin(fmax(out, 0-pid->limit), pid->limit);
	pid->e_2 = pid->e_1;
	pid->e_1 = pid->e_0;
	return out;
}

void StartTaskMotion(void *argument)
{
	motionTask_init();
	DebugSerial_printf("motionTaske has started.\r\n");
	
	while (1) {
		Motion_dirPID.feedback = MagneticSensor_middPointNum[0];
		adj = Motion_pidCalc(&Motion_dirPID);
		Motor_setSpeed(0,50+adj);
		Motor_setSpeed(1,50-adj);
		osDelay(1);
	}
}
