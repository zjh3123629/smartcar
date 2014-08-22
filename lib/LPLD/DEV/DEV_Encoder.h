#ifndef __DEV_ENCODER_H__
#define __DEV_ENCODER_H__

#include "common.h"

enum {
	POSITIVE = 0,
	NEGATIVE
};

void init_encoder(void);
int encoder_dir(void);

#endif