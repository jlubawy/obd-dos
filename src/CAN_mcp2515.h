/**
 * CAN_mcp2515.h - Hardware drivers for the MCP2515 CAN bus controller
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

#ifndef _CAN_MCP2515_H_
#define _CAN_MCP2515_H_

#include <stdint.h>
#include <stdlib.h>


/******************************************************************************
                                     Types
******************************************************************************/
/*****************************************************************************/
typedef enum {
    CAN_MCP2515_OPMODE_NORMAL  = 0,
    CAN_MCP2515_OPMODE_SLEEP,
    CAN_MCP2515_OPMODE_LOOPBACK,
    CAN_MCP2515_OPMODE_LISTEN_ONLY,
    CAN_MCP2515_OPMODE_CONFIGURATION,
} CAN_Mcp2515_OperatingMode_t;


/******************************************************************************
                                   Functions
******************************************************************************/
/*****************************************************************************/
void
CAN_mcp2515_init( void );

/*****************************************************************************/
void
CAN_mcp2515_instReset( void );

/*****************************************************************************/
void
CAN_mcp2515_instRead( uint8_t address, uint8_t* buffer, size_t length );

/*****************************************************************************/
void
CAN_mcp2515_instWrite( uint8_t address, uint8_t* buffer, size_t length );

/*****************************************************************************/
CAN_Mcp2515_OperatingMode_t
CAN_mcp2515_getOperatingMode( void );

/*****************************************************************************/
void
CAN_mcp2515_setOperatingMode( CAN_Mcp2515_OperatingMode_t mode );


#endif /* _CAN_MCP2515_H_ */
