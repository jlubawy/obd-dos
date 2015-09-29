/**
 * GPIO.cpp - GPIO functions for the OBD-Dos platform
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

#include <stdlib.h>

#include <Arduino.h>

#include "Assert.h"
#include "GPIO.h"

/******************************************************************************
                                    Defines
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
                                   Functions
******************************************************************************/
/*****************************************************************************/
void
GPIO_init( void )
{}


/*****************************************************************************/
void
GPIO_configInput( GPIO_Id_t       id,
                  GPIO_Pull_t     pullType,
                  GPIO_Int_t      intType,
                  GPIO_Callback_t callback )
{
    pinMode( id, ( pullType == GPIO_PULL_NONE ) ? INPUT : INPUT_PULLUP );

    if ( intType != GPIO_INT_NONE ) {
        ASSERT( callback != NULL );
        attachInterrupt( digitalPinToInterrupt(id), callback, intType );
    }
}


/*****************************************************************************/
void
GPIO_configOutput( GPIO_Id_t id )
{
    pinMode( id, OUTPUT );
}


/*****************************************************************************/
void
GPIO_outputHigh( GPIO_Id_t id )
{
    digitalWrite( id, HIGH );
}


/*****************************************************************************/
void
GPIO_outputLow( GPIO_Id_t id )
{
    digitalWrite( id, LOW );
}
