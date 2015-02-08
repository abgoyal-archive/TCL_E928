

#include <common.h>
#include <mpc8xx.h>
#include "kup.h"

int misc_init_f (void)
{
	volatile immap_t *immap = (immap_t *) CONFIG_SYS_IMMR;
	volatile sysconf8xx_t *siu = &immap->im_siu_conf;

	while (siu->sc_sipend & 0x20000000) {
		/* printf("waiting for 5V VCC\n"); */
		;
	}

	/* RS232 / RS485 default is RS232 */
	immap->im_ioport.iop_padat &= ~(PA_RS485);
	immap->im_ioport.iop_papar &= ~(PA_RS485);
	immap->im_ioport.iop_paodr &= ~(PA_RS485);
	immap->im_ioport.iop_padir |= (PA_RS485);
	return (0);
}


#ifdef CONFIG_IDE_LED
void ide_led (uchar led, uchar status)
{
	volatile immap_t *immap = (immap_t *) CONFIG_SYS_IMMR;

	/* We have one led for both pcmcia slots */
	if (status) {		/* led on */
		immap->im_ioport.iop_padat &= ~(PA_LED_YELLOW);
	} else {
		immap->im_ioport.iop_padat |= (PA_LED_YELLOW);
	}
}
#endif

void poweron_key (void)
{
	volatile immap_t *immap = (immap_t *) CONFIG_SYS_IMMR;

	immap->im_ioport.iop_pcpar &= ~(PC_SWITCH1);
	immap->im_ioport.iop_pcdir &= ~(PC_SWITCH1);

	if (immap->im_ioport.iop_pcdat & (PC_SWITCH1))
		setenv ("key1", "off");
	else
		setenv ("key1", "on");
}
