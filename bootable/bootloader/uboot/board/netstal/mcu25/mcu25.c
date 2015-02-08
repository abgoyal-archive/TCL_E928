

#include  <common.h>
#include  <ppc4xx.h>
#include  <asm/processor.h>
#include  <asm/io.h>
#include  <asm/u-boot.h>
#include  "../common/nm.h"

DECLARE_GLOBAL_DATA_PTR;

#define MCU25_SLOT_ADDRESS		(0x7A000000 + 0x0A)
#define MCU25_DIGITAL_IO_REGISTER	(0x7A000000 + 0xc0)

#define MCU25_LED_REGISTER_ADDRESS	(0x7C000000 + 0x10)
#define MCU25_VERSIONS_REGISTER	(0x7C000000 + 0x0C)
#define MCU25_IO_CONFIGURATION		(0x7C000000 + 0x0e)
#define MCU_SW_INSTALL_REQUESTED	0x08

#define SDRAM_LEN	(32 << 20)	/* 32 MB - RAM */


#define CPC0_CR0_VALUE	0x0007F03C
#define CPC0_CR1_VALUE	0x00004051

int board_early_init_f (void)
{
	/* Documented in A-1171
	 *
	 * Interrupt controller setup for the MCU25 board.
	 * Note: IRQ 0-15  405GP internally generated; high; level sensitive
	 *       IRQ 16    405GP internally generated; low; level sensitive
	 *      IRQ 17-24 RESERVED/UNUSED
	 *      IRQ 31 (EXT IRQ 6) (unused)
	 */
	mtdcr(UIC0SR, 0xFFFFFFFF); /* clear all ints */
	mtdcr(UIC0ER, 0x00000000); /* disable all ints */
	mtdcr(UIC0CR, 0x00000000); /* set all to be non-critical */
	mtdcr(UIC0PR, 0xFFFFE000); /* set int polarities */
	mtdcr(UIC0TR, 0x00000000); /* set int trigger levels */
	mtdcr(UIC0SR, 0xFFFFFFFF); /* clear all ints */

	mtdcr(CPC0_CR1, CPC0_CR1_VALUE);
	mtdcr(CPC0_ECR, 0x60606000);
	mtdcr(CPC0_EIRR, 0x7C000000);
	out32(GPIO0_OR,		CONFIG_SYS_GPIO0_OR );
	out32(GPIO0_TCR,	CONFIG_SYS_GPIO0_TCR);
	out32(GPIO0_ODR,	CONFIG_SYS_GPIO0_ODR);
	mtspr(SPRN_CCR0,      0x00700000);

	return 0;
}

#ifdef CONFIG_BOARD_PRE_INIT
int board_pre_init (void)
{
	return board_early_init_f ();
}
#endif

int sys_install_requested(void)
{
	u16 ioValue = in_be16((u16 *)MCU25_DIGITAL_IO_REGISTER);
	return (ioValue & MCU_SW_INSTALL_REQUESTED) != 0;
}

int checkboard (void)
{
	u16 boardVersReg = in_be16((u16 *)MCU25_VERSIONS_REGISTER);
	u16 hwConfig   = in_be16((u16 *)MCU25_IO_CONFIGURATION);
	u16 generation = boardVersReg & 0x0f;
	u16 index      = boardVersReg & 0xf0;

	/* Cannot be done in board_early_init */
	mtdcr(CPC0_CR0,  CPC0_CR0_VALUE);

	/* Force /RTS to active. The board it not wired quite
	 * correctly to use cts/rtc flow control, so just force the
	 * /RST active and forget about it.
	 */
	writeb (readb (0xef600404) | 0x03, 0xef600404);
	nm_show_print(generation, index, hwConfig);
	return 0;
}

u32 hcu_led_get(void)
{
	return in_be16((u16 *)MCU25_LED_REGISTER_ADDRESS) & 0x3ff;
}

void hcu_led_set(u32 value)
{
   out_be16((u16 *)MCU25_LED_REGISTER_ADDRESS, value);
}

u32 hcu_get_slot(void)
{
	u16 slot = in_be16((u16 *)MCU25_SLOT_ADDRESS);
	return slot & 0x7f;
}

u32 get_serial_number(void)
{
	u32 serial = in_be32((u32 *)CONFIG_SYS_FLASH_BASE);

	if (serial == 0xffffffff)
		return 0;

	return serial;
}



int misc_init_r(void)
{
	common_misc_init_r();
	set_params_for_sw_install( sys_install_requested(), "mcu25" );
	return 0;
}

phys_size_t initdram(int board_type)
{
	unsigned int dram_size = 64*1024*1024;
	init_ppc405_sdram(dram_size);

#ifdef DEBUG
	show_sdram_registers();
#endif

	return dram_size;
}

#if defined(CONFIG_OF_LIBFDT) && defined(CONFIG_OF_BOARD_SETUP)
void ft_board_setup(void *blob, bd_t *bd)
{
	ft_cpu_setup(blob, bd);

}
#endif /* defined(CONFIG_OF_LIBFDT) && defined(CONFIG_OF_BOARD_SETUP) */

ulong board_flash_get_legacy (ulong base, int banknum, flash_info_t * info)
{
	if (banknum == 0) {	/* non-CFI boot flash */
		info->portwidth = 1;
		info->chipwidth = 1;
		info->interface = FLASH_CFI_X8;
		return 1;
	} else
		return 0;
}