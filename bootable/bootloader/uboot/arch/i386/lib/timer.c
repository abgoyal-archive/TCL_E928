

#include <common.h>
#include <malloc.h>
#include <asm/io.h>
#include <asm/i8254.h>
#include <asm/ibmpc.h>

struct timer_isr_function {
	struct timer_isr_function *next;
	timer_fnc_t *isr_func;
};

static struct timer_isr_function *first_timer_isr = NULL;
static volatile unsigned long system_ticks = 0;

int register_timer_isr (timer_fnc_t *isr_func)
{
	struct timer_isr_function *new_func;
	struct timer_isr_function *temp;
	int flag;

	new_func = malloc(sizeof(struct timer_isr_function));

	if (new_func == NULL)
		return 1;

	new_func->isr_func = isr_func;
	new_func->next = NULL;

	/*
	 *  Don't allow timer interrupts while the
	 *  linked list is being modified
	 */
	flag = disable_interrupts ();

	if (first_timer_isr == NULL) {
		first_timer_isr = new_func;
	} else {
		temp = first_timer_isr;
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new_func;
	}

	if (flag)
		enable_interrupts ();

	return 0;
}

void timer_isr(void *unused)
{
	struct timer_isr_function *temp = first_timer_isr;

	system_ticks++;

	/* Execute each registered function */
	while (temp != NULL) {
		temp->isr_func ();
		temp = temp->next;
	}
}

void reset_timer (void)
{
	system_ticks = 0;
}

ulong get_timer (ulong base)
{
	return (system_ticks - base);
}

void set_timer (ulong t)
{
	system_ticks = t;
}
