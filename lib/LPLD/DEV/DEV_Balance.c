#include "DEV_Balance.h"

static Balance_InitTypeDef balance = {0};

void balance_calc_ang(void)
{
	balance.accel_y = adc_get(ACCEL_Y);
	balance.gyro_h = adc_get(GYRO_H);

#if 0
	balance_type->angle = GYRO_FACTOR*(balance_type->angle + gyro_h * 0.001) + ACCEL_FACTOR*accel;
#else
	// 清华方案
	static float angle_sigma = 0;
	float delta_value = 0;
	float gyro_h = 0;

	gyro_h = balance.gyro_h * BALANCE_GYRO_RATIO;

	balance.angle = angle_sigma / 1024.0;
	delta_value = balance.accel_y - balance.angle;
	delta_value *= BALANCE_ACCE_RATIO;
	
	angle_sigma += (gyro_h + delta_value);
#endif

#ifdef DEBUG_PRINT
	//@3|%d|%d|%d#
	//printf("@3|%d|%d|%d#\n", (int32)balance.accel_y, (int32)balance.gyro_h, (int32)balance.angle);
#endif
}

void balance_keep(void)
{
	float nP=0, nD=0;

	// angle control
	nP = balance.angle * ANGLE_KP;
	nD = balance.gyro_h * ANGLE_KD;
	balance.pwm = (int32)(nD + nP);

	//printf("%d, %d, %d\n", (int32)(nP), (int32)nD, balance.balance_pwm);
}

int32 balance_get_control_value(void)
{
	return balance.pwm;
}

