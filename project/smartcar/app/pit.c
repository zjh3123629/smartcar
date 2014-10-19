#include "pit.h"

static PIT_InitTypeDef pit0_init_struct;

void pit0_isr(void)
{
	static int32 pit0_counter = 0;

	pit0_counter++;

	// 角度环
	// 将gyro_h和accel归一化为+-
	balance_calc_ang();
	balance_keep();

	// 速度环
	speed_get_pulse();
	speed_output_smoothly(pit0_counter);
	if (pit0_counter >= SPEED_PID_CALC_PERIOD/PIT0_TIMER_PERIOD) {
		pit0_counter = 0;

		speed_pid_calc();
	}

	// finally output
	motor_update_pwm(balance_get_control_value(), speed_get_control_value());

	//LPLD_GPIO_Toggle_b(PTB, 23);
}

void init_pit0(void)
{
	bzero(&pit0_init_struct, sizeof(pit0_init_struct));
	
	pit0_init_struct.PIT_Pitx = PIT0;
	pit0_init_struct.PIT_PeriodMs= PIT0_TIMER_PERIOD;
	pit0_init_struct.PIT_Isr = pit0_isr;
	//初始化PIT0
	LPLD_PIT_Init(pit0_init_struct);  
}

void pit0_enable_irq(void)
{
	LPLD_PIT_EnableIrq(pit0_init_struct);
}
