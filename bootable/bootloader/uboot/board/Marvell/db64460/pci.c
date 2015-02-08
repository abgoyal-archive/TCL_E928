
/* PCI.c - PCI functions */


#include <common.h>
#include <pci.h>

#include "../include/pci.h"

#undef DEBUG
#undef IDE_SET_NATIVE_MODE
static unsigned int local_buses[] = { 0, 0 };

static const unsigned char pci_irq_swizzle[2][PCI_MAX_DEVICES] = {
	{0, 0, 0, 0, 0, 0, 0, 27, 27, [9 ... PCI_MAX_DEVICES - 1] = 0 },
	{0, 0, 0, 0, 0, 0, 0, 29, 29, [9 ... PCI_MAX_DEVICES - 1] = 0 },
};


#ifdef DEBUG
static const unsigned int pci_bus_list[] = { PCI_0_MODE, PCI_1_MODE };
static void gt_pci_bus_mode_display (PCI_HOST host)
{
	unsigned int mode;


	mode = (GTREGREAD (pci_bus_list[host]) & (BIT4 | BIT5)) >> 4;
	switch (mode) {
	case 0:
		printf ("PCI %d bus mode: Conventional PCI\n", host);
		break;
	case 1:
		printf ("PCI %d bus mode: 66 MHz PCIX\n", host);
		break;
	case 2:
		printf ("PCI %d bus mode: 100 MHz PCIX\n", host);
		break;
	case 3:
		printf ("PCI %d bus mode: 133 MHz PCIX\n", host);
		break;
	default:
		printf ("Unknown BUS %d\n", mode);
	}
}
#endif

static const unsigned int pci_p2p_configuration_reg[] = {
	PCI_0P2P_CONFIGURATION, PCI_1P2P_CONFIGURATION
};

static const unsigned int pci_configuration_address[] = {
	PCI_0CONFIGURATION_ADDRESS, PCI_1CONFIGURATION_ADDRESS
};

static const unsigned int pci_configuration_data[] = {
	PCI_0CONFIGURATION_DATA_VIRTUAL_REGISTER,
	PCI_1CONFIGURATION_DATA_VIRTUAL_REGISTER
};

static const unsigned int pci_error_cause_reg[] = {
	PCI_0ERROR_CAUSE, PCI_1ERROR_CAUSE
};

static const unsigned int pci_arbiter_control[] = {
	PCI_0ARBITER_CONTROL, PCI_1ARBITER_CONTROL
};

static const unsigned int pci_address_space_en[] = {
	PCI_0_BASE_ADDR_REG_ENABLE, PCI_1_BASE_ADDR_REG_ENABLE
};

static const unsigned int pci_snoop_control_base_0_low[] = {
	PCI_0SNOOP_CONTROL_BASE_0_LOW, PCI_1SNOOP_CONTROL_BASE_0_LOW
};
static const unsigned int pci_snoop_control_top_0[] = {
	PCI_0SNOOP_CONTROL_TOP_0, PCI_1SNOOP_CONTROL_TOP_0
};

static const unsigned int pci_access_control_base_0_low[] = {
	PCI_0ACCESS_CONTROL_BASE_0_LOW, PCI_1ACCESS_CONTROL_BASE_0_LOW
};
static const unsigned int pci_access_control_top_0[] = {
	PCI_0ACCESS_CONTROL_TOP_0, PCI_1ACCESS_CONTROL_TOP_0
};

static const unsigned int pci_scs_bank_size[2][4] = {
	{PCI_0SCS_0_BANK_SIZE, PCI_0SCS_1_BANK_SIZE,
	 PCI_0SCS_2_BANK_SIZE, PCI_0SCS_3_BANK_SIZE},
	{PCI_1SCS_0_BANK_SIZE, PCI_1SCS_1_BANK_SIZE,
	 PCI_1SCS_2_BANK_SIZE, PCI_1SCS_3_BANK_SIZE}
};

static const unsigned int pci_p2p_configuration[] = {
	PCI_0P2P_CONFIGURATION, PCI_1P2P_CONFIGURATION
};


void pciWriteConfigReg (PCI_HOST host, unsigned int regOffset,
			unsigned int pciDevNum, unsigned int data)
{
	volatile unsigned int DataForAddrReg;
	unsigned int functionNum;
	unsigned int busNum = 0;
	unsigned int addr;

	if (pciDevNum > 32)	/* illegal device Number */
		return;
	if (pciDevNum == SELF) {	/* configure our configuration space. */
		pciDevNum =
			(GTREGREAD (pci_p2p_configuration_reg[host]) >> 24) &
			0x1f;
		busNum = GTREGREAD (pci_p2p_configuration_reg[host]) &
			0xff0000;
	}
	functionNum = regOffset & 0x00000700;
	pciDevNum = pciDevNum << 11;
	regOffset = regOffset & 0xfc;
	DataForAddrReg =
		(regOffset | pciDevNum | functionNum | busNum) | BIT31;
	GT_REG_WRITE (pci_configuration_address[host], DataForAddrReg);
	GT_REG_READ (pci_configuration_address[host], &addr);
	if (addr != DataForAddrReg)
		return;
	GT_REG_WRITE (pci_configuration_data[host], data);
}

unsigned int pciReadConfigReg (PCI_HOST host, unsigned int regOffset,
			       unsigned int pciDevNum)
{
	volatile unsigned int DataForAddrReg;
	unsigned int data;
	unsigned int functionNum;
	unsigned int busNum = 0;

	if (pciDevNum > 32)	/* illegal device Number */
		return 0xffffffff;
	if (pciDevNum == SELF) {	/* configure our configuration space. */
		pciDevNum =
			(GTREGREAD (pci_p2p_configuration_reg[host]) >> 24) &
			0x1f;
		busNum = GTREGREAD (pci_p2p_configuration_reg[host]) &
			0xff0000;
	}
	functionNum = regOffset & 0x00000700;
	pciDevNum = pciDevNum << 11;
	regOffset = regOffset & 0xfc;
	DataForAddrReg =
		(regOffset | pciDevNum | functionNum | busNum) | BIT31;
	GT_REG_WRITE (pci_configuration_address[host], DataForAddrReg);
	GT_REG_READ (pci_configuration_address[host], &data);
	if (data != DataForAddrReg)
		return 0xffffffff;
	GT_REG_READ (pci_configuration_data[host], &data);
	return data;
}

void pciOverBridgeWriteConfigReg (PCI_HOST host,
				  unsigned int regOffset,
				  unsigned int pciDevNum,
				  unsigned int busNum, unsigned int data)
{
	unsigned int DataForReg;
	unsigned int functionNum;

	functionNum = regOffset & 0x00000700;
	pciDevNum = pciDevNum << 11;
	regOffset = regOffset & 0xff;
	busNum = busNum << 16;
	if (pciDevNum == SELF) {	/* This board */
		DataForReg = (regOffset | pciDevNum | functionNum) | BIT0;
	} else {
		DataForReg = (regOffset | pciDevNum | functionNum | busNum) |
			BIT31 | BIT0;
	}
	GT_REG_WRITE (pci_configuration_address[host], DataForReg);
	GT_REG_WRITE (pci_configuration_data[host], data);
}


unsigned int pciOverBridgeReadConfigReg (PCI_HOST host,
					 unsigned int regOffset,
					 unsigned int pciDevNum,
					 unsigned int busNum)
{
	unsigned int DataForReg;
	unsigned int data;
	unsigned int functionNum;

	functionNum = regOffset & 0x00000700;
	pciDevNum = pciDevNum << 11;
	regOffset = regOffset & 0xff;
	busNum = busNum << 16;
	if (pciDevNum == SELF) {	/* This board */
		DataForReg = (regOffset | pciDevNum | functionNum) | BIT31;
	} else {		/* agent on another bus */

		DataForReg = (regOffset | pciDevNum | functionNum | busNum) |
			BIT0 | BIT31;
	}
	GT_REG_WRITE (pci_configuration_address[host], DataForReg);
	GT_REG_READ (pci_configuration_data[host], &data);
	return data;
}


static unsigned int pciGetRegOffset (PCI_HOST host, PCI_REGION region)
{
	switch (host) {
	case PCI_HOST0:
		switch (region) {
		case PCI_IO:
			return PCI_0I_O_LOW_DECODE_ADDRESS;
		case PCI_REGION0:
			return PCI_0MEMORY0_LOW_DECODE_ADDRESS;
		case PCI_REGION1:
			return PCI_0MEMORY1_LOW_DECODE_ADDRESS;
		case PCI_REGION2:
			return PCI_0MEMORY2_LOW_DECODE_ADDRESS;
		case PCI_REGION3:
			return PCI_0MEMORY3_LOW_DECODE_ADDRESS;
		}
	case PCI_HOST1:
		switch (region) {
		case PCI_IO:
			return PCI_1I_O_LOW_DECODE_ADDRESS;
		case PCI_REGION0:
			return PCI_1MEMORY0_LOW_DECODE_ADDRESS;
		case PCI_REGION1:
			return PCI_1MEMORY1_LOW_DECODE_ADDRESS;
		case PCI_REGION2:
			return PCI_1MEMORY2_LOW_DECODE_ADDRESS;
		case PCI_REGION3:
			return PCI_1MEMORY3_LOW_DECODE_ADDRESS;
		}
	}
	return PCI_0MEMORY0_LOW_DECODE_ADDRESS;
}

static unsigned int pciGetRemapOffset (PCI_HOST host, PCI_REGION region)
{
	switch (host) {
	case PCI_HOST0:
		switch (region) {
		case PCI_IO:
			return PCI_0I_O_ADDRESS_REMAP;
		case PCI_REGION0:
			return PCI_0MEMORY0_ADDRESS_REMAP;
		case PCI_REGION1:
			return PCI_0MEMORY1_ADDRESS_REMAP;
		case PCI_REGION2:
			return PCI_0MEMORY2_ADDRESS_REMAP;
		case PCI_REGION3:
			return PCI_0MEMORY3_ADDRESS_REMAP;
		}
	case PCI_HOST1:
		switch (region) {
		case PCI_IO:
			return PCI_1I_O_ADDRESS_REMAP;
		case PCI_REGION0:
			return PCI_1MEMORY0_ADDRESS_REMAP;
		case PCI_REGION1:
			return PCI_1MEMORY1_ADDRESS_REMAP;
		case PCI_REGION2:
			return PCI_1MEMORY2_ADDRESS_REMAP;
		case PCI_REGION3:
			return PCI_1MEMORY3_ADDRESS_REMAP;
		}
	}
	return PCI_0MEMORY0_ADDRESS_REMAP;
}

unsigned int pciGetBaseAddress (PCI_HOST host, PCI_REGION region)
{
	unsigned int regBase;
	unsigned int regEnd;
	unsigned int regOffset = pciGetRegOffset (host, region);

	GT_REG_READ (regOffset, &regBase);
	GT_REG_READ (regOffset + 8, &regEnd);

	if (regEnd <= regBase)
		return 0xffffffff;	/* ERROR !!! */

	regBase = regBase << 16;
	return regBase;
}

bool pciMapSpace (PCI_HOST host, PCI_REGION region, unsigned int remapBase,
		  unsigned int bankBase, unsigned int bankLength)
{
	unsigned int low = 0xfff;
	unsigned int high = 0x0;
	unsigned int regOffset = pciGetRegOffset (host, region);
	unsigned int remapOffset = pciGetRemapOffset (host, region);

	if (bankLength != 0) {
		low = (bankBase >> 16) & 0xffff;
		high = ((bankBase + bankLength) >> 16) - 1;
	}

	GT_REG_WRITE (regOffset, low | (1 << 24));	/* no swapping */
	GT_REG_WRITE (regOffset + 8, high);

	if (bankLength != 0) {	/* must do AFTER writing maps */
		GT_REG_WRITE (remapOffset, remapBase >> 16);	/* sorry, 32 bits only.
								   dont support upper 32
								   in this driver */
	}
	return true;
}

unsigned int pciGetSpaceBase (PCI_HOST host, PCI_REGION region)
{
	unsigned int low;
	unsigned int regOffset = pciGetRegOffset (host, region);

	GT_REG_READ (regOffset, &low);
	return (low & 0xffff) << 16;
}

unsigned int pciGetSpaceSize (PCI_HOST host, PCI_REGION region)
{
	unsigned int low, high;
	unsigned int regOffset = pciGetRegOffset (host, region);

	GT_REG_READ (regOffset, &low);
	GT_REG_READ (regOffset + 8, &high);
	return ((high & 0xffff) + 1) << 16;
}


/* ronen - 7/Dec/03*/
void gtPciEnableInternalBAR (PCI_HOST host, PCI_INTERNAL_BAR pciBAR)
{
	RESET_REG_BITS (pci_address_space_en[host], BIT0 << pciBAR);
}

void gtPciDisableInternalBAR (PCI_HOST host, PCI_INTERNAL_BAR pciBAR)
{
	SET_REG_BITS (pci_address_space_en[host], BIT0 << pciBAR);
}

void pciMapMemoryBank (PCI_HOST host, MEMORY_BANK bank,
		       unsigned int pciDramBase, unsigned int pciDramSize)
{
	/*ronen different function for 3rd bank. */
	unsigned int offset = (bank < 2) ? bank * 8 : 0x100 + (bank - 2) * 8;

	pciDramBase = pciDramBase & 0xfffff000;
	pciDramBase = pciDramBase | (pciReadConfigReg (host,
						       PCI_SCS_0_BASE_ADDRESS
						       + offset,
						       SELF) & 0x00000fff);
	pciWriteConfigReg (host, PCI_SCS_0_BASE_ADDRESS + offset, SELF,
			   pciDramBase);
	if (pciDramSize == 0)
		pciDramSize++;
	GT_REG_WRITE (pci_scs_bank_size[host][bank], pciDramSize - 1);
	gtPciEnableInternalBAR (host, bank);
}

bool pciSetRegionFeatures (PCI_HOST host, PCI_ACCESS_REGIONS region,
			   unsigned int features, unsigned int baseAddress,
			   unsigned int regionLength)
{
	unsigned int accessLow;
	unsigned int accessHigh;
	unsigned int accessTop = baseAddress + regionLength;

	if (regionLength == 0) {	/* close the region. */
		pciDisableAccessRegion (host, region);
		return true;
	}
	/* base Address is store is bits [11:0] */
	accessLow = (baseAddress & 0xfff00000) >> 20;
	/* All the features are update according to the defines in pci.h (to be on
	   the safe side we disable bits: [11:0] */
	accessLow = accessLow | (features & 0xfffff000);
	/* write to the Low Access Region register */
	GT_REG_WRITE (pci_access_control_base_0_low[host] + 0x10 * region,
		      accessLow);

	accessHigh = (accessTop & 0xfff00000) >> 20;

	/* write to the High Access Region register */
	GT_REG_WRITE (pci_access_control_top_0[host] + 0x10 * region,
		      accessHigh - 1);
	return true;
}

void pciDisableAccessRegion (PCI_HOST host, PCI_ACCESS_REGIONS region)
{
	/* writing back the registers default values. */
	GT_REG_WRITE (pci_access_control_base_0_low[host] + 0x10 * region,
		      0x01001fff);
	GT_REG_WRITE (pci_access_control_top_0[host] + 0x10 * region, 0);
}

bool pciArbiterEnable (PCI_HOST host)
{
	unsigned int regData;

	GT_REG_READ (pci_arbiter_control[host], &regData);
	GT_REG_WRITE (pci_arbiter_control[host], regData | BIT31);
	return true;
}

bool pciArbiterDisable (PCI_HOST host)
{
	unsigned int regData;

	GT_REG_READ (pci_arbiter_control[host], &regData);
	GT_REG_WRITE (pci_arbiter_control[host], regData & 0x7fffffff);
	return true;
}

bool pciSetArbiterAgentsPriority (PCI_HOST host, PCI_AGENT_PRIO internalAgent,
				  PCI_AGENT_PRIO externalAgent0,
				  PCI_AGENT_PRIO externalAgent1,
				  PCI_AGENT_PRIO externalAgent2,
				  PCI_AGENT_PRIO externalAgent3,
				  PCI_AGENT_PRIO externalAgent4,
				  PCI_AGENT_PRIO externalAgent5)
{
	unsigned int regData;
	unsigned int writeData;

	GT_REG_READ (pci_arbiter_control[host], &regData);
	writeData = (internalAgent << 7) + (externalAgent0 << 8) +
		(externalAgent1 << 9) + (externalAgent2 << 10) +
		(externalAgent3 << 11) + (externalAgent4 << 12) +
		(externalAgent5 << 13);
	regData = (regData & 0xffffc07f) | writeData;
	GT_REG_WRITE (pci_arbiter_control[host], regData & regData);
	return true;
}

bool pciParkingDisable (PCI_HOST host, PCI_AGENT_PARK internalAgent,
			PCI_AGENT_PARK externalAgent0,
			PCI_AGENT_PARK externalAgent1,
			PCI_AGENT_PARK externalAgent2,
			PCI_AGENT_PARK externalAgent3,
			PCI_AGENT_PARK externalAgent4,
			PCI_AGENT_PARK externalAgent5)
{
	unsigned int regData;
	unsigned int writeData;

	GT_REG_READ (pci_arbiter_control[host], &regData);
	writeData = (internalAgent << 14) + (externalAgent0 << 15) +
		(externalAgent1 << 16) + (externalAgent2 << 17) +
		(externalAgent3 << 18) + (externalAgent4 << 19) +
		(externalAgent5 << 20);
	regData = (regData & ~(0x7f << 14)) | writeData;
	GT_REG_WRITE (pci_arbiter_control[host], regData);
	return true;
}

bool pciEnableBrokenAgentDetection (PCI_HOST host, unsigned char brokenValue)
{
	unsigned int data;
	unsigned int regData;

	if (brokenValue > 0xf)
		return false;	/* brokenValue must be 4 bit */
	data = brokenValue << 3;
	GT_REG_READ (pci_arbiter_control[host], &regData);
	regData = (regData & 0xffffff87) | data;
	GT_REG_WRITE (pci_arbiter_control[host], regData | BIT1);
	return true;
}

bool pciDisableBrokenAgentDetection (PCI_HOST host)
{
	unsigned int regData;

	GT_REG_READ (pci_arbiter_control[host], &regData);
	regData = regData & 0xfffffffd;
	GT_REG_WRITE (pci_arbiter_control[host], regData);
	return true;
}

bool pciP2PConfig (PCI_HOST host, unsigned int SecondBusLow,
		   unsigned int SecondBusHigh,
		   unsigned int busNum, unsigned int devNum)
{
	unsigned int regData;

	regData = (SecondBusLow & 0xff) | ((SecondBusHigh & 0xff) << 8) |
		((busNum & 0xff) << 16) | ((devNum & 0x1f) << 24);
	GT_REG_WRITE (pci_p2p_configuration[host], regData);
	return true;
}

bool pciSetRegionSnoopMode (PCI_HOST host, PCI_SNOOP_REGION region,
			    PCI_SNOOP_TYPE snoopType,
			    unsigned int baseAddress,
			    unsigned int regionLength)
{
	unsigned int snoopXbaseAddress;
	unsigned int snoopXtopAddress;
	unsigned int data;
	unsigned int snoopHigh = baseAddress + regionLength;

	if ((region > PCI_SNOOP_REGION3) || (snoopType > PCI_SNOOP_WB))
		return false;
	snoopXbaseAddress =
		pci_snoop_control_base_0_low[host] + 0x10 * region;
	snoopXtopAddress = pci_snoop_control_top_0[host] + 0x10 * region;
	if (regionLength == 0) {	/* closing the region */
		GT_REG_WRITE (snoopXbaseAddress, 0x0000ffff);
		GT_REG_WRITE (snoopXtopAddress, 0);
		return true;
	}
	baseAddress = baseAddress & 0xfff00000;	/* Granularity of 1MByte */
	data = (baseAddress >> 20) | snoopType << 12;
	GT_REG_WRITE (snoopXbaseAddress, data);
	snoopHigh = (snoopHigh & 0xfff00000) >> 20;
	GT_REG_WRITE (snoopXtopAddress, snoopHigh - 1);
	return true;
}

static int gt_read_config_dword (struct pci_controller *hose,
				 pci_dev_t dev, int offset, u32 * value)
{
	int bus = PCI_BUS (dev);

	if ((bus == local_buses[0]) || (bus == local_buses[1])) {
		*value = pciReadConfigReg ((PCI_HOST) hose->cfg_addr, offset,
					   PCI_DEV (dev));
	} else {
		*value = pciOverBridgeReadConfigReg ((PCI_HOST) hose->
						     cfg_addr, offset,
						     PCI_DEV (dev), bus);
	}

	return 0;
}

static int gt_write_config_dword (struct pci_controller *hose,
				  pci_dev_t dev, int offset, u32 value)
{
	int bus = PCI_BUS (dev);

	if ((bus == local_buses[0]) || (bus == local_buses[1])) {
		pciWriteConfigReg ((PCI_HOST) hose->cfg_addr, offset,
				   PCI_DEV (dev), value);
	} else {
		pciOverBridgeWriteConfigReg ((PCI_HOST) hose->cfg_addr,
					     offset, PCI_DEV (dev), bus,
					     value);
	}
	return 0;
}


static void gt_setup_ide (struct pci_controller *hose,
			  pci_dev_t dev, struct pci_config_table *entry)
{
	static const int ide_bar[] = { 8, 4, 8, 4, 0, 0 };
	u32 bar_response, bar_value;
	int bar;

	for (bar = 0; bar < 6; bar++) {
		/*ronen different function for 3rd bank. */
		unsigned int offset =
			(bar < 2) ? bar * 8 : 0x100 + (bar - 2) * 8;

		pci_write_config_dword (dev, PCI_BASE_ADDRESS_0 + offset,
					0x0);
		pci_read_config_dword (dev, PCI_BASE_ADDRESS_0 + offset,
				       &bar_response);

		pciauto_region_allocate (bar_response &
					 PCI_BASE_ADDRESS_SPACE_IO ? hose->
					 pci_io : hose->pci_mem, ide_bar[bar],
					 &bar_value);

		pci_write_config_dword (dev, PCI_BASE_ADDRESS_0 + bar * 4,
					bar_value);
	}
}


/* TODO BJW: Change this for DB64360. This was pulled from the EV64260  */
/* and is curently not called *. */
#if 0
static void gt_fixup_irq (struct pci_controller *hose, pci_dev_t dev)
{
	unsigned char pin, irq;

	pci_read_config_byte (dev, PCI_INTERRUPT_PIN, &pin);

	if (pin == 1) {		/* only allow INT A */
		irq = pci_irq_swizzle[(PCI_HOST) hose->
				      cfg_addr][PCI_DEV (dev)];
		if (irq)
			pci_write_config_byte (dev, PCI_INTERRUPT_LINE, irq);
	}
}
#endif

struct pci_config_table gt_config_table[] = {
	{PCI_ANY_ID, PCI_ANY_ID, PCI_CLASS_STORAGE_IDE,
	 PCI_ANY_ID, PCI_ANY_ID, PCI_ANY_ID, gt_setup_ide},

	{}
};

struct pci_controller pci0_hose = {
/*    fixup_irq: gt_fixup_irq, */
	config_table:gt_config_table,
};

struct pci_controller pci1_hose = {
/*    fixup_irq: gt_fixup_irq, */
	config_table:gt_config_table,
};

void pci_init_board (void)
{
	unsigned int command;

#ifdef DEBUG
	gt_pci_bus_mode_display (PCI_HOST0);
#endif

	pci0_hose.first_busno = 0;
	pci0_hose.last_busno = 0xff;
	local_buses[0] = pci0_hose.first_busno;

	/* PCI memory space */
	pci_set_region (pci0_hose.regions + 0,
			CONFIG_SYS_PCI0_0_MEM_SPACE,
			CONFIG_SYS_PCI0_0_MEM_SPACE,
			CONFIG_SYS_PCI0_MEM_SIZE, PCI_REGION_MEM);

	/* PCI I/O space */
	pci_set_region (pci0_hose.regions + 1,
			CONFIG_SYS_PCI0_IO_SPACE_PCI,
			CONFIG_SYS_PCI0_IO_SPACE, CONFIG_SYS_PCI0_IO_SIZE, PCI_REGION_IO);

	pci_set_ops (&pci0_hose,
		     pci_hose_read_config_byte_via_dword,
		     pci_hose_read_config_word_via_dword,
		     gt_read_config_dword,
		     pci_hose_write_config_byte_via_dword,
		     pci_hose_write_config_word_via_dword,
		     gt_write_config_dword);
	pci0_hose.region_count = 2;

	pci0_hose.cfg_addr = (unsigned int *) PCI_HOST0;

	pci_register_hose (&pci0_hose);
	pciArbiterEnable (PCI_HOST0);
	pciParkingDisable (PCI_HOST0, 1, 1, 1, 1, 1, 1, 1);
	command = pciReadConfigReg (PCI_HOST0, PCI_COMMAND, SELF);
	command |= PCI_COMMAND_MASTER;
	pciWriteConfigReg (PCI_HOST0, PCI_COMMAND, SELF, command);
	command = pciReadConfigReg (PCI_HOST0, PCI_COMMAND, SELF);
	command |= PCI_COMMAND_MEMORY;
	pciWriteConfigReg (PCI_HOST0, PCI_COMMAND, SELF, command);

	pci0_hose.last_busno = pci_hose_scan (&pci0_hose);

#ifdef DEBUG
	gt_pci_bus_mode_display (PCI_HOST1);
#endif
	pci1_hose.first_busno = pci0_hose.last_busno + 1;
	pci1_hose.last_busno = 0xff;
	pci1_hose.current_busno = pci1_hose.first_busno;
	local_buses[1] = pci1_hose.first_busno;

	/* PCI memory space */
	pci_set_region (pci1_hose.regions + 0,
			CONFIG_SYS_PCI1_0_MEM_SPACE,
			CONFIG_SYS_PCI1_0_MEM_SPACE,
			CONFIG_SYS_PCI1_MEM_SIZE, PCI_REGION_MEM);

	/* PCI I/O space */
	pci_set_region (pci1_hose.regions + 1,
			CONFIG_SYS_PCI1_IO_SPACE_PCI,
			CONFIG_SYS_PCI1_IO_SPACE, CONFIG_SYS_PCI1_IO_SIZE, PCI_REGION_IO);

	pci_set_ops (&pci1_hose,
		     pci_hose_read_config_byte_via_dword,
		     pci_hose_read_config_word_via_dword,
		     gt_read_config_dword,
		     pci_hose_write_config_byte_via_dword,
		     pci_hose_write_config_word_via_dword,
		     gt_write_config_dword);

	pci1_hose.region_count = 2;

	pci1_hose.cfg_addr = (unsigned int *) PCI_HOST1;

	pci_register_hose (&pci1_hose);

	pciArbiterEnable (PCI_HOST1);
	pciParkingDisable (PCI_HOST1, 1, 1, 1, 1, 1, 1, 1);

	command = pciReadConfigReg (PCI_HOST1, PCI_COMMAND, SELF);
	command |= PCI_COMMAND_MASTER;
	pciWriteConfigReg (PCI_HOST1, PCI_COMMAND, SELF, command);

	pci1_hose.last_busno = pci_hose_scan (&pci1_hose);

	command = pciReadConfigReg (PCI_HOST1, PCI_COMMAND, SELF);
	command |= PCI_COMMAND_MEMORY;
	pciWriteConfigReg (PCI_HOST1, PCI_COMMAND, SELF, command);

}