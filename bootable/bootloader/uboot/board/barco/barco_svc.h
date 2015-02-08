

#ifndef _LOCAL_BARCOHYDRA_H_
#define _LOCAL_BARCOHYDRA_H_

#include <flash.h>
#include <asm/io.h>

/* Defines for the barcohydra board */
#ifndef CONFIG_SYS_FLASH_ERASE_SECTOR_LENGTH
#define CONFIG_SYS_FLASH_ERASE_SECTOR_LENGTH (0x10000)
#endif

#ifndef CONFIG_SYS_DEFAULT_KERNEL_ADDRESS
#define CONFIG_SYS_DEFAULT_KERNEL_ADDRESS (CONFIG_SYS_FLASH_BASE + 0x30000)
#endif

#ifndef CONFIG_SYS_WORKING_KERNEL_ADDRESS
#define CONFIG_SYS_WORKING_KERNEL_ADDRESS (0xFFE00000)
#endif


typedef struct SBootInfo {
	unsigned int address;
	unsigned int size;
	unsigned char state;
}TSBootInfo;

/* barcohydra.c */
int checkboard(void);
phys_size_t initdram(int board_type);
void pci_init_board(void);
void check_flash(void);
int write_flash(char *addr, char value);
TSBootInfo* find_boot_info(void);
void final_boot(void);
#endif
