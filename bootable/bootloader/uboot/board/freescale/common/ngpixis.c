

#include <common.h>
#include <command.h>
#include <watchdog.h>
#include <asm/cache.h>
#include <asm/io.h>

#include "ngpixis.h"

void pixis_reset(void)
{
	out_8(&pixis->rst, 0);

	while (1);
}

void pixis_bank_reset(void)
{
	out_8(&pixis->vctl, 0);
	out_8(&pixis->vctl, 1);

	while (1);
}

void clear_altbank(void)
{
	/* Tell the ngPIXIS to use this the bits in the physical switch for the
	 * boot bank value, instead of the SWx register.  We need to be careful
	 * only to set the bits in SWx that correspond to the boot bank.
	 */
	clrbits_8(&PIXIS_EN(PIXIS_LBMAP_SWITCH), PIXIS_LBMAP_MASK);
}

void set_altbank(void)
{
	/* Program the alternate bank number into the SWx register.
	 */
	clrsetbits_8(&PIXIS_SW(PIXIS_LBMAP_SWITCH), PIXIS_LBMAP_MASK,
		     PIXIS_LBMAP_ALTBANK);

	/* Tell the ngPIXIS to use this the bits in the SWx register for the
	 * boot bank value, instead of the physical switch.  We need to be
	 * careful only to set the bits in SWx that correspond to the boot bank.
	 */
	setbits_8(&PIXIS_EN(PIXIS_LBMAP_SWITCH), PIXIS_LBMAP_MASK);
}


int pixis_reset_cmd(cmd_tbl_t *cmdtp, int flag, int argc, char *argv[])
{
	unsigned int i;
	char *p_altbank = NULL;
	char *unknown_param = NULL;

	/* No args is a simple reset request.
	 */
	if (argc <= 1)
		pixis_reset();

	for (i = 1; i < argc; i++) {
		if (strcmp(argv[i], "altbank") == 0) {
			p_altbank = argv[i];
			continue;
		}

		unknown_param = argv[i];
	}

	if (unknown_param) {
		printf("Invalid option: %s\n", unknown_param);
		return 1;
	}

	if (p_altbank)
		set_altbank();
	else
		clear_altbank();

	pixis_bank_reset();

	/* Shouldn't be reached. */
	return 0;
}

U_BOOT_CMD(
	pixis_reset, CONFIG_SYS_MAXARGS, 1, pixis_reset_cmd,
	"Reset the board using the FPGA sequencer",
	"- hard reset to default bank\n"
	"pixis_reset altbank - reset to alternate bank\n"
	);
