


#include <common.h>
#include <command.h>
#include <netdev.h>
#include <asm/arch/ixp425.h>
#include <asm/system.h>

ulong loops_per_jiffy;

static void cache_flush(void);

#if defined(CONFIG_DISPLAY_CPUINFO)
int print_cpuinfo (void)
{
	unsigned long id;
	int speed = 0;

	asm ("mrc p15, 0, %0, c0, c0, 0":"=r" (id));

	puts("CPU:   Intel IXP425 at ");
	switch ((id & 0x000003f0) >> 4) {
	case 0x1c:
		loops_per_jiffy = 887467;
		speed = 533;
		break;

	case 0x1d:
		loops_per_jiffy = 666016;
		speed = 400;
		break;

	case 0x1f:
		loops_per_jiffy = 442901;
		speed = 266;
		break;
	}

	if (speed)
		printf("%d MHz\n", speed);
	else
		puts("unknown revision\n");

	return 0;
}
#endif /* CONFIG_DISPLAY_CPUINFO */

int cleanup_before_linux (void)
{
	/*
	 * this function is called just before we call linux
	 * it prepares the processor for linux
	 *
	 * just disable everything that can disturb booting linux
	 */

	disable_interrupts ();

	/* turn off I-cache */
	icache_disable();
	dcache_disable();

	/* flush I-cache */
	cache_flush();

	return 0;
}

/* flush I/D-cache */
static void cache_flush (void)
{
	unsigned long i = 0;

	asm ("mcr p15, 0, %0, c7, c5, 0": :"r" (i));
}

/* FIXME */

#ifdef CONFIG_BOOTCOUNT_LIMIT

void bootcount_store (ulong a)
{
	volatile ulong *save_addr = (volatile ulong *)(CONFIG_SYS_BOOTCOUNT_ADDR);

	save_addr[0] = a;
	save_addr[1] = BOOTCOUNT_MAGIC;
}

ulong bootcount_load (void)
{
	volatile ulong *save_addr = (volatile ulong *)(CONFIG_SYS_BOOTCOUNT_ADDR);

	if (save_addr[1] != BOOTCOUNT_MAGIC)
		return 0;
	else
		return save_addr[0];
}

#endif /* CONFIG_BOOTCOUNT_LIMIT */

int cpu_eth_init(bd_t *bis)
{
#ifdef CONFIG_IXP4XX_NPE
	npe_initialize(bis);
#endif
	return 0;
}
