#include "DEV_Speed.h"

static Speed_InitTypeDef speed = {0};

void init_speed(float point, float kp, float ki)
{
	bzero(&speed, sizeof(speed));
	
	speed.point = point;
	speed.kp = kp;
	speed.ki = ki;
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

	speed.left_pulse += left_pulse;
	speed.right_pulse += right_pulse;

	LPLD_LPTMR_ResetCounter();
	LPLD_FTM_ClearCounter(FTM2);
}

void speed_output_smoothly(int32 step)
{
	int32 nValue = 0;
	
	nValue = speed.new_pwm - speed.old_pwm;
	nValue = nValue * (step - 1) / (SPEED_PID_CALC_PERIOD/PIT0_TIMER_PERIOD - 1) + speed.old_pwm;
	speed.current_pwm = nValue;
}

void speed_pid_calc(void)
{
	float ek=0, P=0;

	// record motor_speed_old 
	speed.old_pwm = speed.new_pwm;

	// calc speed error
	ek = ((float)(speed.left_pulse + speed.right_pulse)) / 2.0;
	ek = speed.point - ek;
	//车轮速度滤波
	speed.speed_filter *= 0.85;
	speed.speed_filter += ek * 0.15;

	// PI control
	P = speed.speed_filter * speed.kp;
	speed.integral -= speed.speed_filter * speed.ki;
	if (speed.integral > SPEED_INTEGRAL_MAX)
		speed.integral = SPEED_INTEGRAL_MAX;
	else if (speed.integral < -SPEED_INTEGRAL_MAX)
		speed.integral = -SPEED_INTEGRAL_MAX;
	
	speed.new_pwm = (int32)(speed.integral - P);
	
	//printf("%d, %d, %d\n", (int32)speed, (int32)speed.integral, speed.speed_new_pwm);

	// clear pulse
#ifdef DEBUG_PRINT
	//@3|%d|%d|%d#
	//printf("%d, %d\n", speed.left_pulse, speed.right_pulse);
#endif
	speed.left_pulse = 0;
	speed.right_pulse = 0;
}

int32 speed_get_control_value(void)
{
	return speed.current_pwm;
}

