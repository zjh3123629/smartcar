#include "DEV_LED.h"

/**
  * @brief  
  * @param  NORMAL/BREATH
  * @retval None
  */
void init_led(uint8 mode)
{
	ASSERT( mode<=BREATH );
	
	if (NORMAL == mode) {
		GPIO_InitTypeDef gpio_init_struct;
		
		gpio_init_struct.GPIO_PTx = PTA;
		gpio_init_struct.GPIO_Pins = GPIO_Pin3;
		gpio_init_struct.GPIO_Dir = DIR_OUTPUT;
		gpio_init_struct.GPIO_Output = OUTPUT_H;
		gpio_init_struct.GPIO_PinControl = IRQC_DIS;
		
		LPLD_GPIO_Init(gpio_init_struct);
	} else {
		/* PTA3 <--> FTM0.ch0 */
		FTM_InitTypeDef ftm_init_struct;
		bzero(&ftm_init_struct, sizeof(FTM_InitTypeDef));
		
		ftm_init_struct.FTM_Ftmx = FTM0;
		ftm_init_struct.FTM_Mode = FTM_MODE_PWM;
		ftm_init_struct.FTM_PwmFreq = 10000;	// PWMÆµÂÊ10KHz
		LPLD_FTM_Init(ftm_init_struct);

		LPLD_FTM_PWM_Enable(FTM0,
							FTM_Ch0,
							0,
							PTA3,
							ALIGN_RIGHT
		);
	}
}

void led_on(void)
{
	LPLD_GPIO_Output_b(PTA, 3, 0);
}

void led_off(void)
{
	LPLD_GPIO_Output_b(PTA, 3, 1);
}

/**
  * @brief  
  * @param  0-100
  * @retval None
  */
void led_update_brightness(int8 percent)
{
	vuint32 mod = FTM0->MOD + 1;
	
	ASSERT( (percent>=0) && (percent <= 100) );
	
	FTM0->CONTROLS[0].CnV = mod/100*percent;
}
