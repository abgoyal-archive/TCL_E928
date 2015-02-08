

#include <common.h>
#include <command.h>

int do_exit(cmd_tbl_t *cmdtp, int flag, int argc, char *argv[])
{
	int r;

	r = 0;
	if (argc > 1)
		r = simple_strtoul(argv[1], NULL, 10);

	return -r - 2;
}

U_BOOT_CMD(
	exit,	2,	1,	do_exit,
	"exit script",
	""
);
