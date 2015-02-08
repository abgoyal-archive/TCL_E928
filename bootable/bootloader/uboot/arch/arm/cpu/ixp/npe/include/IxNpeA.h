
#ifndef __doxygen_HIDE  /* This file is not part of the API */



#ifndef IX_NPE_A_H
#define IX_NPE_A_H

#include "IxQMgr.h"
#include "IxOsal.h"
#include "IxQueueAssignments.h"

/* General Message Ids */

/* ATM Message Ids */

#define IX_NPE_A_MSSG_ATM_UTOPIA_CONFIG_WRITE       0x20

#define IX_NPE_A_MSSG_ATM_UTOPIA_CONFIG_LOAD        0x21

#define IX_NPE_A_MSSG_ATM_UTOPIA_STATUS_UPLOAD      0x22

#define IX_NPE_A_MSSG_ATM_UTOPIA_STATUS_READ        0x23

#define IX_NPE_A_MSSG_ATM_TX_ENABLE                 0x25

 /**
 * @def IX_NPE_A_MSSG_ATM_TX_DISABLE
 *
 * @brief ATM Message ID command triggers the NPE to disable processing on
 * this port
 *
 * This command will be ignored for a port already disabled
 */
#define IX_NPE_A_MSSG_ATM_TX_DISABLE                0x26

#define IX_NPE_A_MSSG_ATM_RX_ENABLE                 0x27

#define IX_NPE_A_MSSG_ATM_RX_DISABLE                0x28

#define IX_NPE_A_MSSG_ATM_STATUS_READ               0x29


#define IX_NPE_A_MSSG_HSS_PORT_CONFIG_WRITE         0x40

#define IX_NPE_A_MSSG_HSS_PORT_CONFIG_LOAD          0x41

#define IX_NPE_A_MSSG_HSS_PORT_ERROR_READ           0x42

#define IX_NPE_A_MSSG_HSS_CHAN_FLOW_ENABLE          0x43

#define IX_NPE_A_MSSG_HSS_CHAN_FLOW_DISABLE         0x44

#define IX_NPE_A_MSSG_HSS_CHAN_IDLE_PATTERN_WRITE   0x45

#define IX_NPE_A_MSSG_HSS_CHAN_NUM_CHANS_WRITE      0x46

#define IX_NPE_A_MSSG_HSS_CHAN_RX_BUF_ADDR_WRITE    0x47

#define IX_NPE_A_MSSG_HSS_CHAN_RX_BUF_CFG_WRITE     0x48

#define IX_NPE_A_MSSG_HSS_CHAN_TX_BLK_CFG_WRITE     0x49

#define IX_NPE_A_MSSG_HSS_CHAN_TX_BUF_ADDR_WRITE    0x4A

#define IX_NPE_A_MSSG_HSS_CHAN_TX_BUF_SIZE_WRITE    0x4B

#define IX_NPE_A_MSSG_HSS_PKT_PIPE_FLOW_ENABLE      0x50

#define IX_NPE_A_MSSG_HSS_PKT_PIPE_FLOW_DISABLE     0x51

#define IX_NPE_A_MSSG_HSS_PKT_NUM_PIPES_WRITE       0x52

#define IX_NPE_A_MSSG_HSS_PKT_PIPE_FIFO_SIZEW_WRITE 0x53

#define IX_NPE_A_MSSG_HSS_PKT_PIPE_HDLC_CFG_WRITE   0x54

#define IX_NPE_A_MSSG_HSS_PKT_PIPE_IDLE_PATTERN_WRITE 0x55

#define IX_NPE_A_MSSG_HSS_PKT_PIPE_RX_SIZE_WRITE    0x56

#define IX_NPE_A_MSSG_HSS_PKT_PIPE_MODE_WRITE       0x57



/* Queue Entry Masks */


#define IX_NPE_A_RXDESCRIPTOR_STATUS_OFFSET          0

#define IX_NPE_A_RXDESCRIPTOR_VCID_OFFSET            1

#define IX_NPE_A_RXDESCRIPTOR_CURRMBUFSIZE_OFFSET    2

#define IX_NPE_A_RXDESCRIPTOR_ATMHEADER_OFFSET       4

#define IX_NPE_A_RXDESCRIPTOR_CURRMBUFLEN_OFFSET    12

#define IX_NPE_A_RXDESCRIPTOR_TIMELIMIT_OFFSET        14

#define IX_NPE_A_RXDESCRIPTOR_PCURRMBUFF_OFFSET     20

#define IX_NPE_A_RXDESCRIPTOR_PCURRMBUFDATA_OFFSET  24

#define IX_NPE_A_RXDESCRIPTOR_PNEXTMBUF_OFFSET      28

#define IX_NPE_A_RXDESCRIPTOR_TOTALLENGTH_OFFSET    32

#define IX_NPE_A_RXDESCRIPTOR_AAL5CRCRESIDUE_OFFSET 36

#define IX_NPE_A_RXDESCRIPTOR_SIZE                  40

#define IX_NPE_A_TXDESCRIPTOR_PORT_OFFSET            0

#define IX_NPE_A_TXDESCRIPTOR_RSVD_OFFSET            1

#define IX_NPE_A_TXDESCRIPTOR_CURRMBUFLEN_OFFSET     2

#define IX_NPE_A_TXDESCRIPTOR_ATMHEADER_OFFSET       4

#define IX_NPE_A_TXDESCRIPTOR_PCURRMBUFF_OFFSET      8

#define IX_NPE_A_TXDESCRIPTOR_PCURRMBUFDATA_OFFSET  12

#define IX_NPE_A_TXDESCRIPTOR_PNEXTMBUF_OFFSET      16

#define IX_NPE_A_TXDESCRIPTOR_TOTALLENGTH_OFFSET    20

#define IX_NPE_A_TXDESCRIPTOR_AAL5CRCRESIDUE_OFFSET 24

#define IX_NPE_A_TXDESCRIPTOR_SIZE                  28

#define IX_NPE_A_CHAIN_DESC_COUNT_MAX            256


/** Mask to acess GFC */
#define GFC_MASK        0xf0000000

/** return GFC from ATM cell header */
#define IX_NPE_A_ATMCELLHEADER_GFC_GET( header ) \
(((header) & GFC_MASK) >> 28)

/** set GFC into ATM cell header */
#define IX_NPE_A_ATMCELLHEADER_GFC_SET( header,gfc ) \
do { \
    (header) &= ~GFC_MASK; \
    (header) |= (((gfc) << 28) & GFC_MASK); \
} while(0)

/** Mask to acess VPI */
#define VPI_MASK        0x0ff00000

/** return VPI from ATM cell header */
#define IX_NPE_A_ATMCELLHEADER_VPI_GET( header ) \
(((header) & VPI_MASK) >> 20)

/** set VPI into ATM cell header */
#define IX_NPE_A_ATMCELLHEADER_VPI_SET( header, vpi ) \
do { \
    (header) &= ~VPI_MASK; \
    (header) |= (((vpi) << 20) & VPI_MASK); \
} while(0)

/** Mask to acess VCI */
#define VCI_MASK        0x000ffff0

/** return VCI from ATM cell header */
#define IX_NPE_A_ATMCELLHEADER_VCI_GET( header ) \
(((header) & VCI_MASK) >> 4)

/** set VCI into ATM cell header */
#define IX_NPE_A_ATMCELLHEADER_VCI_SET( header, vci ) \
do { \
    (header) &= ~VCI_MASK; \
    (header) |= (((vci) << 4) & VCI_MASK); \
} while(0)

/** Mask to acess PTI */
#define PTI_MASK        0x0000000e

/** return PTI from ATM cell header */
#define IX_NPE_A_ATMCELLHEADER_PTI_GET( header ) \
(((header) & PTI_MASK) >> 1)

/** set PTI into ATM cell header */
#define IX_NPE_A_ATMCELLHEADER_PTI_SET( header, pti ) \
do { \
    (header) &= ~PTI_MASK; \
    (header) |= (((pti) << 1) & PTI_MASK); \
} while(0)

/** Mask to acess CLP */
#define CLP_MASK        0x00000001

/** return CLP from ATM cell header */
#define IX_NPE_A_ATMCELLHEADER_CLP_GET( header ) \
((header) & CLP_MASK)

/** set CLP into ATM cell header */
#define IX_NPE_A_ATMCELLHEADER_CLP_SET( header, clp ) \
do { \
    (header) &= ~CLP_MASK; \
    (header) |= ((clp) & CLP_MASK); \
} while(0)



/** Mask to acess the rxBitField status */
#define STATUS_MASK     0x80000000

/** return the rxBitField status */
#define IX_NPE_A_RXBITFIELD_STATUS_GET( rxbitfield ) \
(((rxbitfield) & STATUS_MASK) >> 31)

/** set the rxBitField status */
#define IX_NPE_A_RXBITFIELD_STATUS_SET( rxbitfield, status ) \
do { \
    (rxbitfield) &= ~STATUS_MASK; \
    (rxbitfield) |= (((status) << 31) & STATUS_MASK); \
} while(0)

/** Mask to acess the rxBitField port */
#define PORT_MASK       0x7f000000

/** return the rxBitField port */
#define IX_NPE_A_RXBITFIELD_PORT_GET( rxbitfield ) \
(((rxbitfield) & PORT_MASK) >> 24)

/** set the rxBitField port */
#define IX_NPE_A_RXBITFIELD_PORT_SET( rxbitfield, port ) \
do { \
    (rxbitfield) &= ~PORT_MASK; \
    (rxbitfield) |= (((port) << 24) & PORT_MASK); \
} while(0)

/** Mask to acess the rxBitField vcId */
#define VCID_MASK       0x00ff0000

/** return the rxBitField vcId */
#define IX_NPE_A_RXBITFIELD_VCID_GET( rxbitfield ) \
(((rxbitfield) & VCID_MASK) >> 16)

/** set the rxBitField vcId */
#define IX_NPE_A_RXBITFIELD_VCID_SET( rxbitfield, vcid ) \
do { \
    (rxbitfield) &= ~VCID_MASK; \
    (rxbitfield) |= (((vcid) << 16) & VCID_MASK); \
} while(0)

/** Mask to acess the rxBitField mbuf size */
#define CURRMBUFSIZE_MASK       0x0000ffff

/** return the rxBitField mbuf size */
#define IX_NPE_A_RXBITFIELD_CURRMBUFSIZE_GET( rxbitfield ) \
((rxbitfield) & CURRMBUFSIZE_MASK)

/** set the rxBitField mbuf size */
#define IX_NPE_A_RXBITFIELD_CURRMBUFSIZE_SET( rxbitfield, currmbufsize ) \
do { \
    (rxbitfield) &= ~CURRMBUFSIZE_MASK; \
    (rxbitfield) |= ((currmbufsize) & CURRMBUFSIZE_MASK); \
} while(0)



typedef struct
{
    UINT8 port;				/**< Tx Port number */
    UINT8 aalType; 			/**< AAL Type */
    UINT16 currMbufLen;			/**< mbuf length */
    UINT32 atmCellHeader;		/**< ATM cell header */
    IX_OSAL_MBUF *pCurrMbuf;	        /**< pointer to mbuf */
    unsigned char *pCurrMbufData;	/**< Pointer to mbuf->dat */
    IX_OSAL_MBUF *pNextMbuf;		/**< Pointer to next mbuf */
    UINT32  totalLen;			/**< Total Length */
    UINT32  aal5CrcResidue;		/**< AAL5 CRC Residue */
} IxNpeA_TxAtmVc;





typedef struct
{
    UINT32  rxBitField;			/**< Recieved bit field */
    UINT32  atmCellHeader;		/**< ATM Cell Header */
    UINT32  rsvdWord0;                  /**< Reserved field */
    UINT16  currMbufLen;		/**< Mbuf Length */
    UINT8   timeLimit; 			/**< Payload Reassembly timeLimit (used for aal0_xx only) */
    UINT8   rsvdByte0;                  /**< Reserved field */ 
    UINT32  rsvdWord1;   		/**< Reserved field */
    IX_OSAL_MBUF *pCurrMbuf;		/**< Pointer to current mbuf */
    unsigned char *pCurrMbufData;	/**< Pointer to current mbuf->data */
    IX_OSAL_MBUF *pNextMbuf;		/**< Pointer to next mbuf */
    UINT32  totalLen;			/**< Total Length */
    UINT32  aal5CrcResidue;		/**< AAL5 CRC Residue */
} IxNpeA_RxAtmVc;


typedef enum
{
    IX_NPE_A_AAL_TYPE_INVALID = 0,	/**< Invalid AAL type */
    IX_NPE_A_AAL_TYPE_0_48    = 0x1,	/**< AAL0 - 48 byte */
    IX_NPE_A_AAL_TYPE_0_52    = 0x2,	/**< AAL0 - 52 byte */
    IX_NPE_A_AAL_TYPE_5       = 0x5,	/**< AAL5 */
    IX_NPE_A_AAL_TYPE_OAM     = 0xF	/**< OAM */
} IxNpeA_AalType;

typedef enum
{
    IX_NPE_A_52_BYTE_PAYLOAD = 0,	/**< 52 byte payload */
    IX_NPE_A_48_BYTE_PAYLOAD		/**< 48 byte payload */
} IxNpeA_PayloadFormat;

typedef struct
{
    UINT8   status;		/**< Status of the packet passed to the client */
    UINT8   errorCount;		/**< Number of errors */
    UINT8   chainCount;		/**< Mbuf chain count e.g. 0 - No mbuf chain */
    UINT8   rsvdByte0;		/**< Reserved byte to make the descriptor word align */

    UINT16  packetLength;	/**< Packet Length */
    UINT16  rsvdShort0;		/**< Reserved short to make the descriptor a word align */

    IX_OSAL_MBUF *pRootMbuf;	/**< Pointer to Root mbuf */
    IX_OSAL_MBUF *pNextMbuf;	/**< Pointer to next mbuf */
    UINT8   *pMbufData;		/**< Pointer to the current mbuf->data */
    UINT32  mbufLength;		/**< Current mbuf length */

} IxNpeA_NpePacketDescriptor;


#endif

#endif /* __doxygen_HIDE */
