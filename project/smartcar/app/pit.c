#include "pit.h"

static PIT_InitTypeDef pit0_init_struct;

int32 left_pulse = 0;
int32 right_pulse = 0;

void pit0_isr(void)
{
	left_pulse = LPLD_LPTMR_GetPulseAcc();
	// refer to P1062: 一个脉冲会让CNT+4
	right_pulse = LPLD_FTM_GetCounter(FTM2);

	if (right_pulse > 60000) {
		// negative
		left_pulse = -left_pulse;
		
		right_pulse = (65535 - right_pulse) >> 2;
		right_pulse = -right_pulse;
	} else {
		// positive
		right_pulse = right_pulse >> 2;
	}

	//motor_change_pwm(LEFT_MOTOR, pid_position(&left_motor_pid, left_pulse));
	//motor_change_pwm(RIGHT_MOTOR, pid_position(&right_motor_pid, right_pulse));

#ifdef DEBUG_PRINT
	//@3|%d|%d|%d#
	printf("%d, %d\n", left_pulse, right_pulse);
#endif

	balance.gyro_h= balance.gyro_h_offset*2 - LPLD_ADC_Get(ADC1, DAD1);
	balance.accel_y= LPLD_ADC_Get(ADC1, AD20);
	balance_cal_ang(&balance, balance.accel_y, balance.gyro_h);

#ifdef DEBUG_PRINT
	//@3|%d|%d|%d#
	printf("@3|%d|%d|%d#\n", (uint32)balance.accel_y, (uint32)balance.gyro_h, (uint32)balance.angle);
#endif
	balance_keep(&balance);

	LPLD_LPTMR_ResetCounter();
	LPLD_FTM_ClearCounter(FTM2);
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
