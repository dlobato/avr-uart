#include "stdio_uart.h"
#include "uart.h"

union data_t{
  struct{
    uint8_t c;
    uint8_t err;
  };
  uint16_t d;
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
  union data_t input;
  struct uart_dev_t* uart_dev_p = (struct uart_dev_t*)fdev_get_udata(stream);
  
  if (uart_dev_p == 0)//device not initialized
    return _FDEV_ERR;

  //while(uart_dev_p->available() == 0)
  //  ;
  input.d = uart_dev_p->getc_();
  // UART_NO_DATA, UART_BUFFER_OVERFLOW,UART_OVERRUN_ERROR or UART_FRAME_ERROR
  if (input.err != 0){
    if (input.err == UART_NO_DATA)
      return _FDEV_EOF;
    else{
      uart_dev_p->last_error |= input.err;
      return _FDEV_ERR;
    }
  }
  return input.c;
}

int uart_setup_stream(FILE *stream, struct uart_dev_t *dev, 
		      const uint8_t rwflags){
  if (stream == 0 || dev == 0)
    return -1;

  fdev_setup_stream(stream, uartio_putchar, uartio_getchar, rwflags);
  fdev_set_udata(stream, (void*)dev);
  return 0;
}

uint8_t uart_geterror(FILE *stream){
  struct uart_dev_t* uart_dev_p = (struct uart_dev_t*)fdev_get_udata(stream);
  
  if (uart_dev_p == 0)
    return 0;
  return uart_dev_p->last_error;
}

void uart_clearerror(FILE *stream){
  struct uart_dev_t* uart_dev_p = (struct uart_dev_t*)fdev_get_udata(stream);
  
  if (uart_dev_p != 0)
    uart_dev_p->last_error = 0;
}
  
void uart_close_stream(FILE *stream){
  fdev_set_udata(stream, 0);
  fdev_setup_stream(stream, 0, 0, 0);
}
