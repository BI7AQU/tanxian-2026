#include "RGB.h"
#include "tim.h"

/*Some Static Colors------------------------------*/
const RGB_Color_TypeDef RED = {255, 0, 0}; // 显示红色RGB数据
const RGB_Color_TypeDef ORANGE = {127, 106, 0};
const RGB_Color_TypeDef YELLOW = {255, 255, 0};
const RGB_Color_TypeDef GREEN = {0, 255, 0};
const RGB_Color_TypeDef CYAN = {0, 255, 255};
const RGB_Color_TypeDef BLUE = {0, 0, 255};
const RGB_Color_TypeDef PURPLE = {238, 130, 238};
const RGB_Color_TypeDef BLACK = {0, 0, 0};
const RGB_Color_TypeDef WHITE = {255, 255, 255};
const RGB_Color_TypeDef MAGENTA = {255, 0, 220};

/*二维数组存放最终PWM输出数组，每一行24个
数据代表一个LED，最后一行24个0代表RESET码*/
uint32_t Pixel_Buf[Pixel_NUM + 1][24];

/*
功能：设定单个RGB LED的颜色，把结构体中RGB的24BIT转换为0码和1码
参数：LedId为LED序号，Color：定义的颜色结构体
*/
void RGB_SetColor(uint8_t LedId, RGB_Color_TypeDef Color)
{
    uint8_t i;
    if (LedId > Pixel_NUM)
        return; // avoid overflow 防止写入ID大于LED总数

    for (i = 0; i < 8; i++)
        Pixel_Buf[LedId][i] = ((Color.G & (1 << (7 - i))) ? (CODE_1) : CODE_0); // 数组某一行0~7转化存放G
    for (i = 8; i < 16; i++)
        Pixel_Buf[LedId][i] = ((Color.R & (1 << (15 - i))) ? (CODE_1) : CODE_0); // 数组某一行8~15转化存放R
    for (i = 16; i < 24; i++)
        Pixel_Buf[LedId][i] = ((Color.B & (1 << (23 - i))) ? (CODE_1) : CODE_0); // 数组某一行16~23转化存放B
}

/*
功能：最后一行装在24个0，输出24个周期占空比为0的PWM波，作为最后reset延时，这里总时长为24*1.2=30us > 24us(要求大于24us)
*/
void Reset_Load(void)
{
    uint8_t i;
    for (i = 0; i < 24; i++)
    {
        Pixel_Buf[Pixel_NUM][i] = 0;
    }
}

/*
功能：发送数组
参数：(&htim1)定时器1，(TIM_CHANNEL_1)通道1，((uint32_t *)Pixel_Buf)待发送数组，
            (Pixel_NUM+1)*24)发送个数，数组行列相乘
*/
void RGB_SendArray(uint8_t i)
{
    if (i == 1)
        HAL_TIM_PWM_Start_DMA(&htim5, TIM_CHANNEL_1, (uint32_t *)Pixel_Buf, (Pixel_NUM + 1) * 24);
    else if (i == 0)
        HAL_TIM_PWM_Start_DMA(&htim5, TIM_CHANNEL_2, (uint32_t *)Pixel_Buf, (Pixel_NUM + 1) * 24);
}

/*
功能：显示红色
参数：Pixel_Len为显示LED个数
*/
void RGB_RED(uint16_t Pixel_Len, uint8_t x)
{
    uint16_t i;
    for (i = 0; i < Pixel_Len; i++) // 给对应个数LED写入红色
    {
        RGB_SetColor(i, RED);
    }
    Reset_Load();
    RGB_SendArray(x);
}

/*
功能：显示绿色
参数：Pixel_Len为显示LED个数
*/
void RGB_GREEN(uint16_t Pixel_Len, uint8_t x)
{
    uint16_t i;
    for (i = 0; i < Pixel_Len; i++) // 给对应个数LED写入绿色
    {
        RGB_SetColor(i, GREEN);
    }
    Reset_Load();
    RGB_SendArray(x);
}

/*
功能：显示蓝色
参数：Pixel_Len为显示LED个数
*/
void RGB_BLUE(uint16_t Pixel_Len, uint8_t x)
{
    uint16_t i;
    for (i = 0; i < Pixel_Len; i++) // 给对应个数LED写入蓝色
    {
        RGB_SetColor(i, BLUE);
    }
    Reset_Load();
    RGB_SendArray(x);
}

/*
功能：显示白色
参数：Pixel_Len为显示LED个数
*/
void RGB_WHITE(uint16_t Pixel_Len, uint8_t x)
{
    uint16_t i;
    for (i = 0; i < Pixel_Len; i++) // 给对应个数LED写入白色
    {
        RGB_SetColor(i, WHITE);
    }
    Reset_Load();
    RGB_SendArray(x);
}

void RGB_YELLOW(uint16_t Pixel_Len, uint8_t x)
{
    uint16_t i;
    for (i = 0; i < Pixel_Len; i++) // 给对应个数LED写入黄色
    {
        RGB_SetColor(i, YELLOW);
    }
    Reset_Load();
    RGB_SendArray(x);
}

// 也可以继续添加其他颜色，和颜色变化函数等
// 显示指定颜色
static void rgb_show(uint32_t Pixel_Len, RGB_Color_TypeDef rgb, uint8_t x)
{
    uint16_t i;
    for (i = 0; i < Pixel_Len; i++)
    {
        RGB_SetColor(i, rgb);
    }
    Reset_Load();
    RGB_SendArray(x);
}

// 颜色循环转换
static RGB_Color_TypeDef Wheel(uint8_t WheelPos)
{
    RGB_Color_TypeDef rgb;
    WheelPos = 255 - WheelPos;
    if (WheelPos < 85)
    {
        rgb.R = 255 - WheelPos * 3;
        rgb.G = 0;
        rgb.B = WheelPos * 3;
        return rgb;
    }
    if (WheelPos < 170)
    {
        WheelPos -= 85;
        rgb.R = 0;
        rgb.G = WheelPos * 3;
        rgb.B = 255 - WheelPos * 3;
        return rgb;
    }
    WheelPos -= 170;
    rgb.R = WheelPos * 3;
    rgb.G = 255 - WheelPos * 3;
    rgb.B = 0;
    return rgb;
}

// 彩虹呼吸灯
static void rainbow(uint8_t wait)
{
    uint32_t timestamp = HAL_GetTick();
    uint16_t i;
    static uint8_t j;
    static uint32_t next_time = 0;

    uint32_t flag = 0;
    if (next_time < wait)
    {
        if ((uint64_t)timestamp + wait - next_time > 0)
            flag = 1;
    }
    else if (timestamp > next_time)
    {
        flag = 1;
    }
    if (flag) // && (timestamp - next_time < wait*5))
    {
        j++;
        next_time = timestamp + wait;
        for (i = 0; i < Pixel_NUM; i++)
        {
            RGB_SetColor(i, Wheel((i + j) & 255));
        }
    }
    RGB_SendArray(0);
}

// 彩虹灯旋转
static void rainbowCycle(uint8_t wait)
{
    uint32_t timestamp = HAL_GetTick();
    uint16_t i;
    static uint8_t j;
    static uint32_t next_time = 0;

    static uint8_t loop = 0;
    if (loop == 0)
        next_time = timestamp;
    loop = 1; // 首次调用初始化

    if ((timestamp > next_time)) // && (timestamp - next_time < wait*5))
    {
        j++;
        next_time = timestamp + wait;
        for (i = 0; i < Pixel_NUM; i++)
        {
            RGB_SetColor(i, Wheel(((i * 256 / (Pixel_NUM)) + j) & 255));
        }
    }
    RGB_SendArray(0);
}

void rgb_off(uint8_t i, uint8_t x)
{
    rgb_show(i, BLACK, x);
}

static uint8_t rainbow_change_flag = 0;
void led_loop(uint8_t x)
{
    int i;
    // rgb_off(7);
    // HAL_Delay(300);
    for (i = 1; i <= 4; i++)
    { // 红
        rgb_show(i, RED, x);
        HAL_Delay(50);
    }
    for (i = 1; i <= 4; i++)
    { // 橙
        rgb_show(i, ORANGE, x);
        HAL_Delay(50);
    }
    // for (i = 1; i <= 4; i++)
    // { // 黄
    //     rgb_show(i, YELLOW);
    //     HAL_Delay(50);
    // }
    // for (i = 1; i <= 4; i++)
    // { // 绿
    //     rgb_show(i, GREEN);
    //     HAL_Delay(50);
    // }
    // for (i = 1; i <= 4; i++)
    // { // 青
    //     rgb_show(i, CYAN);
    //     HAL_Delay(50);
    // }
    // for (i = 1; i <= 4; i++)
    // { // 蓝
    //     rgb_show(i, BLUE);
    //     HAL_Delay(50);
    // }
    // for (i = 1; i <= 4; i++)
    // { // 紫
    //     rgb_show(i, PURPLE);
    //     HAL_Delay(50);
    // }
}

void RGB_Clear(uint8_t x)
{
    for (uint8_t i = 0; i < Pixel_NUM; i++)
    {
        rgb_show(i, BLACK, x);
    }
}

// 黄色流水灯控制结构体
typedef struct
{
    uint8_t position;     // 当前操作位置
    uint8_t state;        // 0:亮灯阶段, 1:灭灯阶段
    uint8_t is_active;    // 是否激活
    uint32_t last_update; // 上次更新时间（非阻塞模式下使用）
} FlowLight_Control;

FlowLight_Control yellow_flow = {0, 0, 1, 0}; // 默认激活状态

/*
 * 非阻塞式黄色流水灯（完美修正版）
 */
void FlowLight_Yellow(uint8_t x)
{
    const uint8_t DELAY_MS = 30; // 流水速度（毫秒）

    // 时间检查
    if (HAL_GetTick() - yellow_flow.last_update < DELAY_MS)
    {
        return; // 未到更新时间
    }
    yellow_flow.last_update = HAL_GetTick();

    // 根据当前状态设置灯光
    if (yellow_flow.state == 0)
    {
        RGB_SetColor(yellow_flow.position, YELLOW);

        yellow_flow.position++;

        if (yellow_flow.position >= 9)
        {
            yellow_flow.state = 1;
            yellow_flow.position = 8;
        }
    }
    else
    {
        // 关键修正：只熄灭当前灯
        RGB_SetColor(yellow_flow.position, BLACK);

        if (yellow_flow.position > 0)
        {
            yellow_flow.position--;
        }
        else
        {
            yellow_flow.state = 0;
            yellow_flow.position = 0;
            RGB_Clear(x); // 准备新循环
        }
    }
    // 发送数据到LED
    Reset_Load();
    RGB_SendArray(x);
}

/**
 * @brief  启停控制
 */
void Toggle_FlowLight(uint8_t state,uint8_t x)
{
    yellow_flow.is_active = (state) ? 1 : 0;
    yellow_flow.position = 0;
    yellow_flow.state = 0;
    if (!state)
    {
        RGB_Clear(x);
        Reset_Load();
        RGB_SendArray(x);
    }
}