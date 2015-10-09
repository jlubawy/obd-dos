/**
 * GPIO.h - GPIO functions for the OBD-Dos platform
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

#ifndef _GPIO_H_
#define _GPIO_H_

#include <stdint.h>

/******************************************************************************
                                     Types
******************************************************************************/
/*****************************************************************************/
enum {
    GPIO_ID_CAN_INT = 2,
};

typedef uint8_t GPIO_Id_t;

/*****************************************************************************/
typedef enum {
    GPIO_PULL_NONE,
    GPIO_PULL_UP,
} GPIO_Pull_t;

/*****************************************************************************/
typedef enum {
    GPIO_INT_NONE,
    GPIO_INT_RISING,
    GPIO_INT_FALLING,
} GPIO_Int_t;

/*****************************************************************************/
typedef void (*GPIO_Callback_t)(void);


/******************************************************************************
                                   Functions
******************************************************************************/
/*****************************************************************************/
void
GPIO_configInput( GPIO_Id_t       id,
                  GPIO_Pull_t     pullType,
                  GPIO_Int_t      intType,
                  GPIO_Callback_t callback );

/*****************************************************************************/
void
GPIO_configOutput( GPIO_Id_t id );

/*****************************************************************************/
void
GPIO_outputHigh( GPIO_Id_t id );

/*****************************************************************************/
void
GPIO_outputLow( GPIO_Id_t id );


#endif /* _GPIO_H_ */
