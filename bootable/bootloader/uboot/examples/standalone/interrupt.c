

#include <common.h>
#include <exports.h>
#include <config.h>

#if defined(CONFIG_MPC5xxx)
#define DFL_IRQ MPC5XXX_IRQ1
#else
#define DFL_IRQ 0
#endif

static void irq_handler (void *arg);

int interrupt (int argc, char *argv[])
{
	int c, irq = -1;

	app_startup (argv);

	if (argc > 1)
		irq = simple_strtoul (argv[1], NULL, 0);
	if ((irq < 0) || (irq > NR_IRQS))
		irq = DFL_IRQ;

	printf ("Installing handler for irq vector %d and doing busy wait\n",
		irq);
	printf ("Press 'q' to quit\n");

	/* Install interrupt handler */
	install_hdlr (irq, irq_handler, NULL);
	while ((c = getc ()) != 'q') {
		printf ("Ok, ok, I am still alive!\n");
	}

	free_hdlr (irq);
	printf ("\nInterrupt handler has been uninstalled\n");

	return (0);
}

static void irq_handler (void *arg)
{
	/* just for demonstration */
	printf ("+");
}
