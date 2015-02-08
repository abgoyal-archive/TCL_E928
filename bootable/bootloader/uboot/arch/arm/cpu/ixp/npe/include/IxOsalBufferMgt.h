

#ifndef IxOsalBufferMgt_H
#define IxOsalBufferMgt_H

#include "IxOsal.h"

#define IX_OSAL_MBUF_MAX_POOLS      32

#define IX_OSAL_MBUF_POOL_NAME_LEN  64





/* forward declaration of internal structure */
struct __IXP_BUF;

#ifndef IX_OSAL_ATTRIBUTE_ALIGN32
#define IX_OSAL_ATTRIBUTE_ALIGN32 __attribute__ ((aligned(32)))
#endif

/* release v1.4 backward compatible definitions */
struct __IX_MBUF
{
    struct __IXP_BUF *ix_next IX_OSAL_ATTRIBUTE_ALIGN32;
    struct __IXP_BUF *ix_nextPacket;
    UINT8 *ix_data;
    UINT32 ix_len;  
    unsigned char ix_type;
    unsigned char ix_flags;
    unsigned short ix_reserved;
    UINT32 ix_rsvd;
    UINT32 ix_PktLen; 
    void *ix_priv;     
};

struct __IX_CTRL
{
    UINT32 ix_reserved[2];        /**< Reserved field */
    UINT32 ix_signature;          /**< Field to indicate if buffers are allocated by the system */    
    UINT32 ix_allocated_len;      /**< Allocated buffer length */  
    UINT32 ix_allocated_data;     /**< Allocated buffer data pointer */  
    void *ix_pool;                /**< pointer to the buffer pool */
    struct __IXP_BUF *ix_chain;   /**< chaining */ 
    void *ix_osbuf_ptr;           /**< Storage for OS-specific buffer pointer */
};

struct __IX_NE_SHARED
{
    UINT32 reserved[8] IX_OSAL_ATTRIBUTE_ALIGN32;   /**< Reserved area for NPE Service-specific usage */
};


typedef struct __IXP_BUF
{
    struct __IX_MBUF ix_mbuf IX_OSAL_ATTRIBUTE_ALIGN32; /**< buffer header */
    struct __IX_CTRL ix_ctrl;                           /**< buffer management */
    struct __IX_NE_SHARED ix_ne;                        /**< Reserved area for NPE Service-specific usage*/
} IXP_BUF;



typedef IXP_BUF IX_OSAL_MBUF;


#define IX_OSAL_MBUF_NEXT_BUFFER_IN_PKT_PTR(m_blk_ptr)  \
        (m_blk_ptr)->ix_mbuf.ix_next


#define IX_OSAL_MBUF_NEXT_PKT_IN_CHAIN_PTR(m_blk_ptr)  \
        (m_blk_ptr)->ix_mbuf.ix_nextPacket


#define IX_OSAL_MBUF_MDATA(m_blk_ptr)       (m_blk_ptr)->ix_mbuf.ix_data

#define IX_OSAL_MBUF_MLEN(m_blk_ptr) \
    (m_blk_ptr)->ix_mbuf.ix_len

#define IX_OSAL_MBUF_MTYPE(m_blk_ptr) \
    (m_blk_ptr)->ix_mbuf.ix_type


#define IX_OSAL_MBUF_FLAGS(m_blk_ptr)       \
        (m_blk_ptr)->ix_mbuf.ix_flags


#define IX_OSAL_MBUF_NET_POOL(m_blk_ptr)	\
        (m_blk_ptr)->ix_ctrl.ix_pool



#define IX_OSAL_MBUF_PKT_LEN(m_blk_ptr) \
        (m_blk_ptr)->ix_mbuf.ix_PktLen




#define IX_OSAL_MBUF_PRIV(m_blk_ptr)        \
        (m_blk_ptr)->ix_mbuf.ix_priv



#define IX_OSAL_MBUF_SIGNATURE(m_blk_ptr)  \
        (m_blk_ptr)->ix_ctrl.ix_signature


#define IX_OSAL_MBUF_OSBUF_PTR(m_blk_ptr)  \
        (m_blk_ptr)->ix_ctrl.ix_osbuf_ptr


#define IX_OSAL_MBUF_ALLOCATED_BUFF_LEN(m_blk_ptr)  \
        (m_blk_ptr)->ix_ctrl.ix_allocated_len

#define IX_OSAL_MBUF_ALLOCATED_BUFF_DATA(m_blk_ptr)  \
        (m_blk_ptr)->ix_ctrl.ix_allocated_data



/* Name length */
#define IX_OSAL_MBUF_POOL_NAME_LEN  64



#define IX_OSAL_MBUF_POOL_FREE_COUNT(m_pool_ptr) \
                    ixOsalBuffPoolFreeCountGet(m_pool_ptr)

#define IX_OSAL_MBUF_POOL_SIZE_ALIGN(size)                 \
    ((((size) + (IX_OSAL_CACHE_LINE_SIZE - 1)) /      \
        IX_OSAL_CACHE_LINE_SIZE) *                  \
            IX_OSAL_CACHE_LINE_SIZE)

/* Don't use this directly, use macro */
PUBLIC UINT32 ixOsalBuffPoolMbufAreaSizeGet (int count);


#define IX_OSAL_MBUF_POOL_MBUF_AREA_SIZE_ALIGNED(count) \
        ixOsalBuffPoolMbufAreaSizeGet(count)


/* Don't use this directly, use macro */
PUBLIC UINT32 ixOsalBuffPoolDataAreaSizeGet (int count, int size);


#define IX_OSAL_MBUF_POOL_DATA_AREA_SIZE_ALIGNED(count, size) \
        ixOsalBuffPoolDataAreaSizeGet((count), (size))


#define IX_OSAL_MBUF_POOL_MBUF_AREA_ALLOC(count, memAreaSize) \
    IX_OSAL_CACHE_DMA_MALLOC((memAreaSize =                 \
        IX_OSAL_MBUF_POOL_MBUF_AREA_SIZE_ALIGNED(count)))

#define IX_OSAL_MBUF_POOL_DATA_AREA_ALLOC(count, size, memAreaSize) \
    IX_OSAL_CACHE_DMA_MALLOC((memAreaSize =                     \
        IX_OSAL_MBUF_POOL_DATA_AREA_SIZE_ALIGNED(count,size)))



#define IX_OSAL_MBUF_POOL_INIT(count, size, name) \
    ixOsalPoolInit((count), (size), (name))

#define IX_OSAL_MBUF_NO_ALLOC_POOL_INIT(bufPtr, dataPtr, count, size, name) \
    ixOsalNoAllocPoolInit( (bufPtr), (dataPtr), (count), (size), (name))

#define IX_OSAL_MBUF_POOL_GET(poolPtr) \
        ixOsalMbufAlloc(poolPtr)

#define IX_OSAL_MBUF_POOL_PUT(bufPtr) \
    ixOsalMbufFree(bufPtr)

#define IX_OSAL_MBUF_POOL_PUT_CHAIN(bufPtr) \
    ixOsalMbufChainFree(bufPtr)

#define IX_OSAL_MBUF_POOL_SHOW(poolPtr) \
    ixOsalMbufPoolShow(poolPtr)

#define IX_OSAL_MBUF_POOL_MDATA_RESET(bufPtr) \
    ixOsalMbufDataPtrReset(bufPtr)

#define IX_OSAL_MBUF_POOL_UNINIT(m_pool_ptr)  \
        ixOsalBuffPoolUninit(m_pool_ptr)

#include "IxOsalOsBufferMgt.h"


#define IX_OSAL_CONVERT_OSBUF_TO_IXPBUF( osBufPtr, ixpBufPtr) \
        IX_OSAL_OS_CONVERT_OSBUF_TO_IXPBUF( osBufPtr, ixpBufPtr)        



#define IX_OSAL_CONVERT_IXPBUF_TO_OSBUF( ixpBufPtr, osBufPtr)  \
        IX_OSAL_OS_CONVERT_IXPBUF_TO_OSBUF( ixpBufPtr, osBufPtr)


PUBLIC IX_OSAL_MBUF_POOL *ixOsalPoolInit (UINT32 count,
                      UINT32 size, const char *name);

PUBLIC IX_OSAL_MBUF_POOL *ixOsalNoAllocPoolInit (void *poolBufPtr,
                         void *poolDataPtr,
						 UINT32 count,
						 UINT32 size,
						 const char *name);

PUBLIC IX_OSAL_MBUF *ixOsalMbufAlloc (IX_OSAL_MBUF_POOL * pool);

PUBLIC IX_OSAL_MBUF *ixOsalMbufFree (IX_OSAL_MBUF * mbuf);

PUBLIC void ixOsalMbufChainFree (IX_OSAL_MBUF * mbuf);

PUBLIC void ixOsalMbufDataPtrReset (IX_OSAL_MBUF * mbuf);

PUBLIC void ixOsalMbufPoolShow (IX_OSAL_MBUF_POOL * pool);

PUBLIC IX_STATUS ixOsalBuffPoolUninit (IX_OSAL_MBUF_POOL * pool);

PUBLIC UINT32 ixOsalBuffPoolFreeCountGet(IX_OSAL_MBUF_POOL * pool);




#endif /* IxOsalBufferMgt_H */
