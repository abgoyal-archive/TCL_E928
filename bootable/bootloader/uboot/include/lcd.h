

#ifndef _LCD_H_
#define _LCD_H_

extern char lcd_is_enabled;

extern int lcd_line_length;
extern int lcd_color_fg;
extern int lcd_color_bg;

extern void *lcd_base;		/* Start of framebuffer memory	*/
extern void *lcd_console_address;	/* Start of console buffer	*/

extern short console_col;
extern short console_row;
extern struct vidinfo panel_info;

extern void lcd_ctrl_init (void *lcdbase);
extern void lcd_enable (void);

/* setcolreg used in 8bpp/16bpp; initcolregs used in monochrome */
extern void lcd_setcolreg (ushort regno,
				ushort red, ushort green, ushort blue);
extern void lcd_initcolregs (void);

/* gunzip_bmp used if CONFIG_VIDEO_BMP_GZIP */
extern struct bmp_image *gunzip_bmp(unsigned long addr, unsigned long *lenp);

#if defined CONFIG_MPC823
typedef struct vidinfo {
	ushort	vl_col;		/* Number of columns (i.e. 640) */
	ushort	vl_row;		/* Number of rows (i.e. 480) */
	ushort	vl_width;	/* Width of display area in millimeters */
	ushort	vl_height;	/* Height of display area in millimeters */

	/* LCD configuration register */
	u_char	vl_clkp;	/* Clock polarity */
	u_char	vl_oep;		/* Output Enable polarity */
	u_char	vl_hsp;		/* Horizontal Sync polarity */
	u_char	vl_vsp;		/* Vertical Sync polarity */
	u_char	vl_dp;		/* Data polarity */
	u_char	vl_bpix;	/* Bits per pixel, 0 = 1, 1 = 2, 2 = 4, 3 = 8 */
	u_char	vl_lbw;		/* LCD Bus width, 0 = 4, 1 = 8 */
	u_char	vl_splt;	/* Split display, 0 = single-scan, 1 = dual-scan */
	u_char	vl_clor;	/* Color, 0 = mono, 1 = color */
	u_char	vl_tft;		/* 0 = passive, 1 = TFT */

	/* Horizontal control register. Timing from data sheet */
	ushort	vl_wbl;		/* Wait between lines */

	/* Vertical control register */
	u_char	vl_vpw;		/* Vertical sync pulse width */
	u_char	vl_lcdac;	/* LCD AC timing */
	u_char	vl_wbf;		/* Wait between frames */
} vidinfo_t;

#elif defined CONFIG_PXA250
struct pxafb_dma_descriptor {
	u_long	fdadr;		/* Frame descriptor address register */
	u_long	fsadr;		/* Frame source address register */
	u_long	fidr;		/* Frame ID register */
	u_long	ldcmd;		/* Command register */
};

struct pxafb_info {

	/* Misc registers */
	u_long	reg_lccr3;
	u_long	reg_lccr2;
	u_long	reg_lccr1;
	u_long	reg_lccr0;
	u_long	fdadr0;
	u_long	fdadr1;

	/* DMA descriptors */
	struct	pxafb_dma_descriptor *	dmadesc_fblow;
	struct	pxafb_dma_descriptor *	dmadesc_fbhigh;
	struct	pxafb_dma_descriptor *	dmadesc_palette;

	u_long	screen;		/* physical address of frame buffer */
	u_long	palette;	/* physical address of palette memory */
	u_int	palette_size;
};

typedef struct vidinfo {
	ushort	vl_col;		/* Number of columns (i.e. 640) */
	ushort	vl_row;		/* Number of rows (i.e. 480) */
	ushort	vl_width;	/* Width of display area in millimeters */
	ushort	vl_height;	/* Height of display area in millimeters */

	/* LCD configuration register */
	u_char	vl_clkp;	/* Clock polarity */
	u_char	vl_oep;		/* Output Enable polarity */
	u_char	vl_hsp;		/* Horizontal Sync polarity */
	u_char	vl_vsp;		/* Vertical Sync polarity */
	u_char	vl_dp;		/* Data polarity */
	u_char	vl_bpix;	/* Bits per pixel, 0 = 1, 1 = 2, 2 = 4, 3 = 8, 4 = 16 */
	u_char	vl_lbw;		/* LCD Bus width, 0 = 4, 1 = 8 */
	u_char	vl_splt;	/* Split display, 0 = single-scan, 1 = dual-scan */
	u_char	vl_clor;	/* Color, 0 = mono, 1 = color */
	u_char	vl_tft;		/* 0 = passive, 1 = TFT */

	/* Horizontal control register. Timing from data sheet */
	ushort	vl_hpw;		/* Horz sync pulse width */
	u_char	vl_blw;		/* Wait before of line */
	u_char	vl_elw;		/* Wait end of line */

	/* Vertical control register. */
	u_char	vl_vpw;		/* Vertical sync pulse width */
	u_char	vl_bfw;		/* Wait before of frame */
	u_char	vl_efw;		/* Wait end of frame */

	/* PXA LCD controller params */
	struct	pxafb_info pxa;
} vidinfo_t;

#elif defined(CONFIG_ATMEL_LCD)

typedef struct vidinfo {
	u_long vl_col;		/* Number of columns (i.e. 640) */
	u_long vl_row;		/* Number of rows (i.e. 480) */
	u_long vl_clk;	/* pixel clock in ps    */

	/* LCD configuration register */
	u_long vl_sync;		/* Horizontal / vertical sync */
	u_long vl_bpix;		/* Bits per pixel, 0 = 1, 1 = 2, 2 = 4, 3 = 8, 4 = 16 */
	u_long vl_tft;		/* 0 = passive, 1 = TFT */

	/* Horizontal control register. */
	u_long vl_hsync_len;	/* Length of horizontal sync */
	u_long vl_left_margin;	/* Time from sync to picture */
	u_long vl_right_margin;	/* Time from picture to sync */

	/* Vertical control register. */
	u_long vl_vsync_len;	/* Length of vertical sync */
	u_long vl_upper_margin;	/* Time from sync to picture */
	u_long vl_lower_margin;	/* Time from picture to sync */

	u_long	mmio;		/* Memory mapped registers */
} vidinfo_t;

#else

typedef struct vidinfo {
	ushort	vl_col;		/* Number of columns (i.e. 160) */
	ushort	vl_row;		/* Number of rows (i.e. 100) */

	u_char	vl_bpix;	/* Bits per pixel, 0 = 1 */

	ushort	*cmap;		/* Pointer to the colormap */

	void	*priv;		/* Pointer to driver-specific data */
} vidinfo_t;

#endif /* CONFIG_MPC823, CONFIG_PXA250 or CONFIG_MCC200 or CONFIG_ATMEL_LCD */

extern vidinfo_t panel_info;

/* Video functions */

#if defined(CONFIG_RBC823)
void	lcd_disable	(void);
#endif


/* int	lcd_init	(void *lcdbase); */
void	lcd_putc	(const char c);
void	lcd_puts	(const char *s);
void	lcd_printf	(const char *fmt, ...);

/* Allow boards to customize the information displayed */
void lcd_show_board_info(void);

/************************************************************************/
/* ** BITMAP DISPLAY SUPPORT						*/
/************************************************************************/
#if defined(CONFIG_CMD_BMP) || defined(CONFIG_SPLASH_SCREEN)
# include <bmp_layout.h>
# include <asm/byteorder.h>
#endif

#define CONFIG_SYS_HIGH	0	/* Pins are active high			*/
#define CONFIG_SYS_LOW		1	/* Pins are active low			*/

#define LCD_MONOCHROME	0
#define LCD_COLOR2	1
#define LCD_COLOR4	2
#define LCD_COLOR8	3
#define LCD_COLOR16	4

/*----------------------------------------------------------------------*/
#if defined(CONFIG_LCD_INFO_BELOW_LOGO)
# define LCD_INFO_X		0
# define LCD_INFO_Y		(BMP_LOGO_HEIGHT + VIDEO_FONT_HEIGHT)
#elif defined(CONFIG_LCD_LOGO)
# define LCD_INFO_X		(BMP_LOGO_WIDTH + 4 * VIDEO_FONT_WIDTH)
# define LCD_INFO_Y		(VIDEO_FONT_HEIGHT)
#else
# define LCD_INFO_X		(VIDEO_FONT_WIDTH)
# define LCD_INFO_Y		(VIDEO_FONT_HEIGHT)
#endif

/* Default to 8bpp if bit depth not specified */
#ifndef LCD_BPP
# define LCD_BPP			LCD_COLOR8
#endif
#ifndef LCD_DF
# define LCD_DF			1
#endif

/* Calculate nr. of bits per pixel  and nr. of colors */
#define NBITS(bit_code)		(1 << (bit_code))
#define NCOLORS(bit_code)	(1 << NBITS(bit_code))

/************************************************************************/
/* ** CONSOLE CONSTANTS							*/
/************************************************************************/
#if LCD_BPP == LCD_MONOCHROME

# define CONSOLE_COLOR_BLACK	0
# define CONSOLE_COLOR_WHITE	1	/* Must remain last / highest	*/

#elif LCD_BPP == LCD_COLOR8

# define CONSOLE_COLOR_BLACK	0
# define CONSOLE_COLOR_RED	1
# define CONSOLE_COLOR_GREEN	2
# define CONSOLE_COLOR_YELLOW	3
# define CONSOLE_COLOR_BLUE	4
# define CONSOLE_COLOR_MAGENTA	5
# define CONSOLE_COLOR_CYAN	6
# define CONSOLE_COLOR_GREY	14
# define CONSOLE_COLOR_WHITE	15	/* Must remain last / highest	*/

#else

# define CONSOLE_COLOR_BLACK	0x0000
# define CONSOLE_COLOR_WHITE	0xffff	/* Must remain last / highest	*/

#endif /* color definitions */

/************************************************************************/
#ifndef PAGE_SIZE
# define PAGE_SIZE	4096
#endif

/************************************************************************/
/* ** CONSOLE DEFINITIONS & FUNCTIONS					*/
/************************************************************************/
#if defined(CONFIG_LCD_LOGO) && !defined(CONFIG_LCD_INFO_BELOW_LOGO)
# define CONSOLE_ROWS		((panel_info.vl_row-BMP_LOGO_HEIGHT) \
					/ VIDEO_FONT_HEIGHT)
#else
# define CONSOLE_ROWS		(panel_info.vl_row / VIDEO_FONT_HEIGHT)
#endif

#define CONSOLE_COLS		(panel_info.vl_col / VIDEO_FONT_WIDTH)
#define CONSOLE_ROW_SIZE	(VIDEO_FONT_HEIGHT * lcd_line_length)
#define CONSOLE_ROW_FIRST	(lcd_console_address)
#define CONSOLE_ROW_SECOND	(lcd_console_address + CONSOLE_ROW_SIZE)
#define CONSOLE_ROW_LAST	(lcd_console_address + CONSOLE_SIZE \
					- CONSOLE_ROW_SIZE)
#define CONSOLE_SIZE		(CONSOLE_ROW_SIZE * CONSOLE_ROWS)
#define CONSOLE_SCROLL_SIZE	(CONSOLE_SIZE - CONSOLE_ROW_SIZE)

#if LCD_BPP == LCD_MONOCHROME
# define COLOR_MASK(c)		((c)	  | (c) << 1 | (c) << 2 | (c) << 3 | \
				 (c) << 4 | (c) << 5 | (c) << 6 | (c) << 7)
#elif (LCD_BPP == LCD_COLOR8) || (LCD_BPP == LCD_COLOR16)
# define COLOR_MASK(c)		(c)
#else
# error Unsupported LCD BPP.
#endif

/************************************************************************/

#endif	/* _LCD_H_ */
