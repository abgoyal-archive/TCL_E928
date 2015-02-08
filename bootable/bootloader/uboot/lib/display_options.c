

#include <config.h>
#include <common.h>
#include <linux/ctype.h>
#include <asm/io.h>

int display_options (void)
{
	extern char version_string[];

#if defined(BUILD_TAG)
	printf ("\n\n%s, Build: %s\n\n", version_string, BUILD_TAG);
#else
	printf ("\n\n%s\n\n", version_string);
#endif
	return 0;
}

void print_size(unsigned long long size, const char *s)
{
	unsigned long m = 0, n;
	unsigned long long f;
	static const char names[] = {'E', 'P', 'T', 'G', 'M', 'K'};
	unsigned long d = 10 * ARRAY_SIZE(names);
	char c = 0;
	unsigned int i;

	for (i = 0; i < ARRAY_SIZE(names); i++, d -= 10) {
		if (size >> d) {
			c = names[i];
			break;
		}
	}

	if (!c) {
		printf("%llu Bytes%s", size, s);
		return;
	}

	n = size >> d;
	f = size & ((1ULL << d) - 1);

	/* If there's a remainder, deal with it */
	if (f) {
		m = (10ULL * f + (1ULL << (d - 1))) >> d;

		if (m >= 10) {
			m -= 10;
			n += 1;
		}
	}

	printf ("%lu", n);
	if (m) {
		printf (".%ld", m);
	}
	printf (" %ciB%s", c, s);
}

#define MAX_LINE_LENGTH_BYTES (64)
#define DEFAULT_LINE_LENGTH_BYTES (16)
int print_buffer (ulong addr, void* data, uint width, uint count, uint linelen)
{
	uint8_t linebuf[MAX_LINE_LENGTH_BYTES];
	uint32_t *uip = (void*)linebuf;
	uint16_t *usp = (void*)linebuf;
	uint8_t *ucp = (void*)linebuf;
	int i;

	if (linelen*width > MAX_LINE_LENGTH_BYTES)
		linelen = MAX_LINE_LENGTH_BYTES / width;
	if (linelen < 1)
		linelen = DEFAULT_LINE_LENGTH_BYTES / width;

	while (count) {
		printf("%08lx:", addr);

		/* check for overflow condition */
		if (count < linelen)
			linelen = count;

		/* Copy from memory into linebuf and print hex values */
		for (i = 0; i < linelen; i++) {
			if (width == 4) {
				uip[i] = *(volatile uint32_t *)data;
				printf(" %08x", uip[i]);
			} else if (width == 2) {
				usp[i] = *(volatile uint16_t *)data;
				printf(" %04x", usp[i]);
			} else {
				ucp[i] = *(volatile uint8_t *)data;
				printf(" %02x", ucp[i]);
			}
			data += width;
		}

		/* Print data in ASCII characters */
		puts("    ");
		for (i = 0; i < linelen * width; i++)
			putc(isprint(ucp[i]) && (ucp[i] < 0x80) ? ucp[i] : '.');
		putc ('\n');

		/* update references */
		addr += linelen * width;
		count -= linelen;

		if (ctrlc())
			return -1;
	}

	return 0;
}
