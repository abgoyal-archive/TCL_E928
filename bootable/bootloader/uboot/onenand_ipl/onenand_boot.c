

#include <common.h>

#include "onenand_ipl.h"

typedef int (init_fnc_t)(void);

void start_oneboot(void)
{
	uchar *buf;

	buf = (uchar *) CONFIG_SYS_LOAD_ADDR;

	onenand_read_block(buf);

	((init_fnc_t *)CONFIG_SYS_LOAD_ADDR)();

	/* should never come here */
}

void hang(void)
{
       for (;;);
}
