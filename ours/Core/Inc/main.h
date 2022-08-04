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
#include "tim.h"
#include "usart.h"
#include "stdio.h"
#include "callback_all.h"
#include "callback_uart.h"
#include "callback_tim.h"
#include "callback_exti.h"
#include "key.h"
#include "ble.h"
#include "computer_uart.h"
#include "motor.h"
#include "pid.h"
#include "bsp_delay.h"
#include "bsp_sys.h"
#include "graysensor.h"
#include "guangdian.h"
#include "led.h"
#include "usart.h"
#include "string.h"
#include "math.h"
#include "openmv.h"
#include "oled.h"
#include "oledfont.h"
#include "servo.h"
#include "calculate.h"

#include "mpu6050.h"
#include "inv_mpu.h"
#include "inv_mpu_dmp_motion_driver.h"
/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/*  小车执行任务代码  0-无任务default 1-近端任务 2-中端任务 3-远端任务 */
extern uint8_t Car_Task;
extern uint8_t task_dir;
extern uint8_t LoadOrNot;

/* 任务一 近端病房 */
extern uint8_t task1_dir;
extern uint8_t finish_11, start_11;
extern uint8_t finish_12, start_12;

/* 任务二 中端病房 */
extern uint8_t task2_dir;
extern uint8_t finish_21, start_21;
extern uint8_t finish_22, start_22;

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
#define GRAY_L1_Pin GPIO_PIN_2
#define GRAY_L1_GPIO_Port GPIOE
#define GRAY_L2_Pin GPIO_PIN_3
#define GRAY_L2_GPIO_Port GPIOE
#define GRAY_MID_Pin GPIO_PIN_4
#define GRAY_MID_GPIO_Port GPIOE
#define GRAY_R1_Pin GPIO_PIN_5
#define GRAY_R1_GPIO_Port GPIOE
#define GRAY_R2_Pin GPIO_PIN_6
#define GRAY_R2_GPIO_Port GPIOE
#define GuangDian_Pin GPIO_PIN_1
#define GuangDian_GPIO_Port GPIOC
#define GuangDian_EXTI_IRQn EXTI1_IRQn
#define SCL_Pin GPIO_PIN_10
#define SCL_GPIO_Port GPIOB
#define SDA_Pin GPIO_PIN_11
#define SDA_GPIO_Port GPIOB
#define D0_Pin GPIO_PIN_12
#define D0_GPIO_Port GPIOB
#define D1_Pin GPIO_PIN_13
#define D1_GPIO_Port GPIOB
#define RES_Pin GPIO_PIN_14
#define RES_GPIO_Port GPIOB
#define DC_Pin GPIO_PIN_15
#define DC_GPIO_Port GPIOB
#define AIN1_Pin GPIO_PIN_0
#define AIN1_GPIO_Port GPIOD
#define AIN2_Pin GPIO_PIN_1
#define AIN2_GPIO_Port GPIOD
#define BIN1_Pin GPIO_PIN_2
#define BIN1_GPIO_Port GPIOD
#define BIN2_Pin GPIO_PIN_3
#define BIN2_GPIO_Port GPIOD
#define LED1_Pin GPIO_PIN_4
#define LED1_GPIO_Port GPIOD
#define LED2_Pin GPIO_PIN_5
#define LED2_GPIO_Port GPIOD
#define LED3_Pin GPIO_PIN_6
#define LED3_GPIO_Port GPIOD
#define KEY1_Pin GPIO_PIN_5
#define KEY1_GPIO_Port GPIOB
#define KEY2_Pin GPIO_PIN_6
#define KEY2_GPIO_Port GPIOB
#define KEY3_Pin GPIO_PIN_7
#define KEY3_GPIO_Port GPIOB
#define KEY4_Pin GPIO_PIN_8
#define KEY4_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
