

#include <common.h>
#include <command.h>
#include <environment.h>
#include <linux/stddef.h>
#include <mg_disk.h>

/* references to names in env_common.c */
extern uchar default_environment[];

char * env_name_spec = "MG_DISK";

env_t *env_ptr = 0;

DECLARE_GLOBAL_DATA_PTR;

uchar env_get_char_spec(int index)
{
	return (*((uchar *) (gd->env_addr + index)));
}

void env_relocate_spec(void)
{
	unsigned int err;

	err = mg_disk_init();
	if (err) {
		puts ("*** Warning - mg_disk_init error");
		goto OUT;
	}
	err = mg_disk_read(CONFIG_ENV_ADDR, (u_char *)env_ptr, CONFIG_ENV_SIZE);
	if (err) {
		puts ("*** Warning - mg_disk_read error");
		goto OUT;
	}

	if (crc32(0, env_ptr->data, ENV_SIZE) != env_ptr->crc) {
		puts ("*** Warning - CRC error");
		goto OUT;
	}

	return;

OUT:
	printf (", using default environment\n\n");
	set_default_env();
}

int saveenv(void)
{
	unsigned int err;

	env_ptr->crc = crc32(0, env_ptr->data, ENV_SIZE);
	err = mg_disk_write(CONFIG_ENV_ADDR, (u_char *)env_ptr,
			CONFIG_ENV_SIZE);
	if (err)
		puts ("*** Warning - mg_disk_write error\n\n");

	return err;
}

int env_init(void)
{
	/* use default */
	gd->env_addr = (ulong) & default_environment[0];
	gd->env_valid = 1;

	return 0;
}
