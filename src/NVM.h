/**
 * EEPROM.h - EEPROM drivers for the OBD-Dos platform
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

#ifndef _NVM_H_
#define _NVM_H_

#include <stdint.h>

#include "Error.h"
#include "GPS.h"

/******************************************************************************
                                     Types
******************************************************************************/
/*****************************************************************************/
enum {
    NVM_RESET_REASON_NORMAL  = 0x00,
    NVM_RESET_REASON_ERROR   = 0x01,
};

typedef uint8_t NVM_ResetReason_t;


/******************************************************************************
                                   Functions
******************************************************************************/
/*****************************************************************************/
void
NVM_setResetReason( NVM_ResetReason_t reason );

/*****************************************************************************/
bool
NVM_getResetReason( NVM_ResetReason_t* reason );

/*****************************************************************************/
void
NVM_setLastError( Error_t lastError );

/*****************************************************************************/
Error_t
NVM_getLastError( void );

/*****************************************************************************/
void
NVM_setNextGpsSample( GPS_TransitData_t* location );

/*****************************************************************************/
bool
NVM_getLastGpsSample( GPS_TransitData_t* location );


#endif /* _NVM_H_ */
