

#include <asm/types.h>
#include <config.h>

#ifdef CONFIG_DRIVER_NETARMETH

#define SET_EADDR(ad,val) *(volatile unsigned int*)(ad + NETARM_ETH_MODULE_BASE) = val
#define GET_EADDR(ad) (*(volatile unsigned int*)(ad + NETARM_ETH_MODULE_BASE))

#define NA_MII_POLL_BUSY_DELAY 900

#define NA_MII_NEGOTIATE_DELAY 30

/* Registers in the physical layer chip */
#define MII_PHY_CONTROL		0
#define MII_PHY_STATUS		1
#define MII_PHY_ID              2
#define MII_PHY_AUTONEGADV	4

#endif /* CONFIG_DRIVER_NETARMETH */
