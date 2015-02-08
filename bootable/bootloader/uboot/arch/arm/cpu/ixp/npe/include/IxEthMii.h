

#ifndef IxEthMii_H
#define IxEthMii_H

#include <IxTypes.h>


PUBLIC IX_STATUS ixEthMiiPhyScan(BOOL phyPresent[], UINT32 maxPhyCount);

PUBLIC IX_STATUS ixEthMiiPhyConfig(UINT32 phyAddr,
				    BOOL speed100, 
				    BOOL fullDuplex, 
				    BOOL autonegotiate);

PUBLIC IX_STATUS
ixEthMiiPhyLoopbackEnable (UINT32 phyAddr);

PUBLIC IX_STATUS
ixEthMiiPhyLoopbackDisable (UINT32 phyAddr);

PUBLIC IX_STATUS ixEthMiiPhyReset(UINT32 phyAddr);


PUBLIC IX_STATUS ixEthMiiLinkStatus(UINT32 phyAddr, 
				     BOOL *linkUp,
				     BOOL *speed100, 
				     BOOL *fullDuplex,
				     BOOL *autoneg);

PUBLIC IX_STATUS ixEthMiiPhyShow (UINT32 phyAddr);

#endif /* ndef IxEthMii_H */
