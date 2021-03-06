/**
 * LED.h - LED drivers for the OBD-Dos platform
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

#ifndef _LED_H_
#define _LED_H_

/******************************************************************************
                                     Types
******************************************************************************/
/*****************************************************************************/
typedef enum {
    LED_ID_STATUS  = 0,
    LED_ID_ERROR,

    LED_NUM_OF_COLORS,
} LED_Id_t;


/******************************************************************************
                                   Functions
******************************************************************************/
/*****************************************************************************/
void
LED_init( void );

/*****************************************************************************/
void
LED_allOff( void );

/*****************************************************************************/
void
LED_turnOn( LED_Id_t id );

/*****************************************************************************/
void
LED_turnOff( LED_Id_t id );

/*****************************************************************************/
void
LED_blink( LED_Id_t id, uint32_t durationMs );

/*****************************************************************************/
void
LED_toggle( LED_Id_t id );


#endif /* _LED_H_ */
