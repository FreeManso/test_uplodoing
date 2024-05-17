/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    usart.h
  * @brief   This file contains all the function prototypes for
  *          the usart.c file
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
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
#ifndef __USART_H__
#define __USART_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

extern UART_HandleTypeDef huart1;

/* USER CODE BEGIN Private defines */
/**
  * @brief 压力传感器数据结构
  */
__packed typedef struct
{
	uint8_t len;    //数据长度
	uint8_t ver;   //版本号
//	uint8_t pip;  //枪头状态
//	uint8_t npip;  //
//	uint8_t pretype;  //压力状态
//	uint8_t captype;  //电容状态
//	int32_t curpre; //当前压力
//	int32_t avepre; //压力均值滤波
//	int16_t temp;  //温度值
//	int32_t cap[4]; //静电容值
	uint8_t photoelectricity[4];
	uint8_t Hall_switch[2];
	int32_t times;//发送序号
	uint32_t crc; //crc32
}X_PRESSURE_Res;


/* USER CODE END Private defines */

void MX_USART1_UART_Init(void);

/* USER CODE BEGIN Prototypes */

/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif

#endif /* __USART_H__ */

