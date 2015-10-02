/**
 * SPI.cpp - SPI drivers for the OBD-Dos platform
 * Copyright (C) 2015 Josh Lubawy <jlubawy@gmail.com> <jlubawy@asu.edu>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#include <Arduino.h>

#include "Assert.h"
#include "Serial.h"
#include "SPI.h"
#include "Utility.h"

/******************************************************************************
                                     Macros
******************************************************************************/
/*****************************************************************************/
#define SPI_CSN_ENTER()  digitalWrite( 10, LOW )
#define SPI_CSN_EXIT()   digitalWrite( 10, HIGH )


/******************************************************************************
                                     Types
******************************************************************************/
/*****************************************************************************/
typedef struct {
    uint32_t   clockFreq;
    uint8_t    csnPin;
    SPI_Mode_t mode;
} SPI_Descriptor_t;


/******************************************************************************
                                Local Variables
******************************************************************************/
/*****************************************************************************/
static SPI_Descriptor_t portDescriptors[ SPI_NUM_PORTS ] = {
    /* SPI_PORT_CAN_BUS */
    {
        .clockFreq = 4000000,
        .csnPin    = 10,
        .mode      = SPI_MODE_3,
    },
};

/*****************************************************************************/
static uint8_t rateSel[ SPI_NUM_PORTS ];
static uint8_t doubleSpeed[ SPI_NUM_PORTS ];


/******************************************************************************
                                Local Functions
******************************************************************************/
/*****************************************************************************/
/* Adapted from SPI.h in Arduino SPI library */
static void
SPI_calcDivider( SPI_Port_t port )
{
    uint32_t clockFreq = portDescriptors[port].clockFreq;
    uint8_t clockDiv;

    if ( clockFreq >= F_CPU / 2 ) {
        clockDiv = 0;
    } else if ( clockFreq >= F_CPU / 4 ) {
        clockDiv = 1;
    } else if ( clockFreq >= F_CPU / 8 ) {
        clockDiv = 2;
    } else if ( clockFreq >= F_CPU / 16 ) {
        clockDiv = 3;
    } else if ( clockFreq >= F_CPU / 32 ) {
        clockDiv = 4;
    } else if ( clockFreq >= F_CPU / 64 ) {
        clockDiv = 5;
    } else {
        clockDiv = 7;
    }

    clockDiv ^= 0x1;

    rateSel[port] = clockDiv >> 1;
    doubleSpeed[port] = clockDiv;
}


/******************************************************************************
                                   Functions
******************************************************************************/
/*****************************************************************************/
void
SPI_init( void )
{
    int i;
    uint8_t csnPin;

    /* Set the SS pin as an output */
    pinMode( SS, OUTPUT );

    /* Initialize GPIOs for chip-selects */
    for ( i = 0; i < SPI_NUM_PORTS; i++ ) {
        csnPin = portDescriptors[i].csnPin;

        digitalWrite( csnPin, HIGH );
        pinMode( csnPin, OUTPUT );

        SPI_calcDivider( i );
    }

    SPCR = 0x00;
    SPCR |= BIT(MSTR);

    SPSR = 0x00;

    pinMode( SCK, OUTPUT );
    pinMode( MOSI, OUTPUT );
}


/*****************************************************************************/
void
SPI_startTransaction( SPI_Port_t port )
{
    SPI_Mode_t mode;

    ASSERT( port < DIM(portDescriptors) );

    mode = portDescriptors[port].mode;

    /* Setup SPI hardware for this port */
    SPSR |= (doubleSpeed[port] << SPI2X) & BIT(SPI2X);
    SPCR |= (rateSel[port] << SPR0) & (BIT(SPR1)|BIT(SPR0));
    SPCR |= (mode << CPHA) & (BIT(CPOL)|BIT(CPHA)) ;
    SPCR |= BIT(SPE);

    /* Assert chip-select */
    digitalWrite( portDescriptors[port].csnPin, LOW );
}


/*****************************************************************************/
void
SPI_endTransaction( SPI_Port_t port )
{
    ASSERT( port < DIM(portDescriptors) );

    /* De-assert chip-select */
    digitalWrite( portDescriptors[port].csnPin, HIGH );

    /* Disable SPI hardware */
    SPCR &= ~( BIT(SPE) );
}


/*****************************************************************************/
void
SPI_transfer( void* buffer, size_t length )
{
    size_t i;
    uint8_t* b = (uint8_t*)buffer;

    for ( i = 0; i < length; i++ ) {
        SPDR = b[i];
        while (!(SPSR & BIT(SPIF)));
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
