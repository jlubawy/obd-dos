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
                                    Defines
******************************************************************************/
/*****************************************************************************/
/**
 * CANSTAT (0x0E)
 */
#define bsOPMOD2  (7)
#define bsOPMOD1  (6)
#define bsOPMOD0  (5)
#define bsICOD2   (3)
#define bsICOD1   (2)
#define bsICOD0   (1)

#define bmOPMOD  (_BV(bsOPMOD2)|_BV(bsOPMOD1)|_BV(bsOPMOD0))
#define bmICOD   (_BV(bsICOD2)|_BV(bsICOD1)|_BV(bsICOD0))

/*****************************************************************************/
/**
 * CANCTRL (0x0F)
 */
#define bsREQOP2   (7)
#define bsREQOP1   (6)
#define bsREQOP0   (5)
#define bsABAT     (4)
#define bsOSM      (3)
#define bsCLKEN    (2)
#define bsCLKPRE1  (1)
#define bsCLKPRE0  (0)

#define bmREQOP   (_BV(bsREQOP2)|_BV(bsREQOP1)|_BV(bsREQOP0))
#define bmABAT    (_BV(bsABAT))
#define bmOSM     (_BV(bsOSM))
#define bmCLKEN   (_BV(bsCLKEN))
#define bmCLKPRE  (_BV(bsCLKPRE1)|_BV(bsCLKPRE0)


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
