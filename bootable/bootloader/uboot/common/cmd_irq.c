

#include <common.h>
#include <config.h>
#include <command.h>

int do_interrupts(cmd_tbl_t *cmdtp, int flag, int argc, char *argv[])
{

	if (argc != 2) {
		cmd_usage(cmdtp);
		return 1;
	}

	/* on */
	if (strncmp(argv[1], "on", 2) == 0) {
		enable_interrupts();
	} else {
		disable_interrupts();
	}

	return 0;
}

U_BOOT_CMD(
	interrupts, 5, 0, do_interrupts,
	"enable or disable interrupts",
	"[on, off]"
);

/* Implemented in $(CPU)/interrupts.c */
int do_irqinfo (cmd_tbl_t *cmdtp, int flag, int argc, char *argv[]);

U_BOOT_CMD(
	irqinfo,    1,    1,     do_irqinfo,
	"print information about IRQs",
	""
);
