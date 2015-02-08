

#include <common.h>
#include <asm/processor.h>
#include <asm/io.h>
#include "sc3.h"
#include <pci.h>
#include <i2c.h>
#include <malloc.h>
#include <netdev.h>

#undef writel
#undef writeb
#define writeb(b,addr) ((*(volatile u8 *) (addr)) = (b))
#define writel(b,addr) ((*(volatile u32 *) (addr)) = (b))

/* write only register to configure things in our CPLD */
#define CPLD_CONTROL_1	0x79000102
#define CPLD_VERSION	0x79000103

#define	IS_CAMERON ((*(unsigned char *)(CPLD_VERSION)== 0x32) ? 1 : 0)

static struct pci_controller hose={0,};


#define USB_CHIP_ENABLE 0x04
#define IDE_BOOSTING 0x40

/* --------------- USB stuff ------------------------------------- */
#ifdef CONFIG_ISP1161_PRESENT

static void initUsbHost (unsigned char *cpldConfig)
{
	int i;
	unsigned long usbBase;
	/*
	 * Read back where init.S has located the USB chip
	 */
	mtdcr (0x012, 0x04);
	usbBase = mfdcr (0x013);
	if (!(usbBase & 0x18000))	/* enabled? */
		return;
	usbBase &= 0xFFF00000;

	/*
	 * to test for the USB controller enable using of CS#4 and DMA 3 for USB access
	 */
	writeb (*cpldConfig | USB_CHIP_ENABLE,CPLD_CONTROL_1);

	/*
	 * first check: is the controller assembled?
	 */
	hcWriteWord (usbBase, 0x5555, HcScratch);
	if (hcReadWord (usbBase, HcScratch) == 0x5555) {
		hcWriteWord (usbBase, 0xAAAA, HcScratch);
		if (hcReadWord (usbBase, HcScratch) == 0xAAAA) {
			if ((hcReadWord (usbBase, HcChipID) & 0xFF00) != 0x6100)
				return;	/* this is not our controller */
		/*
		 * try a software reset. This needs up to 10 seconds (see datasheet)
		 */
			hcWriteDWord (usbBase, 0x00000001, HcCommandStatus);
			for (i = 1000; i > 0; i--) {	/* loop up to 10 seconds */
				udelay (10);
				if (!(hcReadDWord (usbBase, HcCommandStatus) & 0x01))
					break;
			}

			if (!i)
				return;  /* the controller doesn't responding. Broken? */
		/*
		 * OK. USB controller is ready. Initialize it in such way the later driver
		 * can us it (without any knowing about specific implementation)
		 */
			hcWriteDWord (usbBase, 0x00000000, HcControl);
		/*
		 * disable all interrupt sources. Because we
		 * don't know where we come from (hard reset, cold start, soft reset...)
		 */
			hcWriteDWord (usbBase, 0x8000007D, HcInterruptDisable);
		/*
		 * our current setup hardware configuration
		 * - every port power supply can switched indepently
		 * - every port can signal overcurrent
		 * - every port is "outside" and the devices are removeable
		 */
			hcWriteDWord (usbBase, 0x32000902, HcRhDescriptorA);
			hcWriteDWord (usbBase, 0x00060000, HcRhDescriptorB);
		/*
		 * don't forget to switch off power supply of each port
		 * The later running driver can reenable them to find and use
		 * the (maybe) connected devices.
		 *
		 */
			hcWriteDWord (usbBase, 0x00000200, HcRhPortStatus1);
			hcWriteDWord (usbBase, 0x00000200, HcRhPortStatus2);
			hcWriteWord (usbBase, 0x0428, HcHardwareConfiguration);
			hcWriteWord (usbBase, 0x0040, HcDMAConfiguration);
			hcWriteWord (usbBase, 0x0000, HcuPInterruptEnable);
			hcWriteWord (usbBase, 0xA000 | (0x03 << 8) | 27, HcScratch);
		/*
		 * controller is present and usable
		 */
			*cpldConfig |= USB_CHIP_ENABLE;
		}
	}
}
#endif

#if defined(CONFIG_START_IDE)
int board_start_ide(void)
{
	if (IS_CAMERON) {
		puts ("no IDE on cameron board.\n");
		return 0;
	}
	return 1;
}
#endif

static int sc3_cameron_init (void)
{
	/* Set up the Memory Controller for the CAMERON version */
	mtebc (PB4AP, 0x01805940);
	mtebc (PB4CR, 0x7401a000);
	mtebc (PB5AP, 0x01805940);
	mtebc (PB5CR, 0x7401a000);
	mtebc (PB6AP, 0x0);
	mtebc (PB6CR, 0x0);
	mtebc (PB7AP, 0x0);
	mtebc (PB7CR, 0x0);
	return 0;
}

void sc3_read_eeprom (void)
{
	uchar i2c_buffer[18];

	i2c_read (0x50, 0x03, 1, i2c_buffer, 9);
	i2c_buffer[9] = 0;
	setenv ("serial#", (char *)i2c_buffer);

	/* read mac-address from eeprom */
	i2c_read (0x50, 0x11, 1, i2c_buffer, 15);
	i2c_buffer[17] = 0;
	i2c_buffer[16] = i2c_buffer[14];
	i2c_buffer[15] = i2c_buffer[13];
	i2c_buffer[14] = ':';
	i2c_buffer[13] = i2c_buffer[12];
	i2c_buffer[12] = i2c_buffer[11];
	i2c_buffer[11] = ':';
	i2c_buffer[8] = ':';
	i2c_buffer[5] = ':';
	i2c_buffer[2] = ':';
	setenv ("ethaddr", (char *)i2c_buffer);
}

int board_early_init_f (void)
{
	/* write only register to configure things in our CPLD */
	unsigned char cpldConfig_1=0x00;


	writeb (cpldConfig_1, CPLD_CONTROL_1);	/* disable everything in CPLD */

	mtdcr (UIC0SR, 0xFFFFFFFF);    /* clear all ints */
	mtdcr (UIC0ER, 0x00000000);    /* disable all ints */
	mtdcr (UIC0CR, 0x00000000);    /* set all to be non-critical */

	if (IS_CAMERON) {
		sc3_cameron_init();
		mtdcr (0x0B6, 0x18000000);
		mtdcr (UIC0PR, 0xFFFFFFF0);
		mtdcr (UIC0TR, 0x10001030);
	} else {
		mtdcr (0x0B6, 0x0000000);
		mtdcr (UIC0PR, 0xFFFFFFE0);
		mtdcr (UIC0TR, 0x10000020);
	}
	mtdcr (UIC0VCR, 0x00000001);   /* set vect base=0,INT0 highest priority */
	mtdcr (UIC0SR, 0xFFFFFFFF);    /* clear all ints */

	/* setup other implementation specific details */
	mtdcr (CPC0_ECR, 0x60606000);

	mtdcr (CPC0_CR1, 0x000042C0);

	if (IS_CAMERON) {
		mtdcr (CPC0_CR0, 0x01380000);
		/* Setup the GPIOs */
		writel (0x08008000, 0xEF600700);	/* Output states */
		writel (0x00000000, 0xEF600718);	/* Open Drain control */
		writel (0x68098000, 0xEF600704);	/* Output control */
	} else {
		mtdcr (CPC0_CR0,0x00080000);
		/* Setup the GPIOs */
		writel (0x08000000, 0xEF600700);	/* Output states */
		writel (0x14000000, 0xEF600718);	/* Open Drain control */
		writel (0x7C000000, 0xEF600704);	/* Output control */
	}

	/* Code decompression disabled */
	mtdcr (KIAR, KCONF);
	mtdcr (KIDR, 0x2B);

	/* CPC0_ER: enable sleep mode of (currently) unused components */
	/* CPC0_FR: force unused components into sleep mode */
	mtdcr (CPMER, 0x3F800000);
	mtdcr (CPMFR, 0x14000000);

	/* set PLB priority */
	mtdcr (0x87, 0x08000000);

	/* --------------- DMA stuff ------------------------------------- */
	mtdcr (0x126, 0x49200000);

#ifndef IDE_USES_ISA_EMULATION
	cpldConfig_1 |= IDE_BOOSTING;	/* enable faster IDE */
	/* cpldConfig |= 0x01; */	/* enable 8.33MHz output, if *not* present on your baseboard */
	writeb (cpldConfig_1, CPLD_CONTROL_1);
#endif

#ifdef CONFIG_ISP1161_PRESENT
	initUsbHost (&cpldConfig_1);
	writeb (cpldConfig_1, CPLD_CONTROL_1);
#endif
	/* FIXME: for what must we do this */
	*(unsigned long *)0x79000080 = 0x0001;
	return(0);
}

int misc_init_r (void)
{
	char *s1;
	int i, xilinx_val;
	volatile char *xilinx_adr;
	xilinx_adr = (char *)0x79000102;

	*xilinx_adr = 0x00;

/* customer settings ***************************************** */

/* individual settings ***************************************** */
	if ((s1 = getenv ("xilinx"))) {
		i=0;
		xilinx_val = 0;
		while (i < 3 && s1[i]) {
			if (s1[i] >= '0' && s1[i] <= '9')
				xilinx_val = (xilinx_val << 4) + s1[i] - '0';
			else
				if (s1[i] >= 'A' && s1[i] <= 'F')
					xilinx_val = (xilinx_val << 4) + s1[i] - 'A' + 10;
				else
					if (s1[i] >= 'a' && s1[i] <= 'f')
						xilinx_val = (xilinx_val << 4) + s1[i] - 'a' + 10;
					else {
						xilinx_val = -1;
						break;
					}
			i++;
		}
		if (xilinx_val >= 0 && xilinx_val <=255 && i < 3) {
			printf ("Xilinx: set to %s\n", s1);
			*xilinx_adr = (unsigned char) xilinx_val;
		} else
			printf ("Xilinx: rejected value %s\n", s1);
	}
	return 0;
}


#ifdef SC3_DEBUGOUT
static void printCSConfig(int reg,unsigned long ap,unsigned long cr)
{
	const char *bsize[4] = {"8","16","32","?"};
	const unsigned char banks[8] = {1, 2, 4, 8, 16, 32, 64, 128};
	const char *bankaccess[4] = {"disabled", "RO", "WO", "RW"};

#define CYCLE 30  /* time of one clock (based on 33MHz) */

	printf("\nCS#%d",reg);
	if (!(cr & 0x00018000))
		puts(" unused");
	else {
		if (((cr&0xFFF00000U) & ((banks[(cr & 0x000E0000) >> 17]-1) << 20)))
			puts(" Address is not multiple of bank size!");

		printf("\n -%s bit device",
			bsize[(cr & 0x00006000) >> 13]);
		printf(" at 0x%08lX", cr & 0xFFF00000U);
		printf(" size: %u MB", banks[(cr & 0x000E0000) >> 17]);
		printf(" rights: %s", bankaccess[(cr & 0x00018000) >> 15]);
		if (ap & 0x80000000) {
			printf("\n -Burst device (%luns/%luns)",
				(((ap & 0x7C000000) >> 26) + 1) * CYCLE,
				(((ap & 0x03800000) >> 23) + 1) * CYCLE);
		} else {
			printf("\n -Non burst device, active cycle %luns",
				(((ap & 0x7F800000) >> 23) + 1) * CYCLE);
			printf("\n -Address setup %luns",
				((ap & 0xC0000) >> 18) * CYCLE);
			printf("\n -CS active to RD %luns/WR %luns",
				((ap & 0x30000) >> 16) * CYCLE,
				((ap & 0xC000) >> 14) * CYCLE);
			printf("\n -WR to CS inactive %luns",
				((ap & 0x3000) >> 12) * CYCLE);
			printf("\n -Hold after access %luns",
				((ap & 0xE00) >> 9) * CYCLE);
			printf("\n -Ready is %sabled",
				ap & 0x100 ? "en" : "dis");
		}
	}
}
#endif

#ifdef SC3_DEBUGOUT

static unsigned int ap[] = {PB0AP, PB1AP, PB2AP, PB3AP, PB4AP,
				PB5AP, PB6AP, PB7AP};
static unsigned int cr[] = {PB0CR, PB1CR, PB2CR, PB3CR, PB4CR,
				PB5CR, PB6CR, PB7CR};

static int show_reg (int nr)
{
	unsigned long ul1, ul2;

	mtdcr (EBC0_CFGADDR, ap[nr]);
	ul1 = mfdcr (EBC0_CFGDATA);
	mtdcr (EBC0_CFGADDR, cr[nr]);
	ul2 = mfdcr(EBC0_CFGDATA);
	printCSConfig(nr, ul1, ul2);
	return 0;
}
#endif

int checkboard (void)
{
#ifdef SC3_DEBUGOUT
	unsigned long ul1;
	int	i;

	for (i = 0; i < 8; i++) {
		show_reg (i);
	}

	mtdcr (EBC0_CFGADDR, EBC0_CFG);
	ul1 = mfdcr (EBC0_CFGDATA);

	puts ("\nGeneral configuration:\n");

	if (ul1 & 0x80000000)
		printf(" -External Bus is always driven\n");

	if (ul1 & 0x400000)
		printf(" -CS signals are always driven\n");

	if (ul1 & 0x20000)
		printf(" -PowerDown after %lu clocks\n",
			(ul1 & 0x1F000) >> 7);

	switch (ul1 & 0xC0000)
	{
	case 0xC0000:
		printf(" -No external master present\n");
		break;
	case 0x00000:
		printf(" -8 bit external master present\n");
		break;
	case 0x40000:
		printf(" -16 bit external master present\n");
		break;
	case 0x80000:
		printf(" -32 bit external master present\n");
		break;
	}

	switch (ul1 & 0x300000)
	{
	case 0x300000:
		printf(" -Prefetch: Illegal setting!\n");
		break;
	case 0x000000:
		printf(" -1 doubleword prefetch\n");
		break;
	case 0x100000:
		printf(" -2 doublewords prefetch\n");
		break;
	case 0x200000:
		printf(" -4 doublewords prefetch\n");
		break;
	}
	putc ('\n');
#endif
	printf("Board: SolidCard III %s %s version.\n",
		(IS_CAMERON ? "Cameron" : "Eurodesign"), CONFIG_SC3_VERSION);
	return 0;
}

static int printSDRAMConfig(char reg, unsigned long cr)
{
	const int bisize[8]={4, 8, 16, 32, 64, 128, 256, 0};
#ifdef SC3_DEBUGOUT
	const char *basize[8]=
		{"4", "8", "16", "32", "64", "128", "256", "Reserved"};

	printf("SDRAM bank %d",reg);

	if (!(cr & 0x01))
		puts(" disabled\n");
	else {
		printf(" at 0x%08lX, size %s MB",cr & 0xFFC00000,basize[(cr&0xE0000)>>17]);
		printf(" mode %lu\n",((cr & 0xE000)>>13)+1);
	}
#endif

	if (cr & 0x01)
		return(bisize[(cr & 0xE0000) >> 17]);

	return 0;
}

#ifdef SC3_DEBUGOUT
static unsigned int mbcf[] = {SDRAM0_B0CR, SDRAM0_B1CR, SDRAM0_B2CR, SDRAM0_B3CR};
#endif

phys_size_t initdram (int board_type)
{
	unsigned int mems=0;
	unsigned long ul1;

#ifdef SC3_DEBUGOUT
	unsigned long ul2;
	int	i;

	puts("\nSDRAM configuration:\n");

	mtdcr (SDRAM0_CFGADDR, SDRAM0_CFG);
	ul1 = mfdcr(SDRAM0_CFGDATA);

	if (!(ul1 & 0x80000000)) {
		puts(" Controller disabled\n");
		return 0;
	}
	for (i = 0; i < 4; i++) {
		mtdcr (SDRAM0_CFGADDR, mbcf[i]);
		ul1 = mfdcr (SDRAM0_CFGDATA);
		mems += printSDRAMConfig (i, ul1);
	}

	mtdcr (SDRAM0_CFGADDR, SDRAM0_TR);
	ul1 = mfdcr(SDRAM0_CFGDATA);

	printf ("Timing:\n -CAS latency %lu\n", ((ul1 & 0x1800000) >> 23)+1);
	printf (" -Precharge %lu (PTA) \n", ((ul1 & 0xC0000) >> 18) + 1);
	printf (" -R/W to Precharge %lu (CTP)\n", ((ul1 & 0x30000) >> 16) + 1);
	printf (" -Leadoff %lu\n", ((ul1 & 0xC000) >> 14) + 1);
	printf (" -CAS to RAS %lu\n", ((ul1 & 0x1C) >> 2) + 4);
	printf (" -RAS to CAS %lu\n", ((ul1 & 0x3) + 1));
	puts ("Misc:\n");
	mtdcr (SDRAM0_CFGADDR, SDRAM0_RTR);
	ul1 = mfdcr(SDRAM0_CFGDATA);
	printf (" -Refresh rate: %luns\n", (ul1 >> 16) * 7);

	mtdcr(SDRAM0_CFGADDR,SDRAM0_PMIT);
	ul2=mfdcr(SDRAM0_CFGDATA);

	mtdcr(SDRAM0_CFGADDR,SDRAM0_CFG);
	ul1=mfdcr(SDRAM0_CFGDATA);

	if (ul1 & 0x20000000)
		printf(" -Power Down after: %luns\n",
			((ul2 & 0xFFC00000) >> 22) * 7);
	else
		puts(" -Power Down disabled\n");

	if (ul1 & 0x40000000)
		printf(" -Self refresh feature active\n");
	else
		puts(" -Self refresh disabled\n");

	if (ul1 & 0x10000000)
		puts(" -ECC enabled\n");
	else
		puts(" -ECC disabled\n");

	if (ul1 & 0x8000000)
		puts(" -Using registered SDRAM\n");

	if (!(ul1 & 0x6000000))
		puts(" -Using 32 bit data width\n");
	else
		puts(" -Illegal data width!\n");

	if (ul1 & 0x400000)
		puts(" -ECC drivers inactive\n");
	else
		puts(" -ECC drivers active\n");

	if (ul1 & 0x200000)
		puts(" -Memory lines always active outputs\n");
	else
		puts(" -Memory lines only at write cycles active outputs\n");

	mtdcr (SDRAM0_CFGADDR, SDRAM0_STATUS);
	ul1 = mfdcr (SDRAM0_CFGDATA);
	if (ul1 & 0x80000000)
		puts(" -SDRAM Controller ready\n");
	else
		puts(" -SDRAM Controller not ready\n");

	if (ul1 & 0x4000000)
		puts(" -SDRAM in self refresh mode!\n");

	return (mems * 1024 * 1024);
#else
	mtdcr (SDRAM0_CFGADDR, SDRAM0_B0CR);
	ul1 = mfdcr (SDRAM0_CFGDATA);
	mems = printSDRAMConfig (0, ul1);

	mtdcr (SDRAM0_CFGADDR, SDRAM0_B1CR);
	ul1 = mfdcr (SDRAM0_CFGDATA);
	mems += printSDRAMConfig (1, ul1);

	mtdcr (SDRAM0_CFGADDR, SDRAM0_B2CR);
	ul1 = mfdcr(SDRAM0_CFGDATA);
	mems += printSDRAMConfig (2, ul1);

	mtdcr (SDRAM0_CFGADDR, SDRAM0_B3CR);
	ul1 = mfdcr(SDRAM0_CFGDATA);
	mems += printSDRAMConfig (3, ul1);

	return (mems * 1024 * 1024);
#endif
}

static void pci_solidcard3_fixup_irq (struct pci_controller *hose, pci_dev_t dev)
{
	unsigned char int_line = 0xff;

	switch (PCI_DEV(dev)) {
	case 10:
		int_line = 31; /* INT A */
		POST_OUT(0x42);
		break;

	case 11:
		int_line = 30; /* INT B */
		POST_OUT(0x43);
		break;

	case 12:
		int_line = 29; /* INT C */
		POST_OUT(0x44);
		break;

	case 13:
		int_line = 28; /* INT D */
		POST_OUT(0x45);
		break;
	}
	pci_hose_write_config_byte(hose, dev, PCI_INTERRUPT_LINE, int_line);
}

extern void pci_405gp_init(struct pci_controller *hose);
extern void pci_405gp_fixup_irq(struct pci_controller *hose, pci_dev_t dev);
extern void pci_405gp_setup_bridge(struct pci_controller *hose, pci_dev_t dev,struct pci_config_table *entry);
static struct pci_config_table pci_solidcard3_config_table[] =
{
/* Host to PCI Bridge device (405GP) */
	{
		vendor: 0x1014,
		device: 0x0156,
		class: PCI_CLASS_BRIDGE_HOST,
		bus: 0,
		dev: 0,
		func: 0,
		config_device: pci_405gp_setup_bridge
	},
	{ }
};


void pci_init_board(void)
{
	POST_OUT(0x41);
	hose.fixup_irq    = pci_solidcard3_fixup_irq;
	hose.config_table = pci_solidcard3_config_table;
	pci_405gp_init(&hose);
}

int board_eth_init(bd_t *bis)
{
	return pci_eth_init(bis);
}
