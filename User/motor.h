#ifndef __MOTOR_H
#define __MOTOR_H

#include<stdint.h>

#define MOTOR_DUTY_MAX 7200

void motor_init(void);
void motor_set(int16_t duty_l,int16_t duty_r);
void motor_stop(void);
#endif    
