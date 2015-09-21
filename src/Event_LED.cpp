/**
 *  File Name : LED.cpp
 *     Author : Josh Lubawy <jlubawy@gmail.com>
 *                          <jlubawy@asu.edu>
 */

#include "Event.h"
#include "Event_LED.h"
#include "LED.h"

/******************************************************************************
                                   Functions
******************************************************************************/
/*****************************************************************************/
void
Event_LED_init( void )
{
    LED_init();
}


/*****************************************************************************/
void
Event_LED_handler( EventId_t id )
{
    if ( id & EVENT_ID_LED_GREEN_0 ) {
        LED_toggle( LED_GREEN_0 );
    }

    if ( id & EVENT_ID_LED_GREEN_1 ) {
        LED_toggle( LED_GREEN_1 );
    }
}
