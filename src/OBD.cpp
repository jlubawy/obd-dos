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

#include <stdint.h>
#include <string.h>

#include "Assert.h"
#include "CAN.h"
#include "Log.h"
#include "OBD.h"
#include "OBD_pids.h"
#include "Utility.h"

/******************************************************************************
                                    Defines
******************************************************************************/
/*****************************************************************************/
#define OBD_TIMER_MAX_SAMPLE_RATE_MS         (5000)
#define OBD_TIMER_DATA_REQUESTED_TIMEOUT_MS  (10000)

/*****************************************************************************/
#define OBD_MAX_NUM_DATA_REQUEST_ERRORS  (3)

/*****************************************************************************/
#define OBD_11BIT_FUNC_BCAST_ADDR  (0x7DF)

/*****************************************************************************/
#define OBD_29BIT_FUNC_BCAST_ID  (0x18DB33F1)

/*****************************************************************************/
#define OBD_DLC_NIBBLE  (8)  /* field must always be 8 for OBD */

/*****************************************************************************/
#define OBD_FRAME_TYPE_SINGLE       (0)
#define OBD_FRAME_TYPE_FIRST        (1)
#define OBD_FRAME_TYPE_CONSECUTIVE  (2)
#define OBD_FRAME_TYPE_FLOW         (3)

/*****************************************************************************/
#define OBD_FIRST_FRAME_INST_NEXT   (0)
#define OBD_FIRST_FRAME_INST_WAIT   (1)
#define OBD_FIRST_FRAME_INST_ABORT  (2)


/******************************************************************************
                                     Macros
******************************************************************************/
/*****************************************************************************/
#define OBD_BUILD_29BIT_PHYS_BCAST_ID( _dest )  ((0x18DA00F1)|((_dest) << 8))
#define OBD_IS_29BIT_PHYS_REPLY( _reply )       ((0x18DA == (((_reply) >> 16) & 0xFFFF)) && (0xF1 == (((_reply) >> 8) & 0xFF)))
#define OBD_GET_29BIT_PHYS_BCAST_SRC( _reply )  (((_reply) >> 8) & 0xFF)

/*****************************************************************************/
#define OBD_GET_FRAME_TYPE( _byte0 )  ((_byte0) & 0xF)


/******************************************************************************
                                     Types
******************************************************************************/
/*****************************************************************************/
typedef enum {
    OBD_STATE_IDLE,
    OBD_STATE_DATA_REQUESTED,
    OBD_STATE_DATA_RECEIVED,
    OBD_STATE_DATA_READY,

    /* Only used by server */
    OBD_STATE_DATA_RESPONDING,
} OBD_State_t;

/*****************************************************************************/
/* Source: https://en.wikipedia.org/wiki/OBD-II_PIDs#Modes */
typedef enum {
    OBD_MODE_01_SHOW_CURRENT_DATA                   = 0x01,
    OBD_MODE_02_SHOW_FREEZE_FRAME_DATA              = 0x02,
    OBD_MODE_03_SHOW_DIAGNOSTIC_TROUBLE_CODES       = 0x03,
    OBD_MODE_04_CLEAR_DIAGNOSTIC_TROUBLE_CODES      = 0x04,
    OBD_MODE_05_OXYGEN_SENSOR_TEST_RESULTS          = 0x05,
    OBD_MODE_06_OTHER_TEST_RESULTS                  = 0x06,
    OBD_MODE_07_SHOW_PENDING_TROUBLE_CODES          = 0x07,
    OBD_MODE_08_COMPONENT_CONTROL                   = 0x08,
    OBD_MODE_09_REQUEST_VEHICLE_INFORMATION         = 0x09,
    OBD_MODE_0A_PERMANENT_DIAGNOSTIC_TROUBLE_CODES  = 0x0A,
} OBD_Mode_t;

/*****************************************************************************/
typedef uint8_t OBD_Pid_t;


/******************************************************************************
                                Local Variables
******************************************************************************/
/*****************************************************************************/
static uint8_t g_OBD_txDataBuffer[8];
static uint8_t g_OBD_rxDataBuffer[8];

/*****************************************************************************/
static volatile OBD_State_t g_OBD_state_client;

/*****************************************************************************/
static volatile OBD_State_t g_OBD_state_server;

/*****************************************************************************/
static unsigned long g_OBD_timer_max_sample_count_ms = 0;

/*****************************************************************************/
static unsigned long g_OBD_timer_data_requested_timeout_count_ms = 0;

/*****************************************************************************/
static bool g_OBD_vehicleSpeedKphValid;
static OBD_SpeedKph_t g_OBD_vehicleSpeedKph;

/*****************************************************************************/
static uint8_t g_OBD_dataRequestErrors = 0;


/******************************************************************************
                                Local Functions
******************************************************************************/
/*****************************************************************************/
static bool
OBD_sendPidRequest( OBD_Mode_t mode,
                    OBD_Pid_t  pid )
{
    bool success;
    const uint8_t size = 2;

    uint8_t sreg = CRITICAL_SECTION_ENTER();

    memset( g_OBD_txDataBuffer, 0, sizeof(g_OBD_txDataBuffer) );

    g_OBD_txDataBuffer[0] = (size << 4) | (OBD_FRAME_TYPE_SINGLE);
    g_OBD_txDataBuffer[1] = mode;
    g_OBD_txDataBuffer[2] = pid;

    Log_printf( "Sending OBD request mode %u PID %u\n", mode, pid );

    success = CAN_sendStandardDataFrame( OBD_11BIT_FUNC_BCAST_ADDR,
                                         g_OBD_txDataBuffer,
                                         sizeof(g_OBD_txDataBuffer) );

    CRITICAL_SECTION_EXIT( sreg );

    return success;
}


/*****************************************************************************/
static bool
OBD_requestVehicleSpeed( void )
{
    g_OBD_vehicleSpeedKphValid = false;
    g_OBD_vehicleSpeedKph = 0;

    return OBD_sendPidRequest( OBD_MODE_01_SHOW_CURRENT_DATA,
                               OBD_MODE_01_PID_VEHICLE_SPEED );
}


/*****************************************************************************/
static bool
OBD_requestVin( void )
{
    return OBD_sendPidRequest( OBD_MODE_09_REQUEST_VEHICLE_INFORMATION,
                               OBD_MODE_09_PID_VIN );
}


/*****************************************************************************/
static void
OBD_clientUpdate( void )
{
    /* OBD client state machine */
    switch ( g_OBD_state_client ) {

        /* IDLE state - wait for sample timer to expire */
        case OBD_STATE_IDLE: {

            /* If in the idle state and the sample expired then request data */
            if ( millis() - g_OBD_timer_max_sample_count_ms >= OBD_TIMER_MAX_SAMPLE_RATE_MS ) {

                /* Handle any errors while requesting data */
                if ( OBD_requestVehicleSpeed() == false ) {
                    g_OBD_dataRequestErrors++;
                    g_OBD_timer_max_sample_count_ms = millis();

                    Log_errorf( "OBD_requestVehicleSpeed() failed %u times\n", g_OBD_dataRequestErrors );

                    if ( g_OBD_dataRequestErrors >= OBD_MAX_NUM_DATA_REQUEST_ERRORS ) {
                        Log_errorf( "Resetting CAN controller\n", NULL );
                        CAN_reset();
                        g_OBD_dataRequestErrors = 0;
                    }
                    return;
                }

                /* Reset error count */
                g_OBD_dataRequestErrors = 0;

                /* Otherwise go to the next state */
                g_OBD_state_client = OBD_STATE_DATA_REQUESTED;

                /* Start the data request timeout timer */
                g_OBD_timer_data_requested_timeout_count_ms = millis();
            }

            break;
        }

        /* DATA_REQUESTED state - wait for data to be returned */
        case OBD_STATE_DATA_REQUESTED: {
            if ( millis() - g_OBD_timer_data_requested_timeout_count_ms >= OBD_TIMER_DATA_REQUESTED_TIMEOUT_MS ) {
                Log_errorf( "OBD data request timed out after %u ms\n", OBD_TIMER_DATA_REQUESTED_TIMEOUT_MS );
                /* If we haven't received a response yet then timeout and go back to idle state */
                g_OBD_state_client = OBD_STATE_IDLE;
            }

            break;
        }

        case OBD_STATE_DATA_RECEIVED: {

            break;
        }

        case OBD_STATE_DATA_READY: {

            break;
        }

        /* invalid state - return to IDLE */
        default: {
            /* debug check since we should never get here */
            ASSERT( false );
            g_OBD_state_client = OBD_STATE_IDLE;

            break;
        }
    }
}


/*****************************************************************************/
static void
OBD_serverUpdate( void )
{
    /* OBD client state machine */
    switch ( g_OBD_state_server ) {

        /* IDLE state - wait for requests */
        case OBD_STATE_IDLE: {
            /* do nothing */
            break;
        }

        case OBD_STATE_DATA_RECEIVED: {

            break;
        }

        case OBD_STATE_DATA_RESPONDING: {

            break;
        }

        /* invalid states - return to idle */
        case OBD_STATE_DATA_REQUESTED:
        case OBD_STATE_DATA_READY:
        default: {
            /* debug check since we should never get here */
            ASSERT( false );
            g_OBD_state_server = OBD_STATE_IDLE;

            break;
        }
    }
}


/*****************************************************************************/
static void
OBD_rxCallback( uint32_t id, bool isExtended )
{
    /* TODO: send to client or server handler based on ID */
    return;
}


/*****************************************************************************/
static void
OBD_errorCallback( CAN_Error_t errorType )
{
    Log_errorf( "OBD error callback\n", NULL );
    return;
}


/******************************************************************************
                                   Functions
******************************************************************************/
/*****************************************************************************/
void
OBD_init( void )
{
    g_OBD_state_client = OBD_STATE_IDLE;
    g_OBD_state_server = OBD_STATE_IDLE;

    g_OBD_dataRequestErrors = 0;

    CAN_init( g_OBD_rxDataBuffer,
              sizeof(g_OBD_rxDataBuffer),
              OBD_rxCallback,
              OBD_errorCallback );
}


/*****************************************************************************/
void
OBD_update( void )
{
    OBD_clientUpdate();
    OBD_serverUpdate();
}


/*****************************************************************************/
bool
OBD_getVehicleSpeed( OBD_SpeedKph_t* speedKph )
{
    *speedKph = g_OBD_vehicleSpeedKph;
    return g_OBD_vehicleSpeedKphValid;
}
