# Definitions.
CC = avr-gcc
CFLAGS = -mmcu=atmega32u2 -Os -Wall -Wstrict-prototypes -Wextra -g -I. -I../../utils -I../../fonts -I../../drivers -I../../drivers/avr
OBJCOPY = avr-objcopy
SIZE = avr-size
DEL = rm

# Default target.
all: tetris.out

tetris.o: tetris.c tetris.h ../../drivers/avr/system.h
	$(CC) -c $(CFLAGS) $< -o $@

pio.o: ../../drivers/avr/pio.c ../../drivers/avr/pio.h ../../drivers/avr/system.h
	$(CC) -c $(CFLAGS) $< -o $@

system.o: ../../drivers/avr/system.c ../../drivers/avr/system.h
	$(CC) -c $(CFLAGS) $< -o $@

led.o: ../../drivers/led.c ../../drivers/avr/pio.h ../../drivers/avr/system.h ../../drivers/led.h
	$(CC) -c $(CFLAGS) $< -o $@

button.o: ../../drivers/button.c ../../drivers/button.h ../../drivers/avr/system.h
	$(CC) -c $(CFLAGS) $< -o $@
	
ledmat.o: ../../drivers/ledmat.o ../../drivers/ledmat.h
	$(CC) -c $(CFLAGS) $< -o $@
	
# Link: create output file (executable) from object files.
tetris.out: tetris.o led.o pio.o system.o button.o
	$(CC) $(CFLAGS) $^ -o $@ -lm
	$(SIZE) $@

# Create hex file for programming from executable file.
tetris.hex: tetris.out
	$(OBJCOPY) -O ihex tetris.out tetris.hex

# Target: clean project.
.PHONY: clean
clean: 
	-$(DEL) *.o *.out *.hex

# Target: program project.
.PHONY: program
program: tetris.hex
	dfu-programmer atmega32u2 erase; dfu-programmer atmega32u2 flash tetris.hex; dfu-programmer atmega32u2 start

