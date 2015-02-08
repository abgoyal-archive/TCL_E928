

/* CPU specific interrupt routine */
#include <common.h>
#include <asm/immap.h>

int interrupt_init(void)
{
	volatile int0_t *intp = (int0_t *) (CONFIG_SYS_INTR_BASE);

	/* Make sure all interrupts are disabled */
	intp->imrh0 |= 0xFFFFFFFF;
	intp->imrl0 |= 0xFFFFFFFF;

	enable_interrupts();

	return 0;
}

#if defined(CONFIG_SLTTMR)
void dtimer_intr_setup(void)
{
	volatile int0_t *intp = (int0_t *) (CONFIG_SYS_INTR_BASE);

	intp->icr0[CONFIG_SYS_TMRINTR_NO] = CONFIG_SYS_TMRINTR_PRI;
	intp->imrh0 &= ~CONFIG_SYS_TMRINTR_MASK;
}
#endif
