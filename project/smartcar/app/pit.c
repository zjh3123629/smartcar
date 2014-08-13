#include "pit.h"

static PIT_InitTypeDef pit0_init_struct;

static uint16 left_pulse = 0;
static uint16 right_pulse = 0;

void pit0_isr(void)
{
	left_pulse = LPLD_LPTMR_GetPulseAcc();
	// refer to P1062: һ���������CNT+4
	right_pulse = LPLD_FTM_GetCounter(FTM2)>>2;

	printf("left_pulse=%d, right_pulse=%d\n", left_pulse, right_pulse);

	LPLD_LPTMR_ResetCounter();
	LPLD_FTM_ClearCounter(FTM2);
}

void init_pit0(void)
{
	bzero(&pit0_init_struct, sizeof(pit0_init_struct));
	
	pit0_init_struct.PIT_Pitx = PIT0;
	pit0_init_struct.PIT_PeriodMs= PIT0_TIMER_PERIOD;
	pit0_init_struct.PIT_Isr = pit0_isr;
	//��ʼ��PIT0
	LPLD_PIT_Init(pit0_init_struct);  
}

void pit0_enable_irq(void)
{
	LPLD_PIT_EnableIrq(pit0_init_struct);
}
