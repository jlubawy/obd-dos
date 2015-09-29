/**
 * Serial.h - UART drivers for the OBD-Dos platform
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

#ifndef _SERIAL_H_
#define _SERIAL_H_

#include <stdio.h>

#include <avr/pgmspace.h>

#include <Arduino.h>

/******************************************************************************
                                   Functions
******************************************************************************/
/*****************************************************************************/
void
Serial_init( void );

/*****************************************************************************/
void
Serial_flush( void );

/*****************************************************************************/
void
Serial_write( const char c );

/*****************************************************************************/
#define Serial_printf( fmt, ... ) { \
    printf_P( PSTR(fmt), __VA_ARGS__ ); \
    Serial_flush(); \
}


#endif /* _SERIAL_H_ */
