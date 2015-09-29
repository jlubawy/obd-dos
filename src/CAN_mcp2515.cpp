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


/******************************************************************************
                                Local Variables
******************************************************************************/
/*****************************************************************************/


/******************************************************************************
                                Local Functions
******************************************************************************/
/*****************************************************************************/
uint8_t
CAN_mcp2515_readByte( uint8_t address )
{
    uint8_t data;

    CAN_mcp2515_instRead( address, &data, sizeof(data) );
    return data;
}


/*****************************************************************************/
void
CAN_mcp2515_writeByte( uint8_t address, uint8_t data )
{
    CAN_mcp2515_instWrite( address, &data, sizeof(data) );
}


/******************************************************************************
                                   Functions
******************************************************************************/
/*****************************************************************************/
void
CAN_mcp2515_init( void )
{
    CAN_mcp2515_writeByte( CAN_MCP2515_REG_BFPCTRL, 0 );
    CAN_mcp2515_writeByte( CAN_MCP2515_REG_TXRTSCTRL, 0 );
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
void
CAN_mcp2515_instBitModify( uint8_t address, uint8_t mask, uint8_t data )
{
    CAN_MCP2515_INST_START( BIT_MODIFY );

    SPI_sendByte( address );
    SPI_sendByte( mask );
    SPI_sendByte( data );

    CAN_MCP2515_INST_STOP();
}


/*****************************************************************************/
CAN_Mcp2515_OperatingMode_t
CAN_mcp2515_getOperatingMode( void )
{
    uint8_t data;

    CAN_mcp2515_instRead( CAN_MCP2515_REG_CANSTAT, &data, sizeof(data) );
    return (CAN_Mcp2515_OperatingMode_t)((data & bmOPMOD) >> bsOPMOD0);
}


/*****************************************************************************/
void
CAN_mcp2515_setOperatingMode( CAN_Mcp2515_OperatingMode_t mode )
{
    uint8_t data;

    CAN_mcp2515_instRead( CAN_MCP2515_REG_CANCTRL, &data, sizeof(data) );
    data &= ~bmOPMOD;
    data |= (mode << bsOPMOD0);
    CAN_mcp2515_instWrite( CAN_MCP2515_REG_CANCTRL, &data, sizeof(data) );
}


/*****************************************************************************/
void
CAN_mcp2515_disableInterrupts( void )
{
    CAN_mcp2515_writeByte( CAN_MCP2515_REG_CANINTE, 0 );
}


/*****************************************************************************/
void
CAN_mcp2515_enableInterrupts( uint8_t mask )
{
    CAN_mcp2515_writeByte( CAN_MCP2515_REG_CANINTE, mask );
}


/*****************************************************************************/
uint8_t
CAN_mcp2515_getInterruptFlags( void )
{
    return CAN_mcp2515_readByte( CAN_MCP2515_REG_CANINTF );
}


/*****************************************************************************/
uint8_t
CAN_mcp2515_getTxErrorCount( void )
{
    return CAN_mcp2515_readByte( CAN_MCP2515_REG_TEC );
}


/*****************************************************************************/
uint8_t
CAN_mcp2515_getRxErrorCount( void )
{
    return CAN_mcp2515_readByte( CAN_MCP2515_REG_REC );
}


/*****************************************************************************/
uint8_t
CAN_mcp2515_getErrorFlags( void )
{
    return CAN_mcp2515_readByte( CAN_MCP2515_REG_EFLG );
}

