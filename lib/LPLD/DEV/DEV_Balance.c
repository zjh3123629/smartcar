#include "DEV_Balance.h"

static Balance_InitTypeDef balance_control;

static void adc0_init(void)
{
	ADC_InitTypeDef adc_init_struct;
	bzero(&adc_init_struct, sizeof(adc_init_struct));

	//配置ADC采样参数
	adc_init_struct.ADC_Adcx = ADC0;
	adc_init_struct.ADC_DiffMode = ADC_SE;        		//单端采集
	adc_init_struct.ADC_BitMode = SE_12BIT;       		//单端12位精度
	adc_init_struct.ADC_SampleTimeCfg = SAMTIME_SHORT;	//短采样时间
	adc_init_struct.ADC_HwAvgSel = HW_4AVG;       		//4次硬件平均
	//adc_init_struct.ADC_CalEnable = TRUE; 			//使能初始化校验
	//初始化ADC
	LPLD_ADC_Init(adc_init_struct);
}

static void adc1_init(void)
{
	ADC_InitTypeDef adc_init_struct;
	bzero(&adc_init_struct, sizeof(adc_init_struct));

	//配置ADC采样参数
	adc_init_struct.ADC_Adcx = ADC1;
	adc_init_struct.ADC_DiffMode = ADC_SE;        		//单端采集
	adc_init_struct.ADC_BitMode = SE_12BIT;       		//单端12位精度
	adc_init_struct.ADC_SampleTimeCfg = SAMTIME_SHORT;	//短采样时间
	adc_init_struct.ADC_HwAvgSel = HW_8AVG;       		//4次硬件平均
	//adc_init_struct.ADC_CalEnable = TRUE; 				//使能初始化校验
	//初始化ADC
	LPLD_ADC_Init(adc_init_struct);
}

static void balance_get_gyro_offset(void)
{
	int i = 0;
	uint32 offset = 0;

	for (i=0; i<AVERAGE_CNT; ++i)
		offset += LPLD_ADC_Get(ADC1, DAD1);

	balance_control.gyro_h_offset = offset / AVERAGE_CNT;

	oled_print(0, 0, int_2_string(balance_control.gyro_h_offset), NORMAL_DISPLAY);
}

static void balance_get_offset(void)
{
	balance_get_gyro_offset();
	balance_control.accel_y_offset = BALANCE_ANGLE;
}

void init_balance(void)
{
	//adc0_init();
	adc1_init();

	// ADC1_DM1 <==> Y
	LPLD_ADC_Chn_Enable(ADC1, AD20);
	// ADC1_DP1 <==> G_H
	LPLD_ADC_Chn_Enable(ADC1, DAD1);

	balance_get_offset();
}

void balance_calc_ang(void)
{
	balance_control.accel_y = (float)(balance_control.accel_y_offset - LPLD_ADC_Get(ADC1, AD20));
	balance_control.gyro_h = (float)(LPLD_ADC_Get(ADC1, DAD1) - balance_control.gyro_h_offset);

#if 0
	balance_type->angle = GYRO_FACTOR*(balance_type->angle + gyro_h * 0.001) + ACCEL_FACTOR*accel;
#else
	// 清华方案
	static float angle_sigma = 0;
	float delta_value = 0;
	float gyro_h = 0;

	gyro_h = balance_control.gyro_h * GYRO_RATIO;
	
	balance_control.angle = angle_sigma / 1024.0;
	delta_value = balance_control.accel_y - balance_control.angle;
	delta_value *= ACCE_RATIO;
	
	angle_sigma += (gyro_h + delta_value);
#endif

#ifdef DEBUG_PRINT
	//@3|%d|%d|%d#
	//printf("@3|%d|%d|%d#\n", (int32)balance.accel_y, (int32)balance.gyro_h, (int32)balance.angle);
#endif
}

void balance_keep(void)
{
	float nP=0, nD=0;

	// angle control
	nP = balance_control.angle * ANGLE_KP;
	nD = balance_control.gyro_h * ANGLE_KD;
	balance_control.pwm = (int32)(nD + nP);

	//printf("%d, %d, %d\n", (int32)(nP), (int32)nD, balance_control.balance_pwm);
}

int32 balance_get_control_value(void)
{
	return balance_control.pwm;
}

