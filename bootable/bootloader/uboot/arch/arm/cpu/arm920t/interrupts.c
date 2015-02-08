

#include <common.h>
#include <asm/proc-armv/ptrace.h>

#if defined (CONFIG_ARCH_INTEGRATOR)
void do_irq (struct pt_regs *pt_regs)
{
	/* ASSUMED to be a timer interrupt  */
	/* Just clear it - count handled in */
	/* integratorap.c                   */
	*(volatile ulong *)(CONFIG_SYS_TIMERBASE + 0x0C) = 0;
}
#endif
