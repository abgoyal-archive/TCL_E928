

#include <common.h>
#include <asm/microblaze_timer.h>
#include <asm/microblaze_intc.h>

volatile int timestamp = 0;

void reset_timer (void)
{
	timestamp = 0;
}

#ifdef CONFIG_SYS_TIMER_0
ulong get_timer (ulong base)
{
	return (timestamp - base);
}
#else
ulong get_timer (ulong base)
{
	return (timestamp++ - base);
}
#endif

void set_timer (ulong t)
{
	timestamp = t;
}

#ifdef CONFIG_SYS_INTC_0
#ifdef CONFIG_SYS_TIMER_0
microblaze_timer_t *tmr = (microblaze_timer_t *) (CONFIG_SYS_TIMER_0_ADDR);

void timer_isr (void *arg)
{
	timestamp++;
	tmr->control = tmr->control | TIMER_INTERRUPT;
}

int timer_init (void)
{
	tmr->loadreg = CONFIG_SYS_TIMER_0_PRELOAD;
	tmr->control = TIMER_INTERRUPT | TIMER_RESET;
	tmr->control =
	    TIMER_ENABLE | TIMER_ENABLE_INTR | TIMER_RELOAD | TIMER_DOWN_COUNT;
	reset_timer ();
	install_interrupt_handler (CONFIG_SYS_TIMER_0_IRQ, timer_isr, (void *)tmr);
	return 0;
}
#endif
#endif
