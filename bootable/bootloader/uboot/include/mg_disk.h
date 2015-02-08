

#ifndef MG_DISK_H_
#define MG_DISK_H_

#include <asm/types.h>

/* private driver data */
struct mg_drv_data {
	/* base address of mflash */
	u32 base;
	/* Initialize hard reset, write protect, deep power down pins.
	 * Set these pins to GPIO and output high
	 */
	void (*mg_ctrl_pin_init) (void);
	/* Set hard reset pin for given level
	 * level : logical level of hard reset pin (0 or 1)
	 */
	void (*mg_hdrst_pin) (u8 level);
};

struct mg_drv_data* mg_get_drv_data (void);

unsigned int mg_disk_init (void);
unsigned int mg_disk_read (u32 addr, u8 *buff, u32 len);
unsigned int mg_disk_write(u32 addr, u8 *buff, u32 len);
unsigned int mg_disk_write_sects(void *buff, u32 sect_num, u32 sect_cnt);
unsigned int mg_disk_read_sects(void *buff, u32 sect_num, u32 sect_cnt);

#endif /*MG_DISK_H_*/
