#include "DEV_Balance.h"

balance_inittype_def balance;
pid_inittypedef balance_pid;

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
	//adc_init_struct.ADC_CalEnable = TRUE; 				//使能初始化校验
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

static void balance_get_gyro_offset(void)
{
#define AVERAGE_SUM	1000
	int i = 0;
	uint32 offset = 0;

	for (i=0; i<AVERAGE_SUM; ++i)
		offset += LPLD_ADC_Get(ADC1, DAD1);

	balance.gyro_h_offset = offset / AVERAGE_SUM;

	oled_print(0, 0, int_2_string(balance.gyro_h_offset), NORMAL_DISPLAY);
}

static void balance_get_offset(void)
{
	balance_get_gyro_offset();
}

void balance_init(void)
{
	//adc0_init();
	adc1_init();

	// ADC1_DM1 <==> Y
	LPLD_ADC_Chn_Enable(ADC1, AD20);
	// ADC1_DP1 <==> G_H
	LPLD_ADC_Chn_Enable(ADC1, DAD1);

	balance_get_offset();
}

uint16 balance_cal_ang(balance_inittype_def* balance_type, float accel, float gyro_h)
{	
	balance_type->angle = GYRO_FACTOR*(balance_type->angle + gyro_h * 0.005) + ACCEL_FACTOR*accel;

	return balance_type->angle;
}

void balance_keep(balance_inittype_def* balance_type)
{
	int32 nP, nD;
	int32 left_motor_pwm=0, right_motor_pwm=0;

	nP = (BALANCE_ANGLE - balance.angle) * ANGLE_KP;
	nD = (balance.gyro_h - balance.gyro_h_offset) * ANGLE_KD;

	right_motor_pwm = left_motor_pwm = nP - nD;

	if (left_motor_pwm >= 0)
		left_motor_pwm += MOTOR_DEADZONE;
	else if (left_motor_pwm < 0)
		left_motor_pwm -= MOTOR_DEADZONE;

	if (right_motor_pwm >= 0)
		right_motor_pwm += MOTOR_DEADZONE;
	else if (right_motor_pwm < 0)
		right_motor_pwm -= MOTOR_DEADZONE;

	//printf("motor_pwm=%d, kp=%d, kd=%d\n", motor_pwm, (int32)(balance_pid.kp), (int32)balance_pid.kd);
	motor_change_pwm(LEFT_MOTOR, left_motor_pwm);
	motor_change_pwm(RIGHT_MOTOR, right_motor_pwm);
}

