
#ifndef __ASM_GLOBAL_DATA_H__
#define __ASM_GLOBAL_DATA_H__


typedef	struct	global_data {
	bd_t		*bd;
	unsigned long	flags;
	unsigned long	baudrate;
	unsigned long	stack_end;	/* highest stack address */
	unsigned long	have_console;	/* serial_init() was called */
	unsigned long	reloc_off;	/* Relocation Offset */
	unsigned long	env_addr;	/* Address of env struct */
	unsigned long	env_valid;	/* Checksum of env valid? */
	unsigned long	cpu_hz;		/* cpu core clock frequency */
#if defined(CONFIG_LCD)
	void		*fb_base;	/* framebuffer address */
#endif
	void		**jt;		/* jump table */
} gd_t;

#define GD_FLG_RELOC	0x00001		/* Code was relocated to RAM	 */
#define GD_FLG_DEVINIT	0x00002		/* Devices have been initialized */
#define GD_FLG_SILENT	0x00004		/* Silent mode			 */
#define GD_FLG_POSTFAIL	0x00008		/* Critical POST test failed	 */
#define GD_FLG_POSTSTOP	0x00010		/* POST seqeunce aborted	 */
#define GD_FLG_LOGINIT	0x00020		/* Log Buf has been initialized	 */
#define GD_FLG_DISABLE_CONSOLE	0x00040		/* Disable console (in & out)	 */

#define DECLARE_GLOBAL_DATA_PTR register gd_t *gd asm("r5")

#endif /* __ASM_GLOBAL_DATA_H__ */
