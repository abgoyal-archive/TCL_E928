

#include <common.h>

int do_reset(cmd_tbl_t *cmdtp, int flag, int argc, char *argv[])
{
	puts ("resetting ...\n");

	udelay (50000);				/* wait 50 ms */

	disable_interrupts();
	reset_cpu(0);

	/*NOTREACHED*/
	return 0;
}
