


#include <common.h>
#include <at91rm9200_net.h>
#include <net.h>
#include <miiphy.h>
#include <lxt971a.h>

#ifdef CONFIG_DRIVER_ETHER

#if defined(CONFIG_CMD_NET)

unsigned int lxt972_IsPhyConnected (AT91PS_EMAC p_mac)
{
	unsigned short Id1, Id2;

	at91rm9200_EmacEnableMDIO (p_mac);
	at91rm9200_EmacReadPhy(p_mac, PHY_PHYIDR1, &Id1);
	at91rm9200_EmacReadPhy(p_mac, PHY_PHYIDR2, &Id2);
	at91rm9200_EmacDisableMDIO (p_mac);

	if ((Id1 == (0x0013)) && ((Id2  & 0xFFF0) == 0x78E0))
		return TRUE;

	return FALSE;
}

UCHAR lxt972_GetLinkSpeed (AT91PS_EMAC p_mac)
{
	unsigned short stat1;

	if (!at91rm9200_EmacReadPhy (p_mac, PHY_LXT971_STAT2, &stat1))
		return FALSE;

	if (!(stat1 & PHY_LXT971_STAT2_LINK))	/* link status up? */
		return FALSE;

	if (stat1 & PHY_LXT971_STAT2_100BTX) {

		if (stat1 & PHY_LXT971_STAT2_DUPLEX_MODE) {

			/*set Emac for 100BaseTX and Full Duplex  */
			p_mac->EMAC_CFG |= AT91C_EMAC_SPD | AT91C_EMAC_FD;
		} else {

			/*set Emac for 100BaseTX and Half Duplex  */
			p_mac->EMAC_CFG = (p_mac->EMAC_CFG &
					~(AT91C_EMAC_SPD | AT91C_EMAC_FD))
					| AT91C_EMAC_SPD;
		}

		return TRUE;

	} else {

		if (stat1 & PHY_LXT971_STAT2_DUPLEX_MODE) {

			/*set MII for 10BaseT and Full Duplex  */
			p_mac->EMAC_CFG = (p_mac->EMAC_CFG &
					~(AT91C_EMAC_SPD | AT91C_EMAC_FD))
					| AT91C_EMAC_FD;
		} else {

			/*set MII for 10BaseT and Half Duplex  */
			p_mac->EMAC_CFG &= ~(AT91C_EMAC_SPD | AT91C_EMAC_FD);
		}

		return TRUE;
	}

	return FALSE;
}


UCHAR lxt972_InitPhy (AT91PS_EMAC p_mac)
{
	UCHAR ret = TRUE;

	at91rm9200_EmacEnableMDIO (p_mac);

	if (!lxt972_GetLinkSpeed (p_mac)) {
		/* Try another time */
		ret = lxt972_GetLinkSpeed (p_mac);
	}

	/* Disable PHY Interrupts */
	at91rm9200_EmacWritePhy (p_mac, PHY_LXT971_INT_ENABLE, 0);

	at91rm9200_EmacDisableMDIO (p_mac);

	return (ret);
}


UCHAR lxt972_AutoNegotiate (AT91PS_EMAC p_mac, int *status)
{
	unsigned short value;

	/* Set lxt972 control register */
	if (!at91rm9200_EmacReadPhy (p_mac, PHY_BMCR, &value))
		return FALSE;

	/* Restart Auto_negotiation  */
	value |= PHY_BMCR_RST_NEG;
	if (!at91rm9200_EmacWritePhy (p_mac, PHY_BMCR, &value))
		return FALSE;

	/*check AutoNegotiate complete */
	udelay (10000);
	at91rm9200_EmacReadPhy(p_mac, PHY_BMSR, &value);
	if (!(value & PHY_BMSR_AUTN_COMP))
		return FALSE;

	return (lxt972_GetLinkSpeed (p_mac));
}

#endif

#endif	/* CONFIG_DRIVER_ETHER */
