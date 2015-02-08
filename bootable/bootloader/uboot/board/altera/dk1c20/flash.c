


#include <common.h>
#include <nios.h>

#include "../common/flash.c"

/*----------------------------------------------------------------------*/
#define BANKSZ		CONFIG_SYS_FLASH_SIZE
#define SECTSZ		(64 * 1024)
#define USERFLASH	(2 * 1024 * 1024)	/* bottom 2 MB for user	*/

/*----------------------------------------------------------------------*/
unsigned long flash_init (void)
{
	int i;
	unsigned long addr;
	flash_info_t *fli = &flash_info[0];

	fli->size = BANKSZ;
	fli->sector_count = CONFIG_SYS_MAX_FLASH_SECT;
	fli->flash_id = FLASH_MAN_AMD + FLASH_AMDLV065D;

	addr = CONFIG_SYS_FLASH_BASE;
	for (i = 0; i < fli->sector_count; ++i) {
		fli->start[i] = addr;
		addr += SECTSZ;

		/* Protect all but 2 MByte user area */
		if (addr < (CONFIG_SYS_FLASH_BASE + USERFLASH))
			fli->protect[i] = 0;
		else
			fli->protect[i] = 1;
	}

	return (BANKSZ);
}
