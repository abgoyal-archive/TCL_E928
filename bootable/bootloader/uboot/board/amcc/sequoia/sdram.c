

/* define DEBUG for debug output */
#undef DEBUG

#include <common.h>
#include <asm/processor.h>
#include <asm/io.h>
#include <ppc440.h>

extern int denali_wait_for_dlllock(void);
extern void denali_core_search_data_eye(void);

#if defined(CONFIG_NAND_SPL)
#define get_bus_freq(val)	133333333
#endif

phys_size_t initdram (int board_type)
{
#if !(defined(CONFIG_NAND_U_BOOT) || defined(CONFIG_SYS_RAMBOOT)) || \
    defined(CONFIG_NAND_SPL)
	ulong speed = get_bus_freq(0);

	mtsdram(DDR0_02, 0x00000000);

	mtsdram(DDR0_00, 0x0000190A);
	mtsdram(DDR0_01, 0x01000000);
	mtsdram(DDR0_03, 0x02030602);
	mtsdram(DDR0_04, 0x0A020200);
	mtsdram(DDR0_05, 0x02020308);
	mtsdram(DDR0_06, 0x0102C812);
	mtsdram(DDR0_07, 0x000D0100);
	mtsdram(DDR0_08, 0x02430001);
	mtsdram(DDR0_09, 0x00011D5F);
	mtsdram(DDR0_10, 0x00000100);
	mtsdram(DDR0_11, 0x0027C800);
	mtsdram(DDR0_12, 0x00000003);
	mtsdram(DDR0_14, 0x00000000);
	mtsdram(DDR0_17, 0x19000000);
	mtsdram(DDR0_18, 0x19191919);
	mtsdram(DDR0_19, 0x19191919);
	mtsdram(DDR0_20, 0x0B0B0B0B);
	mtsdram(DDR0_21, 0x0B0B0B0B);
	mtsdram(DDR0_22, 0x00267F0B);
	mtsdram(DDR0_23, 0x00000000);
	mtsdram(DDR0_24, 0x01010002);
	if (speed > 133333334)
		mtsdram(DDR0_26, 0x5B26050C);
	else
		mtsdram(DDR0_26, 0x5B260408);
	mtsdram(DDR0_27, 0x0000682B);
	mtsdram(DDR0_28, 0x00000000);
	mtsdram(DDR0_31, 0x00000000);
	mtsdram(DDR0_42, 0x01000006);
	mtsdram(DDR0_43, 0x030A0200);
	mtsdram(DDR0_44, 0x00000003);
	mtsdram(DDR0_02, 0x00000001);

	denali_wait_for_dlllock();
#endif /* #ifndef CONFIG_NAND_U_BOOT */

#ifdef CONFIG_DDR_DATA_EYE
	/* -----------------------------------------------------------+
	 * Perform data eye search if requested.
	 * ----------------------------------------------------------*/
	denali_core_search_data_eye();
#endif

	/*
	 * Clear possible errors resulting from data-eye-search.
	 * If not done, then we could get an interrupt later on when
	 * exceptions are enabled.
	 */
	set_mcsr(get_mcsr());

	return (CONFIG_SYS_MBYTES_SDRAM << 20);
}
