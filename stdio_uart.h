#ifndef STDIO_UART_H
#define STDIO_UART_H
/* Some utils to use uart as a stdio stream */

#include <stdio.h>

#ifdef UART_USE_CONFIG_HEADER
#include "config.h"
#endif

enum uart_dev_id_enum{
#ifdef USART0_ENABLED
  UART0_ID,
#endif
#ifdef USART1_ENABLED
  UART1_ID,
#endif
#ifdef USART2_ENABLED
  UART2_ID,
#endif
#ifdef USART3_ENABLED
  UART3_ID,
#endif
  MAX_UART_ID
};

/*
 * Init \c stream with uart \c dev_id device setting \c baudrate
 * \c rwflags set the stream direction
 * return 0 if device is successfully opened, != 0 otherwise
 */
int uartio_open(FILE *stream, const uint8_t dev_id,
		const uint16_t baudrate, const uint8_t rwflags);
void uartio_close(FILE *stream);


#endif //STDIO_UART_H
