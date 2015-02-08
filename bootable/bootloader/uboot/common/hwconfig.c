

#include <config.h>
#include <common.h>
#include <exports.h>
#include <hwconfig.h>
#include <linux/types.h>
#include <linux/string.h>

static const char *hwconfig_parse(const char *opts, size_t maxlen,
				  const char *opt, char stopch, char eqch,
				  size_t *arglen)
{
	size_t optlen = strlen(opt);
	char *str;
	const char *start = opts;
	const char *end;

next:
	str = strstr(opts, opt);
	end = str + optlen;
	if (end - start > maxlen)
		return NULL;

	if (str && (str == opts || str[-1] == stopch) &&
			(*end == stopch || *end == eqch || *end == '\0')) {
		const char *arg_end;

		if (!arglen)
			return str;

		if (*end != eqch)
			return NULL;

		arg_end = strchr(str, stopch);
		if (!arg_end)
			*arglen = min(maxlen, strlen(str)) - optlen - 1;
		else
			*arglen = arg_end - end - 1;

		return end + 1;
	} else if (str) {
		opts = end;
		goto next;
	}
	return NULL;
}

const char *cpu_hwconfig __attribute__((weak));
const char *board_hwconfig __attribute__((weak));

static const char *__hwconfig(const char *opt, size_t *arglen)
{
	const char *env_hwconfig = getenv("hwconfig");

	if (env_hwconfig)
		return hwconfig_parse(env_hwconfig, strlen(env_hwconfig),
				      opt, ';', ':', arglen);

	if (board_hwconfig)
		return hwconfig_parse(board_hwconfig, strlen(board_hwconfig),
				      opt, ';', ':', arglen);

	if (cpu_hwconfig)
		return hwconfig_parse(cpu_hwconfig, strlen(cpu_hwconfig),
				      opt, ';', ':', arglen);

	return NULL;
}

int hwconfig(const char *opt)
{
	return !!__hwconfig(opt, NULL);
}

const char *hwconfig_arg(const char *opt, size_t *arglen)
{
	return __hwconfig(opt, arglen);
}

int hwconfig_arg_cmp(const char *opt, const char *arg)
{
	const char *argstr;
	size_t arglen;

	argstr = hwconfig_arg(opt, &arglen);
	if (!argstr || arglen != strlen(arg))
		return 0;

	return !strncmp(argstr, arg, arglen);
}

int hwconfig_sub(const char *opt, const char *subopt)
{
	size_t arglen;
	const char *arg;

	arg = __hwconfig(opt, &arglen);
	if (!arg)
		return 0;
	return !!hwconfig_parse(arg, arglen, subopt, ',', '=', NULL);
}

const char *hwconfig_subarg(const char *opt, const char *subopt,
			    size_t *subarglen)
{
	size_t arglen;
	const char *arg;

	arg = __hwconfig(opt, &arglen);
	if (!arg)
		return NULL;
	return hwconfig_parse(arg, arglen, subopt, ',', '=', subarglen);
}

int hwconfig_subarg_cmp(const char *opt, const char *subopt, const char *subarg)
{
	const char *argstr;
	size_t arglen;

	argstr = hwconfig_subarg(opt, subopt, &arglen);
	if (!argstr || arglen != strlen(subarg))
		return 0;

	return !strncmp(argstr, subarg, arglen);
}
