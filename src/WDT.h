/**
 * WDT.h - Watchdog timer driver for the OBD-Dos platform
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

#ifndef _WDT_H_
#define _WDT_H_

#include <Arduino.h>

#include "Utility.h"

/******************************************************************************
                                    Defines
******************************************************************************/
/*****************************************************************************/
#define WDT_TIMEOUT_MAX  (BIT(WDP3)|BIT(WDP0))  /* ~8 seconds */
#define WDT_TIMEOUT_MIN  (0)                    /* ~16 ms */


/******************************************************************************
                                   Functions
******************************************************************************/
/*****************************************************************************/
void
WDT_init( void );

/*****************************************************************************/
void
WDT_enable( uint8_t timeout );

/*****************************************************************************/
void
WDT_disable( void );

/*****************************************************************************/
void
WDT_reset( void );

/*****************************************************************************/
void
WDT_forceSystemReset( void );


#endif /* _WDT_H_ */
