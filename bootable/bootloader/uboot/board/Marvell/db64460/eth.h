


#ifndef __EVB64460_ETH_H__
#define __EVB64460_ETH_H__

#include <asm/types.h>
#include <asm/io.h>
#include <asm/byteorder.h>
#include <common.h>

int db64460_eth0_poll(void);
int db64460_eth0_transmit(unsigned int s, volatile char *p);
void db64460_eth0_disable(void);
bool network_start(bd_t *bis);

#endif /* __EVB64460_ETH_H__ */
