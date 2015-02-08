

#include <common.h>
#include <command.h>

#undef DEBUG_DISP

#define DISP_SIZE	8
#define CWORD_CLEAR	0x80
#define CLEAR_DELAY	(110 * 2)

int do_display (cmd_tbl_t *cmdtp, int flag, int argc, char *argv[])
{
	int i;
	int pos;

	/* Clear display */
	*((volatile char*)(CONFIG_SYS_DISP_CWORD)) = CWORD_CLEAR;
	udelay(1000 * CLEAR_DELAY);

	if (argc < 2)
		return (0);

	for (pos = 0, i = 1; i < argc && pos < DISP_SIZE; i++) {
		char *p = argv[i], c;

		if (i > 1) {
			*((volatile uchar *) (CONFIG_SYS_DISP_CHR_RAM + pos++)) = ' ';
#ifdef DEBUG_DISP
			putc(' ');
#endif
		}

		while ((c = *p++) != '\0' && pos < DISP_SIZE) {
			*((volatile uchar *) (CONFIG_SYS_DISP_CHR_RAM + pos++)) = c;
#ifdef DEBUG_DISP
			putc(c);
#endif
		}
	}

#ifdef DEBUG_DISP
	putc('\n');
#endif

	return (0);
}

/***************************************************/

U_BOOT_CMD(
	display,	CONFIG_SYS_MAXARGS,	1,	do_display,
	"display string on dot matrix display",
	"[<string>]\n"
	"    - with <string> argument: display <string> on dot matrix display\n"
	"    - without arguments: clear dot matrix display"
);
