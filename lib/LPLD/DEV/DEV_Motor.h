#ifndef __DEV_MOTOR_H__
#define __DEV_MOTOR_H__

#include "common.h"
#include "pit.h"

#define MOTOR_PWM_HZ	20000
// 100M / 20KHz = 5000
#define MOTOR_PWM_MAX	(BUS_CLK_MHZ*50)
#define MOTOR_PWM_INIT	0

#define MOTOR_DEADZONE 0

#define MOTOR_PID_CALC_PERIOD	50	//ms

#define MOTOR_INIT_SPEED 	0
#define MOTOR_SPEED_KP		10.0
#define MOTOR_SPEED_KI		5.0

enum {
	LEFT_MOTOR,
	RIGHT_MOTOR
};

extern int32 g_left_motor_pwm, g_right_motor_pwm;

void init_motor();
void motor_change_pwm(uint8 left_right, int32 duty);
void motor_speed_smooth(void);
void motor_speed_adjust_calc(void);

#endif
