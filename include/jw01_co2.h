// include/jw01_co2.h
#ifndef JW01_CO2_H
#define JW01_CO2_H

#include <termios.h>

#define CO2_UART_DEVICE "/dev/ttyS0"

int jw01_init();
int jw01_read_co2();
void jw01_cleanup();

#endif