#ifndef __PIT_H__
#define __PIT_H__

#include "common.h"
#include "encoder.h"

#define PIT0_TIMER_PERIOD	10	// 10ms

void init_pit0();
void pit0_enable_irq(void);

#endif