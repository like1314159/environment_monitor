// include/mcp3008_adc.h
#ifndef MCP3008_ADC_H
#define MCP3008_ADC_H

#include <wiringPi.h>
#include <wiringPiSPI.h>

#define SPI_CHANNEL 0
#define SPI_SPEED 1000000

int mcp3008_init();
int mcp3008_read_channel(int channel);
void mcp3008_cleanup();

#endif