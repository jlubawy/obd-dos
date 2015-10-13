/**
 * CAN.cpp - CAN bus functions for the OBD-Dos platform
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
#include <stdlib.h>

#include "CAN.h"
#include "CAN_mcp2515.h"

/******************************************************************************
                                     Types
******************************************************************************/
/*****************************************************************************/


/******************************************************************************
                                Local Variables
******************************************************************************/
/*****************************************************************************/
static CAN_RxCallback_t CAN_rxCallback;

/*****************************************************************************/
static CAN_ErrorCallback_t CAN_errorCallback;


/******************************************************************************
                                Local Functions
******************************************************************************/
/*****************************************************************************/
static void
CAN_mcp2515_rxCallback( uint32_t id, bool isExtended )
{
    if ( CAN_rxCallback ) {
        CAN_rxCallback( id, isExtended );
    }
}


/*****************************************************************************/
static void
CAN_mcp2515_errorCallback( CAN_Mcp2515_Error_t errorType )
{
    /* TODO: interpret error code */
    if ( CAN_errorCallback ) {
        CAN_errorCallback( CAN_ERROR_SUCCESS );
    }
}


/******************************************************************************
                                   Functions
******************************************************************************/
/*****************************************************************************/
void
CAN_init( uint8_t* rxBuf,
          size_t   rxBufSize,
          CAN_RxCallback_t rxCallback,
          CAN_ErrorCallback_t errorCallback )
{
    CAN_rxCallback = rxCallback;
    CAN_errorCallback = errorCallback;

    CAN_mcp2515_init( rxBuf,
                      rxBufSize,
                      CAN_mcp2515_rxCallback,
                      CAN_mcp2515_errorCallback );
}


/*****************************************************************************/
void
CAN_reset( void )
{
    /* Reset and re-init the CAN controller hardware */
    CAN_mcp2515_reset();
}


/*****************************************************************************/
bool
CAN_sendStandardDataFrame( uint16_t id, void* buf, size_t size )
{
    return CAN_mcp2515_sendStandardDataFrame( id, buf, size );
}


/*****************************************************************************/
bool
CAN_sendExtendedDataFrame( uint32_t id, void* buf, size_t size )
{
    return CAN_mcp2515_sendExtendedDataFrame( id, buf, size );
}


/*****************************************************************************/
void
CAN_setOperatingMode( CAN_OperatingMode_t mode )
{
    if ( mode == CAN_OPMODE_NORMAL ) {
        CAN_mcp2515_setOperatingMode( CAN_MCP2515_OPMODE_NORMAL );
    } else if ( mode == CAN_OPMODE_LOOPBACK ) {
        CAN_mcp2515_setOperatingMode( CAN_MCP2515_OPMODE_LOOPBACK );
    }
}

