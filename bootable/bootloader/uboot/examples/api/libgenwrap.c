

#include <common.h>
#include <linux/types.h>
#include <api_public.h>

#include "glue.h"

void printf (const char *fmt, ...)
{
	va_list args;
	uint i;
	char printbuffer[256];

	va_start (args, fmt);

	/* For this to work, printbuffer must be larger than
	 * anything we ever want to print.
	 */
	i = vsprintf (printbuffer, fmt, args);
	va_end (args);

	/* Print the string */
	ub_puts (printbuffer);
}

void vprintf (const char *fmt, va_list args)
{
	uint i;
	char printbuffer[256];

	/* For this to work, printbuffer must be larger than
	 * anything we ever want to print.
	 */
	i = vsprintf (printbuffer, fmt, args);

	/* Print the string */
	ub_puts (printbuffer);
}

void putc (const char c)
{
	ub_putc(c);
}

void __udelay(unsigned long usec)
{
	ub_udelay(usec);
}

void do_reset (void)
{
	ub_reset();
}

void *malloc (size_t len)
{
	return NULL;
}

void hang (void)
{
	while (1) ;
}
