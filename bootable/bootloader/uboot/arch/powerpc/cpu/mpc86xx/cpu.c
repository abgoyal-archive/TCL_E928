

#include <common.h>
#include <watchdog.h>
#include <command.h>
#include <asm/cache.h>
#include <asm/mmu.h>
#include <mpc86xx.h>
#include <asm/fsl_law.h>

DECLARE_GLOBAL_DATA_PTR;

static void
__board_reset(void)
{
	/* Do nothing */
}
void board_reset(void) __attribute__((weak, alias("__board_reset")));


int
checkcpu(void)
{
	sys_info_t sysinfo;
	uint pvr, svr;
	uint ver;
	uint major, minor;
	char buf1[32], buf2[32];
	volatile immap_t *immap = (immap_t *) CONFIG_SYS_IMMR;
	volatile ccsr_gur_t *gur = &immap->im_gur;
	struct cpu_type *cpu;
	uint msscr0 = mfspr(MSSCR0);

	svr = get_svr();
	ver = SVR_SOC_VER(svr);
	major = SVR_MAJ(svr);
	minor = SVR_MIN(svr);

	if (cpu_numcores() > 1) {
#ifndef CONFIG_MP
		puts("Unicore software on multiprocessor system!!\n"
		     "To enable mutlticore build define CONFIG_MP\n");
#endif
	}
	puts("CPU:   ");

	cpu = gd->cpu;

	puts(cpu->name);

	printf(", Version: %d.%d, (0x%08x)\n", major, minor, svr);
	puts("Core:  ");

	pvr = get_pvr();
	ver = PVR_E600_VER(pvr);
	major = PVR_E600_MAJ(pvr);
	minor = PVR_E600_MIN(pvr);

	printf("E600 Core %d", (msscr0 & 0x20) ? 1 : 0 );
	if (gur->pordevsr & MPC86xx_PORDEVSR_CORE1TE)
		puts("\n    Core1Translation Enabled");
	debug(" (MSSCR0=%x, PORDEVSR=%x)", msscr0, gur->pordevsr);

	printf(", Version: %d.%d, (0x%08x)\n", major, minor, pvr);

	get_sys_info(&sysinfo);

	puts("Clock Configuration:\n");
	printf("       CPU:%-4s MHz, ", strmhz(buf1, sysinfo.freqProcessor));
	printf("MPX:%-4s MHz\n", strmhz(buf1, sysinfo.freqSystemBus));
	printf("       DDR:%-4s MHz (%s MT/s data rate), ",
		strmhz(buf1, sysinfo.freqSystemBus / 2),
		strmhz(buf2, sysinfo.freqSystemBus));

	if (sysinfo.freqLocalBus > LCRR_CLKDIV) {
		printf("LBC:%-4s MHz\n", strmhz(buf1, sysinfo.freqLocalBus));
	} else {
		printf("LBC: unknown (LCRR[CLKDIV] = 0x%02lx)\n",
		       sysinfo.freqLocalBus);
	}

	puts("L1:    D-cache 32 KB enabled\n");
	puts("       I-cache 32 KB enabled\n");

	puts("L2:    ");
	if (get_l2cr() & 0x80000000) {
#if defined(CONFIG_MPC8610)
		puts("256");
#elif defined(CONFIG_MPC8641)
		puts("512");
#endif
		puts(" KB enabled\n");
	} else {
		puts("Disabled\n");
	}

	return 0;
}


void
do_reset(cmd_tbl_t *cmdtp, int flag, int argc, char *argv[])
{
	volatile immap_t *immap = (immap_t *)CONFIG_SYS_IMMR;
	volatile ccsr_gur_t *gur = &immap->im_gur;

	/* Attempt board-specific reset */
	board_reset();

	/* Next try asserting HRESET_REQ */
	out_be32(&gur->rstcr, MPC86xx_RSTCR_HRST_REQ);

	while (1)
		;
}


unsigned long
get_tbclk(void)
{
	sys_info_t sys_info;

	get_sys_info(&sys_info);
	return (sys_info.freqSystemBus + 3L) / 4L;
}


#if defined(CONFIG_WATCHDOG)
void
watchdog_reset(void)
{
#if defined(CONFIG_MPC8610)
	/*
	 * This actually feed the hard enabled watchdog.
	 */
	volatile immap_t *immap = (immap_t *)CONFIG_SYS_IMMR;
	volatile ccsr_wdt_t *wdt = &immap->im_wdt;
	volatile ccsr_gur_t *gur = &immap->im_gur;
	u32 tmp = gur->pordevsr;

	if (tmp & 0x4000) {
		wdt->swsrr = 0x556c;
		wdt->swsrr = 0xaa39;
	}
#endif
}
#endif	/* CONFIG_WATCHDOG */

void mpc86xx_reginfo(void)
{
	immap_t *immap = (immap_t *)CONFIG_SYS_IMMR;
	ccsr_lbc_t *lbc = &immap->im_lbc;

	print_bats();
	print_laws();

	printf ("Local Bus Controller Registers\n"
		"\tBR0\t0x%08X\tOR0\t0x%08X \n", in_be32(&lbc->br0), in_be32(&lbc->or0));
	printf("\tBR1\t0x%08X\tOR1\t0x%08X \n", in_be32(&lbc->br1), in_be32(&lbc->or1));
	printf("\tBR2\t0x%08X\tOR2\t0x%08X \n", in_be32(&lbc->br2), in_be32(&lbc->or2));
	printf("\tBR3\t0x%08X\tOR3\t0x%08X \n", in_be32(&lbc->br3), in_be32(&lbc->or3));
	printf("\tBR4\t0x%08X\tOR4\t0x%08X \n", in_be32(&lbc->br4), in_be32(&lbc->or4));
	printf("\tBR5\t0x%08X\tOR5\t0x%08X \n", in_be32(&lbc->br5), in_be32(&lbc->or5));
	printf("\tBR6\t0x%08X\tOR6\t0x%08X \n", in_be32(&lbc->br6), in_be32(&lbc->or6));
	printf("\tBR7\t0x%08X\tOR7\t0x%08X \n", in_be32(&lbc->br7), in_be32(&lbc->or7));

}

void setup_ddr_bat(phys_addr_t dram_size)
{
	unsigned long batu, bl;

	bl = TO_BATU_BL(min(dram_size, CONFIG_MAX_MEM_MAPPED));

	if (BATU_SIZE(bl) != dram_size) {
		u64 sz = (u64)dram_size - BATU_SIZE(bl);
		print_size(sz, " left unmapped\n");
	}

	batu = bl | BATU_VS | BATU_VP;
	write_bat(DBAT0, batu, CONFIG_SYS_DBAT0L);
	write_bat(IBAT0, batu, CONFIG_SYS_IBAT0L);
}
