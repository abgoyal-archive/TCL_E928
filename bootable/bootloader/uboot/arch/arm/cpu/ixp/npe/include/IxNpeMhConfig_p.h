


#ifndef IXNPEMHCONFIG_P_H
#define IXNPEMHCONFIG_P_H

#include "IxOsal.h"

#include "IxNpeMh.h"
#include "IxNpeMhMacros_p.h"

/* enable function inlining for performances */
#ifdef IXNPEMHSOLICITEDCBMGR_C
#		ifndef __wince
#			ifndef IXNPEMHCONFIG_INLINE
#				define IXNPEMHCONFIG_INLINE 
#			endif
#		else
#			ifndef IXNPEMHCONFIG_INLINE
#				define IXNPEMHCONFIG_INLINE IX_OSAL_INLINE_EXTERN
#			endif
#		endif /* __wince*/

#else

#		ifndef IXNPEMHCONFIG_INLINE
#			define IXNPEMHCONFIG_INLINE IX_OSAL_INLINE_EXTERN
#		endif /* IXNPEMHCONFIG_INLINE */
#endif /* IXNPEMHSOLICITEDCBMGR_C */
 
typedef void (*IxNpeMhConfigIsr) (int); /**< ISR function pointer */


typedef struct
{
    IxOsalMutex mutex;          /**< mutex */
    UINT32 interruptId;     /**< interrupt ID */
    UINT32 virtualRegisterBase; /**< register virtual base address */
    UINT32 statusRegister;      /**< status register virtual address */
    UINT32 controlRegister;     /**< control register virtual address */
    UINT32 inFifoRegister;      /**< inFIFO register virutal address */
    UINT32 outFifoRegister;     /**< outFIFO register virtual address */
    IxNpeMhConfigIsr isr;   /**< isr routine for handling interrupt */
    BOOL oldInterruptState; /**< old interrupt state (TRUE => enabled) */
} IxNpeMhConfigNpeInfo;



/**< NPE register base address */
#define IX_NPEMH_NPE_BASE (IX_OSAL_IXP400_PERIPHERAL_PHYS_BASE)

#define IX_NPEMH_NPEA_OFFSET (0x6000) /**< NPE-A register base offset */
#define IX_NPEMH_NPEB_OFFSET (0x7000) /**< NPE-B register base offset */
#define IX_NPEMH_NPEC_OFFSET (0x8000) /**< NPE-C register base offset */

#define IX_NPEMH_NPESTAT_OFFSET (0x002C) /**< NPE status register offset */
#define IX_NPEMH_NPECTL_OFFSET  (0x0030) /**< NPE control register offset */
#define IX_NPEMH_NPEFIFO_OFFSET (0x0038) /**< NPE FIFO register offset */

/** NPE-A register base address */
#define IX_NPEMH_NPEA_BASE (IX_NPEMH_NPE_BASE + IX_NPEMH_NPEA_OFFSET)
/** NPE-B register base address */
#define IX_NPEMH_NPEB_BASE (IX_NPEMH_NPE_BASE + IX_NPEMH_NPEB_OFFSET)
/** NPE-C register base address */
#define IX_NPEMH_NPEC_BASE (IX_NPEMH_NPE_BASE + IX_NPEMH_NPEC_OFFSET)

/* NPE-A configuration */

/** NPE-A interrupt */
#define IX_NPEMH_NPEA_INT  (IX_OSAL_IXP400_NPEA_IRQ_LVL)
/** NPE-A FIFO register */
#define IX_NPEMH_NPEA_FIFO (IX_NPEMH_NPEA_BASE + IX_NPEMH_NPEFIFO_OFFSET)
/** NPE-A control register */
#define IX_NPEMH_NPEA_CTL  (IX_NPEMH_NPEA_BASE + IX_NPEMH_NPECTL_OFFSET)
/** NPE-A status register */
#define IX_NPEMH_NPEA_STAT (IX_NPEMH_NPEA_BASE + IX_NPEMH_NPESTAT_OFFSET)

/* NPE-B configuration */

/** NPE-B interrupt */
#define IX_NPEMH_NPEB_INT  (IX_OSAL_IXP400_NPEB_IRQ_LVL)
/** NPE-B FIFO register */
#define IX_NPEMH_NPEB_FIFO (IX_NPEMH_NPEB_BASE + IX_NPEMH_NPEFIFO_OFFSET)
/** NPE-B control register */
#define IX_NPEMH_NPEB_CTL  (IX_NPEMH_NPEB_BASE + IX_NPEMH_NPECTL_OFFSET)
/** NPE-B status register */
#define IX_NPEMH_NPEB_STAT (IX_NPEMH_NPEB_BASE + IX_NPEMH_NPESTAT_OFFSET)

/* NPE-C configuration */

/** NPE-C interrupt */
#define IX_NPEMH_NPEC_INT  (IX_OSAL_IXP400_NPEC_IRQ_LVL)
/** NPE-C FIFO register */
#define IX_NPEMH_NPEC_FIFO (IX_NPEMH_NPEC_BASE + IX_NPEMH_NPEFIFO_OFFSET)
/** NPE-C control register */
#define IX_NPEMH_NPEC_CTL  (IX_NPEMH_NPEC_BASE + IX_NPEMH_NPECTL_OFFSET)
/** NPE-C status register */
#define IX_NPEMH_NPEC_STAT (IX_NPEMH_NPEC_BASE + IX_NPEMH_NPESTAT_OFFSET)

/* NPE control register bit definitions */
#define IX_NPEMH_NPE_CTL_OFE   (1 << 16) /**< OutFifoEnable */
#define IX_NPEMH_NPE_CTL_IFE   (1 << 17) /**< InFifoEnable */
#define IX_NPEMH_NPE_CTL_OFEWE (1 << 24) /**< OutFifoEnableWriteEnable */
#define IX_NPEMH_NPE_CTL_IFEWE (1 << 25) /**< InFifoEnableWriteEnable */

/* NPE status register bit definitions */
#define IX_NPEMH_NPE_STAT_OFNE  (1 << 16) /**< OutFifoNotEmpty */
#define IX_NPEMH_NPE_STAT_IFNF  (1 << 17) /**< InFifoNotFull */
#define IX_NPEMH_NPE_STAT_OFNF  (1 << 18) /**< OutFifoNotFull */
#define IX_NPEMH_NPE_STAT_IFNE  (1 << 19) /**< InFifoNotEmpty */
#define IX_NPEMH_NPE_STAT_MBINT (1 << 20) /**< Mailbox interrupt */
#define IX_NPEMH_NPE_STAT_IFINT (1 << 21) /**< InFifo interrupt */
#define IX_NPEMH_NPE_STAT_OFINT (1 << 22) /**< OutFifo interrupt */
#define IX_NPEMH_NPE_STAT_WFINT (1 << 23) /**< WatchFifo interrupt */


extern IxNpeMhConfigNpeInfo ixNpeMhConfigNpeInfo[IX_NPEMH_NUM_NPES];




void ixNpeMhConfigInitialize (
    IxNpeMhNpeInterrupts npeInterrupts);


void ixNpeMhConfigUninit (void);


void ixNpeMhConfigIsrRegister (
    IxNpeMhNpeId npeId,
    IxNpeMhConfigIsr isr);


BOOL ixNpeMhConfigNpeInterruptEnable (
    IxNpeMhNpeId npeId);


BOOL ixNpeMhConfigNpeInterruptDisable (
    IxNpeMhNpeId npeId);


IxNpeMhMessageId ixNpeMhConfigMessageIdGet (
    IxNpeMhMessage message);


BOOL ixNpeMhConfigNpeIdIsValid (
    IxNpeMhNpeId npeId);


void ixNpeMhConfigLockGet (
    IxNpeMhNpeId npeId);


void ixNpeMhConfigLockRelease (
    IxNpeMhNpeId npeId);


IXNPEMHCONFIG_INLINE BOOL ixNpeMhConfigInFifoIsEmpty (
    IxNpeMhNpeId npeId);


IXNPEMHCONFIG_INLINE BOOL ixNpeMhConfigInFifoIsFull (
    IxNpeMhNpeId npeId);


IXNPEMHCONFIG_INLINE BOOL ixNpeMhConfigOutFifoIsEmpty (
    IxNpeMhNpeId npeId);


IXNPEMHCONFIG_INLINE BOOL ixNpeMhConfigOutFifoIsFull (
    IxNpeMhNpeId npeId);


IX_STATUS ixNpeMhConfigInFifoWrite (
    IxNpeMhNpeId npeId,
    IxNpeMhMessage message);


IX_STATUS ixNpeMhConfigOutFifoRead (
    IxNpeMhNpeId npeId,
    IxNpeMhMessage *message);


void ixNpeMhConfigShow (
    IxNpeMhNpeId npeId);


void ixNpeMhConfigShowReset (
    IxNpeMhNpeId npeId);

 

IXNPEMHCONFIG_INLINE
BOOL ixNpeMhConfigInFifoIsEmpty (
    IxNpeMhNpeId npeId)
{
    UINT32 ifne;
    volatile UINT32 *statusReg =
        (UINT32 *)ixNpeMhConfigNpeInfo[npeId].statusRegister;

    /* get the IFNE (InFifoNotEmpty) bit of the status register */
    IX_NPEMH_REGISTER_READ_BITS (statusReg, &ifne, IX_NPEMH_NPE_STAT_IFNE);

    /* if the IFNE status bit is unset then the inFIFO is empty */
    return (ifne == 0);
}


IXNPEMHCONFIG_INLINE
BOOL ixNpeMhConfigInFifoIsFull (
    IxNpeMhNpeId npeId)
{
    UINT32 ifnf;
    volatile UINT32 *statusReg =
        (UINT32 *)ixNpeMhConfigNpeInfo[npeId].statusRegister;

    /* get the IFNF (InFifoNotFull) bit of the status register */
    IX_NPEMH_REGISTER_READ_BITS (statusReg, &ifnf, IX_NPEMH_NPE_STAT_IFNF);

    /* if the IFNF status bit is unset then the inFIFO is full */
    return (ifnf == 0);
}


IXNPEMHCONFIG_INLINE
BOOL ixNpeMhConfigOutFifoIsEmpty (
    IxNpeMhNpeId npeId)
{
    UINT32 ofne;
    volatile UINT32 *statusReg =
        (UINT32 *)ixNpeMhConfigNpeInfo[npeId].statusRegister;

    /* get the OFNE (OutFifoNotEmpty) bit of the status register */
    IX_NPEMH_REGISTER_READ_BITS (statusReg, &ofne, IX_NPEMH_NPE_STAT_OFNE);

    /* if the OFNE status bit is unset then the outFIFO is empty */
    return (ofne == 0);
}

IXNPEMHCONFIG_INLINE
BOOL ixNpeMhConfigOutFifoIsFull (
    IxNpeMhNpeId npeId)
{
    UINT32 ofnf;
    volatile UINT32 *statusReg =
        (UINT32 *)ixNpeMhConfigNpeInfo[npeId].statusRegister;

    /* get the OFNF (OutFifoNotFull) bit of the status register */
    IX_NPEMH_REGISTER_READ_BITS (statusReg, &ofnf, IX_NPEMH_NPE_STAT_OFNF);

    /* if the OFNF status bit is unset then the outFIFO is full */
    return (ofnf == 0);
}

#endif /* IXNPEMHCONFIG_P_H */

