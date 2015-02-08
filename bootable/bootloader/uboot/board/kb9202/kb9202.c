


#include <common.h>
#include <asm/arch/AT91RM9200.h>
#include <asm/io.h>
#include <netdev.h>
#if defined(CONFIG_DRIVER_ETHER)
#include <at91rm9200_net.h>
#include <lxt971a.h>
#endif

DECLARE_GLOBAL_DATA_PTR;


void lowlevel_init(void) {
	/* Required by assembly functions - do nothing	*/
}

int board_init (void)
{
	/* Enable Ctrlc */
	console_init_f ();

	/* memory and cpu-speed are setup before relocation */
	/* so we do _nothing_ here */

	gd->bd->bi_arch_number = MACH_TYPE_KB9200;

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

unsigned int lxt972_IsPhyConnected (AT91PS_EMAC p_mac);
UCHAR lxt972_GetLinkSpeed (AT91PS_EMAC p_mac);
UCHAR lxt972_InitPhy (AT91PS_EMAC p_mac);
UCHAR lxt972_AutoNegotiate (AT91PS_EMAC p_mac, int *status);

void at91rm9200_GetPhyInterface(AT91PS_PhyOps p_phyops)
{
	p_phyops->Init = lxt972_InitPhy;
	p_phyops->IsPhyConnected = lxt972_IsPhyConnected;
	p_phyops->GetLinkSpeed = lxt972_GetLinkSpeed;
	p_phyops->AutoNegotiate = lxt972_AutoNegotiate;
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
