

#include <common.h>


#include <post.h>
#include <i2c.h>

#if CONFIG_POST & CONFIG_SYS_POST_I2C

int i2c_post_test (int flags)
{
	unsigned int i;
	unsigned int good = 0;
#ifdef I2C_ADDR_LIST
	unsigned int bad  = 0;
	int j;
	unsigned char i2c_addr_list[] = I2C_ADDR_LIST;
	unsigned char i2c_miss_list[] = I2C_ADDR_LIST;
#endif

	for (i = 0; i < 128; i++) {
		if (i2c_probe (i) == 0) {
#ifndef	I2C_ADDR_LIST
			good++;
#else	/* I2C_ADDR_LIST */
			for (j=0; j<sizeof(i2c_addr_list); ++j) {
				if (i == i2c_addr_list[j]) {
					good++;
					i2c_miss_list[j] = 0xFF;
					break;
				}
			}
			if (j == sizeof(i2c_addr_list)) {
				bad++;
				post_log ("I2C: addr %02X not expected\n",
						i);
			}
#endif	/* I2C_ADDR_LIST */
		}
	}

#ifndef	I2C_ADDR_LIST
	return good > 0 ? 0 : -1;
#else	/* I2C_ADDR_LIST */
	if (good != sizeof(i2c_addr_list)) {
		for (j=0; j<sizeof(i2c_miss_list); ++j) {
			if (i2c_miss_list[j] != 0xFF) {
				post_log ("I2C: addr %02X did not respond\n",
						i2c_miss_list[j]);
			}
		}
	}
	return ((good == sizeof(i2c_addr_list)) && (bad == 0)) ? 0 : -1;
#endif
}

#endif /* CONFIG_POST & CONFIG_SYS_POST_I2C */
