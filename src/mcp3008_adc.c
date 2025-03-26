// src/mcp3008_adc.c
#include "mcp3008_adc.h"

int mcp3008_init() {
    if (wiringPiSetup() == -1) {
        return -1;
    }
    return wiringPiSPISetup(SPI_CHANNEL, SPI_SPEED);
}

int mcp3008_read_channel(int channel) {
    if (channel < 0 || channel > 7) return -1;
    
    unsigned char buffer[3] = {1, (8 + channel) << 4, 0};
    wiringPiSPIDataRW(SPI_CHANNEL, buffer, 3);
    
    return ((buffer[1] & 0x03) << 8) | buffer[2];
}

void mcp3008_cleanup() {
    // SPI接口无需特殊清理
}