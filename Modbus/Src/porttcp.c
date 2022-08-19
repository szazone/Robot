/*

*/

/* ----------------------- System includes ----------------------------------*/
#include <stdio.h>
#include <string.h>
#include "port.h"
#include "w5500.h"
#include "socket.h"

/* ----------------------- Modbus includes ----------------------------------*/
#include "mb.h"
#include "mbport.h"

//modbus ���շ��ͼĴ�����ȫ�ֱ���
#define MB_TCP_BUF_SIZE  2048
extern uint8_t ucTCPRequestFrame[MB_TCP_BUF_SIZE]; //���ռĴ���
extern uint16_t ucTCPRequestLen;
extern uint8_t ucTCPResponseFrame[MB_TCP_BUF_SIZE]; //���ͼĴ���
extern uint16_t ucTCPResponseLen;
extern uint8_t bFrameSent ;  //�Ƿ���з�����Ӧ�ж�

BOOL xMBTCPPortInit( USHORT usTCPPort )
{
 SOCKET sn;
   sn=0;
   if(getSn_SR(sn)==SOCK_CLOSED)
   {
    socket(sn,Sn_MR_TCP,usTCPPort,0x00);//��socket
   }
   if (getSn_SR(sn)==SOCK_INIT)
  {
  listen(sn); //����
   return TRUE;
   }
  return FALSE;
}

BOOL  xMBTCPPortGetRequest( UCHAR **ppucMBTCPFrame, USHORT * usTCPLength )
{
    *ppucMBTCPFrame = (uint8_t *) &ucTCPRequestFrame[0]; 
    *usTCPLength = ucTCPRequestLen;
    /* Reset the buffer. */ 
   ucTCPRequestLen = 0;
    return TRUE;
}


BOOL xMBTCPPortSendResponse( const UCHAR *pucMBTCPFrame, USHORT usTCPLength )
{  
     memcpy(ucTCPResponseFrame,pucMBTCPFrame , usTCPLength);
     ucTCPResponseLen = usTCPLength;
     bFrameSent = TRUE; // ͨ��W5500�������� ?
     return bFrameSent;
}


void vMBTCPPortClose( void )
{
};

void vMBTCPPortDisable( void )
{
};

