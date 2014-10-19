#ifndef __DEV_BALANCE__
#define __DEV_BALANCE__

#include "common.h"
#include "DEV_OLED.h"

typedef struct 
{
	float accel_y;
	float gyro_h;
	float angle;

	int32 gyro_h_offset;
	int32 accel_y_offset;

	int32 pwm;
} Balance_InitTypeDef;

#define AVERAGE_CNT	1000

#define BALANCE_ANGLE 	2465

#if 0
#define GYRO_FACTOR		0.9
#define ACCEL_FACTOR	(1-GYRO_FACTOR)
#else
#define GYRO_RATIO		20.0
#define ACCE_RATIO 	12.0
#endif

#if 0
#define ANGLE_KP	0
#define ANGLE_KD	0
#else
#define ANGLE_KP	35.0
#define ANGLE_KD	7.0
#endif

void init_balance(void);
void balance_calc_ang(void);
void balance_keep(void);

int32 balance_get_control_value(void);

#endif