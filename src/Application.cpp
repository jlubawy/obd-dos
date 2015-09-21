#if 0
/**
 *  File Name : Application.cpp
 *     Author : Josh Lubawy <jlubawy@gmail.com>
 *                          <jlubawy@asu.edu>
 */

#include <stdint.h>

#include "CAN_mcp2515.h"
#include "Debug.h"
#include "GPS.h"
#include "LCD.h"
#include "LED.h"
#include "Log.h"
#include "Storage.h"

#define PROGRAM_NAME  "OBDuino"
#define SESSION_FILENAME_LEN  8 + 1 + 3 + 1  /* 8.3 filename limit + '\0' */
#define DEFAULT_SAMPLE_RATE_MS  1000UL

#define APP_ASSERT(cond) { \
    if (!(cond)) { \
        Log_printf("Assert failed at %s:%d\n", __FILE__, __LINE__); \
        App_exit((__LINE__ == 0) ? 1 : __LINE__); \
    } \
}

static const unsigned int joystickCenterPort = A4;
static int joystickCenterValue;

static char sessionFilename[SESSION_FILENAME_LEN];

static File sessionFile;
static bool storageAvailable;

static unsigned long sampleRateMs = DEFAULT_SAMPLE_RATE_MS;
static unsigned long last = 0UL;

static int sampleIndex;

#define SAMPLE_STR_MAX_LEN  256
static char sampleStr[SAMPLE_STR_MAX_LEN];
static size_t sampleStrLen;

/******************************************************************************
                                Local Functions
******************************************************************************/
/*****************************************************************************/
static void
App_exit(int errorCode)
{
    if (storageAvailable) {
        Log_printf("Closing session file\n", 0);
        Storage_flush(sessionFile);
        Storage_close(sessionFile);
    }

    Log_printf("exit(%d)\n", errorCode);
    LCD_printf(1, "exit(%d)", errorCode);

    exit(errorCode);
}


/*****************************************************************************/
static void
App_createSessionFile()
{
    GPS_Date_t gpsDate;

    LCD_printf(0, "waiting for date", 0);

    /* Wait for the date so we can create a new directory if needed */
    while (1) {
        GPS_update();

        if (GPS_getDate(&gpsDate)) {
            break;  /* date is valid */
        }
    }

    if (storageAvailable) {
        snprintf(sessionFilename, SESSION_FILENAME_LEN, "%02u%02u%04u.CSV", gpsDate.month, gpsDate.day, gpsDate.year);

        LCD_printf(0, "%s", sessionFilename);

        /* Open the new session file */
        Log_printf("Opening session file '%s'\n", sessionFilename);
        APP_ASSERT(sessionFile = Storage_open(sessionFilename, FILE_WRITE));
    } else {
        LCD_printf(0, "%02u/%02u/%04u", gpsDate.month, gpsDate.day, gpsDate.year);
    }
}


/*****************************************************************************/
static void
App_checkForExit()
{
    joystickCenterValue = analogRead(joystickCenterPort);

    /* If center joystick button pressed then close the session file and exit */
    if (joystickCenterValue < 512) {
        App_exit(0);
    }
}


/*****************************************************************************/
static void
App_memoryDebug()
{
    extern char *__malloc_heap_start;
    extern char *__malloc_heap_end;
    extern size_t __malloc_margin;

    __malloc_margin = 32;

    uint8_t* testBuffer = NULL;
    size_t testBufferLen = 1024;

    while( !(testBuffer = (uint8_t*)malloc(testBufferLen)) ) {
        testBufferLen--;
    }

    Log_printf("heap left: %d / %d bytes\n", testBufferLen, __malloc_heap_start - __malloc_heap_end);
    Log_printf("heap start    : 0x%X\n", __malloc_heap_start);
    Log_printf("heap end      : 0x%X\n", __malloc_heap_end);
    Log_printf("malloc margin : %u\n", __malloc_margin);
    free(testBuffer);
}


/******************************************************************************
                                   Functions
******************************************************************************/
/*****************************************************************************/
void
setup()
{
    storageAvailable = false;
    sampleIndex = 0;

    Log_init();
#if DEBUG_APP
    App_memoryDebug();
#endif
    LCD_init();
    storageAvailable = Storage_init();
    GPS_init();

    Log_printf("Starting %s (storage available = %d)\n", PROGRAM_NAME, storageAvailable);

    /* Create session file for logging sampled data */
    App_createSessionFile();

    /* Enable joystick input */
    pinMode(joystickCenterPort, INPUT);
    digitalWrite(joystickCenterPort, HIGH);  /* enable pull-up */
}


/*****************************************************************************/
void
loop()
{
    if ( millis() - last > 500 ) {
        LED_toggle( LED_GREEN_0 );
        LED_toggle( LED_GREEN_1 );
        last = millis();
    }

    bool gpsDateValid;
    GPS_Date_t gpsDate;

    bool gpsTimeValid;
    GPS_Time_t gpsTime;

    bool gpsLocationValid;
    GPS_Location_t gpsLocation;

    bool gpsSpeedMphValid;
    GPS_Speed_t gpsSpeedMph;

    GPS_Course_t gpsCourseDegrees;

    GPS_Altitude_t gpsAltitudeFeet;

    uint32_t gpsNumOfSatellites;

    App_checkForExit();  /* check if we need to exit */
    GPS_update();  /* update GPS data */

    if (millis() - last > sampleRateMs) {
        /* Make sure at least this data is valid */
        gpsDateValid = GPS_getDate(&gpsDate);
        gpsTimeValid = GPS_getTime(&gpsTime);
        gpsLocationValid = GPS_getLocation(&gpsLocation);
        gpsSpeedMphValid = GPS_getSpeedMph(&gpsSpeedMph);

        if (gpsDateValid && gpsTimeValid && gpsLocationValid && gpsSpeedMphValid) {
            /* Reset the sample rate once GPS has locked */
            sampleRateMs = DEFAULT_SAMPLE_RATE_MS;

            /* Sample data */
            sampleStrLen = snprintf(sampleStr, SAMPLE_STR_MAX_LEN, "%d,%02u-%02u-%04u,%02u:%02u:%02u,%f,%f,%f,%f,%f,%u\n",
                sampleIndex,
                gpsDate.month, gpsDate.day, gpsDate.year,
                gpsTime.hour, gpsTime.minute, gpsTime.second,
                gpsLocation.lat, gpsLocation.lng,
                gpsSpeedMph,
                (GPS_getCourseDegrees(&gpsCourseDegrees)) ? gpsCourseDegrees : 0.0f,
                (GPS_getAltitudeFeet(&gpsAltitudeFeet)) ? gpsAltitudeFeet : 0.0f,
                (GPS_getNumberOfSatellites(&gpsNumOfSatellites)) ? gpsNumOfSatellites : 0
            );

            Log_printf("%s", sampleStr);
            LCD_printf(1, "%d samples", sampleIndex + 1);

            if (storageAvailable) {
                /* Write sample data to non-volatile storage.
                 * Assert that the program writes as much as we ask or else there may be a problem. */
                APP_ASSERT(Storage_write((uint8_t*)sampleStr, sampleStrLen, sessionFile) == sampleStrLen);
            }

            sampleIndex++;
        } else {
            /* Back-off 5 seconds at a time, up to 15 seconds, until we get lock.
             * It could take awhile to lock if it's been a few days since the last use. */
            sampleRateMs = (sampleRateMs >= 15000) ? 15000 : sampleRateMs + 5000;
            Log_printf(
                "waiting for valid data (date=%d, time=%d, location=%d, speed=%d\n",
                gpsDateValid, gpsTimeValid, gpsLocationValid, gpsSpeedMphValid
            );
            LCD_printf(1, "waiting for data", 0);
        }

        last = millis();
    }
}
#endif
