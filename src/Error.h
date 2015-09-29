/**
 * Error.h - Error functions for the OBD-Dos platform
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

#ifndef _ERROR_H_
#define _ERROR_H_

#include <stdint.h>

/******************************************************************************
                                     Types
******************************************************************************/
/*****************************************************************************/
enum {
    SUCCESS        = 0,
    ERROR_FAILURE  = 1,
    ERROR_ASSERT   = 2,
};

typedef uint8_t Error_t;


/******************************************************************************
                                   Functions
******************************************************************************/
/*****************************************************************************/
void
Error_halt( Error_t code );

/*****************************************************************************/
void
Error_reset( Error_t code );


#endif /* _ERROR_H_ */
