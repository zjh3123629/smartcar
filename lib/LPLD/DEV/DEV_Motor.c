#include "DEV_Motor.h"

int32 g_motor_speed_old=0, g_motor_speed_new=0;
int32 g_left_motor_pwm=0, g_right_motor_pwm=0;

static void init_FTM0(void)
{
	FTM_InitTypeDef ftm_init_struct;
	bzero(&ftm_init_struct, sizeof(ftm_init_struct));

	ftm_init_struct.FTM_Ftmx = FTM0;			//ʹ��FTM0ͨ��
	ftm_init_struct.FTM_Mode = FTM_MODE_PWM;	//ʹ��PWMģʽ
	ftm_init_struct.FTM_PwmFreq = MOTOR_PWM_HZ;	//PWMƵ��20KHz

	LPLD_FTM_Init(ftm_init_struct);
}

static void init_left_motor(void)
{
	/* DIR0 <==> PTA4 */
	GPIO_InitTypeDef left_motor_dir_gpio;
	bzero(&left_motor_dir_gpio, sizeof(left_motor_dir_gpio));
	
	left_motor_dir_gpio.GPIO_PTx = PTA;
	left_motor_dir_gpio.GPIO_Pins = GPIO_Pin4;
	left_motor_dir_gpio.GPIO_Dir = DIR_OUTPUT;
	left_motor_dir_gpio.GPIO_Output = OUTPUT_L;
	left_motor_dir_gpio.GPIO_PinControl = IRQC_DIS;
	
	LPLD_GPIO_Init(left_motor_dir_gpio);

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
	GPIO_InitTypeDef right_motor_dir_gpio;
	bzero(&right_motor_dir_gpio, sizeof(right_motor_dir_gpio));
	
	right_motor_dir_gpio.GPIO_PTx = PTA;
	right_motor_dir_gpio.GPIO_Pins = GPIO_Pin5;
	right_motor_dir_gpio.GPIO_Dir = DIR_OUTPUT;
	right_motor_dir_gpio.GPIO_Output = OUTPUT_L;
	right_motor_dir_gpio.GPIO_PinControl = IRQC_DIS;
	
	LPLD_GPIO_Init(right_motor_dir_gpio);

	/* PWM1 <==> PTA2 */
	LPLD_FTM_PWM_Enable(FTM0,
						FTM_Ch7,
						MOTOR_PWM_INIT,
						PTA2,
						ALIGN_LEFT
						);
}

/*
 * duty>0: ��ת
 * duty<0: ��ת
 */
void motor_change_pwm(uint8 left_right, int32 duty)
{
	// limit
	if (duty > MOTOR_PWM_MAX)
		duty = MOTOR_PWM_MAX;
	else if (duty < -MOTOR_PWM_MAX)
		duty = -MOTOR_PWM_MAX;

	if (duty > 0) {
		if (LEFT_MOTOR == left_right) {
			LPLD_GPIO_Output_b(PTA, 4, OUTPUT_L);
			
			LPLD_FTM_PWM_ChangeDuty(FTM0, FTM_Ch6, duty);
		}
			
		else if (RIGHT_MOTOR == left_right) {
			LPLD_GPIO_Output_b(PTA, 5, OUTPUT_L);
			
			LPLD_FTM_PWM_ChangeDuty(FTM0, FTM_Ch7, duty);
		}
	} else {
		if (LEFT_MOTOR == left_right) {
			LPLD_GPIO_Output_b(PTA, 4, OUTPUT_H);
			
			LPLD_FTM_PWM_ChangeDuty(FTM0, FTM_Ch6, MOTOR_PWM_MAX+duty);
		}
		else if (RIGHT_MOTOR == left_right) {
			LPLD_GPIO_Output_b(PTA, 5, OUTPUT_H);
			
			LPLD_FTM_PWM_ChangeDuty(FTM0, FTM_Ch7, MOTOR_PWM_MAX+duty);
		}
	}
}

void init_motor(void)
{
	init_FTM0();
	
	init_left_motor();
	init_right_motor();
}

void motor_speed_smooth(void)
{
	int32 nValue = 0;
	
	nValue = g_motor_speed_new - g_motor_speed_old;
	nValue = nValue * (g_pit0_counter + 1) / (MOTOR_PID_CALC_PERIOD/PIT0_TIMER_PERIOD - 1) + g_motor_speed_old;
	g_left_motor_pwm = g_right_motor_pwm = nValue;
}

static int32 integral = 0;
void motor_speed_adjust_calc(void)
{
	int32 left_speed=0, right_speed=0, delta_speed=0;
	int32 P=0, I=0;
	int32 speed=0;
	
	left_speed = g_left_pulse;
	right_speed = g_right_pulse;
	speed = (left_speed + right_speed) / 2;

	g_motor_speed_old = g_motor_speed_new;

#if 0
	delta_speed = MOTOR_INIT_SPEED - speed;
	P = (float)delta_speed * MOTOR_SPEED_KP;
	I = (float)delta_speed * MOTOR_SPEED_KI;

#define SPEED_CONTROL_INTEGRAL_MAX	200
	integral -= I;
	if (integral > SPEED_CONTROL_INTEGRAL_MAX)
		integral = SPEED_CONTROL_INTEGRAL_MAX;
	else if (integral < -SPEED_CONTROL_INTEGRAL_MAX)
		integral = -SPEED_CONTROL_INTEGRAL_MAX;
	
	g_motor_speed_new = (int32)(integral) - P;
	
	printf("delta_speed=%d, integral=%d, P=%d, speed=%d\n", delta_speed, integral, P, g_motor_speed_new);
#else
	g_motor_speed_new = -pid_position(&left_motor_pid, speed);

	printf("delta_speed=%d, speed=%d\n", left_motor_pid.point-speed, g_motor_speed_new);
#endif
	
	//if(integral > MOTOR_OUT_MAX) integral = MOTOR_OUT_MAX;
	//if(integral < MOTOR_OUT_MIN) integral = MOTOR_OUT_MIN;
}


