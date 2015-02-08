

#include <common.h>
#include <command.h>
#include <netdev.h>


/* Define some MPC107 (memory controller) registers */
#define MPC107_EUMB_GCR         0xfce41020
#define MPC107_EUMB_IACKR       0xfce600a0


/* Function prototypes */
extern void unlock_ram_in_cache( void );
extern void _start_warm(void);


phys_size_t initdram( int board_type )
{
    return CONFIG_SYS_SDRAM_SIZE;
}


void after_reloc( ulong dest_addr, gd_t* gd )
{
	/* Jump to the main U-Boot board init code */
	board_init_r( gd, dest_addr );
}


int checkboard( void )
{
    puts( "Board: Wind River PPMC 7xx/74xx\n" );
    return 0;
}


int misc_init_r( void )
{
	/* Reset the EPIC and clear pending interrupts */
	out32r(MPC107_EUMB_GCR, 0xa0000000);
	while( in32r( MPC107_EUMB_GCR ) & 0x80000000 );
	out32r( MPC107_EUMB_GCR, 0x20000000 );
	while( in32r( MPC107_EUMB_IACKR ) != 0xff );

	/* Enable the I-Cache */
	icache_enable();

	return 0;
}


void do_reset( cmd_tbl_t *cmdtp, int flag, int argc, char *argv[] )
{
	printf( "Resetting...\n" );

	/* Disabe and invalidate cache */
	icache_disable();
	dcache_disable();

	/* Jump to warm start (in RAM) */
	_start_warm();

	/* Should never get here */
	while(1);
}

int board_eth_init(bd_t *bis)
{
	return pci_eth_init(bis);
}
