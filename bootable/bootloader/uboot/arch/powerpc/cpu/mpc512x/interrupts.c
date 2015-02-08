

#include <common.h>

DECLARE_GLOBAL_DATA_PTR;

struct irq_action {
	interrupt_handler_t *handler;
	void *arg;
	ulong count;
};

int interrupt_init_cpu (unsigned *decrementer_count)
{
	*decrementer_count = get_tbclk () / CONFIG_SYS_HZ;

	return 0;
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
