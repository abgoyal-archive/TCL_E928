

#ifndef _RS485_H_
#define _RS485_H_

#include <asm/arch/s3c24x0_cpu.h>

int rs485_init (void);
int rs485_getc (void);
void rs485_putc (const char c);
int rs485_tstc (void);
void rs485_puts (const char *s);
void trab_rs485_enable_tx(void);
void trab_rs485_enable_rx(void);

#endif	/* _RS485_H_ */
