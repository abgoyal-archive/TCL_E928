

#include <common.h>
#ifdef CONFIG_AT91_LEGACY
#warning Your board is using legacy SoC access. Please update!
#endif

#include <asm/arch/hardware.h>
#include <asm/arch/at91_pmc.h>
#include <asm/arch/clk.h>
#include <asm/arch/io.h>

#ifndef CONFIG_SYS_AT91_MAIN_CLOCK
#define CONFIG_SYS_AT91_MAIN_CLOCK 0
#endif

#define AT91_GPBR_BOOTCOUNT_REGISTER 3
#define AT91_BOOTCOUNT_ADDRESS (AT91_GPBR + 4*AT91_GPBR_BOOTCOUNT_REGISTER)

int arch_cpu_init(void)
{
	return at91_clock_init(CONFIG_SYS_AT91_MAIN_CLOCK);
}

#if defined(CONFIG_DISPLAY_CPUINFO)
int print_cpuinfo(void)
{
	char buf[32];

	printf("CPU: %s\n", CONFIG_SYS_AT91_CPU_NAME);
	printf("Crystal frequency: %8s MHz\n",
					strmhz(buf, get_main_clk_rate()));
	printf("CPU clock        : %8s MHz\n",
					strmhz(buf, get_cpu_clk_rate()));
	printf("Master clock     : %8s MHz\n",
					strmhz(buf, get_mck_clk_rate()));

	return 0;
}
#endif

#ifdef CONFIG_BOOTCOUNT_LIMIT
void bootcount_store (ulong a)
{
	volatile ulong *save_addr =
		(volatile ulong *)(AT91_BASE_SYS + AT91_BOOTCOUNT_ADDRESS);

	*save_addr = (BOOTCOUNT_MAGIC & 0xffff0000) | (a & 0x0000ffff);
}

ulong bootcount_load (void)
{
	volatile ulong *save_addr =
		(volatile ulong *)(AT91_BASE_SYS + AT91_BOOTCOUNT_ADDRESS);

	if ((*save_addr & 0xffff0000) != (BOOTCOUNT_MAGIC & 0xffff0000))
		return 0;
	else
		return (*save_addr & 0x0000ffff);
}

#endif /* CONFIG_BOOTCOUNT_LIMIT */
