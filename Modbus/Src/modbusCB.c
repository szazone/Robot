 
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
//���ض˿�
#define local_port 6000
uint8_t server_ip[4]={192,168,166,150};			// ����Զ�̷�����IP��ַ
uint16_t server_port=502;								// ����Զ�̷������˿�
uint8_t buffer[2048];									// ����һ��2KB�����飬�������Socket��ͨ������





//����Ĵ�����ʼ��ַ
#define REG_INPUT_START       0x0000
//����Ĵ�������
#define REG_INPUT_NREGS       8
//���ּĴ�����ʼ��ַ
#define REG_HOLDING_START     0x0000
//���ּĴ�������
#define REG_HOLDING_NREGS     256

//��Ȧ��ʼ��ַ
#define REG_COILS_START       0x0000
//��Ȧ����
#define REG_COILS_SIZE        16

//���ؼĴ�����ʼ��ַ
#define REG_DISCRETE_START    0x0000
//���ؼĴ�������
#define REG_DISCRETE_SIZE     16

/* Private variables ---------------------------------------------------------*/
int mode1;
//����Ĵ�������
uint16_t usRegInputBuf[REG_INPUT_NREGS] = {0x1000,0x1001,0x1002,0x1003,0x1004,0x1005,0x1006,0x1007};
//�Ĵ�����ʼ��ַ
uint16_t usRegInputStart = REG_INPUT_START;

//���ּĴ�������
uint16_t usRegHoldingBuf[REG_HOLDING_NREGS];
//���ּĴ�����ʼ��ַ
uint16_t usRegHoldingStart = REG_HOLDING_START;

//��Ȧ״̬
uint8_t ucRegCoilsBuf[REG_COILS_SIZE / 8] = {0x01,0x02};
//��������״̬
uint8_t ucRegDiscreteBuf[REG_DISCRETE_SIZE / 8] = {0x01,0x02};

//modbus ���շ��ͼĴ�����ȫ�ֱ���
//#define MB_TCP_BUF_SIZE  1024
//#define MBTCP_PORT 502;
 uint8_t ucTCPRequestFrame[MB_TCP_BUF_SIZE]; //���ռĴ���
 uint16_t ucTCPRequestLen;
 uint8_t ucTCPResponseFrame[MB_TCP_BUF_SIZE]; //���ͼĴ���
 uint16_t ucTCPResponseLen;
 uint8_t bFrameSent;  //�Ƿ���з�����Ӧ�ж�

// extern uint16_t usRegHoldingBuf[8];
/**
  * @brief  ����Ĵ���������������Ĵ����ɶ���������д��
  * @param  pucRegBuffer  ��������ָ��
  *         usAddress     �Ĵ�����ʼ��ַ
  *         usNRegs       �Ĵ�������
  * @retval eStatus       �Ĵ���״̬
  */
eMBErrorCode 
eMBRegInputCB( UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNRegs )
{
  eMBErrorCode    eStatus = MB_ENOERR;
  int16_t         iRegIndex;
  
  //��ѯ�Ƿ��ڼĴ�����Χ��
  //Ϊ�˱��⾯�棬�޸�Ϊ�з�������
  if( ( (int16_t)usAddress >= REG_INPUT_START ) \
        && ( usAddress + usNRegs <= REG_INPUT_START + REG_INPUT_NREGS ) )
  {
    //��ò���ƫ���������β�����ʼ��ַ-����Ĵ����ĳ�ʼ��ַ
    iRegIndex = ( int16_t )( usAddress - usRegInputStart );
    //�����ֵ
    while( usNRegs > 0 )
    {
      //��ֵ���ֽ�
      *pucRegBuffer++ = ( uint8_t )( usRegInputBuf[iRegIndex] >> 8 );
      //��ֵ���ֽ�
      *pucRegBuffer++ = ( uint8_t )( usRegInputBuf[iRegIndex] & 0xFF );
      //ƫ��������
      iRegIndex++;
      //�������Ĵ��������ݼ�
      usNRegs--;
    }
  }
  else
  {
    //���ش���״̬���޼Ĵ���  
    eStatus = MB_ENOREG;
  }

  return eStatus;
}
//******************************���ּĴ����ص�����**********************************
//��������: eMBErrorCode eMBRegHoldingCB( UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNRegs, eMBRegisterMode eMode )
//��    �������ּĴ�����صĹ��ܣ�������������д������д��
//��ڲ�����pucRegBuffer : �����Ҫ�����û��Ĵ�����ֵ���������������ָ���µļĴ�����ֵ��
//                         ���Э��ջ��֪����ǰ����ֵ���ص��������뽫��ǰֵд�����������
//                        usAddress    : �Ĵ�������ʼ��ַ��
//                        usNRegs      : �Ĵ�������
//            pucRegBuffer  ������ʱ--��������ָ�룬д����ʱ--��������ָ��
//          eMode        : ����ò���ΪeMBRegisterMode::MB_REG_WRITE���û���Ӧ����ֵ����pucRegBuffer�еõ����¡�
//                         ����ò���ΪeMBRegisterMode::MB_REG_READ���û���Ҫ����ǰ��Ӧ�����ݴ洢��pucRegBuffer��
//���ڲ�����eMBErrorCode : ������������صĴ�����
/**
  * @brief  ���ּĴ��������������ּĴ����ɶ����ɶ���д
  * @param  pucRegBuffer  ������ʱ--��������ָ�룬д����ʱ--��������ָ��
  *         usAddress     �Ĵ�����ʼ��ַ
  *         usNRegs       �Ĵ�������
  *         eMode         ������ʽ��������д
  * @retval eStatus       �Ĵ���״̬
  */
eMBErrorCode 
eMBRegHoldingCB( UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNRegs,
                 eMBRegisterMode eMode )

{
  //����״̬
  eMBErrorCode    eStatus = MB_ENOERR;
  //ƫ����
  int16_t         iRegIndex;
  usAddress--;
  //�жϼĴ����ǲ����ڷ�Χ��
  if( ( (int16_t)usAddress >= REG_HOLDING_START ) \
     && ( usAddress + usNRegs <= REG_HOLDING_START + REG_HOLDING_NREGS ) )
  {
    //����ƫ����
    iRegIndex = ( int16_t )( usAddress - usRegHoldingStart );
    mode1=eMode;
    switch ( eMode )
    {
			
      //��������  			
      case MB_REG_READ:
			
        while( usNRegs > 0 )
        {
          *pucRegBuffer++ = ( uint8_t )( usRegHoldingBuf[iRegIndex] >> 8 );
          *pucRegBuffer++ = ( uint8_t )( usRegHoldingBuf[iRegIndex] & 0xFF );
          iRegIndex++;
          usNRegs--;
        }				
        break;
      //д������ 
      case MB_REG_WRITE:
        while( usNRegs > 0 )
        {
          usRegHoldingBuf[iRegIndex] = *pucRegBuffer++ << 8;
          usRegHoldingBuf[iRegIndex] |= *pucRegBuffer++;
          iRegIndex++;
          usNRegs--;
        }	
//		eMode=MB_REG_READ;//������ͨѶ���20190903
        break;
     }
  }
  else
  {
    //���ش���״̬
    eStatus = MB_ENOREG;
  }
  
  return eStatus;
}


/**
  * @brief  ��Ȧ�Ĵ�������������Ȧ�Ĵ����ɶ����ɶ���д
  * @param  pucRegBuffer  ������---��������ָ�룬д����--��������ָ��
  *         usAddress     �Ĵ�����ʼ��ַ
  *         usNRegs       �Ĵ�������
  *         eMode         ������ʽ��������д
  * @retval eStatus       �Ĵ���״̬
  */
eMBErrorCode
eMBRegCoilsCB( UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNCoils,
               eMBRegisterMode eMode )
{
  //����״̬
  eMBErrorCode    eStatus = MB_ENOERR;
  //�Ĵ�������
  int16_t         iNCoils = ( int16_t )usNCoils;
  //�Ĵ���ƫ����
  int16_t         usBitOffset;

  //���Ĵ����Ƿ���ָ����Χ��
  if( ( (int16_t)usAddress >= REG_COILS_START ) &&
        ( usAddress + usNCoils <= REG_COILS_START + REG_COILS_SIZE ) )
  {
    //����Ĵ���ƫ����
    usBitOffset = ( int16_t )( usAddress - REG_COILS_START );
    switch ( eMode )
    {
      //������
      case MB_REG_READ:
        while( iNCoils > 0 )
        {
          *pucRegBuffer++ = xMBUtilGetBits( ucRegCoilsBuf, usBitOffset,
                                          ( uint8_t )( iNCoils > 8 ? 8 : iNCoils ) );
          iNCoils -= 8;
          usBitOffset += 8;
        }
        break;

      //д����
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
  //����״̬
  eMBErrorCode    eStatus = MB_ENOERR;
  //�����Ĵ�������
  int16_t         iNDiscrete = ( int16_t )usNDiscrete;
  //ƫ����
  uint16_t        usBitOffset;

  //�жϼĴ���ʱ�����ƶ���Χ��
  if( ( (int16_t)usAddress >= REG_DISCRETE_START ) &&
        ( usAddress + usNDiscrete <= REG_DISCRETE_START + REG_DISCRETE_SIZE ) )
  {
    //���ƫ����
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
 switch(getSn_SR(sn)) //��ȡsocket״̬
 {
      case SOCK_CLOSED:  //socket���ڹر�״̬
           socket(sn,Sn_MR_TCP,port,0x00); //��socket
      break;
			case SOCK_INIT : //socket�����Ѿ���ʼ��״̬
           listen(sn); //����
      case SOCK_ESTABLISHED : //socket��������״̬
				    
//			     ms2=0;
            if(getSn_IR(sn) & Sn_IR_CON)
                   {
                     setSn_IR(sn,Sn_IR_CON);
										 printf("IP=%d,SN=%d\r\n",Sn_DIPR(sn),Sn_PORT(sn) );
                    }
                  ucTCPRequestLen = getSn_RX_RSR(sn); //��ȡ�������ݳ���
								  if(ucTCPRequestLen>0)	
                   {
                      recv(sn,ucTCPRequestFrame, ucTCPRequestLen); //W5500��������
//					   printf("�յ��ͻ�������:");
//					   for(int i=0;i<ucTCPRequestLen;i++)
//						printf(" %02x",ucTCPRequestFrame[i]);
//					   printf("\r\n");
                      xMBPortEventPost(EV_FRAME_RECEIVED);  //����EV_FRAME_RECEIVED�¼���������eMBpoll()�����е�״̬��
                      eMBPoll();  //����EV_FRAME_RECEIVED�¼�
                      eMBPoll();  //����EV_EXECUTE�¼�
                      if(bFrameSent) 
                      { 
                          bFrameSent = FALSE; 
                      //W5500����ModbusӦ�����ݰ� 	
                      send(sn,ucTCPResponseFrame,ucTCPResponseLen);    
                      } 
//											if(ucTCPRequestFrame[6]==01) ms3=0;
//											if(ucTCPRequestFrame[6]==02) ms4=0;
                    }
        break;
        case SOCK_CLOSE_WAIT :  //socket���ڵȴ��ر�״̬
        disconnect(sn);//�ر�����
				printf("�ر�����\r\n");
        break;
        default:
        break;
 }
}
//void do_tcp_client(void)
// {        
//    uint16_t len=0;        

//         switch(getSn_SR(0))                                        /*��ȡsocket��״̬*/
//         {
//					 case SOCK_CLOSED:                                        /*socket���ڹر�״̬*/
//									 socket(0,Sn_MR_TCP,local_port,Sn_MR_ND);
//						 break;
//					 
//					 case SOCK_INIT:                                          /*socket���ڳ�ʼ��״̬*/
//									 connect(0,server_ip,server_port);                /*socket���ӷ�����*/ 
//						 break;
//					 
//					 case SOCK_ESTABLISHED:                                  /*socket�������ӽ���״̬*/
//									 if(getSn_IR(0) & Sn_IR_CON)
//									 {
//													 setSn_IR(0, Sn_IR_CON);                 /*��������жϱ�־λ*/
//									 }
//					 
//									 len=getSn_RX_RSR(0);                            /*����lenΪ�ѽ������ݵĳ���*/
//									 if(len>0)
//									 {
//													 recv(0,buffer,len);                     /*��������Server������*/
//													 buffer[len]=0x00;                       /*����ַ���������*/
//													 printf("%s\r\n",buffer);
//													 send(0,buffer,len);                     /*��Server��������*/
//									 }                  
//						 break;
//									 
//					 case SOCK_CLOSE_WAIT:                               /*socket���ڵȴ��ر�״̬*/
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
					
//		      Relay5(OFF);//����APģ���ϵ�
//			    HAL_Delay(5000);
//		      Relay5(ON);//����APģ���ϵ�
					rst=1;
			  } 
		 }
				
				if(ms1>1200&&rst<2)
				{ 
					rst=2	;
					DateSave();	
					  HAL_Delay(100);// ����ʱ				
					  SoftReset();	
          		
				}
					
		
   
}
///*ԭ����*/
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


///*******************�ļ���β**************************************************/
