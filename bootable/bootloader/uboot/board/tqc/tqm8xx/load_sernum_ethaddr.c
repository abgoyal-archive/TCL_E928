

#include <common.h>
#include <mpc8xx.h>


void load_sernum_ethaddr (void)
{
	unsigned char *hwi;
	unsigned char  serial [CONFIG_SYS_HWINFO_SIZE];
	unsigned char  ethaddr[CONFIG_SYS_HWINFO_SIZE];
	unsigned short ih, is, ie, part;

	hwi = (unsigned char *)(CONFIG_SYS_FLASH_BASE + CONFIG_SYS_HWINFO_OFFSET);
	ih = is = ie = 0;

	if (*((unsigned long *)hwi) != (unsigned long)CONFIG_SYS_HWINFO_MAGIC) {
		return;
	}

	part = 1;

	/* copy serial # / MAC address */
	while ((hwi[ih] != '\0') && (ih < CONFIG_SYS_HWINFO_SIZE)) {
		if (hwi[ih] < ' ' || hwi[ih] > '~') { /* ASCII strings! */
			return;
		}
		switch (part) {
		default:		/* Copy serial # */
			if (hwi[ih] == ' ') {
				++part;
			}
			serial[is++] = hwi[ih];
			break;
		case 3:			/* Copy MAC address */
			if (hwi[ih] == ' ') {
				++part;
				break;
			}
			ethaddr[ie++] = hwi[ih];
			if ((ie % 3) == 2)
				ethaddr[ie++] = ':';
			break;
		}
		++ih;
	}
	serial[is]  = '\0';
	if (ie && ethaddr[ie-1] == ':')
		--ie;
	ethaddr[ie] = '\0';

	/* set serial# and ethaddr if not yet defined */
	if (getenv("serial#") == NULL) {
		setenv ((char *)"serial#", (char *)serial);
	}

	if (getenv("ethaddr") == NULL) {
		setenv ((char *)"ethaddr", (char *)ethaddr);
	}
}
