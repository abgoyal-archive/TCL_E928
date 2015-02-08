

#include <common.h>
#include <command.h>
#include <net.h>
#include "nfs.h"
#include "bootp.h"
#include "rarp.h"
#include "tftp.h"

#define TIMEOUT		5000UL	/* Milliseconds before trying BOOTP again */
#ifndef	CONFIG_NET_RETRY_COUNT
# define TIMEOUT_COUNT	5		/* # of timeouts before giving up  */
#else
# define TIMEOUT_COUNT  (CONFIG_NET_RETRY_COUNT)
#endif


int		RarpTry;

static void
RarpHandler(uchar * dummi0, unsigned dummi1, unsigned dummi2, unsigned dummi3)
{
	char *s;
	debug("Got good RARP\n");
	if ((s = getenv("autoload")) != NULL) {
		if (*s == 'n') {
			/*
			 * Just use RARP to configure system;
			 * Do not use TFTP/NFS to to load the bootfile.
			 */
			NetState = NETLOOP_SUCCESS;
			return;
#if defined(CONFIG_CMD_NFS)
		} else if ((s != NULL) && !strcmp(s, "NFS")) {
			NfsStart();
			return;
#endif
		}
	}
	TftpStart ();
}


static void
RarpTimeout(void)
{
	if (RarpTry >= TIMEOUT_COUNT) {
		puts ("\nRetry count exceeded; starting again\n");
		NetStartAgain ();
	} else {
		NetSetTimeout (TIMEOUT, RarpTimeout);
		RarpRequest ();
	}
}


void
RarpRequest (void)
{
	int i;
	volatile uchar *pkt;
	ARP_t *	rarp;

	printf("RARP broadcast %d\n", ++RarpTry);
	pkt = NetTxPacket;

	pkt += NetSetEther(pkt, NetBcastAddr, PROT_RARP);

	rarp = (ARP_t *)pkt;

	rarp->ar_hrd = htons (ARP_ETHER);
	rarp->ar_pro = htons (PROT_IP);
	rarp->ar_hln = 6;
	rarp->ar_pln = 4;
	rarp->ar_op  = htons (RARPOP_REQUEST);
	memcpy (&rarp->ar_data[0],  NetOurEther, 6);	/* source ET addr */
	memcpy (&rarp->ar_data[6],  &NetOurIP,   4);	/* source IP addr */
	memcpy (&rarp->ar_data[10], NetOurEther, 6);	/* dest ET addr = source ET addr ??*/
	/* dest. IP addr set to broadcast */
	for (i = 0; i <= 3; i++) {
		rarp->ar_data[16 + i] = 0xff;
	}

	NetSendPacket(NetTxPacket, (pkt - NetTxPacket) + ARP_HDR_SIZE);

	NetSetTimeout(TIMEOUT, RarpTimeout);
	NetSetHandler(RarpHandler);
}
