/**
 *  File Name : SPI.h
 *     Author : Josh Lubawy <jlubawy@gmail.com>
 *                          <jlubawy@asu.edu>
 */

#ifndef _SPI_H_
#define _SPI_H_

#include <stdint.h>
#include <stdlib.h>

#include "Arduino.h"

/******************************************************************************
                                     Macros
******************************************************************************/
/*****************************************************************************/
#define SPI_CSN_ENTER()  digitalWrite( 10, LOW )
#define SPI_CSN_EXIT()   digitalWrite( 10, HIGH )


/******************************************************************************
                                     Types
******************************************************************************/
/*****************************************************************************/
typedef enum {
    SPI_MODE_0,
    SPI_MODE_1,
    SPI_MODE_2,
    SPI_MODE_3,
} SPI_Mode_t;

/*****************************************************************************/
typedef uint32_t SPI_ClockSpeed_t;

/******************************************************************************
                                   Functions
******************************************************************************/
/*****************************************************************************/
void
SPI_init( void );

/*****************************************************************************/
void
SPI_transfer( void* buffer, size_t length );

/*****************************************************************************/
void
SPI_sendByte( uint8_t data );

/*****************************************************************************/
uint8_t
SPI_receiveByte( void );


#endif /* _SPI_H_ */