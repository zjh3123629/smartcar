#include "DEV_ADC.h"

static adc_InitTypeDef adc = {0};

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
	adc_init_struct.ADC_HwAvgSel = HW_4AVG;       		//4次硬件平均
	//adc_init_struct.ADC_CalEnable = TRUE; 				//使能初始化校验
	//初始化ADC
	LPLD_ADC_Init(adc_init_struct);
}

static void adc_get_offset(void)
{
	int i = 0;
	uint32 offset = 0;
	
	// get G_H
	offset = 0;
	for (i=0; i<AVERAGE_CNT; ++i)
		offset += LPLD_ADC_Get(ADC1, DAD1);
	adc.gyro_h_offset = offset / AVERAGE_CNT;
	oled_print(0, 0, int_2_string(adc.gyro_h_offset), NORMAL_DISPLAY);

	// get G_V
	offset = 0;
	for (i=0; i<AVERAGE_CNT; ++i)
		offset += LPLD_ADC_Get(ADC1, DAD3);
	adc.gyro_v_offset = offset / AVERAGE_CNT;
	oled_print(0, 2, int_2_string(adc.gyro_v_offset), NORMAL_DISPLAY);

	// accel_y
	adc.accel_y_offset = BALANCE_ANGLE;
}

void init_adc(void)
{
	//adc0_init();
	adc1_init();

	// ADC1_DM1 <==> Y
	LPLD_ADC_Chn_Enable(ADC1, AD20);
	// ADC1_DP1 <==> G_H
	LPLD_ADC_Chn_Enable(ADC1, DAD1);
	// ADC1_DP3 <==> G_V
	LPLD_ADC_Chn_Enable(ADC1, DAD3);

	adc_get_offset();
}

float adc_get(int32 measure)
{
	if (ACCEL_X == measure)
		return (float)(adc.accel_x_offset - LPLD_ADC_Get(ADC0, AD20));
	else if (ACCEL_Y == measure)
		return (float)(adc.accel_y_offset - LPLD_ADC_Get(ADC1, AD20));
	else if (GYRO_H == measure)
		return (float)(LPLD_ADC_Get(ADC1, DAD1) - adc.gyro_h_offset);
	else if (GYRO_V == measure)
		return (float)(LPLD_ADC_Get(ADC1, DAD3) - adc.gyro_v_offset);
	else
		return 0;
}

