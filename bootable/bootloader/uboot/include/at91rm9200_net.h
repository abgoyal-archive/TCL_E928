

#ifndef AT91RM9200_ETHERNET
#define AT91RM9200_ETHERNET

#include <common.h>
#include <asm/io.h>
#include <asm/arch/hardware.h>

#define FALSE 0
#define TRUE 1


#define ETHERNET_ADDRESS_SIZE           6

typedef unsigned char UCHAR;

/* Interface to drive the physical layer */
typedef struct _AT91S_PhyOps
{
	unsigned char (*Init)(AT91S_EMAC *pmac);
	unsigned int (*IsPhyConnected)(AT91S_EMAC  *pmac);
	unsigned char (*GetLinkSpeed)(AT91S_EMAC *pmac);
	unsigned char (*AutoNegotiate)(AT91S_EMAC *pmac, int *);

} AT91S_PhyOps,*AT91PS_PhyOps;


#define EMAC_DESC_DONE 0x00000001  /* ownership bit */
#define EMAC_DESC_WRAP 0x00000002  /* bit for wrap */

/******************  function prototypes **********************/

/* MII functions */
void at91rm9200_EmacEnableMDIO(AT91PS_EMAC p_mac);
void at91rm9200_EmacDisableMDIO(AT91PS_EMAC p_mac);
UCHAR at91rm9200_EmacReadPhy(AT91PS_EMAC p_mac, unsigned char RegisterAddress, unsigned short *pInput);
UCHAR at91rm9200_EmacWritePhy(AT91PS_EMAC p_mac, unsigned char RegisterAddress, unsigned short *pOutput);
void at91rm9200_GetPhyInterface(AT91PS_PhyOps p_phyops);

#endif /* AT91RM9200_ETHERNET */
