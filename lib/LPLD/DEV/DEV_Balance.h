#ifndef __DEV_BALANCE__
#define __DEV_BALANCE__

#include "common.h"
#include "DEV_ADC.h"

typedef struct 
{
	float accel_y;
	float gyro_h;
	float angle;

	float gyro_v_interal;

	int32 pwm;
} Balance_InitTypeDef;

#if 0
#define GYRO_FACTOR		0.9
#define ACCEL_FACTOR	(1-GYRO_FACTOR)
#else
#define BALANCE_ACCE_RATIO 	12.0
#define BALANCE_GYRO_RATIO		20.0
#endif

#if 0
#define ANGLE_KP	0
#define ANGLE_KD	0
#else
#define ANGLE_KP	35.0
#define ANGLE_KD	7.0
#endif

void balance_calc_ang(void);
void balance_keep(void);
int32 balance_get_control_value(void);

#endif