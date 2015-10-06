/**
 * MainLoop.cpp - Main application loop for the OBD-Dos platform
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

#include "GPS.h"
#include "OBD.h"
#include "Serial.h"
#include "WDT.h"

/******************************************************************************
                                     Types
******************************************************************************/
/*****************************************************************************/

/******************************************************************************
                                Local Variables
******************************************************************************/
/*****************************************************************************/

/******************************************************************************
                                   Functions
******************************************************************************/
/*****************************************************************************/
void
setup( void )
{
    WDT_init();

    Serial_init();
    GPS_init();
    OBD_init();

    OBD_requestVin( NULL );

    /* Start the watchdog timer */
    WDT_enable( WDT_TIMEOUT_MAX );
}


/*****************************************************************************/
void
loop( void )
{
    WDT_reset(); /* reset the WDT in every loop to prevent system reset */
}
