

#include <common.h>
#include <asm/arch/AT91RM9200.h>
#include <netdev.h>
#include <asm/io.h>
#if defined(CONFIG_DRIVER_ETHER)
#include <at91rm9200_net.h>
#include <dm9161.h>
#endif
#include <asm/mach-types.h>

DECLARE_GLOBAL_DATA_PTR;


int board_init (void)
{
	/* Enable Ctrlc */
	console_init_f ();

	/* memory and cpu-speed are setup before relocation */
	/* so we do _nothing_ here */

	/* arch number of MP2USB-Board. */
	gd->bd->bi_arch_number = MACH_TYPE_MP2USB;
	/* adress of boot parameters */
	gd->bd->bi_boot_params = PHYS_SDRAM + 0x100;

	return 0;
}

int dram_init (void)
{
	gd->bd->bi_dram[0].start = PHYS_SDRAM;
	gd->bd->bi_dram[0].size = PHYS_SDRAM_SIZE;
	return 0;
}

#ifdef CONFIG_DRIVER_ETHER
#if defined(CONFIG_CMD_NET)

void at91rm9200_GetPhyInterface(AT91PS_PhyOps p_phyops)
{
	p_phyops->Init = dm9161_InitPhy;
	p_phyops->IsPhyConnected = dm9161_IsPhyConnected;
	p_phyops->GetLinkSpeed = dm9161_GetLinkSpeed;
	p_phyops->AutoNegotiate = dm9161_AutoNegotiate;
}

#endif
#endif	/* CONFIG_DRIVER_ETHER */

#ifdef CONFIG_DRIVER_AT91EMAC
int board_eth_init(bd_t *bis)
{
	int rc = 0;
	rc = at91emac_register(bis, 0);
	return rc;
}
#endif