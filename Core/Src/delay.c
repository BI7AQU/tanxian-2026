#include "delay.h"
void Delay_us(uint32_t udelay)
{
  uint32_t startval, tickn, delays, wait;

  startval = SysTick->VAL; // 获取当前SysTick计数值
  tickn = HAL_GetTick();   // 获取当前毫秒时间戳
  // sysc = 72000;  //SystemCoreClock / (1000U / uwTickFreq);
  delays = udelay * 168; // sysc / 1000 * udelay; // 计算需延时的时钟周期数（168MHz下）
  if (delays > startval) // 需等待时间超过当前ms周期剩余值
  {
    while (HAL_GetTick() == tickn) // 阻塞直到进入下一毫秒周期
    {
    }
    wait = 168000 + startval - delays; // 计算下一周期目标值
    while (wait < SysTick->VAL)        // 等待计数器递减至目标
    {
    }
  }
  else // 可在当前ms周期内完成
  {
    wait = startval - delays; // 计算目标计数值
    while (wait < SysTick->VAL && HAL_GetTick() == tickn)   
    {
    }
  }
}
void Delay_ms(uint32_t delay)
{
  Delay_us(delay * 1000);
}
