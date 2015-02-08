


#ifndef IXDMAACC_H
#define IXDMAACC_H

#include "IxOsal.h"
#include "IxNpeDl.h"

typedef enum
{
    IX_DMA_SUCCESS = IX_SUCCESS,  /**< DMA Transfer Success */
    IX_DMA_FAIL = IX_FAIL,        /**< DMA Transfer Fail */
    IX_DMA_INVALID_TRANSFER_WIDTH, /**< Invalid transfer width */
    IX_DMA_INVALID_TRANSFER_LENGTH, /**< Invalid transfer length */
    IX_DMA_INVALID_TRANSFER_MODE, /**< Invalid transfer mode */
    IX_DMA_INVALID_ADDRESS_MODE, /**< Invalid address mode */
    IX_DMA_REQUEST_FIFO_FULL  /**< DMA request queue is full */
} IxDmaReturnStatus;

typedef enum
{
    IX_DMA_COPY_CLEAR = 0,      /**< copy and clear source*/
    IX_DMA_COPY,                /**< copy */
    IX_DMA_COPY_BYTE_SWAP,      /**< copy and byte swap (endian) */
    IX_DMA_COPY_REVERSE,        /**< copy and reverse */
    IX_DMA_TRANSFER_MODE_INVALID /**< Invalid transfer mode */
} IxDmaTransferMode;

typedef enum
{
    IX_DMA_INC_SRC_INC_DST = 0, /**< Incremental source address to incremental destination address */
    IX_DMA_INC_SRC_FIX_DST,     /**< Incremental source address to incremental destination address */
    IX_DMA_FIX_SRC_INC_DST,     /**< Incremental source address to incremental destination address */
    IX_DMA_FIX_SRC_FIX_DST,     /**< Incremental source address to incremental destination address */
    IX_DMA_ADDRESSING_MODE_INVALID /**< Invalid Addressing Mode */
} IxDmaAddressingMode;

typedef enum
{
    IX_DMA_32_SRC_32_DST = 0,  /**< 32-bit src to 32-bit dst */
    IX_DMA_32_SRC_16_DST,      /**< 32-bit src to 16-bit dst */
    IX_DMA_32_SRC_8_DST,       /**< 32-bit src to 8-bit dst */
    IX_DMA_16_SRC_32_DST,      /**< 16-bit src to 32-bit dst */
    IX_DMA_16_SRC_16_DST,      /**< 16-bit src to 16-bit dst */
    IX_DMA_16_SRC_8_DST,       /**< 16-bit src to 8-bit dst */
    IX_DMA_8_SRC_32_DST,       /**< 8-bit src to 32-bit dst */
    IX_DMA_8_SRC_16_DST,       /**< 8-bit src to 16-bit dst */
    IX_DMA_8_SRC_8_DST,        /**< 8-bit src to 8-bit dst */
    IX_DMA_8_SRC_BURST_DST,    /**< 8-bit src to burst dst - Not supported for fixed destination address */
    IX_DMA_16_SRC_BURST_DST,   /**< 16-bit src to burst dst - Not supported for fixed destination address */
    IX_DMA_32_SRC_BURST_DST,   /**< 32-bit src to burst dst - Not supported for fixed destination address */
    IX_DMA_BURST_SRC_8_DST,    /**< burst src to 8-bit dst  - Not supported for fixed source address */
    IX_DMA_BURST_SRC_16_DST,   /**< burst src to 16-bit dst - Not supported for fixed source address */
    IX_DMA_BURST_SRC_32_DST,   /**< burst src to 32-bit dst - Not supported for fixed source address*/
    IX_DMA_BURST_SRC_BURST_DST, /**< burst src to burst dst  - Not supported for fixed source and destination address
*/
    IX_DMA_TRANSFER_WIDTH_INVALID /**< Invalid transfer width */
} IxDmaTransferWidth;

typedef enum
{
    IX_DMA_NPEID_NPEA = 0, /**< Identifies NPE A */
    IX_DMA_NPEID_NPEB,     /**< Identifies NPE B */
    IX_DMA_NPEID_NPEC,     /**< Identifies NPE C */
    IX_DMA_NPEID_MAX       /**< Total Number of NPEs */
} IxDmaNpeId;
/* @} */

typedef UINT32 IxDmaAccRequestId;

#define IX_DMA_REQUEST_FULL 16

typedef void (*IxDmaAccDmaCompleteCallback) (IxDmaReturnStatus status);

PUBLIC IX_STATUS
ixDmaAccInit(IxNpeDlNpeId npeId);

PUBLIC IxDmaReturnStatus
ixDmaAccDmaTransfer(
    IxDmaAccDmaCompleteCallback callback,
    UINT32 SourceAddr,
    UINT32 DestinationAddr,
    UINT16 TransferLength,
    IxDmaTransferMode TransferMode,
    IxDmaAddressingMode AddressingMode,
    IxDmaTransferWidth TransferWidth);
PUBLIC IX_STATUS
ixDmaAccShow(void);

#endif /* IXDMAACC_H */

