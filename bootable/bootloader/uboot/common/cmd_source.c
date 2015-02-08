


/* #define DEBUG */

#include <common.h>
#include <command.h>
#include <image.h>
#include <malloc.h>
#include <asm/byteorder.h>
#if defined(CONFIG_8xx)
#include <mpc8xx.h>
#endif
#ifdef CONFIG_SYS_HUSH_PARSER
#include <hush.h>
#endif

int
source (ulong addr, const char *fit_uname)
{
	ulong		len;
	image_header_t	*hdr;
	ulong		*data;
	char		*cmd;
	int		rcode = 0;
	int		verify;
#if defined(CONFIG_FIT)
	const void*	fit_hdr;
	int		noffset;
	const void	*fit_data;
	size_t		fit_len;
#endif

	verify = getenv_yesno ("verify");

	switch (genimg_get_format ((void *)addr)) {
	case IMAGE_FORMAT_LEGACY:
		hdr = (image_header_t *)addr;

		if (!image_check_magic (hdr)) {
			puts ("Bad magic number\n");
			return 1;
		}

		if (!image_check_hcrc (hdr)) {
			puts ("Bad header crc\n");
			return 1;
		}

		if (verify) {
			if (!image_check_dcrc (hdr)) {
				puts ("Bad data crc\n");
				return 1;
			}
		}

		if (!image_check_type (hdr, IH_TYPE_SCRIPT)) {
			puts ("Bad image type\n");
			return 1;
		}

		/* get length of script */
		data = (ulong *)image_get_data (hdr);

		if ((len = uimage_to_cpu (*data)) == 0) {
			puts ("Empty Script\n");
			return 1;
		}

		/*
		 * scripts are just multi-image files with one component, seek
		 * past the zero-terminated sequence of image lengths to get
		 * to the actual image data
		 */
		while (*data++);
		break;
#if defined(CONFIG_FIT)
	case IMAGE_FORMAT_FIT:
		if (fit_uname == NULL) {
			puts ("No FIT subimage unit name\n");
			return 1;
		}

		fit_hdr = (const void *)addr;
		if (!fit_check_format (fit_hdr)) {
			puts ("Bad FIT image format\n");
			return 1;
		}

		/* get script component image node offset */
		noffset = fit_image_get_node (fit_hdr, fit_uname);
		if (noffset < 0) {
			printf ("Can't find '%s' FIT subimage\n", fit_uname);
			return 1;
		}

		if (!fit_image_check_type (fit_hdr, noffset, IH_TYPE_SCRIPT)) {
			puts ("Not a image image\n");
			return 1;
		}

		/* verify integrity */
		if (verify) {
			if (!fit_image_check_hashes (fit_hdr, noffset)) {
				puts ("Bad Data Hash\n");
				return 1;
			}
		}

		/* get script subimage data address and length */
		if (fit_image_get_data (fit_hdr, noffset, &fit_data, &fit_len)) {
			puts ("Could not find script subimage data\n");
			return 1;
		}

		data = (ulong *)fit_data;
		len = (ulong)fit_len;
		break;
#endif
	default:
		puts ("Wrong image format for \"source\" command\n");
		return 1;
	}

	debug ("** Script length: %ld\n", len);

	if ((cmd = malloc (len + 1)) == NULL) {
		return 1;
	}

	/* make sure cmd is null terminated */
	memmove (cmd, (char *)data, len);
	*(cmd + len) = 0;

#ifdef CONFIG_SYS_HUSH_PARSER /*?? */
	rcode = parse_string_outer (cmd, FLAG_PARSE_SEMICOLON);
#else
	{
		char *line = cmd;
		char *next = cmd;

		/*
		 * break into individual lines,
		 * and execute each line;
		 * terminate on error.
		 */
		while (*next) {
			if (*next == '\n') {
				*next = '\0';
				/* run only non-empty commands */
				if (*line) {
					debug ("** exec: \"%s\"\n",
						line);
					if (run_command (line, 0) < 0) {
						rcode = 1;
						break;
					}
				}
				line = next + 1;
			}
			++next;
		}
		if (rcode == 0 && *line)
			rcode = (run_command(line, 0) >= 0);
	}
#endif
	free (cmd);
	return rcode;
}

/**************************************************/
#if defined(CONFIG_CMD_SOURCE)
int
do_source (cmd_tbl_t *cmdtp, int flag, int argc, char *argv[])
{
	ulong addr;
	int rcode;
	const char *fit_uname = NULL;

	/* Find script image */
	if (argc < 2) {
		addr = CONFIG_SYS_LOAD_ADDR;
		debug ("*  source: default load address = 0x%08lx\n", addr);
#if defined(CONFIG_FIT)
	} else if (fit_parse_subimage (argv[1], load_addr, &addr, &fit_uname)) {
		debug ("*  source: subimage '%s' from FIT image at 0x%08lx\n",
				fit_uname, addr);
#endif
	} else {
		addr = simple_strtoul(argv[1], NULL, 16);
		debug ("*  source: cmdline image address = 0x%08lx\n", addr);
	}

	printf ("## Executing script at %08lx\n", addr);
	rcode = source (addr, fit_uname);
	return rcode;
}

U_BOOT_CMD(
	source, 2, 0,	do_source,
	"run script from memory",
	"[addr]\n"
	"\t- run script starting at addr\n"
	"\t- A valid image header must be present"
#if defined(CONFIG_FIT)
	"\n"
	"For FIT format uImage addr must include subimage\n"
	"unit name in the form of addr:<subimg_uname>"
#endif
);
#endif