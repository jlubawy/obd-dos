/**
 * GPS.cpp - TinyGPS++ wrapper for the OBD-Dos platform
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

#include <SoftwareSerial.h>
#include <TinyGPS++.h>

#include "GPS.h"
#include "NVM.h"
#include "Serial.h"


/******************************************************************************
                                     Types
******************************************************************************/
/*****************************************************************************/


/******************************************************************************
                                Local Variables
******************************************************************************/
/*****************************************************************************/
static const int rxPin = 4;
static const int txPin = 5;
static const uint32_t baudRate = 4800;
static SoftwareSerial ss(rxPin, txPin);
static TinyGPSPlus gps;
static GPS_TransitData_t g_lastSampleData;

/*****************************************************************************/
static bool g_isUtcDateTimeValid = false;
static bool g_isTransitDataValid = false;


/******************************************************************************
                                   Functions
******************************************************************************/
/*****************************************************************************/
void
GPS_init( void )
{
    ss.begin( baudRate );
    NVM_getLastGpsSample( &g_lastSampleData );
}


/*****************************************************************************/
void
GPS_update( void )
{
    char c;

    while ( ss.available() > 0 ) {
        c = ss.read();
        gps.encode( c );
    }
}


/*****************************************************************************/
uint32_t
GPS_getNumOfSatellites( void )
{
    if ( gps.satellites.isValid() ) {
        return gps.satellites.value();
    }

    return 0;
}


/*****************************************************************************/
bool
GPS_isUtcDateTimeValid( void )
{
    if ( g_isUtcDateTimeValid ) {
        return true;
    }

    g_isUtcDateTimeValid = gps.date.isValid() && gps.time.isValid();
    return g_isUtcDateTimeValid;
}


/*****************************************************************************/
bool
GPS_isUtcDateTimeUpdated( void )
{
    return gps.date.isUpdated() && gps.time.isUpdated();
}


/*****************************************************************************/
bool
GPS_getUtcDateTime( GPS_UtcDateTime_t* datetime )
{
    bool valid;

    if ( valid = GPS_isUtcDateTimeValid() ) {
        datetime->year   = gps.date.year();
        datetime->month  = gps.date.month();
        datetime->day    = gps.date.day();
        datetime->hour   = gps.time.hour();
        datetime->minute = gps.time.minute();
        datetime->second = gps.time.second();
    } else {
        memset( datetime, 0, sizeof(GPS_UtcDateTime_t) );
    }

    return valid;
}


/*****************************************************************************/
bool
GPS_isTransitDataValid( void )
{
    if ( g_isTransitDataValid ) {
        return true;
    }

    g_isTransitDataValid = gps.location.isValid() && gps.speed.isValid() && gps.course.isValid();
    return g_isTransitDataValid;
}


/*****************************************************************************/
bool
GPS_isTransitDataUpdated( void )
{
    return gps.location.isUpdated() && gps.speed.isUpdated() && gps.course.isUpdated();
}


/*****************************************************************************/
bool
GPS_getTransitData( GPS_TransitData_t* transitData )
{
    bool valid;

    if ( valid = GPS_isTransitDataValid() ) {
        transitData->lat      = gps.location.lat();
        transitData->lng      = gps.location.lng();
        transitData->speedMph = gps.speed.mph();
        transitData->course   = gps.course.deg();
    } else {
        memset( transitData, 0, sizeof(GPS_TransitData_t) );
    }

    return valid;
}

