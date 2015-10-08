/**
 * EEPROM.cpp - EEPROM drivers for the OBD-Dos platform
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
#include "EEPROM.h"
#include "Utility.h"

/******************************************************************************
                                    Defines
******************************************************************************/
/*****************************************************************************/


/******************************************************************************
                                     Macros
******************************************************************************/
/*****************************************************************************/


/******************************************************************************
                                     Types
******************************************************************************/
/*****************************************************************************/


/******************************************************************************
                                Local Variables
******************************************************************************/
/*****************************************************************************/


/******************************************************************************
                                Local Functions
******************************************************************************/
/*****************************************************************************/


/******************************************************************************
                                   Functions
******************************************************************************/
/*****************************************************************************/
uint8_t
EEPROM_readByte( uint16_t address )
{
    uint8_t sreg;
    uint8_t data;

    ASSERT( address >= EEPROM_ADDRESS_MIN );
    ASSERT( address < EEPROM_ADDRESS_MAX );

    sreg = CRITICAL_SECTION_ENTER();

    /* Wait for completion of previous write */
    while ( EECR & BIT(EEPE) );
    /* Set address register */
    EEAR = address;
    /* Start eeprom read by writing EERE */
    EECR |= BIT(EERE);
    /* Read data */
    data = EEDR;

    CRITICAL_SECTION_EXIT( sreg );

    return data;
}


/*****************************************************************************/
bool
EEPROM_writeByte( uint16_t address, uint8_t data )
{
    uint8_t sreg;
    uint8_t oldData;
    uint8_t diffMask;
    uint8_t mode;
    bool cycleUsed = true;

    ASSERT( address >= EEPROM_ADDRESS_MIN );
    ASSERT( address < EEPROM_ADDRESS_MAX );

    sreg = CRITICAL_SECTION_ENTER();

    oldData = EEPROM_readByte( address );
    diffMask = data ^ oldData;

    if ( data & diffMask ) {
        /* Need to erase */

        if ( data == 0xFF ) {
            /* No need to program */
            mode = 1; /* erase only */
        } else {
            /* Need to program */
            mode = 0; /* erase and program */
        }
    } else {
        /* No need to erase */

        if ( diffMask ) {
            /* Need to program */
            mode = 2; /* program only */
        } else {
            /* No need to program */
            cycleUsed = false;
            goto WRITE_DONE; /* no erase, no program */
        }
    }

    /* Wait for completion of previous write */
    while ( EECR & BIT(EEPE) );
    /* Set address and data registers */
    EEAR = address;
    EEDR = data;
    /* Set mode and master program enable */
    EECR |= (mode << EEPM0) | BIT(EEMPE);
    /* Start write */
    EECR |= BIT(EEPE);

WRITE_DONE:
    CRITICAL_SECTION_EXIT( sreg );

    return cycleUsed;
}


/*****************************************************************************/
void
EEPROM_read( uint16_t address, void* buf, size_t size )
{
    size_t i;

    for ( i = 0; i < size; i++ ) {
        ((uint8_t *)buf)[i] = EEPROM_readByte( address + i );
    }
}


/*****************************************************************************/
void
EEPROM_write( uint16_t address, void* buf, size_t size )
{
    size_t i;

    for ( i = 0; i < size; i++ ) {
        EEPROM_writeByte( address + i, ((uint8_t *)buf)[i] );
    }
}
