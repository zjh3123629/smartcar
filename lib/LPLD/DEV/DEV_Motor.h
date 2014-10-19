#ifndef __DEV_MOTOR_H__
#define __DEV_MOTOR_H__

#include "common.h"

#define MOTOR_PWM_HZ	20000
// 100M / 20KHz = 5000
#define MOTOR_PWM_MAX	(BUS_CLK_MHZ*50)
#define MOTOR_PWM_INIT	0

#define MOTOR_DEADZONE		0

enum {
	LEFT_MOTOR,
	RIGHT_MOTOR
};

typedef struct {
	int32 left_pwm;
	int32 right_pwm;
} Motor_InitTypeDef;

void init_motor();
void motor_update_pwm(int32 balance_control, int32 speed_control);

#endif
