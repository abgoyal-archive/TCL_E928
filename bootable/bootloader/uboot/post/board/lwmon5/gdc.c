
#include <common.h>


#include <post.h>

#include <asm/io.h>

DECLARE_GLOBAL_DATA_PTR;

#define GDC_SCRATCH_REG 0xC1FF8044
#define GDC_VERSION_REG 0xC1FF8084
#define GDC_RAM_START   0xC0000000
#define GDC_RAM_END     0xC2000000

#if CONFIG_POST & CONFIG_SYS_POST_BSPEC4

static int gdc_test_reg_one(uint value)
{
	int ret;
	uint read_value;

	/* write test pattern */
	out_be32((void *)GDC_SCRATCH_REG, value);
	/* read other location (protect against data lines capacity) */
	ret = in_be32((void *)GDC_RAM_START);
	/* verify test pattern */
	read_value = in_be32((void *)GDC_SCRATCH_REG);
	if (read_value != value) {
		post_log("GDC SCRATCH test failed write %08X, read %08X\n",
			value, read_value);
	}

	return (read_value != value);
}

/* Verify GDC, get memory size */
int gdc_post_test(int flags)
{
	uint   old_value;
	int    ret = 0;

	post_log("\n");
	old_value = in_be32((void *)GDC_SCRATCH_REG);

	/*
	 * GPIOC2 register behaviour: the LIME graphics processor has a
	 * maximum of 5 GPIO ports that can be used in this hardware
	 * configuration. Thus only the  bits  for these 5 GPIOs can be
	 * activated in the GPIOC2 register. All other bits will always be
	 * read as zero.
	 */
	if (gdc_test_reg_one(0x00150015))
		ret = 1;
	if (gdc_test_reg_one(0x000A000A))
		ret = 1;

	out_be32((void *)GDC_SCRATCH_REG, old_value);

	old_value = in_be32((void *)GDC_VERSION_REG);
	post_log("GDC chip version %u.%u, year %04X\n",
		(old_value >> 8) & 0xFF, old_value & 0xFF,
		(old_value >> 16) & 0xFFFF);

	old_value = get_ram_size((void *)GDC_RAM_START,
				 GDC_RAM_END - GDC_RAM_START);
	post_log("GDC RAM size: %d bytes\n", old_value);

	return ret;
}
#endif /* CONFIG_POST & CONFIG_SYS_POST_BSPEC4 */
