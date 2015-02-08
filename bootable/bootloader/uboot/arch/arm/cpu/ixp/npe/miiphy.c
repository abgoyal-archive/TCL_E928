

#include <common.h>
#include <miiphy.h>
#include "IxOsal.h"
#include "IxEthAcc.h"
#include "IxEthAcc_p.h"
#include "IxEthAccMac_p.h"
#include "IxEthAccMii_p.h"

/***********************************************************/
/* Dump out to the screen PHY regs			   */
/***********************************************************/

void miiphy_dump (char *devname, unsigned char addr)
{
	unsigned long i;
	unsigned short data;


	for (i = 0; i < 0x1A; i++) {
		if (miiphy_read (devname, addr, i, &data)) {
			printf ("read error for reg %lx\n", i);
			return;
		}
		printf ("Phy reg %lx ==> %4x\n", i, data);

		/* jump to the next set of regs */
		if (i == 0x07)
			i = 0x0f;

	}			/* end for loop */
}				/* end dump */


/***********************************************************/
/* (Re)start autonegotiation				   */
/***********************************************************/
int phy_setup_aneg (char *devname, unsigned char addr)
{
	unsigned short ctl, adv;

	/* Setup standard advertise */
	miiphy_read (devname, addr, PHY_ANAR, &adv);
	adv |= (PHY_ANLPAR_ACK | PHY_ANLPAR_RF | PHY_ANLPAR_T4 |
		PHY_ANLPAR_TXFD | PHY_ANLPAR_TX | PHY_ANLPAR_10FD |
		PHY_ANLPAR_10);
	miiphy_write (devname, addr, PHY_ANAR, adv);

	/* Start/Restart aneg */
	miiphy_read (devname, addr, PHY_BMCR, &ctl);
	ctl |= (PHY_BMCR_AUTON | PHY_BMCR_RST_NEG);
	miiphy_write (devname, addr, PHY_BMCR, ctl);

	return 0;
}


int npe_miiphy_read (char *devname, unsigned char addr,
		     unsigned char reg, unsigned short *value)
{
	u16 val;

	ixEthAccMiiReadRtn(addr, reg, &val);
	*value = val;

	return 0;
}				/* phy_read */


int npe_miiphy_write (char *devname, unsigned char addr,
		      unsigned char reg, unsigned short value)
{
	ixEthAccMiiWriteRtn(addr, reg, value);
	return 0;
}				/* phy_write */
