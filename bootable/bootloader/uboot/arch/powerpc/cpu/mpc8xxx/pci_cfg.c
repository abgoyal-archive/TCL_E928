

#include <common.h>
#include <asm/fsl_law.h>
#include <pci.h>

struct pci_info {
	u32	cfg;
};


#if defined(CONFIG_MPC8540) || defined(CONFIG_MPC8560)
static struct pci_info pci_config_info[] =
{
	[LAW_TRGT_IF_PCI] = {
		.cfg =   0,
	},
};
#elif defined(CONFIG_MPC8541) || defined(CONFIG_MPC8555)
static struct pci_info pci_config_info[] =
{
	[LAW_TRGT_IF_PCI] = {
		.cfg =   0,
	},
};
#elif defined(CONFIG_MPC8536)
static struct pci_info pci_config_info[] =
{
};
#elif defined(CONFIG_MPC8544)
static struct pci_info pci_config_info[] =
{
	[LAW_TRGT_IF_PCI] = {
		.cfg =   0,
	},
	[LAW_TRGT_IF_PCIE_1] = {
		.cfg =   (1 << 2) | (1 << 3) | (1 << 4) | (1 << 5) |
			 (1 << 6) | (1 << 7),
	},
	[LAW_TRGT_IF_PCIE_2] = {
		.cfg =   (1 << 4) | (1 << 5) | (1 << 6) | (1 << 7),
	},
	[LAW_TRGT_IF_PCIE_3] = {
		.cfg =   (1 << 6) | (1 << 7),
	},
};
#elif defined(CONFIG_MPC8548)
static struct pci_info pci_config_info[] =
{
	[LAW_TRGT_IF_PCI_1] = {
		.cfg =   0,
	},
	[LAW_TRGT_IF_PCI_2] = {
		.cfg =   0,
	},
	/* PCI_2 is always host and we dont use iosel to determine enable/disable */
	[LAW_TRGT_IF_PCIE_1] = {
		.cfg =   (1 << 3) | (1 << 4) | (1 << 7),
	},
};
#elif defined(CONFIG_MPC8568)
static struct pci_info pci_config_info[] =
{
	[LAW_TRGT_IF_PCI] = {
		.cfg =   0,
	},
	[LAW_TRGT_IF_PCIE_1] = {
		.cfg =   (1 << 3) | (1 << 4) | (1 << 7),
	},
};
#elif defined(CONFIG_MPC8569)
static struct pci_info pci_config_info[] =
{
	[LAW_TRGT_IF_PCIE_1] = {
		.cfg =   (1 << 0) | (1 << 4) | (1 << 5) | (1 << 6) | (1 << 7) |
			 (1 << 8) | (1 << 0xc) | (1 << 0xf),
	},
};
#elif defined(CONFIG_MPC8572)
static struct pci_info pci_config_info[] =
{
	[LAW_TRGT_IF_PCIE_1] = {
		.cfg =   (1 << 2) | (1 << 3) | (1 << 7) |
			 (1 << 0xb) | (1 << 0xc) | (1 << 0xf),
	},
	[LAW_TRGT_IF_PCIE_2] = {
		.cfg =   (1 << 3) | (1 << 7),
	},
	[LAW_TRGT_IF_PCIE_3] = {
		.cfg =   (1 << 7),
	},
};
#elif defined(CONFIG_MPC8610)
static struct pci_info pci_config_info[] =
{
	[LAW_TRGT_IF_PCI_1] = {
		.cfg =   0,
	},
	[LAW_TRGT_IF_PCIE_1] = {
		.cfg =   (1 << 1) | (1 << 4),
	},
	[LAW_TRGT_IF_PCIE_2] = {
		.cfg =   (1 << 0) | (1 << 4),
	},
};
#elif defined(CONFIG_MPC8641)
static struct pci_info pci_config_info[] =
{
	[LAW_TRGT_IF_PCIE_1] = {
		.cfg =   (1 << 2) | (1 << 3) | (1 << 5) | (1 << 6) |
			 (1 << 7) | (1 << 0xe) | (1 << 0xf),
	},
};
#elif defined(CONFIG_P1011) || defined(CONFIG_P1020) || \
      defined(CONFIG_P1012) || defined(CONFIG_P1021)
static struct pci_info pci_config_info[] =
{
	[LAW_TRGT_IF_PCIE_1] = {
		.cfg =   (1 << 0) | (1 << 6) | (1 << 0xe) | (1 << 0xf),
	},
	[LAW_TRGT_IF_PCIE_2] = {
		.cfg =   (1 << 0xe),
	},
};
#elif defined(CONFIG_P1013) || defined(CONFIG_P1022)
static struct pci_info pci_config_info[] =
{
	[LAW_TRGT_IF_PCIE_1] = {
		.cfg =   (1 << 6) | (1 << 7) | (1 << 9) | (1 << 0xa) |
			 (1 << 0xb) | (1 << 0xd) | (1 << 0xe) |
			 (1 << 0xf) | (1 << 0x15) | (1 << 0x16) |
			 (1 << 0x17) | (1 << 0x18) | (1 << 0x19) |
			 (1 << 0x1a) | (1 << 0x1b) | (1 << 0x1c) |
			 (1 << 0x1d) | (1 << 0x1e) | (1 << 0x1f),
	},
	[LAW_TRGT_IF_PCIE_2] = {
		.cfg =   (1 << 1) | (1 << 6) | (1 << 7) | (1 << 9) |
			 (1 << 0xd) | (1 << 0x15) | (1 << 0x16) | (1 << 0x17) |
			 (1 << 0x18) | (1 << 0x19) | (1 << 0x1a) | (1 << 0x1b),
	},
	[LAW_TRGT_IF_PCIE_3] = {
		.cfg =   (1 << 0) | (1 << 1) | (1 << 6) | (1 << 7) | (1 << 9) |
			 (1 << 0xa) | (1 << 0xb) | (1 << 0xd) | (1 << 0x15) |
			 (1 << 0x16) | (1 << 0x17) | (1 << 0x18) | (1 << 0x1c),
	},
};
#elif defined(CONFIG_P2010) || defined(CONFIG_P2020)
static struct pci_info pci_config_info[] =
{
	[LAW_TRGT_IF_PCIE_1] = {
		.cfg =   (1 << 0) | (1 << 2) | (1 << 4) | (1 << 6) |
			 (1 << 0xd) | (1 << 0xe) | (1 << 0xf),
	},
	[LAW_TRGT_IF_PCIE_2] = {
		.cfg =   (1 << 2) | (1 << 0xe),
	},
	[LAW_TRGT_IF_PCIE_3] = {
		.cfg =   (1 << 2) | (1 << 4),
	},
};
#elif defined(CONFIG_FSL_CORENET)
#else
#error Need to define pci_config_info for processor
#endif

#ifndef CONFIG_FSL_CORENET
int is_fsl_pci_cfg(enum law_trgt_if trgt, u32 io_sel)
{
	return ((1 << io_sel) & pci_config_info[trgt].cfg);
}
#endif
