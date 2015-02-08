

/* CPU specific interrupt routine */
#include <common.h>
#include <asm/immap.h>

int interrupt_init(void)
{
	volatile int0_t *intp = (int0_t *) (CONFIG_SYS_INTR_BASE);

	/* Make sure all interrupts are disabled */
	intp->imrl0 |= 0x1;

	enable_interrupts();
	return 0;
}

#if defined(CONFIG_MCFTMR)
void dtimer_intr_setup(void)
{
	volatile int0_t *intp = (int0_t *) (CONFIG_SYS_INTR_BASE);

	intp->icr0[CONFIG_SYS_TMRINTR_NO] = CONFIG_SYS_TMRINTR_PRI;
	intp->imrl0 &= ~INTC_IPRL_INT0;
	intp->imrl0 &= ~CONFIG_SYS_TMRINTR_MASK;
}
#endif
