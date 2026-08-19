#include "taskA.h"
void one_to_two2(void)
{
    go_forward(5000, 350);             // 下平台
    tracking(7000, forward_left, 400); // 到桥下
    go_forward(6000, 200);
    tracking(6000, zero, 200);
    go_bridge(5000, 1700);             // 过桥
    tracking(6000, zero, 1000);        // 到平台下
    go_platform(2);                    // 到平台并完成动作
}

void two_to_three2(void)
{
    go_forward(4000, 700);              // 下平台
    tracking(6000, forward_right, 500); // 到岔路口1
    turn_angle(turn_right, 13, 4000);   // 岔路口1右转
    //go_trapezoidal_mountain();        // 过梯形山
    tracking(6000, middle_right, 2200); // 到岔路口2
    turn_angle(turn_right, 111, 5000);  // 岔路口2右转
    tracking(6000, time_break, 1000);
    tracking_expedite(10000, time_break, 3000);
    // while (1)
    // {
    //     stop();
    // }
    tracking(7000, zero, 300); // 到平台下
    go_platform(3);            // 到平台并完成动作
}

void three_to_four2(void)
{
    go_forward(4000, 600);                        // 下平台
    tracking(5000, time_break, 1000);
    tracking_expedite(12000, forward_right, 4000); // 到岔路口4
    go_forward(5000, 200); 
    // while (1)
    // {
    //     stop();
    // }
    turn_angle(turn_left, 17, 5000);              // 岔路口1左转
    tracking(6000, time_break, 1700);  
    go_scenic_spot(100);               // 到达直立景点
    turn_angle(turn_left, 145, 5000);
    tracking(6000, forward_left, 500);
    go_forward(5000, 200);
    turn_angle(turn_left, 114, 5000);                  
    tracking(6000, zero, 600);                   // 到平台下
    go_platform(4);                               // 到平台并完成动作
}

void go_traffic_light(uint8_t num)
{
    switch (num)
    {
    case 1:
        tracking(5500, forward_left, 1000); // 到红绿灯1停

    //   while (1)  //用于调试红绿灯H值，记得开定时器7（100ms），用于OLED显示
    //   {
    //     stop();

    //     /* OLED刷新（TIM7每100ms置位） */
    //     if (oled_update_flag)
    //     {
    //       oled_update_flag = 0;
    //       get_imu_data();
    //       OLED_ShowNum(0, 0, (int32_t)imu.yaw, 3, 16, 1);
    //       uint8_t hsl[3];
    //       if (IIC_Get_HSL(hsl, 3))
    //       {
    //         OLED_ShowNum(0, 16, hsl[0], 3, 16, 1);
    //         OLED_ShowNum(48, 16, hsl[1], 3, 16, 1);
    //         OLED_ShowNum(96, 16, hsl[2], 3, 16, 1);
    //       }
    //       OLED_Refresh();
    //     }
    //   }

        traffic_light(1);
        if (RC.line_flag == 1) // 绿灯
        // if(1)
        {   
            tracking(7000, forward_left, 500);
            go_forward(5000, 50);
            turn_angle(turn_left, 70, 5000);
                // while(1)
                // {
                //     stop();
                // }
        }
        else // 蓝灯或者黑灯
        {
            turn_angle(turn_left, 145, 5000);   // 回头
            tracking(6000, forward_left, 500);  // 到岔路口1
            go_forward(5000, 200);
            turn_angle(turn_left, 107, 5000);   // 岔路口1左转
            go_forward(5000, 200);
        }
        break;
    case 2:
        tracking(5500, forward_left, 500);               // 到红绿灯2停
        traffic_light(2);
        if (RC.line_flag == 2) // 绿灯
        {
            tracking(6000, forward_right, 700);          // 到岔路口1
            go_forward(4000, 100);
            turn_angle(turn_left, 90, 5000);             // 岔路口1左转
            go_forward(4000, 100);
            tracking_expedite(8000, forward_right, 300); // 到岔路口2
            go_forward(5000, 350);
            turn_angle(turn_left, 12, 5000);             // 岔路口2左转
            go_forward(5000, 200);
        }
        else // 蓝灯或者黑灯
        {
            turn_angle(turn_left, 142, 5000);             // 回头
            tracking(5500, forward_right, 700);           // 到岔路口1
            go_forward(5000, 140);
            turn_angle(turn_left, 105, 5000);             // 岔路口1左转
            tracking(6000, forward_right, 500);
            go_forward(6000, 300);
            tracking_expedite(7000, forward_left, 500);  // 到岔路口2

            go_forward(5000, 250);
            turn_angle(turn_left, 115, 5000);             // 岔路口2左转
            go_forward(5000, 150);
        }
        break;
    case 3:
        tracking(5500, forward_left, 400);                // 到红绿灯3停
        traffic_light(3);
        if (RC.line_flag == 3 || RC.line_flag == 5)       // 绿灯或者蓝灯
        {
            tracking_expedite(9000, forward_left, 1300);  // 到岔路口1
            go_forward(6000, 130);
            turn_angle(turn_left, 15, 5000);              // 岔路口1左转
            go_forward(5000, 100);
        }
        else // 黑灯
        {   
            turn_angle(turn_left, 140, 5000);  // 回头
            RC.line_flag = 4;
        // while(1)
        // {
        //     stop(); 
        // }
            tracking(5500, forward_left, 400);           // 到岔路口1
            go_forward(5000, 240);
            turn_angle(turn_left, 115, 5000);            // 岔路口1左转
            tracking_expedite(10000, time_break, 1500);
            tracking(7000, forward_right, 100);          // 到岔路口2
            go_forward(5000, 100);
            turn_angle(turn_left, 65 , 5000);            // 岔路口2左转
            tracking(7000, time_break, 900);             // 到路障前
            tracking(5000, time_break, 2000);            // 过路障
            // while (1)
            // {
            //     stop();
            // }            
            tracking_expedite(7000, forward_right, 900); // 到岔路口3
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
    go_forward(6000, 50);
    turn_angle(turn_left, 76, 5000); // 岔路口2左转

    //traffic
    //one
    tracking(5500, forward_left, 1000);
    stop_time(1000);//fake to traffic
    //green
    // tracking(7000, forward_left, 500);
    // go_forward(5000, 50);
    // turn_angle(turn_left, 70, 5000);
    // //two
    turn_angle(turn_left, 145, 5000);            // 回头
    tracking(7000, forward_left, 500);           // 到岔路口1
    go_forward(5000, 220);
    turn_angle(turn_left, 108, 5000);            // 岔路口1左转
    go_forward(5000, 200);
    tracking(5500, forward_left, 500);
    stop_time(1000);//fake to traffic
    // green
    tracking(6000, forward_right, 300);          // 到岔路口1
    go_forward(4000, 100);
    turn_angle(turn_left, 90, 5000);             // 岔路口1左转
    go_forward(4000, 100);
    tracking_expedite(8000, forward_right, 300); // 到岔路口2
    go_forward(5000, 350);
    turn_angle(turn_left, 12, 5000);             // 岔路口2左转
    go_forward(5000, 200);
    // //three
    // turn_angle(turn_left, 142, 5000);            // 回头
    // tracking(6000, forward_right, 500);          // 到岔路口1
    // go_forward(6000, 200);
    // turn_angle(turn_left, 110, 5000);            // 岔路口1左转
    // tracking_expedite(7000, forward_left, 2000); // 到岔路口2
    // go_forward(5000, 250);
    // turn_angle(turn_left, 115, 5000);            // 岔路口2左转
    // go_forward(5000, 150);
    // tracking(5500, forward_left, 400);
    // stop_time(1000);//fake to traffic
    // tracking_expedite(9000, forward_left, 1300); // 到岔路口1
    // go_forward(6000, 130);
    // turn_angle(turn_left, 15, 5000);             // 岔路口1左转
    // go_forward(5000, 100);
    
    // go_traffic_light(1);             // 到红绿灯1
    // if (RC.line_flag == 0)           // 红绿灯不为绿灯
    //     go_traffic_light(2);         // 到红绿灯2
    // if (RC.line_flag == 0)           // 红绿灯不为绿灯
    //     go_traffic_light(3);         // 到红绿灯3
    tracking_expedite(8000, time_break, 1500);
    tracking(7000, zero, 200);
    go_platform(5);
}

void five_to_seven2(void)
{
    
    go_forward(4000, 400);              // 下平台
    tracking(8000, forward_left, 1200); // 到岔路口1   !!!现场注意距离，修改时间！！！
    go_forward(4000, 150);
    // while(1)
    // {
    //     stop();
    // }
    turn_angle(turn_left, 75, 5000); // 岔路口1左转
    tracking(6000, forward_right, 200);
    go_forward(5000, 110);
    turn_angle(turn_right, 80, 3000);  // 直立景点右转
    go_scenic_spot(100);               // 到达直立景点
    turn_angle(turn_left, 80, 5000);
    tracking(4000, forward_left, 300); // 到岔路口2
    go_forward(5500, 120);
    // while(1)
    // {
    //     stop();
    // }
    turn_angle(turn_left, 75, 4000); // 岔路口2左转
    go_forward(4500, 200);
    tracking(5500, time_break, 1800);
    // tracking(5000, time_break, 1500);
    tracking(7000, forward_right, 700); // 到岔路口3
    go_forward(5000, 120);                                                   
    turn_angle(turn_right, 70, 5000); // 岔路口3右转
    tracking(5500, time_break, 900);
    tracking(6500, forward_right, 20); // 到岔路口4
    go_forward(4000, 160);
    turn_angle(turn_right, 67, 5000); // 岔路口4右转
    tracking_expedite(8000, time_break, 1100);
    tracking(5000, time_break, 1200);
    tracking(7000, forward_right, 20); // 到岔路口5
    go_forward(4000, 200);
    turn_angle(turn_right, 70, 5000);  // 岔路口5右转
    tracking(7000, forward_left, 300); // 到岔路口6
    go_forward(4000, 200);
    turn_angle(turn_right, 70, 5000); // 岔路口6右转
    tracking(5000, forward_right, 600);
    tracking(4000, time_break, 3000);
    tracking(4500, zero, 1200); // 到平台下
    go_platform(7);             // 到平台并完成动作
}

void seven_to_eight2(void)
{
    go_forward(2800, 600);               // 下平台
    tracking(5500, forward_right, 1200); // 路障前
    tracking(4000, time_break, 3800);    // 过路障
    tracking(5500, time_break, 1800);    // 过梯形山
    tracking(6000, time_break, 280);
    go_forward(7000, 300);
    tracking(7000, time_break, 850);     //到平台下
    // while(1)
    // {
    //     stop();
    // }
    tracking(7000, time_break, 1500);
    tracking(5000, zero, 450); // 过8前半平台
    RC.eight_flag = 1;
    go_forward(3000, 700);     // 过平面
    tracking(4000, zero, 180); // 过8后半平台下
    go_platform(8);            // 到平台并完成动作
}

void go_home(uint8_t num)
{
    switch (num)
    {
    case 1: // 第一个红绿灯位绿灯
        go_forward(5000, 120);
        turn_angle(turn_right, 68, 5000);
        tracking_expedite(7000, time_break, 1000); // 到路障前
        tracking(5000, time_break, 2000); // 过路障
        tracking_expedite(6000, middle_left, 200);             // 到岔路口1
        turn_angle(turn_left, 60, 5000);              // 岔路口1左转
        // while(1)
        // {
        //     stop();
        // }
        tracking(5000, time_break, 400);
        tracking_expedite(8000, forward_right, 1000); // 到岔路口2
        go_forward(6000, 50);
        turn_angle(turn_left, 65, 5000);     // 岔路口2左转
        tracking(6000, forward_right, 1000); // 到岔路口3
        go_forward(6000, 250);
        turn_angle(turn_right, 110, 5000); // 岔路口3右转
        break;
    case 2: // 第二个红绿灯为绿灯
        go_forward(5000, 150);
        turn_angle(turn_right, 40, 5000);               // 岔路口1右转
        go_forward(5000, 100);
        tracking_expedite(10000, forward_right, 2600); // 到岔路口2
        go_forward(6000, 150);
        turn_angle(turn_left, 115, 5000);    // 岔路口2左转
        go_forward(6000, 100);
        tracking(6000, forward_right, 1000); // 到岔路口3
        go_forward(6000, 240);
        turn_angle(turn_right, 110, 5000); // 岔路口3右转
        break;
    case 3: // 第三个红绿灯为绿灯
        go_forward(5000, 150);
        turn_angle(turn_right, 40, 5000);             // 岔路口1右转
        go_forward(5000, 100);
        tracking_expedite(8000, forward_left, 1000); // 到岔路口2
        go_forward(6000, 120);
        turn_angle(turn_left, 80, 5000);     // 岔路口2左转
        tracking_expedite(7000, forward_right, 1500); // 到岔路口3
        go_forward(6000, 250);
        turn_angle(turn_right, 108, 5000);           // 岔路口3右转
        tracking_expedite(8000, forward_left, 1200); // 到岔路口4
        go_forward(6000, 300);
        turn_angle(turn_left, 18, 5000); // 岔路口4左转
        break;
    case 4: // 第四个红绿灯为绿灯
        go_forward(5000, 150);
        //直走
        tracking_expedite(10000, forward_left, 1300); // 到岔路口2
        go_forward(5000, 50);
        turn_angle(turn_right, 68, 5000);     // 岔路口2右转
        tracking_expedite(8000, forward_left, 1200); // 到岔路口3
        go_forward(6000, 200);
        turn_angle(turn_left, 15, 5000);           // 岔路口3左转
        break;
    case 5: // 第三个红绿灯为蓝灯
        go_forward(5000, 150);
        //直走
        tracking_expedite(10000, forward_left, 1300); // 到岔路口2
        go_forward(5000, 50);
        turn_angle(turn_right, 68, 5000);             // 岔路口2右转
        tracking_expedite(8000, forward_left, 1200);  // 到岔路口3
        go_forward(6000, 200);
        turn_angle(turn_left, 18, 5000);              // 岔路口3左转
        break;
    }
}
void eight_to_home(void)
{
    go_forward(3000, 500);            // 下平台
    tracking(3000, zero, 1300);       // 下8前半段平台
    go_forward(5000, 800);            // 过平面
    tracking(5500, time_break, 1400); // 下8后半平台
    RC.eight_flag = 0;
    tracking_expedite(7000, forward_left, 300); // 到岔路口1
    go_forward(6000, 320);
    turn_angle(turn_left, 125, 5000); // 岔路口1左转
    go_forward(5000, 150);
    // while (1)
    // {
    //     stop();
    // }
    tracking_expedite(8000, time_break, 1200);
    tracking(6000, forward_left, 200);  // 到岔路口2
    go_forward(6000, 120);
    turn_angle(turn_left, 90, 5000);    // 岔路口2左转
    // while (1)
    // {
    //     stop();
    // }
    tracking(5000, time_break, 500);
    tracking_expedite(7000, forward_right, 500);
    //tracking(7000, forward_right, 200); // 到岔路口3
    go_forward(4000, 150);
    turn_angle(turn_right, 75, 5000);   // 岔路口3右转
    tracking(7000, forward_right, 200);
    go_forward(4000, 180);
    turn_angle(turn_right, 73, 5000);   // 岔路口4右转
    // while(1)
    // {
    //     stop();
    // } 
    tracking(5000, time_break, 600);
    tracking(7000, forward_right, 900);
    go_forward(6000, 110);
    turn_angle(turn_right, 75, 5000);   // 直立景点右转
    go_scenic_spot(100);                // 到达直立景点
    turn_angle(turn_left, 80, 5000);              
    tracking(5500, forward_right, 300);
    go_forward(6000, 100);
    turn_angle(turn_right, 80, 5000);   // 到岔路口5右转
    tracking_expedite(7500, forward_left, 800);
    // while(1)
    // {
    //     stop();
    // }
    tracking_expedite(10000, time_break, 400);
    tracking(10000, forward_right, 300);
    //go_forward(5000, 50);
    turn_angle(turn_right, 70, 5000);  //右转去直立景点
    tracking(6000, forward_right, 200);
    go_forward(5000, 110);
    turn_angle(turn_right, 77, 3000);  // 直立景点右转
    go_scenic_spot(100);               // 到达直立景点
    turn_angle(turn_right, 75, 5000);
    tracking(6000, forward_right, 200);
    // while(1)
    // {
    //     stop();
    // } 
    //回家
    go_home(1);             // 选择路线返回  RC.line_flag
    // while(1)
    // {
    //     stop();
    // } 
    go_forward(5000, 200);  
    tracking(5000, time_break, 200);   // 到路障前
    tracking(4000, time_break, 2000);  // 过路障
    tracking(6000, forward_left, 100); // 到岔路口
    go_forward(5000, 240);
    // if(shibai==0)
    // {
    //     turn_angle(turn_right, 40, 5000);  // 岔路口右转
    //     tracking(5000, zero, 300);         // 到平台下
    //     go_forward(5000, 420);             // 到平台中间
    //     turn_angle(turn_right, 140, 4000);  // 平台you转归正
    //     // PLAY_ARRIVE_HOME();
    //     stop_time(3000);
    //     shibai++;
    // }

    
    turn_angle(turn_right, 16, 5000);  // 岔路口右转
    tracking(5000, zero, 300);         // 到平台下
    go_forward(5000, 420);             // 到平台中间
    turn_angle(turn_right, 140, 4000);  // 平台you转归正
    PLAY_ARRIVE_HOME();
    stop_time(3000);
    //到家了！！！
}