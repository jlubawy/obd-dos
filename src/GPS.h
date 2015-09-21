/**
 *  File Name : GPS.h
 *     Author : Josh Lubawy <jlubawy@gmail.com>
 *                          <jlubawy@asu.edu>
 */

#ifndef _GPS_H_
#define _GPS_H_


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
GPS_init();

/*****************************************************************************/
void
GPS_update();

/*****************************************************************************/
bool
GPS_getLocation(GPS_Location_t* location);

/*****************************************************************************/
bool
GPS_getDate(GPS_Date_t* date);

/*****************************************************************************/
bool
GPS_getTime(GPS_Time_t* time);

/*****************************************************************************/
bool
GPS_getSpeedMph(GPS_Speed_t* speed);

/*****************************************************************************/
bool
GPS_getCourseDegrees(GPS_Course_t* degrees);

/*****************************************************************************/
bool
GPS_getAltitudeFeet(GPS_Altitude_t* altitude);

/*****************************************************************************/
bool
GPS_getNumberOfSatellites(uint32_t* value);

/*****************************************************************************/
bool
GPS_getHDOP(uint32_t* value);


#endif /* _GPS_H_ */
