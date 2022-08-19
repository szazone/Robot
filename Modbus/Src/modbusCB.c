 
#include <stdio.h>
#include "string.h"
#include "mb.h"
#include "mbutils.h"
#include "modbusCB.h"
#include "socket.h"
#include "w5500.h"
#include "port.h"
/* Private variables ---------------------------------------------------------*/
uint16_t H1,H2,H3;
//本地端口
#define local_port 6000
uint8_t server_ip[4]={192,168,166,150};			// 配置远程服务器IP地址
uint16_t server_port=502;								// 配置远程服务器端口
uint8_t buffer[2048];									// 定义一个2KB的数组，用来存放Socket的通信数据





//输入寄存器起始地址
#define REG_INPUT_START       0x0000
//输入寄存器数量
#define REG_INPUT_NREGS       8
//保持寄存器起始地址
#define REG_HOLDING_START     0x0000
//保持寄存器数量
#define REG_HOLDING_NREGS     256

//线圈起始地址
#define REG_COILS_START       0x0000
//线圈数量
#define REG_COILS_SIZE        16

//开关寄存器起始地址
#define REG_DISCRETE_START    0x0000
//开关寄存器数量
#define REG_DISCRETE_SIZE     16

/* Private variables ---------------------------------------------------------*/
int mode1;
//输入寄存器内容
uint16_t usRegInputBuf[REG_INPUT_NREGS] = {0x1000,0x1001,0x1002,0x1003,0x1004,0x1005,0x1006,0x1007};
//寄存器起始地址
uint16_t usRegInputStart = REG_INPUT_START;

//保持寄存器内容
uint16_t usRegHoldingBuf[REG_HOLDING_NREGS];
//保持寄存器起始地址
uint16_t usRegHoldingStart = REG_HOLDING_START;

//线圈状态
uint8_t ucRegCoilsBuf[REG_COILS_SIZE / 8] = {0x01,0x02};
//开关输入状态
uint8_t ucRegDiscreteBuf[REG_DISCRETE_SIZE / 8] = {0x01,0x02};

//modbus 接收发送寄存器，全局变量
//#define MB_TCP_BUF_SIZE  1024
//#define MBTCP_PORT 502;
 uint8_t ucTCPRequestFrame[MB_TCP_BUF_SIZE]; //接收寄存器
 uint16_t ucTCPRequestLen;
 uint8_t ucTCPResponseFrame[MB_TCP_BUF_SIZE]; //发送寄存器
 uint16_t ucTCPResponseLen;
 uint8_t bFrameSent;  //是否进行发送响应判断

// extern uint16_t usRegHoldingBuf[8];
/**
  * @brief  输入寄存器处理函数，输入寄存器可读，但不可写。
  * @param  pucRegBuffer  返回数据指针
  *         usAddress     寄存器起始地址
  *         usNRegs       寄存器长度
  * @retval eStatus       寄存器状态
  */
eMBErrorCode 
eMBRegInputCB( UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNRegs )
{
  eMBErrorCode    eStatus = MB_ENOERR;
  int16_t         iRegIndex;
  
  //查询是否在寄存器范围内
  //为了避免警告，修改为有符号整数
  if( ( (int16_t)usAddress >= REG_INPUT_START ) \
        && ( usAddress + usNRegs <= REG_INPUT_START + REG_INPUT_NREGS ) )
  {
    //获得操作偏移量，本次操作起始地址-输入寄存器的初始地址
    iRegIndex = ( int16_t )( usAddress - usRegInputStart );
    //逐个赋值
    while( usNRegs > 0 )
    {
      //赋值高字节
      *pucRegBuffer++ = ( uint8_t )( usRegInputBuf[iRegIndex] >> 8 );
      //赋值低字节
      *pucRegBuffer++ = ( uint8_t )( usRegInputBuf[iRegIndex] & 0xFF );
      //偏移量增加
      iRegIndex++;
      //被操作寄存器数量递减
      usNRegs--;
    }
  }
  else
  {
    //返回错误状态，无寄存器  
    eStatus = MB_ENOREG;
  }

  return eStatus;
}
//******************************保持寄存器回调函数**********************************
//函数定义: eMBErrorCode eMBRegHoldingCB( UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNRegs, eMBRegisterMode eMode )
//描    述：保持寄存器相关的功能（读、连续读、写、连续写）
//入口参数：pucRegBuffer : 如果需要更新用户寄存器数值，这个缓冲区必须指向新的寄存器数值。
//                         如果协议栈想知道当前的数值，回调函数必须将当前值写入这个缓冲区
//                        usAddress    : 寄存器的起始地址。
//                        usNRegs      : 寄存器数量
//            pucRegBuffer  读操作时--返回数据指针，写操作时--输入数据指针
//          eMode        : 如果该参数为eMBRegisterMode::MB_REG_WRITE，用户的应用数值将从pucRegBuffer中得到更新。
//                         如果该参数为eMBRegisterMode::MB_REG_READ，用户需要将当前的应用数据存储在pucRegBuffer中
//出口参数：eMBErrorCode : 这个函数将返回的错误码
/**
  * @brief  保持寄存器处理函数，保持寄存器可读，可读可写
  * @param  pucRegBuffer  读操作时--返回数据指针，写操作时--输入数据指针
  *         usAddress     寄存器起始地址
  *         usNRegs       寄存器长度
  *         eMode         操作方式，读或者写
  * @retval eStatus       寄存器状态
  */
eMBErrorCode 
eMBRegHoldingCB( UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNRegs,
                 eMBRegisterMode eMode )

{
  //错误状态
  eMBErrorCode    eStatus = MB_ENOERR;
  //偏移量
  int16_t         iRegIndex;
  usAddress--;
  //判断寄存器是不是在范围内
  if( ( (int16_t)usAddress >= REG_HOLDING_START ) \
     && ( usAddress + usNRegs <= REG_HOLDING_START + REG_HOLDING_NREGS ) )
  {
    //计算偏移量
    iRegIndex = ( int16_t )( usAddress - usRegHoldingStart );
    mode1=eMode;
    switch ( eMode )
    {
			
      //读处理函数  			
      case MB_REG_READ:
			
        while( usNRegs > 0 )
        {
          *pucRegBuffer++ = ( uint8_t )( usRegHoldingBuf[iRegIndex] >> 8 );
          *pucRegBuffer++ = ( uint8_t )( usRegHoldingBuf[iRegIndex] & 0xFF );
          iRegIndex++;
          usNRegs--;
        }				
        break;
      //写处理函数 
      case MB_REG_WRITE:
        while( usNRegs > 0 )
        {
          usRegHoldingBuf[iRegIndex] = *pucRegBuffer++ << 8;
          usRegHoldingBuf[iRegIndex] |= *pucRegBuffer++;
          iRegIndex++;
          usNRegs--;
        }	
//		eMode=MB_REG_READ;//监测软件通讯添加20190903
        break;
     }
  }
  else
  {
    //返回错误状态
    eStatus = MB_ENOREG;
  }
  
  return eStatus;
}


/**
  * @brief  线圈寄存器处理函数，线圈寄存器可读，可读可写
  * @param  pucRegBuffer  读操作---返回数据指针，写操作--返回数据指针
  *         usAddress     寄存器起始地址
  *         usNRegs       寄存器长度
  *         eMode         操作方式，读或者写
  * @retval eStatus       寄存器状态
  */
eMBErrorCode
eMBRegCoilsCB( UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNCoils,
               eMBRegisterMode eMode )
{
  //错误状态
  eMBErrorCode    eStatus = MB_ENOERR;
  //寄存器个数
  int16_t         iNCoils = ( int16_t )usNCoils;
  //寄存器偏移量
  int16_t         usBitOffset;

  //检查寄存器是否在指定范围内
  if( ( (int16_t)usAddress >= REG_COILS_START ) &&
        ( usAddress + usNCoils <= REG_COILS_START + REG_COILS_SIZE ) )
  {
    //计算寄存器偏移量
    usBitOffset = ( int16_t )( usAddress - REG_COILS_START );
    switch ( eMode )
    {
      //读操作
      case MB_REG_READ:
        while( iNCoils > 0 )
        {
          *pucRegBuffer++ = xMBUtilGetBits( ucRegCoilsBuf, usBitOffset,
                                          ( uint8_t )( iNCoils > 8 ? 8 : iNCoils ) );
          iNCoils -= 8;
          usBitOffset += 8;
        }
        break;

      //写操作
      case MB_REG_WRITE:
        while( iNCoils > 0 )
        {
          xMBUtilSetBits( ucRegCoilsBuf, usBitOffset,
                        ( uint8_t )( iNCoils > 8 ? 8 : iNCoils ),
                        *pucRegBuffer++ );
          iNCoils -= 8;
        }
        break;
    }

  }
  else
  {
    eStatus = MB_ENOREG;
  }
  return eStatus;
}

eMBErrorCode
eMBRegDiscreteCB( UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNDiscrete )
{
  //错误状态
  eMBErrorCode    eStatus = MB_ENOERR;
  //操作寄存器个数
  int16_t         iNDiscrete = ( int16_t )usNDiscrete;
  //偏移量
  uint16_t        usBitOffset;

  //判断寄存器时候再制定范围内
  if( ( (int16_t)usAddress >= REG_DISCRETE_START ) &&
        ( usAddress + usNDiscrete <= REG_DISCRETE_START + REG_DISCRETE_SIZE ) )
  {
    //获得偏移量
    usBitOffset = ( uint16_t )( usAddress - REG_DISCRETE_START );
    
    while( iNDiscrete > 0 )
    {
      *pucRegBuffer++ = xMBUtilGetBits( ucRegDiscreteBuf, usBitOffset,
                                      ( uint8_t)( iNDiscrete > 8 ? 8 : iNDiscrete ) );
      iNDiscrete -= 8;
      usBitOffset += 8;
    }

  }
  else
  {
    eStatus = MB_ENOREG;
  }
  return eStatus;
}

void modbus_tcps(uint8_t sn, uint16_t port)
{
 switch(getSn_SR(sn)) //获取socket状态
 {
      case SOCK_CLOSED:  //socket处于关闭状态
           socket(sn,Sn_MR_TCP,port,0x00); //打开socket
      break;
			case SOCK_INIT : //socket处于已经初始化状态
           listen(sn); //监听
      case SOCK_ESTABLISHED : //socket处于连接状态
				    
//			     ms2=0;
            if(getSn_IR(sn) & Sn_IR_CON)
                   {
                     setSn_IR(sn,Sn_IR_CON);
										 printf("IP=%d,SN=%d\r\n",Sn_DIPR(sn),Sn_PORT(sn) );
                    }
                  ucTCPRequestLen = getSn_RX_RSR(sn); //获取接收数据长度
								  if(ucTCPRequestLen>0)	
                   {
                      recv(sn,ucTCPRequestFrame, ucTCPRequestLen); //W5500接收数据
//					   printf("收到客户端数据:");
//					   for(int i=0;i<ucTCPRequestLen;i++)
//						printf(" %02x",ucTCPRequestFrame[i]);
//					   printf("\r\n");
                      xMBPortEventPost(EV_FRAME_RECEIVED);  //发送EV_FRAME_RECEIVED事件，以驱动eMBpoll()函数中的状态机
                      eMBPoll();  //处理EV_FRAME_RECEIVED事件
                      eMBPoll();  //处理EV_EXECUTE事件
                      if(bFrameSent) 
                      { 
                          bFrameSent = FALSE; 
                      //W5500发送Modbus应答数据包 	
                      send(sn,ucTCPResponseFrame,ucTCPResponseLen);    
                      } 
//											if(ucTCPRequestFrame[6]==01) ms3=0;
//											if(ucTCPRequestFrame[6]==02) ms4=0;
                    }
        break;
        case SOCK_CLOSE_WAIT :  //socket处于等待关闭状态
        disconnect(sn);//关闭连接
				printf("关闭连接\r\n");
        break;
        default:
        break;
 }
}
//void do_tcp_client(void)
// {        
//    uint16_t len=0;        

//         switch(getSn_SR(0))                                        /*获取socket的状态*/
//         {
//					 case SOCK_CLOSED:                                        /*socket处于关闭状态*/
//									 socket(0,Sn_MR_TCP,local_port,Sn_MR_ND);
//						 break;
//					 
//					 case SOCK_INIT:                                          /*socket处于初始化状态*/
//									 connect(0,server_ip,server_port);                /*socket连接服务器*/ 
//						 break;
//					 
//					 case SOCK_ESTABLISHED:                                  /*socket处于连接建立状态*/
//									 if(getSn_IR(0) & Sn_IR_CON)
//									 {
//													 setSn_IR(0, Sn_IR_CON);                 /*清除接收中断标志位*/
//									 }
//					 
//									 len=getSn_RX_RSR(0);                            /*定义len为已接收数据的长度*/
//									 if(len>0)
//									 {
//													 recv(0,buffer,len);                     /*接收来自Server的数据*/
//													 buffer[len]=0x00;                       /*添加字符串结束符*/
//													 printf("%s\r\n",buffer);
//													 send(0,buffer,len);                     /*向Server发送数据*/
//									 }                  
//						 break;
//									 
//					 case SOCK_CLOSE_WAIT:                               /*socket处于等待关闭状态*/
//									 close(0);
//						 break;

//         }
// }

void TX_Heart()
{ 
	
	uint16_t heart1;
	H3=ucTCPRequestFrame[6];	
	heart1=ucTCPRequestFrame[0] <<8 | ucTCPRequestFrame[1];

   if(ms1==50 && ucTCPRequestFrame[6]==01)
	 {
	    H1=heart1;
	 }
	 if(ms1>=100 && ucTCPRequestFrame[6]==01)
	 {
	    H2=heart1;
			 
		 if(H1 != H2  )
		 {
			 ms1=0;
			 rst=0;
		 }
		}	
		 if(ms1>600&& rst<2)
		 { 
			 if(rst==0)
				{
					
//		      Relay5(OFF);//车载AP模块上电
//			    HAL_Delay(5000);
//		      Relay5(ON);//车载AP模块上电
					rst=1;
			  } 
		 }
				
				if(ms1>1200&&rst<2)
				{ 
					rst=2	;
					DateSave();	
					  HAL_Delay(100);// 短延时				
					  SoftReset();	
          		
				}
					
		
   
}
///*原程序*/
////eMBErrorCode
////eMBRegInputCB( UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNRegs )
////{
////    eMBErrorCode    eStatus = MB_ENOERR;
////	static uint8_t flag = 0;
////	
////	flag == 0 ?  HAL_GPIO_WritePin(GPIOE, GPIO_PIN_0, GPIO_PIN_SET) : HAL_GPIO_WritePin(GPIOE, GPIO_PIN_0, GPIO_PIN_RESET);  
////	flag ^= 1;
////    return eStatus;
////}

////eMBErrorCode
////eMBRegHoldingCB( UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNRegs, eMBRegisterMode eMode )
////{
////	eMBErrorCode    eStatus = MB_ENOERR;
////	static uint8_t flag = 0;
////	
////	flag == 0 ?  HAL_GPIO_WritePin(GPIOE, GPIO_PIN_0, GPIO_PIN_SET) : HAL_GPIO_WritePin(GPIOE, GPIO_PIN_0, GPIO_PIN_RESET);  
////	flag ^= 1;
////    return eStatus;
////}

////eMBErrorCode
////eMBRegCoilsCB( UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNCoils, eMBRegisterMode eMode )
////{
////    static uint8_t flag = 0;
////	
////	flag == 0 ?  HAL_GPIO_WritePin(GPIOE, GPIO_PIN_0, GPIO_PIN_SET) : HAL_GPIO_WritePin(GPIOE, GPIO_PIN_0, GPIO_PIN_RESET);    
////	flag ^= 1;
////	return MB_ENOREG;
////}

////eMBErrorCode
////eMBRegDiscreteCB( UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNDiscrete )
////{
////    static uint8_t flag = 0;
////	
////	flag == 0 ?  HAL_GPIO_WritePin(GPIOE, GPIO_PIN_0, GPIO_PIN_SET) : HAL_GPIO_WritePin(GPIOE, GPIO_PIN_0, GPIO_PIN_RESET);    
////	flag ^= 1;
////	return MB_ENOREG;
////}

///**
//  * @}
//  */


///*******************文件结尾**************************************************/
