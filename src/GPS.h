/**
 * GPS.h - TinyGPS++ wrapper for the OBD-Dos platform
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

#ifndef _GPS_H_
#define _GPS_H_

/******************************************************************************
                                     Types
******************************************************************************/
/*****************************************************************************/
typedef struct {
    uint16_t year;
    uint8_t  month;
    uint8_t  day;
    uint8_t  hour;
    uint8_t  minute;
    uint8_t  second;
} GPS_UtcDateTime_t;

/*****************************************************************************/
typedef struct {
    double lat;
    double lng;
    double speedMph;
    double course;
} GPS_TransitData_t;


/******************************************************************************
                                   Functions
******************************************************************************/
/*****************************************************************************/
void
GPS_init( void );

/*****************************************************************************/
void
GPS_update( void );

/*****************************************************************************/
uint32_t
GPS_getNumOfSatellites( void );

/*****************************************************************************/
bool
GPS_isUtcDateTimeValid( void );

/*****************************************************************************/
bool
GPS_isUtcDateTimeUpdated( void );

/*****************************************************************************/
bool
GPS_getUtcDateTime( GPS_UtcDateTime_t* datetime );

/*****************************************************************************/
bool
GPS_isTransitDataValid( void );

/*****************************************************************************/
bool
GPS_isTransitDataUpdated( void );

/*****************************************************************************/
bool
GPS_getTransitData( GPS_TransitData_t* transitData );


#endif /* _GPS_H_ */
