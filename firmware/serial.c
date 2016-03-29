#include "serial.h"

//=============================================================================
void serial_init() {

   // Setting the baud rate using setbaud.h macros
   UBRR0H = UBRRH_VALUE;
   UBRR0L = UBRRL_VALUE;

   // Setting (or not) 2X baud.
#if USE_2X
   UCSR0A |= _BV(U2X0);
#else
   UCSR0A &= ~(_BV(U2X0));
#endif

   // I found this whole crafty initialization block on the internet...
   UCSR0C = _BV(UCSZ01) | _BV(UCSZ00); /* 8-bit data */
   UCSR0B = _BV(RXEN0) | _BV(TXEN0);   /* Enable RX and TX */

}

//=============================================================================
void serial_write(uint8_t data) {

   // Wait for empty tra0smit buffer 
   while ( !( UCSR0A & (1<<UDRE0)) ) {
      ;
   }

   // Put data into buffer, sends the data 
   UDR0 = data;
}

//=============================================================================
uint8_t serial_read() {

   // Wait for data to be received
   while ( !(UCSR0A & (1<<RXC0)) ) {
      ;
   }

   // Get and return received data from buffer
   return UDR0;
}

