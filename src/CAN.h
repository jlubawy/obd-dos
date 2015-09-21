/**
 *  File Name : CAN.h
 *     Author : Josh Lubawy <jlubawy@gmail.com>
 *                          <jlubawy@asu.edu>
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
