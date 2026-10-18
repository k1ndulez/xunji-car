#include "motor.h"
#include "main.h"
#include "tim.h"
#include "gpio.h"

/*left_motor： AIN1=PB12,AIN2=PB13,PWM=TIM3_CH1(PA6)*/
/*right_motor：BIN1=PB14,BIN2=PB15,PWM=TIM3_CH2(PA7)*/

#define L_IN1_PORT GPIOB
#define L_IN1_PIN  GPIO_PIN_12
#define L_IN2_PORT GPIOB
#define L_IN2_PIN  GPIO_PIN_13
#define L_PWM      TIM_CHANNEL_1

#define R_IN1_PORT GPIOB
#define R_IN1_PIN  GPIO_PIN_14
#define R_IN2_PORT GPIOB
#define R_IN2_PIN  GPIO_PIN_15
#define R_PWM      TIM_CHANNEL_2

/*limit duty*/
int16_t limit(int16_t d)
{
    if(d> MOTOR_DUTY_MAX) return MOTOR_DUTY_MAX;
    if(d< -MOTOR_DUTY_MAX) return -MOTOR_DUTY_MAX;
	return d;
}

/*duty> 0,forward; duty< 0,back*/
void motor_drive(GPIO_TypeDef *p1,uint16_t pin1,GPIO_TypeDef *p2,uint16_t pin2,uint32_t channel, int16_t duty)
{
    if(duty>0)
    {
        HAL_GPIO_WritePin(p1,pin1,GPIO_PIN_SET);
        HAL_GPIO_WritePin(p2,pin2,GPIO_PIN_RESET);
        __HAL_TIM_SET_COMPARE(&htim3, channel,limit(duty));
    }else if(duty<0)
    {
        HAL_GPIO_WritePin(p1,pin1,GPIO_PIN_RESET);
        HAL_GPIO_WritePin(p2,pin2,GPIO_PIN_SET);
        __HAL_TIM_SET_COMPARE(&htim3, channel,limit(-duty));
    }else
    {
        HAL_GPIO_WritePin(p1,pin1,GPIO_PIN_RESET);
        HAL_GPIO_WritePin(p2,pin2,GPIO_PIN_RESET);
        __HAL_TIM_SET_COMPARE(&htim3, channel,0);
    }

}

void motor_stop(void)
{
    motor_drive(L_IN1_PORT,L_IN1_PIN,L_IN2_PORT,L_IN2_PIN,L_PWM,0);
    motor_drive(R_IN1_PORT,R_IN1_PIN,R_IN2_PORT,R_IN2_PIN,R_PWM,0);
}

void motor_init(void)
{
    HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);
    HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_2);
    motor_stop();
}

void motor_set(int16_t duty_l,int16_t duty_r)
{
    motor_drive(L_IN1_PORT,L_IN1_PIN,L_IN2_PORT,L_IN2_PIN,L_PWM,duty_l);
    motor_drive(R_IN1_PORT,R_IN1_PIN,R_IN2_PORT,R_IN2_PIN,R_PWM,duty_r);
}
