// src/jw01_co2.c
#include "jw01_co2.h"
#include <fcntl.h>
#include <unistd.h>

static int uart_fd = -1;

int jw01_init() {
    uart_fd = open(CO2_UART_DEVICE, O_RDWR | O_NOCTTY | O_NDELAY);
    if (uart_fd == -1) return -1;

    struct termios options;
    tcgetattr(uart_fd, &options);
    options.c_cflag = B9600 | CS8 | CLOCAL | CREAD;
    options.c_iflag = IGNPAR;
    options.c_oflag = 0;
    options.c_lflag = 0;
    tcflush(uart_fd, TCIFLUSH);
    tcsetattr(uart_fd, TCSANOW, &options);

    return 0;
}

int jw01_read_co2() {
    if (uart_fd == -1) return -1;

    unsigned char buffer[9];
    int bytes_read = read(uart_fd, buffer, sizeof(buffer));
    
    if (bytes_read == 9 && buffer[0] == 0xFF && buffer[1] == 0x01) {
        return (buffer[3] << 8) | buffer[4];
    }
    return -1;
}

void jw01_cleanup() {
    if (uart_fd != -1) {
        close(uart_fd);
        uart_fd = -1;
    }
}