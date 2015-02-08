


#include <common.h>
#include <command.h>
#include <asm/system.h>
#include <asm/cache.h>
#ifndef CONFIG_L2_OFF
#include <asm/arch/sys_proto.h>
#endif

static void cache_flush(void);
extern void v7_invalidate_dcache_all(void);

int cleanup_before_linux(void)
{
	unsigned int i;

	/*We keep led on when USB/Charger exists*/
//	printf(" > deinit leds..\n");	
//	leds_deinit();    

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
	v7_invalidate_dcache_all();
}

int cpu_init (void)
{
	/*
	 * setup up stacks if necessary
	 */
#ifdef CONFIG_USE_IRQ
	IRQ_STACK_START = _armboot_start - CONFIG_SYS_MALLOC_LEN - CONFIG_SYS_GBL_DATA_SIZE - 4;
	FIQ_STACK_START = IRQ_STACK_START - CONFIG_STACKSIZE_IRQ;
#endif
	return 0;
}
