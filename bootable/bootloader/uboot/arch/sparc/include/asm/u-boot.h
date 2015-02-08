

#ifndef __U_BOOT_H__
#define __U_BOOT_H__


#ifndef __ASSEMBLY__

typedef struct bd_info {
	unsigned long bi_memstart;	/* start of DRAM memory */
	phys_size_t bi_memsize;		/* size  of DRAM memory in bytes */
	unsigned long bi_flashstart;	/* start of FLASH memory */
	unsigned long bi_flashsize;	/* size  of FLASH memory */
	unsigned long bi_flashoffset;	/* reserved area for startup monitor */
	unsigned long bi_sramstart;	/* start of SRAM memory */
	unsigned long bi_sramsize;	/* size  of SRAM memory */
	unsigned long bi_bootflags;	/* boot / reboot flag (for LynxOS) */
	unsigned long bi_ip_addr;	/* IP Address */
	unsigned short bi_ethspeed;	/* Ethernet speed in Mbps */
	unsigned long bi_intfreq;	/* Internal Freq, in MHz */
	unsigned long bi_busfreq;	/* Bus Freq, in MHz */
	unsigned long bi_baudrate;	/* Console Baudrate */
} bd_t;

#endif				/* __ASSEMBLY__ */
#endif				/* __U_BOOT_H__ */
