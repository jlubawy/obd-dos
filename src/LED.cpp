/**
 * LED.cpp - LED drivers for the OBD-Dos platform
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

#include <stdint.h>

#include <Arduino.h>

#include "Assert.h"
#include "Delay.h"
#include "LED.h"

/******************************************************************************
                                     Types
******************************************************************************/
/*****************************************************************************/
typedef enum {
    LED_OFF  = LOW,
    LED_ON   = HIGH,
} LED_State_t;

/*****************************************************************************/
typedef struct {
    LED_Id_t    id;
    uint8_t     pin;
    LED_State_t currentState;
} LED_Info_t;


/******************************************************************************
                                Local Variables
******************************************************************************/
/*****************************************************************************/
static const LED_Info_t ledInfo[ LED_NUM_OF_COLORS ] = {
    { LED_ID_STATUS, 7, LED_OFF },
    { LED_ID_ERROR,  8, LED_OFF },
};

/*****************************************************************************/
static const unsigned int ledInfoCount = sizeof(ledInfo) / sizeof(ledInfo[0]);

/*****************************************************************************/
static LED_State_t ledStates[ LED_NUM_OF_COLORS ];


/******************************************************************************
                                   Functions
******************************************************************************/
/*****************************************************************************/
void
LED_init( void )
{
    LED_allOff();
}


/*****************************************************************************/
void
LED_allOff( void )
{
    int i;

    for ( i = 0; i < ledInfoCount; i++ ) {
        pinMode( ledInfo[i].pin, OUTPUT );
        ledStates[i] = LED_OFF;
        digitalWrite( ledInfo[i].pin, LED_OFF );
    }
}


/*****************************************************************************/
void
LED_turnOn( LED_Id_t color )
{
    ASSERT( color < ledInfoCount );

    ledStates[color] = LED_ON;
    digitalWrite( ledInfo[color].pin, LED_ON );
}


/*****************************************************************************/
void
LED_turnOff( LED_Id_t color )
{
    ASSERT( color < ledInfoCount );

    ledStates[color] = LED_OFF;
    digitalWrite( ledInfo[color].pin, LED_OFF );
}


/*****************************************************************************/
void
LED_blink( LED_Id_t color, uint32_t durationMs )
{
    LED_turnOn( color );
    Delay_ms( durationMs );
    LED_turnOff( color );
}


/*****************************************************************************/
void
LED_toggle( LED_Id_t color )
{
    ASSERT( color < ledInfoCount );

    ledStates[color] = ( LED_ON == ledStates[color] ) ? LED_OFF : LED_ON;
    digitalWrite( ledInfo[color].pin, ledStates[color] );
}
