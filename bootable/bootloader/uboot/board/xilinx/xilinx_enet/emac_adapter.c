

#include <config.h>
#include <common.h>
#include <net.h>
#include "xemac.h"

#if defined(XPAR_EMAC_0_DEVICE_ID)

#define ENET_MAX_MTU           PKTSIZE
#define ENET_MAX_MTU_ALIGNED   PKTSIZE_ALIGN
#define ENET_ADDR_LENGTH       6

static XEmac Emac;
static char etherrxbuff[PKTSIZE_ALIGN];	/* Receive buffer */

/* hardcoded MAC address for the Xilinx EMAC Core when env is nowhere*/
#ifdef CONFIG_ENV_IS_NOWHERE
static u8 EMACAddr[ENET_ADDR_LENGTH] = { 0x00, 0x0a, 0x35, 0x00, 0x22, 0x01 };
#endif

static int initialized = 0;

void
eth_halt(void)
{
	if (initialized)
		(void) XEmac_Stop(&Emac);
}

int
eth_init(bd_t * bis)
{
	u32 Options;
	XStatus Result;
	uchar enetaddr[6];

#ifdef DEBUG
	printf("EMAC Initialization Started\n\r");
#endif

	Result = XEmac_Initialize(&Emac, XPAR_EMAC_0_DEVICE_ID);
	if (Result != XST_SUCCESS) {
		return 0;
	}

	/* make sure the Emac is stopped before it is started */
	(void) XEmac_Stop(&Emac);

	if (!eth_getenv_enetaddr("ethaddr", enetaddr)) {
#ifdef CONFIG_ENV_IS_NOWHERE
		memcpy(enetaddr, EMACAddr, 6);
		eth_setenv_enetaddr("ethaddr", enetaddr);
#endif
	}

	Result = XEmac_SetMacAddress(&Emac, enetaddr);
	if (Result != XST_SUCCESS) {
		return 0;
	}

	Options =
	    (XEM_POLLED_OPTION | XEM_UNICAST_OPTION | XEM_BROADCAST_OPTION |
	     XEM_FDUPLEX_OPTION | XEM_INSERT_FCS_OPTION |
	     XEM_INSERT_PAD_OPTION);
	Result = XEmac_SetOptions(&Emac, Options);
	if (Result != XST_SUCCESS) {
		return 0;
	}

	Result = XEmac_Start(&Emac);
	if (Result != XST_SUCCESS) {
		return 0;
	}
#ifdef DEBUG
	printf("EMAC Initialization complete\n\r");
#endif

	initialized = 1;

	return (0);
}

int
eth_send(volatile void *ptr, int len)
{
	XStatus Result;

	if (len > ENET_MAX_MTU)
		len = ENET_MAX_MTU;

	Result = XEmac_PollSend(&Emac, (u8 *) ptr, len);
	if (Result == XST_SUCCESS) {
		return (1);
	} else {
		printf("Error while sending frame\n\r");
		return (0);
	}

}

int
eth_rx(void)
{
	u32 RecvFrameLength;
	XStatus Result;

	RecvFrameLength = PKTSIZE;
	Result = XEmac_PollRecv(&Emac, (u8 *) etherrxbuff, &RecvFrameLength);
	if (Result == XST_SUCCESS) {
#ifndef CONFIG_EMACLITE
		NetReceive((uchar *)etherrxbuff, RecvFrameLength);
#else
		NetReceive(etherrxbuff, RecvFrameLength);
#endif
		return (1);
	} else {
		return (0);
	}
}

#endif
