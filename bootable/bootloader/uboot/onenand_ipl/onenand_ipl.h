

#ifndef _ONENAND_IPL_H
#define _ONENAND_IPL_H

#include <linux/mtd/onenand_regs.h>

#define onenand_readw(a)        readw(THIS_ONENAND(a))
#define onenand_writew(v, a)    writew(v, THIS_ONENAND(a))

#define THIS_ONENAND(a)         (CONFIG_SYS_ONENAND_BASE + (a))

#define READ_INTERRUPT()	onenand_readw(ONENAND_REG_INTERRUPT)

extern int (*onenand_read_page)(ulong block, ulong page,
				u_char *buf, int pagesize);
extern int onenand_read_block(unsigned char *buf);
#endif
