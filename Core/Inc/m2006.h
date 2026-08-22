#ifndef __M2006_H
#define __M2006_H

#include "main.h"

// 定义转向方向枚举
typedef enum
{
    turn_left = -1,
    turn_right = 1
} TurnDirection;

typedef enum
{
    forward_left = 0,
    forward_right = 1,
    middle_left = 2,
    middle_right = 3,
    zero = 4,
    go_break = 5,
    go_turn = 6,
    time_break = 7,
} exit_cond;

// 串级PID控制器结构体
typedef struct
{
    float outer_kp, outer_ki, outer_kd; // 外环参数
    float inner_kp, inner_ki, inner_kd; // 内环参数
    float outer_integral;               // 外环积分项
    float outer_last_error;             // 外环上次误差
    float inner_integral;               // 内环积分项
    float inner_last_error;             // 内环上次误差
} Cascade_PID;

extern Cascade_PID cascade;

void track_PID(float speed);
void track_run(float speed, float outer_kp, float outer_kd, float inner_kp, float inner_kd);
void motor_tatget(float R_thr, float L_thr);
void stop(void);
void stop1(void);
void go_forward(int16_t speed, uint16_t time);
void go_bridge(int32_t target, uint16_t time);
void turn_angle(TurnDirection direction, float degrees, float speeed);
void tracking(float speed, exit_cond cond, uint16_t time);
void tracking_expedite(float speed, exit_cond cond, uint16_t time);
void stop_time(uint16_t time);
void strike(void);
void strike_line(void);
void go_platform(uint8_t music);
void go_trapezoidal_mountain(void);
void go_scenic_spot(uint16_t time);
void go_bridge2(void);
void traffic_light(uint8_t num);
void turn_angle_Y(TurnDirection direction, float degrees, float speeed);
#endif /*__ M2006_H__ */
