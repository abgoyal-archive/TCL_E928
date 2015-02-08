


#include <config.h>

#include <common.h>
#include <asm/io.h>
#include <ali512x.h>




static void ali_write(u8 index, u8 value)
{
	/* write an arbirary register */
	outb(index, ALI_INDEX);
	outb(value, ALI_DATA);
}

#if 0
static int ali_read(u8 index)
{
	outb(index, ALI_INDEX);
	return inb(ALI_DATA);
}
#endif

#define ALI_OPEN() \
	outb(0x51, ALI_INDEX); \
	outb(0x23, ALI_INDEX)


#define ALI_CLOSE() \
	outb(0xbb, ALI_INDEX)

/* Select a logical device */
#define ALI_SELDEV(dev)	\
	ali_write(0x07, dev)


void ali512x_init(void)
{
	ALI_OPEN();

	ali_write(0x02, 0x01);	/* soft reset */
	ali_write(0x03, 0x03);	/* disable access to CIOs */
	ali_write(0x22, 0x00);	/* disable direct powerdown */
	ali_write(0x23, 0x00);	/* disable auto powerdown */
	ali_write(0x24, 0x00);	/* IR 8 is active hi, pin26 is PDIR */

	ALI_CLOSE();
}

void ali512x_set_fdc(int enabled, u16 io, u8 irq, u8 dma_channel)
{
	ALI_OPEN();
	ALI_SELDEV(0);

	ali_write(0x30, enabled?1:0);
	if (enabled) {
		ali_write(0x60, io >> 8);
		ali_write(0x61, io & 0xff);
		ali_write(0x70, irq);
		ali_write(0x74, dma_channel);

		/* AT mode, no drive swap */
		ali_write(0xf0, 0x08);
		ali_write(0xf1, 0x00);
		ali_write(0xf2, 0xff);
		ali_write(0xf4, 0x00);
	}
	ALI_CLOSE();
}


void ali512x_set_pp(int enabled, u16 io, u8 irq, u8 dma_channel)
{
	ALI_OPEN();
	ALI_SELDEV(3);

	ali_write(0x30, enabled?1:0);
	if (enabled) {
		ali_write(0x60, io >> 8);
		ali_write(0x61, io & 0xff);
		ali_write(0x70, irq);
		ali_write(0x74, dma_channel);

		/* mode: EPP 1.9, ECP FIFO threshold = 7, IRQ active low */
		ali_write(0xf0, 0xbc);
		/* 12 MHz, Burst DMA in ECP */
		ali_write(0xf1, 0x05);
	}
	ALI_CLOSE();

}

void ali512x_set_uart(int enabled, int index, u16 io, u8 irq)
{
	ALI_OPEN();
	ALI_SELDEV(index?5:4);

	ali_write(0x30, enabled?1:0);
	if (enabled) {
		ali_write(0x60, io >> 8);
		ali_write(0x61, io & 0xff);
		ali_write(0x70, irq);

		ali_write(0xf0, 0x00);
		ali_write(0xf1, 0x00);

		/* huh? write 0xf2 twice - a typo in rolo
		 * or some secret ali errata? Who knows?
		 */
		if (index) {
			ali_write(0xf2, 0x00);
		}
		ali_write(0xf2, 0x0c);
	}
	ALI_CLOSE();

}

void ali512x_set_uart2_irda(int enabled)
{
	ALI_OPEN();
	ALI_SELDEV(5);

	ali_write(0xf1, enabled?0x48:0x00); /* fullduplex IrDa */
	ALI_CLOSE();

}

void ali512x_set_rtc(int enabled, u16 io, u8 irq)
{
	ALI_OPEN();
	ALI_SELDEV(6);

	ali_write(0x30, enabled?1:0);
	if (enabled) {
		ali_write(0x60, io >> 8);
		ali_write(0x61, io & 0xff);
		ali_write(0x70, irq);

		ali_write(0xf0, 0x00);
	}
	ALI_CLOSE();
}

void ali512x_set_kbc(int enabled, u8 kbc_irq, u8 mouse_irq)
{
	ALI_OPEN();
	ALI_SELDEV(7);

	ali_write(0x30, enabled?1:0);
	if (enabled) {
		ali_write(0x70, kbc_irq);
		ali_write(0x72, mouse_irq);

		ali_write(0xf0, 0x00);
	}
	ALI_CLOSE();
}



#define ALI_CIO_PORT_SEL 0x83
#define ALI_CIO_INDEX    0xea
#define ALI_CIO_DATA     0xeb

void ali512x_set_cio(int enabled)
{
	int i;

	ALI_OPEN();

	if (enabled) {
		ali_write(0x3, ALI_CIO_PORT_SEL);    /* Enable CIO data register */
	} else {
		ali_write(0x3, ALI_CIO_PORT_SEL & ~0x80);
	}

	ALI_SELDEV(8);

	ali_write(0x30, enabled?1:0);

	/* set all pins to input to start with */
	for (i=0xe0;i<0xee;i++) {
		ali_write(i, 1);
	}

	for (i=0xf5;i<0xfe;i++) {
		ali_write(i, 1);
	}

	ALI_CLOSE();
}


void ali512x_cio_function(int pin, int special, int inv, int input)
{
	u8 data;
	u8 addr;

	/* valid pins are 10-17, 20-25 and 30-37 */
	if (pin >= 10 && pin <= 17) {
		addr = 0xe0+(pin&7);
	} else if (pin >= 20 && pin <= 25) {
		addr = 0xe8+(pin&7);
	} else if (pin >= 30 && pin <= 37) {
		addr = 0xf5+(pin&7);
	} else {
		return;
	}

	ALI_OPEN();

	ALI_SELDEV(8);


	data=0xf4;
	if (special) {
		data |= 0x08;
	} else {
		if (inv) {
			data |= 0x02;
		}
		if (input) {
			data |= 0x01;
		}
	}

	ali_write(addr, data);

	ALI_CLOSE();
}

void ali512x_cio_out(int pin, int value)
{
	u8 reg;
	u8 data;
	u8 bit;

	reg = pin/10;
	bit = 1 << (pin%10);


	outb(reg, ALI_CIO_INDEX);     /* select I/O register */
	data = inb(ALI_CIO_DATA);
	if (value) {
		data |= bit;
	} else {
		data &= ~bit;
	}
	outb(data, ALI_CIO_DATA);
}

int ali512x_cio_in(int pin)
{
	u8 reg;
	u8 data;
	u8 bit;

	/* valid pins are 10-17, 20-25 and 30-37 */
	reg = pin/10;
	bit = 1 << (pin%10);


	outb(reg, ALI_CIO_INDEX);     /* select I/O register */
	data = inb(ALI_CIO_DATA);

	return data & bit;
}
