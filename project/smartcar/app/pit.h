#ifndef __PIT_H__
#define __PIT_H__

#include "common.h"
#include "DEV_Encoder.h"
#include "DEV_PID.h"
#include "DEV_Motor.h"
#include "DEV_Balance.h"

#define PIT0_TIMER_PERIOD	5	// 10ms

extern int32 g_left_pulse;
extern int32 g_right_pulse;

extern int32 g_pit0_counter;

void init_pit0();
void pit0_enable_irq(void);

#endif