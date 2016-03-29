/* Name: main.c
 * Author: <insert your name here>
 * Copyright: <insert your copyright message here>
 * License: <insert your license reference here>
 */

// Changing implementation to Chirps Raven...
//    D0 - D7  = PD0 - PD7
//    D8 - D13 = PB0 - PB5
//    A0 - A5  = PC0 - PC5
//    Switches @ PB0, PD7, PD4, PD2
//    LED @ PB5
//    Clock15MHz @ PB6, PB7

// This is only to resolve the issue with YCM plugin.
/*#ifndef __AVR_ATmega328P__*/
#define __AVR_ATmega328P__
/*#endif*/

// This io.h file will use the above define to include the appropriate
// device-specfic io file.
#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include "dtmf_generator.h"
#include "serial.h"

#define SWITCH1 8
#define SWITCH2 7
#define SWITCH3 4
#define SWITCH4 2

uint8_t  world_init(void);
uint8_t  get_switches(void);
void     set_leds(uint8_t set_mask);
void     send_tone_seq(uint32_t sequence, uint8_t num_chars);

volatile static uint8_t interrupt_flag = 0;

static void uart_putchar(char c, FILE *stream);
static FILE uart_output = FDEV_SETUP_STREAM(uart_putchar, NULL, _FDEV_SETUP_WRITE);

static void uart_putchar(char c, FILE *stream)
{
   if (c == '\n') {
       uart_putchar('\r', stream);
   }
	serial_write(c);
}

ISR(TIMER0_OVF_vect) {
   dtmf_increment();
}


int main(void) {

   uint8_t switches = 0;

   /* Initializations */
   world_init();
   dtmf_init();
   serial_init();

   /*LCDInit(1);*/
   /*LCDWriteInt(123,4);*/

   stdout = &uart_output;
   sei();

   printf("Hello, world!\n");

   send_tone_seq(0x9220821F, 8);
   /*dtmf_set_tone(0x00);*/
   /*dtmf_start();*/


	while(1) {

      switches = get_switches();

	}

	return 0;
}


void send_tone_seq(uint32_t sequence, uint8_t num_chars) {
   int i;

   dtmf_stop();
   _delay_us(500);

   for (i = 0; i < num_chars; i++) {
      dtmf_set_tone( ((uint8_t) (sequence >> (4*(num_chars - i - 1)))) & 0x0F);
      dtmf_start();
      _delay_ms(100);
      dtmf_stop();
      _delay_ms(200);
   }
}

uint8_t get_switches(void) {
//    Switches @ PB0, PD7, PD4, PD2

   uint8_t switches_pb;
   uint8_t switches_pd;
   uint8_t switches_out = 0;

   switches_pb = PINB;
   switches_pd = PIND;

   if ((switches_pb & (1 << 0)) != 0) switches_out |= (1 << 0);
   if ((switches_pd & (1 << 7)) != 0) switches_out |= (1 << 1);
   if ((switches_pd & (1 << 4)) != 0) switches_out |= (1 << 2);
   if ((switches_pd & (1 << 2)) != 0) switches_out |= (1 << 3);

   return switches_out;
}

void set_leds(uint8_t set_mask) {
//    LED @ PB5
   PORTB = (PINB & 0xDF) |  ((set_mask & 0x01) << 5);
}


uint8_t world_init(void) {

   //Crystal Oscillator division factor: 1
   CLKPR=(1<<CLKPCE);
   CLKPR=(0<<CLKPCE) | (0<<CLKPS3) | (0<<CLKPS2) | (0<<CLKPS1) | (0<<CLKPS0);

   // Input/Output Ports initialization
   // Port B initialization
   // Function: Bit7=In Bit6=In Bit5=In Bit4=In Bit3=In Bit2=In Bit1=In Bit0=In 
   DDRB=(0<<DDB7) | (0<<DDB6) | (1<<DDB5) | (0<<DDB4) | (0<<DDB3) | (0<<DDB2) | (0<<DDB1) | (0<<DDB0);
   // State: Bit7=T Bit6=T Bit5=T Bit4=T Bit3=T Bit2=T Bit1=T Bit0=T 
   PORTB=(0<<PORTB7) | (0<<PORTB6) | (0<<PORTB5) | (0<<PORTB4) | (0<<PORTB3) | (0<<PORTB2) | (0<<PORTB1) | (0<<PORTB0);

   // Port C initialization
   // Function: Bit6=In Bit5=Out Bit4=Out Bit3=Out Bit2=Out Bit1=Out Bit0=Out 
   DDRC=(0<<DDC6) | (0<<DDC5) | (0<<DDC4) | (0<<DDC3) | (0<<DDC2) | (0<<DDC1) | (0<<DDC0);
   // State: Bit6=T Bit5=0 Bit4=0 Bit3=0 Bit2=0 Bit1=0 Bit0=0 
   PORTC=(0<<PORTC6) | (0<<PORTC5) | (0<<PORTC4) | (0<<PORTC3) | (0<<PORTC2) | (0<<PORTC1) | (0<<PORTC0);

   // Port D initialization
   // Function: Bit7=In Bit6=Out Bit5=In Bit4=In Bit3=In Bit2=In Bit1=In Bit0=In 
   DDRD=(1<<DDD7) | (1<<DDD6) | (1<<DDD5) | (1<<DDD4) | (1<<DDD3) | (1<<DDD2) | (1<<DDD1) | (1<<DDD0);
   // State: Bit7=T Bit6=0 Bit5=T Bit4=T Bit3=T Bit2=T Bit1=T Bit0=T 
   PORTD=(0<<PORTD7) | (0<<PORTD6) | (0<<PORTD5) | (0<<PORTD4) | (0<<PORTD3) | (0<<PORTD2) | (0<<PORTD1) | (0<<PORTD0);

   return 0;
}
