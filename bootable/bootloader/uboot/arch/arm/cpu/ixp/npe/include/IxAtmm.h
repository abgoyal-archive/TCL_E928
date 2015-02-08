



#ifndef IXATMM_H
#define IXATMM_H

#include "IxAtmSch.h"
#include "IxOsalTypes.h"


#define IX_ATMM_RET_ALREADY_INITIALIZED 2

#define IX_ATMM_RET_INVALID_PORT 3

#define IX_ATMM_RET_INVALID_VC_DESCRIPTOR 4

#define IX_ATMM_RET_VC_CONFLICT 5

#define IX_ATMM_RET_PORT_CAPACITY_IS_FULL 6

#define IX_ATMM_RET_NO_SUCH_VC 7

#define IX_ATMM_RET_INVALID_VC_ID 8

#define IX_ATMM_RET_INVALID_PARAM_PTR 9

#define IX_ATMM_UTOPIA_SPHY_ADDR 31

#define IX_ATMM_THREAD_PRI_HIGH 90


typedef enum
{
    IX_ATMM_VC_DIRECTION_TX=0, /**< Atmm Vc direction transmit*/
    IX_ATMM_VC_DIRECTION_RX, /**< Atmm Vc direction receive*/
    IX_ATMM_VC_DIRECTION_INVALID /**< Atmm Vc direction invalid*/
} IxAtmmVcDirection;

typedef enum
{
    IX_ATMM_VC_CHANGE_EVENT_REGISTER=0, /**< Atmm Vc event register*/
    IX_ATMM_VC_CHANGE_EVENT_DEREGISTER, /**< Atmm Vc event de-register*/
    IX_ATMM_VC_CHANGE_EVENT_INVALID /**< Atmm Vc event invalid*/
} IxAtmmVcChangeEvent;

typedef enum
{
    IX_ATMM_UTOPIA_LOOPBACK_DISABLED=0, /**< Atmm Utopia loopback mode disabled*/
    IX_ATMM_UTOPIA_LOOPBACK_ENABLED, /**< Atmm Utopia loopback mode enabled*/
    IX_ATMM_UTOPIA_LOOPBACK_INVALID /**< Atmm Utopia loopback mode invalid*/
} IxAtmmUtopiaLoopbackMode;

typedef struct {
    unsigned vpi;  /**< VPI value of this virtual connection */
    unsigned vci;  /**< VCI value of this virtual connection. */
    IxAtmmVcDirection direction; /**< VC direction */

    /** Traffic descriptor of this virtual connection.  This structure
     *  is defined by the @ref IxAtmSch component.  */
    IxAtmTrafficDescriptor trafficDesc;
} IxAtmmVc;


typedef enum
{
    IX_ATMM_MPHY_MODE = 0, /**< Atmm phy mode mphy*/
    IX_ATMM_SPHY_MODE, /**< Atmm phy mode sphy*/
    IX_ATMM_PHY_MODE_INVALID /**< Atmm phy mode invalid*/
} IxAtmmPhyMode;


typedef struct {
    unsigned reserved_1:11;     /**< [31:21] Should be zero */
    unsigned UtopiaTxPhyAddr:5; /**< [20:16] Address of the
     *   transmit (Tx) PHY for this
     *   port on the 5-bit UTOPIA
     *   Level-2 address bus */
    unsigned reserved_2:11;     /**< [15:5] Should be zero */
    unsigned UtopiaRxPhyAddr:5; /**< [4:0] Address of the receive
     *   (Rx) PHY for this port on the
     *   5-bit UTOPIA  Level-2
     *   address bus */
} IxAtmmPortCfg;

typedef void (*IxAtmmVcChangeCallback) (IxAtmmVcChangeEvent eventType,
					IxAtmLogicalPort port,
					const IxAtmmVc* vcChanged);





PUBLIC IX_STATUS
ixAtmmInit (void);

PUBLIC IX_STATUS
ixAtmmUtopiaInit (unsigned numPorts,
		  IxAtmmPhyMode phyMode,
		  IxAtmmPortCfg portCfgs[],
		  IxAtmmUtopiaLoopbackMode loopbackMode);


PUBLIC IX_STATUS
ixAtmmPortInitialize (IxAtmLogicalPort port,
		      unsigned txPortRate,
		      unsigned rxPortRate);

PUBLIC IX_STATUS
ixAtmmPortModify (IxAtmLogicalPort port,
		  unsigned txPortRate,
		  unsigned rxPortRate);

PUBLIC IX_STATUS
ixAtmmPortQuery (IxAtmLogicalPort port,
		 unsigned *txPortRate,
		 unsigned *rxPortRate);

PUBLIC IX_STATUS
ixAtmmPortEnable(IxAtmLogicalPort port);

PUBLIC IX_STATUS
ixAtmmPortDisable(IxAtmLogicalPort port);

PUBLIC IX_STATUS
ixAtmmVcRegister (IxAtmLogicalPort port,
		  IxAtmmVc *vcToAdd,
		  IxAtmSchedulerVcId *vcId);

PUBLIC IX_STATUS
ixAtmmVcDeregister (IxAtmLogicalPort port, IxAtmSchedulerVcId vcId);

PUBLIC IX_STATUS
ixAtmmVcQuery (IxAtmLogicalPort port,
	       unsigned vpi,
	       unsigned vci,
	       IxAtmmVcDirection direction,
	       IxAtmSchedulerVcId *vcId,
	       IxAtmmVc *vcDesc);


PUBLIC IX_STATUS
ixAtmmVcIdQuery (IxAtmLogicalPort port, IxAtmSchedulerVcId vcId, IxAtmmVc *vcDesc);

PUBLIC IX_STATUS ixAtmmVcChangeCallbackRegister (IxAtmmVcChangeCallback callback);


PUBLIC IX_STATUS
ixAtmmVcChangeCallbackDeregister (IxAtmmVcChangeCallback callback);

PUBLIC IX_STATUS
ixAtmmUtopiaStatusShow (void);

PUBLIC IX_STATUS
ixAtmmUtopiaCfgShow (void);

#endif
/* IXATMM_H */

/** @} */
