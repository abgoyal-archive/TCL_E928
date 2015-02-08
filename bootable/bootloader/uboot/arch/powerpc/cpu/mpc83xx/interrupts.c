

#include <common.h>
#include <command.h>
#include <mpc83xx.h>
#include <asm/processor.h>

DECLARE_GLOBAL_DATA_PTR;

struct irq_action {
	interrupt_handler_t *handler;
	void *arg;
	ulong count;
};

int interrupt_init_cpu (unsigned *decrementer_count)
{
	volatile immap_t *immr = (immap_t *) CONFIG_SYS_IMMR;

	*decrementer_count = (gd->bus_clk / 4) / CONFIG_SYS_HZ;

	/* Enable e300 time base */

	immr->sysconf.spcr |= 0x00400000;

	return 0;
}



void external_interrupt (struct pt_regs *regs)
{
}



void
irq_install_handler (int irq, interrupt_handler_t * handler, void *arg)
{
}


void irq_free_handler (int irq)
{
}


void timer_interrupt_cpu (struct pt_regs *regs)
{
	/* nothing to do here */
	return;
}


#if defined(CONFIG_CMD_IRQ)

/* ripped this out of ppc4xx/interrupts.c */


void
do_irqinfo(cmd_tbl_t *cmdtp, bd_t *bd, int flag, int argc, char *argv[])
{
}

#endif
