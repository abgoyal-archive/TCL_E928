

typedef volatile struct microblaze_intc_t {
	int isr; /* interrupt status register */
	int ipr; /* interrupt pending register */
	int ier; /* interrupt enable register */
	int iar; /* interrupt acknowledge register */
	int sie; /* set interrupt enable bits */
	int cie; /* clear interrupt enable bits */
	int ivr; /* interrupt vector register */
	int mer; /* master enable register */
} microblaze_intc_t;

struct irq_action {
	interrupt_handler_t *handler; /* pointer to interrupt rutine */
	void *arg;
	int count; /* number of interrupt */
};

void install_interrupt_handler (int irq, interrupt_handler_t * hdlr,
				       void *arg);
