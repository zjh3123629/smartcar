#ifndef __DEV_ADC_H__
#define __DEV_ADC_H__

#include "common.h"
#include "DEV_oled.h"

typedef struct {
	int32 accel_x_offset;
	int32 accel_y_offset;

	int32 gyro_h_offset;
	int32 gyro_v_offset;
} adc_InitTypeDef;

enum {
	ACCEL_X = 0,
	ACCEL_Y = 1,
	GYRO_H = 2,
	GYRO_V = 3,
};

#define AVERAGE_CNT		1000
#define BALANCE_ANGLE 		2480

void init_adc(void);
float adc_get(int32 measure);

#endif
