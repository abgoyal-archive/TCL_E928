

/*******************************************************/
/* file: lenval.c                                      */
/* abstract:  This file contains routines for using    */
/*            the lenVal data structure.               */
/*******************************************************/

#include <common.h>
#include <asm/processor.h>

#include "lenval.h"
#include "ports.h"


long value( lenVal*     plvValue )
{
	long    lValue;         /* result to hold the accumulated result */
	short   sIndex;

	lValue  = 0;
	for ( sIndex = 0; sIndex < plvValue->len ; ++sIndex )
	{
		lValue <<= 8;                       /* shift the accumulated result */
		lValue |= plvValue->val[ sIndex];   /* get the last byte first */
	}

	return( lValue );
}

void initLenVal( lenVal*    plv,
		 long       lValue )
{
	plv->len    = 1;
	plv->val[0] = (unsigned char)lValue;
}

short EqualLenVal( lenVal*  plvTdoExpected,
		   lenVal*  plvTdoCaptured,
		   lenVal*  plvTdoMask )
{
	short           sEqual;
	short           sIndex;
	unsigned char   ucByteVal1;
	unsigned char   ucByteVal2;
	unsigned char   ucByteMask;

	sEqual  = 1;
	sIndex  = plvTdoExpected->len;

	while ( sEqual && sIndex-- )
	{
		ucByteVal1  = plvTdoExpected->val[ sIndex ];
		ucByteVal2  = plvTdoCaptured->val[ sIndex ];
		if ( plvTdoMask )
		{
			ucByteMask  = plvTdoMask->val[ sIndex ];
			ucByteVal1  &= ucByteMask;
			ucByteVal2  &= ucByteMask;
		}
		if ( ucByteVal1 != ucByteVal2 )
		{
			sEqual  = 0;
		}
	}

	return( sEqual );
}


short RetBit( lenVal*   plv,
	      int       iByte,
	      int       iBit )
{
	/* assert( ( iByte >= 0 ) && ( iByte < plv->len ) ); */
	/* assert( ( iBit >= 0 ) && ( iBit < 8 ) ); */
	return( (short)( ( plv->val[ iByte ] >> ( 7 - iBit ) ) & 0x1 ) );
}

void SetBit( lenVal*    plv,
	     int        iByte,
	     int        iBit,
	     short      sVal )
{
	unsigned char   ucByteVal;
	unsigned char   ucBitMask;

	ucBitMask   = (unsigned char)(1 << ( 7 - iBit ));
	ucByteVal   = (unsigned char)(plv->val[ iByte ] & (~ucBitMask));

	if ( sVal )
	{
		ucByteVal   |= ucBitMask;
	}
	plv->val[ iByte ]   = ucByteVal;
}

void addVal( lenVal*    plvResVal,
	     lenVal*    plvVal1,
	     lenVal*    plvVal2 )
{
	unsigned char   ucCarry;
	unsigned short  usSum;
	unsigned short  usVal1;
	unsigned short  usVal2;
	short           sIndex;

	plvResVal->len  = plvVal1->len;         /* set up length of result */

	/* start at least significant bit and add bytes    */
	ucCarry = 0;
	sIndex  = plvVal1->len;
	while ( sIndex-- )
	{
		usVal1  = plvVal1->val[ sIndex ];   /* i'th byte of val1 */
		usVal2  = plvVal2->val[ sIndex ];   /* i'th byte of val2 */

		/* add the two bytes plus carry from previous addition */
		usSum   = (unsigned short)( usVal1 + usVal2 + ucCarry );

		/* set up carry for next byte */
		ucCarry = (unsigned char)( ( usSum > 255 ) ? 1 : 0 );

		/* set the i'th byte of the result */
		plvResVal->val[ sIndex ]    = (unsigned char)usSum;
	}
}

void readVal( lenVal*   plv,
	      short     sNumBytes )
{
	unsigned char*  pucVal;

	plv->len    = sNumBytes;        /* set the length of the lenVal        */
	for ( pucVal = plv->val; sNumBytes; --sNumBytes, ++pucVal )
	{
		/* read a byte of data into the lenVal */
		readByte( pucVal );
	}
}
