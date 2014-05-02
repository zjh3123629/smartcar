#ifndef _DEV_LED_H_
#define _DEV_LED_H_

#include "common.h"

#define NORMAL	0
#define BREATH	1
void init_led(uint8 mode);

void led_on(void);
void led_off(void);

void led_update_brightness(int8 percent);

#endif