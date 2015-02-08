

/* stuff specific for the sc520, but independent of implementation */

#include <common.h>
#include <asm/io.h>
#include <asm/ic/ssi.h>
#include <asm/ic/sc520.h>

int ssi_set_interface(int freq, int lsb_first, int inv_clock, int inv_phase)
{
	u8 temp=0;

	if (freq >= 8192) {
		temp |= CTL_CLK_SEL_4;
	} else if (freq >= 4096) {
		temp |= CTL_CLK_SEL_8;
	} else if (freq >= 2048) {
		temp |= CTL_CLK_SEL_16;
	} else if (freq >= 1024) {
		temp |= CTL_CLK_SEL_32;
	} else if (freq >= 512) {
		temp |= CTL_CLK_SEL_64;
	} else if (freq >= 256) {
		temp |= CTL_CLK_SEL_128;
	} else if (freq >= 128) {
		temp |= CTL_CLK_SEL_256;
	} else {
		temp |= CTL_CLK_SEL_512;
	}

	if (!lsb_first) {
		temp |= MSBF_ENB;
	}

	if (inv_clock) {
		temp |= CLK_INV_ENB;
	}

	if (inv_phase) {
		temp |= PHS_INV_ENB;
	}

	writeb(temp, &sc520_mmcr->ssictl);

	return 0;
}

u8 ssi_txrx_byte(u8 data)
{
	writeb(data, &sc520_mmcr->ssixmit);
	while (readb(&sc520_mmcr->ssista) & SSISTA_BSY);
	writeb(SSICMD_CMD_SEL_XMITRCV, &sc520_mmcr->ssicmd);
	while (readb(&sc520_mmcr->ssista) & SSISTA_BSY);

	return readb(&sc520_mmcr->ssircv);
}


void ssi_tx_byte(u8 data)
{
	writeb(data, &sc520_mmcr->ssixmit);
	while (readb(&sc520_mmcr->ssista) & SSISTA_BSY);
	writeb(SSICMD_CMD_SEL_XMIT, &sc520_mmcr->ssicmd);
}

u8 ssi_rx_byte(void)
{
	while (readb(&sc520_mmcr->ssista) & SSISTA_BSY);
	writeb(SSICMD_CMD_SEL_RCV, &sc520_mmcr->ssicmd);
	while (readb(&sc520_mmcr->ssista) & SSISTA_BSY);

	return readb(&sc520_mmcr->ssircv);
}
