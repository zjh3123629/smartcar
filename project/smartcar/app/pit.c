#include "pit.h"

static PIT_InitTypeDef pit0_init_struct;

int32 g_left_pulse = 0;
int32 g_right_pulse = 0;

int32 g_pit0_counter = 0;

void pit0_isr(void)
{
	uint32 left_pulse, right_pulse=0;
	
	g_pit0_counter++;
	
	// 速度环
	/* calc pulse */
	right_pulse = LPLD_FTM_GetCounter(FTM2);	// refer to P1062: 一个脉冲会让CNT+4
	left_pulse = LPLD_LPTMR_GetPulseAcc();
	if (right_pulse > 60000) {
		// negative
		left_pulse = -left_pulse;
		
		right_pulse = (65536 - right_pulse) / 4;
		right_pulse = -right_pulse;
	} else {
		// positive
		right_pulse = right_pulse >> 2;
	}
	g_left_pulse += left_pulse;
	g_right_pulse += right_pulse;

	if (g_pit0_counter >= MOTOR_PID_CALC_PERIOD/PIT0_TIMER_PERIOD) {
		g_pit0_counter = 0;

#ifdef DEBUG_PRINT
	//@3|%d|%d|%d#
	//printf("%d, %d\n", g_left_pulse, g_right_pulse);
#endif
		motor_speed_adjust_calc();

		g_left_pulse = 0;
		g_right_pulse = 0;
	}

	motor_speed_smooth();



	// 角度环
	balance.gyro_h= balance.gyro_h_offset*2 - LPLD_ADC_Get(ADC1, DAD1);
	balance.accel_y= LPLD_ADC_Get(ADC1, AD20);
	balance_cal_ang(&balance, balance.accel_y, balance.gyro_h);
	balance_keep(&balance);
#ifdef DEBUG_PRINT
	//@3|%d|%d|%d#
	//printf("@3|%d|%d|%d#\n", (uint32)balance.accel_y, (uint32)balance.gyro_h, (uint32)balance.angle);
#endif

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
