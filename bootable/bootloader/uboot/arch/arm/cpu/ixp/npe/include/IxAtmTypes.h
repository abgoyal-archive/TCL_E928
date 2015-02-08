


#ifndef IXATMTYPES_H
#define IXATMTYPES_H

#include "IxNpeA.h"

typedef enum
{
    IX_UTOPIA_PORT_0 = 0,  /**< Port 0 */
#ifdef IX_NPE_MPHYMULTIPORT
    IX_UTOPIA_PORT_1,      /**< Port 1 */
    IX_UTOPIA_PORT_2,      /**< Port 2 */
    IX_UTOPIA_PORT_3,      /**< Port 3 */
    IX_UTOPIA_PORT_4,      /**< Port 4 */
    IX_UTOPIA_PORT_5,      /**< Port 5 */
    IX_UTOPIA_PORT_6,      /**< Port 6 */
    IX_UTOPIA_PORT_7,      /**< Port 7 */
    IX_UTOPIA_PORT_8,      /**< Port 8 */
    IX_UTOPIA_PORT_9,      /**< Port 9 */
    IX_UTOPIA_PORT_10,     /**< Port 10 */
    IX_UTOPIA_PORT_11,     /**< Port 11 */
#endif /* IX_NPE_MPHY */
    IX_UTOPIA_MAX_PORTS    /**< Not a port - just a definition for the
                           * maximum possible ports
                           */
} IxAtmLogicalPort;

#define IX_ATM_CELL_PAYLOAD_SIZE             (48)

#define IX_ATM_CELL_SIZE                     (53)

#define IX_ATM_CELL_SIZE_NO_HEC              (IX_ATM_CELL_SIZE - 1)

#define IX_ATM_OAM_CELL_SIZE_NO_HEC          IX_ATM_CELL_SIZE_NO_HEC

#define IX_ATM_AAL0_48_CELL_PAYLOAD_SIZE     IX_ATM_CELL_PAYLOAD_SIZE

#define IX_ATM_AAL5_CELL_PAYLOAD_SIZE        IX_ATM_CELL_PAYLOAD_SIZE

#define IX_ATM_AAL0_52_CELL_SIZE_NO_HEC      IX_ATM_CELL_SIZE_NO_HEC


#define IX_ATM_MAX_VPI 255

#define IX_ATM_MAX_VCI 65535

 /**
 * @def IX_ATM_MAX_NUM_AAL_VCS
 * @brief Maximum number of active AAL5/AAL0 VCs in the system
 */
#define IX_ATM_MAX_NUM_AAL_VCS 32

#define IX_ATM_MAX_NUM_VC IX_ATM_MAX_NUM_AAL_VCS



#define IX_ATM_MAX_NUM_OAM_TX_VCS IX_UTOPIA_MAX_PORTS

#define IX_ATM_MAX_NUM_OAM_RX_VCS 1

#define IX_ATM_MAX_NUM_AAL_OAM_TX_VCS (IX_ATM_MAX_NUM_AAL_VCS + IX_ATM_MAX_NUM_OAM_TX_VCS)

#define IX_ATM_MAX_NUM_AAL_OAM_RX_VCS (IX_ATM_MAX_NUM_AAL_VCS + IX_ATM_MAX_NUM_OAM_RX_VCS)

#define IX_ATM_IDLE_CELLS_CONNID 0


#define IX_ATM_CELL_HEADER_VCI_GET(cellHeader) \
    (((cellHeader) >> 4) & IX_OAM_VCI_BITS_MASK);

#define IX_ATM_CELL_HEADER_VPI_GET(cellHeader) \
    (((cellHeader) >> 20) & IX_OAM_VPI_BITS_MASK);

#define IX_ATM_CELL_HEADER_PTI_GET(cellHeader) \
    ((cellHeader) >> 1) & IX_OAM_PTI_BITS_MASK;

typedef unsigned int IxAtmCellHeader;


typedef enum
{
    IX_ATM_CBR,    /**< Constant Bit Rate */
    IX_ATM_RTVBR,  /**< Real Time Variable Bit Rate */
    IX_ATM_VBR,    /**< Variable Bit Rate */
    IX_ATM_UBR,    /**< Unspecified Bit Rate */
    IX_ATM_ABR     /**< Available Bit Rate (not supported) */

} IxAtmServiceCategory;

typedef enum
{
    IX_ATM_RX_A = 0,      /**< RX queue A */
    IX_ATM_RX_B,          /**< RX queue B */
    IX_ATM_MAX_RX_STREAMS /**< Maximum number of RX streams */
} IxAtmRxQueueId;

typedef struct
{
    IxAtmServiceCategory atmService; /**< ATM service category */
    unsigned pcr;   /**< Peak Cell Rate - cells per second */
    unsigned cdvt;  /**< Cell Delay Variation Tolerance - in nanoseconds */
    unsigned scr;   /**< Sustained Cell Rate - cells per second */
    unsigned mbs;   /**< Max Burst Size - cells */
    unsigned mcr;   /**< Minimum Cell Rate - cells per second */
    unsigned mfs;   /**< Max Frame Size - cells */
} IxAtmTrafficDescriptor;

typedef unsigned int IxAtmConnId;

typedef int IxAtmSchedulerVcId;

typedef unsigned int IxAtmNpeRxVcId;

typedef struct
{
    IxAtmConnId connId; /**< connection Id
                 *
                 * Identifier of VC from which cells are to be transmitted.
                 * When this valus is IX_ATM_IDLE_CELLS_CONNID, this indicates
                 * that the system should transmit the specified number
                 * of idle cells. Unknown connIds result in the transmission
                 * idle cells.
                 */
    unsigned int numberOfCells; /**< number of cells to transmit
                 *
                 * The number of contiguous cells to schedule from this VC
                 * at this point. The valid range is from 1 to
                 * @a IX_ATM_SCHEDULETABLE_MAXCELLS_PER_ENTRY. This
                 * number can swap over mbufs and pdus. OverSchduling results
                 * in the transmission of idle cells.
                 */
} IxAtmScheduleTableEntry;

typedef struct
{
    unsigned tableSize;      /**< Number of entries
                              *
                              * Indicates the total number of
                              *   entries in the table.
                              */
    unsigned totalCellSlots; /**< Number of cells
                              *
                              * Indicates the total number of ATM
                              *   cells which are scheduled by all the
                              *   entries in the table.
                              */
    IxAtmScheduleTableEntry *table; /**< Pointer to schedule entries
                                     *
                                     * Pointer to an array
                                     *   containing tableSize entries
                                     */
} IxAtmScheduleTable;

#endif /* IXATMTYPES_H */



