
/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
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
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "can.h"
#include "dma.h"
#include "spi.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

uint8_t uart_rx_buffer[BUFFER_SIZE];
uint8_t uart3_data;
uint8_t uart3_index = 0;
uint8_t motor_flag;
uint8_t trage_angle;
flag RC={0,0,0,0,0,0};
uint8_t openmv_data[4];
static void SensorDataUpdata(uint32_t uiReg, uint32_t uiRegNum); // 陀螺仪数据更新
extern uint8_t ucRegIndex;                                       // 注册指数
uint8_t uart7_data;
uint8_t fyaw;
uint16_t max_speed = 2000;
float nowangle;
uint8_t sum;
uint8_t RGB[3] = {0};
uint8_t HSL[3] = {0};
static volatile char s_cDataUpdate1 = 0, s_cDataUpdate2 = 0, s_cDataUpdate3 = 0, s_cDataUpdate4 = 0, s_cCmd = 0xff;
void process_command(uint8_t *cmd, uint8_t len)
{
  char buffer[129];
  int mode = 0;
  int position = 0;
  int speed = 0;
  int angle = 0;

  memcpy(buffer, cmd, len);
  buffer[len] = '\0';

  if (sscanf(buffer, "mode%d,position%d,speed%d,angle%d", &mode, &position, &speed, &angle) == 4)
  {
    trage_angle = angle;
  }
}
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_CAN1_Init();
  MX_SPI5_Init();
  MX_UART7_Init();
  MX_UART8_Init();
  MX_USART6_UART_Init();
  MX_TIM6_Init();
  MX_USART2_UART_Init();
  MX_TIM4_Init();
  MX_TIM3_Init();
  MX_TIM5_Init();
  MX_USART3_UART_Init();
  MX_TIM7_Init();
  /* USER CODE BEGIN 2 */
  HAL_UART_Receive_IT(&huart7, &uart7_data, 1); // 开启串口7接收中断
  HAL_UART_Receive_IT(&huart6, &uart6_data, 1); // 开启串口6接收中断
  HAL_UART_Receive_IT(&huart3, &uart3_data, 1); // 开启串口3接收中断
  WitRegisterCallBack(SensorDataUpdata);        // 注册获取传感器数据回调函数
  power_on();                                   // 打开电机电源
  can_filter_init();                            // CAN滤波器初始化
  oled_Init();                                  // OLED初始化
  for (int i = 0; i < 4; i++)                   // PID初始化
  {
    pid_init(&motor_pid_speed[i]);
    pid_init(&motor_pid[i]);
    motor_pid_speed[i].f_param_init(&motor_pid_speed[i], PID_Speed, 16384, 5000, 0, 0, 8000, 0, 1.5, 0.01, 0.5); // 速度PID  0.6, 0.002, 0.8
    motor_pid[i].f_param_init(&motor_pid[i], PID_Speed, 16384, 5000, 10, 0, 8000, 0, 0.8, 0.02, 0);
  }
  HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_1); // 打开PWM
  HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_2);
  HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_3);
  HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_4);
  HAL_TIM_Base_Start_IT(&htim6); // 开启定时器6
  HAL_TIM_Base_Start_IT(&htim7); // 开启定时器7（100ms），用于OLED显示陀螺仪角度
  // Servo4_SetAngle(0);
  HAL_Delay(2000);
  // Servo4_SetAngle(90);
  HAL_Delay(2000);
  HAL_GPIO_WritePin(LED_R_GPIO_Port, LED_R_Pin, GPIO_PIN_SET);
  HAL_GPIO_WritePin(LED_G_GPIO_Port, LED_G_Pin, GPIO_PIN_SET);
  while (Ping())
  {
    printf("Ping Faild Try Again!\r\n");
    HAL_Delay(100);
  }
  printf("Ping Succseful!\r\n");
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    while (GQ == 0)
      ;
    PLAY_STATE_READY();
    // all_set();
    HAL_Delay(300);

    RGB_RED(9, 0);
    RGB_RED(9, 1);
    // one_to_two2();
    // two_to_three2();
    // three_to_four2();
    // four_to_five2();
    // five_to_seven2();
    // seven_to_eight2();
    // eight_to_home();

    // tracking_expedite(9000, time_break, 2000);
    // tracking(7000, zero, 200);
    // go_platform(5);
    // tracking(4000, time_break, 500);   // 到路障前
    // tracking(3300, time_break, 2500);  // 过路障
    // tracking(6000, forward_left, 100); // 到岔路口
    // go_forward(5000, 190);
    // turn_angle(turn_right, 16, 5000); // 岔路口右转
    // tracking(5000, zero, 500);        // 到平台下
    while(1)
    {
      stop();
      /* 轮询OLED更新标志（TIM7每100ms置位），在主循环中执行I2C读取避免ISR死锁 */
      if (oled_update_flag)
      {
        oled_update_flag = 0;
        get_imu_data();
        OLED_ShowNum(0, 0, (int32_t)imu.yaw, 3, 16, 1);   // Yaw角度

        uint8_t hsl[3];
        if (IIC_Get_HSL(hsl, 3))
        {
          OLED_ShowNum(0, 16, hsl[0], 3, 16, 1);           // H值
          OLED_ShowNum(48, 16, hsl[1], 3, 16, 1);           // S值
          OLED_ShowNum(96, 16, hsl[2], 3, 16, 1);           // L值
        }
        OLED_Refresh();
      }
    }
    // go_forward(5000, 500);            // 到平台中间
    // turn_angle(turn_left, 165, 5000); // 平台左转归正
    // stop_time(3000);

    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 6;
  RCC_OscInitStruct.PLL.PLLN = 168;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 7;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
static void SensorDataUpdata(uint32_t uiReg, uint32_t uiRegNum)
{
  int i;
  for (i = 0; i < uiRegNum; i++)
  {
    switch (uiReg)
    {
      //            case AX:
      //            case AY:
    case AZ:
      s_cDataUpdate1 |= ACC_UPDATE;
      break;
      //            case GX:
      //            case GY:
    case GZ:
      s_cDataUpdate2 |= GYRO_UPDATE;
      break;
      //            case HX:
      //            case HY:
    case HZ:
      s_cDataUpdate4 |= MAG_UPDATE;
      break;
      //            case Roll:
      //            case Pitch:
    case Yaw:
      s_cDataUpdate3 |= ANGLE_UPDATE;
      break;
      //            default:
      //				s_cDataUpdate1 |= READ_UPDATE;
      //			break;
    }
    uiReg++;
  }
}

// static void SensorUartSend(uint8_t *p_data, uint32_t uiSize)
// {
//   HAL_UART_Transmit(&huart3, (uint8_t *)&p_data, uiSize, 100);
// }

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}
#ifdef USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line
     number, ex: printf("Wrong parameters value: file %s on line %d\r\n", file,
     line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
