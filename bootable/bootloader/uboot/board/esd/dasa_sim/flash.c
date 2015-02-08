

#include <common.h>
#include <ppc4xx.h>
#include <asm/processor.h>

#include "../common/flash.c"

static ulong flash_get_size (vu_long *addr, flash_info_t *info);
static void flash_get_offsets (ulong base, flash_info_t *info);



unsigned long flash_init (void)
{
	unsigned long size_b0;
	int i;
	unsigned long base_b0;

	/* Init: no FLASHes known */
	for (i=0; i<CONFIG_SYS_MAX_FLASH_BANKS; ++i) {
		flash_info[i].flash_id = FLASH_UNKNOWN;
	}

	/* Static FLASH Bank configuration here - FIXME XXX */

	size_b0 = flash_get_size((vu_long *)FLASH_BASE0_PRELIM, &flash_info[0]);

	if (flash_info[0].flash_id == FLASH_UNKNOWN) {
		printf ("## Unknown FLASH on Bank 0 - Size = 0x%08lx = %ld MB\n",
			size_b0, size_b0<<20);
	}

	/* Setup offsets */
	flash_get_offsets (-size_b0, &flash_info[0]);

	base_b0 = -size_b0;

	/* Monitor protection ON by default */
	(void)flash_protect(FLAG_PROTECT_SET,
			    -monitor_flash_len,
			    0xffffffff,
			    &flash_info[0]);

	flash_info[0].size = size_b0;

	return (size_b0);
}
