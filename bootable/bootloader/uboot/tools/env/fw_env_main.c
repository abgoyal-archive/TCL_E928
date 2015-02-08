


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "fw_env.h"

#define	CMD_PRINTENV	"fw_printenv"
#define CMD_SETENV	"fw_setenv"

int
main(int argc, char *argv[])
{
	char *p;
	char *cmdname = *argv;

	if ((p = strrchr (cmdname, '/')) != NULL) {
		cmdname = p + 1;
	}

	if (strcmp(cmdname, CMD_PRINTENV) == 0) {

		if (fw_printenv (argc, argv) != 0)
			return (EXIT_FAILURE);

		return (EXIT_SUCCESS);

	} else if (strcmp(cmdname, CMD_SETENV) == 0) {

		if (fw_setenv (argc, argv) != 0)
			return (EXIT_FAILURE);

		return (EXIT_SUCCESS);

	}

	fprintf (stderr,
		"Identity crisis - may be called as `" CMD_PRINTENV
		"' or as `" CMD_SETENV "' but not as `%s'\n",
		cmdname);
	return (EXIT_FAILURE);
}
