/**
  ******************************************************************************
  * @file    CNG_MGS_160N.h
  * @author  szazone
  * @version V0.0.1
  * @date    03-August-2022
  * @brief   HINSON CNG_MGS_160N magnetic sensor source file.
  *
  ******************************************************************************
  */ 

#ifndef __CNG_MGS_160N_H__
#define __CNG_MGS_160N_H__

#ifdef __cplusplus
	extern "C" {
#endif
/* Includes ------------------------------------------------------------------*/

void CNG_MGS_160N_init(unsigned char nodeId);
void CNG_MGS_160N_config(unsigned char nodeId);

#ifdef __cplusplus
	}
#endif

#endif	// __CNG_MGS_160N_H__
