




#ifndef IXATMDACC_H
#define IXATMDACC_H

#include "IxAtmTypes.h"


#define IX_ATMDACC_WARNING 2

#define IX_ATMDACC_BUSY 3

#define IX_ATMDACC_RESOURCES_STILL_ALLOCATED 4

#define IX_ATMDACC_DEFAULT_REPLENISH_COUNT 0


#define IX_ATMDACC_OAM_TX_VPI 0

#define IX_ATMDACC_OAM_TX_VCI 0


 /**
 * @ingroup IxAtmdAccAPI
 *
 * @def IX_ATMDACC_OAM_RX_PORT
 *
 * @brief The reserved dummy PORT used for all dedicated OAM
 * Rx connections. Note that this is not a real port but must
 * have a value that lies within the valid range of port values.
 */
#define IX_ATMDACC_OAM_RX_PORT IX_UTOPIA_PORT_0

 /**
 * @ingroup IxAtmdAccAPI
 *
 * @def IX_ATMDACC_OAM_RX_VPI
 *
 * @brief The reserved value value used for the dedicated OAM
 * Rx connection. This value should be chosen so that it does not
 * coencide with the VPI value used in an AAL0/AAL5 connection.
 * Any attempt to connect a service type other than OAM on this VPI will fail.
 */
#define IX_ATMDACC_OAM_RX_VPI 0

#define IX_ATMDACC_OAM_RX_VCI 0



typedef enum
{
    IX_ATMDACC_AAL0_VALID = 0,    /**< aal0 pdu */
    IX_ATMDACC_OAM_VALID,         /**< OAM pdu */
    IX_ATMDACC_AAL2_VALID,        /**< aal2 pdu @b reserved for future use */
    IX_ATMDACC_AAL5_VALID,        /**< aal5 pdu complete and trailer is valid */
    IX_ATMDACC_AAL5_PARTIAL,      /**< aal5 pdu not complete, trailer is missing */
    IX_ATMDACC_AAL5_CRC_ERROR,    /**< aal5 pdu not complete, crc error/length error */
    IX_ATMDACC_MBUF_RETURN        /**< empty buffer returned to the user */
} IxAtmdAccPduStatus;


typedef enum
{
    IX_ATMDACC_AAL5,                /**< ITU-T AAL5 */
    IX_ATMDACC_AAL2,                /**< ITU-T AAL2 @b reserved for future use */
    IX_ATMDACC_AAL0_48,             /**< AAL0 48 byte payloads (cell header is added by NPE)*/
    IX_ATMDACC_AAL0_52,             /**< AAL0 52 byte cell data (HEC is added by NPE) */
    IX_ATMDACC_OAM,                 /**< OAM cell transport service (HEC is added by NPE)*/
    IX_ATMDACC_MAX_SERVICE_TYPE     /**< not a service, used for parameter validation */
} IxAtmdAccAalType;

typedef enum
{
    IX_ATMDACC_CLP_NOT_SET = 0,     /**< CLP indication is not set */
    IX_ATMDACC_CLP_SET = 1     /**< CLP indication is set */
} IxAtmdAccClpStatus;

typedef unsigned int IxAtmdAccUserId;


typedef void (*IxAtmdAccRxVcRxCallback) (IxAtmLogicalPort port,
                       IxAtmdAccUserId userId,
                       IxAtmdAccPduStatus status,
                       IxAtmdAccClpStatus clp,
                       IX_OSAL_MBUF * mbufPtr);

typedef void (*IxAtmdAccRxVcFreeLowCallback) (IxAtmdAccUserId userId);


typedef void (*IxAtmdAccTxVcBufferReturnCallback) (IxAtmdAccUserId userId,
                        IX_OSAL_MBUF * mbufPtr);


PUBLIC IX_STATUS ixAtmdAccInit (void);

PUBLIC void
ixAtmdAccShow (void);

PUBLIC void
ixAtmdAccStatsShow (void);

PUBLIC void
ixAtmdAccStatsReset (void);


PUBLIC IX_STATUS ixAtmdAccRxVcConnect (IxAtmLogicalPort port,
                      unsigned int vpi,
                      unsigned int vci,
                      IxAtmdAccAalType aalServiceType,
                      IxAtmRxQueueId rxQueueId,
                      IxAtmdAccUserId userCallbackId,
                      IxAtmdAccRxVcRxCallback rxCallback,
                      unsigned int minimumReplenishCount,
                      IxAtmConnId * connIdPtr,
                      IxAtmNpeRxVcId * npeVcIdPtr );

PUBLIC IX_STATUS ixAtmdAccRxVcFreeReplenish (IxAtmConnId connId,
                        IX_OSAL_MBUF * mbufPtr);

PUBLIC IX_STATUS ixAtmdAccRxVcFreeLowCallbackRegister (IxAtmConnId connId,
    unsigned int numberOfMbufs,
    IxAtmdAccRxVcFreeLowCallback callback);

PUBLIC IX_STATUS ixAtmdAccRxVcFreeEntriesQuery (IxAtmConnId connId,
                         unsigned int *numberOfMbufsPtr);

PUBLIC IX_STATUS ixAtmdAccRxVcEnable (IxAtmConnId connId);

PUBLIC IX_STATUS ixAtmdAccRxVcDisable (IxAtmConnId connId);

PUBLIC IX_STATUS ixAtmdAccRxVcTryDisconnect (IxAtmConnId connId);


PUBLIC IX_STATUS ixAtmdAccTxVcConnect (IxAtmLogicalPort port,
                      unsigned int vpi,
                      unsigned int vci,
                      IxAtmdAccAalType aalServiceType,
                      IxAtmdAccUserId userId,
                      IxAtmdAccTxVcBufferReturnCallback bufferFreeCallback,
                      IxAtmConnId * connIdPtr);

PUBLIC IX_STATUS ixAtmdAccTxVcPduSubmit (IxAtmConnId connId,
                    IX_OSAL_MBUF * mbufPtr,
                    IxAtmdAccClpStatus clp,
                    unsigned int numberOfCells);

PUBLIC IX_STATUS ixAtmdAccTxVcTryDisconnect (IxAtmConnId connId);

#endif /* IXATMDACC_H */



