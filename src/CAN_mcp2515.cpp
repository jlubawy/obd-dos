/**
 * CAN_mcp2515.cpp - Hardware drivers for the MCP2515 CAN bus controller
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

#include "CAN_mcp2515.h"
#include "SPI.h"

/******************************************************************************
                                     Macros
******************************************************************************/
/*****************************************************************************/
#define CAN_MCP2515_INST_START( _inst ) { \
    SPI_startTransaction( SPI_PORT_CAN_BUS ); \
    SPI_sendByte( CAN_MCP2515_INST_ ## _inst ); \
}

#define CAN_MCP2515_INST_STOP()  SPI_endTransaction( SPI_PORT_CAN_BUS )


/******************************************************************************
                                     Types
******************************************************************************/
/*****************************************************************************/
typedef enum {
    CAN_MCP2515_INST_RESET             = 0xC0,
    CAN_MCP2515_INST_READ              = 0x03,
    CAN_MCP2515_INST_READ_RX_BUFFER_0  = 0x90,
    CAN_MCP2515_INST_READ_RX_BUFFER_1  = 0x92,
    CAN_MCP2515_INST_READ_RX_BUFFER_2  = 0x94,
    CAN_MCP2515_INST_READ_RX_BUFFER_3  = 0x96,
    CAN_MCP2515_INST_WRITE             = 0x02,
    CAN_MCP2515_INST_LOAD_TX_BUFFER_0  = 0x40,
    CAN_MCP2515_INST_LOAD_TX_BUFFER_1  = 0x41,
    CAN_MCP2515_INST_LOAD_TX_BUFFER_2  = 0x42,
    CAN_MCP2515_INST_LOAD_TX_BUFFER_3  = 0x43,
    CAN_MCP2515_INST_LOAD_TX_BUFFER_4  = 0x44,
    CAN_MCP2515_INST_LOAD_TX_BUFFER_5  = 0x45,
    CAN_MCP2515_INST_RTS_TXB0          = 0x81,
    CAN_MCP2515_INST_RTS_TXB1          = 0x82,
    CAN_MCP2515_INST_RTS_TXB2          = 0x83,
    CAN_MCP2515_INST_READ_STATUS       = 0xA0,
    CAN_MCP2515_INST_RX_STATUS         = 0xB0,
    CAN_MCP2515_INST_BIT_MODIFY        = 0x05,
} CAN_Mcp2515_Inst_t;

/*****************************************************************************/
typedef enum {
    CAN_MCP2515_REG_BFPCTRL    = 0x0C,
    CAN_MCP2515_REG_TXRTSCTRL  = 0x0D,
    CAN_MCP2515_REG_CANSTAT    = 0x0E,
    CAN_MCP2515_REG_CANCTRL    = 0x0F,
    CAN_MCP2515_REG_TEC        = 0x1C,
    CAN_MCP2515_REG_REC        = 0x1D,
    CAN_MCP2515_REG_CNF3       = 0x28,
    CAN_MCP2515_REG_CNF2       = 0x29,
    CAN_MCP2515_REG_CNF1       = 0x2A,
    CAN_MCP2515_REG_CANINTE    = 0x2B,
    CAN_MCP2515_REG_CANINTF    = 0x2C,
    CAN_MCP2515_REG_EFLG       = 0x2D,
    CAN_MCP2515_REG_TXB0CTRL   = 0x30,
    CAN_MCP2515_REG_TXB1CTRL   = 0x40,
    CAN_MCP2515_REG_TXB2CTRL   = 0x50,
    CAN_MCP2515_REG_RXB0CTRL   = 0x60,
    CAN_MCP2515_REG_RXB1CTRL   = 0x70,
} CAN_Mcp2515_Reg_t;


/******************************************************************************
                                Local Variables
******************************************************************************/
/*****************************************************************************/


/******************************************************************************
                                   Functions
******************************************************************************/
/*****************************************************************************/
void
CAN_mcp2515_init( void )
{
}


/*****************************************************************************/
void
CAN_mcp2515_instReset( void )
{
    CAN_MCP2515_INST_START( RESET );
    CAN_MCP2515_INST_STOP();
}


/*****************************************************************************/
void
CAN_mcp2515_instRead( uint8_t address, uint8_t* buffer, size_t length )
{
    int i;

    CAN_MCP2515_INST_START( READ );

    SPI_sendByte( address );

    for ( i = 0; i < length; i++ ) {
        buffer[i] = SPI_receiveByte();
    }

    CAN_MCP2515_INST_STOP();
}


/*****************************************************************************/
void
CAN_mcp2515_instWrite( uint8_t address, uint8_t* buffer, size_t length )
{
    int i;

    CAN_MCP2515_INST_START( WRITE );

    SPI_sendByte( address );

    for ( i = 0; i < length; i++ ) {
        SPI_sendByte( buffer[i] );
    }

    CAN_MCP2515_INST_STOP();
}


/*****************************************************************************/
CAN_Mcp2515_OperatingMode_t
CAN_mcp2515_getOperatingMode( void )
{
    uint8_t data = 0x00;
    CAN_mcp2515_instRead( CAN_MCP2515_REG_CANSTAT, &data, sizeof(data) );
    return (CAN_Mcp2515_OperatingMode_t)((data >> 5) & 0x7);
}


/*****************************************************************************/
void
CAN_mcp2515_setOperatingMode( CAN_Mcp2515_OperatingMode_t mode )
{
    uint8_t data = (mode & 0x7) << 5;
    CAN_mcp2515_instWrite( CAN_MCP2515_REG_CANCTRL, &data, sizeof(data) );
}
