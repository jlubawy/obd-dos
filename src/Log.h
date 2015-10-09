/**
 * Log.h - Logging functions for the OBD-Dos platform
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

#ifndef _LOG_H_
#define _LOG_H_

#include "Serial.h"

/******************************************************************************
                                     Macros
******************************************************************************/
/*****************************************************************************/
#define OBD_LOG_ENABLE
#if defined( OBD_LOG_ENABLE )
#define Log_printf( _fmt, ... )  (Serial_printf( "[INFO ]: " _fmt, __VA_ARGS__ ))
#define Log_errorf( _fmt, ... )  (Serial_printf( "[ERROR]: " _fmt, __VA_ARGS__ ))
#else
#define Log_printf( _fmt, ... )
#define Log_errorf( _fmt, ... )
#endif

#endif /* _LOG_H_ */
