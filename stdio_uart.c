#include "stdio_uart.h"
#include "uart.h"

struct uart_dev_t{
  void (*init_)(uint16_t baudrate);
  uint16_t (*getc_)(void);
  void (*putc_)(uint8_t data);
  uint16_t (*available_)(void);
  void (*flush_)(void);
};

struct uart_dev_t uart_dev[] ={
#ifdef USART0_ENABLED
  {
    .init_ = uart0_init,
    .getc_ = uart0_getc,
    .putc_ = uart0_putc,
    .available_ = uart0_available,
    .flush_ = uart0_flush
  },
#endif
#ifdef USART1_ENABLED
  {
    .init_ = uart1_init,
    .getc_ = uart1_getc,
    .putc_ = uart1_putc,
    .available_ = uart1_available,
    .flush_ = uart1_flush
  },
#endif
#ifdef USART2_ENABLED
  {
    .init_ = uart2_init,
    .getc_ = uart2_getc,
    .putc_ = uart2_putc,
    .available_ = uart2_available,
    .flush_ = uart2_flush
  },
#endif
#ifdef USART3_ENABLED
  {
    .init_ = uart3_init,
    .getc_ = uart3_getc,
    .putc_ = uart3_putc,
    .available_ = uart3_available,
    .flush_ = uart3_flush
  },
#endif
};

int uartio_putchar(const char c, FILE *stream){
  const struct uart_dev_t* uart_dev_p = (const struct uart_dev_t*)fdev_get_udata(stream);
  if (uart_dev_p == 0)//device not initialized
    return _FDEV_ERR;

  //if (c == '\n') {
  //  uartio_putchar('\r', stream);
  //}
  uart_dev_p->putc_((uint8_t)c);
  return 0;
}

int uartio_getchar(FILE *stream){
  uint16_t data;
  const struct uart_dev_t* uart_dev_p = (const struct uart_dev_t*)fdev_get_udata(stream);
  
  if (uart_dev_p == 0)//device not initialized
    return _FDEV_ERR;

  //while(uart_dev_p->available() == 0)
  //  ;
  data = uart_dev_p->getc_();
  // UART_NO_DATA, UART_BUFFER_OVERFLOW,UART_OVERRUN_ERROR or UART_FRAME_ERROR
  if ((data>>8) != 0){
    if (data == UART_NO_DATA)
      return _FDEV_EOF;
    else
      return _FDEV_ERR;
  }
  return data;
}

int uartio_open(FILE *stream, const uint8_t dev_id,
		const uint16_t baudrate, const uint8_t rwflags){
  if (dev_id >= MAX_UART_ID)
    return -1;

  uart_dev[dev_id].init_(baudrate);
  fdev_setup_stream(stream, uartio_putchar, uartio_getchar, rwflags);
  fdev_set_udata(stream, (void*)&uart_dev[dev_id]);
  return 0;
}
  
void uartio_close(FILE *stream){
  fdev_setup_stream(stream, 0, 0, 0);
}
