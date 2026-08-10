#include "sensor.h"

void read_sensor_data(void)
{
    E2;
    E6;
    E7;
    E8;
    E9;
    E10;
    E11;
    E15;
    sum = E2 + E6 + E7 + E8 + E9 + E10 + E11 + E15;
}

void Servo1_SetAngle(float Angle)   //E,底座
{
    TIM4->CCR1 = Angle / 180 * 2000 + 500;
}
void Servo2_SetAngle(float Angle)   //F,右手
{
    TIM4->CCR2 = Angle / 180 * 2000 + 500;
}
void Servo3_SetAngle(float Angle)   //G,左手
{
    TIM4->CCR3 = Angle / 180 * 2000 + 500;
}
void Servo4_SetAngle(float Angle)   //H,头
{
    TIM4->CCR4 = Angle / 180 * 2000 + 500;
}

void all_set(void)
{
    Servo1_SetAngle(0);    //机器人站起
    HAL_Delay(200);
    Servo4_SetAngle(90);   //头部转向前方
    Servo2_SetAngle(180);
    Servo3_SetAngle(10);
    HAL_Delay(1000);
    Servo2_SetAngle(0);
    Servo3_SetAngle(190);
    HAL_Delay(200);
    Servo1_SetAngle(100);    //机器人倒下
}

void do_platform(void)
{
    Servo1_SetAngle(0);    //机器人站起
    HAL_Delay(200);
    Servo2_SetAngle(180);
    HAL_Delay(300);
    Servo3_SetAngle(10);
    HAL_Delay(300);
    Servo2_SetAngle(0);
    HAL_Delay(300);
    Servo3_SetAngle(190);
    HAL_Delay(200);
    Servo1_SetAngle(100);    //机器人倒下
}