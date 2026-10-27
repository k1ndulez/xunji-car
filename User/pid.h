#ifndef __PID_H
#define __PID_H
#include <stdint.h>

typedef struct
{
    float kp;
    float ki;
    float kd;

    float out_min;
    float out_max;

    float iout_min;
    float iout_max;

    float set;//目标
    float fdb;//反馈

    float error[2];/* [0] 本次，[1] 上次 */
    float pout;
    float iout;
    float dout;
    float out;
    uint8_t ready;
} pid_t;

void  pid_init(pid_t *p, float kp, float ki, float kd, float out_min, float out_max);

void  pid_set_integral_limit(pid_t *p, float iout_min, float iout_max);

void  pid_reset(pid_t *p);

float pid_calc(pid_t *p, float target, float meas);

#endif