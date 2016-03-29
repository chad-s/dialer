#ifndef DTMF_GENERATOR_H
#define DTMF_GENERATOR_H

//#ifndef __AVR_ATmega328P__
//#define __AVR_ATmega328P__
//#endif

#include <avr/io.h>

void  dtmf_init();
void  dtmf_increment();
void  dtmf_set_tone(uint8_t tone);
void  dtmf_stop(void);
void  dtmf_start(void);
void  dtmf_set_offsets(uint8_t tone);

extern uint16_t index_hi;
extern uint16_t index_lo;
extern uint16_t offset_hi;
extern uint16_t offset_lo;

extern const uint8_t wave_table[256];

#endif
