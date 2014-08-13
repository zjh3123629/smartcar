#include "common.h"

#include "motor.h"
#include "pit.h"
#include "encoder.h"

void main(void)
{
	init_motor();

	init_encoder();
	
	init_pit0();
	pit0_enable_irq();

	while (1) {

	}
}

