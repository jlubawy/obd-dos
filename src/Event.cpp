/**
 * Event.cpp - Event queue implementation for the OBD-Dos platform
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

#include <stdlib.h>

#include "Event.h"

/******************************************************************************
                                    Defines
******************************************************************************/
/*****************************************************************************/
#define MAX_NUM_OF_EVENTS  16


/******************************************************************************
                                     Types
******************************************************************************/
/*****************************************************************************/
struct Event_s {
    EventGroup_t group;
    EventId_t id;
    bool isValid;
};


/******************************************************************************
                                Local Variables
******************************************************************************/
/*****************************************************************************/
static struct Event_s events[ MAX_NUM_OF_EVENTS ];
static size_t head;
static size_t tail;


/******************************************************************************
                                   Functions
******************************************************************************/
/*****************************************************************************/
void
Event_init( void )
{
    size_t i;

    head = 0;
    tail = 0;

    for ( i = 0; i < MAX_NUM_OF_EVENTS; i++ ) {
        events[i].isValid = false;
    }
}


/*****************************************************************************/
Event_t
Event_enqueue( EventGroup_t group, EventId_t id )
{
    /* Queue is full */
    if ( (head == tail) && events[tail].isValid ) {
            return NULL;
    }

    events[tail].isValid = true;
    events[tail].group = group;
    events[tail].id = id;

    tail = (tail+1) % MAX_NUM_OF_EVENTS;

    return (Event_t)(&events[tail]);
}


/*****************************************************************************/
Event_t
Event_dequeue( void )
{
    Event_t event;

    /* Queue is empty */
    if ( events[head].isValid == false ) {
        return NULL;
    }

    events[head].isValid = false;
    event = (Event_t)(&events[head]);
    head = (head+1) % MAX_NUM_OF_EVENTS;

    return event;
}


/*****************************************************************************/
EventGroup_t
Event_getGroup( Event_t event )
{
    return event->group;
}


/*****************************************************************************/
EventId_t
Event_getId( Event_t event )
{
    return event->id;
}
