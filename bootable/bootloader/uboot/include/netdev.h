


#ifndef _NETDEV_H_
#define _NETDEV_H_


int board_eth_init(bd_t *bis);
int cpu_eth_init(bd_t *bis);

/* Driver initialization prototypes */
int altera_tse_initialize(u8 dev_num, int mac_base,
			  int sgdma_rx_base, int sgdma_tx_base);
int au1x00_enet_initialize(bd_t*);
int at91emac_register(bd_t *bis, unsigned long iobase);
int bfin_EMAC_initialize(bd_t *bis);
int cs8900_initialize(u8 dev_num, int base_addr);
int dc21x4x_initialize(bd_t *bis);
int davinci_emac_initialize(void);
int dnet_eth_initialize(int id, void *regs, unsigned int phy_addr);
int e1000_initialize(bd_t *bis);
int eepro100_initialize(bd_t *bis);
int ep93xx_eth_initialize(u8 dev_num, int base_addr);
int ethoc_initialize(u8 dev_num, int base_addr);
int eth_3com_initialize (bd_t * bis);
int fec_initialize (bd_t *bis);
int fecmxc_initialize (bd_t *bis);
int ftmac100_initialize(bd_t *bits);
int greth_initialize(bd_t *bis);
void gt6426x_eth_initialize(bd_t *bis);
int inca_switch_initialize(bd_t *bis);
int kirkwood_egiga_initialize(bd_t *bis);
int lan91c96_initialize(u8 dev_num, int base_addr);
int macb_eth_initialize(int id, void *regs, unsigned int phy_addr);
int mcdmafec_initialize(bd_t *bis);
int mcffec_initialize(bd_t *bis);
int mpc512x_fec_initialize(bd_t *bis);
int mpc5xxx_fec_initialize(bd_t *bis);
int mpc8220_fec_initialize(bd_t *bis);
int mpc82xx_scc_enet_initialize(bd_t *bis);
int natsemi_initialize(bd_t *bis);
int npe_initialize(bd_t *bis);
int ns8382x_initialize(bd_t *bis);
int pcnet_initialize(bd_t *bis);
int plb2800_eth_initialize(bd_t *bis);
int ppc_4xx_eth_initialize (bd_t *bis);
int rtl8139_initialize(bd_t *bis);
int rtl8169_initialize(bd_t *bis);
int scc_initialize(bd_t *bis);
int skge_initialize(bd_t *bis);
int smc911x_initialize(u8 dev_num, int base_addr);
int smc91111_initialize(u8 dev_num, int base_addr);
int tsi108_eth_initialize(bd_t *bis);
int uec_initialize(int index);
int uec_standard_init(bd_t *bis);
int uli526x_initialize(bd_t *bis);
int sh_eth_initialize(bd_t *bis);
int dm9000_initialize(bd_t *bis);


static inline int pci_eth_init(bd_t *bis)
{
	int num = 0;

#ifdef CONFIG_PCI

#ifdef CONFIG_EEPRO100
	num += eepro100_initialize(bis);
#endif
#ifdef CONFIG_TULIP
	num += dc21x4x_initialize(bis);
#endif
#ifdef CONFIG_E1000
	num += e1000_initialize(bis);
#endif
#ifdef CONFIG_PCNET
	num += pcnet_initialize(bis);
#endif
#ifdef CONFIG_NATSEMI
	num += natsemi_initialize(bis);
#endif
#ifdef CONFIG_NS8382X
	num += ns8382x_initialize(bis);
#endif
#if defined(CONFIG_RTL8139)
	num += rtl8139_initialize(bis);
#endif
#if defined(CONFIG_RTL8169)
	num += rtl8169_initialize(bis);
#endif
#if defined(CONFIG_ULI526X)
	num += uli526x_initialize(bis);
#endif

#endif  /* CONFIG_PCI */
	return num;
}

#if defined(CONFIG_MV88E61XX_SWITCH)
enum mv88e61xx_cfg_vlan {
	MV88E61XX_VLANCFG_DEFAULT,
	MV88E61XX_VLANCFG_ROUTER
};

enum mv88e61xx_cfg_mdip {
	MV88E61XX_MDIP_NOCHANGE,
	MV88E61XX_MDIP_REVERSE
};

enum mv88e61xx_cfg_ledinit {
	MV88E61XX_LED_INIT_DIS,
	MV88E61XX_LED_INIT_EN
};

enum mv88e61xx_cfg_rgmiid {
	MV88E61XX_RGMII_DELAY_DIS,
	MV88E61XX_RGMII_DELAY_EN
};

enum mv88e61xx_cfg_prtstt {
	MV88E61XX_PORTSTT_DISABLED,
	MV88E61XX_PORTSTT_BLOCKING,
	MV88E61XX_PORTSTT_LEARNING,
	MV88E61XX_PORTSTT_FORWARDING
};

struct mv88e61xx_config {
	char *name;
	enum mv88e61xx_cfg_vlan vlancfg;
	enum mv88e61xx_cfg_rgmiid rgmii_delay;
	enum mv88e61xx_cfg_prtstt portstate;
	enum mv88e61xx_cfg_ledinit led_init;
	enum mv88e61xx_cfg_mdip mdip;
	u32 ports_enabled;
	u8 cpuport;
};

int mv88e61xx_switch_initialize(struct mv88e61xx_config *swconfig);
#endif /* CONFIG_MV88E61XX_SWITCH */

#endif /* _NETDEV_H_ */
