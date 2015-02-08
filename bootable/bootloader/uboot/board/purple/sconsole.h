

#ifndef _SCONSOLE_H_
#define _SCONSOLE_H_

#include <config.h>

typedef struct sconsole_buffer_s {
	unsigned long size;
	unsigned long max_size;
	unsigned long pos;
	char data[1];
} sconsole_buffer_t;

#define SCONSOLE_BUFFER		((sconsole_buffer_t *) CONFIG_SYS_SCONSOLE_ADDR)

extern void	(* sconsole_putc)	(char);
extern void	(* sconsole_puts)	(const char *);
extern int	(* sconsole_getc)	(void);
extern int	(* sconsole_tstc)	(void);
extern void	(* sconsole_setbrg)	(void);

extern void	sconsole_flush		(void);

#endif
