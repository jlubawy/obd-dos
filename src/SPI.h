/**
 * SPI.h - SPI drivers for the OBD-Dos platform
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

#ifndef _SPI_H_
#define _SPI_H_

#include <stdint.h>
#include <stdlib.h>

/******************************************************************************
                                     Types
******************************************************************************/
/*****************************************************************************/
enum {
    SPI_PORT_CAN_BUS,

    SPI_NUM_PORTS,
};

typedef int SPI_Port_t;

/*****************************************************************************/
/* polarity + phase */
typedef enum {
    SPI_MODE_0,
    SPI_MODE_1,
    SPI_MODE_2,
    SPI_MODE_3,
} SPI_Mode_t;

/*****************************************************************************/
typedef uint32_t SPI_ClockSpeed_t;

/******************************************************************************
                                   Functions
******************************************************************************/
/*****************************************************************************/
void
SPI_init( void );

/*****************************************************************************/
void
SPI_startTransaction( SPI_Port_t port );

/*****************************************************************************/
void
SPI_endTransaction( SPI_Port_t port );

/*****************************************************************************/
void
SPI_transfer( void* buffer, size_t length );

/*****************************************************************************/
void
SPI_sendByte( uint8_t data );

/*****************************************************************************/
uint8_t
SPI_receiveByte( void );


#endif /* _SPI_H_ */
