#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdio.h>

/**
 * F73 -- Helper API for RNControl Board with ATmega32
*/

// Stream for input and output via uart. 
extern FILE uartStream;

/**
 * Init UART in async mode using 
 * baud symbols per second (see datasheet for supported baud rates),
 * dataBits data bits (5 ... 9),
 * parity 'N' (no), 'E' (even), 'O' (odd), and
 * stoppBits stop bits (1 or 2).
*/
void uartInit(uint32_t baud, uint8_t dataBits, char parity, uint8_t stoppBits);

/**
 * Write a single char c to UART, f must be a pointer to uartStream (global)
*/
int uartPutc(char c, FILE* f);

/**
 * Read a single char from UART,  f must be a pointer to uartStream (global)
*/
int uartGetc(FILE* f);

/**
 * Reads a line from UART and stores it into the string pointed to by, str.
 * It stops when either the newline character \n, carriage return \r, EOF, EOT or \0 is read.
 * Always returns a null-terminaled string.
 * DON'T USE THIS FUNCTION. It will make your software vunerable (-> buffer overflows).
*/
char* uartGets(char* str);

#ifdef __cplusplus
}
#endif
