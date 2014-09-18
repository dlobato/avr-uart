#ifndef STDIO_UART_H
#define STDIO_UART_H
/* Some utils to use uart as a stdio stream */

#include <stdio.h>
#include "uart.h"

#ifdef USE_CONFIG_HEADER
#include "config.h"
#endif

/*
 * Init \c stream with uart \c dev device.
 * \c rwflags set the stream direction
 * return 0 if device is successfully opened, != 0 otherwise
 */
int uart_setup_stream(FILE *stream, struct uart_dev_t *dev, const uint8_t rwflags);

/* 
 * get last error. error must be cleared with uart_clearerror
 */
uint8_t uart_geterror(FILE *stream);

/*
 * clear last error
 */
void uart_clearerror(FILE *stream);

/*
 * close stream and unlink uart device
 */
void uart_close_stream(FILE *stream);


#endif //STDIO_UART_H
