
#include <common.h>
#include "biosemui.h"
#include <malloc.h>

/* Length of the BIOS image */
#define MAX_BIOSLEN	    (128 * 1024L)

/* Define some useful types and macros */
#define true		    1
#define false		    0

/* Place to save PCI BAR's that we change and later restore */
static u32 saveROMBaseAddress;
static u32 saveBaseAddress10;
static u32 saveBaseAddress14;
static u32 saveBaseAddress18;
static u32 saveBaseAddress20;

static void PCI_doBIOSPOST(pci_dev_t pcidev, BE_VGAInfo * VGAInfo)
{
	RMREGS regs;
	RMSREGS sregs;

	/* Determine the value to store in AX for BIOS POST. Per the PCI specs,
	 AH must contain the bus and AL must contain the devfn, encoded as
	 (dev << 3) | fn
	 */
	memset(&regs, 0, sizeof(regs));
	memset(&sregs, 0, sizeof(sregs));
	regs.x.ax = ((int)PCI_BUS(pcidev) << 8) |
	    ((int)PCI_DEV(pcidev) << 3) | (int)PCI_FUNC(pcidev);

	/*Setup the X86 emulator for the VGA BIOS*/
	BE_setVGA(VGAInfo);

	/*Execute the BIOS POST code*/
	BE_callRealMode(0xC000, 0x0003, &regs, &sregs);

	/*Cleanup and exit*/
	BE_getVGA(VGAInfo);
}

static u32 PCI_findBIOSAddr(pci_dev_t pcidev, int *bar)
{
	u32 base, size;

	for (*bar = 0x10; *bar <= 0x14; (*bar) += 4) {
		pci_read_config_dword(pcidev, *bar, &base);
		if (!(base & 0x1)) {
			pci_write_config_dword(pcidev, *bar, 0xFFFFFFFF);
			pci_read_config_dword(pcidev, *bar, &size);
			size = ~(size & ~0xFF) + 1;
			if (size >= MAX_BIOSLEN)
				return base & ~0xFF;
		}
	}
	return 0;
}

static void PCI_fixupIObase(pci_dev_t pcidev, int reg, u32 * base)
{
	if ((*base & 0x1) && (*base > 0xFFFE)) {
		*base &= 0xFFFF;
		pci_write_config_dword(pcidev, reg, *base);

	}
}

void *PCI_mapBIOSImage(pci_dev_t pcidev)
{
	u32 BIOSImageBus;
	int BIOSImageBAR;
	u8 *BIOSImage;

	/*Save PCI BAR registers that might get changed*/
	pci_read_config_dword(pcidev, PCI_ROM_ADDRESS, &saveROMBaseAddress);
	pci_read_config_dword(pcidev, PCI_BASE_ADDRESS_0, &saveBaseAddress10);
	pci_read_config_dword(pcidev, PCI_BASE_ADDRESS_1, &saveBaseAddress14);
	pci_read_config_dword(pcidev, PCI_BASE_ADDRESS_2, &saveBaseAddress18);
	pci_read_config_dword(pcidev, PCI_BASE_ADDRESS_4, &saveBaseAddress20);

	/*Fix up I/O base registers to less than 64K */
	if(saveBaseAddress14 != 0)
		PCI_fixupIObase(pcidev, PCI_BASE_ADDRESS_1, &saveBaseAddress14);
	else
		PCI_fixupIObase(pcidev, PCI_BASE_ADDRESS_4, &saveBaseAddress20);

	/* Some cards have problems that stop us from being able to read the
	 BIOS image from the ROM BAR. To fix this we have to do some chipset
	 specific programming for different cards to solve this problem.
	*/

	BIOSImageBus = PCI_findBIOSAddr(pcidev, &BIOSImageBAR);
	if (BIOSImageBus == 0) {
		printf("Find bios addr error\n");
		return NULL;
	}

	BIOSImage = pci_bus_to_virt(pcidev, BIOSImageBus,
				    PCI_REGION_MEM, 0, MAP_NOCACHE);

	/*Change the PCI BAR registers to map it onto the bus.*/
	pci_write_config_dword(pcidev, BIOSImageBAR, 0);
	pci_write_config_dword(pcidev, PCI_ROM_ADDRESS, BIOSImageBus | 0x1);

	udelay(1);

	/*Check that the BIOS image is valid. If not fail, or return the
	 compiled in BIOS image if that option was enabled
	 */
	if (BIOSImage[0] != 0x55 || BIOSImage[1] != 0xAA || BIOSImage[2] == 0) {
		return NULL;
	}

	return BIOSImage;
}

void PCI_unmapBIOSImage(pci_dev_t pcidev, void *BIOSImage)
{
	pci_write_config_dword(pcidev, PCI_ROM_ADDRESS, saveROMBaseAddress);
	pci_write_config_dword(pcidev, PCI_BASE_ADDRESS_0, saveBaseAddress10);
	pci_write_config_dword(pcidev, PCI_BASE_ADDRESS_1, saveBaseAddress14);
	pci_write_config_dword(pcidev, PCI_BASE_ADDRESS_2, saveBaseAddress18);
	pci_write_config_dword(pcidev, PCI_BASE_ADDRESS_4, saveBaseAddress20);
}

static int PCI_postController(pci_dev_t pcidev, BE_VGAInfo * VGAInfo)
{
	u32 BIOSImageLen;
	uchar *mappedBIOS;
	uchar *copyOfBIOS;

	/*Allocate memory to store copy of BIOS from display controller*/
	if ((mappedBIOS = PCI_mapBIOSImage(pcidev)) == NULL) {
		printf("videoboot: Video ROM failed to map!\n");
		return false;
	}

	BIOSImageLen = mappedBIOS[2] * 512;

	if ((copyOfBIOS = malloc(BIOSImageLen)) == NULL) {
		printf("videoboot: Out of memory!\n");
		return false;
	}
	memcpy(copyOfBIOS, mappedBIOS, BIOSImageLen);

	PCI_unmapBIOSImage(pcidev, mappedBIOS);

	/*Save information in VGAInfo structure*/
	VGAInfo->function = PCI_FUNC(pcidev);
	VGAInfo->device = PCI_DEV(pcidev);
	VGAInfo->bus = PCI_BUS(pcidev);
	VGAInfo->pcidev = pcidev;
	VGAInfo->BIOSImage = copyOfBIOS;
	VGAInfo->BIOSImageLen = BIOSImageLen;

	/*Now execute the BIOS POST for the device*/
	if (copyOfBIOS[0] != 0x55 || copyOfBIOS[1] != 0xAA) {
		printf("videoboot: Video ROM image is invalid!\n");
		return false;
	}

	PCI_doBIOSPOST(pcidev, VGAInfo);

	/*Reset the size of the BIOS image to the final size*/
	VGAInfo->BIOSImageLen = copyOfBIOS[2] * 512;
	return true;
}

int BootVideoCardBIOS(pci_dev_t pcidev, BE_VGAInfo ** pVGAInfo, int cleanUp)
{
	BE_VGAInfo *VGAInfo;

	printf("videoboot: Booting PCI video card bus %d, function %d, device %d\n",
	     PCI_BUS(pcidev), PCI_FUNC(pcidev), PCI_DEV(pcidev));

	/*Initialise the x86 BIOS emulator*/
	if ((VGAInfo = malloc(sizeof(*VGAInfo))) == NULL) {
		printf("videoboot: Out of memory!\n");
		return false;
	}
	memset(VGAInfo, 0, sizeof(*VGAInfo));
	BE_init(0, 65536, VGAInfo, 0);

	/*Post all the display controller BIOS'es*/
	if (!PCI_postController(pcidev, VGAInfo))
		return false;

	/*Cleanup and exit the emulator if requested. If the BIOS emulator
	is needed after booting the card, we will not call BE_exit and
	leave it enabled for further use (ie: VESA driver etc).
	*/
	if (cleanUp) {
		BE_exit();
		if (VGAInfo->BIOSImage)
			free(VGAInfo->BIOSImage);
		free(VGAInfo);
		VGAInfo = NULL;
	}
	/*Return VGA info pointer if the caller requested it*/
	if (pVGAInfo)
		*pVGAInfo = VGAInfo;
	return true;
}
