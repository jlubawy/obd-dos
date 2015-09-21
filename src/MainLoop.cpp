/**
 *  File Name : MainLoop.cpp
 *     Author : Josh Lubawy <jlubawy@gmail.com>
 *                          <jlubawy@asu.edu>
 */

#include "Arduino.h"

#include "CAN_mcp2515.h"
#include "Event.h"
#include "Event_LED.h"
#include "Log.h"

/******************************************************************************
                                     Types
******************************************************************************/
/*****************************************************************************/
enum {
    EVENT_GROUP_LED,
};


/******************************************************************************
                                Local Variables
******************************************************************************/
/*****************************************************************************/
unsigned long green0 = 0UL;
unsigned long green1 = 500UL;


/******************************************************************************
                                   Functions
******************************************************************************/
/*****************************************************************************/
void
setup( void )
{
    CAN_Mcp2515_OperatingMode_t mode;

    Log_init();

    Event_init();
    Event_LED_init();

    CAN_mcp2515_init();

    mode = CAN_mcp2515_getOperatingMode();
    Log_printf( "mode: 0x%02X\n", mode );
}


/*****************************************************************************/
void
loop( void )
{
    Event_t event;
    EventId_t id;

    if ( event = Event_dequeue() ) {
        id = Event_getId( event );

        switch ( Event_getGroup( event ) ) {
            case EVENT_GROUP_LED: {
                Event_LED_handler( id );
                break;
            }

            default: {
                break;
            }
        }
    }

    if ( (millis() - green0) > 500 ) {
        Event_enqueue( EVENT_GROUP_LED, EVENT_ID_LED_GREEN_0 );
        green0 = millis();
    }

    if ( (millis() - green1) > 500 ) {
        Event_enqueue( EVENT_GROUP_LED, EVENT_ID_LED_GREEN_1 );
        green1 = millis();
    }
}
