

#ifndef __CFM_FLASH_H_
#define __CFM_FLASH_H_

#define	FREESCALE_MANUFACT 0xFACFFACF
#define	FREESCALE_ID_MCF5281 0x5281
#define	FREESCALE_ID_MCF5282 0x5282

extern void cfm_flash_print_info (flash_info_t * info);
extern int cfm_flash_erase_sector (flash_info_t * info, int sector);
extern void cfm_flash_init (flash_info_t * info);
extern int cfm_flash_write_buff (flash_info_t * info, uchar * src, ulong addr, ulong cnt);
#ifdef CONFIG_SYS_FLASH_PROTECTION
extern int cfm_flash_protect(flash_info_t * info,long sector,int prot);
#endif

#endif
