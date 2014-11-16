#include "common.h"
#include "pit.h"

#include "DEV_Motor.h"
#include "DEV_Encoder.h"
#include "DEV_PID.h"
#include "DEV_Balance.h"
#include "DEV_OLED.h"

void init_indicate_gpio(void)
{
	GPIO_InitTypeDef indicate_gpio;
	bzero(&indicate_gpio, sizeof(indicate_gpio));
		
	indicate_gpio.GPIO_PTx = PTB;
	indicate_gpio.GPIO_Pins = GPIO_Pin23;
	indicate_gpio.GPIO_Dir = DIR_OUTPUT;
	indicate_gpio.GPIO_Output = OUTPUT_H;
	indicate_gpio.GPIO_PinControl = IRQC_DIS;

	LPLD_GPIO_Init(indicate_gpio);
}

void main(void)
{
	delay_ms(1000);

	//init_indicate_gpio();

	init_oled();
	init_adc();
	init_encoder();
	init_motor();
	init_speed(0, 40, 2);
	
	init_pit0();
	pit0_enable_irq();

	while (1) {

	}
}

