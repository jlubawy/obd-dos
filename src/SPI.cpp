/**
 *  File Name : SPI.cpp
 *     Author : Josh Lubawy <jlubawy@gmail.com>
 *                          <jlubawy@asu.edu>
 */

#include "SPI.h"

/******************************************************************************
                                   Functions
******************************************************************************/
/*****************************************************************************/
void
SPI_init( void )
{
    /* Set the SS pin as an output */
    pinMode( SS, OUTPUT );

    /* Initialize GPIOs for chip-selects */
    digitalWrite( 10, HIGH );
    pinMode( 10, OUTPUT );

    SPCR |= _BV(MSTR);
    SPCR |= 0x0C;
    SPCR |= _BV(SPE);

    pinMode( SCK, OUTPUT );
    pinMode( MOSI, OUTPUT );
}


/*****************************************************************************/
void
SPI_transfer( void* buffer, size_t length )
{
    size_t i;
    uint8_t* b = (uint8_t*)buffer;

    for ( i = 0; i < length; i++ ) {
        SPDR = b[i];
        while (!(SPSR & _BV(SPIF)));
        b[i] = SPDR;
    }
}


/*****************************************************************************/
void
SPI_sendByte( uint8_t data )
{
    SPI_transfer( &data, sizeof(data) );
}


/*****************************************************************************/
uint8_t
SPI_receiveByte( void )
{
    uint8_t data = 0x00; /* send zero out TX buffer */
    SPI_transfer( &data, sizeof(data) );
    return data;
}
