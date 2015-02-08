

#ifndef	__ASM_GBL_DATA_H
#define __ASM_GBL_DATA_H

#include <asm/regdef.h>


typedef	struct	global_data {
	bd_t		*bd;
	unsigned long	flags;
	unsigned long	baudrate;
	unsigned long	have_console;	/* serial_init() was called */
	phys_size_t	ram_size;	/* RAM size */
	unsigned long	reloc_off;	/* Relocation Offset */
	unsigned long	env_addr;	/* Address  of Environment struct */
	unsigned long	env_valid;	/* Checksum of Environment valid? */
	void		**jt;		/* jump table */
} gd_t;

#define	GD_FLG_RELOC	0x00001		/* Code was relocated to RAM     */
#define	GD_FLG_DEVINIT	0x00002		/* Devices have been initialized */
#define	GD_FLG_SILENT	0x00004		/* Silent mode			 */
#define	GD_FLG_POSTFAIL	0x00008		/* Critical POST test failed	 */
#define	GD_FLG_POSTSTOP	0x00010		/* POST seqeunce aborted	 */
#define	GD_FLG_LOGINIT	0x00020		/* Log Buf has been initialized	 */
#define GD_FLG_DISABLE_CONSOLE	0x00040		/* Disable console (in & out)	 */

#define DECLARE_GLOBAL_DATA_PTR     register volatile gd_t *gd asm ("k0")

#endif /* __ASM_GBL_DATA_H */
