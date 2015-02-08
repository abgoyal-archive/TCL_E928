

#include <common.h>
#include <nios2.h>
#include <nios2-io.h>

#if defined (CONFIG_SYS_NIOS_SYSID_BASE)
extern void display_sysid (void);
#endif /* CONFIG_SYS_NIOS_SYSID_BASE */

int checkcpu (void)
{
	printf ("CPU   : Nios-II\n");
#if !defined(CONFIG_SYS_NIOS_SYSID_BASE)
	printf ("SYSID : <unknown>\n");
#else
	display_sysid ();
#endif
	return (0);
}


int do_reset (void)
{
	void (*rst)(void) = (void(*)(void))CONFIG_SYS_RESET_ADDR;
	disable_interrupts ();
	rst();
	return(0);
}
