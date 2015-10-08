/**
 * MainLoop.cpp - Main application loop for the OBD-Dos platform
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

#include <Arduino.h>

#include "GPS.h"
#include "LED.h"
#include "NVM.h"
#include "OBD.h"
#include "Serial.h"
#include "WDT.h"

/******************************************************************************
                                    Defines
******************************************************************************/
/*****************************************************************************/
#define TIMER_GPS_LOCKED_SAMPLE_RATE_MS      (1000)
#define TIMER_GPS_NOT_LOCKED_SAMPLE_RATE_MS  (10000)


/******************************************************************************
                                     Types
******************************************************************************/
/*****************************************************************************/


/******************************************************************************
                                Local Variables
******************************************************************************/
/*****************************************************************************/
static bool g_sampleDataValid;

/*****************************************************************************/
static GPS_UtcDateTime_t g_sampledDateTime;

/*****************************************************************************/
static GPS_TransitData_t g_sampledTransitData;

/*****************************************************************************/
static OBD_Data_t g_sampledObdData;

/*****************************************************************************/
static unsigned long g_timer_sample_count_ms = 0;

/*****************************************************************************/
static unsigned long g_timer_sample_delta_ms = 0;

/*****************************************************************************/
static unsigned long g_timer_sample_rate_ms = 0;


/******************************************************************************
                                Local Functions
******************************************************************************/
/*****************************************************************************/



/******************************************************************************
                                   Functions
******************************************************************************/
/*****************************************************************************/
void
setup( void )
{
    NVM_ResetReason_t resetReason;

    /* Assume data is invalid to begin with */
    g_sampleDataValid = false;

    WDT_init();

    LED_init();

    /* Initialize serial UART drivers */
    Serial_init();

    /* Initialize sensors */
    GPS_init();
    OBD_init();

    /* Print or initialize the reset reason */
    if ( NVM_getResetReason( &resetReason ) ) {
        /* Valid reset reason */
        if ( NVM_RESET_REASON_NORMAL != resetReason ) {
            Serial_printf( "Reset Reason: 0x%02X\n", resetReason );
        }
    } else {
        /* Invalid reset reason, initialize it */
        NVM_setResetReason( NVM_RESET_REASON_NORMAL );
    }

    /* Start the watchdog timer */
    WDT_enable( WDT_TIMEOUT_MAX );
}


/*****************************************************************************/
void
loop( void )
{
    bool gpsDateTimeValid;
    bool gpsTransitDataValid;
    bool obdDataValid;

    /* Update GPS & OBD data drivers */
    GPS_update();
    OBD_update();

    /* Wait for valid date & time */
    if ( millis() - g_timer_sample_count_ms > g_timer_sample_rate_ms ) {
        g_timer_sample_delta_ms = (millis() - g_timer_sample_count_ms) - g_timer_sample_rate_ms;

        /* Blink status LED for 100ms */
        LED_blink( LED_ID_STATUS, 100 );

        /* Get GPS date & time */
        gpsDateTimeValid = GPS_getUtcDateTime( &g_sampledDateTime );

        /* Increase sample rate if GPS date and time is locked */
        g_timer_sample_rate_ms = ( gpsDateTimeValid )
                                    ? TIMER_GPS_LOCKED_SAMPLE_RATE_MS
                                    : TIMER_GPS_NOT_LOCKED_SAMPLE_RATE_MS;

        /* Adjust the sample rate based after accounting for delays */
        g_timer_sample_rate_ms -= g_timer_sample_delta_ms;

        /* Get GPS transit data */
        gpsTransitDataValid = GPS_getTransitData( &g_sampledTransitData );

        /* Get OBD data */
        obdDataValid = OBD_getData( &g_sampledObdData );

        /* Output sampled data to serial port */
        Serial_printf(
            "%lu,%u,%04u-%02u-%02uT%02u:%02u:%02uZ00:00,%u,%f,%f,%f,%f,%u,%f\n",

            GPS_getNumOfSatellites(),

            gpsDateTimeValid,
            g_sampledDateTime.year,
            g_sampledDateTime.month,
            g_sampledDateTime.day,
            g_sampledDateTime.hour,
            g_sampledDateTime.minute,
            g_sampledDateTime.second,

            gpsTransitDataValid,
            g_sampledTransitData.lat,
            g_sampledTransitData.lng,
            g_sampledTransitData.speedMph,
            g_sampledTransitData.course,

            obdDataValid,
            g_sampledObdData.speedMph
        );

        g_timer_sample_count_ms = millis();
    }

    /* Reset the WDT */
    WDT_reset();
}
