


#include <common.h>
#include <command.h>
#include <clps7111.h>
#include <asm/hardware.h>
#include <asm/system.h>

#if defined(CONFIG_IMPA7) || defined(CONFIG_EP7312) || defined(CONFIG_ARMADILLO)
static void cache_flush(void);
#endif

int cleanup_before_linux (void)
{
	/*
	 * this function is called just before we call linux
	 * it prepares the processor for linux
	 *
	 * we turn off caches etc ...
	 * and we set the CPU-speed to 73 MHz - see start.S for details
	 */

#if defined(CONFIG_IMPA7) || defined(CONFIG_EP7312) || defined(CONFIG_ARMADILLO)
	disable_interrupts ();

	/* turn off I-cache */
	icache_disable();
	dcache_disable();

	/* flush I-cache */
	cache_flush();
#ifdef CONFIG_ARM7_REVD
	/* go to high speed */
	IO_SYSCON3 = (IO_SYSCON3 & ~CLKCTL) | CLKCTL_73;
#endif
#elif defined(CONFIG_NETARM) || defined(CONFIG_S3C4510B) || defined(CONFIG_LPC2292)
	disable_interrupts ();
	/* Nothing more needed */
#elif defined(CONFIG_INTEGRATOR) && defined(CONFIG_ARCH_INTEGRATOR)
	/* No cleanup before linux for IntegratorAP/CM720T as yet */
#else
#error No cleanup_before_linux() defined for this CPU type
#endif
	return 0;
}

#if defined(CONFIG_IMPA7) || defined(CONFIG_EP7312) || defined(CONFIG_ARMADILLO)
/* flush I/D-cache */
static void cache_flush (void)
{
	unsigned long i = 0;

	asm ("mcr p15, 0, %0, c7, c5, 0": :"r" (i));
}
#elif defined(CONFIG_INTEGRATOR) && defined(CONFIG_ARCH_INTEGRATOR)
	/* No specific cache setup for IntegratorAP/CM720T as yet */
	void icache_enable (void)
	{
	}
#endif
