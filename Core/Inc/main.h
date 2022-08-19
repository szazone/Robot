/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define RGB_PIN_G2_Pin GPIO_PIN_2
#define RGB_PIN_G2_GPIO_Port GPIOE
#define RGB_PIN_B_Pin GPIO_PIN_3
#define RGB_PIN_B_GPIO_Port GPIOE
#define RGB_PIN_STR_Pin GPIO_PIN_4
#define RGB_PIN_STR_GPIO_Port GPIOE
#define WDI_Pin GPIO_PIN_13
#define WDI_GPIO_Port GPIOC
#define USART4_TXD_Pin GPIO_PIN_0
#define USART4_TXD_GPIO_Port GPIOA
#define USART4_RXD_Pin GPIO_PIN_1
#define USART4_RXD_GPIO_Port GPIOA
#define BAT_EN_Pin GPIO_PIN_2
#define BAT_EN_GPIO_Port GPIOA
#define EM_SIG_Pin GPIO_PIN_3
#define EM_SIG_GPIO_Port GPIOA
#define COMP_SIG_Pin GPIO_PIN_4
#define COMP_SIG_GPIO_Port GPIOA
#define IN_Pin GPIO_PIN_5
#define IN_GPIO_Port GPIOA
#define GREEN_CTL_Pin GPIO_PIN_6
#define GREEN_CTL_GPIO_Port GPIOA
#define RED_CTL_Pin GPIO_PIN_7
#define RED_CTL_GPIO_Port GPIOA
#define BLUE_CTL_Pin GPIO_PIN_0
#define BLUE_CTL_GPIO_Port GPIOB
#define LED_RIGHT_CTL_Pin GPIO_PIN_7
#define LED_RIGHT_CTL_GPIO_Port GPIOE
#define LED_LEFT_CTL_Pin GPIO_PIN_8
#define LED_LEFT_CTL_GPIO_Port GPIOE
#define LED_RUN_Pin GPIO_PIN_13
#define LED_RUN_GPIO_Port GPIOE
#define LED_ALARM_Pin GPIO_PIN_14
#define LED_ALARM_GPIO_Port GPIOE
#define LED_ERROR_Pin GPIO_PIN_15
#define LED_ERROR_GPIO_Port GPIOE
#define IIC_SCL_Pin GPIO_PIN_10
#define IIC_SCL_GPIO_Port GPIOB
#define IIC_SDA_Pin GPIO_PIN_11
#define IIC_SDA_GPIO_Port GPIOB
#define IO1_Pin GPIO_PIN_12
#define IO1_GPIO_Port GPIOB
#define IO2_Pin GPIO_PIN_13
#define IO2_GPIO_Port GPIOB
#define USART6_TX_Pin GPIO_PIN_6
#define USART6_TX_GPIO_Port GPIOC
#define USART6_RX_Pin GPIO_PIN_7
#define USART6_RX_GPIO_Port GPIOC
#define USART1_TX_Pin GPIO_PIN_9
#define USART1_TX_GPIO_Port GPIOA
#define USART1_RX_Pin GPIO_PIN_10
#define USART1_RX_GPIO_Port GPIOA
#define SWDIO_Pin GPIO_PIN_13
#define SWDIO_GPIO_Port GPIOA
#define SWCLK_Pin GPIO_PIN_14
#define SWCLK_GPIO_Port GPIOA
#define MCU485_TX_Pin GPIO_PIN_12
#define MCU485_TX_GPIO_Port GPIOC
#define CAN_RX_Pin GPIO_PIN_0
#define CAN_RX_GPIO_Port GPIOD
#define CAN_TX_Pin GPIO_PIN_1
#define CAN_TX_GPIO_Port GPIOD
#define MCU485_RX_Pin GPIO_PIN_2
#define MCU485_RX_GPIO_Port GPIOD
#define USART2_TXD_Pin GPIO_PIN_5
#define USART2_TXD_GPIO_Port GPIOD
#define USART2_RXD_Pin GPIO_PIN_6
#define USART2_RXD_GPIO_Port GPIOD
#define MCU485_DRE_Pin GPIO_PIN_1
#define MCU485_DRE_GPIO_Port GPIOE
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
