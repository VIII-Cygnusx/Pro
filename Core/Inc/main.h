/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
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
#include "stm32u5xx_hal.h"

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
#define WRST_Pin GPIO_PIN_6
#define WRST_GPIO_Port GPIOA
#define WEN_Pin GPIO_PIN_4
#define WEN_GPIO_Port GPIOC
#define RCLK_Pin GPIO_PIN_5
#define RCLK_GPIO_Port GPIOC
#define VSYNC_Pin GPIO_PIN_0
#define VSYNC_GPIO_Port GPIOB
#define VSYNC_EXTI_IRQn EXTI0_IRQn
#define D7_Pin GPIO_PIN_1
#define D7_GPIO_Port GPIOB
#define D5_Pin GPIO_PIN_2
#define D5_GPIO_Port GPIOB
#define OE_Pin GPIO_PIN_12
#define OE_GPIO_Port GPIOB
#define D6_Pin GPIO_PIN_6
#define D6_GPIO_Port GPIOC
#define D4_Pin GPIO_PIN_7
#define D4_GPIO_Port GPIOC
#define D2_Pin GPIO_PIN_8
#define D2_GPIO_Port GPIOC
#define D0_Pin GPIO_PIN_9
#define D0_GPIO_Port GPIOC
#define SCCB_SDA_Pin GPIO_PIN_10
#define SCCB_SDA_GPIO_Port GPIOC
#define SCCB_SCL_Pin GPIO_PIN_11
#define SCCB_SCL_GPIO_Port GPIOC
#define D3_Pin GPIO_PIN_3
#define D3_GPIO_Port GPIOB
#define D1_Pin GPIO_PIN_4
#define D1_GPIO_Port GPIOB
#define RRST_Pin GPIO_PIN_8
#define RRST_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
