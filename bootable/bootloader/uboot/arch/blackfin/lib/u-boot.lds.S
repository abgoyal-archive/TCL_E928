

#include <config.h>
#include <asm/blackfin.h>
#undef ALIGN
#undef ENTRY

#ifndef LDS_BOARD_TEXT
# define LDS_BOARD_TEXT
#endif

#ifndef L1_DATA_B_SRAM
# define L1_DATA_B_SRAM      CONFIG_SYS_MONITOR_BASE
# define L1_DATA_B_SRAM_SIZE 0
#endif

/* The 0xC offset is so we don't clobber the tiny LDR jump block. */
#ifdef CONFIG_BFIN_BOOTROM_USES_EVT1
# define L1_CODE_ORIGIN L1_INST_SRAM
#else
# define L1_CODE_ORIGIN L1_INST_SRAM + 0xC
#endif

OUTPUT_ARCH(bfin)

MEMORY
{
#if CONFIG_MEM_SIZE
	ram     : ORIGIN = CONFIG_SYS_MONITOR_BASE, LENGTH = CONFIG_SYS_MONITOR_LEN
# define ram_code ram
# define ram_data ram
#else
# define ram_code l1_code
# define ram_data l1_data
#endif
	l1_code : ORIGIN = L1_CODE_ORIGIN,          LENGTH = L1_INST_SRAM_SIZE
	l1_data : ORIGIN = L1_DATA_B_SRAM,          LENGTH = L1_DATA_B_SRAM_SIZE
}

ENTRY(_start)
SECTIONS
{
	.text.pre :
	{
		arch/blackfin/cpu/start.o (.text .text.*)

		LDS_BOARD_TEXT
	} >ram_code

	.text.init :
	{
		arch/blackfin/cpu/initcode.o (.text .text.*)
	} >ram_code
	__initcode_lma = LOADADDR(.text.init);
	__initcode_len = SIZEOF(.text.init);

	.text :
	{
		*(.text .text.*)
	} >ram_code

	.rodata :
	{
		. = ALIGN(4);
		*(SORT_BY_ALIGNMENT(SORT_BY_NAME(.rodata*)))
		. = ALIGN(4);
	} >ram_data

	.data :
	{
		. = ALIGN(4);
		*(.data .data.*)
		*(.data1)
		*(.sdata)
		*(.sdata2)
		*(.dynamic)
		CONSTRUCTORS
	} >ram_data

	.u_boot_cmd :
	{
		___u_boot_cmd_start = .;
		*(.u_boot_cmd)
		___u_boot_cmd_end = .;
	} >ram_data

	.text_l1 :
	{
		. = ALIGN(4);
		__stext_l1 = .;
		*(.l1.text)
		. = ALIGN(4);
		__etext_l1 = .;
	} >l1_code AT>ram_code
	__text_l1_lma = LOADADDR(.text_l1);
	__text_l1_len = SIZEOF(.text_l1);
	ASSERT (__text_l1_len <= L1_INST_SRAM_SIZE, "L1 text overflow!")

	.data_l1 :
	{
		. = ALIGN(4);
		__sdata_l1 = .;
		*(.l1.data)
		*(.l1.bss)
		. = ALIGN(4);
		__edata_l1 = .;
	} >l1_data AT>ram_data
	__data_l1_lma = LOADADDR(.data_l1);
	__data_l1_len = SIZEOF(.data_l1);
	ASSERT (__data_l1_len <= L1_DATA_B_SRAM_SIZE, "L1 data B overflow!")

	.bss :
	{
		. = ALIGN(4);
		*(.sbss) *(.scommon)
		*(.dynbss)
		*(.bss .bss.*)
		*(COMMON)
	} >ram_data
	__bss_vma = ADDR(.bss);
	__bss_len = SIZEOF(.bss);
}
