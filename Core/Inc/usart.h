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
  * @brief ѹ�����������ݽṹ
  */
__packed typedef struct
{
	uint8_t len;    //���ݳ���
	uint8_t ver;   //�汾��
//	uint8_t pip;  //ǹͷ״̬
//	uint8_t npip;  //
//	uint8_t pretype;  //ѹ��״̬
//	uint8_t captype;  //����״̬
//	int32_t curpre; //��ǰѹ��
//	int32_t avepre; //ѹ����ֵ�˲�
//	int16_t temp;  //�¶�ֵ
//	int32_t cap[4]; //������ֵ
	uint8_t photoelectricity[4];
	uint8_t Hall_switch[2];
	int32_t times;//�������
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

