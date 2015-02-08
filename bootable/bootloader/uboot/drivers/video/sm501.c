


#include <common.h>

#include <video_fb.h>
#include <sm501.h>

#define read8(ptrReg)                \
    *(volatile unsigned char *)(sm501.isaBase + ptrReg)

#define write8(ptrReg,value) \
    *(volatile unsigned char *)(sm501.isaBase + ptrReg) = value

#define read16(ptrReg) \
    (*(volatile unsigned short *)(sm501.isaBase + ptrReg))

#define write16(ptrReg,value) \
    (*(volatile unsigned short *)(sm501.isaBase + ptrReg) = value)

#define read32(ptrReg) \
    (*(volatile unsigned int *)(sm501.isaBase + ptrReg))

#define write32(ptrReg, value) \
    (*(volatile unsigned int *)(sm501.isaBase + ptrReg) = value)

GraphicDevice sm501;

static void SmiSetRegs (void)
{
	/*
	 * The content of the chipset register depends on the board (clocks,
	 * ...)
	 */
	const SMI_REGS *preg = board_get_regs ();
	while (preg->Index) {
		write32 (preg->Index, preg->Value);
		/*
		 * Insert a delay between
		 */
		udelay (1000);
		preg ++;
	}
}

void *video_hw_init (void)
{
	unsigned int *vm, i;

	memset (&sm501, 0, sizeof (GraphicDevice));

	/*
	 * Initialization of the access to the graphic chipset Retreive base
	 * address of the chipset (see board/RPXClassic/eccx.c)
	 */
	if ((sm501.isaBase = board_video_init ()) == 0) {
		return (NULL);
	}

	if ((sm501.frameAdrs = board_video_get_fb ()) == 0) {
		return (NULL);
	}

	sm501.winSizeX = board_get_width ();
	sm501.winSizeY = board_get_height ();

#if defined(CONFIG_VIDEO_SM501_8BPP)
	sm501.gdfIndex = GDF__8BIT_INDEX;
	sm501.gdfBytesPP = 1;

#elif defined(CONFIG_VIDEO_SM501_16BPP)
	sm501.gdfIndex = GDF_16BIT_565RGB;
	sm501.gdfBytesPP = 2;

#elif defined(CONFIG_VIDEO_SM501_32BPP)
	sm501.gdfIndex = GDF_32BIT_X888RGB;
	sm501.gdfBytesPP = 4;
#else
#error Unsupported SM501 BPP
#endif

	sm501.memSize = sm501.winSizeX * sm501.winSizeY * sm501.gdfBytesPP;

	/* Load Smi registers */
	SmiSetRegs ();

	/* (see board/RPXClassic/RPXClassic.c) */
	board_validate_screen (sm501.isaBase);

	/* Clear video memory */
	i = sm501.memSize/4;
	vm = (unsigned int *)sm501.frameAdrs;
	while(i--)
		*vm++ = 0;

	return (&sm501);
}

void video_set_lut (
	unsigned int index,           /* color number */
	unsigned char r,              /* red */
	unsigned char g,              /* green */
	unsigned char b               /* blue */
	)
{
}
