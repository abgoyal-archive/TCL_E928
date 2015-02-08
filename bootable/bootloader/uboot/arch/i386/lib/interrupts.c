


#include <common.h>
#include <asm/interrupt.h>

struct irq_action {
	interrupt_handler_t *handler;
	void *arg;
	unsigned int count;
};

static struct irq_action irq_handlers[CONFIG_SYS_NUM_IRQS] = { {0} };
static int spurious_irq_cnt = 0;
static int spurious_irq = 0;

void irq_install_handler(int irq, interrupt_handler_t *handler, void *arg)
{
	int status;

	if (irq < 0 || irq >= CONFIG_SYS_NUM_IRQS) {
		printf("irq_install_handler: bad irq number %d\n", irq);
		return;
	}

	if (irq_handlers[irq].handler != NULL)
		printf("irq_install_handler: 0x%08lx replacing 0x%08lx\n",
		       (ulong) handler,
		       (ulong) irq_handlers[irq].handler);

	status = disable_interrupts ();

	irq_handlers[irq].handler = handler;
	irq_handlers[irq].arg = arg;
	irq_handlers[irq].count = 0;

	unmask_irq(irq);

	if (status)
		enable_interrupts();

	return;
}

void irq_free_handler(int irq)
{
	int status;

	if (irq < 0 || irq >= CONFIG_SYS_NUM_IRQS) {
		printf("irq_free_handler: bad irq number %d\n", irq);
		return;
	}

	status = disable_interrupts ();

	mask_irq(irq);

	irq_handlers[irq].handler = NULL;
	irq_handlers[irq].arg = NULL;

	if (status)
		enable_interrupts();

	return;
}

void do_irq(int hw_irq)
{
	int irq = hw_irq - 0x20;

	if (irq < 0 || irq >= CONFIG_SYS_NUM_IRQS) {
		printf("do_irq: bad irq number %d\n", irq);
		return;
	}

	if (irq_handlers[irq].handler) {
		mask_irq(irq);

		irq_handlers[irq].handler(irq_handlers[irq].arg);
		irq_handlers[irq].count++;

		unmask_irq(irq);
		specific_eoi(irq);

	} else {
		if ((irq & 7) != 7) {
			spurious_irq_cnt++;
			spurious_irq = irq;
		}
	}
}

#if defined(CONFIG_CMD_IRQ)
int do_irqinfo(cmd_tbl_t *cmdtp, int flag, int argc, char *argv[])
{
	int irq;

	printf("Spurious IRQ: %u, last unknown IRQ: %d\n",
	       spurious_irq_cnt, spurious_irq);

	printf ("Interrupt-Information:\n");
	printf ("Nr  Routine   Arg       Count\n");

	for (irq = 0; irq <= CONFIG_SYS_NUM_IRQS; irq++) {
		if (irq_handlers[irq].handler != NULL) {
			printf ("%02d  %08lx  %08lx  %d\n",
					irq,
					(ulong)irq_handlers[irq].handler,
					(ulong)irq_handlers[irq].arg,
					irq_handlers[irq].count);
		}
	}

	return 0;
}
#endif
