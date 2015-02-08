

#include <at91rm9200_net.h>
#include <net.h>
#include <ks8721.h>

#ifdef CONFIG_DRIVER_ETHER

#if defined(CONFIG_CMD_NET)

unsigned int ks8721_isphyconnected(AT91PS_EMAC p_mac)
{
	unsigned short id1, id2;

	at91rm9200_EmacEnableMDIO(p_mac);
	at91rm9200_EmacReadPhy(p_mac,
		CONFIG_PHY_ADDRESS | KS8721_PHYID1, &id1);
	at91rm9200_EmacReadPhy(p_mac,
		CONFIG_PHY_ADDRESS | KS8721_PHYID2, &id2);
	at91rm9200_EmacDisableMDIO(p_mac);

	if ((id1 == (KS8721_PHYID_OUI >> 6)) &&
		((id2 >> 10) == (KS8721_PHYID_OUI & KS8721_LSB_MASK))) {
		if ((id2 & KS8721_MODELMASK) == KS8721BL_MODEL)
			printf("Micrel KS8721bL PHY detected : ");
		else
			printf("Unknown Micrel PHY detected : ");
		return 1;
	}
	return 0;
}

unsigned char ks8721_getlinkspeed(AT91PS_EMAC p_mac)
{
	unsigned short stat1;

	if (!at91rm9200_EmacReadPhy(p_mac, KS8721_BMSR, &stat1))
		return 0;

	if (!(stat1 & KS8721_LINK_STATUS)) {
		/* link status up? */
		printf("Link Down !\n");
		return 0;
	}

	if (stat1 & KS8721_100BASE_TX_FD) {
		/* set Emac for 100BaseTX and Full Duplex */
		printf("100BT FD\n");
		p_mac->EMAC_CFG |= AT91C_EMAC_SPD | AT91C_EMAC_FD;
		return 1;
	}

	if (stat1 & KS8721_10BASE_T_FD) {
		/* set MII for 10BaseT and Full Duplex */
		printf("10BT FD\n");
		p_mac->EMAC_CFG = (p_mac->EMAC_CFG &
				~(AT91C_EMAC_SPD | AT91C_EMAC_FD))
				| AT91C_EMAC_FD;
		return 1;
	}

	if (stat1 & KS8721_100BASE_T4_HD) {
		/* set MII for 100BaseTX and Half Duplex */
		printf("100BT HD\n");
		p_mac->EMAC_CFG = (p_mac->EMAC_CFG &
				~(AT91C_EMAC_SPD | AT91C_EMAC_FD))
				| AT91C_EMAC_SPD;
		return 1;
	}

	if (stat1 & KS8721_10BASE_T_HD) {
		/* set MII for 10BaseT and Half Duplex */
		printf("10BT HD\n");
		p_mac->EMAC_CFG &= ~(AT91C_EMAC_SPD | AT91C_EMAC_FD);
		return 1;
	}
	return 0;
}

unsigned char ks8721_initphy(AT91PS_EMAC p_mac)
{
	unsigned char ret = 1;
	unsigned short intvalue;

	at91rm9200_EmacEnableMDIO(p_mac);

	/* Try another time */
	if (!ks8721_getlinkspeed(p_mac))
		ret = ks8721_getlinkspeed(p_mac);

	/* Disable PHY Interrupts */
	intvalue = 0;
	at91rm9200_EmacWritePhy(p_mac,
		CONFIG_PHY_ADDRESS | KS8721_MDINTR, &intvalue);
	at91rm9200_EmacDisableMDIO(p_mac);

	return ret;
}

unsigned char ks8721_autonegotiate(AT91PS_EMAC p_mac, int *status)
{
	unsigned short value;
	unsigned short phyanar;
	unsigned short phyanalpar;

	/* Set ks8721 control register */
	if (!at91rm9200_EmacReadPhy(p_mac,
		CONFIG_PHY_ADDRESS | KS8721_BMCR, &value))
		return 0;

	/* remove autonegotiation enable */
	value &= ~KS8721_AUTONEG;
	/* Electrically isolate PHY */
	value |= KS8721_ISOLATE;
	if (!at91rm9200_EmacWritePhy(p_mac,
		CONFIG_PHY_ADDRESS | KS8721_BMCR, &value)) {
		return 0;
	}
	/*
	 * Set the Auto_negotiation Advertisement Register
	 * MII advertising for Next page, 100BaseTxFD and HD,
	 * 10BaseTFD and HD, IEEE 802.3
	 */
	phyanar = KS8721_NP | KS8721_TX_FDX | KS8721_TX_HDX |
		  KS8721_10_FDX | KS8721_10_HDX | KS8721_AN_IEEE_802_3;
	if (!at91rm9200_EmacWritePhy(p_mac,
		CONFIG_PHY_ADDRESS | KS8721_ANAR, &phyanar)) {
		return 0;
	}
	/* Read the Control Register */
	if (!at91rm9200_EmacReadPhy(p_mac,
		CONFIG_PHY_ADDRESS | KS8721_BMCR, &value)) {
		return 0;
	}
	value |= KS8721_SPEED_SELECT | KS8721_AUTONEG | KS8721_DUPLEX_MODE;
	if (!at91rm9200_EmacWritePhy(p_mac,
		CONFIG_PHY_ADDRESS | KS8721_BMCR, &value)) {
		return 0;
	}
	/* Restart Auto_negotiation */
	value |= KS8721_RESTART_AUTONEG;
	value &= ~KS8721_ISOLATE;
	if (!at91rm9200_EmacWritePhy(p_mac,
		CONFIG_PHY_ADDRESS | KS8721_BMCR, &value)) {
		return 0;
	}
	/* Check AutoNegotiate complete */
	udelay(10000);
	at91rm9200_EmacReadPhy(p_mac,
		CONFIG_PHY_ADDRESS | KS8721_BMSR, &value);
	if (!(value & KS8721_AUTONEG_COMP))
		return 0;

	/* Get the AutoNeg Link partner base page */
	if (!at91rm9200_EmacReadPhy(p_mac,
		CONFIG_PHY_ADDRESS | KS8721_ANLPAR, &phyanalpar)) {
		return 0;
	}

	if ((phyanar & KS8721_TX_FDX) && (phyanalpar & KS8721_TX_FDX)) {
		/* Set MII for 100BaseTX and Full Duplex */
		p_mac->EMAC_CFG |= AT91C_EMAC_SPD | AT91C_EMAC_FD;
		return 1;
	}

	if ((phyanar & KS8721_10_FDX) && (phyanalpar & KS8721_10_FDX)) {
		/* Set MII for 10BaseT and Full Duplex */
		p_mac->EMAC_CFG = (p_mac->EMAC_CFG &
				~(AT91C_EMAC_SPD | AT91C_EMAC_FD))
				| AT91C_EMAC_FD;
		return 1;
	}
	return 0;
}

#endif	/* CONFIG_CMD_NET */

#endif	/* CONFIG_DRIVER_ETHER */
