
 

#ifndef IXHSSACC_H
#define IXHSSACC_H

#include "IxOsal.h"


#define IX_HSSACC_TSLOTS_PER_HSS_PORT 128

#define IX_HSSACC_PARAM_ERR 2

#define IX_HSSACC_RESOURCE_ERR 3

#define IX_HSSACC_PKT_DISCONNECTING 4

#define IX_HSSACC_Q_WRITE_OVERFLOW 5

#define IX_HSSACC_NO_ERROR 0

#define IX_HSSACC_TX_FRM_SYNC_ERR 1

#define IX_HSSACC_TX_OVER_RUN_ERR 2

#define IX_HSSACC_CHANNELISED_SW_TX_ERR 3

#define IX_HSSACC_PACKETISED_SW_TX_ERR 4

#define IX_HSSACC_RX_FRM_SYNC_ERR 5

#define IX_HSSACC_RX_OVER_RUN_ERR 6

#define IX_HSSACC_CHANNELISED_SW_RX_ERR 7

#define IX_HSSACC_PACKETISED_SW_RX_ERR 8


#define IX_HSSACC_PKT_MIN_RX_MBUF_SIZE 64

typedef enum
{
    IX_HSSACC_HSS_PORT_0,   /**< HSS Port 0 */
    IX_HSSACC_HSS_PORT_1,   /**< HSS Port 1 */
    IX_HSSACC_HSS_PORT_MAX  /**< Delimiter for error checks */
} IxHssAccHssPort;

typedef enum
{
   IX_HSSACC_HDLC_PORT_0,   /**< HDLC Port 0 */
   IX_HSSACC_HDLC_PORT_1,   /**< HDLC Port 1 */
   IX_HSSACC_HDLC_PORT_2,   /**< HDLC Port 2 */
   IX_HSSACC_HDLC_PORT_3,   /**< HDLC Port 3 */
   IX_HSSACC_HDLC_PORT_MAX  /**< Delimiter for error checks */
} IxHssAccHdlcPort;

typedef enum
{
    IX_HSSACC_TDMMAP_UNASSIGNED,    /**< Unassigned */
    IX_HSSACC_TDMMAP_HDLC,          /**< HDLC - packetised */
    IX_HSSACC_TDMMAP_VOICE56K,      /**< Voice56K - channelised */
    IX_HSSACC_TDMMAP_VOICE64K,      /**< Voice64K - channelised */
    IX_HSSACC_TDMMAP_MAX            /**< Delimiter for error checks */
} IxHssAccTdmSlotUsage;

typedef enum
{
    IX_HSSACC_FRM_SYNC_ACTIVE_LOW,   /**< Frame sync is sampled low */
    IX_HSSACC_FRM_SYNC_ACTIVE_HIGH,  /**< sampled high */
    IX_HSSACC_FRM_SYNC_FALLINGEDGE,  /**< sampled on a falling edge */
    IX_HSSACC_FRM_SYNC_RISINGEDGE,   /**< sampled on a rising edge */
    IX_HSSACC_FRM_SYNC_TYPE_MAX      /**< Delimiter for error checks */
} IxHssAccFrmSyncType;

typedef enum
{
    IX_HSSACC_FRM_SYNC_INPUT,          /**< Frame sync is sampled as an input */
    IX_HSSACC_FRM_SYNC_INVALID_VALUE,  /**< 1 is not used */
    IX_HSSACC_FRM_SYNC_OUTPUT_FALLING, /**< Frame sync is an output generated 
					  off a falling clock edge */
    IX_HSSACC_FRM_SYNC_OUTPUT_RISING,  /**< Frame sync is an output generated 
					  off a rising clock edge */
    IX_HSSACC_FRM_SYNC_ENABLE_MAX      /**< Delimiter for error checks */
} IxHssAccFrmSyncEnable;

typedef enum
{
    IX_HSSACC_CLK_EDGE_FALLING,  /**< Clock sampled off a falling edge */
    IX_HSSACC_CLK_EDGE_RISING,   /**< Clock sampled off a rising edge */
    IX_HSSACC_CLK_EDGE_MAX       /**< Delimiter for error checks */
} IxHssAccClkEdge;

typedef enum
{
    IX_HSSACC_SYNC_CLK_DIR_INPUT,    /**< Clock is an input */
    IX_HSSACC_SYNC_CLK_DIR_OUTPUT,   /**< Clock is an output */
    IX_HSSACC_SYNC_CLK_DIR_MAX       /**< Delimiter for error checks */
} IxHssAccClkDir;

typedef enum
{
    IX_HSSACC_FRM_PULSE_ENABLED,     /**< Generate/Receive frame pulses */
    IX_HSSACC_FRM_PULSE_DISABLED,    /**< Disregard frame pulses */
    IX_HSSACC_FRM_PULSE_MAX          /**< Delimiter for error checks */
} IxHssAccFrmPulseUsage;

typedef enum
{
    IX_HSSACC_CLK_RATE,      /**< Data rate is at the configured clk speed */
    IX_HSSACC_HALF_CLK_RATE, /**< Data rate is half the configured clk speed */
    IX_HSSACC_DATA_RATE_MAX  /**< Delimiter for error checks */
} IxHssAccDataRate;

typedef enum
{
    IX_HSSACC_DATA_POLARITY_SAME,   /**< Don't invert data between NPE and 
				       HSS FIFOs */
    IX_HSSACC_DATA_POLARITY_INVERT, /**< Invert data between NPE and HSS 
				       FIFOs */
    IX_HSSACC_DATA_POLARITY_MAX     /**< Delimiter for error checks */
} IxHssAccDataPolarity;

typedef enum
{
    IX_HSSACC_LSB_ENDIAN,    /**< TX/RX Least Significant Bit first */
    IX_HSSACC_MSB_ENDIAN,    /**< TX/RX Most Significant Bit first */
    IX_HSSACC_ENDIAN_MAX     /**< Delimiter for the purposes of error checks */
} IxHssAccBitEndian;


typedef enum
{
    IX_HSSACC_TX_PINS_NORMAL,       /**< Normal mode */
    IX_HSSACC_TX_PINS_OPEN_DRAIN,   /**< Open Drain mode */
    IX_HSSACC_TX_PINS_MAX           /**< Delimiter for error checks */
} IxHssAccDrainMode;

typedef enum
{
    IX_HSSACC_SOF_FBIT,  /**< Framing bit transmitted and expected on rx */
    IX_HSSACC_SOF_DATA,  /**< Framing bit not transmitted nor expected on rx */
    IX_HSSACC_SOF_MAX    /**< Delimiter for error checks */
} IxHssAccSOFType;

typedef enum
{
    IX_HSSACC_DE_TRI_STATE,   /**< TRI-State the data pins */
    IX_HSSACC_DE_DATA,        /**< Push data out the data pins */
    IX_HSSACC_DE_MAX          /**< Delimiter for error checks */
} IxHssAccDataEnable;

typedef enum
{
    IX_HSSACC_TXSIG_LOW,        /**< Drive the data pins low */
    IX_HSSACC_TXSIG_HIGH,       /**< Drive the data pins high */
    IX_HSSACC_TXSIG_HIGH_IMP,   /**< Drive the data pins with high impedance */
    IX_HSSACC_TXSIG_MAX         /**< Delimiter for error checks */
} IxHssAccTxSigType;

typedef enum
{
    IX_HSSACC_FB_FIFO,        /**< Fbit is dictated in FIFO */
    IX_HSSACC_FB_HIGH_IMP,    /**< Fbit is high impedance */
    IX_HSSACC_FB_MAX          /**< Delimiter for error checks */
} IxHssAccFbType;

typedef enum
{
    IX_HSSACC_56KE_BIT_7_UNUSED,  /**< High bit is unused */
    IX_HSSACC_56KE_BIT_0_UNUSED,  /**< Low bit is unused */
    IX_HSSACC_56KE_MAX            /**< Delimiter for error checks */
} IxHssAcc56kEndianness;

typedef enum
{
    IX_HSSACC_56KS_32_8_DATA,  /**< 32/8 bit data */
    IX_HSSACC_56KS_56K_DATA,   /**< 56K data */
    IX_HSSACC_56KS_MAX         /**< Delimiter for error checks */
} IxHssAcc56kSel;


typedef enum
{
    IX_HSSACC_CLK_SPEED_512KHZ,     /**< 512KHz */
    IX_HSSACC_CLK_SPEED_1536KHZ,    /**< 1.536MHz */
    IX_HSSACC_CLK_SPEED_1544KHZ,    /**< 1.544MHz */
    IX_HSSACC_CLK_SPEED_2048KHZ,    /**< 2.048MHz */
    IX_HSSACC_CLK_SPEED_4096KHZ,    /**< 4.096MHz */
    IX_HSSACC_CLK_SPEED_8192KHZ,    /**< 8.192MHz */
    IX_HSSACC_CLK_SPEED_MAX      /**< Delimiter for error checking */
} IxHssAccClkSpeed;

typedef enum
{
    IX_HSSACC_PKT_OK,              /**< Error free.*/
    IX_HSSACC_STOP_SHUTDOWN_ERROR, /**< Errored due to stop or shutdown 
				      occurrance.*/
    IX_HSSACC_HDLC_ALN_ERROR,      /**< HDLC alignment error */
    IX_HSSACC_HDLC_FCS_ERROR,       /**< HDLC Frame Check Sum error.*/
    IX_HSSACC_RXFREE_Q_EMPTY_ERROR,       /**< RxFree Q became empty 
					     while receiving this packet.*/
    IX_HSSACC_HDLC_MAX_FRAME_SIZE_EXCEEDED,      /**< HDLC frame size 
						   received is greater than
						   max specified at connect.*/
    IX_HSSACC_HDLC_ABORT_ERROR,   /**< HDLC frame received is invalid due to an 
				   abort sequence received.*/
    IX_HSSACC_DISCONNECT_IN_PROGRESS     /**< Packet returned
					    because a disconnect is in progress */
} IxHssAccPktStatus;


typedef enum
{
    IX_HSSACC_PKT_16_BIT_CRC = 16,  /**< 16 bit CRC is being used */
    IX_HSSACC_PKT_32_BIT_CRC = 32   /**< 32 bit CRC is being used */
} IxHssAccPktCrcType;

typedef enum
{
    IX_HSSACC_HDLC_IDLE_ONES,    /**< idle tx/rx will be a succession of ones */
    IX_HSSACC_HDLC_IDLE_FLAGS    /**< idle tx/rx will be repeated flags */
} IxHssAccPktHdlcIdleType;

typedef struct
{
    IxHssAccFrmSyncType frmSyncType;     /**< frame sync pulse type (tx/rx) */
    IxHssAccFrmSyncEnable frmSyncIO;     /**< how the frame sync pulse is 
					    used (tx/rx) */
    IxHssAccClkEdge frmSyncClkEdge;      /**< frame sync clock edge type 
					    (tx/rx) */
    IxHssAccClkEdge dataClkEdge;         /**< data clock edge type (tx/rx) */
    IxHssAccClkDir clkDirection;         /**< clock direction (tx/rx) */
    IxHssAccFrmPulseUsage frmPulseUsage; /**< whether to use the frame sync 
					    pulse or not (tx/rx) */
    IxHssAccDataRate dataRate;           /**< data rate in relation to the 
					    clock (tx/rx) */
    IxHssAccDataPolarity dataPolarity;   /**< data polarity type (tx/rx) */
    IxHssAccBitEndian dataEndianness;    /**< data endianness (tx/rx) */
    IxHssAccDrainMode drainMode;         /**< tx pin open drain mode (tx) */
    IxHssAccSOFType fBitUsage;           /**< start of frame types (tx/rx) */
    IxHssAccDataEnable dataEnable;       /**< whether or not to drive the data 
					    pins (tx) */
    IxHssAccTxSigType voice56kType;      /**< how to drive the data pins for 
					    voice56k type (tx) */
    IxHssAccTxSigType unassignedType;    /**< how to drive the data pins for 
					    unassigned type (tx) */
    IxHssAccFbType fBitType;             /**< how to drive the Fbit (tx) */
    IxHssAcc56kEndianness voice56kEndian;/**< 56k data endianness when using 
					    the 56k type (tx) */
    IxHssAcc56kSel voice56kSel;          /**< 56k data transmission type when 
					    using the 56k type (tx) */
    unsigned frmOffset;                  /**< frame pulse offset in bits wrt 
					    the first timeslot (0-1023) (tx/rx) */
    unsigned maxFrmSize;                 /**< frame size in bits (1-1024) 
					    (tx/rx) */
} IxHssAccPortConfig;

typedef struct
{
    IxHssAccPortConfig txPortConfig; /**< HSS tx port configuration */
    IxHssAccPortConfig rxPortConfig; /**< HSS rx port configuration */
    unsigned numChannelised;         /**< The number of channelised 
					timeslots (0-32) */
    unsigned hssPktChannelCount;     /**< The number of packetised 
					clients (0 - 4) */
    UINT8 channelisedIdlePattern;    /**< The byte to be transmitted on 
					channelised service when there 
					is no client data to tx */
    BOOL loopback;                   /**< The HSS loopback state */
    unsigned packetizedIdlePattern;  /**< The data to be transmitted on 
					packetised service when there is 
					no client data to tx */
    IxHssAccClkSpeed clkSpeed;       /**< The HSS clock speed */
} IxHssAccConfigParams;

typedef struct
{
    BOOL hdlc56kMode;                    /**< 56kbps(TRUE)/64kbps(FALSE) HDLC */
    IxHssAcc56kEndianness hdlc56kEndian; /**< 56kbps data endianness 
					    - ignored if hdlc56kMode is FALSE*/
    BOOL hdlc56kUnusedBitPolarity0;      /**< The polarity '0'(TRUE)/'1'(FALSE) of the unused
					   bit while in 56kbps mode
					   - ignored if hdlc56kMode is FALSE*/
} IxHssAccHdlcMode;

typedef struct
{
    IxHssAccPktHdlcIdleType hdlcIdleType;   /**< What to transmit when a HDLC port is idle */
    IxHssAccBitEndian dataEndian;           /**< The HDLC data endianness */
    IxHssAccPktCrcType crcType;             /**< The CRC type to be used for this HDLC port */
} IxHssAccPktHdlcFraming;

typedef UINT32 IxHssAccPktUserId;


typedef void (*IxHssAccLastErrorCallback) (unsigned lastHssError, 
					   unsigned servicePort);

typedef void (*IxHssAccPktRxCallback) (IX_OSAL_MBUF *buffer, 
				       unsigned numHssErrs, 
				       IxHssAccPktStatus pktStatus, 
				       IxHssAccPktUserId rxUserId);

typedef void (*IxHssAccPktRxFreeLowCallback) (IxHssAccPktUserId rxFreeLowUserId);

typedef void (*IxHssAccPktTxDoneCallback) (IX_OSAL_MBUF *buffer, 
					   unsigned numHssErrs,
					   IxHssAccPktStatus pktStatus, 
					   IxHssAccPktUserId txDoneUserId);

typedef void (*IxHssAccChanRxCallback) (IxHssAccHssPort hssPortId,
					unsigned rxOffset, 
					unsigned txOffset, 
					unsigned numHssErrs);


PUBLIC IX_STATUS 
ixHssAccPortInit (IxHssAccHssPort hssPortId, 
		  IxHssAccConfigParams *configParams, 
		  IxHssAccTdmSlotUsage *tdmMap, 
		  IxHssAccLastErrorCallback lastHssErrorCallback);

PUBLIC IX_STATUS 
ixHssAccLastErrorRetrievalInitiate (IxHssAccHssPort hssPortId);


PUBLIC IX_STATUS 
ixHssAccInit (void);


PUBLIC IX_STATUS 
ixHssAccPktPortConnect (IxHssAccHssPort hssPortId, 
			IxHssAccHdlcPort hdlcPortId, 
			BOOL hdlcFraming, 
			IxHssAccHdlcMode hdlcMode,
			BOOL hdlcBitInvert,
			unsigned blockSizeInWords,
			UINT32 rawIdleBlockPattern,
			IxHssAccPktHdlcFraming hdlcTxFraming, 
			IxHssAccPktHdlcFraming hdlcRxFraming, 
			unsigned frmFlagStart, 
			IxHssAccPktRxCallback rxCallback,
			IxHssAccPktUserId rxUserId, 
			IxHssAccPktRxFreeLowCallback rxFreeLowCallback, 
			IxHssAccPktUserId rxFreeLowUserId,
			IxHssAccPktTxDoneCallback txDoneCallback,
			IxHssAccPktUserId txDoneUserId);

PUBLIC IX_STATUS 
ixHssAccPktPortEnable (IxHssAccHssPort hssPortId, 
		       IxHssAccHdlcPort hdlcPortId);

PUBLIC IX_STATUS 
ixHssAccPktPortDisable (IxHssAccHssPort hssPortId, 
			IxHssAccHdlcPort hdlcPortId);

PUBLIC IX_STATUS 
ixHssAccPktPortDisconnect (IxHssAccHssPort hssPortId, 
			   IxHssAccHdlcPort hdlcPortId);

PUBLIC BOOL 
ixHssAccPktPortIsDisconnectComplete (IxHssAccHssPort hssPortId, 
				     IxHssAccHdlcPort hdlcPortId);


PUBLIC IX_STATUS 
ixHssAccPktPortRxFreeReplenish (IxHssAccHssPort hssPortId, 
				IxHssAccHdlcPort hdlcPortId, 
				IX_OSAL_MBUF *buffer);

PUBLIC IX_STATUS 
ixHssAccPktPortTx (IxHssAccHssPort hssPortId, 
		   IxHssAccHdlcPort hdlcPortId, 
		   IX_OSAL_MBUF *buffer);

 
PUBLIC IX_STATUS 
ixHssAccChanConnect (IxHssAccHssPort hssPortId, 
		     unsigned bytesPerTSTrigger, 
		     UINT8 *rxCircular, 
		     unsigned numRxBytesPerTS, 
		     UINT32 *txPtrList, 
		     unsigned numTxPtrLists, 
		     unsigned numTxBytesPerBlk, 
		     IxHssAccChanRxCallback rxCallback);

PUBLIC IX_STATUS 
ixHssAccChanPortEnable (IxHssAccHssPort hssPortId);

PUBLIC IX_STATUS 
ixHssAccChanPortDisable (IxHssAccHssPort hssPortId);

PUBLIC IX_STATUS 
ixHssAccChanDisconnect (IxHssAccHssPort hssPortId);

PUBLIC IX_STATUS 
ixHssAccChanStatusQuery (IxHssAccHssPort hssPortId, 
			 BOOL *dataRecvd, 
			 unsigned *rxOffset, 
			 unsigned *txOffset, 
			 unsigned *numHssErrs);

PUBLIC void 
ixHssAccShow (void);

PUBLIC void 
ixHssAccStatsInit (void);

#endif /* IXHSSACC_H */

