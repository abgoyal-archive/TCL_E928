

#include <common.h>


#include <post.h>

#include <i2c.h>
#include <asm/io.h>

DECLARE_GLOBAL_DATA_PTR;

#define DSPIC_POST_ERROR_REG	0x800
#define DSPIC_SYS_ERROR_REG	0x802
#define DSPIC_VERSION_REG	0x804

#if CONFIG_POST & CONFIG_SYS_POST_BSPEC1

/* Verify that dsPIC ready test done early at hw init passed ok */
int dspic_init_post_test(int flags)
{
	if (in_be32((void *)CONFIG_SYS_DSPIC_TEST_ADDR) & CONFIG_SYS_DSPIC_TEST_MASK) {
		post_log("dsPIC init test failed\n");
		return 1;
	}

	return 0;
}

#endif /* CONFIG_POST & CONFIG_SYS_POST_BSPEC1 */

#if CONFIG_POST & CONFIG_SYS_POST_BSPEC2
/* Read a register from the dsPIC. */
int dspic_read(ushort reg)
{
	uchar buf[2];

	if (i2c_read(CONFIG_SYS_I2C_DSPIC_IO_ADDR, reg, 2, buf, 2))
		return -1;

	return (uint)((buf[0] << 8) | buf[1]);
}

/* Verify error codes regs, display version */
int dspic_post_test(int flags)
{
	int data;
	int ret = 0;

	post_log("\n");
	data = dspic_read(DSPIC_VERSION_REG);
	if (data == -1) {
		post_log("dsPIC : failed read version\n");
		ret = 1;
	} else {
		post_log("dsPIC version: %u.%u\n",
			(data >> 8) & 0xFF, data & 0xFF);
	}

	data = dspic_read(DSPIC_POST_ERROR_REG);
	if (data != 0) ret = 1;
	if (data == -1) {
		post_log("dsPIC : failed read POST code\n");
	} else {
		post_log("dsPIC POST code 0x%04X\n", data);
	}

	data = dspic_read(DSPIC_SYS_ERROR_REG);
	if (data == -1) {
		post_log("dsPIC : failed read system error\n");
		ret = 1;
	} else {
		post_log("dsPIC SYS-ERROR code: 0x%04X\n", data);
	}

	return ret;
}

#endif /* CONFIG_POST & CONFIG_SYS_POST_BSPEC2 */
