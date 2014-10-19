#ifndef __DEV_SPEED_H__
#define __DEV_SPEED_H__

#include "common.h"
#include "pit.h"

typedef struct {
	int32 left_pulse;
	int32 right_pulse;

	float kp;
	float ki;
	float integral;
	
	float point;
	float speed_filter;

	// uesd for control motor smoothly
	int32 old_pwm;
	int32 new_pwm;
	int32 current_pwm;
} Speed_InitTypeDef;

#define SPEED_PID_CALC_PERIOD	20	//ms

void init_speed(float point, float kp, float ki);
void speed_get_pulse(void);
void speed_output_smoothly(int32 step);
void speed_pid_calc(void);

int32 speed_get_control_value(void);

#endif