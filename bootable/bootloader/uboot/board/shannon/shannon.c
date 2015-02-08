

#include <common.h>

DECLARE_GLOBAL_DATA_PTR;


int board_init (void)
{
	/* memory and cpu-speed are setup before relocation */
	/* but if we use InfernoLoader, we must do some inits here */

#ifdef CONFIG_INFERNO
	{
	unsigned long temp;
	__asm__ __volatile__(/* disable MMU, enable icache */
			     "mrc p15, 0, %0, c1, c0\n"
			     "bic %0, %0, #0x00002000\n"
			     "bic %0, %0, #0x0000000f\n"
			     "orr %0, %0, #0x00001000\n"
			     "orr %0, %0, #0x00000002\n"
			     "mcr p15, 0, %0, c1, c0\n"
			     /* flush caches */
			     "mov %0, #0\n"
			     "mcr p15, 0, %0, c7, c7, 0\n"
			     "mcr p15, 0, %0, c8, c7, 0\n"
			     : "=r" (temp)
			     :
			     : "memory");
	/* setup PCMCIA timing */
	temp = 0xa0000018;
	*(unsigned long *)temp = 0x00060006;

	}
#endif /* CONFIG_INFERNO */

	/* arch number for shannon */
	gd->bd->bi_arch_number = MACH_TYPE_SHANNON;

	/* adress of boot parameters */
	gd->bd->bi_boot_params = 0xc0000100;

	return 0;
}

int dram_init (void)
{
#if defined(PHYS_SDRAM_1) || defined(PHYS_SDRAM_2) || \
    defined(PHYS_SDRAM_3) || defined(PHYS_SDRAM_4)
	bd_t *bd = gd->bd;
#endif

#ifdef PHYS_SDRAM_1
	bd->bi_dram[0].start = PHYS_SDRAM_1;
	bd->bi_dram[0].size = PHYS_SDRAM_1_SIZE;
#endif

#ifdef PHYS_SDRAM_2
	bd->bi_dram[1].start = PHYS_SDRAM_2;
	bd->bi_dram[1].size = PHYS_SDRAM_2_SIZE;
#endif

#ifdef PHYS_SDRAM_3
	bd->bi_dram[2].start = PHYS_SDRAM_3;
	bd->bi_dram[2].size = PHYS_SDRAM_3_SIZE;
#endif

#ifdef PHYS_SDRAM_4
	bd->bi_dram[3].start = PHYS_SDRAM_4;
	bd->bi_dram[3].size = PHYS_SDRAM_4_SIZE;
#endif

	return (0);
}
