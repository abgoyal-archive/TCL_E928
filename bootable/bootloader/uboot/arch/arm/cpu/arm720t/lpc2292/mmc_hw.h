

#ifndef _MMC_HW_
#define _MMC_HW_

unsigned char mmc_read_csd(unsigned char *Buffer);
unsigned char mmc_read_sector (unsigned long addr,
			       unsigned char *Buffer);
unsigned char mmc_write_sector (unsigned long addr,unsigned char *Buffer);
int mmc_hw_init(void);

#endif /* _MMC_HW_ */
