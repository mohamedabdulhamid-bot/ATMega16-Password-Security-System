MCU = atmega16
F_CPU = 16000000UL
CC = avr-gcc
CFLAGS = -mmcu=$(MCU) -DF_CPU=$(F_CPU) -Os
OBJ = main.o
TARGET = main

all: $(TARGET).hex

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGET).elf: $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@

$(TARGET).hex: $(TARGET).elf
	avr-objcopy -O ihex $< $@

clean:
	rm -f *.o *.elf *.hex

# Add this to your Makefile
SRC = main.c alcd.c
OBJ = $(SRC:.c=.o)

main.elf: $(OBJ)
	avr-gcc -mmcu=atmega16 -DF_CPU=16000000UL -Os $(OBJ) -o main.elf

%.o: %.c
	avr-gcc -mmcu=atmega16 -DF_CPU=16000000UL -Os -c $< -o $@