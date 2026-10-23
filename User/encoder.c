#include "encoder.h"
#include "tim.h"

#define ENCODER_CPR  1320.0f //编码器一转的脉冲数

static int16_t last_count = 0;
static uint32_t last_tick = 0;
float rpm_now = 0.0f;

void encoder_init(void)
{
    HAL_TIM_Encoder_Start(&htim1, TIM_CHANNEL_ALL);
    last_count = __HAL_TIM_GET_COUNTER(&htim1);//读取当前脉冲数记为起点脉冲
    last_tick = HAL_GetTick();//读取当时时间为起点时间
}

float encoder_rpm(void)
{
    int16_t  now_count = (int16_t)__HAL_TIM_GET_COUNTER(&htim1);
    int16_t  delta   = now_count - last_count;
    uint32_t now_tick = HAL_GetTick();
    uint32_t delta_tick = now_tick - last_tick;
    
    if(delta_tick > 0)
    {
     float counts_pre_second = (float)delta / ((float)delta_tick / 1000.0f);//计算每秒的脉冲数
     rpm_now = counts_pre_second / ENCODER_CPR * 60.0f;//计算每分钟转速
    }
    last_tick  = now_tick;
    last_count = now_count;
    return rpm_now;
}