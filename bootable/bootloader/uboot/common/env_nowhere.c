

#include <common.h>

#if defined(CONFIG_ENV_IS_NOWHERE) /* Environment is nowhere */

#include <command.h>
#include <environment.h>
#include <linux/stddef.h>

DECLARE_GLOBAL_DATA_PTR;

env_t *env_ptr = NULL;

extern uchar default_environment[];


void env_relocate_spec (void)
{
}

uchar env_get_char_spec (int index)
{
	return ( *((uchar *)(gd->env_addr + index)) );
}

int  env_init(void)
{
	gd->env_addr  = (ulong)&default_environment[0];
	gd->env_valid = 0;

	return (0);
}

#endif /* CFG_ENV_IS_NOWHERE) */
