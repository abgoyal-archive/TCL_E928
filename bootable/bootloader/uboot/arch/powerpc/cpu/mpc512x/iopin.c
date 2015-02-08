

#include <common.h>
#include <linux/types.h>
#include <asm/io.h>

void iopin_initialize(iopin_t *ioregs_init, int len)
{
	short i, j, p;
	u32 *reg;
	immap_t *im = (immap_t *)CONFIG_SYS_IMMR;

	reg = (u32 *)&(im->io_ctrl);

	if (sizeof(ioregs_init) == 0)
		return;

	for (i = 0; i < len; i++) {
		for (p = 0, j = ioregs_init[i].p_offset / sizeof(u_long);
			p < ioregs_init[i].nr_pins; p++, j++) {
			if (ioregs_init[i].bit_or)
				setbits_be32(reg + j, ioregs_init[i].val);
			else
				out_be32 (reg + j, ioregs_init[i].val);
		}
	}
	return;
}
