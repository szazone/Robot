/**
  ******************************************************************************
  * @file    Hinson_CNS_MGS.c
  * @author  szazone
  * @version V0.0.1
  * @date    03-August-2022
  * @brief   Hinson CNS_MSG series magnetic sensor CANOpen protocol source file.
  *
  ******************************************************************************
  */ 

/* Includes ------------------------------------------------------------------*/
#include "Hinson_CNS_MGS.h"

// Application/User/Core
#include "can.h"
// Middlewares/FreeRTOS
#include "cmsis_os2.h"
// Hardware
#include "canOpen.h"

//报文
CanOpen_OD_t Hinson_CNS_MGS_MagSwitch = {0x2000,0x00,4,0x0000};		// 磁场点开关信号数据
CanOpen_OD_t Hinson_CNS_MGS_MagSensorData_Num = {0x2001,0x00,1,18};	// 磁场强度数据对象子 索引数
CanOpen_OD_t Hinson_CNS_MGS_MagSensorData_value[] = {				// 磁场强度数据
	{0x2001,0x01,2,0},
	{0x2001,0x02,2,0},
	{0x2001,0x03,2,0},
	{0x2001,0x04,2,0},
	{0x2001,0x05,2,0},
	{0x2001,0x06,2,0},
	{0x2001,0x07,2,0},
	{0x2001,0x08,2,0},
	{0x2001,0x09,2,0},
	{0x2001,0x0A,2,0},
	{0x2001,0x0B,2,0},
	{0x2001,0x0C,2,0},
	{0x2001,0x0D,2,0},
	{0x2001,0x0E,2,0},
	{0x2001,0x0F,2,0},
	{0x2001,0x10,2,0},
	{0x2001,0x11,2,0},
	{0x2001,0x12,2,0},
};
CanOpen_OD_t Hinson_CNS_MGS_FaultStatus = {0x2002,0x00,1,0};		// 传感器状态
CanOpen_OD_t Hinson_CNS_MGS_MagPoisStatus = {0x2003,0x00,1,0};		// 磁条感应状态
CanOpen_OD_t Hinson_CNS_MGS_ForkSelect = {0x2004,0x00,1,0};			// 岔路选择
CanOpen_OD_t Hinson_CNS_MGS_SelectPoistion = {0x2005,0x00,2,0};		// 岔路选择返回磁条位置
CanOpen_OD_t Hinson_CNS_MGS_SelectStrength = {0x2006,0x00,2,0};		// 岔路选择返回磁场强度
CanOpen_OD_t Hinson_CNS_MGS_SelectPointNum = {0x2007,0x00,2,0};		// 岔路选择返回磁感应点数
CanOpen_OD_t Hinson_CNS_MGS_LeftPoistion = {0x2008,0x00,2,0};		// 左侧磁条位置
CanOpen_OD_t Hinson_CNS_MGS_MiddPosition = {0x2009,0x00,2,0};		// 中间磁条位置
CanOpen_OD_t Hinson_CNS_MGS_RightPosition = {0x200A,0x00,2,0};		// 右侧磁条位置
CanOpen_OD_t Hinson_CNS_MGS_LeftStrength = {0x200B,0x00,2,0};		// 左侧磁条平均强度值
CanOpen_OD_t Hinson_CNS_MGS_MiddStrength = {0x200C,0x00,2,0};		// 中间磁条平均强度值
CanOpen_OD_t Hinson_CNS_MGS_RightStrength = {0x200D,0x00,2,0};		// 右侧磁条平均强度值
CanOpen_OD_t Hinson_CNS_MGS_LeftPointNum = {0x200E,0x00,2,0};		// 左侧磁条感应点数
CanOpen_OD_t Hinson_CNS_MGS_MiddPointNum = {0x2009,0x00,2,0};		// 中间磁条感应点数
CanOpen_OD_t Hinson_CNS_MGS_RightPointNum = {0x2010,0x00,2,0};		// 右侧磁条感应点数
CanOpen_OD_t Hinson_CNS_MGS_SensorPolarity = {0x2011,0x00,2,0};		// 磁条感应极性
CanOpen_OD_t Hinson_CNS_MGS_MinPointNumber = {0x2012,0x00,2,1};		// 最少感应点数
CanOpen_OD_t Hinson_CNS_MGS_MaxPointNumber = {0x2013,0x00,2,4};		// 最大感应点数
CanOpen_OD_t Hinson_CNS_MGS_PointDifference = {0x2014,0x00,2,0};	// 磁条区分度
CanOpen_OD_t Hinson_CNS_MGS_SensorSensitivity = {0x2015,0x00,2,0};	// 灵敏度调节
CanOpen_OD_t Hinson_CNS_MGS_MiddCenterPostion = {0x2016,0x00,2,0};	// 中间偏移（155mm-195mm）
CanOpen_OD_t Hinson_CNS_MGS_CanIDAddress = {0x2017,0x00,2,0};		// CAN BUS 地址（1-127）
CanOpen_OD_t Hinson_CNS_MGS_CanBaudRate = {0x2018,0x00,2,0};		// CAN BUS 波特率
CanOpen_OD_t Hinson_CNS_MGS_WriteCommand = {0x2019,0x00,2,0};		// 参数写入
CanOpen_OD_t Hinson_CNS_MGS_RebootSensor = {0x201A,0x00,2,0};		// 传感器重启
