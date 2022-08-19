/**
  ******************************************************************************
  * @file    iso3082.h
  * @author  szazone
  * @version V0.0.1
  * @date    03-August-2022
  * @brief   ISO3082 Isolated 5-V Full- and Half-Duplex RS-485 Transceivers 
  * 		 Board Support Package head file.
  *
  ******************************************************************************
  */ 

#ifndef ISO3082_H
#define ISO3082_H

#ifdef __cplusplus
	extern "C" {
#endif
/* Includes ------------------------------------------------------------------*/
// STM32F4xx_HAL_Driver
#include "stm32f4xx.h"

void ISO3082_Direction(unsigned char dir);

#ifdef __cplusplus
	}
#endif

#endif	// ISO3082
