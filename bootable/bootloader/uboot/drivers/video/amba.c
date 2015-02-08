

#include <common.h>
#include <asm/io.h>
#include <lcd.h>
#include <amba_clcd.h>

/* These variables are required by lcd.c -- although it sets them by itself */
int lcd_line_length;
int lcd_color_fg;
int lcd_color_bg;
void *lcd_base;
void *lcd_console_address;
short console_col;
short console_row;


/* There is nothing to do with color registers, we use true color */
void lcd_setcolreg(ushort regno, ushort red, ushort green, ushort blue)
{
	return;
}

/* Low level initialization of the logic cell: depends on panel_info */
void lcd_ctrl_init(void *lcdbase)
{
	struct clcd_config *config;
	struct clcd_registers *regs;
	u32 cntl;

	config = panel_info.priv;
	regs = config->address;
	cntl = config->cntl & ~CNTL_LCDEN;

	/* Lazily, just copy the registers over: first control with disable */
	writel(cntl, &regs->cntl);

	writel(config->tim0, &regs->tim0);
	writel(config->tim1, &regs->tim1);
	writel(config->tim2, &regs->tim2);
	writel(config->tim3, &regs->tim3);
	writel((u32)lcdbase, &regs->ubas);
	/* finally, enable */
	writel(cntl | CNTL_LCDEN, &regs->cntl);
}

/* This is trivial, and copied from atmel_lcdfb.c */
ulong calc_fbsize(void)
{
	return ((panel_info.vl_col * panel_info.vl_row *
		NBITS(panel_info.vl_bpix)) / 8) + PAGE_SIZE;
}
