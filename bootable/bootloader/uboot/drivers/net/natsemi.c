


/* Includes */
#include <common.h>
#include <malloc.h>
#include <net.h>
#include <netdev.h>
#include <asm/io.h>
#include <pci.h>

/* defines */
#define EEPROM_SIZE 0xb /*12 16-bit chunks, or 24 bytes*/

#define DSIZE		0x00000FFF
#define ETH_ALEN	6
#define CRC_SIZE	4
#define TOUT_LOOP	500000
#define TX_BUF_SIZE	1536
#define RX_BUF_SIZE	1536
#define NUM_RX_DESC	4	/* Number of Rx descriptor registers. */

enum register_offsets {
	ChipCmd	= 0x00,
	ChipConfig	= 0x04,
	EECtrl		= 0x08,
	IntrMask	= 0x14,
	IntrEnable	= 0x18,
	TxRingPtr	= 0x20,
	TxConfig	= 0x24,
	RxRingPtr	= 0x30,
	RxConfig	= 0x34,
	ClkRun		= 0x3C,
	RxFilterAddr	= 0x48,
	RxFilterData	= 0x4C,
	SiliconRev	= 0x58,
	PCIPM		= 0x44,
	BasicControl	= 0x80,
	BasicStatus	= 0x84,
	/* These are from the spec, around page 78... on a separate table. */
	PGSEL		= 0xCC,
	PMDCSR		= 0xE4,
	TSTDAT		= 0xFC,
	DSPCFG		= 0xF4,
	SDCFG		= 0x8C
};

/* Bit in ChipCmd. */
enum ChipCmdBits {
	ChipReset	= 0x100,
	RxReset		= 0x20,
	TxReset		= 0x10,
	RxOff		= 0x08,
	RxOn		= 0x04,
	TxOff		= 0x02,
	TxOn		= 0x01
};

enum ChipConfigBits {
	LinkSts	= 0x80000000,
	HundSpeed	= 0x40000000,
	FullDuplex	= 0x20000000,
	TenPolarity	= 0x10000000,
	AnegDone	= 0x08000000,
	AnegEnBothBoth	= 0x0000E000,
	AnegDis100Full	= 0x0000C000,
	AnegEn100Both	= 0x0000A000,
	AnegDis100Half	= 0x00008000,
	AnegEnBothHalf	= 0x00006000,
	AnegDis10Full	= 0x00004000,
	AnegEn10Both	= 0x00002000,
	DuplexMask	= 0x00008000,
	SpeedMask	= 0x00004000,
	AnegMask	= 0x00002000,
	AnegDis10Half	= 0x00000000,
	ExtPhy		= 0x00001000,
	PhyRst		= 0x00000400,
	PhyDis		= 0x00000200,
	BootRomDisable	= 0x00000004,
	BEMode		= 0x00000001,
};

enum TxConfig_bits {
	TxDrthMask	= 0x3f,
	TxFlthMask	= 0x3f00,
	TxMxdmaMask	= 0x700000,
	TxMxdma_512	= 0x0,
	TxMxdma_4	= 0x100000,
	TxMxdma_8	= 0x200000,
	TxMxdma_16	= 0x300000,
	TxMxdma_32	= 0x400000,
	TxMxdma_64	= 0x500000,
	TxMxdma_128	= 0x600000,
	TxMxdma_256	= 0x700000,
	TxCollRetry	= 0x800000,
	TxAutoPad	= 0x10000000,
	TxMacLoop	= 0x20000000,
	TxHeartIgn	= 0x40000000,
	TxCarrierIgn	= 0x80000000
};

enum RxConfig_bits {
	RxDrthMask	= 0x3e,
	RxMxdmaMask	= 0x700000,
	RxMxdma_512	= 0x0,
	RxMxdma_4	= 0x100000,
	RxMxdma_8	= 0x200000,
	RxMxdma_16	= 0x300000,
	RxMxdma_32	= 0x400000,
	RxMxdma_64	= 0x500000,
	RxMxdma_128	= 0x600000,
	RxMxdma_256	= 0x700000,
	RxAcceptLong	= 0x8000000,
	RxAcceptTx	= 0x10000000,
	RxAcceptRunt	= 0x40000000,
	RxAcceptErr	= 0x80000000
};

/* Bits in the RxMode register. */
enum rx_mode_bits {
	AcceptErr	= 0x20,
	AcceptRunt	= 0x10,
	AcceptBroadcast	= 0xC0000000,
	AcceptMulticast	= 0x00200000,
	AcceptAllMulticast = 0x20000000,
	AcceptAllPhys	= 0x10000000,
	AcceptMyPhys	= 0x08000000
};

typedef struct _BufferDesc {
	u32 link;
	vu_long cmdsts;
	u32 bufptr;
	u32 software_use;
} BufferDesc;

/* Bits in network_desc.status */
enum desc_status_bits {
	DescOwn = 0x80000000, DescMore = 0x40000000, DescIntr = 0x20000000,
	DescNoCRC = 0x10000000, DescPktOK = 0x08000000,
	DescSizeMask = 0xfff,

	DescTxAbort = 0x04000000, DescTxFIFO = 0x02000000,
	DescTxCarrier = 0x01000000, DescTxDefer = 0x00800000,
	DescTxExcDefer = 0x00400000, DescTxOOWCol = 0x00200000,
	DescTxExcColl = 0x00100000, DescTxCollCount = 0x000f0000,

	DescRxAbort = 0x04000000, DescRxOver = 0x02000000,
	DescRxDest = 0x01800000, DescRxLong = 0x00400000,
	DescRxRunt = 0x00200000, DescRxInvalid = 0x00100000,
	DescRxCRC = 0x00080000, DescRxAlign = 0x00040000,
	DescRxLoop = 0x00020000, DesRxColl = 0x00010000,
};

/* Globals */
#ifdef NATSEMI_DEBUG
static int natsemi_debug = 0;	/* 1 verbose debugging, 0 normal */
#endif
static u32 SavedClkRun;
static unsigned int cur_rx;
static unsigned int advertising;
static unsigned int rx_config;
static unsigned int tx_config;

static BufferDesc txd __attribute__ ((aligned(4)));
static BufferDesc rxd[NUM_RX_DESC] __attribute__ ((aligned(4)));

static unsigned char txb[TX_BUF_SIZE] __attribute__ ((aligned(4)));
static unsigned char rxb[NUM_RX_DESC * RX_BUF_SIZE]
    __attribute__ ((aligned(4)));

/* Function Prototypes */
#if 0
static void write_eeprom(struct eth_device *dev, long addr, int location,
			 short value);
#endif
static int read_eeprom(struct eth_device *dev, long addr, int location);
static int mdio_read(struct eth_device *dev, int phy_id, int location);
static int natsemi_init(struct eth_device *dev, bd_t * bis);
static void natsemi_reset(struct eth_device *dev);
static void natsemi_init_rxfilter(struct eth_device *dev);
static void natsemi_init_txd(struct eth_device *dev);
static void natsemi_init_rxd(struct eth_device *dev);
static void natsemi_set_rx_mode(struct eth_device *dev);
static void natsemi_check_duplex(struct eth_device *dev);
static int natsemi_send(struct eth_device *dev, volatile void *packet,
			int length);
static int natsemi_poll(struct eth_device *dev);
static void natsemi_disable(struct eth_device *dev);

static struct pci_device_id supported[] = {
	{PCI_VENDOR_ID_NS, PCI_DEVICE_ID_NS_83815},
	{}
};

#define bus_to_phys(a)	pci_mem_to_phys((pci_dev_t)dev->priv, a)
#define phys_to_bus(a)	pci_phys_to_mem((pci_dev_t)dev->priv, a)

static inline int
INW(struct eth_device *dev, u_long addr)
{
	return le16_to_cpu(*(vu_short *) (addr + dev->iobase));
}

static int
INL(struct eth_device *dev, u_long addr)
{
	return le32_to_cpu(*(vu_long *) (addr + dev->iobase));
}

static inline void
OUTW(struct eth_device *dev, int command, u_long addr)
{
	*(vu_short *) ((addr + dev->iobase)) = cpu_to_le16(command);
}

static inline void
OUTL(struct eth_device *dev, int command, u_long addr)
{
	*(vu_long *) ((addr + dev->iobase)) = cpu_to_le32(command);
}


int
natsemi_initialize(bd_t * bis)
{
	pci_dev_t devno;
	int card_number = 0;
	struct eth_device *dev;
	u32 iobase, status, chip_config;
	int i, idx = 0;
	int prev_eedata;
	u32 tmp;

	while (1) {
		/* Find PCI device(s) */
		if ((devno = pci_find_devices(supported, idx++)) < 0) {
			break;
		}

		pci_read_config_dword(devno, PCI_BASE_ADDRESS_0, &iobase);
		iobase &= ~0x3;	/* bit 1: unused and bit 0: I/O Space Indicator */

		pci_write_config_dword(devno, PCI_COMMAND,
				       PCI_COMMAND_MEMORY | PCI_COMMAND_MASTER);

		/* Check if I/O accesses and Bus Mastering are enabled. */
		pci_read_config_dword(devno, PCI_COMMAND, &status);
		if (!(status & PCI_COMMAND_MEMORY)) {
			printf("Error: Can not enable MEM access.\n");
			continue;
		} else if (!(status & PCI_COMMAND_MASTER)) {
			printf("Error: Can not enable Bus Mastering.\n");
			continue;
		}

		dev = (struct eth_device *) malloc(sizeof *dev);

		sprintf(dev->name, "dp83815#%d", card_number);
		dev->iobase = bus_to_phys(iobase);
#ifdef NATSEMI_DEBUG
		printf("natsemi: NatSemi ns8381[56] @ %#x\n", dev->iobase);
#endif
		dev->priv = (void *) devno;
		dev->init = natsemi_init;
		dev->halt = natsemi_disable;
		dev->send = natsemi_send;
		dev->recv = natsemi_poll;

		eth_register(dev);

		card_number++;

		/* Set the latency timer for value. */
		pci_write_config_byte(devno, PCI_LATENCY_TIMER, 0x20);

		udelay(10 * 1000);

		/* natsemi has a non-standard PM control register
		 * in PCI config space.  Some boards apparently need
		 * to be brought to D0 in this manner.  */
		pci_read_config_dword(devno, PCIPM, &tmp);
		if (tmp & (0x03 | 0x100)) {
			/* D0 state, disable PME assertion */
			u32 newtmp = tmp & ~(0x03 | 0x100);
			pci_write_config_dword(devno, PCIPM, newtmp);
		}

		printf("natsemi: EEPROM contents:\n");
		for (i = 0; i <= EEPROM_SIZE; i++) {
			short eedata = read_eeprom(dev, EECtrl, i);
			printf(" %04hx", eedata);
		}
		printf("\n");

		/* get MAC address */
		prev_eedata = read_eeprom(dev, EECtrl, 6);
		for (i = 0; i < 3; i++) {
			int eedata = read_eeprom(dev, EECtrl, i + 7);
			dev->enetaddr[i*2] = (eedata << 1) + (prev_eedata >> 15);
			dev->enetaddr[i*2+1] = eedata >> 7;
			prev_eedata = eedata;
		}

		/* Reset the chip to erase any previous misconfiguration. */
		OUTL(dev, ChipReset, ChipCmd);

		advertising = mdio_read(dev, 1, 4);
		chip_config = INL(dev, ChipConfig);
#ifdef NATSEMI_DEBUG
		printf("%s: Transceiver status %#08X advertising %#08X\n",
			dev->name, (int) INL(dev, BasicStatus), advertising);
		printf("%s: Transceiver default autoneg. %s 10%s %s duplex.\n",
			dev->name, chip_config & AnegMask ? "enabled, advertise" :
			"disabled, force", chip_config & SpeedMask ? "0" : "",
			chip_config & DuplexMask ? "full" : "half");
#endif
		chip_config |= AnegEnBothBoth;
#ifdef NATSEMI_DEBUG
		printf("%s: changed to autoneg. %s 10%s %s duplex.\n",
			dev->name, chip_config & AnegMask ? "enabled, advertise" :
			"disabled, force", chip_config & SpeedMask ? "0" : "",
			chip_config & DuplexMask ? "full" : "half");
#endif
		/*write new autoneg bits, reset phy*/
		OUTL(dev, (chip_config | PhyRst), ChipConfig);
		/*un-reset phy*/
		OUTL(dev, chip_config, ChipConfig);

		/* Disable PME:
		 * The PME bit is initialized from the EEPROM contents.
		 * PCI cards probably have PME disabled, but motherboard
		 * implementations may have PME set to enable WakeOnLan.
		 * With PME set the chip will scan incoming packets but
		 * nothing will be written to memory. */
		SavedClkRun = INL(dev, ClkRun);
		OUTL(dev, SavedClkRun & ~0x100, ClkRun);
	}
	return card_number;
}


#define eeprom_delay(ee_addr)	INL(dev, ee_addr)

enum EEPROM_Ctrl_Bits {
	EE_ShiftClk = 0x04,
	EE_DataIn = 0x01,
	EE_ChipSelect = 0x08,
	EE_DataOut = 0x02
};

#define EE_Write0 (EE_ChipSelect)
#define EE_Write1 (EE_ChipSelect | EE_DataIn)
/* The EEPROM commands include the alway-set leading bit. */
enum EEPROM_Cmds {
	EE_WrEnCmd = (4 << 6), EE_WriteCmd = (5 << 6),
	EE_ReadCmd = (6 << 6), EE_EraseCmd = (7 << 6),
};

#if 0
static void
write_eeprom(struct eth_device *dev, long addr, int location, short value)
{
	int i;
	int ee_addr = (typeof(ee_addr))addr;
	short wren_cmd = EE_WrEnCmd | 0x30; /*wren is 100 + 11XXXX*/
	short write_cmd = location | EE_WriteCmd;

#ifdef NATSEMI_DEBUG
	printf("write_eeprom: %08x, %04hx, %04hx\n",
		dev->iobase + ee_addr, write_cmd, value);
#endif
	/* Shift the write enable command bits out. */
	for (i = 9; i >= 0; i--) {
		short cmdval = (wren_cmd & (1 << i)) ? EE_Write1 : EE_Write0;
		OUTL(dev, cmdval, ee_addr);
		eeprom_delay(ee_addr);
		OUTL(dev, cmdval | EE_ShiftClk, ee_addr);
		eeprom_delay(ee_addr);
	}

	OUTL(dev, 0, ee_addr); /*bring chip select low*/
	OUTL(dev, EE_ShiftClk, ee_addr);
	eeprom_delay(ee_addr);

	/* Shift the write command bits out. */
	for (i = 9; i >= 0; i--) {
		short cmdval = (write_cmd & (1 << i)) ? EE_Write1 : EE_Write0;
		OUTL(dev, cmdval, ee_addr);
		eeprom_delay(ee_addr);
		OUTL(dev, cmdval | EE_ShiftClk, ee_addr);
		eeprom_delay(ee_addr);
	}

	for (i = 0; i < 16; i++) {
		short cmdval = (value & (1 << i)) ? EE_Write1 : EE_Write0;
		OUTL(dev, cmdval, ee_addr);
		eeprom_delay(ee_addr);
		OUTL(dev, cmdval | EE_ShiftClk, ee_addr);
		eeprom_delay(ee_addr);
	}

	OUTL(dev, 0, ee_addr); /*bring chip select low*/
	OUTL(dev, EE_ShiftClk, ee_addr);
	for (i = 0; i < 200000; i++) {
		OUTL(dev, EE_Write0, ee_addr); /*poll for done*/
		if (INL(dev, ee_addr) & EE_DataOut) {
		    break; /*finished*/
		}
	}
	eeprom_delay(ee_addr);

	/* Terminate the EEPROM access. */
	OUTL(dev, EE_Write0, ee_addr);
	OUTL(dev, 0, ee_addr);
	return;
}
#endif

static int
read_eeprom(struct eth_device *dev, long addr, int location)
{
	int i;
	int retval = 0;
	int ee_addr = (typeof(ee_addr))addr;
	int read_cmd = location | EE_ReadCmd;

	OUTL(dev, EE_Write0, ee_addr);

	/* Shift the read command bits out. */
	for (i = 10; i >= 0; i--) {
		short dataval = (read_cmd & (1 << i)) ? EE_Write1 : EE_Write0;
		OUTL(dev, dataval, ee_addr);
		eeprom_delay(ee_addr);
		OUTL(dev, dataval | EE_ShiftClk, ee_addr);
		eeprom_delay(ee_addr);
	}
	OUTL(dev, EE_ChipSelect, ee_addr);
	eeprom_delay(ee_addr);

	for (i = 0; i < 16; i++) {
		OUTL(dev, EE_ChipSelect | EE_ShiftClk, ee_addr);
		eeprom_delay(ee_addr);
		retval |= (INL(dev, ee_addr) & EE_DataOut) ? 1 << i : 0;
		OUTL(dev, EE_ChipSelect, ee_addr);
		eeprom_delay(ee_addr);
	}

	/* Terminate the EEPROM access. */
	OUTL(dev, EE_Write0, ee_addr);
	OUTL(dev, 0, ee_addr);
#ifdef NATSEMI_DEBUG
	if (natsemi_debug)
		printf("read_eeprom: %08x, %08x, retval %08x\n",
			dev->iobase + ee_addr, read_cmd, retval);
#endif
	return retval;
}


static int
mdio_read(struct eth_device *dev, int phy_id, int location)
{
	if (phy_id == 1 && location < 32)
		return INL(dev, BasicControl+(location<<2))&0xffff;
	else
		return 0xffff;
}


static int
natsemi_init(struct eth_device *dev, bd_t * bis)
{

	natsemi_reset(dev);

	/* Disable PME:
	 * The PME bit is initialized from the EEPROM contents.
	 * PCI cards probably have PME disabled, but motherboard
	 * implementations may have PME set to enable WakeOnLan.
	 * With PME set the chip will scan incoming packets but
	 * nothing will be written to memory. */
	OUTL(dev, SavedClkRun & ~0x100, ClkRun);

	natsemi_init_rxfilter(dev);
	natsemi_init_txd(dev);
	natsemi_init_rxd(dev);

	/* Configure the PCI bus bursts and FIFO thresholds. */
	tx_config = TxAutoPad | TxCollRetry | TxMxdma_256 | (0x1002);
	rx_config = RxMxdma_256 | 0x20;

#ifdef NATSEMI_DEBUG
	printf("%s: Setting TxConfig Register %#08X\n", dev->name, tx_config);
	printf("%s: Setting RxConfig Register %#08X\n", dev->name, rx_config);
#endif
	OUTL(dev, tx_config, TxConfig);
	OUTL(dev, rx_config, RxConfig);

	natsemi_check_duplex(dev);
	natsemi_set_rx_mode(dev);

	OUTL(dev, (RxOn | TxOn), ChipCmd);
	return 1;
}

static void
natsemi_reset(struct eth_device *dev)
{
	OUTL(dev, ChipReset, ChipCmd);

	/* On page 78 of the spec, they recommend some settings for "optimum
	   performance" to be done in sequence.  These settings optimize some
	   of the 100Mbit autodetection circuitry.  Also, we only want to do
	   this for rev C of the chip.  */
	if (INL(dev, SiliconRev) == 0x302) {
		OUTW(dev, 0x0001, PGSEL);
		OUTW(dev, 0x189C, PMDCSR);
		OUTW(dev, 0x0000, TSTDAT);
		OUTW(dev, 0x5040, DSPCFG);
		OUTW(dev, 0x008C, SDCFG);
	}
	/* Disable interrupts using the mask. */
	OUTL(dev, 0, IntrMask);
	OUTL(dev, 0, IntrEnable);
}


static void
natsemi_init_rxfilter(struct eth_device *dev)
{
	int i;

	for (i = 0; i < ETH_ALEN; i += 2) {
		OUTL(dev, i, RxFilterAddr);
		OUTW(dev, dev->enetaddr[i] + (dev->enetaddr[i + 1] << 8),
		     RxFilterData);
	}
}


static void
natsemi_init_txd(struct eth_device *dev)
{
	txd.link = (u32) 0;
	txd.cmdsts = (u32) 0;
	txd.bufptr = (u32) & txb[0];

	/* load Transmit Descriptor Register */
	OUTL(dev, (u32) & txd, TxRingPtr);
#ifdef NATSEMI_DEBUG
	printf("natsemi_init_txd: TX descriptor reg loaded with: %#08X\n",
	       INL(dev, TxRingPtr));
#endif
}


static void
natsemi_init_rxd(struct eth_device *dev)
{
	int i;

	cur_rx = 0;

	/* init RX descriptor */
	for (i = 0; i < NUM_RX_DESC; i++) {
		rxd[i].link =
		    cpu_to_le32((i + 1 <
				 NUM_RX_DESC) ? (u32) & rxd[i +
							    1] : (u32) &
				rxd[0]);
		rxd[i].cmdsts = cpu_to_le32((u32) RX_BUF_SIZE);
		rxd[i].bufptr = cpu_to_le32((u32) & rxb[i * RX_BUF_SIZE]);
#ifdef NATSEMI_DEBUG
		printf
		    ("natsemi_init_rxd: rxd[%d]=%p link=%X cmdsts=%lX bufptr=%X\n",
			i, &rxd[i], le32_to_cpu(rxd[i].link),
				rxd[i].cmdsts, rxd[i].bufptr);
#endif
	}

	/* load Receive Descriptor Register */
	OUTL(dev, (u32) & rxd[0], RxRingPtr);

#ifdef NATSEMI_DEBUG
	printf("natsemi_init_rxd: RX descriptor register loaded with: %X\n",
	       INL(dev, RxRingPtr));
#endif
}


static void
natsemi_set_rx_mode(struct eth_device *dev)
{
	u32 rx_mode = AcceptBroadcast | AcceptMyPhys;

	OUTL(dev, rx_mode, RxFilterAddr);
}

static void
natsemi_check_duplex(struct eth_device *dev)
{
	int duplex = INL(dev, ChipConfig) & FullDuplex ? 1 : 0;

#ifdef NATSEMI_DEBUG
	printf("%s: Setting %s-duplex based on negotiated link"
	       " capability.\n", dev->name, duplex ? "full" : "half");
#endif
	if (duplex) {
		rx_config |= RxAcceptTx;
		tx_config |= (TxCarrierIgn | TxHeartIgn);
	} else {
		rx_config &= ~RxAcceptTx;
		tx_config &= ~(TxCarrierIgn | TxHeartIgn);
	}
	OUTL(dev, tx_config, TxConfig);
	OUTL(dev, rx_config, RxConfig);
}

static int
natsemi_send(struct eth_device *dev, volatile void *packet, int length)
{
	u32 i, status = 0;
	u32 tx_status = 0;
	u32 *tx_ptr = &tx_status;
	vu_long *res = (vu_long *)tx_ptr;

	/* Stop the transmitter */
	OUTL(dev, TxOff, ChipCmd);

#ifdef NATSEMI_DEBUG
	if (natsemi_debug)
		printf("natsemi_send: sending %d bytes\n", (int) length);
#endif

	/* set the transmit buffer descriptor and enable Transmit State Machine */
	txd.link = cpu_to_le32(0);
	txd.bufptr = cpu_to_le32(phys_to_bus((u32) packet));
	txd.cmdsts = cpu_to_le32(DescOwn | length);

	/* load Transmit Descriptor Register */
	OUTL(dev, phys_to_bus((u32) & txd), TxRingPtr);
#ifdef NATSEMI_DEBUG
	if (natsemi_debug)
	    printf("natsemi_send: TX descriptor register loaded with: %#08X\n",
	     INL(dev, TxRingPtr));
#endif
	/* restart the transmitter */
	OUTL(dev, TxOn, ChipCmd);

	for (i = 0;
	     (*res = le32_to_cpu(txd.cmdsts)) & DescOwn;
	     i++) {
		if (i >= TOUT_LOOP) {
			printf
			    ("%s: tx error buffer not ready: txd.cmdsts == %#X\n",
			     dev->name, tx_status);
			goto Done;
		}
	}

	if (!(tx_status & DescPktOK)) {
		printf("natsemi_send: Transmit error, Tx status %X.\n",
		       tx_status);
		goto Done;
	}

	status = 1;
      Done:
	return status;
}


static int
natsemi_poll(struct eth_device *dev)
{
	int retstat = 0;
	int length = 0;
	u32 rx_status = le32_to_cpu(rxd[cur_rx].cmdsts);

	if (!(rx_status & (u32) DescOwn))
		return retstat;
#ifdef NATSEMI_DEBUG
	if (natsemi_debug)
		printf("natsemi_poll: got a packet: cur_rx:%d, status:%X\n",
		       cur_rx, rx_status);
#endif
	length = (rx_status & DSIZE) - CRC_SIZE;

	if ((rx_status & (DescMore | DescPktOK | DescRxLong)) != DescPktOK) {
		printf
		    ("natsemi_poll: Corrupted packet received, buffer status = %X\n",
		     rx_status);
		retstat = 0;
	} else {		/* give packet to higher level routine */
		NetReceive((rxb + cur_rx * RX_BUF_SIZE), length);
		retstat = 1;
	}

	/* return the descriptor and buffer to receive ring */
	rxd[cur_rx].cmdsts = cpu_to_le32(RX_BUF_SIZE);
	rxd[cur_rx].bufptr = cpu_to_le32((u32) & rxb[cur_rx * RX_BUF_SIZE]);

	if (++cur_rx == NUM_RX_DESC)
		cur_rx = 0;

	/* re-enable the potentially idle receive state machine */
	OUTL(dev, RxOn, ChipCmd);

	return retstat;
}


static void
natsemi_disable(struct eth_device *dev)
{
	/* Disable interrupts using the mask. */
	OUTL(dev, 0, IntrMask);
	OUTL(dev, 0, IntrEnable);

	/* Stop the chip's Tx and Rx processes. */
	OUTL(dev, RxOff | TxOff, ChipCmd);

	/* Restore PME enable bit */
	OUTL(dev, SavedClkRun, ClkRun);
}
