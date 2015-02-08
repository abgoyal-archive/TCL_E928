

/* stuff specific for the sc520, but independent of implementation */

#include <common.h>
#include <asm/io.h>
#include <asm/interrupt.h>
#include <asm/ic/sc520.h>

void sc520_timer_isr(void)
{
	/* Ack the GP Timer Interrupt */
	writeb(0x02, &sc520_mmcr->gptmrsta);
}

int timer_init(void)
{
	/* Register the SC520 specific timer interrupt handler */
	register_timer_isr (sc520_timer_isr);

	/* Install interrupt handler for GP Timer 1 */
	irq_install_handler (0, timer_isr, NULL);

	/* Map GP Timer 1 to Master PIC IR0  */
	writeb(0x01, &sc520_mmcr->gp_tmr_int_map[1]);

	/* Disable GP Timers 1 & 2 - Allow configuration writes */
	writew(0x4000, &sc520_mmcr->gptmr1ctl);
	writew(0x4000, &sc520_mmcr->gptmr2ctl);

	/* Reset GP Timers 1 & 2 */
	writew(0x0000, &sc520_mmcr->gptmr1cnt);
	writew(0x0000, &sc520_mmcr->gptmr2cnt);

	/* Setup GP Timer 2 as a 100kHz (10us) prescaler */
	writew(83, &sc520_mmcr->gptmr2maxcmpa);
	writew(0xc001, &sc520_mmcr->gptmr2ctl);

	/* Setup GP Timer 1 as a 1000 Hz (1ms) interrupt generator */
	writew(100, &sc520_mmcr->gptmr1maxcmpa);
	writew(0xe009, &sc520_mmcr->gptmr1ctl);

	unmask_irq (0);

	/* Clear the GP Timer 1 status register to get the show rolling*/
	writeb(0x02, &sc520_mmcr->gptmrsta);

	return 0;
}

/* Allow boards to override udelay implementation */
void __udelay(unsigned long usec)
	__attribute__((weak, alias("sc520_udelay")));

void sc520_udelay(unsigned long usec)
{
	int m = 0;
	long u;
	long temp;

	temp = readw(&sc520_mmcr->swtmrmilli);
	temp = readw(&sc520_mmcr->swtmrmicro);

	do {
		m += readw(&sc520_mmcr->swtmrmilli);
		u = readw(&sc520_mmcr->swtmrmicro) + (m * 1000);
	} while (u < usec);
}
