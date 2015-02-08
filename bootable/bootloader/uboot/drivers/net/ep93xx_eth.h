

#ifndef _EP93XX_ETH_H
#define _EP93XX_ETH_H

#include <net.h>

#undef EP93XX_MAC_DEBUG

#define NUMRXDESC		PKTBUFSRX

#define NUMTXDESC		1

#define TXSTARTMAX		944

struct rx_descriptor {
	uint32_t word1;
	uint32_t word2;
};

struct rx_status {
	uint32_t word1;
	uint32_t word2;
};

#define RX_STATUS_RWE(rx_status) ((rx_status->word1 >> 30) & 0x01)
#define RX_STATUS_RFP(rx_status) ((rx_status->word1 >> 31) & 0x01)
#define RX_STATUS_FRAME_LEN(rx_status) (rx_status->word2 & 0xFFFF)

struct tx_descriptor {
	uint32_t word1;
	uint32_t word2;
};

#define TX_DESC_EOF (1 << 31)

struct tx_status {
	uint32_t word1;
};

#define TX_STATUS_TXWE(tx_status) (((tx_status)->word1 >> 30) & 0x01)
#define TX_STATUS_TXFP(tx_status) (((tx_status)->word1 >> 31) & 0x01)

struct tx_descriptor_queue {
	struct tx_descriptor *base;
	struct tx_descriptor *current;
	struct tx_descriptor *end;
};

struct tx_status_queue {
	struct tx_status *base;
	volatile struct tx_status *current;
	struct tx_status *end;
};

struct rx_descriptor_queue {
	struct rx_descriptor *base;
	struct rx_descriptor *current;
	struct rx_descriptor *end;
};

struct rx_status_queue {
	struct rx_status *base;
	volatile struct rx_status *current;
	struct rx_status *end;
};

struct ep93xx_priv {
	struct rx_descriptor_queue	rx_dq;
	struct rx_status_queue		rx_sq;
	void				*rx_buffer[NUMRXDESC];

	struct tx_descriptor_queue	tx_dq;
	struct tx_status_queue		tx_sq;

	struct mac_regs			*regs;
};

#endif
