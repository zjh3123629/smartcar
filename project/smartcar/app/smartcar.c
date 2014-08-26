#include "common.h"
#include "pit.h"

#include "DEV_Motor.h"
#include "DEV_Encoder.h"
#include "DEV_PID.h"
#include "DEV_Balance.h"
#include "DEV_OLED.h"

void main(void)
{
	delay_ms(1000);

	init_pid(&left_motor_pid);
	init_pid(&right_motor_pid);
	//pid_set_parameters(&left_motor_pid, 60, 6, 0, 5);
	pid_set_parameters(&left_motor_pid, 0, 6, 0.1, 8);
	pid_set_parameters(&right_motor_pid, 0, 0, 0, 0);

	init_oled();
	
	balance_init();

	init_motor();

	init_encoder();
	
	init_pit0();
	pit0_enable_irq();

#if 0
	// init pid
	init_pid(&left_motor_pid);
	init_pid(&right_motor_pid);
	pid_set_parameters(&left_motor_pid, 100, 50, 4, 10);
	pid_set_parameters(&right_motor_pid, 100, 50, 4, 10);
#endif

	while (1) {

	}
}

