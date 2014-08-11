#ifndef __MOTOR_H__
#define __MOTOR_H__

#include "common.h"

#define MOTOR_PWM_HZ	20000
// 100M / 20KHz = 5000
#define MOTOR_PWM_MAX	(BUS_CLK_MHZ*1000000/MOTOR_PWM_HZ)
#define MOTOR_PWM_INIT	(MOTOR_PWM_MAX/5)

void init_motor();

#endif
