


#include <common.h>
#include <config.h>
#include <asm/microblaze_intc.h>
#include <asm/asm.h>

void do_reset (void)
{
#ifdef CONFIG_SYS_GPIO_0
	*((unsigned long *)(CONFIG_SYS_GPIO_0_ADDR)) =
	    ++(*((unsigned long *)(CONFIG_SYS_GPIO_0_ADDR)));
#endif
#ifdef CONFIG_SYS_RESET_ADDRESS
	puts ("Reseting board\n");
	asm ("bra r0");
#endif
}

int gpio_init (void)
{
#ifdef CONFIG_SYS_GPIO_0
	*((unsigned long *)(CONFIG_SYS_GPIO_0_ADDR)) = 0xFFFFFFFF;
#endif
	return 0;
}

#ifdef CONFIG_SYS_FSL_2
void fsl_isr2 (void *arg) {
	volatile int num;
	*((unsigned int *)(CONFIG_SYS_GPIO_0_ADDR + 0x4)) =
	    ++(*((unsigned int *)(CONFIG_SYS_GPIO_0_ADDR + 0x4)));
	GET (num, 2);
	NGET (num, 2);
	puts("*");
}

int fsl_init2 (void) {
	puts("fsl_init2\n");
	install_interrupt_handler (FSL_INTR_2, fsl_isr2, NULL);
	return 0;
}
#endif
