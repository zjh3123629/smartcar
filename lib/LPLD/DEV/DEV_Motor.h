#ifndef __DEV_MOTOR_H__
#define __DEV_MOTOR_H__

#include "common.h"

#define MOTOR_PWM_HZ	20000
// 100M / 20KHz = 5000
#define MOTOR_PWM_MAX	(BUS_CLK_MHZ*50)
#define MOTOR_PWM_INIT	0

#define MOTOR_DEADZONE 100

enum {
	LEFT_MOTOR,
	RIGHT_MOTOR
};

void init_motor();
void motor_change_pwm(uint8 left_right, int32 duty);

#endif
