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

#include "Arduino.h"

#include "CAN_mcp2515.h"
#include "Event.h"
#include "Event_LED.h"
#include "Log.h"
#include "SPI.h"

/******************************************************************************
                                     Types
******************************************************************************/
/*****************************************************************************/
enum {
    EVENT_GROUP_LED,
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
    CAN_Mcp2515_OperatingMode_t mode;

    SPI_init();
    Log_init();

    Event_init();
    Event_LED_init();

    CAN_mcp2515_init();

    mode = CAN_mcp2515_getOperatingMode();
    Log_printf( "mode: 0x%02X\n", mode );
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
            case EVENT_GROUP_LED: {
                Event_LED_handler( id );
                break;
            }

            default: {
                break;
            }
        }
    }

    if ( (millis() - green0) > 500 ) {
        Event_enqueue( EVENT_GROUP_LED, EVENT_ID_LED_GREEN_0 );
        green0 = millis();
    }

    if ( (millis() - green1) > 500 ) {
        Event_enqueue( EVENT_GROUP_LED, EVENT_ID_LED_GREEN_1 );
        green1 = millis();
    }
}
