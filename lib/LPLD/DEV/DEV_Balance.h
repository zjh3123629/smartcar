#ifndef __DEV_BALANCE__
#define __DEV_BALANCE__

#include "common.h"
#include "DEV_PID.h"
#include "DEV_Motor.h"
#include "DEV_OLED.h"
#include "pit.h"

typedef struct 
{
	float accel_y;
	float gyro_h;
	float angle;

	uint32 gyro_h_offset;

} balance_inittype_def ;

extern balance_inittype_def balance;

#define BALANCE_ANGLE 	2630
#define BALANCE_GYRO	2779

#define GYRO_FACTOR	0.9
#define ACCEL_FACTOR	(1-GYRO_FACTOR)

enum {
	ANGLE_KP = 12,
	ANGLE_KD = 8,
};

void balance_init(void);
uint16 balance_cal_ang(balance_inittype_def* balance_type, float accel, float gyro_h);
void balance_keep(balance_inittype_def* balance_type);

#endif