

#ifndef _ASM_IC_SSI_H_
#define _ASM_IC_SSI_H_ 1

int ssi_set_interface(int, int, int, int);
void ssi_chip_select(int);
u8 ssi_txrx_byte(u8);
void ssi_tx_byte(u8);
u8 ssi_rx_byte(void);


#endif
