

#include <common.h>
#if defined(CONFIG_NS9750DEV)
# include <./configs/ns9750dev.h>
# include <./ns9750_bbus.h>
#endif

DECLARE_GLOBAL_DATA_PTR;

void flash__init( void );
void ether__init( void );

static inline void delay( unsigned long loops )
{
	__asm__ volatile ("1:\n"
		"subs %0, %1, #1\n"
		"bne 1b":"=r" (loops):"0" (loops));
}



int board_init( void )
{
	/* Active BBUS modules */
	*get_bbus_reg_addr( NS9750_BBUS_MASTER_RESET ) = 0;

#warning Please register your machine at http://www.arm.linux.org.uk/developer/machines/?action=new
	/* arch number of OMAP 1510-Board */
	/* to be changed for OMAP 1610 Board */
	gd->bd->bi_arch_number = 234;

	/* adress of boot parameters */
	gd->bd->bi_boot_params = 0x10000100;


	icache_enable();

	flash__init();
	ether__init();
	return 0;
}


int misc_init_r (void)
{
	/* currently empty */
	return (0);
}

void flash__init (void)
{
}
void ether__init (void)
{
}

int dram_init (void)
{
	gd->bd->bi_dram[0].start = PHYS_SDRAM_1;
	gd->bd->bi_dram[0].size = PHYS_SDRAM_1_SIZE;

#if CONFIG_NR_DRAM_BANKS > 1
	gd->bd->bi_dram[1].start = PHYS_SDRAM_2;
	gd->bd->bi_dram[1].size = PHYS_SDRAM_2_SIZE;
#endif
	return 0;
}
