
/*****************************************************************************/

#ifndef XEMAC_L_H		/* prevent circular inclusions */
#define XEMAC_L_H		/* by using protection macros */

/***************************** Include Files *********************************/

#include "xbasic_types.h"
#include "xio.h"

/************************** Constant Definitions *****************************/

/* Offset of the MAC registers from the IPIF base address */
#define XEM_REG_OFFSET	   0x1100UL

#define XEM_EMIR_OFFSET	  (XEM_REG_OFFSET + 0x0)	/* EMAC Module ID */
#define XEM_ECR_OFFSET	  (XEM_REG_OFFSET + 0x4)	/* MAC Control */
#define XEM_IFGP_OFFSET	  (XEM_REG_OFFSET + 0x8)	/* Interframe Gap */
#define XEM_SAH_OFFSET	  (XEM_REG_OFFSET + 0xC)	/* Station addr, high */
#define XEM_SAL_OFFSET	  (XEM_REG_OFFSET + 0x10)	/* Station addr, low */
#define XEM_MGTCR_OFFSET  (XEM_REG_OFFSET + 0x14)	/* MII mgmt control */
#define XEM_MGTDR_OFFSET  (XEM_REG_OFFSET + 0x18)	/* MII mgmt data */
#define XEM_RPLR_OFFSET	  (XEM_REG_OFFSET + 0x1C)	/* Rx packet length */
#define XEM_TPLR_OFFSET	  (XEM_REG_OFFSET + 0x20)	/* Tx packet length */
#define XEM_TSR_OFFSET	  (XEM_REG_OFFSET + 0x24)	/* Tx status */
#define XEM_RMFC_OFFSET	  (XEM_REG_OFFSET + 0x28)	/* Rx missed frames */
#define XEM_RCC_OFFSET	  (XEM_REG_OFFSET + 0x2C)	/* Rx collisions */
#define XEM_RFCSEC_OFFSET (XEM_REG_OFFSET + 0x30)	/* Rx FCS errors */
#define XEM_RAEC_OFFSET	  (XEM_REG_OFFSET + 0x34)	/* Rx alignment errors */
#define XEM_TEDC_OFFSET	  (XEM_REG_OFFSET + 0x38)	/* Transmit excess
							 * deferral cnt */

#define XEM_ISR_OFFSET		 0x20UL /* Interrupt status */

#define XEM_DMA_OFFSET		 0x2300UL
#define XEM_DMA_SEND_OFFSET	 (XEM_DMA_OFFSET + 0x0) /* DMA send channel */
#define XEM_DMA_RECV_OFFSET	 (XEM_DMA_OFFSET + 0x40)	/* DMA recv channel */

#define XEM_PFIFO_OFFSET	 0x2000UL
#define XEM_PFIFO_TXREG_OFFSET	 (XEM_PFIFO_OFFSET + 0x0)	/* Tx registers */
#define XEM_PFIFO_RXREG_OFFSET	 (XEM_PFIFO_OFFSET + 0x10)	/* Rx registers */
#define XEM_PFIFO_TXDATA_OFFSET	 (XEM_PFIFO_OFFSET + 0x100)	/* Tx keyhole */
#define XEM_PFIFO_RXDATA_OFFSET	 (XEM_PFIFO_OFFSET + 0x200)	/* Rx keyhole */

#define XEM_EMIR_VERSION_MASK	 0xFFFF0000UL	/* Device version */
#define XEM_EMIR_TYPE_MASK	 0x0000FF00UL	/* Device type */

#define XEM_ECR_FULL_DUPLEX_MASK	 0x80000000UL	/* Full duplex mode */
#define XEM_ECR_XMIT_RESET_MASK		 0x40000000UL	/* Reset transmitter */
#define XEM_ECR_XMIT_ENABLE_MASK	 0x20000000UL	/* Enable transmitter */
#define XEM_ECR_RECV_RESET_MASK		 0x10000000UL	/* Reset receiver */
#define XEM_ECR_RECV_ENABLE_MASK	 0x08000000UL	/* Enable receiver */
#define XEM_ECR_PHY_ENABLE_MASK		 0x04000000UL	/* Enable PHY */
#define XEM_ECR_XMIT_PAD_ENABLE_MASK	 0x02000000UL	/* Enable xmit pad insert */
#define XEM_ECR_XMIT_FCS_ENABLE_MASK	 0x01000000UL	/* Enable xmit FCS insert */
#define XEM_ECR_XMIT_ADDR_INSERT_MASK	 0x00800000UL	/* Enable xmit source addr
							 * insertion */
#define XEM_ECR_XMIT_ERROR_INSERT_MASK	 0x00400000UL	/* Insert xmit error */
#define XEM_ECR_XMIT_ADDR_OVWRT_MASK	 0x00200000UL	/* Enable xmit source addr
							 * overwrite */
#define XEM_ECR_LOOPBACK_MASK		 0x00100000UL	/* Enable internal
							 * loopback */
#define XEM_ECR_RECV_STRIP_ENABLE_MASK	 0x00080000UL	/* Enable recv pad/fcs strip */
#define XEM_ECR_UNICAST_ENABLE_MASK	 0x00020000UL	/* Enable unicast addr */
#define XEM_ECR_MULTI_ENABLE_MASK	 0x00010000UL	/* Enable multicast addr */
#define XEM_ECR_BROAD_ENABLE_MASK	 0x00008000UL	/* Enable broadcast addr */
#define XEM_ECR_PROMISC_ENABLE_MASK	 0x00004000UL	/* Enable promiscuous mode */
#define XEM_ECR_RECV_ALL_MASK		 0x00002000UL	/* Receive all frames */
#define XEM_ECR_RESERVED2_MASK		 0x00001000UL	/* Reserved */
#define XEM_ECR_MULTI_HASH_ENABLE_MASK	 0x00000800UL	/* Enable multicast hash */
#define XEM_ECR_PAUSE_FRAME_MASK	 0x00000400UL	/* Interpret pause frames */
#define XEM_ECR_CLEAR_HASH_MASK		 0x00000200UL	/* Clear hash table */
#define XEM_ECR_ADD_HASH_ADDR_MASK	 0x00000100UL	/* Add hash table address */

#define XEM_IFGP_PART1_MASK	    0xF8000000UL	/* Interframe Gap Part1 */
#define XEM_IFGP_PART1_SHIFT	    27
#define XEM_IFGP_PART2_MASK	    0x07C00000UL	/* Interframe Gap Part2 */
#define XEM_IFGP_PART2_SHIFT	    22

#define XEM_SAH_ADDR_MASK	    0x0000FFFFUL	/* Station address high bytes */

#define XEM_SAL_ADDR_MASK	    0xFFFFFFFFUL	/* Station address low bytes */

#define XEM_MGTCR_START_MASK	    0x80000000UL	/* Start/Busy */
#define XEM_MGTCR_RW_NOT_MASK	    0x40000000UL	/* Read/Write Not (direction) */
#define XEM_MGTCR_PHY_ADDR_MASK	    0x3E000000UL	/* PHY address */
#define XEM_MGTCR_PHY_ADDR_SHIFT    25	/* PHY address shift */
#define XEM_MGTCR_REG_ADDR_MASK	    0x01F00000UL	/* Register address */
#define XEM_MGTCR_REG_ADDR_SHIFT    20	/* Register addr shift */
#define XEM_MGTCR_MII_ENABLE_MASK   0x00080000UL	/* Enable MII from EMAC */
#define XEM_MGTCR_RD_ERROR_MASK	    0x00040000UL	/* MII mgmt read error */

#define XEM_MGTDR_DATA_MASK	    0x0000FFFFUL	/* MII data */

#define XEM_RPLR_LENGTH_MASK	    0x0000FFFFUL	/* Receive packet length */

#define XEM_TPLR_LENGTH_MASK	    0x0000FFFFUL	/* Transmit packet length */

#define XEM_TSR_EXCESS_DEFERRAL_MASK 0x80000000UL	/* Transmit excess deferral */
#define XEM_TSR_FIFO_UNDERRUN_MASK   0x40000000UL	/* Packet FIFO underrun */
#define XEM_TSR_ATTEMPTS_MASK	     0x3E000000UL	/* Transmission attempts */
#define XEM_TSR_LATE_COLLISION_MASK  0x01000000UL	/* Transmit late collision */

#define XEM_RMFC_DATA_MASK	    0x0000FFFFUL

#define XEM_RCC_DATA_MASK	    0x0000FFFFUL

#define XEM_RFCSEC_DATA_MASK	    0x0000FFFFUL

#define XEM_RAEC_DATA_MASK	    0x0000FFFFUL

#define XEM_TEDC_DATA_MASK	    0x0000FFFFUL

#define XEM_EIR_XMIT_DONE_MASK	       0x00000001UL	/* Xmit complete */
#define XEM_EIR_RECV_DONE_MASK	       0x00000002UL	/* Recv complete */
#define XEM_EIR_XMIT_ERROR_MASK	       0x00000004UL	/* Xmit error */
#define XEM_EIR_RECV_ERROR_MASK	       0x00000008UL	/* Recv error */
#define XEM_EIR_XMIT_SFIFO_EMPTY_MASK  0x00000010UL	/* Xmit status fifo empty */
#define XEM_EIR_RECV_LFIFO_EMPTY_MASK  0x00000020UL	/* Recv length fifo empty */
#define XEM_EIR_XMIT_LFIFO_FULL_MASK   0x00000040UL	/* Xmit length fifo full */
#define XEM_EIR_RECV_LFIFO_OVER_MASK   0x00000080UL	/* Recv length fifo
							 * overrun */
#define XEM_EIR_RECV_LFIFO_UNDER_MASK  0x00000100UL	/* Recv length fifo
							 * underrun */
#define XEM_EIR_XMIT_SFIFO_OVER_MASK   0x00000200UL	/* Xmit status fifo
							 * overrun */
#define XEM_EIR_XMIT_SFIFO_UNDER_MASK  0x00000400UL	/* Transmit status fifo
							 * underrun */
#define XEM_EIR_XMIT_LFIFO_OVER_MASK   0x00000800UL	/* Transmit length fifo
							 * overrun */
#define XEM_EIR_XMIT_LFIFO_UNDER_MASK  0x00001000UL	/* Transmit length fifo
							 * underrun */
#define XEM_EIR_XMIT_PAUSE_MASK	       0x00002000UL	/* Transmit pause pkt
							 * received */
#define XEM_EIR_RECV_DFIFO_OVER_MASK   0x00004000UL	/* Receive data fifo
							 * overrun */
#define XEM_EIR_RECV_MISSED_FRAME_MASK 0x00008000UL	/* Receive missed frame
							 * error */
#define XEM_EIR_RECV_COLLISION_MASK    0x00010000UL	/* Receive collision
							 * error */
#define XEM_EIR_RECV_FCS_ERROR_MASK    0x00020000UL	/* Receive FCS error */
#define XEM_EIR_RECV_LEN_ERROR_MASK    0x00040000UL	/* Receive length field
							 * error */
#define XEM_EIR_RECV_SHORT_ERROR_MASK  0x00080000UL	/* Receive short frame
							 * error */
#define XEM_EIR_RECV_LONG_ERROR_MASK   0x00100000UL	/* Receive long frame
							 * error */
#define XEM_EIR_RECV_ALIGN_ERROR_MASK  0x00200000UL	/* Receive alignment
							 * error */

/**************************** Type Definitions *******************************/

/***************** Macros (Inline Functions) Definitions *********************/


/****************************************************************************/
#define XEmac_mReadReg(BaseAddress, RegOffset) \
		    XIo_In32((BaseAddress) + (RegOffset))

/****************************************************************************/
#define XEmac_mWriteReg(BaseAddress, RegOffset, Data) \
		    XIo_Out32((BaseAddress) + (RegOffset), (Data))

/****************************************************************************/
#define XEmac_mSetControlReg(BaseAddress, Mask) \
		    XIo_Out32((BaseAddress) + XEM_ECR_OFFSET, (Mask))

/****************************************************************************/
#define XEmac_mSetMacAddress(BaseAddress, AddressPtr)		    \
{								    \
    u32 MacAddr;						\
								    \
    MacAddr = ((AddressPtr)[0] << 8) | (AddressPtr)[1];		    \
    XIo_Out32((BaseAddress) + XEM_SAH_OFFSET, MacAddr);		    \
								    \
    MacAddr = ((AddressPtr)[2] << 24) | ((AddressPtr)[3] << 16) |   \
	      ((AddressPtr)[4] << 8) | (AddressPtr)[5];		    \
								    \
    XIo_Out32((BaseAddress) + XEM_SAL_OFFSET, MacAddr);		    \
}

/****************************************************************************/
#define XEmac_mEnable(BaseAddress) \
{ \
    u32 Control; \
    Control = XIo_In32((BaseAddress) + XEM_ECR_OFFSET); \
    Control &= ~(XEM_ECR_XMIT_RESET_MASK | XEM_ECR_RECV_RESET_MASK); \
    Control |= (XEM_ECR_XMIT_ENABLE_MASK | XEM_ECR_RECV_ENABLE_MASK); \
    XIo_Out32((BaseAddress) + XEM_ECR_OFFSET, Control); \
}

/****************************************************************************/
#define XEmac_mDisable(BaseAddress) \
		XIo_Out32((BaseAddress) + XEM_ECR_OFFSET, \
		    XIo_In32((BaseAddress) + XEM_ECR_OFFSET) & \
		    ~(XEM_ECR_XMIT_ENABLE_MASK | XEM_ECR_RECV_ENABLE_MASK))

/****************************************************************************/
#define XEmac_mIsTxDone(BaseAddress) \
	     (XIo_In32((BaseAddress) + XEM_ISR_OFFSET) & XEM_EIR_XMIT_DONE_MASK)

/****************************************************************************/
#define XEmac_mIsRxEmpty(BaseAddress) \
	  (!(XIo_In32((BaseAddress) + XEM_ISR_OFFSET) & XEM_EIR_RECV_DONE_MASK))

/****************************************************************************/
#define XEmac_mPhyReset(BaseAddress) \
{ \
    u32 Control;				    \
    Control = XIo_In32((BaseAddress) + XEM_ECR_OFFSET); \
    Control &= ~XEM_ECR_PHY_ENABLE_MASK;		\
    XIo_Out32((BaseAddress) + XEM_ECR_OFFSET, Control); \
    Control |= XEM_ECR_PHY_ENABLE_MASK;			\
    XIo_Out32((BaseAddress) + XEM_ECR_OFFSET, Control); \
}

/************************** Function Prototypes ******************************/

void XEmac_SendFrame(u32 BaseAddress, u8 * FramePtr, int Size);
int XEmac_RecvFrame(u32 BaseAddress, u8 * FramePtr);

#endif				/* end of protection macro */
