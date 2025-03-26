// src/mq4_gas.c
#include "mq4_gas.h"

float mq4_read_gas() {
    int sensor_value = mcp3008_read_channel(GAS_CHANNEL);
    float voltage = (sensor_value * 3.3f) / 1023.0f;
    float rs_ro_ratio = (3.3f - voltage) / voltage;
    float gas_concentration = (MQ4_RO_CLEAR_AIR - rs_ro_ratio) * 1000.0f;
    return gas_concentration > 0.0f ? gas_concentration : 0.0f;
}