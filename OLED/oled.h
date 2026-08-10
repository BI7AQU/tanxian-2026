#ifndef __OLED_H
#define __OLED_H

#include "stdlib.h"
#include "main.h"

//-----------------OLED端口定义----------------

#define OLED_SCL_Clr() HAL_GPIO_WritePin(OLED_SCK_GPIO_Port, OLED_SCK_Pin, 0) // SCL
#define OLED_SCL_Set() HAL_GPIO_WritePin(OLED_SCK_GPIO_Port, OLED_SCK_Pin, 1)

#define OLED_SDA_Clr() HAL_GPIO_WritePin(OLED_MOSI_GPIO_Port, OLED_MOSI_Pin, 0) // SDA
#define OLED_SDA_Set() HAL_GPIO_WritePin(OLED_MOSI_GPIO_Port, OLED_MOSI_Pin, 1)

#define OLED_RES_Clr() HAL_GPIO_WritePin(OLED_RST_GPIO_Port, OLED_RST_Pin, 0) // RES
#define OLED_RES_Set() HAL_GPIO_WritePin(OLED_RST_GPIO_Port, OLED_RST_Pin, 1)

#define OLED_DC_Clr() HAL_GPIO_WritePin(OLED_DC_GPIO_Port, OLED_DC_Pin, 0) // DC
#define OLED_DC_Set() HAL_GPIO_WritePin(OLED_DC_GPIO_Port, OLED_DC_Pin, 1)

#define OLED_CS_Clr() HAL_GPIO_WritePin(OLED_CS_GPIO_Port, OLED_CS_Pin, 0) // CS
#define OLED_CS_Set() HAL_GPIO_WritePin(OLED_CS_GPIO_Port, OLED_CS_Pin, 1)

#define OLED_CMD 0  // 写命令
#define OLED_DATA 1 // 写数据

void OLED_ClearPoint(uint8_t x, uint8_t y);
void OLED_ColorTurn(uint8_t i);
void OLED_DisplayTurn(uint8_t i);
void OLED_WR_Byte(uint8_t dat, uint8_t mode);
void OLED_DisPlay_On(void);
void OLED_DisPlay_Off(void);
void OLED_Refresh(void);
void OLED_Clear(void);
void OLED_DrawPoint(uint8_t x, uint8_t y, uint8_t t);
void OLED_DrawLine(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, uint8_t mode);
void OLED_DrawCircle(uint8_t x, uint8_t y, uint8_t r);
void OLED_ShowChar(uint8_t x, uint8_t y, uint8_t chr, uint8_t size1, uint8_t mode);
void OLED_ShowChar6x8(uint8_t x, uint8_t y, uint8_t chr, uint8_t mode);
void OLED_ShowString(uint8_t x, uint8_t y, uint8_t *chr, uint8_t size1, uint8_t mode);
void OLED_ShowNum(uint8_t x, uint8_t y, int32_t num, uint8_t len, uint8_t size1, uint8_t mode);
void OLED_ShowChinese(uint8_t x, uint8_t y, uint8_t num, uint8_t size1, uint8_t mode);
void OLED_ScrollDisplay(uint8_t num, uint8_t space, uint8_t mode);
void OLED_ShowPicture(uint8_t x, uint8_t y, uint8_t sizex, uint8_t sizey, uint8_t BMP[], uint8_t mode);
void oled_Init(void);

#endif
