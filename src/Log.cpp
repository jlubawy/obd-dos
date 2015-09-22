/**
 * Log.cpp - UART logging functions for the OBD-Dos platform
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

#include "Log.h"

/******************************************************************************
                                Local Variables
******************************************************************************/
static FILE uartout = {0};


/******************************************************************************
                                Local Functions
******************************************************************************/
/*****************************************************************************/
static int uart_putchar(char c, FILE* stream)
{
    Serial.write(c);
    return 0 ;
}


/******************************************************************************
                                   Functions
******************************************************************************/
/*****************************************************************************/
void
Log_init()
{
    fdev_setup_stream(&uartout, uart_putchar, NULL, _FDEV_SETUP_WRITE);
    Serial.begin(115200, SERIAL_8N1);
    stdout = &uartout;
}


/*****************************************************************************/
void
Log_flush()
{
    Serial.flush();
}


/*****************************************************************************/
void Log_write(const char c)
{
    Serial.write(c);
}
