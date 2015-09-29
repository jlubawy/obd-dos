/**
 * Error.cpp - Error functions for the OBD-Dos platform
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

#include "Delay.h"
#include "Error.h"
#include "LED.h"
#include "WDT.h"

/******************************************************************************
                                    Defines
******************************************************************************/
/*****************************************************************************/
#define ERROR_LONG_BLINK_MS   (1000)
#define ERROR_SHORT_BLINK_MS  (500)


/******************************************************************************
                                Local Functions
******************************************************************************/
/*****************************************************************************/
static void
Error_blinkCode( Error_t code )
{
    /* 0->1 , 1->2, etc. */
    code = code + 1;

    do {
        LED_toggle( LED_GREEN_0 );
        Delay_ms( ERROR_SHORT_BLINK_MS );
        LED_toggle( LED_GREEN_0 );
        Delay_ms( ERROR_SHORT_BLINK_MS );
    } while ( code-- );
}


/******************************************************************************
                                   Functions
******************************************************************************/
/*****************************************************************************/
void
Error_halt( Error_t code )
{
    LED_allOff();

    /* Blink the error code (+1) in the following sequence:
     *    long pause -> blink fast -> long pause -> ... */
    while (1) {
        Delay_ms( ERROR_LONG_BLINK_MS );
        Error_blinkCode( code );
    }
}


/*****************************************************************************/
void
Error_reset( Error_t code )
{
    /* Force a system reset */
    WDT_forceSystemReset();
}

