#ifndef _DEFINE_H_
#define _DEFINE_H_

/* Exported types ------------------------------------------------------------*/
typedef unsigned char   INT8U;
typedef signed   char   INT8S;
typedef unsigned short  INT16U;
typedef signed   short  INT16S;
typedef unsigned int    INT32U;
typedef signed   int    INT32S;
typedef          int    INT32;
typedef          long   _iq;
typedef          INT32S _iq24; 
typedef unsigned long long       INT64U;
typedef signed   long long       INT64S;
typedef float                    FP32;
typedef float                    FLOAT32;
typedef double                   FP64;


#define IQ1         16777216L
#define IQtoF1(x)   (FLOAT32)((FLOAT32)(x) / 16777216.0L)
#define _IQ(x)      (_iq)((x) * 16777216.0L)
#define IQmpy1(x,y) (_iq)(((INT64S)(x) * (y)) >> 24)
#define IQdiv1(x,y) (_iq)(((INT64S)(x) << 24) / (y))

#define _IQ0(x)    (_iq)((x) * 1.0L)
#define _IQ1(x)    (_iq)((x) * 2.0L)
#define _IQ2(x)    (_iq)((x) * 4.0L)
#define _IQ3(x)    (_iq)((x) * 8.0L)
#define _IQ4(x)    (_iq)((x) * 16.0L)
#define _IQ5(x)    (_iq)((x) * 32.0L)
#define _IQ6(x)    (_iq)((x) * 64.0L)
#define _IQ7(x)    (_iq)((x) * 128.0L)
#define _IQ8(x)    (_iq)((x) * 256.0L)
#define _IQ9(x)    (_iq)((x) * 512.0L)
#define _IQ10(x)    (_iq)((x) * 1024.0L)
#define _IQ11(x)    (_iq)((x) * 2048.0L)
#define _IQ12(x)    (_iq)((x) * 4096.0L)
#define _IQ13(x)    (_iq)((x) * 8192.0L)
#define _IQ14(x)    (_iq)((x) * 16384.0L)
#define _IQ15(x)    (_iq)((x) * 32768.0L)
#define _IQ16(x)    (_iq)((x) * 65536.0L)
#define _IQ17(x)    (_iq)((x) * 131072.0L)
#define _IQ18(x)    (_iq)((x) * 262144.0L)
#define _IQ19(x)    (_iq)((x) * 524288.0L)
#define _IQ20(x)    (_iq)((x) * 1048576.0L)
#define _IQ21(x)    (_iq)((x) * 2097152.0L)
#define _IQ22(x)    (_iq)((x) * 4194304.0L)
#define _IQ23(x)    (_iq)((x) * 8388608.0L)
#define _IQ24(x)    (_iq)((x) * 16777216.0L)
#define _IQ25(x)    (_iq)((x) * 33554432.0L)
#define _IQ26(x)    (_iq)((x) * 67108864.0L)
#define _IQ27(x)    (_iq)((x) * 134217728.0L)
#define _IQ28(x)    (_iq)((x) * 268435456.0L)
#define _IQ29(x)    (_iq)((x) * 536870912.0L)
#define _IQ30(x)    (_iq)((x) * 1073741824.0L)
#define _IQ31(x)    (_iq)((x) * 2147483648.0L)

#define _IQ0mpy(x,y) (_iq)(((INT64S)(x) * (y)) >> 0)
#define _IQ1mpy(x,y) (_iq)(((INT64S)(x) * (y)) >> 1)
#define _IQ2mpy(x,y) (_iq)(((INT64S)(x) * (y)) >> 2)
#define _IQ3mpy(x,y) (_iq)(((INT64S)(x) * (y)) >> 3)
#define _IQ4mpy(x,y) (_iq)(((INT64S)(x) * (y)) >> 4)
#define _IQ5mpy(x,y) (_iq)(((INT64S)(x) * (y)) >> 5)
#define _IQ6mpy(x,y) (_iq)(((INT64S)(x) * (y)) >> 6)
#define _IQ7mpy(x,y) (_iq)(((INT64S)(x) * (y)) >> 7)
#define _IQ8mpy(x,y) (_iq)(((INT64S)(x) * (y)) >> 8)
#define _IQ9mpy(x,y) (_iq)(((INT64S)(x) * (y)) >> 9)
#define _IQ10mpy(x,y) (_iq)(((INT64S)(x) * (y)) >> 10)
#define _IQ11mpy(x,y) (_iq)(((INT64S)(x) * (y)) >> 11)
#define _IQ12mpy(x,y) (_iq)(((INT64S)(x) * (y)) >> 12)
#define _IQ13mpy(x,y) (_iq)(((INT64S)(x) * (y)) >> 13)
#define _IQ14mpy(x,y) (_iq)(((INT64S)(x) * (y)) >> 14)
#define _IQ15mpy(x,y) (_iq)(((INT64S)(x) * (y)) >> 15)
#define _IQ16mpy(x,y) (_iq)(((INT64S)(x) * (y)) >> 16)
#define _IQ17mpy(x,y) (_iq)(((INT64S)(x) * (y)) >> 17)
#define _IQ18mpy(x,y) (_iq)(((INT64S)(x) * (y)) >> 18)
#define _IQ19mpy(x,y) (_iq)(((INT64S)(x) * (y)) >> 19)
#define _IQ20mpy(x,y) (_iq)(((INT64S)(x) * (y)) >> 20)
#define _IQ21mpy(x,y) (_iq)(((INT64S)(x) * (y)) >> 21)
#define _IQ22mpy(x,y) (_iq)(((INT64S)(x) * (y)) >> 22)
#define _IQ23mpy(x,y) (_iq)(((INT64S)(x) * (y)) >> 23)
#define _IQ24mpy(x,y) (_iq)(((INT64S)(x) * (y)) >> 24)
#define _IQ25mpy(x,y) (_iq)(((INT64S)(x) * (y)) >> 25)
#define _IQ26mpy(x,y) (_iq)(((INT64S)(x) * (y)) >> 26)
#define _IQ27mpy(x,y) (_iq)(((INT64S)(x) * (y)) >> 27)
#define _IQ28mpy(x,y) (_iq)(((INT64S)(x) * (y)) >> 28)
#define _IQ29mpy(x,y) (_iq)(((INT64S)(x) * (y)) >> 29)
#define _IQ30mpy(x,y) (_iq)(((INT64S)(x) * (y)) >> 30)
#define _IQ31mpy(x,y) (_iq)(((INT64S)(x) * (y)) >> 31)

#define _IQ0div(x,y) (_iq)(((INT64S)(x) << 0) / (y))
#define _IQ1div(x,y) (_iq)(((INT64S)(x) << 1) / (y))
#define _IQ2div(x,y) (_iq)(((INT64S)(x) << 2) / (y))
#define _IQ3div(x,y) (_iq)(((INT64S)(x) << 3) / (y))
#define _IQ4div(x,y) (_iq)(((INT64S)(x) << 4) / (y))
#define _IQ5div(x,y) (_iq)(((INT64S)(x) << 5) / (y))
#define _IQ6div(x,y) (_iq)(((INT64S)(x) << 6) / (y))
#define _IQ7div(x,y) (_iq)(((INT64S)(x) << 7) / (y))
#define _IQ8div(x,y) (_iq)(((INT64S)(x) << 8) / (y))
#define _IQ9div(x,y) (_iq)(((INT64S)(x) << 9) / (y))
#define _IQ10div(x,y) (_iq)(((INT64S)(x) << 10) / (y))
#define _IQ11div(x,y) (_iq)(((INT64S)(x) << 11) / (y))
#define _IQ12div(x,y) (_iq)(((INT64S)(x) << 12) / (y))
#define _IQ13div(x,y) (_iq)(((INT64S)(x) << 13) / (y))
#define _IQ14div(x,y) (_iq)(((INT64S)(x) << 14) / (y))
#define _IQ15div(x,y) (_iq)(((INT64S)(x) << 15) / (y))
#define _IQ16div(x,y) (_iq)(((INT64S)(x) << 16) / (y))
#define _IQ17div(x,y) (_iq)(((INT64S)(x) << 17) / (y))
#define _IQ18div(x,y) (_iq)(((INT64S)(x) << 18) / (y))
#define _IQ19div(x,y) (_iq)(((INT64S)(x) << 19) / (y))
#define _IQ20div(x,y) (_iq)(((INT64S)(x) << 20) / (y))
#define _IQ21div(x,y) (_iq)(((INT64S)(x) << 21) / (y))
#define _IQ22div(x,y) (_iq)(((INT64S)(x) << 22) / (y))
#define _IQ23div(x,y) (_iq)(((INT64S)(x) << 23) / (y))
#define _IQ24div(x,y) (_iq)(((INT64S)(x) << 24) / (y))
#define _IQ25div(x,y) (_iq)(((INT64S)(x) << 25) / (y))
#define _IQ26div(x,y) (_iq)(((INT64S)(x) << 26) / (y))
#define _IQ27div(x,y) (_iq)(((INT64S)(x) << 27) / (y))
#define _IQ28div(x,y) (_iq)(((INT64S)(x) << 28) / (y))
#define _IQ29div(x,y) (_iq)(((INT64S)(x) << 29) / (y))
#define _IQ30div(x,y) (_iq)(((INT64S)(x) << 30) / (y))
#define _IQ31div(x,y) (_iq)(((INT64S)(x) << 31) / (y))

#define PIQ23	26353589.0
#define PIQ24	52707178.0

#define _IQ22sinPU(x)	(IQsinPU1((x)<<2)>>2)
#define _IQ22cosPU(x)	(IQcosPU1((x)<<2)>>2)
#define _IQ23sin(x)		(IQsinPU1(_IQ24((x)/PIQ24))>>1)
#define _IQ23cos(x)		(IQcosPU1(_IQ24((x)/PIQ24))>>1)		//x/2/pi Q23


#define MAX(a,b)  (((a) > (b)) ? (a) : (b)) 
#define MIN(a,b)  (((a) < (b)) ? (a) : (b)) 



#endif
