


#include <common.h>
#include <mpc8xx.h>
#include <mpc8xx_irq.h>
#include <asm/processor.h>
#include <commproc.h>
#include <command.h>

int interrupt_init_cpu (unsigned *decrementer_count)
{
#if defined(DEBUG) && !defined(CONFIG_AMIGAONEG3SE)
	printf("interrupt_init: GT main cause reg: %08x:%08x\n",
	       GTREGREAD(LOW_INTERRUPT_CAUSE_REGISTER),
	       GTREGREAD(HIGH_INTERRUPT_CAUSE_REGISTER));
	printf("interrupt_init: ethernet cause regs: %08x %08x %08x\n",
	       GTREGREAD(ETHERNET0_INTERRUPT_CAUSE_REGISTER),
	       GTREGREAD(ETHERNET1_INTERRUPT_CAUSE_REGISTER),
	       GTREGREAD(ETHERNET2_INTERRUPT_CAUSE_REGISTER));
	printf("interrupt_init: ethernet mask regs:  %08x %08x %08x\n",
	       GTREGREAD(ETHERNET0_INTERRUPT_MASK_REGISTER),
	       GTREGREAD(ETHERNET1_INTERRUPT_MASK_REGISTER),
	       GTREGREAD(ETHERNET2_INTERRUPT_MASK_REGISTER));
	puts("interrupt_init: setting decrementer_count\n");
#endif
	*decrementer_count = get_tbclk() / CONFIG_SYS_HZ;

	return (0);
}

/****************************************************************************/

void
external_interrupt(struct pt_regs *regs)
{
	puts("external_interrupt (oops!)\n");
}

volatile ulong timestamp = 0;

void
timer_interrupt_cpu (struct pt_regs *regs)
{
	/* nothing to do here */
	return;
}

/****************************************************************************/


void
irq_install_handler(int vec, interrupt_handler_t *handler, void *arg)
{

}

void
irq_free_handler(int vec)
{

}

/****************************************************************************/

void
do_irqinfo(cmd_tbl_t *cmdtp, bd_t *bd, int flag, int argc, char *argv[])
{
	puts("IRQ related functions are unimplemented currently.\n");
}
