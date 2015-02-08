

#include <common.h>
#include <mpc86xx.h>
#include <command.h>
#include <asm/processor.h>

int interrupt_init_cpu(unsigned long *decrementer_count)
{
	volatile immap_t *immr = (immap_t *)CONFIG_SYS_IMMR;
	volatile ccsr_pic_t *pic = &immr->im_pic;

	pic->gcr = MPC86xx_PICGCR_RST;
	while (pic->gcr & MPC86xx_PICGCR_RST)
		;
	pic->gcr = MPC86xx_PICGCR_MODE;

	*decrementer_count = get_tbclk() / CONFIG_SYS_HZ;
	debug("interrupt init: tbclk() = %d MHz, decrementer_count = %ld\n",
	      (get_tbclk() / 1000000),
	      *decrementer_count);

#ifdef CONFIG_INTERRUPTS

	pic->iivpr1 = 0x810001;	/* 50220 enable mcm interrupts */
	debug("iivpr1@%x = %x\n", &pic->iivpr1, pic->iivpr1);

	pic->iivpr2 = 0x810002;	/* 50240 enable ddr interrupts */
	debug("iivpr2@%x = %x\n", &pic->iivpr2, pic->iivpr2);

	pic->iivpr3 = 0x810003;	/* 50260 enable lbc interrupts */
	debug("iivpr3@%x = %x\n", &pic->iivpr3, pic->iivpr3);

#if defined(CONFIG_PCI1) || defined(CONFIG_PCIE1)
	pic->iivpr8 = 0x810008;	/* enable pcie1 interrupts */
	debug("iivpr8@%x = %x\n", &pic->iivpr8, pic->iivpr8);
#endif
#if defined(CONFIG_PCI2) || defined(CONFIG_PCIE2)
	pic->iivpr9 = 0x810009;	/* enable pcie2 interrupts */
	debug("iivpr9@%x = %x\n", &pic->iivpr9, pic->iivpr9);
#endif

	pic->ctpr = 0;	/* 40080 clear current task priority register */
#endif

	return 0;
}

void timer_interrupt_cpu(struct pt_regs *regs)
{
	/* nothing to do here */
}

void irq_install_handler(int vec, interrupt_handler_t *handler, void *arg)
{
}

void irq_free_handler(int vec)
{
}

int do_irqinfo(cmd_tbl_t *cmdtp, int flag, int argc, char *argv[])
{
	return 0;
}

void external_interrupt(struct pt_regs *regs)
{
	puts("external_interrupt (oops!)\n");
}
