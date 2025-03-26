// include/max4466_noise.h
#ifndef MAX4466_NOISE_H
#define MAX4466_NOISE_H

#include "mcp3008_adc.h"

#define NOISE_CHANNEL 0
#define NOISE_REFERENCE 0.00002f  // 20μPa参考声压

float max4466_read_noise();

#endif