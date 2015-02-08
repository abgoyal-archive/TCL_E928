

#include <common.h>
#include <command.h>
#include <asm/byteorder.h>
#include <asm/cache.h>

#define NIOS_MAGIC 0x534f494e /* enable command line and initrd passing */

int do_bootm_linux(int flag, int argc, char *argv[], bootm_headers_t *images)
{
	void (*kernel)(int, int, int, char *) = (void *)images->ep;
	char *commandline = getenv("bootargs");
	ulong initrd_start = images->rd_start;
	ulong initrd_end = images->rd_end;

	if ((flag != 0) && (flag != BOOTM_STATE_OS_GO))
		return 1;

	/* flushes data and instruction caches before calling the kernel */
	disable_interrupts();
	flush_dcache((ulong)kernel, CONFIG_SYS_DCACHE_SIZE);
	flush_icache((ulong)kernel, CONFIG_SYS_ICACHE_SIZE);

	debug("bootargs=%s @ 0x%lx\n", commandline, (ulong)&commandline);
	debug("initrd=0x%lx-0x%lx\n", (ulong)initrd_start, (ulong)initrd_end);
	kernel(NIOS_MAGIC, initrd_start, initrd_end, commandline);
	/* does not return */

	return 1;
}
