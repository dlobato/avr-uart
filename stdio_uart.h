#ifndef STDIO_UART_H
#define STDIO_UART_H
/* Some utils to use uart as a stdio stream */

#include <stdio.h>
#include "uart.h"

#ifdef USE_CONFIG_HEADER
#include "config.h"
#endif

/*
 * Open \c stream with uart \c dev device.
 * \c rwflags set the stream direction
 * return 0 if device is successfully opened, != 0 otherwise
 * getchar is nonblocking, so any time we read from the stream if there's no data available
 * EOF is returned.
 */
int uart_open_stream(FILE *stream, struct uart_dev_t *dev, const uint8_t rwflags);

/* /\*  */
/*  * get last error. error must be cleared with uart_clearerror */
/*  *\/ */
/* uint8_t uart_geterror_stream(FILE *stream); */

/* /\* */
/*  * clear last error */
/*  *\/ */
/* void uart_clearerror_stream(FILE *stream); */

/*
 * close stream and unlink uart device flushing it before
 */
void uart_close_stream(FILE *stream);


/*
 * return the uart device linked to the stream
 */
struct uart_dev_t * uart_get_device_stream(FILE *stream);


/*
 * flush stream. after the call no more chars are waiting to be sent.
 */
void uart_flush_stream(FILE *stream);

/*
 * return number of characters available on the stream
 */
uint16_t uart_available_stream(FILE *stream);

#endif //STDIO_UART_H
