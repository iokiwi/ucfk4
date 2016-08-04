# File:   Makefile
# Author: S. O. Merrick, CSSE
# Date:   19 Oct 2013
# Descr:  Makefile for rpsls

# Definitions.
CC = avr-gcc
CFLAGS = -mmcu=atmega32u2 -Os -Wall -Wstrict-prototypes -Wextra -g -I../../drivers/avr -I../../utils -I../../drivers
OBJCOPY = avr-objcopy
SIZE = avr-size
DEL = rm

# Default target.
all: rpsls.out

# Compile: create object files from C source files.
rpsls.o: rpsls.c rpsls.h ../../drivers/avr/pio.h ../../drivers/avr/system.h ../../utils/pacer.h
	$(CC) -c $(CFLAGS) $< -o $@

pio.o: ../../drivers/avr/pio.c ../../drivers/avr/pio.h ../../drivers/avr/system.h
	$(CC) -c $(CFLAGS) $< -o $@

system.o: ../../drivers/avr/system.c ../../drivers/avr/system.h
	$(CC) -c $(CFLAGS) $< -o $@

timer.o: ../../drivers/avr/timer.c ../../drivers/avr/system.h ../../drivers/avr/timer.h
	$(CC) -c $(CFLAGS) $< -o $@

pacer.o: ../../utils/pacer.c ../../drivers/avr/system.h ../../drivers/avr/timer.h ../../utils/pacer.h
	$(CC) -c $(CFLAGS) $< -o $@

led.o: ../../drivers/led.c ../../drivers/led.h ../../drivers/avr/pio.h ../../drivers/avr/system.h 
	$(CC) -c $(CFLAGS) $< -o $@

navswitch.o: ../../drivers/navswitch.c ../../drivers/avr/delay.h ../../drivers/avr/pio.h ../../drivers/avr/system.h ../../drivers/navswitch.h
	$(CC) -c $(CFLAGS) $< -o $@
	
ledmat.o: ../../drivers/ledmat.c ../../drivers/avr/pio.h ../../drivers/avr/system.h ../../drivers/ledmat.h
	$(CC) -c $(CFLAGS) $< -o $@
	
pacer.o: ../../utils/pacer.c ../../drivers/avr/system.h ../../drivers/avr/timer.h ../../utils/pacer.h
	$(CC) -c $(CFLAGS) $< -o $@

tinygl.o: ../../utils/tinygl.c ../../drivers/avr/system.h ../../drivers/display.h ../../utils/font.h ../../utils/tinygl.h
	$(CC) -c $(CFLAGS) $< -o $@

display.o: ../../drivers/display.c ../../drivers/avr/system.h ../../drivers/display.h ../../drivers/ledmat.h
	$(CC) -c $(CFLAGS) $< -o $@

font.o: ../../utils/font.c ../../drivers/avr/system.h ../../utils/font.h
	$(CC) -c $(CFLAGS) $< -o $@
	

# Link: create output file (executable) from object files.
rpsls.out: rpsls.o pio.o system.o timer.o pacer.o led.o navswitch.o ledmat.o pacer.o tinygl.o display.o font.o
	$(CC) $(CFLAGS) $^ -o $@ -lm
	$(SIZE) $@

# Create hex file for programming from executable file.
rpsls.hex: rpsls.out
	$(OBJCOPY) -O ihex rpsls.out rpsls.hex

# Target: clean project.
.PHONY: clean
clean: 
	-$(DEL) *.o *.out *.hex

# Target: program project.
.PHONY: program
program: rpsls.hex
	dfu-programmer atmega32u2 erase; dfu-programmer atmega32u2 flash rpsls.hex; dfu-programmer atmega32u2 start
