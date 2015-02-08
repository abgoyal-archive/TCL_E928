

#ifndef _U_BOOT_H_
#define _U_BOOT_H_	1

typedef struct bd_info {
	int bi_baudrate;		/* serial console baudrate */
	unsigned long bi_ip_addr;	/* IP Address */
	unsigned long bi_boot_params;	/* where this board expects params */
	unsigned long bi_memstart;	/* start of DRAM memory */
	phys_size_t bi_memsize;		/* size  of DRAM memory in bytes */
	unsigned long bi_flashstart;	/* start of FLASH memory */
	unsigned long bi_flashsize;	/* size  of FLASH memory */
	unsigned long bi_flashoffset;	/* reserved area for startup monitor */
	const char *bi_r_version;
	const char *bi_cpu;
	const char *bi_board_name;
	unsigned long bi_vco;
	unsigned long bi_cclk;
	unsigned long bi_sclk;
} bd_t;

#endif	/* _U_BOOT_H_ */
