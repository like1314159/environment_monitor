CC = gcc
CFLAGS = -Wall -Iinclude
LDFLAGS = -lwiringPi -lcurl -lm
SRC = src/main.c src/mcp3008_adc.c src/jw01_co2.c src/max4466_noise.c src/mq4_gas.c src/onenet_upload.c
OBJ = $(SRC:.c=.o)
TARGET = environment_monitor

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJ) $(TARGET)

.PHONY: all clean