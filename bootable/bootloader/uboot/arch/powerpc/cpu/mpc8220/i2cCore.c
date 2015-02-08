
/* I2cCore.c - MPC8220 PPC I2C Library */

/* Copyright 2004      Freescale Semiconductor, Inc. */



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vxWorks.h>
#include <sysLib.h>
#include <iosLib.h>
#include <logLib.h>
#include <tickLib.h>

/* BSP Includes */
#include "config.h"
#include "mpc8220.h"
#include "i2cCore.h"

#ifdef DEBUG_I2CCORE
int I2CCDbg = 0;
#endif

#define ABS(x)	((x < 0)? -x : x)

char *I2CERR[16] = {
	"Transfer in Progress\n",	/* 0 */
	"Transfer complete\n",
	"Not Addressed\n",		/* 2 */
	"Addressed as a slave\n",
	"Bus is Idle\n",		/* 4 */
	"Bus is busy\n",
	"Arbitration Lost\n",		/* 6 */
	"Arbitration on Track\n",
	"Slave receive, master writing to slave\n",	/* 8 */
	"Slave transmit, master reading from slave\n",
	"Interrupt is pending\n",	/* 10 */
	"Interrupt complete\n",
	"Acknowledge received\n",	/* 12 */
	"No acknowledge received\n",
	"Unknown status\n",		/* 14 */
	"\n"
};


STATUS chk_status (PSI2C pi2c, UINT8 sta_bit, UINT8 truefalse)
{
	int i, status = 0;

	for (i = 0; i < I2C_POLL_COUNT; i++) {
		if ((pi2c->sr & sta_bit) == (truefalse ? sta_bit : 0))
			return (OK);
	}

	I2CCDBG (L2, ("--- sr %x stabit %x truefalse %d\n",
		      pi2c->sr, sta_bit, truefalse, 0, 0, 0));

	if (i == I2C_POLL_COUNT) {
		switch (sta_bit) {
		case I2C_STA_CF:
			status = 0;
			break;
		case I2C_STA_AAS:
			status = 2;
			break;
		case I2C_STA_BB:
			status = 4;
			break;
		case I2C_STA_AL:
			status = 6;
			break;
		case I2C_STA_SRW:
			status = 8;
			break;
		case I2C_STA_IF:
			status = 10;
			break;
		case I2C_STA_RXAK:
			status = 12;
			break;
		default:
			status = 14;
			break;
		}

		if (!truefalse)
			status++;

		I2CCDBG (NO, ("--- status %d\n", status, 0, 0, 0, 0, 0));
		I2CCDBG (NO, (I2CERR[status], 0, 0, 0, 0, 0, 0));
	}

	return (ERROR);
}

STATUS i2c_enable (SI2C * pi2c, PI2CSET pi2cSet)
{
	int fdr = pi2cSet->bit_rate;
	UINT8 adr = pi2cSet->i2c_adr;

	I2CCDBG (L2, ("i2c_enable fdr %d adr %x\n", fdr, adr, 0, 0, 0, 0));

	i2c_clear (pi2c);	/* Clear FDR, ADR, SR and CR reg */

	SetI2cFDR (pi2c, fdr);	/* Frequency			*/
	pi2c->adr = adr;

	pi2c->cr = I2C_CTL_EN;	/* Set Enable			*/

	/*
	   The I2C bus should be in Idle state. If the bus is busy,
	   clear the STA bit in control register
	 */
	if (chk_status (pi2c, I2C_STA_BB, 0) != OK) {
		if ((pi2c->cr & I2C_CTL_STA) == I2C_CTL_STA)
			pi2c->cr &= ~I2C_CTL_STA;

		/* Check again if it is still busy, return error if found */
		if (chk_status (pi2c, I2C_STA_BB, 1) == OK)
			return ERROR;
	}

	return (OK);
}

STATUS i2c_disable (PSI2C pi2c)
{
	i2c_clear (pi2c);

	pi2c->cr &= I2C_CTL_EN; /* Disable I2c			*/

	if ((pi2c->cr & I2C_CTL_STA) == I2C_CTL_STA)
		pi2c->cr &= ~I2C_CTL_STA;

	if (chk_status (pi2c, I2C_STA_BB, 0) != OK)
		return ERROR;

	return (OK);
}

STATUS i2c_clear (PSI2C pi2c)
{
	pi2c->adr = 0;
	pi2c->fdr = 0;
	pi2c->cr = 0;
	pi2c->sr = 0;

	return (OK);
}


STATUS i2c_start (PSI2C pi2c, PI2CSET pi2cSet)
{
#ifdef TWOBYTES
	UINT16 ByteOffset = pi2cSet->str_adr;
#else
	UINT8 ByteOffset = pi2cSet->str_adr;
#endif
#if 1
	UINT8 tmp = 0;
#endif
	UINT8 Addr = pi2cSet->slv_adr;

	pi2c->cr |= I2C_CTL_STA;	/* Generate start signal	*/

	if (chk_status (pi2c, I2C_STA_BB, 1) != OK)
		return ERROR;

	/* Write slave address */
	if (i2c_writebyte (pi2c, &Addr) != OK) {
		i2c_stop (pi2c);	/* Disable I2c			*/
		return ERROR;
	}
#ifdef TWOBYTES
#   if 0
	/* Issue the offset to start */
	if (i2c_write2byte (pi2c, &ByteOffset) != OK) {
		i2c_stop (pi2c);	/* Disable I2c			*/
		return ERROR;
	}
#endif
	tmp = (ByteOffset >> 8) & 0xff;
	if (i2c_writebyte (pi2c, &tmp) != OK) {
		i2c_stop (pi2c);	/* Disable I2c			*/
		return ERROR;
	}
	tmp = ByteOffset & 0xff;
	if (i2c_writebyte (pi2c, &tmp) != OK) {
		i2c_stop (pi2c);	/* Disable I2c			*/
		return ERROR;
	}
#else
	if (i2c_writebyte (pi2c, &ByteOffset) != OK) {
		i2c_stop (pi2c);	/* Disable I2c			*/
		return ERROR;
	}
#endif

	return (OK);
}

STATUS i2c_stop (PSI2C pi2c)
{
	pi2c->cr &= ~I2C_CTL_STA;	/* Generate stop signal		*/
	if (chk_status (pi2c, I2C_STA_BB, 0) != OK)
		return ERROR;

	return (OK);
}

int i2c_readblock (SI2C * pi2c, PI2CSET pi2cSet, UINT8 * Data)
{
	int i = 0;
	UINT8 Tmp;

/*    UINT8 ByteOffset = pi2cSet->str_adr; not used? */
	UINT8 Addr = pi2cSet->slv_adr;
	int Length = pi2cSet->xfer_size;

	I2CCDBG (L1, ("i2c_readblock addr %x data 0x%08x len %d offset %d\n",
		      Addr, (int) Data, Length, ByteOffset, 0, 0));

	if (pi2c->sr & I2C_STA_AL) {	/* Check if Arbitration lost	*/
		I2CCDBG (FN, ("Arbitration lost\n", 0, 0, 0, 0, 0, 0));
		pi2c->sr &= ~I2C_STA_AL;	/* Clear Arbitration status bit */
		return ERROR;
	}

	pi2c->cr |= I2C_CTL_TX; /* Enable the I2c for TX, Ack	*/

	if (i2c_start (pi2c, pi2cSet) == ERROR)
		return ERROR;

	pi2c->cr |= I2C_CTL_RSTA;	/* Repeat Start */

	Tmp = Addr | 1;

	if (i2c_writebyte (pi2c, &Tmp) != OK) {
		i2c_stop (pi2c);	/* Disable I2c	*/
		return ERROR;
	}

	if (((pi2c->sr & 0x07) == 0x07) || (pi2c->sr & 0x01))
		return ERROR;

	pi2c->cr &= ~I2C_CTL_TX;	/* Set receive mode	*/

	if (((pi2c->sr & 0x07) == 0x07) || (pi2c->sr & 0x01))
		return ERROR;

	/* Dummy Read */
	if (i2c_readbyte (pi2c, &Tmp, &i) != OK) {
		i2c_stop (pi2c);	/* Disable I2c	*/
		return ERROR;
	}

	i = 0;
	while (Length) {
		if (Length == 2)
			pi2c->cr |= I2C_CTL_TXAK;

		if (Length == 1)
			pi2c->cr &= ~I2C_CTL_STA;

		if (i2c_readbyte (pi2c, Data, &Length) != OK) {
			return i2c_stop (pi2c);
		}
		i++;
		Length--;
		Data++;
	}

	if (i2c_stop (pi2c) == ERROR)
		return ERROR;

	return i;
}

STATUS i2c_writeblock (SI2C * pi2c, PI2CSET pi2cSet, UINT8 * Data)
{
	int Length = pi2cSet->xfer_size;

#ifdef TWOBYTES
	UINT16 ByteOffset = pi2cSet->str_adr;
#else
	UINT8 ByteOffset = pi2cSet->str_adr;
#endif
	int j, k;

	I2CCDBG (L2, ("i2c_writeblock\n", 0, 0, 0, 0, 0, 0));

	if (pi2c->sr & I2C_STA_AL) {
		/* Check if arbitration lost */
		I2CCDBG (L2, ("Arbitration lost\n", 0, 0, 0, 0, 0, 0));
		pi2c->sr &= ~I2C_STA_AL;	/* Clear the condition	*/
		return ERROR;
	}

	pi2c->cr |= I2C_CTL_TX; /* Enable the I2c for TX, Ack	*/

	/* Do the not even offset first */
	if ((ByteOffset % 8) != 0) {
		int remain;

		if (Length > 8) {
			remain = 8 - (ByteOffset % 8);
			Length -= remain;

			pi2cSet->str_adr = ByteOffset;

			if (i2c_start (pi2c, pi2cSet) == ERROR)
				return ERROR;

			for (j = ByteOffset; j < remain; j++) {
				if (i2c_writebyte (pi2c, Data++) != OK)
					return ERROR;
			}

			if (i2c_stop (pi2c) == ERROR)
				return ERROR;

			sysMsDelay (32);

			/* Update the new ByteOffset */
			ByteOffset += remain;
		}
	}

	for (j = ByteOffset, k = 0; j < (Length + ByteOffset); j++) {
		if ((j % 8) == 0) {
			pi2cSet->str_adr = j;
			if (i2c_start (pi2c, pi2cSet) == ERROR)
				return ERROR;
		}

		k++;

		if (i2c_writebyte (pi2c, Data++) != OK)
			return ERROR;

		if ((j == (Length - 1)) || ((k % 8) == 0)) {
			if (i2c_stop (pi2c) == ERROR)
				return ERROR;

			sysMsDelay (50);
		}

	}

	return k;
}

STATUS i2c_readbyte (SI2C * pi2c, UINT8 * readb, int *index)
{
	pi2c->sr &= ~I2C_STA_IF;	/* Clear Interrupt Bit	*/
	*readb = pi2c->dr;		/* Read a byte		*/

	/*
	   Set I2C_CTRL_TXAK will cause Transfer pending and
	   set I2C_CTRL_STA will cause Interrupt pending
	 */
	if (*index != 2) {
		if (chk_status (pi2c, I2C_STA_CF, 1) != OK)	/* Transfer not complete?	*/
			return ERROR;
	}

	if (*index != 1) {
		if (chk_status (pi2c, I2C_STA_IF, 1) != OK)
			return ERROR;
	}

	return (OK);
}


STATUS i2c_writebyte (SI2C * pi2c, UINT8 * writeb)
{
	pi2c->sr &= ~I2C_STA_IF;	/* Clear Interrupt	*/
	pi2c->dr = *writeb;		/* Write a byte		*/

	if (chk_status (pi2c, I2C_STA_CF, 1) != OK)	/* Transfer not complete?	*/
		return ERROR;

	if (chk_status (pi2c, I2C_STA_IF, 1) != OK)
		return ERROR;

	return OK;
}

STATUS i2c_write2byte (SI2C * pi2c, UINT16 * writeb)
{
	UINT8 data;

	data = (UINT8) ((*writeb >> 8) & 0xff);
	if (i2c_writebyte (pi2c, &data) != OK)
		return ERROR;
	data = (UINT8) (*writeb & 0xff);
	if (i2c_writebyte (pi2c, &data) != OK)
		return ERROR;
	return OK;
}

STATUS SetI2cFDR (PSI2C pi2cRegs, int bitrate)
{
/* Constants */
	const UINT8 div_hold[8][3] = { {9, 3}, {10, 3},
	{12, 4}, {15, 4},
	{5, 1}, {6, 1},
	{7, 2}, {8, 2}
	};

	const UINT8 scl_tap[8][2] = { {4, 1}, {4, 2},
	{6, 4}, {6, 8},
	{14, 16}, {30, 32},
	{62, 64}, {126, 128}
	};

	UINT8 mfdr_bits;

	int i = 0;
	int j = 0;

	int Diff, min;
	int WhichFreq, iRec, jRec;
	int SCL_Period;
	int SCL_Hold;
	int I2C_Freq;

	I2CCDBG (L2, ("Entering getBitRate: bitrate %d pi2cRegs 0x%08x\n",
		      bitrate, (int) pi2cRegs, 0, 0, 0, 0));

	if (bitrate < 0) {
		I2CCDBG (NO, ("Invalid bitrate\n", 0, 0, 0, 0, 0, 0));
		return ERROR;
	}

	/* Initialize */
	mfdr_bits = 0;
	min = 0x7fffffff;
	WhichFreq = iRec = jRec = 0;

	for (i = 0; i < 8; i++) {
		for (j = 0; j < 8; j++) {
			/* SCL Period = 2 * (scl2tap + [(SCL_Tap - 1) * tap2tap] + 2)
			 * SCL Hold   = scl2tap + ((SDA_Tap - 1) * tap2tap) + 3
			 * Bit Rate (I2C Freq) = System Freq / SCL Period
			 */
			SCL_Period =
				2 * (scl_tap[i][0] +
				     ((div_hold[j][0] - 1) * scl_tap[i][1]) +
				     2);

			/* Now get the I2C Freq */
			I2C_Freq = DEV_CLOCK_FREQ / SCL_Period;

			/* Take equal or slower */
			if (I2C_Freq > bitrate)
				continue;

			/* Take the differences */
			Diff = I2C_Freq - bitrate;

			Diff = ABS (Diff);

			/* Find the closer value */
			if (Diff < min) {
				min = Diff;
				WhichFreq = I2C_Freq;
				iRec = i;
				jRec = j;
			}

			I2CCDBG (L2,
				 ("--- (%d,%d) I2C_Freq %d minDiff %d min %d\n",
				  i, j, I2C_Freq, Diff, min, 0));
		}
	}

	SCL_Period =
		2 * (scl_tap[iRec][0] +
		     ((div_hold[jRec][0] - 1) * scl_tap[iRec][1]) + 2);

	I2CCDBG (L2, ("\nmin %d WhichFreq %d iRec %d jRec %d\n",
		      min, WhichFreq, iRec, jRec, 0, 0));
	I2CCDBG (L2, ("--- scl2tap %d SCL_Tap %d tap2tap %d\n",
		      scl_tap[iRec][0], div_hold[jRec][0], scl_tap[iRec][1],
		      0, 0, 0));

	/* This may no require */
	SCL_Hold =
		scl_tap[iRec][0] +
		((div_hold[jRec][1] - 1) * scl_tap[iRec][1]) + 3;
	I2CCDBG (L2,
		 ("--- SCL_Period %d SCL_Hold %d\n", SCL_Period, SCL_Hold, 0,
		  0, 0, 0));

	I2CCDBG (L2, ("--- mfdr_bits %x\n", mfdr_bits, 0, 0, 0, 0, 0));

	/* FDR 4,3,2 */
	if ((iRec & 1) == 1)
		mfdr_bits |= 0x04;	/* FDR 2 */
	if ((iRec & 2) == 2)
		mfdr_bits |= 0x08;	/* FDR 3 */
	if ((iRec & 4) == 4)
		mfdr_bits |= 0x10;	/* FDR 4 */
	/* FDR 5,1,0 */
	if ((jRec & 1) == 1)
		mfdr_bits |= 0x01;	/* FDR 0 */
	if ((jRec & 2) == 2)
		mfdr_bits |= 0x02;	/* FDR 1 */
	if ((jRec & 4) == 4)
		mfdr_bits |= 0x20;	/* FDR 5 */

	I2CCDBG (L2, ("--- mfdr_bits %x\n", mfdr_bits, 0, 0, 0, 0, 0));

	pi2cRegs->fdr = mfdr_bits;

	return OK;
}
