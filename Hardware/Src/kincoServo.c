/**
  ******************************************************************************
  * @file    kincoServo.c
  * @author  szazone
  * @version V0.0.1
  * @date    03-August-2022
  * @brief   KincoServo CANOpen protocol  source file.
  *
  ******************************************************************************
  */ 

/* Includes ------------------------------------------------------------------*/
#include "kincoServo.h"

// Application/User/Core
#include "can.h"
// Middlewares/FreeRTOS
#include "cmsis_os2.h"
// Hardware
#include "canOpen.h"

CanOpen_OD_t KincoServo_DigitalInAndOutput_Num = {0x2010,0x00,1,0x06};
CanOpen_OD_t KincoServo_DigitalInAndOutput[KincoServo_DigitalInAndOutput_Num_MAX] = {
	{0x2010,0x01,2,0x06},
};

void KincoServo_init(void)
{
	int i;
	CanOpen_OD_t od;
	
	if (KincoServo_DigitalInAndOutput_Num.data.dataValue > KincoServo_DigitalInAndOutput_Num_MAX) {
		 KincoServo_DigitalInAndOutput_Num.data.dataValue = KincoServo_DigitalInAndOutput_Num_MAX;
	}
	od.index = 0x2010;
	od.length = 2;
	od.data.dataValue = 0x00;
	for (i=1; i<=CANOpen_PreDefinedErrorField_Num.data.dataValue; ++i) {
		od.subindex = i;
		CANOpen_PreDefinedErrorField_Value[i-1] = od;
	}
}
