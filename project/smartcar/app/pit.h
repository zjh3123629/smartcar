#ifndef __PIT_H__
#define __PIT_H__

#include "common.h"
#include "DEV_Encoder.h"
#include "DEV_PID.h"
#include "DEV_Motor.h"
#include "DEV_Balance.h"

#define PIT0_TIMER_PERIOD	5	// 10ms

extern int32 left_pulse;
extern int32 right_pulse;

void init_pit0();
void pit0_enable_irq(void);

#endif