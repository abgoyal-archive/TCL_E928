


#include <common.h>
#include <command.h>
#include <asm/system.h>
#include <asm/cache.h>
#ifndef CONFIG_L2_OFF
#include <asm/arch/sys_proto.h>
#endif

static void cache_flush(void);

int cleanup_before_linux(void)
{
	unsigned int i;

	/*
	 * this function is called just before we call linux
	 * it prepares the processor for linux
	 *
	 * we turn off caches etc ...
	 */
	disable_interrupts();

	/* turn off I/D-cache */
	icache_disable();
	dcache_disable();

	/* invalidate I-cache */
	cache_flush();

#ifndef CONFIG_L2_OFF
	/* turn off L2 cache */
	l2_cache_disable();
	/* invalidate L2 cache also */
	invalidate_dcache(get_device_type());
#endif
	i = 0;
	/* mem barrier to sync up things */
	asm("mcr p15, 0, %0, c7, c10, 4": :"r"(i));

#ifndef CONFIG_L2_OFF
	l2_cache_enable();
#endif

	return 0;
}

static void cache_flush(void)
{
	asm ("mcr p15, 0, %0, c7, c5, 0": :"r" (0));
}
