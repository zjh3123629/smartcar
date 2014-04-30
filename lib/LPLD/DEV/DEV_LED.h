#ifndef _DEV_LED_H_
#define _DEV_LED_H_

#include "common.h"

#define DARK	0
#define LIGHT	1

void init_led(void);
void led_on(void);
void led_off(void);

#endif