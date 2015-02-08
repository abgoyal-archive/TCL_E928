

#include <common.h>
#include <watchdog.h>
#include <command.h>
#include <netdev.h>

#include <asm/immap.h>

DECLARE_GLOBAL_DATA_PTR;

int do_reset(cmd_tbl_t * cmdtp, bd_t * bd, int flag, int argc, char *argv[])
{
	volatile ccm_t *ccm = (ccm_t *) MMAP_CCM;

	ccm->rcr = CCM_RCR_SOFTRST;
	/* we don't return! */
	return 0;
};

int checkcpu(void)
{
	volatile ccm_t *ccm = (ccm_t *) MMAP_CCM;
	u16 msk;
	u16 id = 0;
	u8 ver;

	puts("CPU:   ");
	msk = (ccm->cir >> 6);
	ver = (ccm->cir & 0x003f);
	switch (msk) {
	case 0x31:
		id = 5235;
		break;
	}

	if (id) {
		char buf1[32], buf2[32];

		printf("Freescale MCF%d (Mask:%01x Version:%x)\n", id, msk,
		       ver);
		printf("       CPU CLK %s MHz BUS CLK %s MHz\n",
		       strmhz(buf1, gd->cpu_clk),
		       strmhz(buf2, gd->bus_clk));
	}

	return 0;
};

#if defined(CONFIG_WATCHDOG)
/* Called by macro WATCHDOG_RESET */
void watchdog_reset(void)
{
	volatile wdog_t *wdp = (wdog_t *) (MMAP_WDOG);

	wdp->sr = 0x5555;	/* Count register */
	asm("nop");
	wdp->sr = 0xAAAA;	/* Count register */
}

int watchdog_disable(void)
{
	volatile wdog_t *wdp = (wdog_t *) (MMAP_WDOG);

	/* UserManual, once the wdog is disabled, wdog cannot be re-enabled */
	wdp->cr |= WTM_WCR_HALTED;	/* halted watchdog timer */

	puts("WATCHDOG:disabled\n");
	return (0);
}

int watchdog_init(void)
{
	volatile wdog_t *wdp = (wdog_t *) (MMAP_WDOG);
	u32 wdog_module = 0;

	/* set timeout and enable watchdog */
	wdog_module = ((CONFIG_SYS_CLK / CONFIG_SYS_HZ) * CONFIG_WATCHDOG_TIMEOUT);
	wdog_module |= (wdog_module / 8192);
	wdp->mr = wdog_module;

	wdp->cr = WTM_WCR_EN;
	puts("WATCHDOG:enabled\n");

	return (0);
}
#endif				/* CONFIG_WATCHDOG */

#if defined(CONFIG_MCFFEC)

int cpu_eth_init(bd_t *bis)
{
	return mcffec_initialize(bis);
}
#endif
