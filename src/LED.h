/**
 *  File Name : LED.h
 *     Author : Josh Lubawy <jlubawy@gmail.com>
 *                          <jlubawy@asu.edu>
 */

#ifndef _LED_H_
#define _LED_H_

/******************************************************************************
                                     Types
******************************************************************************/
/*****************************************************************************/
typedef enum {
    LED_GREEN_0  = 0,
    LED_GREEN_1,

    LED_NUM_OF_COLORS,
} LED_Color_t;


/******************************************************************************
                                   Functions
******************************************************************************/
/*****************************************************************************/
void
LED_init( void );

/*****************************************************************************/
void
LED_turnOn( LED_Color_t color );

/*****************************************************************************/
void
LED_turnOff( LED_Color_t color );

/*****************************************************************************/
void
LED_toggle( LED_Color_t color );


#endif /* _LED_H_ */