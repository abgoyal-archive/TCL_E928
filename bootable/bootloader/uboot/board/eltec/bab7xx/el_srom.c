

#include <common.h>
#include "srom.h"

/*----------------------------------------------------------------------------*/
static void eepStart (void)
{
    out8(I2C_BUS_DAT, 0x60);     /* SCLK = high  SDIO = high */
    out8(I2C_BUS_DIR, 0x60);     /* set output direction for SCLK/SDIO */
    udelay(10);
    out8(I2C_BUS_DAT, 0x40);     /* SCLK = high  SDIO = low */
    udelay(10);
    out8(I2C_BUS_DAT, 0x00);     /* SCLK = low   SDIO = low */
    udelay(10);
}

/*----------------------------------------------------------------------------*/
static void eepStop (void)
{
    out8(I2C_BUS_DAT, 0x00);      /* SCLK = low   SDIO = low */
    out8(I2C_BUS_DIR, 0x60);      /* set output direction for SCLK/SDIO */
    udelay(10);
    out8(I2C_BUS_DAT, 0x40);      /* SCLK = high  SDIO = low */
    udelay(10);
    out8(I2C_BUS_DAT, 0x60);      /* SCLK = high  SDIO = high */
    udelay(10);
    out8(I2C_BUS_DIR, 0x00);      /* reset to input direction */
}

/*----------------------------------------------------------------------------*/
static unsigned char eepReadByte (void)
{
    register unsigned char buf = 0x00;
    register int i;

    out8(I2C_BUS_DIR, 0x40);

    for (i = 0; i < 8; i++)
    {
	out8(I2C_BUS_DAT, 0x00);    /* SCLK = low   SDIO = high */
	udelay(10);
	out8(I2C_BUS_DAT, 0x40);    /* SCLK = high  SDIO = high */
	udelay(15);
	buf <<= 1;
	buf = (in8(I2C_BUS_DAT) & 0x20) ? (buf | 0x01) : (buf & 0xFE);
	out8(I2C_BUS_DAT, 0x00);    /* SCLK = low   SDIO = high */
	udelay(10);
    }
    return(buf);
}

/*----------------------------------------------------------------------------*/
static void eepWriteByte (register unsigned char buf)
{
    register int    i;

    (buf & 0x80) ? out8(I2C_BUS_DAT, 0x20) : out8(I2C_BUS_DAT, 0x00);     /* SCLK = low   SDIO = data */
    out8(I2C_BUS_DIR, 0x60);

    for (i = 7; i >= 0; i--)
    {
	(buf & 0x80) ? out8(I2C_BUS_DAT, 0x20) : out8(I2C_BUS_DAT, 0x00); /* SCLK=low  SDIO=data */
	udelay(10);
	(buf & 0x80) ? out8(I2C_BUS_DAT, 0x60) : out8(I2C_BUS_DAT, 0x40); /* SCLK=high SDIO=data */
	udelay(15);
	(buf & 0x80) ? out8(I2C_BUS_DAT, 0x20) : out8(I2C_BUS_DAT, 0x00); /* SCLK=low  SDIO=data */
	udelay(10);
	buf <<= 1;
    }
}

/*----------------------------------------------------------------------------*/
static int eepReadAck (void)
{
    int retval;

    out8(I2C_BUS_DIR, 0x40);
    out8(I2C_BUS_DAT, 0x00);            /* SCLK = low   SDIO = high */
    udelay(10);
    out8(I2C_BUS_DAT, 0x40);            /* SCLK = high  SDIO = high */
    udelay(10);
    retval = (in8(I2C_BUS_DAT) & 0x20) ? ERROR : 0;
    udelay(10);
    out8(I2C_BUS_DAT, 0x00);            /* SCLK = low   SDIO = high */
    udelay(10);

    return(retval);
}

/*----------------------------------------------------------------------------*/
static void eepWriteAck (unsigned char ack)
{
    ack ? out8(I2C_BUS_DAT, 0x20) : out8(I2C_BUS_DAT, 0x00); /* SCLK = low   SDIO = ack */
    out8(I2C_BUS_DIR, 0x60);
    udelay(10);
    ack ? out8(I2C_BUS_DAT, 0x60) : out8(I2C_BUS_DAT, 0x40); /* SCLK = high  SDIO = ack */
    udelay(15);
    ack ? out8(I2C_BUS_DAT, 0x20) : out8(I2C_BUS_DAT, 0x00); /* SCLK = low   SDIO = ack */
    udelay(10);
}

/*----------------------------------------------------------------------------*/
int el_srom_load (addr, buf, cnt, device, block)
unsigned char addr;
unsigned char *buf;
int cnt;
unsigned char device;
unsigned char block;
{
    register int i;

    for (i=0;i<cnt;i++)
    {
	eepStart();
	eepWriteByte(0xA0 | device | block);
	if (eepReadAck() == ERROR)
	{
	   eepStop();
	    return(ERROR);
	}
	eepWriteByte(addr++);
	if (eepReadAck() == ERROR)
	{
	    eepStop();
	    return(ERROR);
	}
	eepStart();

	eepWriteByte(0xA1 | device | block);
	if (eepReadAck() == ERROR)
	{
	    eepStop();
	    return(ERROR);
	}

	*buf++ = eepReadByte();
	eepWriteAck(1);
	eepStop();

	if ((addr == 0) && (i != (cnt-1)))    /* is it the same block ? */
	{
	    if (block == FIRST_BLOCK)
		block = SECOND_BLOCK;
	    else
		return(ERROR);
	}
    }
    return(cnt);
}

/*----------------------------------------------------------------------------*/
int el_srom_store (addr, buf, cnt, device, block)
unsigned char    addr, *buf, device, block;
int        cnt;
{
    register int i, retVal;

    for (i=0;i<cnt;i++)
    {
	retVal = ERROR;
	do
	{
	    eepStart();
	    eepWriteByte(0xA0 | device | block);
	    if ((retVal = eepReadAck()) == ERROR)
		eepStop();
	} while (retVal == ERROR);

	eepWriteByte(addr++);
	if (eepReadAck() == ERROR)  return(ERROR);

	if ((addr == 0) && (i != (cnt-1)))    /* is it the same block ? */
	{
	    if (block == FIRST_BLOCK)
		block = SECOND_BLOCK;
	    else
	    return(ERROR);
	}

	eepWriteByte(*buf++);
	if (eepReadAck() == ERROR)
	    return(ERROR);

	eepStop();
    }
    return(cnt);
}

/*----------------------------------------------------------------------------*/
unsigned long el_srom_checksum (ptr, size)
register unsigned char *ptr;
unsigned long size;
{
    u_long f, accu = 0;
    u_int  i;
    u_char byte;

    for (; size; size--)
    {
	byte = *ptr++;
	for (i = 8; i; i--)
	{
	    f =  ((byte & 1) ^ (accu & 1)) ? 0x84083001 : 0;
	    accu >>= 1; accu ^= f;
	    byte >>= 1;
	}
    }
    return(accu);
}

/*----------------------------------------------------------------------------*/
