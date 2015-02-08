

#include <config.h>
#include <common.h>

#include "sconsole.h"

void	(*sconsole_putc) (char) = 0;
void	(*sconsole_puts) (const char *) = 0;
int	(*sconsole_getc) (void) = 0;
int	(*sconsole_tstc) (void) = 0;
void	(*sconsole_setbrg) (void) = 0;

int serial_init (void)
{
	sconsole_buffer_t *sb = SCONSOLE_BUFFER;

	sb->pos  = 0;
	sb->size = 0;
	sb->max_size = CONFIG_SYS_SCONSOLE_SIZE - sizeof (sconsole_buffer_t);

	return (0);
}

void serial_putc (char c)
{
	if (sconsole_putc) {
		(*sconsole_putc) (c);
	} else {
		sconsole_buffer_t *sb = SCONSOLE_BUFFER;

		if (c) {
			sb->data[sb->pos++] = c;
			if (sb->pos == sb->max_size) {
				sb->pos = 0;
			}
			if (sb->size < sb->max_size) {
				sb->size++;
			}
		}
	}
}

void serial_puts (const char *s)
{
	if (sconsole_puts) {
		(*sconsole_puts) (s);
	} else {
		sconsole_buffer_t *sb = SCONSOLE_BUFFER;

		while (*s) {
			sb->data[sb->pos++] = *s++;
			if (sb->pos == sb->max_size) {
				sb->pos = 0;
			}
			if (sb->size < sb->max_size) {
				sb->size++;
			}
		}
	}
}

int serial_getc (void)
{
	if (sconsole_getc) {
		return (*sconsole_getc) ();
	} else {
		return 0;
	}
}

int serial_tstc (void)
{
	if (sconsole_tstc) {
		return (*sconsole_tstc) ();
	} else {
		return 0;
	}
}

void serial_setbrg (void)
{
	if (sconsole_setbrg) {
		(*sconsole_setbrg) ();
	}
}

void sconsole_flush (void)
{
	if (sconsole_putc) {
		sconsole_buffer_t *sb = SCONSOLE_BUFFER;
		unsigned int end = sb->pos < sb->size
				? sb->pos + sb->max_size - sb->size
				: sb->pos - sb->size;

		while (sb->size) {
			(*sconsole_putc) (sb->data[end++]);
			if (end == sb->max_size) {
				end = 0;
			}
			sb->size--;
		}
	}
}
