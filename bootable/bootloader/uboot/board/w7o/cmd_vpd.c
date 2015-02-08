

#include <common.h>
#include <command.h>

#if defined(CONFIG_CMD_BSP)

#include "vpd.h"

int do_vpd (cmd_tbl_t * cmdtp, int flag, int argc, char *argv[])
{
	VPD vpd;			/* Board specific data struct */
	uchar dev_addr = CONFIG_SYS_DEF_EEPROM_ADDR;

	/* Validate usage */
	if (argc > 2) {
		cmd_usage(cmdtp);
		return 1;
	}

	/* Passed in EEPROM address */
	if (argc == 2)
		dev_addr = (uchar) simple_strtoul (argv[1], NULL, 16);

	/* Read VPD and output it */
	if (!vpd_get_data (dev_addr, &vpd)) {
		vpd_print (&vpd);
		return 0;
	}

	return 1;
}

U_BOOT_CMD(
	  vpd,	2,	1,	do_vpd,
	  "Read Vital Product Data",
	  "[dev_addr]\n"
	  "        - Read VPD Data from default address, or device address 'dev_addr'."
);

#endif
