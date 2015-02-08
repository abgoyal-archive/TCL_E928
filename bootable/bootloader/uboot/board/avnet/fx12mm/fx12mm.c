

#include <config.h>
#include <common.h>
#include <asm/processor.h>

int checkboard(void)
{
	char tmp[64];
	char *s, *e;
	int i = getenv_r("serial", tmp, sizeof(tmp));

	if (i < 0) {
		printf("Avnet Virtex4 FX12 with no serial #");
	} else {
		for (e = tmp; *e; ++e) {
			if (*e == ' ')
				break;
		}
		printf("Avnet Virtex4 FX12 Minimodul # ");
		for (s = tmp; s < e; ++s)
			putc(*s);
	}
	putc('\n');
	return 0;
}
