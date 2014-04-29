#include "DEV_LED.h"

void init_led(void)
{
	GPIO_InitTypeDef gpio_init_struct;
	
	gpio_init_struct.GPIO_PTx = PTA;
	gpio_init_struct.GPIO_Pins = GPIO_Pin3;
	gpio_init_struct.GPIO_Dir = DIR_OUTPUT;
	gpio_init_struct.GPIO_Output = OUTPUT_H;
	gpio_init_struct.GPIO_PinControl = IRQC_DIS;
	
	LPLD_GPIO_Init(gpio_init_struct);
}

void led_on(void)
{
	LPLD_GPIO_Output_b(PTA, 3, 0);
}

void led_off(void)
{
	LPLD_GPIO_Output_b(PTA, 3, 1);
}