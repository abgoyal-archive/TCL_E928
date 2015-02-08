

#include <common.h>
#include <netdev.h>
#include <asm/arch/AT91RM9200.h>
#include <asm/io.h>

#if defined(CONFIG_DRIVER_ETHER)
#include <at91rm9200_net.h>
#include <ks8721.h>
#endif

DECLARE_GLOBAL_DATA_PTR;

/* ------------------------------------------------------------------------- */

int board_init(void)
{
	/* Enable Ctrlc */
	console_init_f();
	/* arch number of CPUAT91-Board */
	gd->bd->bi_arch_number = MACH_TYPE_CPUAT91;
	/* adress of boot parameters */
	gd->bd->bi_boot_params = PHYS_SDRAM + 0x100;

	return 0;
}

int dram_init(void)
{
	gd->bd->bi_dram[0].start = PHYS_SDRAM;
	gd->bd->bi_dram[0].size = PHYS_SDRAM_SIZE;
	return 0;
}

#if defined(CONFIG_DRIVER_ETHER)
#if defined(CONFIG_CMD_NET)

void at91rm9200_GetPhyInterface(AT91PS_PhyOps p_phyops)
{
	p_phyops->Init = ks8721_initphy;
	p_phyops->IsPhyConnected = ks8721_isphyconnected;
	p_phyops->GetLinkSpeed = ks8721_getlinkspeed;
	p_phyops->AutoNegotiate = ks8721_autonegotiate;
}

#endif	/* CONFIG_CMD_NET */
#endif	/* CONFIG_DRIVER_ETHER */
#ifdef CONFIG_DRIVER_AT91EMAC

int board_eth_init(bd_t *bis)
{
	int rc = 0;
	rc = at91emac_register(bis, 0);
	return rc;
}
#endif
