

#include <common.h>

#include <post.h>

#if CONFIG_POST & CONFIG_SYS_POST_DSP
#include <asm/io.h>

/* This test verifies DSP status bits in FPGA */

DECLARE_GLOBAL_DATA_PTR;

#define DSP_STATUS_REG 0xC4000008

int dsp_post_test(int flags)
{
	uint   read_value;
	int    ret;

	ret = 0;
	read_value = in_be32((void *)DSP_STATUS_REG) & 0x3;
	if (read_value != 0x3) {
		post_log("\nDSP status read %08X\n", read_value);
		ret = 1;
	}

	return ret;
}

#endif /* CONFIG_POST & CONFIG_SYS_POST_DSP */
