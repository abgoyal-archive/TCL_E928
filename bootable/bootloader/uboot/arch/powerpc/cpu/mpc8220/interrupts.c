


#include <common.h>
#include <asm/processor.h>
#include <command.h>

int interrupt_init_cpu (ulong * decrementer_count)
{
	*decrementer_count = get_tbclk () / CONFIG_SYS_HZ;

	return (0);
}

/****************************************************************************/

void external_interrupt (struct pt_regs *regs)
{
	puts ("external_interrupt (oops!)\n");
}

void timer_interrupt_cpu (struct pt_regs *regs)
{
	/* nothing to do here */
	return;
}

/****************************************************************************/


void irq_install_handler (int vec, interrupt_handler_t * handler, void *arg)
{

}

void irq_free_handler (int vec)
{

}

/****************************************************************************/

void
do_irqinfo (cmd_tbl_t * cmdtp, bd_t * bd, int flag, int argc, char *argv[])
{
	puts ("IRQ related functions are unimplemented currently.\n");
}
