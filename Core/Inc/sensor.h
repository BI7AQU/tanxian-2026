#ifndef __SENSOR_H
#define __SENSOR_H

#include "main.h"

/*-------------车头十六路灰度----------------*/
#define E2 HAL_GPIO_ReadPin(I2_GPIO_Port, I2_Pin)
#define E6 HAL_GPIO_ReadPin(J2_GPIO_Port, J2_Pin)
#define E7 HAL_GPIO_ReadPin(K2_GPIO_Port, K2_Pin)
#define E8 HAL_GPIO_ReadPin(L2_GPIO_Port, L2_Pin)
#define E9 HAL_GPIO_ReadPin(M2_GPIO_Port, M2_Pin)
#define E10 HAL_GPIO_ReadPin(N2_GPIO_Port, N2_Pin)
#define E11 HAL_GPIO_ReadPin(O2_GPIO_Port, O2_Pin)
#define E15 HAL_GPIO_ReadPin(P2_GPIO_Port, P2_Pin)

#define EL HAL_GPIO_ReadPin(X_GPIO_Port, X_Pin) //车身色标
#define ER HAL_GPIO_ReadPin(W_GPIO_Port, W_Pin) //车身色标
#define QL HAL_GPIO_ReadPin(Z_GPIO_Port, Z_Pin) //车头色标
#define QR HAL_GPIO_ReadPin(Y_GPIO_Port, Y_Pin) //车头色标

#define EQ HAL_GPIO_ReadPin(V_GPIO_Port, V_Pin) //车头按键
#define GQ HAL_GPIO_ReadPin(U_GPIO_Port,U_Pin)  //车头红外
void read_sensor_data(void);

void Servo1_SetAngle(float Angle);
void Servo2_SetAngle(float Angle);
void Servo3_SetAngle(float Angle);
void Servo4_SetAngle(float Angle);

void all_set(void);
void do_platform(void);

#endif
