/**
 * CAN.h - CAN bus functions for the OBD-Dos platform
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

#ifndef _CAN_H_
#define _CAN_H_

#include <stdlib.h>

/******************************************************************************
                                     Types
******************************************************************************/
/*****************************************************************************/
typedef enum {
    CAN_ERROR_SUCCESS = 0,
} CAN_Error_t;

/*****************************************************************************/
typedef enum {
    CAN_OPMODE_NORMAL,
    CAN_OPMODE_LOOPBACK,
} CAN_OperatingMode_t;

/*****************************************************************************/
typedef void (*CAN_RxCallback_t)( uint32_t id,
                                  bool     isExtended );

/*****************************************************************************/
typedef void (*CAN_ErrorCallback_t)( CAN_Error_t errorType );


/******************************************************************************
                                   Functions
******************************************************************************/
/*****************************************************************************/
void
CAN_init( uint8_t* rxBuf,
          size_t   rxBufSize,
          CAN_RxCallback_t rxCallback,
          CAN_ErrorCallback_t errorCallback );

/*****************************************************************************/
void
CAN_reset( void );

/*****************************************************************************/
bool
CAN_sendStandardDataFrame( uint16_t id, void* buf, size_t size );

/*****************************************************************************/
bool
CAN_sendExtendedDataFrame( uint32_t id, void* buf, size_t size );

/*****************************************************************************/
void
CAN_setOperatingMode( CAN_OperatingMode_t mode );


#endif /* _CAN_H_ */
