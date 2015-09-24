/**
 * OBD.cpp - OBD-II functions for the OBD-Dos platform
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

#include "OBD.h"

/******************************************************************************
                                     Types
******************************************************************************/
/*****************************************************************************/
/* Source: https://en.wikipedia.org/wiki/OBD-II_PIDs#Modes */
typedef enum {
    OBD_MODE_SHOW_CURRENT_DATA                   = 0x01,
    OBD_MODE_SHOW_FREEZE_FRAME_DATA              = 0x02,
    OBD_MODE_SHOW_DIAGNOSTIC_TROUBLE_CODES       = 0x03,
    OBD_MODE_CLEAR_DIAGNOSTIC_TROUBLE_CODES      = 0x04,
    OBD_MODE_OXYGEN_SENSOR_TEST_RESULTS          = 0x05,
    OBD_MODE_OTHER_TEST_RESULTS                  = 0x06,
    OBD_MODE_SHOW_PENDING_TROUBLE_CODES          = 0x07,
    OBD_MODE_COMPONENT_CONTROL                   = 0x08,
    OBD_MODE_REQUEST_VEHICLE_INFORMATION         = 0x09,
    OBD_MODE_PERMANENT_DIAGNOSTIC_TROUBLE_CODES  = 0x0A,
} OBD_Mode_t;


/******************************************************************************
                                Local Variables
******************************************************************************/
/*****************************************************************************/


/******************************************************************************
                                   Functions
******************************************************************************/
/*****************************************************************************/
void
OBD_init( void )
{

}


/*****************************************************************************/
void
OBD_getSupportedPids( OBD_Supported_PIDs_t pid )
{

}
