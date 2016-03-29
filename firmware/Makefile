# Name: Makefile
# Author: <insert your name here>
# Copyright: <insert your copyright message here>
# License: <insert your license reference here>

# This is a prototype Makefile. Modify it according to your needs.
# You should at least check the settings for
# DEVICE ....... The AVR device you compile for
# CLOCK ........ Target AVR clock rate in Hertz
# OBJECTS ...... The object files created from your source files. This list is
#                usually the same as the list of source files with suffix ".o".
# PROGRAMMER ... Options to avrdude which define the hardware you use for
#                uploading to the AVR and the interface where this hardware
#                is connected. We recommend that you leave it undefined and
#                add settings like this to your ~/.avrduderc file:
#                   default_programmer = "stk500v2"
#                   default_serial = "avrdoper"
# FUSES ........ Parameters for avrdude to flash the fuses appropriately.

#DEVICE     = atmega328p
DEVICE     = atmega168
#CLOCK      = 8000000
CLOCK      = 14700000

# This is for using an arduino as programmer. Modify the serial port for
# different arduino's / OS's.
# See https://learn.adafruit.com/arduino-tips-tricks-and-techniques/arduinoisp
# for Arduion programmer sketch. The one that comes with the Arduino IDE
# is buggy.

# This line is to use an Arduino as programmer
#PROGRAMMER = -c arduino -P /dev/tty.usbserial-AH02Y9KT -b 19200
# This line uses the Atmel ISP mkII
PROGRAMMER = -c avrisp2 -P usb
OBJECTS    = main.o dtmf_generator.o serial.o

### FUSES ###
# the fuse bit calculator at http://www.engbedded.com/fusecalc/
# Default fuse settings for ATMEGA328p.
#FUSES      = -U lfuse:w:0xe2:m -U hfuse:w:0xd9:m -U efuse:w:0xff:m

# Default fuse with clk/8 divider for ATMEGA328p.
#FUSES      = -U lfuse:w:0x62:m -U hfuse:w:0xd9:m -U efuse:w:0xff:m

FUSES  		= -U lfuse:w:0xde:m -U hfuse:w:0xdf:m -U efuse:w:0xf9:m
#FUSES       = -U lfuse:w:0x62:m -U hfuse:w:0xdf:m -U efuse:w:0xf9:m





# Tune the lines below only if you know what you are doing:

AVRDUDE = avrdude $(PROGRAMMER) -p $(DEVICE)
COMPILE = avr-gcc -Wall -Os -DF_CPU=$(CLOCK) -mmcu=$(DEVICE)

# symbolic targets:
all:	main.hex

.c.o:
	$(COMPILE) -c $< -o $@

.S.o:
	$(COMPILE) -x assembler-with-cpp -c $< -o $@
# "-x assembler-with-cpp" should not be necessary since this is the default
# file type for the .S (with capital S) extension. However, upper case
# characters are not always preserved on Windows. To ensure WinAVR
# compatibility define the file type manually.

.c.s:
	$(COMPILE) -S $< -o $@

flash:	all
	$(AVRDUDE) -U flash:w:main.hex:i

fuse:
	$(AVRDUDE) $(FUSES)

# Xcode uses the Makefile targets "", "clean" and "install"
install: flash fuse

# if you use a bootloader, change the command below appropriately:
load: all
	bootloadHID main.hex

clean:
	rm -f main.hex main.elf $(OBJECTS)

# file targets:
main.elf: $(OBJECTS)
	$(COMPILE) -o main.elf $(OBJECTS)

main.hex: main.elf
	rm -f main.hex
	avr-objcopy -j .text -j .data -O ihex main.elf main.hex
	avr-size --format=avr --mcu=$(DEVICE) main.elf
# If you have an EEPROM section, you must also create a hex file for the
# EEPROM and add it to the "flash" target.

# Targets for code debugging and analysis:
disasm:	main.elf
	avr-objdump -d main.elf

cpp:
	$(COMPILE) -E main.c
