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

#include "Assert.h"
#include "CAN.h"
#include "Event.h"
#include "GPS.h"
#include "OBD.h"
#include "Serial.h"
#include "SPI.h"
#include "WDT.h"

/******************************************************************************
                                     Types
******************************************************************************/
/*****************************************************************************/
enum {
    EVENT_GROUP_OBD,
};


/******************************************************************************
                                Local Variables
******************************************************************************/
/*****************************************************************************/
unsigned long green0 = 0UL;
unsigned long green1 = 500UL;


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


    SPI_init();
    CAN_init();

    uint8_t data = 0xCC;
    CAN_sendStandardDataFrame( 0x1234, &data, sizeof(data) );

    OBD_init();

    /* Initialize the event loop and start the watchdog timer */
    Event_init();
    WDT_enable( WDT_TIMEOUT_MAX );
}


/*****************************************************************************/
void
loop( void )
{
    Event_t event;
    EventId_t id;

    if ( event = Event_dequeue() ) {
        id = Event_getId( event );

        switch ( Event_getGroup( event ) ) {
            case EVENT_GROUP_OBD: {
                //OBD_event_handler( id );
                break;
            }

            default: {
                break;
            }
        }
    }

    WDT_reset(); /* reset the WDT in every loop to prevent system reset */
}
