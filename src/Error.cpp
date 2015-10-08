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
#include "NVM.h"
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
    /* Long pause */
    Delay_ms( ERROR_LONG_BLINK_MS );

    /* Blink fast */
    for ( code = code + 1; code > 0; code-- ) {
        LED_turnOn( LED_ID_ERROR );
        Delay_ms( ERROR_SHORT_BLINK_MS );
        LED_turnOff( LED_ID_ERROR );
        Delay_ms( ERROR_SHORT_BLINK_MS );

        /* Reset watchdog */
        WDT_reset();
    }
}


/******************************************************************************
                                   Functions
******************************************************************************/
/*****************************************************************************/
void
Error_halt( Error_t code )
{
    /* Set watchdog to max timeout */
    WDT_enable( WDT_TIMEOUT_MAX );

    LED_allOff();

    /* Blink the error code (+1) in the following sequence:
     *    long pause -> blink fast -> long pause -> ... */
    while (1) {
        Error_blinkCode( code );
    }
}


/*****************************************************************************/
void
Error_reset( Error_t code )
{
    NVM_setResetReason( NVM_RESET_REASON_ERROR );
    NVM_setLastError( code );

    /* Force a system reset */
    WDT_forceSystemReset();
}

