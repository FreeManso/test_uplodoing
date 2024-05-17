/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32g0xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
typedef struct {  //定义结构体名称
   int val;          //数值
   char next;     //指针

}Bob;  //定义结构体变量

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
#define STATE_Pin GPIO_PIN_15
#define STATE_GPIO_Port GPIOC
#define RST_IN1_Pin GPIO_PIN_0
#define RST_IN1_GPIO_Port GPIOA
#define RST_IN2_Pin GPIO_PIN_1
#define RST_IN2_GPIO_Port GPIOA
#define RST_IN3_Pin GPIO_PIN_2
#define RST_IN3_GPIO_Port GPIOA
#define RST_IN4_Pin GPIO_PIN_3
#define RST_IN4_GPIO_Port GPIOA
#define HALL1_Pin GPIO_PIN_4
#define HALL1_GPIO_Port GPIOA
#define HALL1A5_Pin GPIO_PIN_5
#define HALL1A5_GPIO_Port GPIOA

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
