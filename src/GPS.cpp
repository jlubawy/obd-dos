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
#include "Log.h"

/******************************************************************************
                                     Macros
******************************************************************************/
#define IS_VALID(data) (gps.data.isValid())


/******************************************************************************
                                Local Variables
******************************************************************************/
static const int rxPin = 4;
static const int txPin = 5;
static const uint32_t baudRate = 4800;
static SoftwareSerial ss(rxPin, txPin);

static TinyGPSPlus gps;


/******************************************************************************
                                   Functions
******************************************************************************/
/*****************************************************************************/
void
GPS_init()
{
    ss.begin(baudRate);
}


/*****************************************************************************/
void
GPS_update()
{
    char c;

    while (ss.available() > 0) {
        c = ss.read();
        gps.encode(c);
#if DEBUG_GPS
        Log_write(c);  /* output NMEA sentences */
#endif
    }
}


/*****************************************************************************/
bool
GPS_getLocation(GPS_Location_t* location)
{
    if (IS_VALID(location)) {
        location->lat = gps.location.lat();
        location->lng = gps.location.lng();
        return true;
    }

    return false;
}


/*****************************************************************************/
bool
GPS_getDate(GPS_Date_t* date)
{
    if (IS_VALID(date)) {
        date->year = gps.date.year();
        date->month = gps.date.month();
        date->day = gps.date.day();
        return true;
    }

    return false;
}


/*****************************************************************************/
bool
GPS_getTime(GPS_Time_t* time)
{
    if (IS_VALID(time)) {
        time->hour = gps.time.hour();
        time->minute = gps.time.minute();
        time->second = gps.time.second();
        return true;
    }

    return false;
}


/*****************************************************************************/
bool
GPS_getSpeedMph(GPS_Speed_t* speed)
{
    if (IS_VALID(speed)) {
        *speed = gps.speed.mph();
        return true;
    }

    return false;
}


/*****************************************************************************/
bool
GPS_getCourseDegrees(GPS_Course_t* degrees)
{
    if (IS_VALID(course)) {
        *degrees = gps.course.deg();
        return true;
    }

    return false;
}


/*****************************************************************************/
bool
GPS_getAltitudeFeet(GPS_Altitude_t* altitude)
{
    if (IS_VALID(altitude)) {
        *altitude = gps.altitude.feet();
        return true;
    }

    return false;
}


/*****************************************************************************/
bool
GPS_getNumberOfSatellites(uint32_t* value)
{
    if (IS_VALID(satellites)) {
        *value = gps.satellites.value();
        return true;
    }

    return false;
}


/*****************************************************************************/
bool
GPS_getHDOP(uint32_t* value)
{
    if (IS_VALID(hdop)) {
        *value = gps.hdop.value();
        return true;
    }

    return false;
}
