// src/max4466_noise.c
#include "max4466_noise.h"
#include <math.h>
#include <time.h>

float max4466_read_noise() {
    int max_value = 0;
    time_t start_time = time(NULL);
    
    // 采样50ms
    while (time(NULL) - start_time < 0.05) {
        int value = mcp3008_read_channel(NOISE_CHANNEL);
        if (value > max_value) max_value = value;
        usleep(100);
    }
    
    float voltage = (max_value * 3.3f) / 1023.0f;
    float sound_pressure = voltage / 100.0f / 0.00631f;
    
    if (sound_pressure <= 0.0f) return 0.0f;
    
    float db = 20.0f * log10f(sound_pressure / NOISE_REFERENCE);
    return db > 0.0f ? db : 0.0f;
}