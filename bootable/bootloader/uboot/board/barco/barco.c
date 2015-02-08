


#include <common.h>
#include <mpc824x.h>
#include <pci.h>
#include <malloc.h>
#include <command.h>

#include "config.h"
#include "barco_svc.h"

#define TRY_WORKING  (3)
#define BOOT_DEFAULT (2)
#define BOOT_WORKING (1)

int checkboard (void)
{
	/*TODO: Check processor type */

	puts (	"Board: Streaming Video Card for Hydra systems "
#ifdef CONFIG_MPC8240
		"8240"
#endif
#ifdef CONFIG_MPC8245
		"8245"
#endif
		" Unity ##Test not implemented yet##\n");
	return 0;
}

phys_size_t initdram (int board_type)
{
	long size;
	long new_bank0_end;
	long mear1;
	long emear1;

	size = get_ram_size (CONFIG_SYS_SDRAM_BASE, CONFIG_SYS_MAX_RAM_SIZE);

	new_bank0_end = size - 1;
	mear1 = mpc824x_mpc107_getreg (MEAR1);
	emear1 = mpc824x_mpc107_getreg (EMEAR1);
	mear1 = (mear1  & 0xFFFFFF00) |
		((new_bank0_end & MICR_ADDR_MASK) >> MICR_ADDR_SHIFT);
	emear1 = (emear1 & 0xFFFFFF00) |
		((new_bank0_end & MICR_ADDR_MASK) >> MICR_EADDR_SHIFT);
	mpc824x_mpc107_setreg (MEAR1, mear1);
	mpc824x_mpc107_setreg (EMEAR1, emear1);

	return (size);
}

#ifndef CONFIG_PCI_PNP
static struct pci_config_table pci_barcohydra_config_table[] = {
	{ PCI_ANY_ID, PCI_ANY_ID, PCI_ANY_ID, PCI_ANY_ID, 0x0f, PCI_ANY_ID,
	  pci_cfgfunc_config_device, { PCI_ENET0_IOADDR,
				       PCI_ENET0_MEMADDR,
				       PCI_COMMAND_MEMORY | PCI_COMMAND_MASTER } },
	{ PCI_ANY_ID, PCI_ANY_ID, PCI_ANY_ID, PCI_ANY_ID, 0x10, PCI_ANY_ID,
	  pci_cfgfunc_config_device, { PCI_ENET1_IOADDR,
				       PCI_ENET1_MEMADDR,
				       PCI_COMMAND_MEMORY | PCI_COMMAND_MASTER } },
	{ }
};
#endif

struct pci_controller hose = {
#ifndef CONFIG_PCI_PNP
	config_table: pci_barcohydra_config_table,
#endif
};

void pci_init_board (void)
{
	pci_mpc824x_init (&hose);
}

int write_flash (char *addr, char value)
{
	char *adr = (char *)0xFF800000;
	int cnt = 0;
	char status,oldstatus;

	*(adr+0x55) = 0xAA; udelay (1);
	*(adr+0xAA) = 0x55; udelay (1);
	*(adr+0x55) = 0xA0; udelay (1);
	*addr = value;

	status = *addr;
	do {
		oldstatus = status;
		status = *addr;

		if ((oldstatus & 0x40) == (status & 0x40)) {
			return 4;
		}
		cnt++;
		if (cnt > 10000) {
			return 2;
		}
	} while ( (status & 0x20) == 0 );

	oldstatus = *addr;
	status = *addr;

	if ((oldstatus & 0x40) == (status & 0x40)) {
		return 0;
	} else {
		*(adr+0x55) = 0xF0;
		return 1;
	}
}

unsigned update_flash (unsigned char *buf)
{
	switch ((*buf) & 0x3) {
	case TRY_WORKING:
		printf ("found 3 and converted it to 2\n");
		write_flash ((char *)buf, (*buf) & 0xFE);
		*((unsigned char *)0xFF800000) = 0xF0;
		udelay (100);
		printf ("buf [%#010x] %#010x\n", (unsigned)buf, (*buf));
		/* XXX - fall through??? */
	case BOOT_WORKING :
		return BOOT_WORKING;
	}
	return BOOT_DEFAULT;
}

unsigned scan_flash (void)
{
	char section[] =  "kernel";
	int cfgFileLen  =  (CONFIG_SYS_FLASH_ERASE_SECTOR_LENGTH >> 1);
	int sectionPtr  = 0;
	int foundItem   = 0; /* 0: None, 1: section found, 2: "=" found */
	int bufPtr;
	unsigned char *buf;

	buf = (unsigned char*)(CONFIG_SYS_FLASH_RANGE_BASE + CONFIG_SYS_FLASH_RANGE_SIZE \
			- CONFIG_SYS_FLASH_ERASE_SECTOR_LENGTH);
	for (bufPtr = 0; bufPtr < cfgFileLen; ++bufPtr) {
		if ((buf[bufPtr]==0xFF) && (*(int*)(buf+bufPtr)==0xFFFFFFFF)) {
			return BOOT_DEFAULT;
		}
		/* This is the scanning loop, we try to find a particular
		 * quoted value
		 */
		switch (foundItem) {
		case 0:
			if ((section[sectionPtr] == 0)) {
				++foundItem;
			} else if (buf[bufPtr] == section[sectionPtr]) {
				++sectionPtr;
			} else {
				sectionPtr = 0;
			}
			break;
		case 1:
			++foundItem;
			break;
		case 2:
			++foundItem;
			break;
		case 3:
		default:
			return update_flash (&buf[bufPtr - 1]);
		}
	}

	printf ("Failed to read %s\n",section);
	return BOOT_DEFAULT;
}

TSBootInfo* find_boot_info (void)
{
	unsigned bootimage = scan_flash ();
	TSBootInfo* info = (TSBootInfo*)malloc (sizeof(TSBootInfo));

	switch (bootimage) {
	case TRY_WORKING:
		info->address = CONFIG_SYS_WORKING_KERNEL_ADDRESS;
		break;
	case BOOT_WORKING :
		info->address = CONFIG_SYS_WORKING_KERNEL_ADDRESS;
		break;
	case BOOT_DEFAULT:
	default:
		info->address= CONFIG_SYS_DEFAULT_KERNEL_ADDRESS;

	}
	info->size = *((unsigned int *)(info->address ));

	return info;
}

void barcobcd_boot (void)
{
	TSBootInfo* start;
	char *bootm_args[2];
	char *buf;
	int cnt;
	extern int do_bootm (cmd_tbl_t *, int, int, char *[]);

	buf = (char *)(0x00800000);
	/* make certain there are enough chars to print the command line here!
	 */
	bootm_args[0] = (char *)malloc (16*sizeof(char));
	bootm_args[1] = (char *)malloc (16*sizeof(char));

	start = find_boot_info ();

	printf ("Booting kernel at address %#10x with size %#10x\n",
			start->address, start->size);

	/* give length of the kernel image to bootm */
	sprintf (bootm_args[0],"%x",start->size);
	/* give address of the kernel image to bootm */
	sprintf (bootm_args[1],"%x",(unsigned)buf);

	printf ("flash address: %#10x\n",start->address+8);
	printf ("buf address: %#10x\n",(unsigned)buf);

	/* aha, we reserve 8 bytes here... */
	for (cnt = 0; cnt < start->size ; cnt++) {
		buf[cnt] = ((char *)start->address)[cnt+8];
	}

	/* initialise RAM memory */
	*((unsigned int *)0xFEC00000) = 0x00141A98;
	do_bootm (NULL,0,2,bootm_args);
}

int barcobcd_boot_image (cmd_tbl_t *cmdtp, int flag, int argc, char *argv[])
{
#if 0
	if (argc > 1) {
		cmd_usage(cmdtp);
		return 1;
	}
#endif
	barcobcd_boot ();

	return 0;
}


U_BOOT_CMD (
		try_working, 1, 1, barcobcd_boot_image,
		"check flash value and boot the appropriate image",
		""
	  );

U_BOOT_CMD (
		boot_working, 1, 1, barcobcd_boot_image,
		"check flash value and boot the appropriate image",
		""
	  );

U_BOOT_CMD (
		boot_default, 1, 1, barcobcd_boot_image,
		"check flash value and boot the appropriate image",
		""
	  );
int serial_init (void)
{
	return 0;
}
void serial_setbrg (void)
{
	return;
}
void serial_putc (const char c)
{
	return;
}
void serial_puts (const char *c)
{
	return;
}
int serial_getc (void)
{
	return 0;
}
int serial_tstc (void)
{
	return 0;
}

unsigned long post_word_load (void)
{
	return 0l;
}
void post_word_store (unsigned long val)
{
	return;
}
