
#include <common.h>
#include <command.h>
#include <environment.h>
#include <linux/stddef.h>
#include <dataflash.h>

DECLARE_GLOBAL_DATA_PTR;

env_t *env_ptr = NULL;

char * env_name_spec = "dataflash";

extern int read_dataflash (unsigned long addr, unsigned long size, char
*result);
extern int write_dataflash (unsigned long addr_dest, unsigned long addr_src,
		     unsigned long size);
extern int AT91F_DataflashInit (void);
extern uchar default_environment[];


uchar env_get_char_spec (int index)
{
	uchar c;
	read_dataflash(CONFIG_ENV_ADDR + index + offsetof(env_t,data),
	1, (char *)&c);
	return (c);
}

void env_relocate_spec (void)
{
	read_dataflash(CONFIG_ENV_ADDR, CONFIG_ENV_SIZE, (char *)env_ptr);
}

int saveenv(void)
{
	/* env must be copied to do not alter env structure in memory*/
	unsigned char temp[CONFIG_ENV_SIZE];
	memcpy(temp, env_ptr, CONFIG_ENV_SIZE);
	return write_dataflash(CONFIG_ENV_ADDR, (unsigned long)temp, CONFIG_ENV_SIZE);
}

int env_init(void)
{
	ulong crc, len, new;
	unsigned off;
	uchar buf[64];
	if (gd->env_valid == 0){
		AT91F_DataflashInit();	/* prepare for DATAFLASH read/write */

		/* read old CRC */
		read_dataflash(CONFIG_ENV_ADDR + offsetof(env_t, crc),
			sizeof(ulong), (char *)&crc);
		new = 0;
		len = ENV_SIZE;
		off = offsetof(env_t,data);
		while (len > 0) {
			int n = (len > sizeof(buf)) ? sizeof(buf) : len;
			read_dataflash(CONFIG_ENV_ADDR + off, n, (char *)buf);
			new = crc32 (new, buf, n);
			len -= n;
			off += n;
		}
		if (crc == new) {
			gd->env_addr  = offsetof(env_t,data);
			gd->env_valid = 1;
		} else {
			gd->env_addr  = (ulong)&default_environment[0];
			gd->env_valid = 0;
		}
	}

	return (0);
}
