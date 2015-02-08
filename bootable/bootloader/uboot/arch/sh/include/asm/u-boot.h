

#ifndef __ASM_SH_U_BOOT_H_
#define __ASM_SH_U_BOOT_H_

typedef struct bd_info {
	unsigned long   bi_memstart;    /* start of DRAM memory */
	phys_size_t	bi_memsize;     /* size  of DRAM memory in bytes */
	unsigned long   bi_flashstart;  /* start of FLASH memory */
	unsigned long   bi_flashsize;   /* size  of FLASH memory */
	unsigned long   bi_flashoffset; /* reserved area for startup monitor */
	unsigned long   bi_sramstart;   /* start of SRAM memory */
	unsigned long   bi_sramsize;    /* size  of SRAM memory */
	unsigned long   bi_ip_addr;     /* IP Address */
	unsigned long   bi_baudrate;    /* Console Baudrate */
	unsigned long	bi_boot_params; /* where this board expects params */
} bd_t;

#endif
