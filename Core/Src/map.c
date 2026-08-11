#include "map.h"
int i;
int line1 = 0;
int line2 = 0;
int line3 = 0;
int line4 = 0;

void one_to_two(void)
{
  // 到白线
  go_forward(4500, 300);
  // 到桥坡下前循迹
  while (1)
  {
    read_sensor_data();
    RC.tim_flag = 1;
    HAL_Delay(10);
    if (sum == 0 && time6_count > 1500) // 到桥坡下
    {
      RC.tim_flag = 0;
      HAL_Delay(10);
      break;
    }
    else
    {
      track_PID(6000); // 循迹
    }
  }
  // while (1)
  // {
  //     stop();
  // }
  go_bridge(5000, 1700);
  // 下桥
  while (1)
  {
    RC.tim_flag = 1;
    speed_pid(3000);
    set_moto_current(motor_pid_speed[0].output, motor_pid_speed[1].output,
                     motor_pid_speed[2].output, motor_pid_speed[3].output);
    read_sensor_data();
    HAL_Delay(10);
    if (sum > 0 && time6_count > 300)
    {
      RC.tim_flag = 0;
      HAL_Delay(10);
      break;
    }
  }
  // 上平台前循迹
  while (1)
  {
    RC.tim_flag = 1;
    track_PID(7000);
    read_sensor_data();
    if (sum == 0 && time6_count > 400) // 到平台
    {
      RC.tim_flag = 0;
      HAL_Delay(10);
      break;
    }
  }

  // 撞击平台
  while (1)
  {
    speed_pid(3000);
    set_moto_current(motor_pid_speed[0].output, motor_pid_speed[1].output,
                     motor_pid_speed[2].output, motor_pid_speed[3].output);
    HAL_Delay(10);
    if (EQ == 0)
    {
      break;
    }
  }
  while (1)
  {
    RC.tim_flag = 1;
    stop();
    if (time6_count > 300)
    {
      RC.tim_flag = 0;
      HAL_Delay(10);
      break;
    }
  }
  go_forward(-3000, 300);
  while (1) // 停下等待
  {
    stop();
    RC.tim_flag = 1;
    if (time6_count >= 500)
    {
      RC.tim_flag = 0;
      HAL_Delay(10);
      break;
    }
  }

  // 语音报告
  PLAY_ARRIVE_TWO();
  do_platform();

  // 平台转弯
  RGB_YELLOW(9, 1);
  turn_angle(turn_left, 163,5000);
}
void two_to_three(void)
{
  // 下平台
  go_forward(4500, 350);
  // 循迹到岔路口1
  while (1)
  {
    RC.tim_flag = 1;
    track_PID(5000);
    if (QR == 0 && time6_count > 700)
    {
      RC.tim_flag = 0;
      HAL_Delay(10);
      break;
    }
  }

  // 岔路口1右转
  turn_angle(turn_right, 45,5000);
  // 循迹过梯形山
  while (1)
  {
    RC.tim_flag = 1;
    track_PID(5000);
    if (time6_count > 2500)
    {
      RC.tim_flag = 0;
      HAL_Delay(10);
      break;
    }
  }

  // 循迹到岔路口2
  while (1)
  {
    track_PID(5000);
    if (QL == 0)
    {
      break;
    }
  }

  // 岔路口右转
  go_forward(4500, 130);
  turn_angle(turn_right, 105, 5000);

  while (1) // 起步
  {
    RC.tim_flag = 1;
    track_PID(6000);
    if (time6_count > 200)
    {
      RC.tim_flag = 0;
      HAL_Delay(10);
      break;
    }
  }
  while (1) // 中速
  {
    RC.tim_flag = 1;
    track_PID(7000);
    if (time6_count > 200)
    {
      RC.tim_flag = 0;
      HAL_Delay(10);
      break;
    }
  }
  while (1) // 中速
  {
    RC.tim_flag = 1;
    track_PID(8000);
    if (time6_count > 400)
    {
      RC.tim_flag = 0;
      HAL_Delay(1);
      break;
    }
  }
  while (1) // 高速
  {
    RC.tim_flag = 1;
    track_PID(10000);
    if (time6_count > 300)
    {
      RC.tim_flag = 0;
      HAL_Delay(1);
      break;
    }
  }
  while (1) // 高速
  {
    RC.tim_flag = 1;
    track_PID(12000);
    if (time6_count > 1000)
    {
      RC.tim_flag = 0;
      HAL_Delay(1);
      break;
    }
  }
  while (1) // 高速
  {
    RC.tim_flag = 1;
    track_PID(10000);
    if (time6_count > 200)
    {
      RC.tim_flag = 0;
      HAL_Delay(1);
      break;
    }
  }
  while (1) // 高速
  {
    RC.tim_flag = 1;
    track_PID(8500);
    if (time6_count > 200)
    {
      RC.tim_flag = 0;
      HAL_Delay(1);
      break;
    }
  }
  // 到平台
  while (1)
  {
    track_PID(7000);
    RC.tim_flag = 1;
    read_sensor_data();
    if (sum == 0 && time6_count > 300)
    {

      RC.tim_flag = 0;
      HAL_Delay(1);
      break;
    }
  }
  while (1)
  {
    track_PID(6000);
    RC.tim_flag = 1;
    read_sensor_data();
    if (sum == 0 && time6_count > 300)
    {

      RC.tim_flag = 0;
      HAL_Delay(1);
      break;
    }
  }

  // 撞击平台
  while (1)
  {
    speed_pid(3000);
    set_moto_current(motor_pid_speed[0].output, motor_pid_speed[1].output,
                     motor_pid_speed[2].output, motor_pid_speed[3].output);
    HAL_Delay(10);
    if (EQ == 0)
    {
      break;
    }
  }
  while (1)
  {
    RC.tim_flag = 1;
    stop();
    if (time6_count > 300)
    {
      RC.tim_flag = 0;
      HAL_Delay(1);
      break;
    }
  }
  go_forward(-3000, 300);
  while (1) // 停下等待
  {
    stop();
    RC.tim_flag = 1;
    if (time6_count >= 500)
    {
      RC.tim_flag = 0;
      HAL_Delay(10);
      break;
    }
  }

  // 语音播报
  PLAY_ARRIVE_THREE();
  do_platform();

  // 平台3掉头
  turn_angle(turn_left, 163, 5000);
}

void three_to_four(void)
{
  // 下平台
  go_forward(4000, 500);
  while (1) // 中速
  {
    RC.tim_flag = 1;
    track_PID(6000);
    if (time6_count > 200)
    {
      RC.tim_flag = 0;
      HAL_Delay(1);
      break;
    }
  }
  while (1) // 中速
  {
    RC.tim_flag = 1;
    track_PID(7000);
    if (time6_count > 200)
    {
      RC.tim_flag = 0;
      HAL_Delay(1);
      break;
    }
  }
  while (1) // 中速
  {
    RC.tim_flag = 1;
    track_PID(7500);
    if (time6_count > 300)
    {
      RC.tim_flag = 0;
      HAL_Delay(1);
      break;
    }
  }
  while (1) // 高速
  {
    RC.tim_flag = 1;
    track_PID(8000);
    if (time6_count > 300)
    {
      RC.tim_flag = 0;
      HAL_Delay(1);
      break;
    }
  }

  // 第一个岔路口
  while (1)
  {
    RC.tim_flag = 1;
    track_PID(8000);
    if ((QL == 0) && time6_count >= 200)
    {
      RC.tim_flag = 0;
      HAL_Delay(1);
      break;
    }
  }
  // go_forward(8000, 100);
  // while (1)
  // {
  //     stop();
  // }

  // 第二个岔路口
  while (1)
  {
    RC.tim_flag = 1;
    track_PID(8000);
    if ((QL == 0) && time6_count >= 200)
    {
      RC.tim_flag = 0;
      HAL_Delay(1);
      break;
    }
  }
  go_forward(8000, 100);
  // while (1)
  // {
  //     stop();
  // }

  while (1)
  {
    RC.tim_flag = 1;
    track_PID(8000);
    if ((QR == 0) && time6_count >= 200)
    {
      RC.tim_flag = 0;
      HAL_Delay(1);
      break;
    }
  }
  go_forward(8000, 100);

  while (1)
  {
    RC.tim_flag = 1;
    track_PID(7000);
    if (time6_count >= 200)
    {
      RC.tim_flag = 0;
      HAL_Delay(1);
      break;
    }
  }

  // 第四个岔路口
  while (1)
  {
    RC.tim_flag = 1;
    track_PID(6000);
    if ((QR == 0) && time6_count >= 300)
    {
      RC.tim_flag = 0;
      HAL_Delay(1);
      break;
    }
  }

  // 左转
  go_forward(7000, 160);
  turn_angle(turn_left, 28, 5000);

  // 中途加速
  while (1)
  {
    RC.tim_flag = 1;
    track_PID(6000);
    if (time6_count > 200)
    {
      RC.tim_flag = 0;
      HAL_Delay(10);
      break;
    }
  }
  while (1)
  {
    RC.tim_flag = 1;
    track_PID(7000);
    if (time6_count > 200)
    {
      RC.tim_flag = 0;
      HAL_Delay(10);
      break;
    }
  }
  while (1)
  {
    RC.tim_flag = 1;
    track_PID(8000);
    if (time6_count > 600)
    {
      RC.tim_flag = 0;
      HAL_Delay(10);
      break;
    }
  }
  while (1)
  {
    RC.tim_flag = 1;
    track_PID(6000);
    if (time6_count > 400)
    {
      RC.tim_flag = 0;
      HAL_Delay(10);
      break;
    }
  }

  // 到达景点
  while (1)
  {
    track_PID(4000);
    if (EQ == 0)
    {
      break;
    }
  }

  // 停，识别景点
  while (1)
  {
    RC.tim_flag = 1;
    stop();
    if (time6_count > 600)
    {
      RC.tim_flag = 0;
      HAL_Delay(10);
      break;
    }
  }

  // 语音播报
  PLAY_UPRIGHT_SPOTS();

  // 倒车调头
  go_forward(-4000, 300);
  turn_angle(turn_left, 160, 5000);
  // 识别到岔路口
  while (1)
  {
    RC.tim_flag = 1;
    track_PID(6000);
    if (time6_count >= 100)
    {
      RC.tim_flag = 0;
      HAL_Delay(10);
      break;
    }
  }
  while (1)
  {
    RC.tim_flag = 1;
    track_PID(8000);
    if ((QL == 0) && time6_count >= 230)
    {
      RC.tim_flag = 0;
      HAL_Delay(10);
      break;
    }
  }

  // 左转
  go_forward(6000, 250);
  turn_angle(turn_left, 105, 5000);

  // 上平台
  while (1)
  {
    RC.tim_flag = 1;
    track_PID(5000);
    read_sensor_data();
    if ((sum == 0) && time6_count >= 1500)
    {
      RC.tim_flag = 0;
      HAL_Delay(10);
      break;
    }
  }

  // 撞击平台
  while (1)
  {
    speed_pid(3000);
    set_moto_current(motor_pid_speed[0].output, motor_pid_speed[1].output,
                     motor_pid_speed[2].output, motor_pid_speed[3].output);
    HAL_Delay(10);
    if (EQ == 0)
    {
      break;
    }
  }
  while (1)
  {
    RC.tim_flag = 1;
    stop();
    if (time6_count > 300)
    {
      RC.tim_flag = 0;
      HAL_Delay(10);
      break;
    }
  }
  go_forward(-3000, 300);
  while (1) // 停下等待
  {
    stop();
    RC.tim_flag = 1;
    if (time6_count >= 500)
    {
      RC.tim_flag = 0;
      HAL_Delay(10);
      break;
    }
  }

  // 语音播报
  PLAY_ARRIVE_FOUR();
  do_platform();

  // 平台4掉头
  turn_angle(turn_left, 160, 5000);
}

// void two_to_four(void)
// {
//     go_forward(4000, 500); // 下平台
//     while (1)              // 循迹到岔路口1
//     {
//         RC.tim_flag = 1;
//         track_PID(3500);
//         read_sensor_data();
//         if (QR == 0 && time6_count > 400)
//         {
//             RC.tim_flag = 0;
//             HAL_Delay(10);
//             break;
//         }
//     }
//     go_forward(4000, 80);
//     while (1) // 岔路口1转弯
//     {
//         RC.tim_flag = 1;
//         RGB_YELLOW(9, 1);
//         turn_right(4000);
//         if ((E8 || E9) && time6_count > 220)
//         {
//             RGB_RED(9, 1);
//             RC.tim_flag = 0;
//             HAL_Delay(10);
//             break;
//         }
//     }
//     while (1) // 循迹过梯形山
//     {
//         RC.tim_flag = 1;
//         track_PID(4500);
//         if (time6_count > 2600)
//         {
//             RC.tim_flag = 0;
//             HAL_Delay(10);
//             break;
//         }
//     }
//     while (1)
//     {
//         track_PID(4500);
//         if (QR == 0)
//         {
//             break;
//         }
//     }
//     go_forward(4000, 280);
//     while (1) // 到岔路口2左转
//     {
//         RGB_YELLOW(9, 0);
//         RC.tim_flag = 1;
//         turn_left(4500);
//         if ((E6 || E8) && time6_count > 100)
//         {
//             RGB_RED(9, 0);
//             RC.tim_flag = 0;
//             HAL_Delay(10);
//             break;
//         }
//     }
//     go_forward(6000, 180);
//     while (1) // 循迹到岔路口3
//     {
//         RC.tim_flag = 1;
//         track_PID(10000);
//         if (QR == 0 && time6_count > 200)
//         {
//             RC.tim_flag = 0;
//             HAL_Delay(10);
//             break;
//         }
//     }
//     go_forward(8000, 150);
//     while (1) // 循迹到岔路口4
//     {
//         RC.tim_flag = 1;
//         track_PID(10000);
//         if (QR == 0 && time6_count > 200)
//         {
//             RC.tim_flag = 0;
//             HAL_Delay(10);
//             break;
//         }
//     }
//     go_forward(7000, 200);
//     while (1) // 到平台
//     {
//         track_PID(5000);
//         read_sensor_data();
//         if (sum == 0)
//         {
//             break;
//         }
//     }
//     while (1) // 撞击平台
//     {
//         speed_pid(3000);
//         set_moto_current(motor_pid_speed[0].output,
//         motor_pid_speed[1].output, motor_pid_speed[2].output,
//         motor_pid_speed[3].output); HAL_Delay(10); if (EQ == 0)
//         {
//             break;
//         }
//     }
//     while (1)
//     {
//         RC.tim_flag = 1;
//         stop();
//         if (time6_count > 300)
//         {
//             RC.tim_flag = 0;
//             HAL_Delay(10);
//             break;
//         }
//     }
//     go_forward(-3000, 300);
//     while (1) // 停下等待
//     {
//         stop();
//         RC.tim_flag = 1;
//         if (time6_count >= 500)
//         {
//             RC.tim_flag = 0;
//             HAL_Delay(10);
//             break;
//         }
//     }
//     // PLAY_ARRIVE_FOUR(); // 语音播报
//     // do_platform();
//     while (1)
//     {
//         RC.tim_flag = 1;
//         turn_left(4000);
//         if (time6_count > 990)
//         {
//             RC.tim_flag = 0;
//             stop();
//             HAL_Delay(10);
//             break;
//         }
//     }
// }

/************************************************************************************************************************************
 */
void four_to_five(void)
{
  // 下平台
  go_forward(4500, 600);

  // 循迹过岔路口1
  while (1)
  {
    RC.tim_flag = 1;
    track_PID(7000);
    if (QR == 0 && time6_count > 500)
    {
      RC.tim_flag = 0;
      HAL_Delay(10);
      break;
    }
  }

  // 循迹到岔路口2
  while (1)
  {
    RC.tim_flag = 1;
    track_PID(7000);
    if (QL == 0 && time6_count > 700)
    {
      RC.tim_flag = 0;
      HAL_Delay(10);
      break;
    }
  }

  // 左转
  go_forward(4000, 140);
  turn_angle(turn_left, 78, 5000);

  while (1) // 到红绿灯1停
  {
    RC.tim_flag = 1;
    track_PID(6000);
    if ((QL == 0 || QR == 0) && time6_count > 600)
    {
      RC.tim_flag = 0;
      break;
    }
  }
  while (1)
  {
    HAL_UART_Receive_IT(&huart8, k230_data, 1);
    while (1) // 停，识别红绿灯1
    {
      RC.tim_flag = 1;
      if (time6_count > 3000)
      {
        RC.tim_flag = 0;
        HAL_Delay(10);
        break;
      }
      stop();
    }
    if (RC.green_flag == 1) // 遇到红绿灯1且为绿灯      到岔路口2
    {
      line1 = 1;
      HAL_UART_AbortReceive_IT(&huart8);
      k230_data[2] = 0;
      RC.black_flag = 0;
      RC.green_flag = 0;
      RC.blue_flag = 0;
      while (1)
      {
        RC.tim_flag = 1;
        track_PID(8000);
        if (QR == 0 && time6_count > 600)
        {
          RC.tim_flag = 0;
          HAL_Delay(10);
          break;
        }
      }
      go_forward(5000, 220);
      turn_angle(turn_left, 90, 5000);
      while (1)
      {
        RC.tim_flag = 1;
        track_PID(7000);
        if (QR == 0 && time6_count > 600)
        {
          RC.tim_flag = 0;
          HAL_Delay(1);
          break;
        }
      }
    }
    else if (RC.green_flag == 0) // 第一个红绿灯为红灯
    {
      HAL_UART_AbortReceive_IT(&huart8);
      k230_data[2] = 0;
      RC.black_flag = 0;
      RC.green_flag = 0;
      RC.blue_flag = 0;

      // 调头
      turn_angle(turn_left, 150, 5000);
      // 循迹到岔路口1
      while (1)
      {
        RC.tim_flag = 1;
        track_PID(7000);
        if (QL == 0 && time6_count > 500)
        {
          RC.tim_flag = 0;
          HAL_Delay(10);
          break;
        }
      }
      go_forward(4800, 200);

      // 岔路口1左转
      turn_angle(turn_left, 115, 5000);

      // 到红绿灯停
      while (1)
      {
        RC.tim_flag = 1;
        track_PID(6000);
        if ((QL == 0 || QR == 0) && time6_count > 600)
        {
          RC.tim_flag = 0;
          break;
        }
      }

      HAL_UART_Receive_IT(&huart8, k230_data, 1);
      while (1) // 停，识别红绿灯2
      {
        RC.tim_flag = 1;
        if (time6_count > 3000)
        {
          RC.tim_flag = 0;
          HAL_Delay(10);
          break;
        }
        stop();
      }

      if (RC.green_flag == 1) // 遇到红绿灯2且为绿灯      到岔路口2
      {
        line2 = 1;
        HAL_UART_AbortReceive_IT(&huart8);
        k230_data[2] = 0;
        RC.black_flag = 0;
        RC.green_flag = 0;
        RC.blue_flag = 0;
        while (1)
        {
          RC.tim_flag = 1;
          track_PID(7000);
          if (QR == 0 && time6_count > 300)
          {
            RC.tim_flag = 0;
            HAL_Delay(10);
            break;
          }
        }

        go_forward(4000, 100);
        // 岔路口左转
        turn_angle(turn_left, 90, 5000);

        go_forward(4000, 150);

        // 循迹到岔路口

        while (1)
        {
          RC.tim_flag = 1;
          track_PID(6000);
          if (time6_count > 150)
          {
            RC.tim_flag = 0;
            HAL_Delay(10);
            break;
          }
        }
        while (1)
        {
          RC.tim_flag = 1;
          track_PID(8000);
          if (QR == 0 && time6_count > 150)
          {
            RC.tim_flag = 0;
            HAL_Delay(10);
            break;
          }
        }
        go_forward(5000, 350);
        // 左转
        turn_angle(turn_left, 16, 5000);
        go_forward(5000, 200);

        while (1)
        {
          RC.tim_flag = 1;
          track_PID(6000);
          if (QR == 0 && time6_count > 350)
          {
            RC.tim_flag = 0;
            HAL_Delay(10);
            break;
          }
        }

        while (1) // 岔路口7冲刺
        {
          track_PID(7000);
          if (QR == 0)
          {
            break;
          }
        }
      }
      else if (RC.green_flag == 0) // 第二个红绿灯为红灯
      {
        HAL_UART_AbortReceive_IT(&huart8);
        k230_data[2] = 0;
        RC.black_flag = 0;
        RC.green_flag = 0;
        RC.blue_flag = 0;

        // 第二次回头
        turn_angle(turn_right, 160, 5000);

        while (1)
        {
          RC.tim_flag = 1;
          track_PID(7000);
          if (QR == 0 && time6_count > 300)
          {
            RC.tim_flag = 0;
            HAL_Delay(5);
            break;
          }
        }

        // 左转
        go_forward(6000, 250);
        turn_angle(turn_left, 105, 5000);

        // 岔路口3冲刺
        // 第二个岔路口前循迹，渐加速
        while (1) // 低速
        {
          RC.tim_flag = 1;
          track_PID(5000);
          if (time6_count > 200)
          {
            RC.tim_flag = 0;
            HAL_Delay(1);
            break;
          }
        }
        while (1) // 中速
        {
          RC.tim_flag = 1;
          track_PID(6000);
          if (time6_count > 200)
          {
            RC.tim_flag = 0;
            HAL_Delay(1);
            break;
          }
        }
        while (1) // 高速
        {
          RC.tim_flag = 1;
          track_PID(7000);
          if (time6_count > 1000)
          {
            RC.tim_flag = 0;
            HAL_Delay(10);
            break;
          }
        }

        // 循迹到岔路口4
        while (1)
        {
          track_PID(7000);
          if (QL == 0)
          {
            break;
          }
        }

        go_forward(6000, 250);
        turn_angle(turn_left, 120, 5000);

        while (1)
        {
          RC.tim_flag = 1;
          track_PID(6000);
          if ((QL == 0 || QR == 0) && time6_count > 600)
          {
            RC.tim_flag = 0;
            break;
          }
        }

        HAL_UART_Receive_IT(&huart8, k230_data, 1);
        while (1) // 停，识别红绿灯3
        {
          RC.tim_flag = 1;
          stop();
          if (time6_count > 3000)
          {
            RC.tim_flag = 0;
            HAL_Delay(10);
            break;
          }
        }

        if (RC.green_flag == 1) // 遇到红绿灯3且为绿灯      到岔路口2
        {
          line3 = 1;
          HAL_UART_AbortReceive_IT(&huart8);
          k230_data[2] = 0;
          RC.green_flag = 0;
          RC.black_flag = 0;
          RC.blue_flag = 0;

          while (1) // 第三条路
          {
            RC.tim_flag = 1;
            track_PID(7000);
            if (time6_count > 300)
            {
              RC.tim_flag = 0;
              HAL_Delay(10);
              break;
            }
          }
          while (1)
          {
            RC.tim_flag = 1;
            track_PID(8500);
            if (time6_count > 300)
            {
              RC.tim_flag = 0;
              HAL_Delay(10);
              break;
            }
          }
          // 循迹到岔路口6
          while (1) // 高速
          {
            RC.tim_flag = 1;
            track_PID(8000);
            if (time6_count > 1000)
            {
              RC.tim_flag = 0;
              HAL_Delay(10);
              break;
            }
          }
          while (1)
          {
            RC.tim_flag = 1;
            track_PID(8000);
            if (QL == 0 && time6_count > 400)
            {
              RC.tim_flag = 0;
              HAL_Delay(10);
              break;
            }
          }

          // 左转
          go_forward(5000, 150);
          turn_angle(turn_left, 20, 5000);

          while (1) // 岔路口7冲刺
          {
            RC.tim_flag = 1;
            track_PID(6000);
            if (time6_count > 200)
            {
              RC.tim_flag = 0;
              HAL_Delay(10);
              break;
            }
          }
          while (1) // 岔路口7冲刺
          {
            RC.tim_flag = 1;
            track_PID(8500);
            if (time6_count > 1500)
            {
              RC.tim_flag = 0;
              HAL_Delay(10);
              break;
            }
          }
        }

        else if (RC.blue_flag == 1) // 第三个红绿灯为蓝灯
        {
          line4 = 1;
          HAL_UART_AbortReceive_IT(&huart8);
          k230_data[2] = 0;
          RC.black_flag = 0;
          RC.green_flag = 0;
          RC.blue_flag = 0;

          // while(1)
          // {
          //     stop();
          // }
          while (1) // 第三条路
          {
            RC.tim_flag = 1;
            track_PID(7000);
            if (time6_count > 300)
            {
              RC.tim_flag = 0;
              HAL_Delay(10);
              break;
            }
          }

          while (1)
          {
            RC.tim_flag = 1;
            track_PID(8500);
            if (time6_count > 300)
            {
              RC.tim_flag = 0;
              HAL_Delay(10);
              break;
            }
          }

          // 循迹到岔路口6
          while (1) // 高速
          {
            RC.tim_flag = 1;
            track_PID(8000);
            if (time6_count > 1000)
            {
              RC.tim_flag = 0;
              HAL_Delay(10);
              break;
            }
          }
          while (1)
          {
            RC.tim_flag = 1;
            track_PID(8000);
            if (QL == 0 && time6_count > 400)
            {
              RC.tim_flag = 0;
              HAL_Delay(10);
              break;
            }
          }

          // 左转
          go_forward(5000, 150);
          turn_angle(turn_left, 20, 5000);

          while (1) // 岔路口7冲刺
          {
            RC.tim_flag = 1;
            track_PID(6000);
            if (time6_count > 200)
            {
              RC.tim_flag = 0;
              HAL_Delay(10);
              break;
            }
          }
          while (1) // 岔路口7冲刺
          {
            RC.tim_flag = 1;
            track_PID(8500);
            if (time6_count > 1500)
            {
              RC.tim_flag = 0;
              HAL_Delay(10);
              break;
            }
          }
        }
        else if (RC.black_flag == 1) // 第三个红绿灯为黑灯
        {
          line4 = 1;
          HAL_UART_AbortReceive_IT(&huart8);

          // 第三次回头
          turn_angle(turn_right, 165, 5000);

          while (1)
          {
            RC.tim_flag = 1;
            track_PID(7000);
            if (QL == 0 && time6_count > 400)
            {
              RC.tim_flag = 0;
              HAL_Delay(10);
              break;
            }
          }

          go_forward(5000, 300);
          turn_angle(turn_left, 120, 5000); // 第一个路口左转

          while (1)
          {
            RC.tim_flag = 1;
            track_PID(7000);
            if (time6_count > 500)
            {
              RC.tim_flag = 0;
              HAL_Delay(10);
              break;
            }
          }

          while (1)
          {
            RC.tim_flag = 1;
            track_PID(6000);
            if (time6_count > 800)
            {
              RC.tim_flag = 0;
              HAL_Delay(10);
              break;
            }
          }
          //   while(1)
          // {
          //     stop();
          // }

          while (1)
          {
            RC.tim_flag = 1;
            track_PID(55000);
            if (QL == 0 && time6_count > 100)
            {
              RC.tim_flag = 0;
              HAL_Delay(10);
              break;
            }
          }

          go_forward(5000, 230);
          turn_angle(turn_left, 70, 5000);

          while (1) // 循迹到路障前路口
          {
            RC.tim_flag = 1;
            track_PID(6000);
            if (time6_count >= 500)
            {
              RC.tim_flag = 0;
              HAL_Delay(10);
              break;
            }
          }

          while (1) // 过路障
          {
            RC.tim_flag = 1;
            track_PID(3300);
            if (time6_count >= 3900)
            {
              RC.tim_flag = 0;
              HAL_Delay(10);
              break;
            }
          }

          while (1) // 加速
          {
            RC.tim_flag = 1;
            track_PID(6000);
            if (time6_count >= 200)
            {
              RC.tim_flag = 0;
              HAL_Delay(10);
              break;
            }
          }

          while (1) // 加速
          {
            RC.tim_flag = 1;
            track_PID(7000);
            if (time6_count >= 1700)
            {
              RC.tim_flag = 0;
              HAL_Delay(10);
              break;
            }
          }
        }
      }
    }
    break;
  }

  while (1) // 上平台
  {
    RC.tim_flag = 1;
    read_sensor_data();
    track_PID(6000);
    if (sum == 0 && time6_count > 600)
    {
      HAL_Delay(10);
      RC.tim_flag = 0;
      break;
    }
  }

  while (1) // 撞击平台
  {
    speed_pid(3000);
    set_moto_current(motor_pid_speed[0].output, motor_pid_speed[1].output, motor_pid_speed[2].output, motor_pid_speed[3].output);
    HAL_Delay(10);
    if (EQ == 0)
    {
      break;
    }
  }
  while (1)
  {
    RC.tim_flag = 1;
    stop();
    if (time6_count > 900)
    {
      RC.tim_flag = 0;
      HAL_Delay(10);
      break;
    }
  }
  go_forward(-3000, 300);

  while (1) // 停下等待
  {
    stop();
    RC.tim_flag = 1;
    if (time6_count >= 500)
    {
      RC.tim_flag = 0;
      HAL_Delay(10);
      break;
    }
  }
  PLAY_ARRIVE_FIVE(); // 语言播报
  do_platform();

  turn_angle(turn_left, 165, 5000);
}

/************************************************************************************************************************************
 */
void five_to_seven(void)
{
  go_forward(4000, 600); // 下平台
  while (1)              // 循迹过岔路口1
  {
    RC.tim_flag = 1;
    track_PID(6000);
    if (time6_count > 200)
    {
      RC.tim_flag = 0;
      HAL_Delay(5);
      break;
    }
  }
  while (1)
  {
    track_PID(6500);
    if (QR == 0)
    {
      break;
    }
  }
  go_forward(6500, 400);
  while (1) // 循迹过岔路口1
  {
    RC.tim_flag = 1;
    track_PID(7000);
    if (time6_count > 700)
    {
      RC.tim_flag = 0;
      HAL_Delay(10);
      break;
    }
  }

  while (1) // 循迹到岔路口2
  {
    track_PID(6000);
    RC.tim_flag = 1;
    if (QL == 0 && time6_count > 200)
    {
      RC.tim_flag = 0;
      HAL_Delay(10);
      break;
    }
  }

  go_forward(4000, 150);
  turn_angle(turn_left, 82, 5000);

  while (1) // 循迹到岔路口3
  {
    RC.tim_flag = 1;
    track_PID(4000);
    if (QR == 0 && time6_count > 10)
    {
      RC.tim_flag = 0;
      HAL_Delay(10);
      break;
    }
  }

  go_forward(4500, 150);
  turn_angle(turn_right, 73, 5000);
  while (1) // 到达景点
  {
    track_PID(3000);
    if (EQ == 0)
    {
      break;
    }
  }

  while (1) // 停，识别景点
  {
    RC.tim_flag = 1;
    stop();
    if (time6_count > 600)
    {
      RC.tim_flag = 0;
      HAL_Delay(10);
      break;
    }
  }
  PLAY_UPRIGHT_SPOTS(); // 语音播报
  while (1)
  {
    track_PID(-4500);
    if (EL == 0 || ER == 0)
    {
      break;
    }
  }

  // 岔路口3左转
  turn_angle(turn_left, 80, 5000);
  while (1) // 循迹到岔路口4
  {
    RC.tim_flag = 1;
    track_PID(4000);
    if (QR == 0 && time6_count > 150)
    {
      RC.tim_flag = 0;
      HAL_Delay(10);
      break;
    }
  }
  go_forward(4500, 180);
  turn_angle(turn_left, 75, 5000);
  go_forward(4500, 210);

  while (1) // 循迹过梯形山1
  {
    RC.tim_flag = 1;
    track_PID(5000);
    if (time6_count > 2400)
    {
      RC.tim_flag = 0;
      HAL_Delay(10);
      break;
    }
  }

  while (1) // 循迹到路口5
  {
    read_sensor_data();
    track_PID(7000);
    RC.tim_flag = 1;
    if (QR == 0 && time6_count > 20)
    {
      RC.tim_flag = 0;
      HAL_Delay(10);
      break;
    }
  }
  go_forward(4000, 200);

  turn_angle(turn_right, 70, 5000);
  while (1) // 循迹到岔路口6
  {
    RC.tim_flag = 1;
    track_PID(7000);
    if (time6_count > 900)
    {
      RC.tim_flag = 0;
      HAL_Delay(10);
      break;
    }
  }
  while (1) // 循迹到岔路口6
  {
    track_PID(6500);
    if (QR == 0)
    {
      break;
    }
  }
  go_forward(4000, 200);
  turn_angle(turn_right, 70, 5000);
  while (1) // 循迹到梯形山2前
  {
    RC.tim_flag = 1;
    track_PID(8500);
    if (time6_count > 800)
    {
      RC.tim_flag = 0;
      HAL_Delay(10);
      break;
    }
  }

  while (1) // 循迹下梯形山2
  {
    RC.tim_flag = 1;
    track_PID(5000);
    if (time6_count > 1000)
    {
      RC.tim_flag = 0;
      HAL_Delay(10);
      break;
    }
  }
  // while(1)
  // {
  //     stop();
  // }
  while (1) // 循迹到路口7
  {
    track_PID(6500);
    if (QR == 0)
    {
      break;
    }
  }
  go_forward(4000, 200);
  turn_angle(turn_right, 70, 5000);
  while (1) // 循迹到岔路口8
  {
    RC.tim_flag = 1;
    track_PID(5000);
    if (QL == 0 && time6_count > 300)
    {
      RC.tim_flag = 0;
      HAL_Delay(10);
      break;
    }
  }
  go_forward(4000, 200);
  turn_angle(turn_right, 70, 5000);
  while (1)
  {
    RC.tim_flag = 1;
    track_PID(5000);
    if (time6_count >= 300)
    {
      RC.tim_flag = 0;
      HAL_Delay(10);
      break;
    }
  }
  while (1) // 过路障
  {
    RC.tim_flag = 1;
    track_PID(3300);
    if (time6_count > 4600)
    {
      RC.tim_flag = 0;
      HAL_Delay(10);
      break;
    }
  }
  // while (1)
  // {
  //     stop();
  // }
  while (1) // 上平台
  {
    RC.tim_flag = 1;
    track_PID(5000);
    read_sensor_data();
    if (sum == 0 && time6_count > 600)
    {
      RC.tim_flag = 0;
      HAL_Delay(10);
      break;
    }
  }
  while (1) // 撞击平台
  {
    speed_pid(3000);
    set_moto_current(motor_pid_speed[0].output, motor_pid_speed[1].output,
                     motor_pid_speed[2].output, motor_pid_speed[3].output);
    HAL_Delay(10);
    if (EQ == 0)
    {
      break;
    }
  }
  go_forward(-3000, 300);
  while (1) // 停下等待
  {
    stop();
    RC.tim_flag = 1;
    if (time6_count >= 500)
    {
      RC.tim_flag = 0;
      HAL_Delay(10);
      break;
    }
  }
  PLAY_ARRIVE_SEVEN(); // 语音播报
  do_platform();

  turn_angle(turn_left, 167, 5000);
}

/************************************************************************************************************************************
 */
void seven_to_eight(void)
{
  go_forward(3000, 600); // 下平台
  while (1)              // 循迹到路障
  {
    track_PID(4500);
    RC.tim_flag = 1;
    if (QR == 0 && time6_count > 1200)
    {
      RC.tim_flag = 0;
      time6_count = 0;
      HAL_Delay(10);
      break;
    }
  }
  // while (1)
  // {
  //     stop();
  // }
  while (1) // 过路障
  {
    RC.tim_flag = 1;
    track_PID(3300);
    if (time6_count > 4100)
    {
      RC.tim_flag = 0;
      time6_count = 0;
      HAL_Delay(10);
      break;
    }
  }
  // while (1)
  // {
  //     stop();
  // }
  while (1) // 循迹到梯形山
  {
    RC.tim_flag = 1;
    track_PID(8000);
    if (time6_count > 900)
    {
      RC.tim_flag = 0;
      time6_count = 0;
      HAL_Delay(10);
      break;
    }
  }
  // while(1)
  // {
  //     stop();
  // }
  while (1) // 循迹过梯形山
  {
    RC.tim_flag = 1;
    track_PID(5000);
    if (time6_count > 1300)
    {
      RC.tim_flag = 0;
      time6_count = 0;
      HAL_Delay(10);
      break;
    }
  }
  // while(1)
  // {
  //     stop();
  // }

  while (1)
  {
    RC.tim_flag = 1;
    track_PID(7500);
    if (time6_count > 1200)
    {
      RC.tim_flag = 0;
      time6_count = 0;
      HAL_Delay(10);
      break;
    }
  }
  // while (1)
  // {
  //     stop();
  // }
  while (1) // 上平台8前半
  {
    RC.tim_flag = 1;
    track_PID(3000);
    read_sensor_data();
    if (sum == 0 && time6_count > 500)
    {
      RC.tim_flag = 0;
      time6_count = 0;
      HAL_Delay(10);
      break;
    }
  }
  while (1) // 上平台8后半
  {
    track_PID(2500);
    read_sensor_data();
    if (sum == 0)
    {
      break;
    }
  }
  while (1) // 撞击平台
  {
    speed_pid(3000);
    set_moto_current(motor_pid_speed[0].output, motor_pid_speed[1].output,
                     motor_pid_speed[2].output, motor_pid_speed[3].output);
    HAL_Delay(10);
    if (EQ == 0)
    {
      break;
    }
  }
  while (1)
  {
    RC.tim_flag = 1;
    stop();
    if (time6_count > 300)
    {
      RC.tim_flag = 0;
      HAL_Delay(10);
      break;
    }
  }
  go_forward(-3000, 300);
  while (1) // 停下等待
  {
    stop();
    RC.tim_flag = 1;
    if (time6_count >= 500)
    {
      RC.tim_flag = 0;
      HAL_Delay(10);
      break;
    }
  }
  PLAY_ARRIVE_EIGHT(); // 语音播报
  do_platform();
  turn_angle(turn_right, 160, 5000);
}

/************************************************************************************************************************************
 */
void eight_to_spot(void)
{
  go_forward(3000, 100); // 下平台
  while (1)
  {
    track_PID(2500);
    RC.tim_flag = 1;
    read_sensor_data();
    if (sum == 0 && time6_count > 1200) // 到平台8中
    {
      RC.tim_flag = 0;
      time6_count = 0;
      break;
    }
  }
  go_forward(5000, 800);
  while (1) // 循迹到岔路口
  {
    track_PID(4000);
    RC.tim_flag = 1;
    if (time6_count > 1000)
    {
      RC.tim_flag = 0;
      time6_count = 0;
      break;
    }
  }
  while (1) // 循迹到岔路口
  {
    track_PID(7000);
    read_sensor_data();
    if (QL == 0)
    {
      break;
    }
  }
  go_forward(6000, 300);
  turn_angle(turn_left, 110, 5000); // 转Y弯
  while (1)                   // 循迹到路口1
  {
    RC.tim_flag = 1;
    track_PID(6000);
    if (time6_count > 300)
    {
      RC.tim_flag = 0;
      HAL_Delay(10);
      break;
    }
  }
  while (1) // 循迹到路口1
  {
    RC.tim_flag = 1;
    track_PID(8000);
    if (time6_count > 1000)
    {
      RC.tim_flag = 0;
      HAL_Delay(10);
      break;
    }
  }
  while (1) // 循迹到路口1
  {
    RC.tim_flag = 1;
    track_PID(6000);
    if (QL == 0 && time6_count > 200)
    {
      RC.tim_flag = 0;
      HAL_Delay(10);
      break;
    }
  }
  // while (1)
  // {
  //     stop();
  // }

  go_forward(4000, 200);
  turn_angle(turn_left, 100, 5000);

  // 过山洞1

  while (1) // 循迹到路口2
  {
    RC.tim_flag = 1;
    track_PID(8000);
    if (time6_count > 500)
    {
      RC.tim_flag = 0;
      HAL_Delay(10);
      break;
    }
  }
  while (1) // 循迹到路口2
  {
    RC.tim_flag = 1;
    track_PID(6000);
    if (QR == 0 && time6_count > 200)
    {
      RC.tim_flag = 0;
      HAL_Delay(10);
      break;
    }
  }
  go_forward(4000, 190);
  HAL_Delay(10);
  turn_angle(turn_right, 88, 5000);

  while (1) // 循迹到路口3
  {
    RC.tim_flag = 1;
    track_PID(6500);
    if (QR == 0 && time6_count > 200)
    {
      RC.tim_flag = 0;
      HAL_Delay(10);
      break;
    }
  }
  go_forward(4000, 180);
  HAL_Delay(10);
  turn_angle(turn_right, 50, 5000); // 右转小心撞山洞

  // 过山洞2

  while (1) // 循迹到直立景点
  {
    RC.tim_flag = 1;
    track_PID(7000);
    if (QR == 0 && time6_count > 200)
    {
      RC.tim_flag = 0;
      HAL_Delay(10);
      break;
    }
  }

  go_forward(4000, 150);
  HAL_Delay(10);
  turn_angle(turn_right, 75, 5000);

  while (1) // 到达景点
  {
    track_PID(3000);
    if (EQ == 0)
    {
      break;
    }
  }
  PLAY_UPRIGHT_SPOTS(); // 语音播报
}

void spot_to_home(void)
{

  while (1)
  {
    track_PID(-4500);
    if (EL == 0)
    {
      break;
    }
  }

  turn_angle(turn_left, 90, 5000);

  while (1) // 循迹到路口
  {
    RC.tim_flag = 1;
    track_PID(5000);
    if (QR == 0 && time6_count > 200)
    {
      RC.tim_flag = 0;
      HAL_Delay(10);
      break;
    }
  }

  go_forward(5000, 80);
  turn_angle(turn_right, 65, 5000);

  while (1) // 循迹到路障前路口（低速）
  {
    RC.tim_flag = 1;
    track_PID(5000);
    if (QL == 0 && time6_count > 100)
    {
      RC.tim_flag = 0;
      HAL_Delay(10);
      break;
    }
  }

  go_forward(5000, 1200);
  while (1) // 循迹到路障前路口（高速）
  {
    RC.tim_flag = 1;
    track_PID(5000);
    if (time6_count >= 200)
    {
      RC.tim_flag = 0;
      HAL_Delay(10);
      break;
    }
  }
  while (1) // 循迹到路障前路口（高速）
  {
    RC.tim_flag = 1;
    track_PID(7000);
    if (time6_count >= 600)
    {
      RC.tim_flag = 0;
      HAL_Delay(10);
      break;
    }
  }

  // while(1)
  // {
  //     stop();
  // }

  while (1) // 循迹到路障前路口（低速）
  {
    RC.tim_flag = 1;
    track_PID(6000);
    if (QR == 0 && time6_count >= 100)
    {
      RC.tim_flag = 0;
      HAL_Delay(10);
      break;
    }
  }
  // while(1)
  // {
  //     stop();
  // }
  // line1 = 1;
  if (line1 == 1) // 第一个指示牌为绿灯
  {

    while (1) // 循迹路障前
    {
      RC.tim_flag = 1;
      track_PID(6000);
      if (time6_count >= 500)
      {
        RC.tim_flag = 0;
        HAL_Delay(10);
        break;
      }
    }
    // while (1)
    // {
    //     stop();
    // }
    while (1) // 过路障
    {
      RC.tim_flag = 1;
      track_PID(3500);
      if (time6_count > 4000)
      {
        RC.tim_flag = 0;
        HAL_Delay(10);
        break;
      }
    }
    // while (1)
    // {
    //     stop();
    // }
    while (1) // 循迹到绿灯前一个路口
    {
      RC.tim_flag = 1;
      track_PID(7000);
      if (time6_count >= 500)
      {
        RC.tim_flag = 0;
        HAL_Delay(10);
        break;
      }
    }

    while (1) // 循迹到绿灯前一个路口
    {

      track_PID(7000);
      if (EL == 0)
      {
        HAL_Delay(10);
        break;
      }
    }

    HAL_Delay(10);
    turn_angle(turn_left, 65, 5000);
    while (1) // 过绿灯
    {

      RC.tim_flag = 1;
      track_PID(6000);
      if (time6_count > 300)
      {
        RC.tim_flag = 0;
        HAL_Delay(10);
        break;
      }
    }

    while (1) // 过绿灯
    {

      RC.tim_flag = 1;
      track_PID(8500);
      if (time6_count > 1200)
      {
        RC.tim_flag = 0;
        HAL_Delay(10);
        break;
      }
    }
    while (1) // 过绿灯
    {

      RC.tim_flag = 1;
      track_PID(7000);
      if (QL == 0 && time6_count > 200)
      {
        RC.tim_flag = 0;
        HAL_Delay(10);
        break;
      }
    }

    go_forward(6000, 200);
    HAL_Delay(10);
    turn_angle(turn_left, 65, 5000);

    while (1) // 岔路口前
    {

      RC.tim_flag = 1;
      track_PID(6000);
      if (QR == 0 && time6_count > 1000)
      {
        RC.tim_flag = 0;
        HAL_Delay(10);
        break;
      }
    }

    go_forward(6000, 200);
    HAL_Delay(10);
    turn_angle(turn_right, 110, 5000);
  }

  else if (line4 == 1) // 第四个指示牌为绿灯
  {
    go_forward(4000, 110);
    turn_angle(turn_left, 75, 5000);

    while (1) //  路线4到岔路口（低速）
    {
      RC.tim_flag = 1;
      track_PID(6000);
      if (time6_count >= 500)
      {
        RC.tim_flag = 0;
        HAL_Delay(10);
        break;
      }
    }
    while (1) // 路线4到岔路口（高速）
    {
      RC.tim_flag = 1;
      track_PID(8500);
      if (time6_count >= 1400)
      {
        RC.tim_flag = 0;
        HAL_Delay(10);
        break;
      }
    }
    //         while (1)
    // {
    //     stop();
    // }
    while (1) // 路线4到岔路口（低速）
    {
      RC.tim_flag = 1;
      track_PID(6000);
      if (QL == 0 && time6_count >= 100)
      {
        RC.tim_flag = 0;
        HAL_Delay(10);
        break;
      }
    }
    //     while (1)
    // {
    //     stop();
    // }
    go_forward(4000, 160);
    turn_angle(turn_right, 65, 5000);

    while (1) // 路线4到k字路口（低速）
    {
      RC.tim_flag = 1;
      track_PID(6000);
      if (time6_count >= 100)
      {
        RC.tim_flag = 0;
        HAL_Delay(10);
        break;
      }
    }

    while (1) // 路线4到k字路口（高速）
    {
      RC.tim_flag = 1;
      track_PID(8500);
      if (time6_count >= 800)
      {
        RC.tim_flag = 0;
        HAL_Delay(10);
        break;
      }
    }

    while (1) // 路线4到k字路口（低速）
    {
      RC.tim_flag = 1;
      track_PID(6000);
      if (QL == 0 && time6_count >= 100)
      {
        RC.tim_flag = 0;
        HAL_Delay(10);
        break;
      }
    }
    //     while (1)
    // {
    //     stop();
    // }
    go_forward(4000, 350);
    turn_angle(turn_left, 30, 5000);
  }
  else if (line2 == 1) // 第二指示牌为绿灯
  {
    go_forward(5000, 200);
    turn_angle(turn_left, 40, 5000); // 左转

    while (1)
    {
      RC.tim_flag = 1;
      track_PID(7000);
      if (time6_count > 300)
      {
        RC.tim_flag = 0;
        HAL_Delay(10);
        break;
      }
    }

    while (1)
    {
      RC.tim_flag = 1;
      track_PID(8500);
      if (time6_count > 300)
      {
        RC.tim_flag = 0;
        HAL_Delay(10);
        break;
      }
    }

    // 循迹到岔路口6
    while (1) // 高速
    {
      RC.tim_flag = 1;
      track_PID(8000);
      if (time6_count > 1700)
      {
        RC.tim_flag = 0;
        HAL_Delay(10);
        break;
      }
    }
    while (1)
    {
      RC.tim_flag = 1;
      track_PID(8000);
      if (QL == 0 && time6_count > 400)
      {
        RC.tim_flag = 0;
        HAL_Delay(10);
        break;
      }
    }

    // 左转
    go_forward(5000, 150);
    turn_angle(turn_left, 105, 5000);
    while (1) // 岔路口前
    {

      RC.tim_flag = 1;
      track_PID(6000);
      if (QR == 0 && time6_count > 1000)
      {
        RC.tim_flag = 0;
        HAL_Delay(10);
        break;
      }
    }

    go_forward(6000, 150);
    HAL_Delay(10);
    turn_angle(turn_right, 110, 5000);
  }
  else if (line3 == 1) // 第三个指示牌为绿灯
  {
    go_forward(4000, 150);
    turn_angle(turn_left, 35, 5000); // 左转

    while (1)
    {
      RC.tim_flag = 1;
      track_PID(6000);
      if (time6_count > 440)
      {
        RC.tim_flag = 0;
        HAL_Delay(10);
        break;
      }
    }

    while (1)
    {
      track_PID(8000);
      RC.tim_flag = 1;
      if (time6_count > 700)
      {
        RC.tim_flag = 0;
        HAL_Delay(10);
        break;
      }
    }

    while (1)
    {
      track_PID(6000);
      RC.tim_flag = 1;
      read_sensor_data();
      if (QL == 0 && time6_count > 200)
      {
        RC.tim_flag = 0;
        HAL_Delay(10);
        break;
      }
    }

    go_forward(4000, 150);
    turn_angle(turn_left, 80, 5000); // 左转

    while (1)
    {
      RC.tim_flag = 1;
      track_PID(7000);
      if (time6_count > 400)
      {
        RC.tim_flag = 0;
        HAL_Delay(10);
        break;
      }
    }

    while (1)
    {
      track_PID(8000);
      RC.tim_flag = 1;
      if (time6_count > 800)
      {
        RC.tim_flag = 0;
        HAL_Delay(10);
        break;
      }
    }

    while (1)
    {
      track_PID(6000);
      RC.tim_flag = 1;
      read_sensor_data();
      if (QL == 0 && time6_count > 200)
      {
        RC.tim_flag = 0;
        HAL_Delay(10);
        break;
      }
    }

    go_forward(4000, 350);
    turn_angle(turn_right, 110, 5000); // 右转

    while (1) // 路线4到k字路口（低速）
    {
      RC.tim_flag = 1;
      track_PID(6000);
      if (time6_count >= 100)
      {
        RC.tim_flag = 0;
        HAL_Delay(10);
        break;
      }
    }

    while (1) // 路线4到k字路口（高速）
    {
      RC.tim_flag = 1;
      track_PID(8500);
      if (time6_count >= 800)
      {
        RC.tim_flag = 0;
        HAL_Delay(10);
        break;
      }
    }

    while (1) // 路线4到k字路口（低速）
    {
      RC.tim_flag = 1;
      track_PID(6000);
      if (QL == 0 && time6_count >= 100)
      {
        RC.tim_flag = 0;
        HAL_Delay(10);
        break;
      }
    }
    //     while (1)
    // {
    //     stop();
    // }
    go_forward(4000, 350);
    turn_angle(turn_left, 30, 5000);
  }

  while (1) // 过路障前
  {
    RC.tim_flag = 1;
    track_PID(4000);
    if (time6_count > 500)
    {
      RC.tim_flag = 0;
      HAL_Delay(10);
      break;
    }
  }

  while (1) // 过路障
  {
    RC.tim_flag = 1;
    track_PID(3300);
    if (time6_count > 2000)
    {
      RC.tim_flag = 0;
      HAL_Delay(10);
      break;
    }
  }

  while (1) // 岔路口前
  {
    RC.tim_flag = 1;
    track_PID(6000);
    if (QL == 0 && time6_count > 300)
    {
      RC.tim_flag = 0;
      HAL_Delay(10);
      break;
    }
  }
  go_forward(5000, 190);
  turn_angle(turn_right, 16, 5000); // 右转

  // 到平台
  while (1)
  {
    track_PID(6000);
    RC.tim_flag = 1;
    read_sensor_data();
    if (sum == 0 && time6_count > 400)
    {
      HAL_Delay(10);
      RC.tim_flag = 0;
      break;
    }
  }

  go_forward(5000, 1300);
  // 平台3掉头
  turn_angle(turn_left, 165, 5000);
  while (1)
  {
    RC.tim_flag = 1;
    stop();
    if (time6_count > 3000)
    {
      RC.tim_flag = 0;
      HAL_Delay(10);
      break;
    }
  }
}
