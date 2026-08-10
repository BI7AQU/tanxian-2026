#include "taskA.h"
void one_to_two2(void)
{
    go_forward(4000, 400);             // 下平台
    tracking(6000, forward_left, 500); // 到桥下
    go_forward(6000, 200);
    tracking(6000, zero, 200);
    go_bridge(5000, 1700);      // 过桥
    tracking(6000, zero, 1000); // 到平台下
    go_platform(2);             // 到平台并完成动作
}

void two_to_three2(void)
{
    go_forward(4000, 700);              // 下平台
    tracking(6000, forward_right, 400); // 到岔路口1
    turn_angle(turn_right, 45, 5000);   // 岔路口1右转
    // go_trapezoidal_mountain();                  // 过梯形山
    tracking(6000, middle_right, 2200); // 到岔路口2
    turn_angle(turn_right, 110, 5000);  // 岔路口2右转
    tracking_expedite(11000, time_break, 3000);
    tracking(7000, zero, 300); // 到平台下
    go_platform(3);            // 到平台并完成动作
}

void three_to_four2(void)
{
    go_forward(4000, 600);                        // 下平台
    tracking_expedite(12000, forward_left, 4300); // 到岔路口4
    tracking(7000, zero, 1000);                   // 到平台下
    go_platform(4);                               // 到平台并完成动作
}

void go_traffic_light(uint8_t num)
{
    switch (num)
    {
    case 1:
        tracking(7000, forward_left, 1000); // 到红绿灯1停
        traffic_light(1);
        if (RC.line_flag == 1) // 绿灯
        {
            tracking(7000, forward_left, 500);
            go_forward(7000, 120);
            while(1)
            {
               stop(); 
            }
            stop();
            turn_angle(turn_left, 90, 5000);
        }
        else // 蓝灯或者黑灯
        {
            turn_angle(turn_left, 160, 5000);   // 回头
            tracking(7000, forward_right, 500); // 到岔路口1
            go_forward(6000, 160);
            turn_angle(turn_left, 113, 5000); // 岔路口1左转
        }
        break;
    case 2:
        tracking(6000, forward_left, 400); // 到红绿灯2停
        traffic_light(2);
        if (RC.line_flag == 2) // 绿灯
        {
            tracking(7000, forward_right, 300); // 到岔路口1
            go_forward(4000, 100);
            turn_angle(turn_left, 90, 5000); // 岔路口1左转
            go_forward(4000, 140);
            tracking_expedite(8000, forward_right, 300); // 到岔路口2
            go_forward(5000, 350);
            turn_angle(turn_left, 16, 5000); // 岔路口2左转
            go_forward(5000, 200);
        }
        else // 蓝灯或者黑灯
        {
            turn_angle(turn_left, 160, 5000);   // 回头
            tracking(6000, forward_right, 700); // 到岔路口1
            go_forward(6000, 210);
            turn_angle(turn_left, 105, 5000);             // 岔路口1左转
            tracking_expedite(10000, forward_left, 2000); // 到岔路口2
            go_forward(6000, 250);
            turn_angle(turn_left, 115, 5000); // 岔路口2左转
        }
        break;
    case 3:
        tracking(7000, forward_left, 400); // 到红绿灯3停
        traffic_light(3);
        if (RC.line_flag == 3 || RC.line_flag == 5) // 绿灯或者蓝灯
        {
            tracking_expedite(9000, forward_left, 1300); // 到岔路口1
            go_forward(6000, 130);
            turn_angle(turn_left, 20, 5000); // 岔路口1左转
            go_forward(5000, 100);
        }
        else // 黑灯
        {
            turn_angle(turn_left, 155, 5000);  // 回头
            tracking(7000, forward_left, 400); // 到岔路口1
            go_forward(6000, 250);
            turn_angle(turn_left, 110, 5000); // 岔路口1左转
            tracking_expedite(12000, time_break, 1500);
            tracking(8000, forward_right, 100); // 到岔路口2
            go_forward(6000, 170);
            turn_angle(turn_left, 70, 5000);              // 岔路口2左转
            tracking(6000, time_break, 500);              // 到路障前
            tracking(3300, time_break, 3900);             // 过路障
            tracking_expedite(8000, forward_right, 1000); // 到岔路口3
            go_forward(6000, 120);
        }
        break;
    }
}
void four_to_five2(void)
{
    go_forward(4000, 400); // 下平台
    tracking(7000, forward_right, 300);
    go_forward(7000, 250);
    tracking(8000, forward_left, 800); // 到岔路口2
    go_forward(6000, 90);
    turn_angle(turn_left, 90, 5000); // 岔路口2左转
    go_traffic_light(1);             // 到红绿灯1
    if (RC.line_flag == 0)           // 红绿灯不为绿灯
        go_traffic_light(2);         // 到红绿灯2
    if (RC.line_flag == 0)           // 红绿灯不为绿灯
        go_traffic_light(3);         // 到红绿灯3
    tracking_expedite(9000, time_break, 2000);
    tracking(7000, zero, 200);
    go_platform(5);
}

void five_to_seven2(void)
{
    go_forward(4000, 400);              // 下平台
    tracking(8000, forward_left, 2000); // 到岔路口1
    go_forward(6000, 150);
    turn_angle(turn_left, 82, 5000); // 岔路口1左转
    tracking(6000, forward_right, 400);
    go_forward(6000, 110);
    turn_angle(turn_right, 80, 5000);  // 直立景点右转
    go_scenic_spot(110);               // 到达直立景点
    tracking(6000, forward_left, 800); // 到岔路口2
    go_forward(4500, 170);
    turn_angle(turn_left, 75, 5000); // 岔路口2左转
    go_forward(4500, 200);
    tracking(7000, time_break, 1400);
    tracking(5000, time_break, 1500);
    tracking(7000, forward_right, 20); // 到岔路口3
    go_forward(4000, 200);
    turn_angle(turn_right, 70, 5000); // 岔路口3右转
    tracking(7000, time_break, 900);
    tracking(6500, forward_right, 20); // 到岔路口4
    go_forward(4000, 200);
    turn_angle(turn_right, 70, 5000); // 岔路口4右转
    tracking(8000, time_break, 1100);
    tracking(5000, time_break, 1200);
    tracking(7000, forward_right, 20); // 到岔路口5
    go_forward(4000, 200);
    turn_angle(turn_right, 70, 5000);  // 岔路口5右转
    tracking(7000, forward_left, 300); // 到岔路口6
    go_forward(4000, 200);
    turn_angle(turn_right, 70, 5000); // 岔路口6右转
    tracking(6000, forward_right, 500);
    tracking(3500, time_break, 4000);
    tracking(4500, zero, 1800); // 到平台下
    go_platform(7);             // 到平台并完成动作
}

void seven_to_eight2(void)
{
    go_forward(3000, 600);               // 下平台
    tracking(5500, forward_right, 1200); // 到岔路口1
    tracking(3600, time_break, 4100);
    tracking(8000, time_break, 900);
    tracking(6000, time_break, 1300);
    tracking(7500, time_break, 1400);
    tracking(5000, zero, 500); // 过8前半平台
    RC.eight_flag = 1;
    go_forward(3000, 800);     // 过平面
    tracking(4000, zero, 500); // 过8后半平台下
    go_platform(8);            // 到平台并完成动作
}

void go_home(uint8_t num)
{
    switch (num)
    {
    case 1:                               // 第一个红绿灯位绿灯
        tracking(7000, time_break, 1000); // 到路障前

        tracking(3500, time_break, 4000); // 过路障
        // while(1)
        // {
        //     stop();
        // }
        tracking(7000, middle_left, 300);             // 到岔路口1
        turn_angle(turn_left, 65, 5000);              // 岔路口1左转
        tracking_expedite(8000, forward_right, 1300); // 到岔路口2
        go_forward(6000, 150);
        turn_angle(turn_left, 65, 5000);     // 岔路口2左转
        tracking(6000, forward_right, 1000); // 到岔路口3
        go_forward(6000, 200);
        turn_angle(turn_right, 110, 5000); // 岔路口3右转
        break;
    case 2: // 第二个红绿灯为绿灯
        go_forward(5000, 200);
        turn_angle(turn_left, 40, 5000);               // 岔路口1左转
        tracking_expedite(10000, forward_right, 2600); // 到岔路口2
        go_forward(6000, 100);
        turn_angle(turn_left, 105, 5000);    // 岔路口2左转
        tracking(6000, forward_right, 1000); // 到岔路口3
        go_forward(6000, 150);
        turn_angle(turn_right, 110, 5000); // 岔路口3右转
        break;
    case 3: // 第三个红绿灯为绿灯
        go_forward(5000, 200);
        turn_angle(turn_left, 40, 5000);             // 岔路口1左转
        tracking_expedite(8000, forward_left, 1500); // 到岔路口2
        go_forward(6000, 100);
        turn_angle(turn_left, 60, 5000);     // 岔路口2左转
        tracking(7000, forward_right, 1500); // 到岔路口3
        go_forward(6000, 250);
        turn_angle(turn_right, 110, 5000);           // 岔路口3右转
        tracking_expedite(8000, forward_left, 1200); // 到岔路口4
        go_forward(6000, 200);
        turn_angle(turn_left, 30, 5000); // 岔路口4左转
        break;
    case 4: // 第四个红绿灯为绿灯
    case 5: // 第三个红绿灯为蓝灯
        go_forward(4000, 110);
        turn_angle(turn_left, 75, 5000);              // 岔路口1左转
        tracking_expedite(10000, forward_left, 1800); // 到岔路口2
        go_forward(4000, 160);
        turn_angle(turn_right, 65, 5000);            // 岔路口2右转
        tracking_expedite(9000, forward_left, 1000); // 到岔路口3
        go_forward(4000, 350);
        turn_angle(turn_left, 30, 5000); //  岔路口3左转
        break;
    }
}
void eight_to_home(void)
{
    go_forward(3000, 700);            // 下平台
    tracking(3000, zero, 1200);       // 下8前半段平台
    go_forward(5000, 800);            // 过平面
    tracking(5500, time_break, 1400); // 下8后半平台
    RC.eight_flag = 0;
    tracking(7000, forward_left, 200); // 到岔路口1
    go_forward(6000, 300);
    turn_angle(turn_left, 110, 5000); // 岔路口1左转
    tracking(6000, time_break, 300);
    tracking(8000, time_break, 1000);
    tracking(6000, forward_left, 200); // 到岔路口2
    go_forward(4000, 240);
    turn_angle(turn_left, 100, 5000); // 岔路口2左转
    tracking(8000, time_break, 700);
    tracking(7000, forward_right, 500); // 到岔路口3
    go_forward(4000, 190);
    turn_angle(turn_right, 80, 5000); // 岔路口3右转
    tracking(7000, forward_right, 200);
    go_forward(4000, 180);
    turn_angle(turn_right, 80, 5000);
    tracking(6000, forward_right, 900);
    go_forward(6000, 110);
    turn_angle(turn_right, 80, 5000); // 直立景点右转
    go_scenic_spot(200);              // 到达直立景点
    tracking(5500, forward_right, 500);
    go_forward(6000, 120);
    turn_angle(turn_right, 80, 5000);
    tracking(5000, forward_left, 100); // 到岔路口5
    go_forward(5000, 1400);
    tracking(5000, time_break, 400);
    tracking(7000, time_break, 500);
    tracking(6000, forward_right, 100);
    go_home(RC.line_flag);             // 选择路线返回
    tracking(4000, time_break, 500);   // 到路障前
    tracking(3300, time_break, 2500);  // 过路障
    tracking(6000, forward_left, 100); // 到岔路口
    go_forward(5000, 190);
    turn_angle(turn_right, 16, 5000); // 岔路口右转
    tracking(5000, zero, 300);        // 到平台下
    go_forward(5000, 500);            // 到平台中间
    turn_angle(turn_left, 165, 5000); // 平台左转归正
    stop_time(3000);
}