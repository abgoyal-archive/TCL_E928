


#include <common.h>
#include <ppc4xx.h>
#include <asm/processor.h>

#undef DEBUG
#ifdef DEBUG
#define DEBUGF(x...) printf(x)
#else
#define DEBUGF(x...)
#endif				/* DEBUG */

#define     BOOT_SMALL_FLASH        32	/* 00100000 */
#define     FLASH_ONBD_N            2	/* 00000010 */
#define     FLASH_SRAM_SEL          1	/* 00000001 */

#define     BOOT_SMALL_FLASH_VAL    4
#define     FLASH_ONBD_N_VAL        2
#define     FLASH_SRAM_SEL_VAL      1

static unsigned long flash_addr_table[8][CONFIG_SYS_MAX_FLASH_BANKS] = {
	{0xffc00000, 0xffe00000, 0xff880000},	/* 0:000: configuraton 3 */
	{0xffc00000, 0xffe00000, 0xff800000},	/* 1:001: configuraton 4 */
	{0xffc00000, 0xffe00000, 0x00000000},	/* 2:010: configuraton 7 */
	{0xffc00000, 0xffe00000, 0x00000000},	/* 3:011: configuraton 8 */
	{0xff800000, 0xffa00000, 0xfff80000},	/* 4:100: configuraton 1 */
	{0xff800000, 0xffa00000, 0xfff00000},	/* 5:101: configuraton 2 */
	{0xffc00000, 0xffe00000, 0x00000000},	/* 6:110: configuraton 5 */
	{0xffc00000, 0xffe00000, 0x00000000}	/* 7:111: configuraton 6 */
};

#include "../common/flash.c"

static ulong flash_get_size(vu_long * addr, flash_info_t * info);

unsigned long flash_init(void)
{
	unsigned long total_b = 0;
	unsigned long size_b[CONFIG_SYS_MAX_FLASH_BANKS];
	unsigned char *fpga_base = (unsigned char *)CONFIG_SYS_FPGA_BASE;
	unsigned char switch_status;
	unsigned short index = 0;
	int i;

	/* read FPGA base register FPGA_REG0 */
	switch_status = *fpga_base;

	/* check the bitmap of switch status */
	if (switch_status & BOOT_SMALL_FLASH) {
		index += BOOT_SMALL_FLASH_VAL;
	}
	if (switch_status & FLASH_ONBD_N) {
		index += FLASH_ONBD_N_VAL;
	}
	if (switch_status & FLASH_SRAM_SEL) {
		index += FLASH_SRAM_SEL_VAL;
	}

	DEBUGF("\n");
	DEBUGF("FLASH: Index: %d\n", index);

	/* Init: no FLASHes known */
	for (i = 0; i < CONFIG_SYS_MAX_FLASH_BANKS; ++i) {
		flash_info[i].flash_id = FLASH_UNKNOWN;
		flash_info[i].sector_count = -1;
		flash_info[i].size = 0;

		/* check whether the address is 0 */
		if (flash_addr_table[index][i] == 0) {
			continue;
		}

		/* call flash_get_size() to initialize sector address */
		size_b[i] = flash_get_size((vu_long *)
					   flash_addr_table[index][i],
					   &flash_info[i]);
		flash_info[i].size = size_b[i];
		if (flash_info[i].flash_id == FLASH_UNKNOWN) {
			printf("## Unknown FLASH on Bank %d - Size = 0x%08lx = %ld MB\n",
			       i, size_b[i], size_b[i] << 20);
			flash_info[i].sector_count = -1;
			flash_info[i].size = 0;
		}

		/* Monitor protection ON by default */
		(void)flash_protect(FLAG_PROTECT_SET, CONFIG_SYS_MONITOR_BASE,
				    CONFIG_SYS_MONITOR_BASE + CONFIG_SYS_MONITOR_LEN - 1,
				    &flash_info[2]);
#ifdef CONFIG_ENV_IS_IN_FLASH
		(void)flash_protect(FLAG_PROTECT_SET, CONFIG_ENV_ADDR,
				    CONFIG_ENV_ADDR + CONFIG_ENV_SECT_SIZE - 1,
				    &flash_info[2]);
		(void)flash_protect(FLAG_PROTECT_SET, CONFIG_ENV_ADDR_REDUND,
				    CONFIG_ENV_ADDR_REDUND + CONFIG_ENV_SECT_SIZE - 1,
				    &flash_info[2]);
#endif

		total_b += flash_info[i].size;
	}

	return total_b;
}