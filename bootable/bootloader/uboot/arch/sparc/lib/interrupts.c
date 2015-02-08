

#include <common.h>
#include <asm/processor.h>
#include <asm/irq.h>

/* Implemented by SPARC CPUs */
extern int interrupt_init_cpu(void);
extern void timer_interrupt_cpu(void *arg);
extern int timer_interrupt_init_cpu(void);

int intLock(void)
{
	unsigned int pil;

	pil = get_pil();

	/* set PIL to 15 ==> no pending interrupts will interrupt CPU */
	set_pil(15);

	return pil;
}

void intUnlock(int oldLevel)
{
	set_pil(oldLevel);
}

void enable_interrupts(void)
{
	set_pil(0);		/* enable all interrupts */
}

int disable_interrupts(void)
{
	return intLock();
}

int interrupt_init(void)
{
	int ret;

	/* call cpu specific function from $(CPU)/interrupts.c */
	ret = interrupt_init_cpu();

	/* enable global interrupts */
	enable_interrupts();

	return ret;
}

/* timer interrupt/overflow counter */
static volatile ulong timestamp = 0;

void timer_interrupt(struct pt_regs *regs)
{
	/* call cpu specific function from $(CPU)/interrupts.c */
	timer_interrupt_cpu((void *)regs);

	timestamp++;
}

void reset_timer(void)
{
	timestamp = 0;
}

ulong get_timer(ulong base)
{
	return (timestamp - base);
}

void set_timer(ulong t)
{
	timestamp = t;
}

void timer_interrupt_init(void)
{
	int irq;

	reset_timer();

	irq = timer_interrupt_init_cpu();

	if (irq < 0) {
		/* cpu specific code handled the interrupt registration it self */
		return;
	}
	/* register interrupt handler for timer */
	irq_install_handler(irq, (void (*)(void *))timer_interrupt, NULL);
}
