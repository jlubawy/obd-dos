/**
 *  File Name : Log.h
 *     Author : Josh Lubawy <jlubawy@gmail.com>
 *                          <jlubawy@asu.edu>
 */

#ifndef _LOG_H_
#define _LOG_H_

#include <Arduino.h>
#include <avr/pgmspace.h>
#include <stdio.h>

/* Store format strings in flash memory */
#define APP_ENABLE_LOGGING
#ifdef APP_ENABLE_LOGGING
#define Log_printf(fmt, ...) { \
    printf_P(PSTR(fmt), __VA_ARGS__); \
    Log_flush(); \
}
#else
#define Log_printf(fmt, ...)
#endif

/******************************************************************************
                                   Functions
******************************************************************************/
/*****************************************************************************/
void
Log_init();

/*****************************************************************************/
void
Log_flush();

/*****************************************************************************/
void
Log_write(const char c);


#endif /* _LOG_H_ */
