
#include "serial.h"

// Helper functions for setting Baud Rate.
/*#define F_CPU 14700000UL*/
#define BAUD  57600
#include <util/setbaud.h>

void serial_init()
{
  // USART0 initialization
  // Communication Parameters: 8 Data, 1 Stop, No Parity
  // USART0 Receiver: On
  // USART0 Transmitter: On
  // USART0 Mode: Asynchronous
  // USART0 Baud Rate: 57600
  /*UCSR0A=(0<<RXC0) | (0<<TXC0) | (0<<UDRE0) | (0<<FE0) | (0<<DOR0) | (0<<UPE0) | (0<<U2X0) | (0<<MPCM0);*/
  /*UCSR0B=(0<<RXCIE0) | (0<<TXCIE0) | (0<<UDRIE0) | (1<<RXEN0) | (1<<TXEN0) | (0<<UCSZ02) | (0<<RXB80) | (0<<TXB80);*/
  /*UCSR0C=(0<<UMSEL01) | (0<<UMSEL00) | (0<<UPM01) | (0<<UPM00) | (0<<USBS0) | (1<<UCSZ01) | (1<<UCSZ00) | (0<<UCPOL0);*/

   UBRR0H = UBRRH_VALUE;
   UBRR0L = UBRRL_VALUE;

#if USE_2X
   UCSR0A |= _BV(U2X0);
#else
   UCSR0A &= ~(_BV(U2X0));
#endif

   UCSR0C = _BV(UCSZ01) | _BV(UCSZ00); /* 8-bit data */
   UCSR0B = _BV(RXEN0) | _BV(TXEN0);   /* Enable RX and TX */

}

//=============================================================================
void serial_write(uint8_t data)
{
  // Wait for empty tra0smit buffer 
  while ( !( UCSR0A & (1<<UDRE0)) )
  {
    ;
  }
  // Put data into buffer, sends the data 
  UDR0 = data;
}

//=============================================================================
uint8_t serial_read()
{
  // Wait for data to be received
  while ( !(UCSR0A & (1<<RXC0)) )
  {
    ;
  }
  // Get and return received data from buffer
  return UDR0;
}

//-----------------------------------------------------------------------------
//      __   __              ___  ___
//     |__) |__) | \  /  /\   |  |__
//     |    |  \ |  \/  /~~\  |  |___
//
//-----------------------------------------------------------------------------


//==============================================================================

