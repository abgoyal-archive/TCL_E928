

#include <common.h>
#include <netdev.h>
#if defined(CONFIG_OMAP1610)
#include <./configs/omap1510.h>
#endif

DECLARE_GLOBAL_DATA_PTR;

#ifdef CONFIG_CS_AUTOBOOT
unsigned long omap_flash_base;
#endif

void flash__init (void);
void ether__init (void);
void set_muxconf_regs (void);
void peripheral_power_enable (void);

#define COMP_MODE_ENABLE ((unsigned int)0x0000EAEF)

static inline void delay (unsigned long loops)
{
	__asm__ volatile ("1:\n"
		"subs %0, %1, #1\n"
		"bne 1b":"=r" (loops):"0" (loops));
}


int board_init (void)
{
	if (machine_is_omap_h2())
		gd->bd->bi_arch_number = MACH_TYPE_OMAP_H2;
	else if (machine_is_omap_innovator())
		gd->bd->bi_arch_number = MACH_TYPE_OMAP_INNOVATOR;
	else
		gd->bd->bi_arch_number = MACH_TYPE_OMAP_GENERIC;

	/* adress of boot parameters */
	gd->bd->bi_boot_params = 0x10000100;

	/* Configure MUX settings */
	set_muxconf_regs ();
	peripheral_power_enable ();

	icache_enable ();

	flash__init ();
	ether__init ();
	return 0;
}


int misc_init_r (void)
{
	/* currently empty */
	return (0);
}

void flash__init (void)
{
#define EMIFS_GlB_Config_REG 0xfffecc0c
	unsigned int regval;

#ifdef CONFIG_CS_AUTOBOOT
	 /* Check swapping of CS0 and CS3, set flash base accordingly */
	omap_flash_base = ((*((u32 *)OMAP_EMIFS_CONFIG_REG) & 0x02) == 0) ?
					PHYS_FLASH_1_BM0 : PHYS_FLASH_1_BM1;
#endif
	regval = *((volatile unsigned int *) EMIFS_GlB_Config_REG);
	/* Turn off write protection for flash devices. */
	regval = regval | 0x0001;
	*((volatile unsigned int *) EMIFS_GlB_Config_REG) = regval;
}
void ether__init (void)
{
#define ETH_CONTROL_REG 0x0400030b

#ifdef CONFIG_H2_OMAP1610
	#define LAN_RESET_REGISTER 0x0400001c

	/* The debug board on which the lan chip resides may not be powered
	 * ON at the same time as the OMAP chip. So wait in a loop until the
	 * lan reset register (on the debug board) is available (powered on)
	 * and reset the lan chip.
	 */

	*((volatile unsigned short *) LAN_RESET_REGISTER) = 0x0000;
	do {
		*((volatile unsigned short *) LAN_RESET_REGISTER) = 0x0001;
		udelay (3);
	} while (*((volatile unsigned short *) LAN_RESET_REGISTER) != 0x0001);

	do {
		*((volatile unsigned short *) LAN_RESET_REGISTER) = 0x0000;
		udelay (3);
	} while (*((volatile unsigned short *) LAN_RESET_REGISTER) != 0x0000);
#endif

	*((volatile unsigned char *) ETH_CONTROL_REG) &= ~0x01;
	udelay (3);
}

int dram_init (void)
{
	gd->bd->bi_dram[0].start = PHYS_SDRAM_1;
	gd->bd->bi_dram[0].size = PHYS_SDRAM_1_SIZE;

	return 0;
}

void set_muxconf_regs (void)
{
	volatile unsigned int *MuxConfReg;
	/* set each registers to its reset value; */
	MuxConfReg =
		(volatile unsigned int *) ((unsigned int) FUNC_MUX_CTRL_0);
	/* setup for UART1 */
	*MuxConfReg &= ~(0x02000000);	/* bit 25 */
	/* setup for UART2 */
	*MuxConfReg &= ~(0x01000000);	/* bit 24 */
	/* Disable Uwire CS Hi-Z */
	*MuxConfReg |= 0x08000000;
	MuxConfReg =
		(volatile unsigned int *) ((unsigned int) FUNC_MUX_CTRL_3);
	*MuxConfReg = 0x00000000;
	MuxConfReg =
		(volatile unsigned int *) ((unsigned int) FUNC_MUX_CTRL_4);
	*MuxConfReg = 0x00000000;
	MuxConfReg =
		(volatile unsigned int *) ((unsigned int) FUNC_MUX_CTRL_5);
	*MuxConfReg = 0x00000000;
	MuxConfReg =
		(volatile unsigned int *) ((unsigned int) FUNC_MUX_CTRL_6);
	/*setup mux for UART3 */
	*MuxConfReg |= 0x00000001;	/* bit3, 1, 0 (mux0 5,5,26) */
	*MuxConfReg &= ~0x0000003e;
	MuxConfReg =
		(volatile unsigned int *) ((unsigned int) FUNC_MUX_CTRL_7);
	*MuxConfReg = 0x00000000;
	MuxConfReg =
		(volatile unsigned int *) ((unsigned int) FUNC_MUX_CTRL_8);
	/* Disable Uwire CS Hi-Z */
	*MuxConfReg |= 0x00001200;	/*bit 9 for CS0 12 for CS3 */
	MuxConfReg =
		(volatile unsigned int *) ((unsigned int) FUNC_MUX_CTRL_9);
	/*  Need to turn on bits 21 and 12 in FUNC_MUX_CTRL_9 so the  */
	/*  hardware will actually use TX and RTS based on bit 25 in  */
	/*  FUNC_MUX_CTRL_0.  I told you this thing was screwy!  */
	*MuxConfReg |= 0x00201000;
	MuxConfReg =
		(volatile unsigned int *) ((unsigned int) FUNC_MUX_CTRL_A);
	*MuxConfReg = 0x00000000;
	MuxConfReg =
		(volatile unsigned int *) ((unsigned int) FUNC_MUX_CTRL_B);
	*MuxConfReg = 0x00000000;
	MuxConfReg =
		(volatile unsigned int *) ((unsigned int) FUNC_MUX_CTRL_C);
	/* setup for UART2 */
	/*  Need to turn on bits 27 and 24 in FUNC_MUX_CTRL_C so the  */
	/*  hardware will actually use TX and RTS based on bit 24 in  */
	/*  FUNC_MUX_CTRL_0. */
	*MuxConfReg |= 0x09000000;
	MuxConfReg =
		(volatile unsigned int *) ((unsigned int) PULL_DWN_CTRL_0);
	*MuxConfReg = 0x00000000;
	MuxConfReg =
		(volatile unsigned int *) ((unsigned int) PULL_DWN_CTRL_1);
	*MuxConfReg = 0x00000000;
	/* mux setup for SD/MMC driver */
	MuxConfReg =
		(volatile unsigned int *) ((unsigned int) PULL_DWN_CTRL_2);
	*MuxConfReg &= 0xFFFE0FFF;
	MuxConfReg =
		(volatile unsigned int *) ((unsigned int) PULL_DWN_CTRL_3);
	*MuxConfReg = 0x00000000;
	MuxConfReg =
		(volatile unsigned int *) ((unsigned int) MOD_CONF_CTRL_0);
	/* bit 13 for MMC2 XOR_CLK */
	*MuxConfReg &= ~(0x00002000);
	/* bit 29 for UART 1 */
	*MuxConfReg &= ~(0x00002000);
	MuxConfReg =
		(volatile unsigned int *) ((unsigned int) FUNC_MUX_CTRL_0);
	/* Configure for USB. Turn on VBUS_CTRL and VBUS_MODE. */
	*MuxConfReg |= 0x000C0000;
	MuxConfReg =
		(volatile unsigned int *) ((unsigned int)USB_TRANSCEIVER_CTRL);
	*MuxConfReg &= ~(0x00000070);
	*MuxConfReg &= ~(0x00000008);
	*MuxConfReg |= 0x00000003;
	*MuxConfReg |= 0x00000180;
	MuxConfReg =
		(volatile unsigned int *) ((unsigned int) MOD_CONF_CTRL_0);
	/* bit 17, software controls VBUS */
	*MuxConfReg &= ~(0x00020000);
	/* Enable USB 48 and 12M clocks */
	*MuxConfReg |= 0x00000200;
	*MuxConfReg &= ~(0x00000180);
	/*2.75V for MMCSDIO1 */
	MuxConfReg =
		(volatile unsigned int *) ((unsigned int) VOLTAGE_CTRL_0);
	*MuxConfReg = 0x00001FE7;
	MuxConfReg =
		(volatile unsigned int *) ((unsigned int) PU_PD_SEL_0);
	*MuxConfReg = 0x00000000;
	MuxConfReg =
		(volatile unsigned int *) ((unsigned int) PU_PD_SEL_1);
	*MuxConfReg = 0x00000000;
	MuxConfReg =
		(volatile unsigned int *) ((unsigned int) PU_PD_SEL_2);
	*MuxConfReg = 0x00000000;
	MuxConfReg =
		(volatile unsigned int *) ((unsigned int) PU_PD_SEL_3);
	*MuxConfReg = 0x00000000;
	MuxConfReg =
		(volatile unsigned int *) ((unsigned int) PU_PD_SEL_4);
	*MuxConfReg = 0x00000000;
	MuxConfReg =
		(volatile unsigned int *) ((unsigned int) PULL_DWN_CTRL_4);
	*MuxConfReg = 0x00000000;
	/* Turn on UART2 48 MHZ clock */
	MuxConfReg =
		(volatile unsigned int *) ((unsigned int) MOD_CONF_CTRL_0);
	*MuxConfReg |= 0x40000000;
	MuxConfReg =
		(volatile unsigned int *) ((unsigned int) USB_OTG_CTRL);
	/* setup for USB VBus detection OMAP161x */
	*MuxConfReg |= 0x00040000;	/* bit 18 */
	MuxConfReg =
		(volatile unsigned int *) ((unsigned int) PU_PD_SEL_2);
	/* PullUps for SD/MMC driver */
	*MuxConfReg |= ~(0xFFFE0FFF);
	MuxConfReg =
		(volatile unsigned int *) ((unsigned int)COMP_MODE_CTRL_0);
	*MuxConfReg = COMP_MODE_ENABLE;
}

void peripheral_power_enable (void)
{
#define UART1_48MHZ_ENABLE	((unsigned short)0x0200)
#define SW_CLOCK_REQUEST	((volatile unsigned short *)0xFFFE0834)

	*SW_CLOCK_REQUEST |= UART1_48MHZ_ENABLE;
}

#ifdef CONFIG_CMD_NET
int board_eth_init(bd_t *bis)
{
	int rc = 0;
#ifdef CONFIG_LAN91C96
	rc = lan91c96_initialize(0, CONFIG_LAN91C96_BASE);
#endif
	return rc;
}
#endif
