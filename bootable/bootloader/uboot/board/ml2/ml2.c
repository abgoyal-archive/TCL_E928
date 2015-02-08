

#include <common.h>
#include <asm/processor.h>


int board_early_init_f (void)
{
	return 0;
}


int checkboard (void)
{
	char *s = getenv ("serial#");
	char *e;

	if (!s || strncmp (s, "ML2", 9)) {
		printf ("### No HW ID - assuming ML2");
	} else {
		for (e = s; *e; ++e) {
			if (*e == ' ')
				break;
		}

		for (; s < e; ++s) {
			putc (*s);
		}
	}


	putc ('\n');

	return (0);
}


phys_size_t initdram (int board_type)
{
	return 32 * 1024 * 1024;
}

int testdram (void)
{
	printf ("test: xxx MB - ok\n");

	return (0);
}
