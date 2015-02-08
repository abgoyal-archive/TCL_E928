

#include <common.h>
#include <command.h>
#include <image.h>
#include <u-boot/zlib.h>
#include <bzlib.h>
#include <watchdog.h>
#include <environment.h>
#include <asm/byteorder.h>
#ifdef CONFIG_SHOW_BOOT_PROGRESS
# include <status_led.h>
#endif

DECLARE_GLOBAL_DATA_PTR;

#define PHYSADDR(x) x

#define LINUX_MAX_ENVS		256
#define LINUX_MAX_ARGS		256

static ulong get_sp (void);
static void set_clocks_in_mhz (bd_t *kbd);

void arch_lmb_reserve(struct lmb *lmb)
{
	ulong sp;

	/*
	 * Booting a (Linux) kernel image
	 *
	 * Allocate space for command line and board info - the
	 * address should be as high as possible within the reach of
	 * the kernel (see CONFIG_SYS_BOOTMAPSZ settings), but in unused
	 * memory, which means far enough below the current stack
	 * pointer.
	 */
	sp = get_sp();
	debug ("## Current stack ends at 0x%08lx ", sp);

	/* adjust sp by 1K to be safe */
	sp -= 1024;
	lmb_reserve(lmb, sp, (CONFIG_SYS_SDRAM_BASE + gd->ram_size - sp));
}

int do_bootm_linux(int flag, int argc, char *argv[], bootm_headers_t *images)
{
	ulong rd_len;
	ulong initrd_start, initrd_end;
	int ret;

	ulong cmd_start, cmd_end;
	ulong bootmap_base;
	bd_t  *kbd;
	void  (*kernel) (bd_t *, ulong, ulong, ulong, ulong);
	struct lmb *lmb = &images->lmb;

	if ((flag != 0) && (flag != BOOTM_STATE_OS_GO))
		return 1;

	bootmap_base = getenv_bootm_low();

	/* allocate space and init command line */
	ret = boot_get_cmdline (lmb, &cmd_start, &cmd_end, bootmap_base);
	if (ret) {
		puts("ERROR with allocation of cmdline\n");
		goto error;
	}

	/* allocate space for kernel copy of board info */
	ret = boot_get_kbd (lmb, &kbd, bootmap_base);
	if (ret) {
		puts("ERROR with allocation of kernel bd\n");
		goto error;
	}
	set_clocks_in_mhz(kbd);

	kernel = (void (*)(bd_t *, ulong, ulong, ulong, ulong))images->ep;

	rd_len = images->rd_end - images->rd_start;
	ret = boot_ramdisk_high (lmb, images->rd_start, rd_len,
			&initrd_start, &initrd_end);
	if (ret)
		goto error;

	debug("## Transferring control to Linux (at address %08lx) ...\n",
	      (ulong) kernel);

	show_boot_progress (15);

	/*
	 * Linux Kernel Parameters (passing board info data):
	 *   sp+00: Ignore, side effect of using jsr to jump to kernel
	 *   sp+04: ptr to board info data
	 *   sp+08: initrd_start or 0 if no initrd
	 *   sp+12: initrd_end - unused if initrd_start is 0
	 *   sp+16: Start of command line string
	 *   sp+20: End   of command line string
	 */
	(*kernel) (kbd, initrd_start, initrd_end, cmd_start, cmd_end);
	/* does not return */
error:
	return 1;
}

static ulong get_sp (void)
{
	ulong sp;

	asm("movel %%a7, %%d0\n"
	    "movel %%d0, %0\n": "=d"(sp): :"%d0");

	return sp;
}

static void set_clocks_in_mhz (bd_t *kbd)
{
	char *s;

	if ((s = getenv("clocks_in_mhz")) != NULL) {
		/* convert all clock information to MHz */
		kbd->bi_intfreq /= 1000000L;
		kbd->bi_busfreq /= 1000000L;
	}
}
