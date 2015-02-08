

#include <common.h>
#include <watchdog.h>
#include <asm/processor.h>
#include <asm/immap.h>

#ifdef	CONFIG_M5272
int interrupt_init(void)
{
	volatile intctrl_t *intp = (intctrl_t *) (MMAP_INTC);

	/* disable all external interrupts */
	intp->int_icr1 = 0x88888888;
	intp->int_icr2 = 0x88888888;
	intp->int_icr3 = 0x88888888;
	intp->int_icr4 = 0x88888888;
	intp->int_pitr = 0x00000000;
	/* initialize vector register */
	intp->int_pivr = 0x40;

	enable_interrupts();

	return 0;
}

#if defined(CONFIG_MCFTMR)
void dtimer_intr_setup(void)
{
	volatile intctrl_t *intp = (intctrl_t *) (CONFIG_SYS_INTR_BASE);

	intp->int_icr1 &= ~INT_ICR1_TMR3MASK;
	intp->int_icr1 |= CONFIG_SYS_TMRINTR_PRI;
}
#endif				/* CONFIG_MCFTMR */
#endif				/* CONFIG_M5272 */

#if defined(CONFIG_M5208) || defined(CONFIG_M5282) || \
    defined(CONFIG_M5271) || defined(CONFIG_M5275)
int interrupt_init(void)
{
	volatile int0_t *intp = (int0_t *) (CONFIG_SYS_INTR_BASE);

	/* Make sure all interrupts are disabled */
#if defined(CONFIG_M5208)
	intp->imrl0 = 0xFFFFFFFF;
	intp->imrh0 = 0xFFFFFFFF;
#else
	intp->imrl0 |= 0x1;
#endif

	enable_interrupts();
	return 0;
}

#if defined(CONFIG_MCFTMR)
void dtimer_intr_setup(void)
{
	volatile int0_t *intp = (int0_t *) (CONFIG_SYS_INTR_BASE);

	intp->icr0[CONFIG_SYS_TMRINTR_NO] = CONFIG_SYS_TMRINTR_PRI;
	intp->imrl0 &= 0xFFFFFFFE;
	intp->imrl0 &= ~CONFIG_SYS_TMRINTR_MASK;
}
#endif				/* CONFIG_MCFTMR */
#endif				/* CONFIG_M5282 | CONFIG_M5271 | CONFIG_M5275 */

#if defined(CONFIG_M5249) || defined(CONFIG_M5253)
int interrupt_init(void)
{
	enable_interrupts();

	return 0;
}

#if defined(CONFIG_MCFTMR)
void dtimer_intr_setup(void)
{
	mbar_writeLong(MCFSIM_IMR, mbar_readLong(MCFSIM_IMR) & ~0x00000400);
	mbar_writeByte(MCFSIM_TIMER2ICR, CONFIG_SYS_TMRINTR_PRI);
}
#endif				/* CONFIG_MCFTMR */
#endif				/* CONFIG_M5249 || CONFIG_M5253 */
