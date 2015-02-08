

#ifndef _KEYMILE_HDLC_ENET_H_
#define _KEYMILE_HDLC_ENET_H_

/* Unfortuantely, we have do this to get the flag defines in the cbd_t */
#ifdef CONFIG_KM8XX
#include <commproc.h>
#endif
#ifdef CONFIG_MGCOGE
#include <mpc8260.h>
#include <asm/cpm_8260.h>
#endif




struct icn_hdr {
	unsigned char dest_addr;
	unsigned char src_addr;
	unsigned char application;
} __attribute__((packed));

#define ICNHDR_LEN	(sizeof(struct icn_hdr))
#define CRC_LEN		(sizeof(short))
/* bytes to remove from packet before sending it upstream */
#define REMOVE		(ICNHDR_LEN + CRC_LEN)

struct icn_frame {
	struct icn_hdr hdr;
	unsigned char data[0];	/* a place holder */
} __attribute__((packed));

/* Address field */
#define HDLC_UUA	0x00 /* Unicast Unit Address */
#define HDLC_UUA_MASK	0x3f /* the last 6 bits contain the slot number */
#define SET_HDLC_UUA(x) ((HDLC_UUA | ((x) & HDLC_UUA_MASK)))
#define HDLC_UACUA	0x7f /* Unicast Active Control Unit Address */
#define HDLC_BCAST	0xff /* broadcast */

/* Application field */
#define MGS_UUSP	0x00
#define MGS_UREP	0x01
#define MGS_IUP		0x02
#define MGS_UTA		0x03
#define MGS_MDS		0x04
#define MGS_ITIME	0x05
/* added by DENX */
#define MGS_NETCONS	0x06	/* netconsole */
#define MGS_TFTP	0x07

/* Useful defines for buffer sizes, etc. */
#define HDLC_PKTBUFSRX		32
#define MAX_FRAME_LENGTH	1500 /* ethernet frame size */
			 /*   14        +    28     */
#define INET_HDR_SIZE	(ETHER_HDR_SIZE + IP_HDR_SIZE)
#define INET_HDR_ALIGN	(((INET_HDR_SIZE + PKTALIGN - 1) / PKTALIGN) * PKTALIGN)
/* INET_HDR_SIZE is stripped off */
#define PKT_MAXBLR_SIZE	(MAX_FRAME_LENGTH + INET_HDR_ALIGN)

enum {
	IP_ADDR = 0,	/* getenv_IPaddr("serverip"); */
	IP_SERVER,	/* getenv_IPaddr("ipaddr"); */
	TFTP_SRC_PORT,	/* simple_strtol(getenv("tftpsrcp"), NULL, 10); */
	TFTP_DST_PORT,	/* simple_strtol(getenv("tftpdstp"), NULL, 10); */
	NETCONS_PORT,	/* simple_strtol(getenv("ncip"), NULL, 10); */
	CACHEDNUMBERS
};

#define WELL_KNOWN_PORT 69	/* Well known TFTP port # */

/* define this to create a test commend (htest) */
#undef TEST_IT
#ifdef TEST_IT
/* have to save a copy of the eth_device for the test command's use */
struct eth_device *seth;
#endif
/* define this for outputting of received packets */
#undef TEST_RX
/* define this for outputting of packets being sent */
#undef TEST_TX

#endif /* _KEYMILE_HDLC_ENET_H_ */
