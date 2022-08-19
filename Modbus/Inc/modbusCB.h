/* 
 * FreeModbus Libary: A portable Modbus implementation for Modbus ASCII/RTU.
 * Copyright (c) 2006 Christian Walter <wolti@sil.at>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. The name of the author may not be used to endorse or promote products
 *    derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * File: $Id: mbtcp.h,v 1.2 2006/12/07 22:10:34 wolti Exp $
 */
#include "stm32f4xx.h"
#include "mb.h"
#include "port.h"
#include <stdbool.h>
#ifndef _MODBUS_CB_H
#define _MODBUS_CB_H

#ifdef __cplusplus
PR_BEGIN_EXTERN_C
#endif
//modbus 接收发送寄存器，全局变量
#define MB_TCP_BUF_SIZE  2048
#define MBTCP_PORT 502;
#define W_RST_Pin GPIO_PIN_1
#define W_RST_GPIO_Port GPIOA
/* ----------------------- Defines ------------------------------------------*/
extern int mode1;
extern uint16_t usRegHoldingBuf[256];
extern uint8_t ucTCPRequestFrame[MB_TCP_BUF_SIZE]; //接收寄存器
extern uint8_t ucTCPResponseFrame[MB_TCP_BUF_SIZE]; //发送寄存器
/* ----------------------- Function prototypes ------------------------------*/
extern volatile uint8_t rx1_len;
extern volatile uint8_t recv1_end_flag;
extern uint8_t rx1_buffer[64];
extern uint8_t tx1_buffer[64];
extern volatile uint8_t rx3_len;
extern volatile uint8_t recv3_end_flag;
extern uint8_t rx3_buffer[13];
extern uint8_t tx3_buffer[12];
extern uint8_t I2c_Buf_Write[512];
extern uint8_t I2c_Buf_Read[512];
/* USER CODE END Includes */
extern uint32_t ZQS1;	
extern uint16_t ZQS2;
extern uint16_t DI1;
extern uint16_t Z;

extern uint16_t PLC_Date;
extern uint32_t X1;

extern uint16_t ms;
extern uint16_t ms1;
extern uint16_t ms2;
extern uint16_t ms3;
extern uint16_t ms4;      //定位计时器
extern uint16_t ms5; 
extern uint16_t ms6;
extern uint16_t a;        //电机转速加速度控制
extern int16_t SD;        //电机速度给定
extern uint16_t FX;       //电机转速控制
extern uint16_t rec_sd;   //电机速度给定
extern uint16_t zd_d_fb;

extern uint16_t dw1;    //定位柱计数
extern uint16_t gs1;    //光栅计数
extern uint16_t gsk1;   //光栅孔计数
extern uint16_t gsk2;   //光栅孔计数2
extern uint32_t x0[512];
extern uint16_t rst;   //机器人复位状态，用于机器人通讯失败自我复位后检测
extern bool plc_tsj_sdw;
extern int32_t DJQSZ;    //1
extern int32_t DJQSF;    //2

extern uint16_t MOD;
#define ON  1
#define OFF 0


/*带参宏 */
//moubus通讯电源
#define Relay0(a)	if (a)\
					HAL_GPIO_WritePin(GPIOE, GPIO_PIN_8, GPIO_PIN_SET);\
					else		\
				  HAL_GPIO_WritePin(GPIOE, GPIO_PIN_8, GPIO_PIN_RESET);
//1#电机电源	DO0				
#define Relay1(a)	if (a)	\
					HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7, GPIO_PIN_SET);\
					else		\
				  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7, GPIO_PIN_RESET);
//2#电机电源	DO1
#define Relay2(a)	if (a)	\
					HAL_GPIO_WritePin(GPIOC, GPIO_PIN_6, GPIO_PIN_SET);\
					else		\
				  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_6, GPIO_PIN_RESET);
//运行指示灯电源	DO2					
#define Relay3(a)	if (a)	\
					HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, GPIO_PIN_SET);\
					else		\
				  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, GPIO_PIN_RESET);
//故障指示灯电源	DO3					
#define Relay4(a)	if (a)	\
					HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14, GPIO_PIN_SET);\
					else		\
				  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14, GPIO_PIN_RESET);
//24V1#备用电源			DO4			
#define Relay5(a)	if (a)	\
					HAL_GPIO_WritePin(GPIOD, GPIO_PIN_13, GPIO_PIN_SET);\
					else		\
				  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_13, GPIO_PIN_RESET);
//24v2#备用电源			DO5		
#define Relay6(a)	if (a)	\
					HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, GPIO_PIN_SET);\
					else		\
				  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, GPIO_PIN_RESET);
//光电开关电源					
#define Relay7(a)	if (a)	\
					HAL_GPIO_WritePin(GPIOE, GPIO_PIN_9, GPIO_PIN_SET);\
					else		\
				  HAL_GPIO_WritePin(GPIOE, GPIO_PIN_9, GPIO_PIN_RESET);
//24V 1#继电器电源				救援勾 1#24V备用继电器 20211029
#define Relay8(a)	if (a)	\
					HAL_GPIO_WritePin(GPIOE, GPIO_PIN_10, GPIO_PIN_SET);\
					else		\
				  HAL_GPIO_WritePin(GPIOE, GPIO_PIN_10, GPIO_PIN_RESET);
//12V 1#继电器电源	DO15			
#define Relay9(a)	if (a)	\
					HAL_GPIO_WritePin(GPIOE, GPIO_PIN_13, GPIO_PIN_SET);\
					else		\
				  HAL_GPIO_WritePin(GPIOE, GPIO_PIN_13, GPIO_PIN_RESET);
//24V 2#继电器电源			 救援勾 2#24V备用 继电器 20211029			
#define Relay10(a)	if (a)	\
					HAL_GPIO_WritePin(GPIOE, GPIO_PIN_11, GPIO_PIN_SET);\
					else		\
				  HAL_GPIO_WritePin(GPIOE, GPIO_PIN_11, GPIO_PIN_RESET);
////电池充电继电器电源					
//#define Relay11(a)	if (a)	\
//					HAL_GPIO_WritePin(GPIOD, GPIO_PIN_0, GPIO_PIN_SET);\
//					else		\
//				  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_0, GPIO_PIN_RESET);
//12 2#继电器电源		DO14	1号备用12v继电器 20211029			
#define Relay12(a)	if (a)	\
					HAL_GPIO_WritePin(GPIOE, GPIO_PIN_12, GPIO_PIN_SET);\
					else		\
				  HAL_GPIO_WritePin(GPIOE, GPIO_PIN_12, GPIO_PIN_RESET);
//后端LED电源			DO13			
#define Relay13(a)	if (a)	\
					HAL_GPIO_WritePin(GPIOE, GPIO_PIN_15, GPIO_PIN_SET);\
					else		\
				  HAL_GPIO_WritePin(GPIOE, GPIO_PIN_15, GPIO_PIN_RESET);
//前端LED电源			DO12		
#define Relay14(a)	if (a)	\
					HAL_GPIO_WritePin(GPIOE, GPIO_PIN_14, GPIO_PIN_SET);\
					else		\
				  HAL_GPIO_WritePin(GPIOE, GPIO_PIN_14, GPIO_PIN_RESET);
//2#摄像头电源		DO11			
#define Relay15(a)	if (a)	\
					HAL_GPIO_WritePin(GPIOD, GPIO_PIN_10, GPIO_PIN_SET);\
					else		\
				  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_10, GPIO_PIN_RESET);
//1#摄像头电源		DO10			
#define Relay16(a)	if (a)	\
					HAL_GPIO_WritePin(GPIOD, GPIO_PIN_11, GPIO_PIN_SET);\
					else		\
				  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_11, GPIO_PIN_RESET);
#define LED(a)	if (a)	\
					HAL_GPIO_WritePin(GPIOE, GPIO_PIN_0, GPIO_PIN_RESET);\
					else		\
				  HAL_GPIO_WritePin(GPIOE, GPIO_PIN_0, GPIO_PIN_SET);

					
typedef struct _aaa
{

unsigned char a1 :1;
unsigned char a2 :1;
unsigned char a3 :1;
unsigned char a4 :1;
unsigned char a5 :1;
unsigned char a6 :1;
unsigned char a7 :1;
unsigned char a8 :1;
unsigned char a9 :1;
unsigned char a10 :1;
unsigned char a11 :1;
unsigned char a12 :1;
unsigned char a13 :1;
unsigned char a14 :1;
unsigned char a15 :1;
unsigned char a16 :1;

}aaa;
 union  PD {
 aaa testBit;
 uint16_t ucTestByte;
};
unsigned int CRC16(unsigned char *puchMsg , unsigned char usDataLen);
void modbus_tcps(uint8_t sn, uint16_t port);
void DateSave(void);
void SoftReset(void);
void TX_Heart(void);
void wizchip_user_init(void);
void network_init(void);
#ifdef __cplusplus
PR_END_EXTERN_C
#endif
#endif
