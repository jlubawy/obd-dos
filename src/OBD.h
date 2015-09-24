/**
 * OBD.cpp - OBD-II functions for the OBD-Dos platform
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

#ifndef _OBD_H_
#define _OBD_H_

/******************************************************************************
                                     Types
******************************************************************************/
typedef enum {
    OBD_SUPPORTED_PIDS_01_20,
    OBD_SUPPORTED_PIDS_21_40,
    OBD_SUPPORTED_PIDS_41_60,
    OBD_SUPPORTED_PIDS_61_80,
    OBD_SUPPORTED_PIDS_81_A0,
    OBD_SUPPORTED_PIDS_A1_C0,
    OBD_SUPPORTED_PIDS_C1_E0,
} OBD_Supported_PIDs_t;


/******************************************************************************
                                   Functions
******************************************************************************/
/*****************************************************************************/
void
OBD_init( void );


#endif /* _OBD_H_ */
