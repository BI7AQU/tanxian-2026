#include "color_sensor.h"

/* 基本时序操作 */
static void IIC_Delay(void)
{
    Delay_us(10); // 根据实际I2C速度调整延时
}

/* 软件I2C基础函数 */
void IIC_Start(void)
{
    SDA_HIGH();
    SCL_HIGH();
    IIC_Delay();
    SDA_LOW();
    IIC_Delay();
    SCL_LOW();
}

void IIC_Stop(void)
{
    SDA_LOW();
    IIC_Delay();
    SCL_HIGH();
    IIC_Delay();
    SDA_HIGH();
    IIC_Delay();
}

unsigned char IIC_WaitAck(void)
{
    unsigned char ack;
    SDA_HIGH();
    SCL_HIGH();
    IIC_Delay();
    ack = READ_SDA();
    SCL_LOW();
    IIC_Delay();
    return ack;
}

void IIC_SendAck(void)
{
    SDA_LOW();
    SCL_HIGH();
    IIC_Delay();
    SCL_LOW();
    SDA_HIGH();
}

void IIC_SendNAck(void)
{
    SDA_HIGH();
    SCL_HIGH();
    IIC_Delay();
    SCL_LOW();
}

unsigned char IIC_SendByte(unsigned char dat)
{
    for (unsigned char i = 0; i < 8; i++)
    {
        (dat & 0x80) ? SDA_HIGH() : SDA_LOW();
        dat <<= 1;
        SCL_HIGH();
        IIC_Delay();
        SCL_LOW();
        IIC_Delay();
    }
    return IIC_WaitAck();
}

unsigned char IIC_RecvByte(void)
{
    unsigned char dat = 0;
    SDA_HIGH();

    /* STM32F4 必须在接收前切换 SDA 为输入模式（开漏输出无法正确读取引脚电平） */
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin = SDA_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    HAL_GPIO_Init(SDA_PORT, &GPIO_InitStruct);

    for (unsigned char i = 0; i < 8; i++)
    {
        dat <<= 1;
        SCL_HIGH();
        IIC_Delay();
        if (READ_SDA())
            dat |= 0x01;
        SCL_LOW();
        IIC_Delay();
    }

    /* 接收完毕后恢复 SDA 为开漏输出模式 */
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;
    HAL_GPIO_Init(SDA_PORT, &GPIO_InitStruct);

    return dat;
}

/* 应用层函数 */
unsigned char IIC_ReadBytes(unsigned char Salve_Address, unsigned char Reg_Address,
                            unsigned char *Result, unsigned char len)
{
    IIC_Start();
    if (IIC_SendByte(Salve_Address & 0xFE))
    { // 写模式
        IIC_Stop();
        return 0;
    }
    if (IIC_SendByte(Reg_Address))
    {
        IIC_Stop();
        return 0;
    }
    IIC_Start();
    if (IIC_SendByte(Salve_Address | 0x01))
    { // 读模式
        IIC_Stop();
        return 0;
    }

    for (unsigned char i = 0; i < len; i++)
    {
        Result[i] = IIC_RecvByte();
        (i == len - 1) ? IIC_SendNAck() : IIC_SendAck();
    }
    IIC_Stop();
    return 1;
}

unsigned char IIC_WriteByte(unsigned char Salve_Address, unsigned char Reg_Address,
                            unsigned char data)
{
    IIC_Start();
    if (IIC_SendByte(Salve_Address & 0xFE))
    { // 写模式
        IIC_Stop();
        return 0;
    }
    if (IIC_SendByte(Reg_Address))
    {
        IIC_Stop();
        return 0;
    }
    if (IIC_SendByte(data))
    {
        IIC_Stop();
        return 0;
    }
    IIC_Stop();
    return 1;
}

unsigned char IIC_WriteBytes(unsigned char Salve_Address, unsigned char Reg_Address,
                             unsigned char *data, unsigned char len)
{
    IIC_Start();
    if (IIC_SendByte(Salve_Address & 0xFE))
    {
        IIC_Stop();
        return 0;
    }
    if (IIC_SendByte(Reg_Address))
    {
        IIC_Stop();
        return 0;
    }

    for (unsigned char i = 0; i < len; i++)
    {
        if (IIC_SendByte(data[i]))
        {
            IIC_Stop();
            return 0;
        }
    }
    IIC_Stop();
    return 1;
}

unsigned char Ping(void)
{
    unsigned char dat;
    IIC_ReadBytes(Color_Adress << 1, PING, &dat, 1);
    if (dat == PING_OK)
    {
        return 0;
    }
    else
        return 1;
}

unsigned char IIC_Get_Error(void)
{
    unsigned char dat;
    IIC_ReadBytes(Color_Adress << 1, Error, &dat, 1);
    return dat;
}

unsigned char IIC_Get_RGB(unsigned char *Result, unsigned char len)
{
    if (IIC_ReadBytes(Color_Adress << 1, RGB_Reg, Result, len))
        return 1;
    else
        return 0;
}

unsigned char IIC_Get_HSL(unsigned char *Result, unsigned char len)
{
    if (IIC_ReadBytes(Color_Adress << 1, HSL_Reg, Result, len))
        return 1;
    else
        return 0;
}

void get_color(void)
{
    uint16_t h_sum = 0, s_sum = 0, l_sum = 0;
    uint8_t temp_hsl[3];
    for (int i = 0; i < 10; i++)
    {
        if (IIC_Get_HSL(temp_hsl, 3))
        {
            h_sum += temp_hsl[0];
            s_sum += temp_hsl[1];
            l_sum += temp_hsl[2];
        }
        HAL_Delay(10);
    }
    HSL[0] = h_sum / 10;
    HSL[1] = s_sum / 10;
    HSL[2] = l_sum / 10;

    /* 颜色识别：绿、蓝、黑 */
    if (HSL[0] > 100 && HSL[0] < 190) // 绿色
    {
        RC.green_flag = 1;
        RC.blue_flag = 0;
        RC.black_flag = 0;
    }
    else if (HSL[0] > 140 && HSL[0] < 180) // 蓝色
    {
        RC.green_flag = 0;
        RC.blue_flag = 1;
        RC.black_flag = 0;
    }
    else if ((HSL[0] > 180 && HSL[0] < 240) || HSL[0] == 0) // 黑色
    {
        RC.green_flag = 0;
        RC.blue_flag = 0;
        RC.black_flag = 1;
    }
    else
    {
        RC.green_flag = 0;
        RC.blue_flag = 0;
        RC.black_flag = 0;
    }
}