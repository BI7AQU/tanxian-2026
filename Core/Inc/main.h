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
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#define COUNTOF(__BUFFER__) (sizeof(__BUFFER__) / sizeof(*(__BUFFER__)))

#include <stdio.h>
#include <string.h>
#include "math.h"

#include "can.h"
#include "spi.h"
#include "usart.h"
#include "gpio.h"
#include "tim.h"

#include "bsp_can.h"
// #include "OLED.h"
#include "oled.h"
#include "pid.h"
#include "m2006.h"
#include "mp3.h"
#include "map.h"
#include "sensor.h"
#include "RGB.h"
#include "bmp.h"
#include "hwt101.h"
#include "taskA.h"
#include "color_sensor.h"

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */
#define ACC_UPDATE 0x01
#define GYRO_UPDATE 0x02
#define ANGLE_UPDATE 0x04
#define MAG_UPDATE 0x08
#define READ_UPDATE 0x80
/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */
  typedef struct
  {
    uint8_t tim_flag;
    uint8_t green_flag;
    uint8_t blue_flag;
    uint8_t black_flag;
    uint8_t line_flag;
    uint8_t eight_flag;
  } flag;

typedef unsigned char bool;
#define true 1
#define false 0
/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */
  extern uint8_t backhome;
  extern uint32_t time6_count;
  extern uint8_t treasure[5];
  extern flag RC;
  extern uint8_t uart6_data;
  extern uint8_t sum;
  extern uint8_t k230_data[4];
  extern uint8_t uart7_data;
  extern uint8_t uart8_data;
  extern uint8_t fyaw;
  void process_command(uint8_t *cmd, uint8_t len);
#define BUFFER_SIZE 128
  extern uint8_t uart_rx_buffer[BUFFER_SIZE];
  extern uint8_t uart3_index;
  extern uint8_t uart3_data;
  extern uint8_t motor_flag;
  extern uint8_t HSL[3];
  /* USER CODE END EM */

  /* Exported functions prototypes ---------------------------------------------*/
  void
  Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define OLED_SCK_Pin GPIO_PIN_3
#define OLED_SCK_GPIO_Port GPIOB
#define J2_Pin GPIO_PIN_4
#define J2_GPIO_Port GPIOE
#define J1_Pin GPIO_PIN_5
#define J1_GPIO_Port GPIOE
#define K1_Pin GPIO_PIN_6
#define K1_GPIO_Port GPIOE
#define OLED_DC_Pin GPIO_PIN_9
#define OLED_DC_GPIO_Port GPIOB
#define Y_Pin GPIO_PIN_7
#define Y_GPIO_Port GPIOI
#define X_Pin GPIO_PIN_6
#define X_GPIO_Port GPIOI
#define W_Pin GPIO_PIN_5
#define W_GPIO_Port GPIOI
#define Z_Pin GPIO_PIN_2
#define Z_GPIO_Port GPIOI
#define Q2_Pin GPIO_PIN_9
#define Q2_GPIO_Port GPIOI
#define I2_Pin GPIO_PIN_0
#define I2_GPIO_Port GPIOF
#define RGB_SDA_Pin GPIO_PIN_0
#define RGB_SDA_GPIO_Port GPIOI
#define POWER1_CTRL_Pin GPIO_PIN_2
#define POWER1_CTRL_GPIO_Port GPIOH
#define POWER2_CTRL_Pin GPIO_PIN_3
#define POWER2_CTRL_GPIO_Port GPIOH
#define I1_Pin GPIO_PIN_1
#define I1_GPIO_Port GPIOF
#define POWER3_CTRL_Pin GPIO_PIN_4
#define POWER3_CTRL_GPIO_Port GPIOH
#define POWER4_CTRL_Pin GPIO_PIN_5
#define POWER4_CTRL_GPIO_Port GPIOH
#define SPI5_NSS_Pin GPIO_PIN_6
#define SPI5_NSS_GPIO_Port GPIOF
#define RGB_SCL_Pin GPIO_PIN_12
#define RGB_SCL_GPIO_Port GPIOH
#define Q1_Pin GPIO_PIN_10
#define Q1_GPIO_Port GPIOF
#define E_Pin GPIO_PIN_15
#define E_GPIO_Port GPIOD
#define N2_Pin GPIO_PIN_0
#define N2_GPIO_Port GPIOC
#define O2_Pin GPIO_PIN_1
#define O2_GPIO_Port GPIOC
#define L1_Pin GPIO_PIN_2
#define L1_GPIO_Port GPIOC
#define M1_Pin GPIO_PIN_3
#define M1_GPIO_Port GPIOC
#define KEY_Pin GPIO_PIN_2
#define KEY_GPIO_Port GPIOB
#define F_Pin GPIO_PIN_14
#define F_GPIO_Port GPIOD
#define G_Pin GPIO_PIN_13
#define G_GPIO_Port GPIOD
#define T_Pin GPIO_PIN_1
#define T_GPIO_Port GPIOA
#define S_Pin GPIO_PIN_0
#define S_GPIO_Port GPIOA
#define P2_Pin GPIO_PIN_4
#define P2_GPIO_Port GPIOA
#define N1_Pin GPIO_PIN_4
#define N1_GPIO_Port GPIOC
#define H_Pin GPIO_PIN_12
#define H_GPIO_Port GPIOD
#define U_Pin GPIO_PIN_2
#define U_GPIO_Port GPIOA
#define OLED_CS_Pin GPIO_PIN_6
#define OLED_CS_GPIO_Port GPIOA
#define P1_Pin GPIO_PIN_5
#define P1_GPIO_Port GPIOA
#define O1_Pin GPIO_PIN_5
#define O1_GPIO_Port GPIOC
#define LED_R_Pin GPIO_PIN_11
#define LED_R_GPIO_Port GPIOE
#define V_Pin GPIO_PIN_3
#define V_GPIO_Port GPIOA
#define OLED_MOSI_Pin GPIO_PIN_7
#define OLED_MOSI_GPIO_Port GPIOA
#define M2_Pin GPIO_PIN_1
#define M2_GPIO_Port GPIOB
#define L2_Pin GPIO_PIN_0
#define L2_GPIO_Port GPIOB
#define LED_G_Pin GPIO_PIN_14
#define LED_G_GPIO_Port GPIOF
#define K2_Pin GPIO_PIN_12
#define K2_GPIO_Port GPIOE
#define OLED_RST_Pin GPIO_PIN_10
#define OLED_RST_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
