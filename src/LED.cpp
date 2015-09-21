/**
 *  File Name : LED.cpp
 *     Author : Josh Lubawy <jlubawy@gmail.com>
 *                          <jlubawy@asu.edu>
 */

#include <stdint.h>

#include "Arduino.h"

#include "Assert.h"
#include "LED.h"

/******************************************************************************
                                     Types
******************************************************************************/
/*****************************************************************************/
typedef enum {
    LED_OFF  = LOW,
    LED_ON   = HIGH,
} LED_State_t;

/*****************************************************************************/
typedef struct {
    LED_Color_t color;
    uint8_t     pin;
    LED_State_t currentState;
} LED_Info_t;


/******************************************************************************
                                Local Variables
******************************************************************************/
/*****************************************************************************/
static const LED_Info_t ledInfo[ LED_NUM_OF_COLORS ] = {
    { LED_GREEN_0, 7, LED_OFF },
    { LED_GREEN_1, 8, LED_OFF },
};

/*****************************************************************************/
static const unsigned int ledInfoCount = sizeof(ledInfo) / sizeof(ledInfo[0]);

/*****************************************************************************/
static LED_State_t ledStates[ LED_NUM_OF_COLORS ];


/******************************************************************************
                                   Functions
******************************************************************************/
/*****************************************************************************/
void
LED_init( void )
{
    int i;

    for ( i = 0; i < ledInfoCount; i++ ) {
        pinMode( ledInfo[i].pin, OUTPUT );
        ledStates[i] = LED_OFF;
        digitalWrite( ledInfo[i].pin, LED_OFF );
    }
}


/*****************************************************************************/
void
LED_turnOn( LED_Color_t color )
{
    ASSERT( color < ledInfoCount );

    ledStates[color] = LED_ON;
    digitalWrite( ledInfo[color].pin, LED_ON );
}


/*****************************************************************************/
void
LED_turnOff( LED_Color_t color )
{
    ASSERT( color < ledInfoCount );

    ledStates[color] = LED_OFF;
    digitalWrite( ledInfo[color].pin, LED_OFF );
}


/*****************************************************************************/
void
LED_toggle( LED_Color_t color )
{
    ASSERT( color < ledInfoCount );

    ledStates[color] = ( LED_ON == ledStates[color] ) ? LED_OFF : LED_ON;
    digitalWrite( ledInfo[color].pin, ledStates[color] );
}
