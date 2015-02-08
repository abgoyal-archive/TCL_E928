



#include <common.h>
#include <mpc5xx.h>

#define SRAM_SIZE	1024000L	/* 1M RAM available*/

#if defined(__APPLE__)
/* Leading underscore on symbols */
#  define SYM_CHAR "_"
#else /* No leading character on symbols */
#  define SYM_CHAR
#endif

#define GEN_SYMNAME(str) SYM_CHAR #str
#define GEN_VALUE(str) #str
#define GEN_ABS(name, value) \
		asm (".globl " GEN_SYMNAME(name)); \
		asm (GEN_SYMNAME(name) " = " GEN_VALUE(value))

int checkboard(void)
{
    puts ("Board: ### No HW ID - assuming CMI board\n");
    return (0);
}

phys_size_t initdram(int board_type)
{
	return (SRAM_SIZE);		/* We currently have a static size adapted for cmi board. */
}

GEN_ABS(env_start, CONFIG_ENV_OFFSET + CONFIG_SYS_FLASH_BASE);
