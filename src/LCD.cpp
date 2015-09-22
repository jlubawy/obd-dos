/**
 * LCD.cpp - LCD screen drivers for the OBD-Dos platform
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

#include <stdarg.h>

#include <SoftwareSerial.h>

/******************************************************************************
                                     Macros
******************************************************************************/
/*
Calculate values to set the cursor to a specific line and x position:
    128, 129, 130, 131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143
    192, 193, 194, 195, 196, 197, 198, 199, 200, 201, 202, 203, 204, 205, 206, 207
*/
#define CURSOR_VALUE(line, x) (128 + (64*line) + x)


/******************************************************************************
                                Local Variables
******************************************************************************/
static const int rxPin = 3;
static const int txPin = 6;
static const uint32_t baudRate = 9600;
static SoftwareSerial ss(rxPin, txPin);

static const int NUM_OF_CHARACTERS = 16;
static const int NUM_OF_LINES = 2;

static const char blank_line[NUM_OF_CHARACTERS+1] = "                ";


/******************************************************************************
                                Local Functions
******************************************************************************/
/*****************************************************************************/
static bool
LCD_setCursor(unsigned int line, unsigned int x)
{
    if ((line >= NUM_OF_LINES) && (x >= NUM_OF_CHARACTERS)) {
        return false;
    }

    ss.write(254);
    ss.write(CURSOR_VALUE(line, x));
    return true;
}


/*****************************************************************************/
static bool
LCD_write(unsigned int line, unsigned int x, const char *str)
{
    if (!LCD_setCursor(line, x)) {
        return false;
    }

    ss.write(str);
    return true;
}


/*****************************************************************************/
static bool
LCD_clearLine(unsigned int line)
{
    return LCD_write(line, 0, blank_line);
}


/*****************************************************************************/
static void
LCD_clearScreen()
{
    int i;

    for (i = 0; i < NUM_OF_LINES; i++) {
        LCD_clearLine(i);
    }
}


/******************************************************************************
                                   Functions
******************************************************************************/
/*****************************************************************************/
void
LCD_init()
{
#if HAS_LCD == TRUE
    ss.begin(baudRate);
    LCD_clearScreen();
#endif /* HAS_LCD */
}


/*****************************************************************************/
void
LCD_printf(unsigned int line, const char *format, ...)
{
#if HAS_LCD
    char str_buffer[NUM_OF_CHARACTERS + 1];
    va_list args;

    va_start(args, format);
    vsnprintf(str_buffer, sizeof(str_buffer), format, args);
    va_end(args);

    if (LCD_clearLine(line)) {
        LCD_write(line, 0, str_buffer);
    }
#endif /* HAS_LCD */
}
