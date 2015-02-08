


#include <common.h>
#include <command.h>
#include <environment.h>
#include <linux/stddef.h>

DECLARE_GLOBAL_DATA_PTR;

#ifdef CONFIG_SYS_NVRAM_ACCESS_ROUTINE
extern void *nvram_read(void *dest, const long src, size_t count);
extern void nvram_write(long dest, const void *src, size_t count);
env_t *env_ptr = NULL;
#else
env_t *env_ptr = (env_t *)CONFIG_ENV_ADDR;
#endif

char * env_name_spec = "NVRAM";

extern uchar default_environment[];

#ifdef CONFIG_AMIGAONEG3SE
uchar env_get_char_spec (int index)
{
#ifdef CONFIG_SYS_NVRAM_ACCESS_ROUTINE
	uchar c;

	nvram_read(&c, CONFIG_ENV_ADDR+index, 1);

	return c;
#else
	uchar retval;
	enable_nvram();
	retval = *((uchar *)(gd->env_addr + index));
	disable_nvram();
	return retval;
#endif
}
#else
uchar env_get_char_spec (int index)
{
#ifdef CONFIG_SYS_NVRAM_ACCESS_ROUTINE
	uchar c;

	nvram_read(&c, CONFIG_ENV_ADDR+index, 1);

	return c;
#else
	return *((uchar *)(gd->env_addr + index));
#endif
}
#endif

void env_relocate_spec (void)
{
#if defined(CONFIG_SYS_NVRAM_ACCESS_ROUTINE)
	nvram_read(env_ptr, CONFIG_ENV_ADDR, CONFIG_ENV_SIZE);
#else
	memcpy (env_ptr, (void*)CONFIG_ENV_ADDR, CONFIG_ENV_SIZE);
#endif
}

int saveenv (void)
{
	int rcode = 0;
#ifdef CONFIG_AMIGAONEG3SE
	enable_nvram();
#endif
#ifdef CONFIG_SYS_NVRAM_ACCESS_ROUTINE
	nvram_write(CONFIG_ENV_ADDR, env_ptr, CONFIG_ENV_SIZE);
#else
	if (memcpy ((char *)CONFIG_ENV_ADDR, env_ptr, CONFIG_ENV_SIZE) == NULL)
		    rcode = 1 ;
#endif
#ifdef CONFIG_AMIGAONEG3SE
	udelay(10000);
	disable_nvram();
#endif
	return rcode;
}


int env_init (void)
{
#ifdef CONFIG_AMIGAONEG3SE
	enable_nvram();
#endif
#if defined(CONFIG_SYS_NVRAM_ACCESS_ROUTINE)
	ulong crc;
	uchar data[ENV_SIZE];
	nvram_read (&crc, CONFIG_ENV_ADDR, sizeof(ulong));
	nvram_read (data, CONFIG_ENV_ADDR+sizeof(ulong), ENV_SIZE);

	if (crc32(0, data, ENV_SIZE) == crc) {
		gd->env_addr  = (ulong)CONFIG_ENV_ADDR + sizeof(long);
#else
	if (crc32(0, env_ptr->data, ENV_SIZE) == env_ptr->crc) {
		gd->env_addr  = (ulong)&(env_ptr->data);
#endif
		gd->env_valid = 1;
	} else {
		gd->env_addr  = (ulong)&default_environment[0];
		gd->env_valid = 0;
	}
#ifdef CONFIG_AMIGAONEG3SE
	disable_nvram();
#endif
	return (0);
}
