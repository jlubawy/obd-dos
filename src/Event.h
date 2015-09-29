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

#ifndef _EVENT_H_
#define _EVENT_H_

#include <stdint.h>

/******************************************************************************
                                     Types
******************************************************************************/
/*****************************************************************************/
typedef uint16_t EventGroup_t;

/*****************************************************************************/
typedef uint16_t EventId_t;

/*****************************************************************************/
typedef struct Event_s* Event_t;


/******************************************************************************
                                   Functions
******************************************************************************/
/*****************************************************************************/
void
Event_init( void );

/*****************************************************************************/
Event_t
Event_enqueue( EventGroup_t group, EventId_t id );

/*****************************************************************************/
Event_t
Event_dequeue( void );

/*****************************************************************************/
EventGroup_t
Event_getGroup( Event_t event );

/*****************************************************************************/
EventId_t
Event_getId( Event_t event );


#endif /* _EVENT_H_ */
