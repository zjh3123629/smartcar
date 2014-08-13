#include "motor.h"

static void init_FTM0(void)
{
	FTM_InitTypeDef ftm_init_struct;
	bzero(&ftm_init_struct, sizeof(ftm_init_struct));

	ftm_init_struct.FTM_Ftmx = FTM0;			//使能FTM0通道
	ftm_init_struct.FTM_Mode = FTM_MODE_PWM;	//使能PWM模式
	ftm_init_struct.FTM_PwmFreq = MOTOR_PWM_HZ;	//PWM频率20KHz

	LPLD_FTM_Init(ftm_init_struct);
}

static void init_left_motor(void)
{
	/* DIR0 <==> PTA4 */
	GPIO_InitTypeDef gpio_init_struct;
	bzero(&gpio_init_struct, sizeof(gpio_init_struct));
	
	gpio_init_struct.GPIO_PTx = PTA;
	gpio_init_struct.GPIO_Pins = GPIO_Pin4;
	gpio_init_struct.GPIO_Dir = DIR_OUTPUT;
	gpio_init_struct.GPIO_Output = OUTPUT_L;
	gpio_init_struct.GPIO_PinControl = IRQC_DIS;
	
	LPLD_GPIO_Init(gpio_init_struct);

	/* PWM0 <==> PTA1 */
	LPLD_FTM_PWM_Enable(FTM0,
						FTM_Ch6,
						MOTOR_PWM_INIT,
						PTA1,
						ALIGN_LEFT
						);
}

static void init_right_motor(void)
{
	/* DIR1 <==> PTA5 */
	GPIO_InitTypeDef gpio_init_struct;
	bzero(&gpio_init_struct, sizeof(gpio_init_struct));
	
	gpio_init_struct.GPIO_PTx = PTA;
	gpio_init_struct.GPIO_Pins = GPIO_Pin5;
	gpio_init_struct.GPIO_Dir = DIR_OUTPUT;
	gpio_init_struct.GPIO_Output = OUTPUT_L;
	gpio_init_struct.GPIO_PinControl = IRQC_DIS;
	
	LPLD_GPIO_Init(gpio_init_struct);

	/* PWM1 <==> PTA2 */
	LPLD_FTM_PWM_Enable(FTM0,
						FTM_Ch7,
						MOTOR_PWM_INIT,
						PTA2,
						ALIGN_LEFT
						);
}

void init_motor(void)
{
	init_FTM0();
	
	init_left_motor();
	init_right_motor();
}
