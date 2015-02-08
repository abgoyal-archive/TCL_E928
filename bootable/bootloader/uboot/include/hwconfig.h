

#ifndef _HWCONFIG_H
#define _HWCONFIG_H

#include <linux/types.h>
#include <asm/errno.h>

#ifdef CONFIG_HWCONFIG

extern int hwconfig(const char *opt);
extern const char *hwconfig_arg(const char *opt, size_t *arglen);
extern int hwconfig_arg_cmp(const char *opt, const char *arg);
extern int hwconfig_sub(const char *opt, const char *subopt);
extern const char *hwconfig_subarg(const char *opt, const char *subopt,
				   size_t *subarglen);
extern int hwconfig_subarg_cmp(const char *opt, const char *subopt,
			       const char *subarg);

#else

static inline int hwconfig(const char *opt)
{
	return -ENOSYS;
}

static inline const char *hwconfig_arg(const char *opt, size_t *arglen)
{
	*arglen = 0;
	return "";
}

static inline int hwconfig_arg_cmp(const char *opt, const char *arg)
{
	return -ENOSYS;
}

static inline int hwconfig_sub(const char *opt, const char *subopt)
{
	return -ENOSYS;
}

static inline const char *hwconfig_subarg(const char *opt, const char *subopt,
					  size_t *subarglen)
{
	*subarglen = 0;
	return "";
}

static inline int hwconfig_subarg_cmp(const char *opt, const char *subopt,
				      const char *subarg)
{
	return -ENOSYS;
}

#endif /* CONFIG_HWCONFIG */

#endif /* _HWCONFIG_H */
