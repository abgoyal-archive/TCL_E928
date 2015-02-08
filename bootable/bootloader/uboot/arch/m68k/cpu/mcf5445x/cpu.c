

#include <common.h>
#include <watchdog.h>
#include <command.h>
#include <netdev.h>

#include <asm/immap.h>

DECLARE_GLOBAL_DATA_PTR;

int do_reset(cmd_tbl_t * cmdtp, bd_t * bd, int flag, int argc, char *argv[])
{
	volatile rcm_t *rcm = (rcm_t *) (MMAP_RCM);
	udelay(1000);
	rcm->rcr |= RCM_RCR_SOFTRST;

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
	case 0x48:
		id = 54455;
		break;
	case 0x49:
		id = 54454;
		break;
	case 0x4a:
		id = 54453;
		break;
	case 0x4b:
		id = 54452;
		break;
	case 0x4d:
		id = 54451;
		break;
	case 0x4f:
		id = 54450;
		break;
	}

	if (id) {
		char buf1[32], buf2[32], buf3[32];

		printf("Freescale MCF%d (Mask:%01x Version:%x)\n", id, msk,
		       ver);
		printf("       CPU CLK %s MHz BUS CLK %s MHz FLB CLK %s MHz\n",
		       strmhz(buf1, gd->cpu_clk),
		       strmhz(buf2, gd->bus_clk),
		       strmhz(buf3, gd->flb_clk));
#ifdef CONFIG_PCI
		printf("       PCI CLK %s MHz INP CLK %s MHz VCO CLK %s MHz\n",
		       strmhz(buf1, gd->pci_clk),
		       strmhz(buf2, gd->inp_clk),
		       strmhz(buf3, gd->vco_clk));
#else
		printf("       INP CLK %s MHz VCO CLK %s MHz\n",
		       strmhz(buf1, gd->inp_clk),
		       strmhz(buf2, gd->vco_clk));
#endif
	}

	return 0;
}

#if defined(CONFIG_MCFFEC)

int cpu_eth_init(bd_t *bis)
{
	return mcffec_initialize(bis);
}
#endif
