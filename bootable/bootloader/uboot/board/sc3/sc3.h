

static void inline hcWriteWord (unsigned long base, unsigned int value,
				unsigned int offset)
{
	out_le16 ((volatile u16*)(base + 2), offset | 0x80);
	out_le16 ((volatile u16*)base, value);
}


static void inline hcWriteDWord (unsigned long base, unsigned long value,
				unsigned int offset)
{
	out_le16 ((volatile u16*)(base + 2), offset | 0x80);
	out_le16 ((volatile u16*)base, value);
	out_le16 ((volatile u16*)base, value >> 16);
}


static unsigned int inline hcReadWord (unsigned long base, unsigned int offset)
{
	out_le16 ((volatile u16*)(base + 2), offset);
	return (in_le16 ((volatile u16*)base));
}


static unsigned long inline hcReadDWord (unsigned long base, unsigned int offset)
{
	unsigned long val, val16;

	out_le16 ((volatile u16*)(base + 2), offset);
	val = in_le16((volatile u16*)base);
	val16 = in_le16((volatile u16*)base);
	return (val | (val16 << 16));
}

/* control and status registers isp1161 */
#define HcRevision		0x00
#define HcControl		0x01
#define HcCommandStatus		0x02
#define HcInterruptStatus	0x03
#define HcInterruptEnable	0x04
#define HcInterruptDisable	0x05
#define HcFmInterval		0x0D
#define HcFmRemaining		0x0E
#define HcFmNumber		0x0F
#define HcLSThreshold		0x11
#define HcRhDescriptorA		0x12
#define HcRhDescriptorB		0x13
#define HcRhStatus		0x14
#define HcRhPortStatus1		0x15
#define HcRhPortStatus2		0x16

#define HcHardwareConfiguration 0x20
#define HcDMAConfiguration	0x21
#define HcTransferCounter	0x22
#define HcuPInterrupt		0x24
#define HcuPInterruptEnable	0x25
#define HcChipID		0x27
#define HcScratch		0x28
#define HcSoftwareReset		0x29
#define HcITLBufferLength	0x2A
#define HcATLBufferLength	0x2B
#define HcBufferStatus		0x2C
#define HcReadBackITL0Length	0x2D
#define HcReadBackITL1Length	0x2E
#define HcITLBufferPort		0x40
#define HcATLBufferPort		0x41