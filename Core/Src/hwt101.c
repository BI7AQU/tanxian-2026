#include "hwt101.h"

imu_TypeDef imu;
uint8_t ucRegIndex = 0;

/**
 * @brief  从SDK的sReg寄存器中读取IMU数据并更新imu结构体
 *         wit_c_sdk通过WitSerialDataIn()在串口中断中自动解析数据到sReg[]
 *         此函数只需从sReg[]读取即可
 */
void get_imu_data(void)
{
    imu.roll     = sReg[Roll]   / 32768.0f * 180.0f;   // 角度
    imu.pitch    = sReg[Pitch]  / 32768.0f * 180.0f;   // 角度
    imu.yaw      = sReg[Yaw]    / 32768.0f * 180.0f;   // 角度
    imu.angularx = sReg[GX]     / 32768.0f * 2000.0f;  // 角速度
    imu.angulary = sReg[GY]     / 32768.0f * 2000.0f;  // 角速度
    imu.angularz = sReg[GZ]     / 32768.0f * 2000.0f;  // 角速度
}
