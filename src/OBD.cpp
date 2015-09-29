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

#include <stdint.h>

#include "Assert.h"
#include "OBD.h"
#include "OBD_pids.h"

/******************************************************************************
                                    Defines
******************************************************************************/
/*****************************************************************************/
#define OBD_11BIT_FUNC_BCAST_ADDR  (0x7DF)

/*****************************************************************************/
#define OBD_29BIT_FUNC_BCAST_ID  (0x18DB33F1)

/*****************************************************************************/
#define OBD_DLC_NIBBLE  (8)  /* field must always be 8 for OBD */

/*****************************************************************************/
#define OBD_FRAME_TYPE_SINGLE       (0)
#define OBD_FRAME_TYPE_FIRST        (1)
#define OBD_FRAME_TYPE_CONSECUTIVE  (2)
#define OBD_FRAME_TYPE_FLOW         (3)

/*****************************************************************************/
#define OBD_FIRST_FRAME_INST_NEXT   (0)
#define OBD_FIRST_FRAME_INST_WAIT   (1)
#define OBD_FIRST_FRAME_INST_ABORT  (2)


/******************************************************************************
                                     Macros
******************************************************************************/
/*****************************************************************************/
#define OBD_BUILD_29BIT_PHYS_BCAST_ID( _dest )  ((0x18DA00F1)|((_dest) << 8))
#define OBD_IS_29BIT_PHYS_REPLY( _reply )       ((0x18DA == (((_reply) >> 16) & 0xFFFF)) && (0xF1 == (((_reply) >> 8) & 0xFF)))
#define OBD_GET_29BIT_PHYS_BCAST_SRC( _reply )  (((_reply) >> 8) & 0xFF)

/*****************************************************************************/
#define OBD_GET_FRAME_TYPE( _byte0 )  (_byte0 & 0xF)


/******************************************************************************
                                     Types
******************************************************************************/
/*****************************************************************************/
/* Source: https://en.wikipedia.org/wiki/OBD-II_PIDs#Modes */
typedef enum {
    OBD_MODE_01_SHOW_CURRENT_DATA                   = 0x01,
    OBD_MODE_02_SHOW_FREEZE_FRAME_DATA              = 0x02,
    OBD_MODE_03_SHOW_DIAGNOSTIC_TROUBLE_CODES       = 0x03,
    OBD_MODE_04_CLEAR_DIAGNOSTIC_TROUBLE_CODES      = 0x04,
    OBD_MODE_05_OXYGEN_SENSOR_TEST_RESULTS          = 0x05,
    OBD_MODE_06_OTHER_TEST_RESULTS                  = 0x06,
    OBD_MODE_07_SHOW_PENDING_TROUBLE_CODES          = 0x07,
    OBD_MODE_08_COMPONENT_CONTROL                   = 0x08,
    OBD_MODE_09_REQUEST_VEHICLE_INFORMATION         = 0x09,
    OBD_MODE_0A_PERMANENT_DIAGNOSTIC_TROUBLE_CODES  = 0x0A,
} OBD_Mode_t;

/*****************************************************************************/
typedef enum {
    OBD_SUPPORTED_PIDS_01_20,
    OBD_SUPPORTED_PIDS_21_40,
    OBD_SUPPORTED_PIDS_41_60,
    OBD_SUPPORTED_PIDS_61_80,
    OBD_SUPPORTED_PIDS_81_A0,
    OBD_SUPPORTED_PIDS_A1_C0,
    OBD_SUPPORTED_PIDS_C1_E0,
} OBD_Supported_PIDs_t;


/******************************************************************************
                                Local Variables
******************************************************************************/
/*****************************************************************************/
static uint8_t OBD_txBuffer[8];
static uint8_t OBD_rxBuffer[8];


/******************************************************************************
                                Local Functions
******************************************************************************/
/*****************************************************************************/
void
OBD_sendSingleFrameRequest( uint8_t* buffer, uint8_t size )
{
    uint8_t txBuffer[8];

    ASSERT( size <= 7 );

    txBuffer[0] = (size << 4) | (OBD_FRAME_TYPE_SINGLE);
}


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


/*****************************************************************************/
uint8_t
OBD_getVehicleSpeed( void )
{

}


/*****************************************************************************/
void
OBD_requestVin( void )
{
    uint8_t txBuffer[8];
    const uint8_t size = 2;

    txBuffer[0] = (size << 4) | (OBD_FRAME_TYPE_SINGLE);
    txBuffer[1] = OBD_MODE_09_REQUEST_VEHICLE_INFORMATION;
    txBuffer[2] = OBD_MODE_09_PID_VIN;


}
