/**
 *  File Name : CAN_mcp2515.h
 *     Author : Josh Lubawy <jlubawy@gmail.com>
 *                          <jlubawy@asu.edu>
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
