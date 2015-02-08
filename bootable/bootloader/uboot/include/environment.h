

#ifndef _ENVIRONMENT_H_
#define _ENVIRONMENT_H_	1


#if defined(CONFIG_ENV_IS_IN_FLASH)
# ifndef  CONFIG_ENV_ADDR
#  define CONFIG_ENV_ADDR	(CONFIG_SYS_FLASH_BASE + CONFIG_ENV_OFFSET)
# endif
# ifndef  CONFIG_ENV_OFFSET
#  define CONFIG_ENV_OFFSET (CONFIG_ENV_ADDR - CONFIG_SYS_FLASH_BASE)
# endif
# if !defined(CONFIG_ENV_ADDR_REDUND) && defined(CONFIG_ENV_OFFSET_REDUND)
#  define CONFIG_ENV_ADDR_REDUND	(CONFIG_SYS_FLASH_BASE + CONFIG_ENV_OFFSET_REDUND)
# endif
# if defined(CONFIG_ENV_SECT_SIZE) || defined(CONFIG_ENV_SIZE)
#  ifndef  CONFIG_ENV_SECT_SIZE
#   define CONFIG_ENV_SECT_SIZE	CONFIG_ENV_SIZE
#  endif
#  ifndef  CONFIG_ENV_SIZE
#   define CONFIG_ENV_SIZE	CONFIG_ENV_SECT_SIZE
#  endif
# else
#  error "Both CONFIG_ENV_SECT_SIZE and CONFIG_ENV_SIZE undefined"
# endif
# if defined(CONFIG_ENV_ADDR_REDUND) && !defined(CONFIG_ENV_SIZE_REDUND)
#  define CONFIG_ENV_SIZE_REDUND	CONFIG_ENV_SIZE
# endif
# if (CONFIG_ENV_ADDR >= CONFIG_SYS_MONITOR_BASE) && \
     (CONFIG_ENV_ADDR+CONFIG_ENV_SIZE) <= (CONFIG_SYS_MONITOR_BASE + CONFIG_SYS_MONITOR_LEN)
#  define ENV_IS_EMBEDDED	1
# endif
# if defined(CONFIG_ENV_ADDR_REDUND) || defined(CONFIG_ENV_OFFSET_REDUND)
#  define CONFIG_SYS_REDUNDAND_ENVIRONMENT	1
# endif
# ifdef CONFIG_ENV_IS_EMBEDDED
#  error "do not define CONFIG_ENV_IS_EMBEDDED in your board config"
#  error "it is calculated automatically for you"
# endif
#endif	/* CONFIG_ENV_IS_IN_FLASH */

#if defined(CONFIG_ENV_IS_IN_NAND)
# ifndef CONFIG_ENV_OFFSET
#  error "Need to define CONFIG_ENV_OFFSET when using CONFIG_ENV_IS_IN_NAND"
# endif
# ifndef CONFIG_ENV_SIZE
#  error "Need to define CONFIG_ENV_SIZE when using CONFIG_ENV_IS_IN_NAND"
# endif
# ifdef CONFIG_ENV_OFFSET_REDUND
#  define CONFIG_SYS_REDUNDAND_ENVIRONMENT
# endif
#endif /* CONFIG_ENV_IS_IN_NAND */

#if defined(CONFIG_ENV_IS_IN_MG_DISK)
# ifndef CONFIG_ENV_ADDR
#  error "Need to define CONFIG_ENV_ADDR when using CONFIG_ENV_IS_IN_MG_DISK"
# endif
# ifndef CONFIG_ENV_SIZE
#  error "Need to define CONFIG_ENV_SIZE when using CONFIG_ENV_IS_IN_MG_DISK"
# endif
#endif /* CONFIG_ENV_IS_IN_MG_DISK */

/* Embedded env is only supported for some flash types */
#ifdef CONFIG_ENV_IS_EMBEDDED
# if !defined(CONFIG_ENV_IS_IN_FLASH) && \
     !defined(CONFIG_ENV_IS_IN_NAND) && \
     !defined(CONFIG_ENV_IS_IN_ONENAND)
#  error "CONFIG_ENV_IS_EMBEDDED not supported for your flash type"
# endif
#endif

#if defined(CONFIG_ENV_IS_EMBEDDED) && !defined(ENV_IS_EMBEDDED)
# define ENV_IS_EMBEDDED 1
#endif

/* The build system likes to know if the env is embedded */
#ifdef DO_DEPS_ONLY
# ifdef ENV_IS_EMBEDDED
#  define CONFIG_ENV_IS_EMBEDDED
# endif
#endif

#include "compiler.h"

#ifdef CONFIG_SYS_REDUNDAND_ENVIRONMENT
# define ENV_HEADER_SIZE	(sizeof(uint32_t) + 1)
#else
# define ENV_HEADER_SIZE	(sizeof(uint32_t))
#endif


#define ENV_SIZE (CONFIG_ENV_SIZE - ENV_HEADER_SIZE)

typedef	struct environment_s {
	uint32_t	crc;		/* CRC32 over data bytes	*/
#ifdef CONFIG_SYS_REDUNDAND_ENVIRONMENT
	unsigned char	flags;		/* active/obsolete flags	*/
#endif
	unsigned char	data[ENV_SIZE]; /* Environment data		*/
} env_t;

/* Function that returns a character from the environment */
unsigned char env_get_char (int);

/* Function that returns a pointer to a value from the environment */
unsigned char *env_get_addr(int);
unsigned char env_get_char_memory (int index);

/* Function that updates CRC of the enironment */
void env_crc_update (void);

/* [re]set to the default environment */
void set_default_env(void);

#endif	/* _ENVIRONMENT_H_ */
