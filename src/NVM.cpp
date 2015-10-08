/**
 * NVM.cpp - Non-volatile memory drivers for the OBD-Dos platform
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

#include <stddef.h>

#include "EEPROM.h"
#include "Error.h"
#include "NVM.h"
#include "Utility.h"

/******************************************************************************
                                    Defines
******************************************************************************/
/*****************************************************************************/
/* The goal is to have the EEPROM last 10 years:
 *     10 yrs = 5,256,000 mins
 *     @ 1 sample / 5 mins this is 1,051,200 total samples
 *     @ 100,000 samples / EEPROM cell
 *     we end up needing to rotate through about 10 samples
 */
#define NVM_NUM_OF_GPS_SAMPLES  (10)


/******************************************************************************
                                     Macros
******************************************************************************/
/*****************************************************************************/


/******************************************************************************
                                     Types
******************************************************************************/
/*****************************************************************************/
enum {
    NVM_ADDR_RESET_REASON  = 0,
    NVM_ADDR_LAST_ERROR    = NVM_ADDR_RESET_REASON + sizeof(NVM_ResetReason_t),
    NVM_ADDR_GPS_SAMPLES   = NVM_ADDR_LAST_ERROR   + sizeof(Error_t),
};

/*****************************************************************************/
PACKED_START
typedef struct PACKED {
    uint8_t           valid;
    GPS_TransitData_t transitData;
} NVM_GpsSample_t;
PACKED_END


/******************************************************************************
                                Local Variables
******************************************************************************/
/*****************************************************************************/


/******************************************************************************
                                Local Functions
******************************************************************************/
/*****************************************************************************/
static bool
NVM_getLastGpsSampleAddress( uint16_t* address )
{
    size_t i;
    uint8_t valid;

    /* Find the first valid byte */
    for ( i = 0; i < NVM_NUM_OF_GPS_SAMPLES; i++ ) {
        *address = NVM_ADDR_GPS_SAMPLES + (i * sizeof(NVM_GpsSample_t));
        EEPROM_read( *address + offsetof(NVM_GpsSample_t, valid),
                     &valid,
                     sizeof(valid) );

        if ( valid == 1 ) {
            /* valid sample found */
            return true;
        }
    }

    /* no valid sample found */
    return false;
}


/*****************************************************************************/
static uint16_t
NVM_getNextGpsSampleAddress( void )
{
    uint16_t lastAddress;
    uint16_t nextOffset;
    bool lastValid = NVM_getLastGpsSampleAddress( &lastAddress );

    /* If there was no valid sample then start at the first */
    if ( lastValid == false ) {
        return NVM_ADDR_GPS_SAMPLES;
    }

    /* Otherwise calculate the next address and offset */
    nextOffset = ( lastAddress + sizeof(NVM_GpsSample_t) )
                    % ( NVM_NUM_OF_GPS_SAMPLES * sizeof(NVM_GpsSample_t) );

    return NVM_ADDR_GPS_SAMPLES + nextOffset;
}


/******************************************************************************
                                   Functions
******************************************************************************/
/*****************************************************************************/
void
NVM_setResetReason( NVM_ResetReason_t reason )
{
    uint8_t validReason = BIT(7) | reason; /* set the valid bit */
    EEPROM_write( NVM_ADDR_RESET_REASON, &validReason, sizeof(validReason) );
}


/*****************************************************************************/
bool
NVM_getResetReason( NVM_ResetReason_t* reason )
{
    NVM_ResetReason_t rawReason;

    EEPROM_read( NVM_ADDR_RESET_REASON, &rawReason, sizeof(rawReason) );

    *reason = rawReason & (0x7F);
    return ((rawReason & 0x80) == 0x80);  /* is valid? */
}


/*****************************************************************************/
void
NVM_setLastError( Error_t lastError )
{
    EEPROM_write( NVM_ADDR_LAST_ERROR, &lastError, sizeof(lastError) );
}


/*****************************************************************************/
Error_t
NVM_getLastError( void )
{
    Error_t lastError;
    EEPROM_read( NVM_ADDR_LAST_ERROR, &lastError, sizeof(lastError) );
    return lastError;
}


/*****************************************************************************/
void
NVM_setNextGpsSample( GPS_TransitData_t* transitData )
{
    uint16_t lastAddress;
    uint16_t nextAddress = NVM_getNextGpsSampleAddress();
    bool lastValid = NVM_getLastGpsSampleAddress( &lastAddress );
    uint8_t valid = 1;
    uint8_t invalid = 0;

    /* Invalidate the last GPS sample if there was one */
    if ( lastValid ) {
        EEPROM_write( lastAddress + offsetof(NVM_GpsSample_t, valid),
                      &invalid,
                      sizeof(invalid) );
    }

    /* Write the next GPS sample */
    EEPROM_write( nextAddress + offsetof(NVM_GpsSample_t, valid),
                  &valid,
                  sizeof(valid) );

    EEPROM_write( nextAddress + offsetof(NVM_GpsSample_t, transitData),
                  transitData,
                  sizeof(GPS_TransitData_t) );
}


/*****************************************************************************/
bool
NVM_getLastGpsSample( GPS_TransitData_t* transitData )
{
    uint16_t lastAddress;
    bool lastValid = NVM_getLastGpsSampleAddress( &lastAddress );

    if ( lastValid == false ) {
        return false;
    }

    EEPROM_read( lastAddress + offsetof(NVM_GpsSample_t, transitData),
                 transitData,
                 sizeof(GPS_TransitData_t) );

    return true;
}
