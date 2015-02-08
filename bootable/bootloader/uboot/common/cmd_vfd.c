

#include <common.h>
#include <command.h>

#if defined(CONFIG_CMD_VFD)

#include <vfd_logo.h>
#define VFD_TEST_LOGO_BMPNR 0
#define VFD_REMOTE_LOGO_BMPNR 1

extern int transfer_pic(unsigned char, unsigned char *, int, int);

int trab_vfd (ulong bitmap);

int do_vfd (cmd_tbl_t *cmdtp, int flag, int argc, char *argv[])
{
	ulong bitmap;

	if (argc != 2) {
		cmd_usage(cmdtp);
		return 1;
	}

	if (argv[1][0] == '/') {	/* select bitmap by number */
		bitmap = simple_strtoul(argv[1]+1, NULL, 10);
		return (trab_vfd(bitmap));
	}

	/* display bitmap at given address */
	bitmap = simple_strtoul(argv[1], NULL, 16);
	transfer_pic(3, (uchar *)bitmap, VFD_LOGO_HEIGHT, VFD_LOGO_WIDTH);
	return 0;
}

U_BOOT_CMD(
	vfd,	2,	0,	do_vfd,
	"load a bitmap to the VFDs on TRAB",
	"/N\n"
	"    - load bitmap N to the VFDs (N is _decimal_ !!!)\n"
	"vfd ADDR\n"
	"    - load bitmap at address ADDR"
);
#endif

int trab_vfd (ulong bitmap)
{
	uchar *addr;
	char *s;

	switch (bitmap) {
	case VFD_TEST_LOGO_BMPNR:
		if ((s = getenv ("bitmap0")) != NULL) {
			addr = (uchar *)simple_strtoul (s, NULL, 16);
		} else {
			addr = &vfd_test_logo_bitmap[0];
		}
		break;
	case VFD_REMOTE_LOGO_BMPNR:
		if ((s = getenv ("bitmap1")) != NULL) {
			addr = (uchar *)simple_strtoul (s, NULL, 16);
		} else {
			addr = &vfd_remote_logo_bitmap[0];
		}
		break;
	default:
		printf("Unknown bitmap %ld\n", bitmap);
		return 1;
	}
	transfer_pic(3, addr, VFD_LOGO_HEIGHT, VFD_LOGO_WIDTH);
	return 0;
}
