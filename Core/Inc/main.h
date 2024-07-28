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
#include "stm32h7xx_hal.h"

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
#define T_DIN_Pin GPIO_PIN_1
#define T_DIN_GPIO_Port GPIOC
#define T_DO_Pin GPIO_PIN_2
#define T_DO_GPIO_Port GPIOC
#define RS_Pin GPIO_PIN_3
#define RS_GPIO_Port GPIOC
#define M1_DIR_Pin GPIO_PIN_1
#define M1_DIR_GPIO_Port GPIOA
#define M1_STEP_Pin GPIO_PIN_2
#define M1_STEP_GPIO_Port GPIOA
#define M2_DIR_Pin GPIO_PIN_3
#define M2_DIR_GPIO_Port GPIOA
#define M2_STEP_Pin GPIO_PIN_4
#define M2_STEP_GPIO_Port GPIOA
#define WR_Pin GPIO_PIN_4
#define WR_GPIO_Port GPIOC
#define RD_Pin GPIO_PIN_5
#define RD_GPIO_Port GPIOC
#define M6_DIR_Pin GPIO_PIN_0
#define M6_DIR_GPIO_Port GPIOB
#define M6_STEP_Pin GPIO_PIN_1
#define M6_STEP_GPIO_Port GPIOB
#define M1_S_Pin GPIO_PIN_2
#define M1_S_GPIO_Port GPIOB
#define M1_S_EXTI_IRQn EXTI2_IRQn
#define T_CLK_Pin GPIO_PIN_10
#define T_CLK_GPIO_Port GPIOB
#define SD_CS_Pin GPIO_PIN_11
#define SD_CS_GPIO_Port GPIOB
#define T_CS_Pin GPIO_PIN_12
#define T_CS_GPIO_Port GPIOB
#define USER_LED_Pin GPIO_PIN_13
#define USER_LED_GPIO_Port GPIOB
#define LED_A_Pin GPIO_PIN_15
#define LED_A_GPIO_Port GPIOB
#define DB8_Pin GPIO_PIN_8
#define DB8_GPIO_Port GPIOD
#define DB9_Pin GPIO_PIN_9
#define DB9_GPIO_Port GPIOD
#define DB10_Pin GPIO_PIN_10
#define DB10_GPIO_Port GPIOD
#define DB11_Pin GPIO_PIN_11
#define DB11_GPIO_Port GPIOD
#define DB12_Pin GPIO_PIN_12
#define DB12_GPIO_Port GPIOD
#define DB13_Pin GPIO_PIN_13
#define DB13_GPIO_Port GPIOD
#define DB14_Pin GPIO_PIN_14
#define DB14_GPIO_Port GPIOD
#define DB15_Pin GPIO_PIN_15
#define DB15_GPIO_Port GPIOD
#define CS_Pin GPIO_PIN_6
#define CS_GPIO_Port GPIOC
#define F_CS_Pin GPIO_PIN_7
#define F_CS_GPIO_Port GPIOC
#define REST_Pin GPIO_PIN_8
#define REST_GPIO_Port GPIOC
#define T_IRQ_Pin GPIO_PIN_9
#define T_IRQ_GPIO_Port GPIOC
#define T_IRQ_EXTI_IRQn EXTI9_5_IRQn
#define M3_DIR_Pin GPIO_PIN_8
#define M3_DIR_GPIO_Port GPIOA
#define M3_STEP_Pin GPIO_PIN_9
#define M3_STEP_GPIO_Port GPIOA
#define M4_DIR_Pin GPIO_PIN_10
#define M4_DIR_GPIO_Port GPIOA
#define M4_STEP_Pin GPIO_PIN_11
#define M4_STEP_GPIO_Port GPIOA
#define M5_DIR_Pin GPIO_PIN_12
#define M5_DIR_GPIO_Port GPIOA
#define M5_STEP_Pin GPIO_PIN_15
#define M5_STEP_GPIO_Port GPIOA
#define DB0_Pin GPIO_PIN_0
#define DB0_GPIO_Port GPIOD
#define DB1_Pin GPIO_PIN_1
#define DB1_GPIO_Port GPIOD
#define DB2_Pin GPIO_PIN_2
#define DB2_GPIO_Port GPIOD
#define DB3_Pin GPIO_PIN_3
#define DB3_GPIO_Port GPIOD
#define DB4_Pin GPIO_PIN_4
#define DB4_GPIO_Port GPIOD
#define DB5_Pin GPIO_PIN_5
#define DB5_GPIO_Port GPIOD
#define DB6_Pin GPIO_PIN_6
#define DB6_GPIO_Port GPIOD
#define DB7_Pin GPIO_PIN_7
#define DB7_GPIO_Port GPIOD
#define M2_S_Pin GPIO_PIN_5
#define M2_S_GPIO_Port GPIOB
#define M2_S_EXTI_IRQn EXTI9_5_IRQn
#define M3_S_Pin GPIO_PIN_6
#define M3_S_GPIO_Port GPIOB
#define M3_S_EXTI_IRQn EXTI9_5_IRQn
#define M4_S_Pin GPIO_PIN_7
#define M4_S_GPIO_Port GPIOB
#define M4_S_EXTI_IRQn EXTI9_5_IRQn
#define M5_S_Pin GPIO_PIN_8
#define M5_S_GPIO_Port GPIOB
#define M5_S_EXTI_IRQn EXTI9_5_IRQn

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
