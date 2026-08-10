#include "m2006.h"

/*************************************
 *底盘电机定义：
 *motor1：右前轮
 *motor2：右后轮
 *motor3：左前轮
 *motor4：左后轮
 **************************************/

void track_PID(float speed)
{
	if (speed <= 3000)
		track_run(speed, 8, 0, 1.0, 0);
	else if (speed <= 5000)
		track_run(speed, 6, 0, 1.0, 0);
	else if (speed <= 7000)
		track_run(speed, 6, 0, 0.8, 0);
	else if (speed <= 10000)
		track_run(speed, 5, 0, 0.7, 0);
	else if (speed <= 12000)
		track_run(speed, 4, 0, 0.4, 0);
}
void motor_tatget(float right_speed, float left_speed)
{
	for (int i = 0; i < 2; i++)
	{
		motor_pid_speed[i].target = -right_speed;
		motor_pid_speed[i].f_cal_pid(&motor_pid_speed[i], motor_chassis[i].speed_rpm); // 根据设定值进行PID计算。
	}
	for (int i = 2; i < 4; i++)
	{
		motor_pid_speed[i].target = left_speed;
		motor_pid_speed[i].f_cal_pid(&motor_pid_speed[i], motor_chassis[i].speed_rpm); // 根据设定值进行PID计算。
	}
}
/*************************************
 *函数名称：track_PID
 *函数功能：直线循迹，用串口线连接，只输出偏移值
 *参数：throttle：最大速度值，取值范围0-85，P：比例系数，取值范围0.01-0.80
 *说明：
 *
 **************************************/
void track_run(float speed, float outer_kp, float outer_kd, float inner_kp, float inner_kd)
{

	read_sensor_data();
	if ((sum >= 3 || E8 || E9) && RC.eight_flag == 0)
	{
		motor_tatget(speed, speed);
	}
	else
	{
		float outer_ki = 0;
		float inner_ki = 0;
		uint16_t temp_data[2] = {0};   // 灰度数据缓存
		float position_error = 0;	   // 位置偏差
		float target_angular_velocity; // 目标角速度
		float angular_error;		   // 角速度偏差
		float pid_output;			   // PID输出

		static float outer_integral, outer_last_error, inner_integral, inner_last_error;

		// 传感器数据读取
		Read_Data(temp_data);
		get_imu_data();
		// 灰度误差计算
		position_error = (temp_data[0] == 0) ? -temp_data[1] : temp_data[1];

		// 外环（位置环）计算
		float outer_p = outer_kp * position_error;
		float outer_i = outer_ki * (outer_integral += position_error);
		float outer_d = outer_kd * (position_error - outer_last_error);
		outer_last_error = position_error;

		// 外环输出=目标角速度
		target_angular_velocity = outer_p + outer_i + outer_d;

		// 内环（速度环）计算
		float angular_velocity = imu.angularz; // 当前角速度
		angular_error = target_angular_velocity - angular_velocity;

		float inner_p = inner_kp * angular_error;
		float inner_i = inner_ki * (inner_integral += angular_error);
		float inner_d = inner_kd * (angular_error - inner_last_error);
		inner_last_error = angular_error;

		pid_output = inner_p + inner_i + inner_d;

		float left_speed = speed + pid_output;
		float right_speed = speed - pid_output;
		motor_tatget(right_speed, left_speed);
	}
	set_moto_current(motor_pid_speed[0].output, motor_pid_speed[1].output, motor_pid_speed[2].output, motor_pid_speed[3].output);

	HAL_Delay(4);
}

/// @brief 使用速度环控制向前走
/// @param speed
/// @param time
void go_forward(int16_t speed, uint16_t time)
{
	RC.tim_flag = 1;
	while (time6_count < time)
	{
		speed_pid(speed);
		set_moto_current(motor_pid_speed[0].output, motor_pid_speed[1].output, motor_pid_speed[2].output, motor_pid_speed[3].output);
		HAL_Delay(10);
	}
	RC.tim_flag = 0;
	time6_count = 0;
}

/// @brief 走直线桥函数
/// @param
void go_bridge(int32_t target, uint16_t time)
{
	RC.tim_flag = 1;
	int32_t Ltarget, Rtarget;
	while (1)
	{
		for (int i = 0; i < 2; i++)
		{
			Ltarget = target;
			if ((ER == 0 || QR == 0) && time6_count > 400)
			{
				Ltarget += 2000;
			}
			motor_pid_speed[i].target = -Ltarget;
			motor_pid_speed[i].f_cal_pid(&motor_pid_speed[i], motor_chassis[i].speed_rpm); // 根据设定值进行PID计算。
		}
		for (int i = 2; i < 4; i++)
		{
			Rtarget = target;
			if ((EL == 0 || QL == 0) && time6_count > 400)
			{
				Rtarget += 2000;
			}
			motor_pid_speed[i].target = Rtarget;
			motor_pid_speed[i].f_cal_pid(&motor_pid_speed[i], motor_chassis[i].speed_rpm); // 根据设定值进行PID计算。
		}
		set_moto_current(motor_pid_speed[0].output, motor_pid_speed[1].output, motor_pid_speed[2].output, motor_pid_speed[3].output);
		HAL_Delay(10);
		if (time6_count > time)
		{
			RC.tim_flag = 0;
			time6_count = 0;
			break;
		}
	}
	while (1)
	{
		RC.tim_flag = 1;
		speed_pid(3000);
		set_moto_current(motor_pid_speed[0].output, motor_pid_speed[1].output, motor_pid_speed[2].output, motor_pid_speed[3].output);
		read_sensor_data();
		HAL_Delay(10);
		if (sum > 0 && time6_count > 300)
		{
			RC.tim_flag = 0;
			time6_count = 0;
			return;
		}
	}
}

/// @brief 陀螺仪转弯
/// @param dir
/// @param angle
/// @param time
/// @return
void turn_angle(TurnDirection direction, float degrees, float speeed)
{
	get_imu_data();
	float current_yaw = imu.yaw;
	float target_angle = current_yaw + (-direction * degrees);
	if (target_angle > 180)
		target_angle -= 360;
	if (target_angle < -180)
		target_angle += 360;
	float error;
	if (direction == turn_left)
	{
		RGB_YELLOW(9, 0);
	}
	else
	{
		RGB_YELLOW(9, 1);
	}
	while (1)
	{
		get_imu_data();
		// if (direction == turn_left)
		// {
		// 	FlowLight_Yellow(0);
		// }
		// else
		// {
		// 	FlowLight_Yellow(1);
		// }
		for (int i = 0; i < 4; i++)
		{
			motor_pid_speed[i].target = direction * speeed;
			motor_pid_speed[i].f_cal_pid(&motor_pid_speed[i], motor_chassis[i].speed_rpm); // 根据设定值进行PID计算。
		}
		set_moto_current(motor_pid_speed[0].output, motor_pid_speed[1].output, motor_pid_speed[2].output, motor_pid_speed[3].output);
		HAL_Delay(10);
		if (fabs(target_angle - imu.yaw) < 5.0f)
		{
			if (direction == turn_left)
			{
				RGB_RED(9, 0);
			}
			else
			{
				RGB_RED(9, 1);
			}
			return;
		}
	}
}

void stop(void)
{
	speed_pid(0);
	set_moto_current(motor_pid_speed[0].output, motor_pid_speed[1].output, motor_pid_speed[2].output, motor_pid_speed[3].output);
	HAL_Delay(10);
}

void stop1(void)
{
	set_moto_current(0, 0, 0, 0);
}

void tracking(float speed, exit_cond cond, uint16_t time) // 循迹
{
	while (1)
	{
		track_PID(speed);
		RC.tim_flag = 1;
		if (time6_count > time)
		{
			uint8_t should_exit = 0;
			switch (cond)
			{
			case forward_left:
				should_exit = (QL == 0);
				break;
			case forward_right:
				should_exit = (QR == 0);
				break;
			case middle_left:
				should_exit = (EL == 0);
				break;
			case middle_right:
				should_exit = (ER == 0);
				break;
			case zero:
				should_exit = (sum == 0);
				break;
			case time_break:
				should_exit = (time6_count > time);
				break;
			default:
				break;
			}

			if (should_exit)
			{
				RC.tim_flag = 0;
				time6_count = 0;
				return;
			}
		}
	}
}

void tracking_expedite(float speed, exit_cond cond, uint16_t time)
{
	RC.tim_flag = 1;
	float current_speed = 6000;
	uint8_t expedite = 1;

	while (1) // 加速
	{
		uint16_t time_now;
		if (current_speed < speed && expedite == 1)
		{
			if (time6_count - time_now >= 200)
			{
				time_now = time6_count;
				current_speed += 1000;
				if (current_speed > speed)
				{
					current_speed = speed;
					expedite = 0;
					time_now = 0;
				}
			}
		}
		if ((time - time6_count) < 600) // 减速
		{

			if (time6_count - time_now >= 100)
			{
				time_now = time6_count;
				current_speed -= 2000;
				if (current_speed < 6000)
					current_speed = 6000;
			}
		}

		track_PID(current_speed);

		uint8_t should_exit = 0;
		if (time6_count > time)
		{
			switch (cond)
			{
			case forward_left:
				should_exit = (QL == 0);
				break;
			case forward_right:
				should_exit = (QR == 0);
				break;
			case middle_left:
				should_exit = (EL == 0);
				break;
			case middle_right:
				should_exit = (ER == 0);
				break;
			case zero:
				should_exit = (sum == 0);
				break;
			case time_break:
				should_exit = (time6_count >= time);
				break;
			default:
				break;
			}
		}

		if (should_exit)
		{
			RC.tim_flag = 0;
			time6_count = 0;
			return;
		}
	}
}

void stop_time(uint16_t time) // 等待
{
	while (1)
	{
		RC.tim_flag = 1;
		stop();
		if (time6_count > time)
		{
			time6_count = 0;
			RC.tim_flag = 0;
			HAL_Delay(10);
			return;
		}
	}
}
void strike(void) // 撞击平台
{
	while (1)
	{
		speed_pid(3000);
		set_moto_current(motor_pid_speed[0].output, motor_pid_speed[1].output, motor_pid_speed[2].output, motor_pid_speed[3].output);
		HAL_Delay(10);
		if (EQ == 0)
		{
			return;
		}
	}
}
void go_platform(uint8_t music) // 到平台
{
	strike(); // 撞击平台
	stop_time(400);
	go_forward(-3000, 300);
	stop_time(400);
	stop1();
	switch (music)
	{
	case 2:
		PLAY_ARRIVE_TWO();
		break;
	case 3:
		PLAY_ARRIVE_THREE();
		break;
	case 4:
		PLAY_ARRIVE_FOUR();
		break;
	case 5:
		PLAY_ARRIVE_FIVE();
		break;
	case 6:
		PLAY_ARRIVE_SIX();
		break;
	case 7:
		PLAY_ARRIVE_SEVEN();
		break;
	case 8:
		PLAY_ARRIVE_EIGHT();
		break;
	default:
		break;
	}
	stop1();
	do_platform();
	turn_angle(turn_right, 160, 5000);
	stop1();
}

void go_trapezoidal_mountain(void) // 过梯形山
{
}

void go_scenic_spot(uint16_t time) // 到景点
{
	strike(); // 撞击平台
	PLAY_UPRIGHT_SPOTS();
	stop_time(300);
	while (1)
	{
		track_PID(-3000);
		if (EL == 0 || ER == 0)
		{
			break;
		}
	}
	go_forward(-3000,time);
	turn_angle(turn_left, 80, 5000);
}

void go_bridge2(void)
{
}
void traffic_light(uint8_t num)
{
	stop_time(1000);
	get_color();
	switch (num)
	{
	case 1:
		if (RC.green_flag == 1)
		{
			RC.line_flag = 1;
		}
		else
		{
			RC.line_flag = 0;
		}
		break;

	case 2:
		if (RC.green_flag == 1)
		{
			RC.line_flag = 2;
		}
		else
		{
			RC.line_flag = 0;
		}
		break;

	case 3:
		if (RC.green_flag == 1)
		{
			RC.line_flag = 3;
		}
		else if (RC.blue_flag == 1)
		{
			RC.line_flag = 5;
		}
		else
		{
			RC.line_flag = 0;
		}
		break;

	case 4:
		if (RC.green_flag == 1)
		{
			RC.line_flag = 4;
		}
		else
		{
			RC.line_flag = 0;
		}
		break;

	default:
		break;
	}
}