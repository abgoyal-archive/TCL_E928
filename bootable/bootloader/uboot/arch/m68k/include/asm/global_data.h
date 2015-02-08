

#ifndef	__ASM_GBL_DATA_H
#define __ASM_GBL_DATA_H

typedef	struct	global_data {
	bd_t		*bd;
	unsigned long	flags;
	unsigned long	baudrate;
	unsigned long	cpu_clk;	/* CPU clock in Hz!		*/
	unsigned long	bus_clk;
#ifdef CONFIG_PCI
	unsigned long	pci_clk;
#endif
#ifdef CONFIG_EXTRA_CLOCK
	unsigned long	inp_clk;
	unsigned long	vco_clk;
	unsigned long	flb_clk;
#endif
#ifdef CONFIG_FSL_I2C
	unsigned long	i2c1_clk;
	unsigned long	i2c2_clk;
#endif
	phys_size_t	ram_size;	/* RAM size */
	unsigned long	reloc_off;	/* Relocation Offset */
	unsigned long	reset_status;	/* reset status register at boot	*/
	unsigned long	env_addr;	/* Address  of Environment struct	*/
	unsigned long	env_valid;	/* Checksum of Environment valid?	*/
	unsigned long	have_console;	/* serial_init() was called		*/
#if defined(CONFIG_LCD) || defined(CONFIG_VIDEO)
	unsigned long	fb_base;	/* Base addr of framebuffer memory */
#endif
#ifdef CONFIG_BOARD_TYPES
	unsigned long	board_type;
#endif
	void		**jt;		/* Standalone app jump table */
} gd_t;

#define	GD_FLG_RELOC	0x00001		/* Code was relocated to RAM		*/
#define	GD_FLG_DEVINIT	0x00002		/* Devices have been initialized	*/
#define	GD_FLG_SILENT	0x00004		/* Silent mode				*/
#define	GD_FLG_POSTFAIL	0x00008		/* Critical POST test failed		*/
#define	GD_FLG_POSTSTOP	0x00010		/* POST seqeunce aborted		*/
#define	GD_FLG_LOGINIT	0x00020		/* Log Buffer has been initialized	*/
#define GD_FLG_DISABLE_CONSOLE	0x00040		/* Disable console (in & out)	 */

#if 0
extern gd_t *global_data;
#define DECLARE_GLOBAL_DATA_PTR     gd_t *gd = global_data
#else
#define DECLARE_GLOBAL_DATA_PTR     register volatile gd_t *gd asm ("d7")
#endif

#endif /* __ASM_GBL_DATA_H */
