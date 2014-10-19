#include "DEV_Speed.h"

static Speed_InitTypeDef speed_control = {0};

void init_speed(float point, float kp, float ki)
{
	bzero(&speed_control, sizeof(speed_control));
	
	speed_control.point = point;
	speed_control.kp= kp;
	speed_control.ki = ki;
}

void speed_get_pulse(void)
{
	int32 left_pulse=0, right_pulse=0;

	/* calc pulse */
	left_pulse = LPLD_LPTMR_GetPulseAcc();
	right_pulse = LPLD_FTM_GetCounter(FTM2);	// refer to P1062: 一个脉冲会让CNT+4

	if (right_pulse > 60000) {
		right_pulse = 65536 - right_pulse;
	} else {
		left_pulse = -left_pulse;
		right_pulse = -right_pulse;
	}
/*
	if (right_pulse > 60000) {
		// negative
		left_pulse = -left_pulse;
		
		right_pulse = (65536 - right_pulse) / 4.0;
		right_pulse = -right_pulse;
	} else {
		// positive
		right_pulse = right_pulse / 4.0;
	}
*/

	speed_control.left_pulse += left_pulse;
	speed_control.right_pulse += right_pulse;

	LPLD_LPTMR_ResetCounter();
	LPLD_FTM_ClearCounter(FTM2);
}

void speed_output_smoothly(int32 step)
{
	int32 nValue = 0;
	
	nValue = speed_control.new_pwm - speed_control.old_pwm;
	nValue = nValue * (step - 1) / (SPEED_PID_CALC_PERIOD/PIT0_TIMER_PERIOD - 1) + speed_control.old_pwm;
	speed_control.current_pwm = nValue;
}

void speed_pid_calc(void)
{
	float speed=0, P=0;

	// record motor_speed_old 
	speed_control.old_pwm = speed_control.new_pwm;

	// calc speed error
	speed = ((float)(speed_control.left_pulse + speed_control.right_pulse)) / 2.0;
	speed = speed_control.point - speed;
	//车轮速度滤波
	speed_control.speed_filter *= 0.85;
	speed_control.speed_filter += speed * 0.15;

	// PI control
	P = speed_control.speed_filter * speed_control.kp;
	speed_control.integral -= speed_control.speed_filter * speed_control.ki;
#define SPEED_CONTROL_INTEGRAL_MAX	1000
	if (speed_control.integral > SPEED_CONTROL_INTEGRAL_MAX)
		speed_control.integral = SPEED_CONTROL_INTEGRAL_MAX;
	else if (speed_control.integral < -SPEED_CONTROL_INTEGRAL_MAX)
		speed_control.integral = -SPEED_CONTROL_INTEGRAL_MAX;
	
	speed_control.new_pwm = (int32)(speed_control.integral - P);
	
	//printf("%d, %d, %d\n", (int32)speed, (int32)speed_control.integral, speed_control.speed_new_pwm);

	// clear pulse
#ifdef DEBUG_PRINT
	//@3|%d|%d|%d#
	//printf("%d, %d\n", speed_control.left_pulse, speed_control.right_pulse);
#endif
	speed_control.left_pulse = 0;
	speed_control.right_pulse = 0;
}

int32 speed_get_control_value(void)
{
	return speed_control.current_pwm;
}

