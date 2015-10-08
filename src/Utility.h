/**
 * Utility.h - Utility macros for the OBD-Dos platform
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

#ifndef _UTILITY_H_
#define _UTILITY_H_

#include <stdint.h>

#include "Interrupts.h"

/******************************************************************************
                                     Macros
******************************************************************************/
/*****************************************************************************/
#define BIT( _n )  (1 << (_n))

/*****************************************************************************/
#define DIM( _array )  (sizeof((_array)) / sizeof((_array)[0]))

/*****************************************************************************/
#define CRITICAL_SECTION_ENTER()        Interrupts_criticalSectionEnter()
#define CRITICAL_SECTION_EXIT( _sreg )  Interrupts_criticalSectionExit(_sreg)

/*****************************************************************************/
#define REG8( _address )        Interrupts_criticalSectionEnter()

/*****************************************************************************/
#define PACKED_START
#define PACKED_END
#define PACKED()      (__attribute__ ((packed)))


#endif /* _UTILITY_H_ */
