

#ifndef _U_BOOT_H_
#define _U_BOOT_H_

typedef struct bd_info {
	unsigned long	bi_memstart;	/* start of DRAM memory */
	phys_size_t	bi_memsize;	/* size	 of DRAM memory in bytes */
	unsigned long	bi_flashstart;	/* start of FLASH memory */
	unsigned long	bi_flashsize;	/* size	 of FLASH memory */
	unsigned long	bi_flashoffset; /* reserved area for startup monitor */
	unsigned long	bi_sramstart;	/* start of SRAM memory */
	unsigned long	bi_sramsize;	/* size	 of SRAM memory */
	unsigned long	bi_ip_addr;	/* IP Address */
	unsigned long	bi_baudrate;	/* Console Baudrate */
} bd_t;


#endif	/* _U_BOOT_H_ */
