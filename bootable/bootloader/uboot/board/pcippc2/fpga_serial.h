

#ifndef _FPGA_SERIAL_H_
#define _FPGA_SERIAL_H_

extern void	fpga_serial_init	(int);
extern void	fpga_serial_putc	(char);
extern void	fpga_serial_puts	(const char *);
extern int	fpga_serial_getc	(void);
extern int	fpga_serial_tstc	(void);
extern void	fpga_serial_setbrg	(void);

#endif
