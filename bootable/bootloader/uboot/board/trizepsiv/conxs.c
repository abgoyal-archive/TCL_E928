

#include <common.h>
#include <asm/arch/pxa-regs.h>
#include <netdev.h>

DECLARE_GLOBAL_DATA_PTR;

#define		RH_A_PSM	(1 << 8)	/* power switching mode */
#define		RH_A_NPS	(1 << 9)	/* no power switching */

extern struct serial_device serial_ffuart_device;
extern struct serial_device serial_btuart_device;
extern struct serial_device serial_stuart_device;

#if CONFIG_POLARIS
#define BOOT_CONSOLE	"serial_stuart"
#else
#define BOOT_CONSOLE	"serial_ffuart"
#endif
/* ------------------------------------------------------------------------- */


int usb_board_init(void)
{
	UHCHR = (UHCHR | UHCHR_PCPL | UHCHR_PSPL) &
		~(UHCHR_SSEP0 | UHCHR_SSEP1 | UHCHR_SSEP2 | UHCHR_SSE);

	UHCHR |= UHCHR_FSBIR;

	while (UHCHR & UHCHR_FSBIR);

	UHCHR &= ~UHCHR_SSE;
	UHCHIE = (UHCHIE_UPRIE | UHCHIE_RWIE);

	/* Clear any OTG Pin Hold */
	if (PSSR & PSSR_OTGPH)
		PSSR |= PSSR_OTGPH;

	UHCRHDA &= ~(RH_A_NPS);
	UHCRHDA |= RH_A_PSM;

	/* Set port power control mask bits, only 3 ports. */
	UHCRHDB |= (0x7<<17);

	return 0;
}

void usb_board_init_fail(void)
{
	return;
}

void usb_board_stop(void)
{
	UHCHR |= UHCHR_FHR;
	udelay(11);
	UHCHR &= ~UHCHR_FHR;

	UHCCOMS |= 1;
	udelay(10);

	CKEN &= ~CKEN10_USBHOST;

	return;
}

int board_init (void)
{
	/* memory and cpu-speed are setup before relocation */
	/* so we do _nothing_ here */

	/* arch number of ConXS Board */
	gd->bd->bi_arch_number = 776;

	/* adress of boot parameters */
	gd->bd->bi_boot_params = 0xa000003c;

	return 0;
}

int board_late_init(void)
{
#if defined(CONFIG_SERIAL_MULTI)
	char *console=getenv("boot_console");

	if ((console == NULL) || (strcmp(console,"serial_btuart") &&
		strcmp(console,"serial_stuart") &&
		strcmp(console,"serial_ffuart"))) {
			console = BOOT_CONSOLE;
	}
	setenv("stdout",console);
	setenv("stdin", console);
	setenv("stderr",console);
#endif
	return 0;
}

struct serial_device *default_serial_console (void)
{
	return &serial_ffuart_device;
}

int dram_init (void)
{
	gd->bd->bi_dram[0].start = PHYS_SDRAM_1;
	gd->bd->bi_dram[0].size = PHYS_SDRAM_1_SIZE;
	gd->bd->bi_dram[1].start = PHYS_SDRAM_2;
	gd->bd->bi_dram[1].size = PHYS_SDRAM_2_SIZE;
	gd->bd->bi_dram[2].start = PHYS_SDRAM_3;
	gd->bd->bi_dram[2].size = PHYS_SDRAM_3_SIZE;
	gd->bd->bi_dram[3].start = PHYS_SDRAM_4;
	gd->bd->bi_dram[3].size = PHYS_SDRAM_4_SIZE;

	return 0;
}

#ifdef CONFIG_DRIVER_DM9000
int board_eth_init(bd_t *bis)
{
	return dm9000_initialize(bis);
}
#endif
