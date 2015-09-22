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

/******************************************************************************
                                     Types
******************************************************************************/
typedef struct {
    bool valid;
    bool updated;
    bool age;
} GPS_Status_t;

typedef struct {
    double lat;
    double lng;
} GPS_Location_t;

typedef struct {
    uint16_t year;
    uint8_t month;
    uint8_t day;
} GPS_Date_t;

typedef struct {
    uint8_t hour;
    uint8_t minute;
    uint8_t second;
} GPS_Time_t;

typedef double GPS_Speed_t;

typedef double GPS_Course_t;

typedef double GPS_Altitude_t;


/******************************************************************************
                                   Functions
******************************************************************************/
/*****************************************************************************/
void
CAN_init( void );


#endif /* _CAN_H_ */
