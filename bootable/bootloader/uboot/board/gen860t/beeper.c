

#include <common.h>
#include <mpc8xx.h>
#include <asm/8xx_immap.h>
#include <linux/ctype.h>


void init_beeper (void)
{
	volatile immap_t *immap = (immap_t *) CONFIG_SYS_IMMR;

	immap->im_cpmtimer.cpmt_tgcr &= ~TGCR_RST1 | TGCR_STP1;
	immap->im_cpmtimer.cpmt_tmr1 = ((33 << TMR_PS_SHIFT) & TMR_PS_MSK)
		| TMR_OM | TMR_FRR | TMR_ICLK_IN_GEN;
	immap->im_cpmtimer.cpmt_tcn1 = 0;
	immap->im_cpmtimer.cpmt_ter1 = 0xffff;
	immap->im_cpmtimer.cpmt_tgcr |= TGCR_RST1;
}

void set_beeper_frequency (uint frequency)
{
#define FREQ_LIMIT	2500

	volatile immap_t *immap = (immap_t *) CONFIG_SYS_IMMR;

	/*
	 * Compute timer ticks given desired frequency.  The timer is set up
	 * to count 0.5 uS per tick and it takes two ticks per cycle (Hz).
	 */
	if (frequency > FREQ_LIMIT)
		frequency = FREQ_LIMIT;
	frequency = 1000000 / frequency;
	immap->im_cpmtimer.cpmt_trr1 = (ushort) frequency;
}

void beeper_on (void)
{
	volatile immap_t *immap = (immap_t *) CONFIG_SYS_IMMR;

	immap->im_cpmtimer.cpmt_tgcr &= ~TGCR_STP1;
}

void beeper_off (void)
{
	volatile immap_t *immap = (immap_t *) CONFIG_SYS_IMMR;

	immap->im_cpmtimer.cpmt_tgcr |= TGCR_STP1;
}

void set_beeper_volume (int steps)
{
	volatile immap_t *immap = (immap_t *) CONFIG_SYS_IMMR;
	int i;

	if (steps >= 0) {
		for (i = 0; i < (steps >= 64 ? 64 : steps); i++) {
			immap->im_cpm.cp_pbodr &= ~(0x80000000 >> 19);
			udelay (1);
			immap->im_cpm.cp_pbodr |= (0x80000000 >> 19);
			udelay (1);
		}
	} else {
		for (i = 0; i > (steps <= -64 ? -64 : steps); i--) {
			immap->im_cpm.cp_pbdat &= ~(0x80000000 >> 19);
			udelay (1);
			immap->im_cpm.cp_pbdat |= (0x80000000 >> 19);
			udelay (1);
		}
	}
}

int do_beeper (char *sequence)
{
#define DELIMITER	';'

	int args[4];
	int i;
	int val;
	char *p = sequence;
	char *tp;

	/*
	 * Parse the control sequence.  This is a really simple parser
	 * without any real error checking.  You can probably blow it
	 * up really easily.
	 */
	if (*p == '\0' || !isdigit (*p)) {
		printf ("%s:%d: null or invalid string (%s)\n",
			__FILE__, __LINE__, p);
		return 0;
	}

	i = 0;
	while (*p != '\0') {
		while (*p != DELIMITER) {
			if (i > 3)
				i = 0;
			val = (int) simple_strtol (p, &tp, 0);
			if (tp == p) {
				printf ("%s:%d: no digits or bad format\n",
					__FILE__, __LINE__);
				return 0;
			} else {
				args[i] = val;
			}

			i++;
			if (*tp == DELIMITER)
				p = tp;
			else
				p = ++tp;
		}
		p++;

		/*
		 * Well, we got something that has a chance of being correct
		 */
#if 0
		for (i = 0; i < 4; i++) {
			printf ("%s:%d:arg %d = %d\n", __FILE__, __LINE__, i,
				args[i]);
		}
		printf ("\n");
#endif
		set_beeper_frequency (args[0]);
		set_beeper_volume (args[1]);
		beeper_on ();
		udelay (1000 * args[2]);
		beeper_off ();
		udelay (1000 * args[3]);
	}
	return 1;
}
