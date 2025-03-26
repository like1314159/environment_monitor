// include/mq4_gas.h
#ifndef MQ4_GAS_H
#define MQ4_GAS_H

#include "mcp3008_adc.h"

#define GAS_CHANNEL 1
#define MQ4_RO_CLEAR_AIR 9.83f

float mq4_read_gas();

#endif