

#include <at91rm9200_net.h>
#include <net.h>
#ifdef CONFIG_DRIVER_ETHER

#include <bcm5221.h>

#if defined(CONFIG_CMD_NET)

unsigned int bcm5221_IsPhyConnected (AT91PS_EMAC p_mac)
{
	unsigned short Id1, Id2;

	at91rm9200_EmacEnableMDIO (p_mac);
	at91rm9200_EmacReadPhy (p_mac, BCM5221_PHYID1, &Id1);
	at91rm9200_EmacReadPhy (p_mac, BCM5221_PHYID2, &Id2);
	at91rm9200_EmacDisableMDIO (p_mac);

	if ((Id1 == (BCM5221_PHYID1_OUI >> 6)) &&
		((Id2 >> 10) == (BCM5221_PHYID1_OUI & BCM5221_LSB_MASK)))
		return TRUE;

	return FALSE;
}

unsigned char bcm5221_GetLinkSpeed (AT91PS_EMAC p_mac)
{
	unsigned short stat1, stat2;

	if (!at91rm9200_EmacReadPhy (p_mac, BCM5221_BMSR, &stat1))
		return FALSE;

	if (!(stat1 & BCM5221_LINK_STATUS))	/* link status up? */
		return FALSE;

	if (!at91rm9200_EmacReadPhy (p_mac, BCM5221_ACSR, &stat2))
		return FALSE;

	if ((stat1 & BCM5221_100BASE_TX_FD) && (stat2 & BCM5221_100) && (stat2 & BCM5221_FDX)) {
		/*set Emac for 100BaseTX and Full Duplex  */
		p_mac->EMAC_CFG |= AT91C_EMAC_SPD | AT91C_EMAC_FD;
		return TRUE;
	}

	if ((stat1 & BCM5221_10BASE_T_FD) && !(stat2 & BCM5221_100) && (stat2 & BCM5221_FDX)) {
		/*set MII for 10BaseT and Full Duplex  */
		p_mac->EMAC_CFG = (p_mac->EMAC_CFG &
				~(AT91C_EMAC_SPD | AT91C_EMAC_FD))
				| AT91C_EMAC_FD;
		return TRUE;
	}

	if ((stat1 & BCM5221_100BASE_TX_HD) && (stat2 & BCM5221_100) && !(stat2 & BCM5221_FDX)) {
		/*set MII for 100BaseTX and Half Duplex  */
		p_mac->EMAC_CFG = (p_mac->EMAC_CFG &
				~(AT91C_EMAC_SPD | AT91C_EMAC_FD))
				| AT91C_EMAC_SPD;
		return TRUE;
	}

	if ((stat1 & BCM5221_10BASE_T_HD) && !(stat2 & BCM5221_100) && !(stat2 & BCM5221_FDX)) {
		/*set MII for 10BaseT and Half Duplex  */
		p_mac->EMAC_CFG &= ~(AT91C_EMAC_SPD | AT91C_EMAC_FD);
		return TRUE;
	}
	return FALSE;
}


unsigned char bcm5221_InitPhy (AT91PS_EMAC p_mac)
{
	unsigned char ret = TRUE;
	unsigned short IntValue;

	at91rm9200_EmacEnableMDIO (p_mac);

	if (!bcm5221_GetLinkSpeed (p_mac)) {
		/* Try another time */
		ret = bcm5221_GetLinkSpeed (p_mac);
	}

	/* Disable PHY Interrupts */
	at91rm9200_EmacReadPhy (p_mac, BCM5221_INTR, &IntValue);
	/* clear FDX LED and INTR Enable */
	IntValue &= ~(BCM5221_FDX_LED | BCM5221_INTR_ENABLE);
	/* set FDX, SPD, Link, INTR masks */
	IntValue |= (BCM5221_FDX_MASK  | BCM5221_SPD_MASK |
		     BCM5221_LINK_MASK | BCM5221_INTR_MASK);
	at91rm9200_EmacWritePhy (p_mac, BCM5221_INTR, &IntValue);
	at91rm9200_EmacDisableMDIO (p_mac);

	return (ret);
}


unsigned char bcm5221_AutoNegotiate (AT91PS_EMAC p_mac, int *status)
{
	unsigned short value;
	unsigned short PhyAnar;
	unsigned short PhyAnalpar;

	/* Set bcm5221 control register */
	if (!at91rm9200_EmacReadPhy (p_mac, BCM5221_BMCR, &value))
		return FALSE;
	value &= ~BCM5221_AUTONEG;	/* remove autonegotiation enable */
	value |=  BCM5221_ISOLATE;	/* Electrically isolate PHY */
	if (!at91rm9200_EmacWritePhy (p_mac, BCM5221_BMCR, &value))
		return FALSE;

	/* Set the Auto_negotiation Advertisement Register */
	/* MII advertising for 100BaseTxFD and HD, 10BaseTFD and HD, IEEE 802.3 */
	PhyAnar = BCM5221_TX_FDX | BCM5221_TX_HDX |
		  BCM5221_10_FDX | BCM5221_10_HDX | BCM5221_AN_IEEE_802_3;
	if (!at91rm9200_EmacWritePhy (p_mac, BCM5221_ANAR, &PhyAnar))
		return FALSE;

	/* Read the Control Register     */
	if (!at91rm9200_EmacReadPhy (p_mac, BCM5221_BMCR, &value))
		return FALSE;

	value |= BCM5221_SPEED_SELECT | BCM5221_AUTONEG | BCM5221_DUPLEX_MODE;
	if (!at91rm9200_EmacWritePhy (p_mac, BCM5221_BMCR, &value))
		return FALSE;
	/* Restart Auto_negotiation  */
	value |= BCM5221_RESTART_AUTONEG;
	value &= ~BCM5221_ISOLATE;
	if (!at91rm9200_EmacWritePhy (p_mac, BCM5221_BMCR, &value))
		return FALSE;

	/*check AutoNegotiate complete */
	udelay (10000);
	at91rm9200_EmacReadPhy (p_mac, BCM5221_BMSR, &value);
	if (!(value & BCM5221_AUTONEG_COMP))
		return FALSE;

	/* Get the AutoNeg Link partner base page */
	if (!at91rm9200_EmacReadPhy (p_mac, BCM5221_ANLPAR, &PhyAnalpar))
		return FALSE;

	if ((PhyAnar & BCM5221_TX_FDX) && (PhyAnalpar & BCM5221_TX_FDX)) {
		/*set MII for 100BaseTX and Full Duplex  */
		p_mac->EMAC_CFG |= AT91C_EMAC_SPD | AT91C_EMAC_FD;
		return TRUE;
	}

	if ((PhyAnar & BCM5221_10_FDX) && (PhyAnalpar & BCM5221_10_FDX)) {
		/*set MII for 10BaseT and Full Duplex  */
		p_mac->EMAC_CFG = (p_mac->EMAC_CFG &
				~(AT91C_EMAC_SPD | AT91C_EMAC_FD))
				| AT91C_EMAC_FD;
		return TRUE;
	}
	return FALSE;
}

#endif

#endif	/* CONFIG_DRIVER_ETHER */
