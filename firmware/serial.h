#ifndef SERIAL_H
#define ADC_H

#include <avr/io.h>

// Helper functions for setting Baud Rate.
/*#define F_CPU 14700000UL*/
#define BAUD  57600
#include <util/setbaud.h>

void serial_init();
void serial_write(uint8_t data);
uint8_t serial_read();

#endif // SERIAL_H

