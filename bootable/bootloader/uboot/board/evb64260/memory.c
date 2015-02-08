
/* Memory.c - Memory mappings and remapping functions */

/* Copyright - Galileo technology. */


#include <galileo/core.h>
#include <galileo/memory.h>

static unsigned long memoryGetBankRegOffset(MEMORY_BANK bank)
{
    switch (bank)
    {
	case BANK0:
	    return SCS_0_LOW_DECODE_ADDRESS;
	case BANK1:
	    return SCS_1_LOW_DECODE_ADDRESS;
	case BANK2:
	    return SCS_2_LOW_DECODE_ADDRESS;
	case BANK3:
	    return SCS_3_LOW_DECODE_ADDRESS;
    }
    return SCS_0_LOW_DECODE_ADDRESS; /* default value */
}

unsigned int memoryGetBankBaseAddress(MEMORY_BANK bank)
{
    unsigned int base;
    unsigned int regOffset=memoryGetBankRegOffset(bank);

    GT_REG_READ(regOffset,&base);
    base = base << 20;
    return base;
}

static unsigned int memoryGetDeviceRegOffset(DEVICE device)
{
    switch (device)
    {
	case DEVICE0:
	    return CS_0_LOW_DECODE_ADDRESS;
	case DEVICE1:
	    return CS_1_LOW_DECODE_ADDRESS;
	case DEVICE2:
	    return CS_2_LOW_DECODE_ADDRESS;
	case DEVICE3:
	    return CS_3_LOW_DECODE_ADDRESS;
	case BOOT_DEVICE:
	    return BOOTCS_LOW_DECODE_ADDRESS;
    }
    return CS_0_LOW_DECODE_ADDRESS; /* default value */
}

unsigned int memoryGetDeviceBaseAddress(DEVICE device)
{
    unsigned int regBase;
    unsigned int regEnd;
    unsigned int regOffset=memoryGetDeviceRegOffset(device);

    GT_REG_READ(regOffset, &regBase);
    GT_REG_READ(regOffset+8, &regEnd);

    if(regEnd<=regBase) return 0xffffffff;	/* ERROR !!! */

    regBase = regBase << 20;
    return regBase;
}

unsigned int memoryGetBankSize(MEMORY_BANK bank)
{
    unsigned int size,base;
    unsigned int highValue;
    unsigned int highAddress=memoryGetBankRegOffset(bank)+8;

    base = memoryGetBankBaseAddress(bank);
    GT_REG_READ(highAddress,&highValue);
    highValue = (highValue + 1) << 20;
    if(base > highValue)
	size=0;
    else
	size = highValue - base;
    return size;
}

unsigned int memoryGetDeviceSize(DEVICE device)
{
    unsigned int size,base;
    unsigned int highValue;
    unsigned int highAddress=memoryGetDeviceRegOffset(device)+8;

    base = memoryGetDeviceBaseAddress(device);
    GT_REG_READ(highAddress,&highValue);
    if (highValue == 0xfff)
    {
	size = (~base) + 1;	/* what the heck is this? */
	return size;
    }
    else
	highValue = (highValue + 1) << 20;

    if(base > highValue)
	size=0;
    else
	size = highValue - base;
    return size;
}

unsigned int memoryGetDeviceWidth(DEVICE device)
{
    unsigned int width;
    unsigned int regValue;

    GT_REG_READ(DEVICE_BANK0PARAMETERS + device*4,&regValue);
    width =  (regValue & 0x00300000) >> 20;
    switch (width)
    {
	case 0:
	    return 1;
	case 1:
	    return 2;
	case 2:
	    return 4;
	case 3:
	    return 8;
	default:
	    return 0;
    }
}

bool memoryMapBank(MEMORY_BANK bank, unsigned int bankBase,unsigned int bankLength)
{
    unsigned int low=0xfff;
    unsigned int high=0x0;
    unsigned int regOffset=memoryGetBankRegOffset(bank);

    if(bankLength!=0) {
	low = (bankBase >> 20) & 0xffff;
	high=((bankBase+bankLength)>>20)-1;
    }

#ifdef DEBUG
    {
	unsigned int oldLow, oldHigh;
	GT_REG_READ(regOffset,&oldLow);
	GT_REG_READ(regOffset+8,&oldHigh);

	printf("b%d %x-%x->%x-%x\n", bank, oldLow, oldHigh, low, high);
    }
#endif

    GT_REG_WRITE(regOffset,low);
    GT_REG_WRITE(regOffset+8,high);

    return true;
}
bool memoryMapDeviceSpace(DEVICE device, unsigned int deviceBase,unsigned int deviceLength)
{
    /* TODO: what are appropriate "unmapped" values? */
    unsigned int low=0xfff;
    unsigned int high=0x0;
    unsigned int regOffset=memoryGetDeviceRegOffset(device);

    if(deviceLength != 0) {
	low=deviceBase>>20;
	high=((deviceBase+deviceLength)>>20)-1;
    } else {
	/* big problems in here... */
	/* this will HANG */
    }

    GT_REG_WRITE(regOffset,low);
    GT_REG_WRITE(regOffset+8,high);

    return true;
}


bool memoryMapInternalRegistersSpace(unsigned int internalRegBase)
{
    unsigned int currentValue;
    unsigned int internalValue = internalRegBase;

    internalRegBase = (internalRegBase >> 20);
    GT_REG_READ(INTERNAL_SPACE_DECODE,&currentValue);
    internalRegBase = (currentValue & 0xffff0000) | internalRegBase;
    GT_REG_WRITE(INTERNAL_SPACE_DECODE,internalRegBase);
    INTERNAL_REG_BASE_ADDR = internalValue;
    return true;
}

unsigned int memoryGetInternalRegistersSpace(void)
{
    return INTERNAL_REG_BASE_ADDR;
}

bool memorySetProtectRegion(MEMORY_PROTECT_REGION region,
			    MEMORY_ACCESS memAccess,
			    MEMORY_ACCESS_WRITE memWrite,
			    MEMORY_CACHE_PROTECT cacheProtection,
			    unsigned int baseAddress,
			    unsigned int regionLength)
{
    unsigned int protectHigh = baseAddress + regionLength;

    if(regionLength == 0) /* closing the region */
    {
	GT_REG_WRITE(CPU_LOW_PROTECT_ADDRESS_0 + 0x10*region,0x0000ffff);
	GT_REG_WRITE(CPU_HIGH_PROTECT_ADDRESS_0 + 0x10*region,0);
	return true;
    }
    baseAddress =  (baseAddress & 0xfff00000) >> 20;
    baseAddress = baseAddress | memAccess << 16 |  memWrite << 17
		     | cacheProtection << 18;
    GT_REG_WRITE(CPU_LOW_PROTECT_ADDRESS_0 + 0x10*region,baseAddress);
    protectHigh = (protectHigh & 0xfff00000) >> 20;
    GT_REG_WRITE(CPU_HIGH_PROTECT_ADDRESS_0 + 0x10*region,protectHigh - 1);
    return true;
}

bool memorySetRegionSnoopMode(MEMORY_SNOOP_REGION region,
			      MEMORY_SNOOP_TYPE snoopType,
			      unsigned int baseAddress,
			      unsigned int regionLength)
{
    unsigned int snoopXbaseAddress;
    unsigned int snoopXtopAddress;
    unsigned int data;
    unsigned int snoopHigh = baseAddress + regionLength;

    if( (region > MEM_SNOOP_REGION3) || (snoopType > MEM_SNOOP_WB) )
	return false;
    snoopXbaseAddress = SNOOP_BASE_ADDRESS_0 + 0x10 * region;
    snoopXtopAddress = SNOOP_TOP_ADDRESS_0 + 0x10 * region;
    if(regionLength == 0) /* closing the region */
    {
	GT_REG_WRITE(snoopXbaseAddress,0x0000ffff);
	GT_REG_WRITE(snoopXtopAddress,0);
	return true;
    }
    baseAddress = baseAddress & 0xffff0000;
    data = (baseAddress >> 16) | snoopType << 16;
    GT_REG_WRITE(snoopXbaseAddress,data);
    snoopHigh = (snoopHigh & 0xfff00000) >> 20;
    GT_REG_WRITE(snoopXtopAddress,snoopHigh - 1);
    return true;
}

bool memoryRemapAddress(unsigned int remapReg, unsigned int remapValue)
{
    unsigned int valueForReg;
    valueForReg = (remapValue & 0xfff00000) >> 20;
    GT_REG_WRITE(remapReg, valueForReg);
    return true;
}

bool memoryGetDeviceParam(DEVICE_PARAM *deviceParam, DEVICE deviceNum)
{
    unsigned int valueOfReg;
    unsigned int calcData;

    GT_REG_READ(DEVICE_BANK0PARAMETERS + 4 * deviceNum, &valueOfReg);
    calcData = (0x7 & valueOfReg) + ((0x400000 & valueOfReg) >> 19);
    deviceParam -> turnOff = calcData;          /* Turn Off */

    calcData = ((0x78 & valueOfReg) >> 3) + ((0x800000 & valueOfReg) >> 19);
    deviceParam -> acc2First = calcData;        /* Access To First */

    calcData = ((0x780 & valueOfReg) >> 7) + ((0x1000000 & valueOfReg) >> 20);
    deviceParam -> acc2Next = calcData;         /* Access To Next */

    calcData = ((0x3800 & valueOfReg) >> 11) + ((0x2000000 & valueOfReg) >> 22);
    deviceParam -> ale2Wr = calcData;           /* Ale To Write */

    calcData = ((0x1c000 & valueOfReg) >> 14) + ((0x4000000 & valueOfReg) >> 23);
    deviceParam -> wrLow = calcData;            /* Write Active */

    calcData = ((0xe0000 & valueOfReg) >> 17) + ((0x8000000 & valueOfReg) >> 24);
    deviceParam -> wrHigh = calcData;           /* Write High */

    calcData = ((0x300000 & valueOfReg) >> 20);
    switch (calcData)
    {
    case 0:
	deviceParam -> deviceWidth = 1;         /* one Byte - 8-bit */
	break;
    case 1:
	deviceParam -> deviceWidth = 2;         /* two Bytes - 16-bit */
	break;
    case 2:
	deviceParam -> deviceWidth = 4;         /* four Bytes - 32-bit */
	break;
    case 3:
	deviceParam -> deviceWidth = 8;         /* eight Bytes - 64-bit */
	break;
    default:
	deviceParam -> deviceWidth = 1;
	break;
    }
    return true;
}

bool memorySetDeviceParam(DEVICE_PARAM *deviceParam, DEVICE deviceNum)
{
    unsigned int valueForReg;

    if((deviceParam -> turnOff >= 0xf) || (deviceParam -> acc2First >= 0x1f) ||
       (deviceParam -> acc2Next >= 0x1f) || (deviceParam -> ale2Wr >= 0xf) ||
	(deviceParam -> wrLow >= 0xf) || (deviceParam -> wrHigh >= 0xf))
	return false;
    valueForReg = (((deviceParam -> turnOff) & 0x7) |
		   (((deviceParam -> turnOff) & 0x8) << 19) |
		   (((deviceParam -> acc2First) & 0xf) << 3) |
		   (((deviceParam -> acc2First) & 0x10) << 19) |
		   (((deviceParam -> acc2Next) & 0xf) << 7) |
		   (((deviceParam -> acc2Next) & 0x10) << 20) |
		   (((deviceParam -> ale2Wr) & 0x7) << 11) |
		   (((deviceParam -> ale2Wr) & 0xf) << 22) |
		   (((deviceParam -> wrLow) & 0x7) << 14) |
		   (((deviceParam -> wrLow) & 0xf) << 23) |
		   (((deviceParam -> wrHigh) & 0x7) << 17) |
		   (((deviceParam -> wrHigh) & 0xf) << 24));
    /* insert the device width: */
    switch(deviceParam->deviceWidth)
    {
    case 1:
	valueForReg = valueForReg | _8BIT;
	break;
    case 2:
	valueForReg = valueForReg | _16BIT;
	break;
    case 4:
	valueForReg = valueForReg | _32BIT;
	break;
    case 8:
	valueForReg = valueForReg | _64BIT;
	break;
    default:
	valueForReg = valueForReg | _8BIT;
	break;
    }
    GT_REG_WRITE(DEVICE_BANK0PARAMETERS + 4 * deviceNum, valueForReg);
    return true;
}
