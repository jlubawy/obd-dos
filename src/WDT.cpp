/**
 * WDT.cpp - Watchdog timer driver for the OBD-Dos platform
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

#include <avr/wdt.h>

#include "WDT.h"

/******************************************************************************
                                   Functions
******************************************************************************/
/*****************************************************************************/
void
WDT_init( void )
{
    WDT_disable();
}


/*****************************************************************************/
void
WDT_enable( uint8_t timeout )
{
    uint8_t sreg = CRITICAL_SECTION_ENTER();
    wdt_reset();
    MCUSR &= ~BIT(WDRF);
    WDTCSR |= BIT(WDCE)|BIT(WDE);
    WDTCSR = BIT(WDE)|(timeout);
    CRITICAL_SECTION_EXIT(sreg);
}


/*****************************************************************************/
void
WDT_disable( void )
{
    uint8_t sreg = CRITICAL_SECTION_ENTER();
    wdt_reset();
    MCUSR &= ~BIT(WDRF);
    WDTCSR |= BIT(WDCE)|BIT(WDE);
    WDTCSR = 0;
    CRITICAL_SECTION_EXIT(sreg);
}


/*****************************************************************************/
void
WDT_reset( void )
{
    wdt_reset();
}


/*****************************************************************************/
void
WDT_forceSystemReset( void )
{
    WDT_enable( WDT_TIMEOUT_MIN );
    while (1);  /* wait for system reset */
}
