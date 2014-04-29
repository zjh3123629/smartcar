#ifndef _DEV_LED_H_
#define _DEV_LED_H_

#include "common.h"

enum {
	DARK = 0,
	LIGHT,
};

void init_led(void);
void led_on(void);
void led_off(void);

#endif