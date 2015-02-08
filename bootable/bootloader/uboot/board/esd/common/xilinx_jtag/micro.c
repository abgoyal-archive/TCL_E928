


#include <common.h>
#include <command.h>
#include <asm/processor.h>

#include "micro.h"
#include "lenval.h"
#include "ports.h"

const unsigned char *xsvfdata;


#define XSVF_VERSION    "5.00"

#ifndef XSVF_SUPPORT_COMPRESSION
#define XSVF_SUPPORT_COMPRESSION    1
#endif

#ifndef XSVF_SUPPORT_ERRORCODES
#define XSVF_SUPPORT_ERRORCODES     1
#endif

#ifdef  XSVF_SUPPORT_ERRORCODES
#define XSVF_ERRORCODE(errorCode)   errorCode
#else   /* Use legacy error code */
#define XSVF_ERRORCODE(errorCode)   ((errorCode==XSVF_ERROR_NONE)?1:0)
#endif  /* XSVF_SUPPORT_ERRORCODES */


#define DEBUG_MODE

#ifdef  DEBUG_MODE
#define XSVFDBG_PRINTF(iDebugLevel,pzFormat) \
		{ if ( xsvf_iDebugLevel >= iDebugLevel ) \
		    printf( pzFormat ); }
#define XSVFDBG_PRINTF1(iDebugLevel,pzFormat,arg1) \
		{ if ( xsvf_iDebugLevel >= iDebugLevel ) \
		    printf( pzFormat, arg1 ); }
#define XSVFDBG_PRINTF2(iDebugLevel,pzFormat,arg1,arg2) \
		{ if ( xsvf_iDebugLevel >= iDebugLevel ) \
		    printf( pzFormat, arg1, arg2 ); }
#define XSVFDBG_PRINTF3(iDebugLevel,pzFormat,arg1,arg2,arg3) \
		{ if ( xsvf_iDebugLevel >= iDebugLevel ) \
		    printf( pzFormat, arg1, arg2, arg3 ); }
#define XSVFDBG_PRINTLENVAL(iDebugLevel,plenVal) \
		{ if ( xsvf_iDebugLevel >= iDebugLevel ) \
		    xsvfPrintLenVal(plenVal); }
#else   /* !DEBUG_MODE */
#define XSVFDBG_PRINTF(iDebugLevel,pzFormat)
#define XSVFDBG_PRINTF1(iDebugLevel,pzFormat,arg1)
#define XSVFDBG_PRINTF2(iDebugLevel,pzFormat,arg1,arg2)
#define XSVFDBG_PRINTF3(iDebugLevel,pzFormat,arg1,arg2,arg3)
#define XSVFDBG_PRINTLENVAL(iDebugLevel,plenVal)
#endif  /* DEBUG_MODE */



typedef struct tagSXsvfInfo
{
	/* XSVF status information */
	unsigned char   ucComplete;         /* 0 = running; 1 = complete */
	unsigned char   ucCommand;          /* Current XSVF command byte */
	long            lCommandCount;      /* Number of commands processed */
	int             iErrorCode;         /* An error code. 0 = no error. */

	/* TAP state/sequencing information */
	unsigned char   ucTapState;         /* Current TAP state */
	unsigned char   ucEndIR;            /* ENDIR TAP state (See SVF) */
	unsigned char   ucEndDR;            /* ENDDR TAP state (See SVF) */

	/* RUNTEST information */
	unsigned char   ucMaxRepeat;        /* Max repeat loops (for xc9500/xl) */
	long            lRunTestTime;       /* Pre-specified RUNTEST time (usec) */

	/* Shift Data Info and Buffers */
	long            lShiftLengthBits;   /* Len. current shift data in bits */
	short           sShiftLengthBytes;  /* Len. current shift data in bytes */

	lenVal          lvTdi;              /* Current TDI shift data */
	lenVal          lvTdoExpected;      /* Expected TDO shift data */
	lenVal          lvTdoCaptured;      /* Captured TDO shift data */
	lenVal          lvTdoMask;          /* TDO mask: 0=dontcare; 1=compare */

#ifdef  XSVF_SUPPORT_COMPRESSION
	/* XSDRINC Data Buffers */
	lenVal          lvAddressMask;      /* Address mask for XSDRINC */
	lenVal          lvDataMask;         /* Data mask for XSDRINC */
	lenVal          lvNextData;         /* Next data for XSDRINC */
#endif  /* XSVF_SUPPORT_COMPRESSION */
} SXsvfInfo;

/* Declare pointer to functions that perform XSVF commands */
typedef int (*TXsvfDoCmdFuncPtr)( SXsvfInfo* );


/* encodings of xsvf instructions */
#define XCOMPLETE        0
#define XTDOMASK         1
#define XSIR             2
#define XSDR             3
#define XRUNTEST         4
/* Reserved              5 */
/* Reserved              6 */
#define XREPEAT          7
#define XSDRSIZE         8
#define XSDRTDO          9
#define XSETSDRMASKS     10
#define XSDRINC          11
#define XSDRB            12
#define XSDRC            13
#define XSDRE            14
#define XSDRTDOB         15
#define XSDRTDOC         16
#define XSDRTDOE         17
#define XSTATE           18         /* 4.00 */
#define XENDIR           19         /* 4.04 */
#define XENDDR           20         /* 4.04 */
#define XSIR2            21         /* 4.10 */
#define XCOMMENT         22         /* 4.14 */
#define XWAIT            23         /* 5.00 */
/* Insert new commands here */
/* and add corresponding xsvfDoCmd function to xsvf_pfDoCmd below. */
#define XLASTCMD         24         /* Last command marker */



#define XSTATE_RESET     0          /* 4.00 parameter for XSTATE */
#define XSTATE_RUNTEST   1          /* 4.00 parameter for XSTATE */

#define XENDXR_RUNTEST   0          /* 4.04 parameter for XENDIR/DR */
#define XENDXR_PAUSE     1          /* 4.04 parameter for XENDIR/DR */

/* TAP states */
#define XTAPSTATE_RESET     0x00
#define XTAPSTATE_RUNTEST   0x01    /* a.k.a. IDLE */
#define XTAPSTATE_SELECTDR  0x02
#define XTAPSTATE_CAPTUREDR 0x03
#define XTAPSTATE_SHIFTDR   0x04
#define XTAPSTATE_EXIT1DR   0x05
#define XTAPSTATE_PAUSEDR   0x06
#define XTAPSTATE_EXIT2DR   0x07
#define XTAPSTATE_UPDATEDR  0x08
#define XTAPSTATE_IRSTATES  0x09    /* All IR states begin here */
#define XTAPSTATE_SELECTIR  0x09
#define XTAPSTATE_CAPTUREIR 0x0A
#define XTAPSTATE_SHIFTIR   0x0B
#define XTAPSTATE_EXIT1IR   0x0C
#define XTAPSTATE_PAUSEIR   0x0D
#define XTAPSTATE_EXIT2IR   0x0E
#define XTAPSTATE_UPDATEIR  0x0F


int xsvfDoIllegalCmd( SXsvfInfo* pXsvfInfo );   /* Illegal command function */
int xsvfDoXCOMPLETE( SXsvfInfo* pXsvfInfo );
int xsvfDoXTDOMASK( SXsvfInfo* pXsvfInfo );
int xsvfDoXSIR( SXsvfInfo* pXsvfInfo );
int xsvfDoXSIR2( SXsvfInfo* pXsvfInfo );
int xsvfDoXSDR( SXsvfInfo* pXsvfInfo );
int xsvfDoXRUNTEST( SXsvfInfo* pXsvfInfo );
int xsvfDoXREPEAT( SXsvfInfo* pXsvfInfo );
int xsvfDoXSDRSIZE( SXsvfInfo* pXsvfInfo );
int xsvfDoXSDRTDO( SXsvfInfo* pXsvfInfo );
int xsvfDoXSETSDRMASKS( SXsvfInfo* pXsvfInfo );
int xsvfDoXSDRINC( SXsvfInfo* pXsvfInfo );
int xsvfDoXSDRBCE( SXsvfInfo* pXsvfInfo );
int xsvfDoXSDRTDOBCE( SXsvfInfo* pXsvfInfo );
int xsvfDoXSTATE( SXsvfInfo* pXsvfInfo );
int xsvfDoXENDXR( SXsvfInfo* pXsvfInfo );
int xsvfDoXCOMMENT( SXsvfInfo* pXsvfInfo );
int xsvfDoXWAIT( SXsvfInfo* pXsvfInfo );
/* Insert new command functions here */


/* Array of XSVF command functions.  Must follow command byte value order! */
/* If your compiler cannot take this form, then convert to a switch statement*/
TXsvfDoCmdFuncPtr   xsvf_pfDoCmd[]  =
{
	xsvfDoXCOMPLETE,        /*  0 */
	xsvfDoXTDOMASK,         /*  1 */
	xsvfDoXSIR,             /*  2 */
	xsvfDoXSDR,             /*  3 */
	xsvfDoXRUNTEST,         /*  4 */
	xsvfDoIllegalCmd,       /*  5 */
	xsvfDoIllegalCmd,       /*  6 */
	xsvfDoXREPEAT,          /*  7 */
	xsvfDoXSDRSIZE,         /*  8 */
	xsvfDoXSDRTDO,          /*  9 */
#ifdef  XSVF_SUPPORT_COMPRESSION
	xsvfDoXSETSDRMASKS,     /* 10 */
	xsvfDoXSDRINC,          /* 11 */
#else
	xsvfDoIllegalCmd,       /* 10 */
	xsvfDoIllegalCmd,       /* 11 */
#endif  /* XSVF_SUPPORT_COMPRESSION */
	xsvfDoXSDRBCE,          /* 12 */
	xsvfDoXSDRBCE,          /* 13 */
	xsvfDoXSDRBCE,          /* 14 */
	xsvfDoXSDRTDOBCE,       /* 15 */
	xsvfDoXSDRTDOBCE,       /* 16 */
	xsvfDoXSDRTDOBCE,       /* 17 */
	xsvfDoXSTATE,           /* 18 */
	xsvfDoXENDXR,           /* 19 */
	xsvfDoXENDXR,           /* 20 */
	xsvfDoXSIR2,            /* 21 */
	xsvfDoXCOMMENT,         /* 22 */
	xsvfDoXWAIT             /* 23 */
/* Insert new command functions here */
};

#ifdef  DEBUG_MODE
char* xsvf_pzCommandName[]  =
{
	"XCOMPLETE",
	"XTDOMASK",
	"XSIR",
	"XSDR",
	"XRUNTEST",
	"Reserved5",
	"Reserved6",
	"XREPEAT",
	"XSDRSIZE",
	"XSDRTDO",
	"XSETSDRMASKS",
	"XSDRINC",
	"XSDRB",
	"XSDRC",
	"XSDRE",
	"XSDRTDOB",
	"XSDRTDOC",
	"XSDRTDOE",
	"XSTATE",
	"XENDIR",
	"XENDDR",
	"XSIR2",
	"XCOMMENT",
	"XWAIT"
};

char*   xsvf_pzErrorName[]  =
{
	"No error",
	"ERROR:  Unknown",
	"ERROR:  TDO mismatch",
	"ERROR:  TDO mismatch and exceeded max retries",
	"ERROR:  Unsupported XSVF command",
	"ERROR:  Illegal state specification",
	"ERROR:  Data overflows allocated MAX_LEN buffer size"
};

char*   xsvf_pzTapState[] =
{
	"RESET",        /* 0x00 */
	"RUNTEST/IDLE", /* 0x01 */
	"DRSELECT",     /* 0x02 */
	"DRCAPTURE",    /* 0x03 */
	"DRSHIFT",      /* 0x04 */
	"DREXIT1",      /* 0x05 */
	"DRPAUSE",      /* 0x06 */
	"DREXIT2",      /* 0x07 */
	"DRUPDATE",     /* 0x08 */
	"IRSELECT",     /* 0x09 */
	"IRCAPTURE",    /* 0x0A */
	"IRSHIFT",      /* 0x0B */
	"IREXIT1",      /* 0x0C */
	"IRPAUSE",      /* 0x0D */
	"IREXIT2",      /* 0x0E */
	"IRUPDATE"      /* 0x0F */
};
#endif  /* DEBUG_MODE */

/*#ifdef DEBUG_MODE	*/
/*    FILE* in;   /XXX* Legacy DEBUG_MODE file pointer */
int xsvf_iDebugLevel;
/*#endif /XXX* DEBUG_MODE */


#ifdef  DEBUG_MODE
void xsvfPrintLenVal( lenVal *plv )
{
	int i;

	if ( plv )
	{
		printf( "0x" );
		for ( i = 0; i < plv->len; ++i )
		{
			printf( "%02x", ((unsigned int)(plv->val[ i ])) );
		}
	}
}
#endif  /* DEBUG_MODE */


int xsvfInfoInit( SXsvfInfo* pXsvfInfo )
{
	XSVFDBG_PRINTF1( 4, "    sizeof( SXsvfInfo ) = %d bytes\n",
			 sizeof( SXsvfInfo ) );

	pXsvfInfo->ucComplete       = 0;
	pXsvfInfo->ucCommand        = XCOMPLETE;
	pXsvfInfo->lCommandCount    = 0;
	pXsvfInfo->iErrorCode       = XSVF_ERROR_NONE;
	pXsvfInfo->ucMaxRepeat      = 0;
	pXsvfInfo->ucTapState       = XTAPSTATE_RESET;
	pXsvfInfo->ucEndIR          = XTAPSTATE_RUNTEST;
	pXsvfInfo->ucEndDR          = XTAPSTATE_RUNTEST;
	pXsvfInfo->lShiftLengthBits = 0L;
	pXsvfInfo->sShiftLengthBytes= 0;
	pXsvfInfo->lRunTestTime     = 0L;

	return( 0 );
}

void xsvfInfoCleanup( SXsvfInfo* pXsvfInfo )
{
}

short xsvfGetAsNumBytes( long lNumBits )
{
	return( (short)( ( lNumBits + 7L ) / 8L ) );
}

void xsvfTmsTransition( short sTms )
{
	setPort( TMS, sTms );
	setPort( TCK, 0 );
	setPort( TCK, 1 );
}

int xsvfGotoTapState( unsigned char*   pucTapState,
		      unsigned char    ucTargetState )
{
	int i;
	int iErrorCode;

	iErrorCode  = XSVF_ERROR_NONE;
	if ( ucTargetState == XTAPSTATE_RESET )
	{
		/* If RESET, always perform TMS reset sequence to reset/sync TAPs */
		xsvfTmsTransition( 1 );
		for ( i = 0; i < 5; ++i )
		{
			setPort( TCK, 0 );
			setPort( TCK, 1 );
		}
		*pucTapState    = XTAPSTATE_RESET;
		XSVFDBG_PRINTF( 3, "   TMS Reset Sequence -> Test-Logic-Reset\n" );
		XSVFDBG_PRINTF1( 3, "   TAP State = %s\n",
				 xsvf_pzTapState[ *pucTapState ] );
	} else if ( ( ucTargetState != *pucTapState ) &&
		  ( ( ( ucTargetState == XTAPSTATE_EXIT2DR ) && ( *pucTapState != XTAPSTATE_PAUSEDR ) ) ||
		    ( ( ucTargetState == XTAPSTATE_EXIT2IR ) && ( *pucTapState != XTAPSTATE_PAUSEIR ) ) ) )
	{
		/* Trap illegal TAP state path specification */
		iErrorCode      = XSVF_ERROR_ILLEGALSTATE;
	} else {
		if ( ucTargetState == *pucTapState )
		{
			/* Already in target state.  Do nothing except when in DRPAUSE
			   or in IRPAUSE to comply with SVF standard */
			if ( ucTargetState == XTAPSTATE_PAUSEDR )
			{
				xsvfTmsTransition( 1 );
				*pucTapState    = XTAPSTATE_EXIT2DR;
				XSVFDBG_PRINTF1( 3, "   TAP State = %s\n",
						 xsvf_pzTapState[ *pucTapState ] );
			}
			else if ( ucTargetState == XTAPSTATE_PAUSEIR )
			{
				xsvfTmsTransition( 1 );
				*pucTapState    = XTAPSTATE_EXIT2IR;
				XSVFDBG_PRINTF1( 3, "   TAP State = %s\n",
						 xsvf_pzTapState[ *pucTapState ] );
			}
		}

		/* Perform TAP state transitions to get to the target state */
		while ( ucTargetState != *pucTapState )
		{
			switch ( *pucTapState )
			{
			case XTAPSTATE_RESET:
				xsvfTmsTransition( 0 );
				*pucTapState    = XTAPSTATE_RUNTEST;
				break;
			case XTAPSTATE_RUNTEST:
				xsvfTmsTransition( 1 );
				*pucTapState    = XTAPSTATE_SELECTDR;
				break;
			case XTAPSTATE_SELECTDR:
				if ( ucTargetState >= XTAPSTATE_IRSTATES )
				{
					xsvfTmsTransition( 1 );
					*pucTapState    = XTAPSTATE_SELECTIR;
				}
				else
				{
					xsvfTmsTransition( 0 );
					*pucTapState    = XTAPSTATE_CAPTUREDR;
				}
				break;
			case XTAPSTATE_CAPTUREDR:
				if ( ucTargetState == XTAPSTATE_SHIFTDR )
				{
					xsvfTmsTransition( 0 );
					*pucTapState    = XTAPSTATE_SHIFTDR;
				}
				else
				{
					xsvfTmsTransition( 1 );
					*pucTapState    = XTAPSTATE_EXIT1DR;
				}
				break;
			case XTAPSTATE_SHIFTDR:
				xsvfTmsTransition( 1 );
				*pucTapState    = XTAPSTATE_EXIT1DR;
				break;
			case XTAPSTATE_EXIT1DR:
				if ( ucTargetState == XTAPSTATE_PAUSEDR )
				{
					xsvfTmsTransition( 0 );
					*pucTapState    = XTAPSTATE_PAUSEDR;
				}
				else
				{
					xsvfTmsTransition( 1 );
					*pucTapState    = XTAPSTATE_UPDATEDR;
				}
				break;
			case XTAPSTATE_PAUSEDR:
				xsvfTmsTransition( 1 );
				*pucTapState    = XTAPSTATE_EXIT2DR;
				break;
			case XTAPSTATE_EXIT2DR:
				if ( ucTargetState == XTAPSTATE_SHIFTDR )
				{
					xsvfTmsTransition( 0 );
					*pucTapState    = XTAPSTATE_SHIFTDR;
				}
				else
				{
					xsvfTmsTransition( 1 );
					*pucTapState    = XTAPSTATE_UPDATEDR;
				}
				break;
			case XTAPSTATE_UPDATEDR:
				if ( ucTargetState == XTAPSTATE_RUNTEST )
				{
					xsvfTmsTransition( 0 );
					*pucTapState    = XTAPSTATE_RUNTEST;
				}
				else
				{
					xsvfTmsTransition( 1 );
					*pucTapState    = XTAPSTATE_SELECTDR;
				}
				break;
			case XTAPSTATE_SELECTIR:
				xsvfTmsTransition( 0 );
				*pucTapState    = XTAPSTATE_CAPTUREIR;
				break;
			case XTAPSTATE_CAPTUREIR:
				if ( ucTargetState == XTAPSTATE_SHIFTIR )
				{
					xsvfTmsTransition( 0 );
					*pucTapState    = XTAPSTATE_SHIFTIR;
				}
				else
				{
					xsvfTmsTransition( 1 );
					*pucTapState    = XTAPSTATE_EXIT1IR;
				}
				break;
			case XTAPSTATE_SHIFTIR:
				xsvfTmsTransition( 1 );
				*pucTapState    = XTAPSTATE_EXIT1IR;
				break;
			case XTAPSTATE_EXIT1IR:
				if ( ucTargetState == XTAPSTATE_PAUSEIR )
				{
					xsvfTmsTransition( 0 );
					*pucTapState    = XTAPSTATE_PAUSEIR;
				}
				else
				{
					xsvfTmsTransition( 1 );
					*pucTapState    = XTAPSTATE_UPDATEIR;
				}
				break;
			case XTAPSTATE_PAUSEIR:
				xsvfTmsTransition( 1 );
				*pucTapState    = XTAPSTATE_EXIT2IR;
				break;
			case XTAPSTATE_EXIT2IR:
				if ( ucTargetState == XTAPSTATE_SHIFTIR )
				{
					xsvfTmsTransition( 0 );
					*pucTapState    = XTAPSTATE_SHIFTIR;
				}
				else
				{
					xsvfTmsTransition( 1 );
					*pucTapState    = XTAPSTATE_UPDATEIR;
				}
				break;
			case XTAPSTATE_UPDATEIR:
				if ( ucTargetState == XTAPSTATE_RUNTEST )
				{
					xsvfTmsTransition( 0 );
					*pucTapState    = XTAPSTATE_RUNTEST;
				}
				else
				{
					xsvfTmsTransition( 1 );
					*pucTapState    = XTAPSTATE_SELECTDR;
				}
				break;
			default:
				iErrorCode      = XSVF_ERROR_ILLEGALSTATE;
				*pucTapState    = ucTargetState;    /* Exit while loop */
				break;
			}
			XSVFDBG_PRINTF1( 3, "   TAP State = %s\n",
					 xsvf_pzTapState[ *pucTapState ] );
		}
	}

	return( iErrorCode );
}

void xsvfShiftOnly( long    lNumBits,
		    lenVal* plvTdi,
		    lenVal* plvTdoCaptured,
		    int     iExitShift )
{
	unsigned char*  pucTdi;
	unsigned char*  pucTdo;
	unsigned char   ucTdiByte;
	unsigned char   ucTdoByte;
	unsigned char   ucTdoBit;
	int             i;

	/* assert( ( ( lNumBits + 7 ) / 8 ) == plvTdi->len ); */

	/* Initialize TDO storage len == TDI len */
	pucTdo  = 0;
	if ( plvTdoCaptured )
	{
		plvTdoCaptured->len = plvTdi->len;
		pucTdo              = plvTdoCaptured->val + plvTdi->len;
	}

	/* Shift LSB first.  val[N-1] == LSB.  val[0] == MSB. */
	pucTdi  = plvTdi->val + plvTdi->len;
	while ( lNumBits )
	{
		/* Process on a byte-basis */
		ucTdiByte   = (*(--pucTdi));
		ucTdoByte   = 0;
		for ( i = 0; ( lNumBits && ( i < 8 ) ); ++i )
		{
			--lNumBits;
			if ( iExitShift && !lNumBits )
			{
				/* Exit Shift-DR state */
				setPort( TMS, 1 );
			}

			/* Set the new TDI value */
			setPort( TDI, (short)(ucTdiByte & 1) );
			ucTdiByte   >>= 1;

			/* Set TCK low */
			setPort( TCK, 0 );

			if ( pucTdo )
			{
				/* Save the TDO value */
				ucTdoBit    = readTDOBit();
				ucTdoByte   |= ( ucTdoBit << i );
			}

			/* Set TCK high */
			setPort( TCK, 1 );
		}

		/* Save the TDO byte value */
		if ( pucTdo )
		{
			(*(--pucTdo))   = ucTdoByte;
		}
	}
}

int xsvfShift( unsigned char*   pucTapState,
	       unsigned char    ucStartState,
	       long             lNumBits,
	       lenVal*          plvTdi,
	       lenVal*          plvTdoCaptured,
	       lenVal*          plvTdoExpected,
	       lenVal*          plvTdoMask,
	       unsigned char    ucEndState,
	       long             lRunTestTime,
	       unsigned char    ucMaxRepeat )
{
	int             iErrorCode;
	int             iMismatch;
	unsigned char   ucRepeat;
	int             iExitShift;

	iErrorCode  = XSVF_ERROR_NONE;
	iMismatch   = 0;
	ucRepeat    = 0;
	iExitShift  = ( ucStartState != ucEndState );

	XSVFDBG_PRINTF1( 3, "   Shift Length = %ld\n", lNumBits );
	XSVFDBG_PRINTF( 4, "    TDI          = ");
	XSVFDBG_PRINTLENVAL( 4, plvTdi );
	XSVFDBG_PRINTF( 4, "\n");
	XSVFDBG_PRINTF( 4, "    TDO Expected = ");
	XSVFDBG_PRINTLENVAL( 4, plvTdoExpected );
	XSVFDBG_PRINTF( 4, "\n");

	if ( !lNumBits )
	{
		/* Compatibility with XSVF2.00:  XSDR 0 = no shift, but wait in RTI */
		if ( lRunTestTime )
		{
			/* Wait for prespecified XRUNTEST time */
			xsvfGotoTapState( pucTapState, XTAPSTATE_RUNTEST );
			XSVFDBG_PRINTF1( 3, "   Wait = %ld usec\n", lRunTestTime );
			waitTime( lRunTestTime );
		}
	}
	else
	{
		do
		{
			/* Goto Shift-DR or Shift-IR */
			xsvfGotoTapState( pucTapState, ucStartState );

			/* Shift TDI and capture TDO */
			xsvfShiftOnly( lNumBits, plvTdi, plvTdoCaptured, iExitShift );

			if ( plvTdoExpected )
			{
				/* Compare TDO data to expected TDO data */
				iMismatch   = !EqualLenVal( plvTdoExpected,
							    plvTdoCaptured,
							    plvTdoMask );
			}

			if ( iExitShift )
			{
				/* Update TAP state:  Shift->Exit */
				++(*pucTapState);
				XSVFDBG_PRINTF1( 3, "   TAP State = %s\n",
						 xsvf_pzTapState[ *pucTapState ] );

				if ( iMismatch && lRunTestTime && ( ucRepeat < ucMaxRepeat ) )
				{
					XSVFDBG_PRINTF( 4, "    TDO Expected = ");
					XSVFDBG_PRINTLENVAL( 4, plvTdoExpected );
					XSVFDBG_PRINTF( 4, "\n");
					XSVFDBG_PRINTF( 4, "    TDO Captured = ");
					XSVFDBG_PRINTLENVAL( 4, plvTdoCaptured );
					XSVFDBG_PRINTF( 4, "\n");
					XSVFDBG_PRINTF( 4, "    TDO Mask     = ");
					XSVFDBG_PRINTLENVAL( 4, plvTdoMask );
					XSVFDBG_PRINTF( 4, "\n");
					XSVFDBG_PRINTF1( 3, "   Retry #%d\n", ( ucRepeat + 1 ) );
					/* Do exception handling retry - ShiftDR only */
					xsvfGotoTapState( pucTapState, XTAPSTATE_PAUSEDR );
					/* Shift 1 extra bit */
					xsvfGotoTapState( pucTapState, XTAPSTATE_SHIFTDR );
					/* Increment RUNTEST time by an additional 25% */
					lRunTestTime    += ( lRunTestTime >> 2 );
				}
				else
				{
					/* Do normal exit from Shift-XR */
					xsvfGotoTapState( pucTapState, ucEndState );
				}

				if ( lRunTestTime )
				{
					/* Wait for prespecified XRUNTEST time */
					xsvfGotoTapState( pucTapState, XTAPSTATE_RUNTEST );
					XSVFDBG_PRINTF1( 3, "   Wait = %ld usec\n", lRunTestTime );
					waitTime( lRunTestTime );
				}
			}
		} while ( iMismatch && ( ucRepeat++ < ucMaxRepeat ) );
	}

	if ( iMismatch )
	{
		XSVFDBG_PRINTF( 1, " TDO Expected = ");
		XSVFDBG_PRINTLENVAL( 1, plvTdoExpected );
		XSVFDBG_PRINTF( 1, "\n");
		XSVFDBG_PRINTF( 1, " TDO Captured = ");
		XSVFDBG_PRINTLENVAL( 1, plvTdoCaptured );
		XSVFDBG_PRINTF( 1, "\n");
		XSVFDBG_PRINTF( 1, " TDO Mask     = ");
		XSVFDBG_PRINTLENVAL( 1, plvTdoMask );
		XSVFDBG_PRINTF( 1, "\n");
		if ( ucMaxRepeat && ( ucRepeat > ucMaxRepeat ) )
		{
			iErrorCode  = XSVF_ERROR_MAXRETRIES;
		}
		else
		{
			iErrorCode  = XSVF_ERROR_TDOMISMATCH;
		}
	}

	return( iErrorCode );
}

int xsvfBasicXSDRTDO( unsigned char*    pucTapState,
		      long              lShiftLengthBits,
		      short             sShiftLengthBytes,
		      lenVal*           plvTdi,
		      lenVal*           plvTdoCaptured,
		      lenVal*           plvTdoExpected,
		      lenVal*           plvTdoMask,
		      unsigned char     ucEndState,
		      long              lRunTestTime,
		      unsigned char     ucMaxRepeat )
{
	readVal( plvTdi, sShiftLengthBytes );
	if ( plvTdoExpected )
	{
		readVal( plvTdoExpected, sShiftLengthBytes );
	}
	return( xsvfShift( pucTapState, XTAPSTATE_SHIFTDR, lShiftLengthBits,
			   plvTdi, plvTdoCaptured, plvTdoExpected, plvTdoMask,
			   ucEndState, lRunTestTime, ucMaxRepeat ) );
}

#ifdef  XSVF_SUPPORT_COMPRESSION
void xsvfDoSDRMasking( lenVal*  plvTdi,
		       lenVal*  plvNextData,
		       lenVal*  plvAddressMask,
		       lenVal*  plvDataMask )
{
	int             i;
	unsigned char   ucTdi;
	unsigned char   ucTdiMask;
	unsigned char   ucDataMask;
	unsigned char   ucNextData;
	unsigned char   ucNextMask;
	short           sNextData;

	/* add the address Mask to dataVal and return as a new dataVal */
	addVal( plvTdi, plvTdi, plvAddressMask );

	ucNextData  = 0;
	ucNextMask  = 0;
	sNextData   = plvNextData->len;
	for ( i = plvDataMask->len - 1; i >= 0; --i )
	{
		/* Go through data mask in reverse order looking for mask (1) bits */
		ucDataMask  = plvDataMask->val[ i ];
		if ( ucDataMask )
		{
			/* Retrieve the corresponding TDI byte value */
			ucTdi       = plvTdi->val[ i ];

			/* For each bit in the data mask byte, look for 1's */
			ucTdiMask   = 1;
			while ( ucDataMask )
			{
				if ( ucDataMask & 1 )
				{
					if ( !ucNextMask )
					{
						/* Get the next data byte */
						ucNextData  = plvNextData->val[ --sNextData ];
						ucNextMask  = 1;
					}

					/* Set or clear the data bit according to the next data */
					if ( ucNextData & ucNextMask )
					{
						ucTdi   |= ucTdiMask;       /* Set bit */
					}
					else
					{
						ucTdi   &= ( ~ucTdiMask );  /* Clear bit */
					}

					/* Update the next data */
					ucNextMask  <<= 1;
				}
				ucTdiMask   <<= 1;
				ucDataMask  >>= 1;
			}

			/* Update the TDI value */
			plvTdi->val[ i ]    = ucTdi;
		}
	}
}
#endif  /* XSVF_SUPPORT_COMPRESSION */


int xsvfDoIllegalCmd( SXsvfInfo* pXsvfInfo )
{
	XSVFDBG_PRINTF2( 0, "ERROR:  Encountered unsupported command #%d (%s)\n",
			 ((unsigned int)(pXsvfInfo->ucCommand)),
			 ((pXsvfInfo->ucCommand < XLASTCMD)
			  ? (xsvf_pzCommandName[pXsvfInfo->ucCommand])
			  : "Unknown") );
	pXsvfInfo->iErrorCode   = XSVF_ERROR_ILLEGALCMD;
	return( pXsvfInfo->iErrorCode );
}

int xsvfDoXCOMPLETE( SXsvfInfo* pXsvfInfo )
{
	pXsvfInfo->ucComplete   = 1;
	return( XSVF_ERROR_NONE );
}

int xsvfDoXTDOMASK( SXsvfInfo* pXsvfInfo )
{
	readVal( &(pXsvfInfo->lvTdoMask), pXsvfInfo->sShiftLengthBytes );
	XSVFDBG_PRINTF( 4, "    TDO Mask     = ");
	XSVFDBG_PRINTLENVAL( 4, &(pXsvfInfo->lvTdoMask) );
	XSVFDBG_PRINTF( 4, "\n");
	return( XSVF_ERROR_NONE );
}

int xsvfDoXSIR( SXsvfInfo* pXsvfInfo )
{
	unsigned char   ucShiftIrBits;
	short           sShiftIrBytes;
	int             iErrorCode;

	/* Get the shift length and store */
	readByte( &ucShiftIrBits );
	sShiftIrBytes   = xsvfGetAsNumBytes( ucShiftIrBits );
	XSVFDBG_PRINTF1( 3, "   XSIR length = %d\n",
			 ((unsigned int)ucShiftIrBits) );

	if ( sShiftIrBytes > MAX_LEN )
	{
		iErrorCode  = XSVF_ERROR_DATAOVERFLOW;
	}
	else
	{
		/* Get and store instruction to shift in */
		readVal( &(pXsvfInfo->lvTdi), xsvfGetAsNumBytes( ucShiftIrBits ) );

		/* Shift the data */
		iErrorCode  = xsvfShift( &(pXsvfInfo->ucTapState), XTAPSTATE_SHIFTIR,
					 ucShiftIrBits, &(pXsvfInfo->lvTdi),
					 /*plvTdoCaptured*/0, /*plvTdoExpected*/0,
					 /*plvTdoMask*/0, pXsvfInfo->ucEndIR,
					 pXsvfInfo->lRunTestTime, /*ucMaxRepeat*/0 );
	}

	if ( iErrorCode != XSVF_ERROR_NONE )
	{
		pXsvfInfo->iErrorCode   = iErrorCode;
	}
	return( iErrorCode );
}

int xsvfDoXSIR2( SXsvfInfo* pXsvfInfo )
{
	long            lShiftIrBits;
	short           sShiftIrBytes;
	int             iErrorCode;

	/* Get the shift length and store */
	readVal( &(pXsvfInfo->lvTdi), 2 );
	lShiftIrBits    = value( &(pXsvfInfo->lvTdi) );
	sShiftIrBytes   = xsvfGetAsNumBytes( lShiftIrBits );
	XSVFDBG_PRINTF1( 3, "   XSIR2 length = %d\n", (int)lShiftIrBits);

	if ( sShiftIrBytes > MAX_LEN )
	{
		iErrorCode  = XSVF_ERROR_DATAOVERFLOW;
	}
	else
	{
		/* Get and store instruction to shift in */
		readVal( &(pXsvfInfo->lvTdi), xsvfGetAsNumBytes( lShiftIrBits ) );

		/* Shift the data */
		iErrorCode  = xsvfShift( &(pXsvfInfo->ucTapState), XTAPSTATE_SHIFTIR,
					 lShiftIrBits, &(pXsvfInfo->lvTdi),
					 /*plvTdoCaptured*/0, /*plvTdoExpected*/0,
					 /*plvTdoMask*/0, pXsvfInfo->ucEndIR,
					 pXsvfInfo->lRunTestTime, /*ucMaxRepeat*/0 );
	}

	if ( iErrorCode != XSVF_ERROR_NONE )
	{
		pXsvfInfo->iErrorCode   = iErrorCode;
	}
	return( iErrorCode );
}

int xsvfDoXSDR( SXsvfInfo* pXsvfInfo )
{
	int iErrorCode;
	readVal( &(pXsvfInfo->lvTdi), pXsvfInfo->sShiftLengthBytes );
	/* use TDOExpected from last XSDRTDO instruction */
	iErrorCode  = xsvfShift( &(pXsvfInfo->ucTapState), XTAPSTATE_SHIFTDR,
				 pXsvfInfo->lShiftLengthBits, &(pXsvfInfo->lvTdi),
				 &(pXsvfInfo->lvTdoCaptured),
				 &(pXsvfInfo->lvTdoExpected),
				 &(pXsvfInfo->lvTdoMask), pXsvfInfo->ucEndDR,
				 pXsvfInfo->lRunTestTime, pXsvfInfo->ucMaxRepeat );
	if ( iErrorCode != XSVF_ERROR_NONE )
	{
		pXsvfInfo->iErrorCode   = iErrorCode;
	}
	return( iErrorCode );
}

int xsvfDoXRUNTEST( SXsvfInfo* pXsvfInfo )
{
	readVal( &(pXsvfInfo->lvTdi), 4 );
	pXsvfInfo->lRunTestTime = value( &(pXsvfInfo->lvTdi) );
	XSVFDBG_PRINTF1( 3, "   XRUNTEST = %ld\n", pXsvfInfo->lRunTestTime );
	return( XSVF_ERROR_NONE );
}

int xsvfDoXREPEAT( SXsvfInfo* pXsvfInfo )
{
	readByte( &(pXsvfInfo->ucMaxRepeat) );
	XSVFDBG_PRINTF1( 3, "   XREPEAT = %d\n",
			 ((unsigned int)(pXsvfInfo->ucMaxRepeat)) );
	return( XSVF_ERROR_NONE );
}

int xsvfDoXSDRSIZE( SXsvfInfo* pXsvfInfo )
{
	int iErrorCode;
	iErrorCode  = XSVF_ERROR_NONE;
	readVal( &(pXsvfInfo->lvTdi), 4 );
	pXsvfInfo->lShiftLengthBits = value( &(pXsvfInfo->lvTdi) );
	pXsvfInfo->sShiftLengthBytes= xsvfGetAsNumBytes( pXsvfInfo->lShiftLengthBits );
	XSVFDBG_PRINTF1( 3, "   XSDRSIZE = %ld\n", pXsvfInfo->lShiftLengthBits );
	if ( pXsvfInfo->sShiftLengthBytes > MAX_LEN )
	{
		iErrorCode  = XSVF_ERROR_DATAOVERFLOW;
		pXsvfInfo->iErrorCode   = iErrorCode;
	}
	return( iErrorCode );
}

int xsvfDoXSDRTDO( SXsvfInfo* pXsvfInfo )
{
	int iErrorCode;
	iErrorCode  = xsvfBasicXSDRTDO( &(pXsvfInfo->ucTapState),
					pXsvfInfo->lShiftLengthBits,
					pXsvfInfo->sShiftLengthBytes,
					&(pXsvfInfo->lvTdi),
					&(pXsvfInfo->lvTdoCaptured),
					&(pXsvfInfo->lvTdoExpected),
					&(pXsvfInfo->lvTdoMask),
					pXsvfInfo->ucEndDR,
					pXsvfInfo->lRunTestTime,
					pXsvfInfo->ucMaxRepeat );
	if ( iErrorCode != XSVF_ERROR_NONE )
	{
		pXsvfInfo->iErrorCode   = iErrorCode;
	}
	return( iErrorCode );
}

#ifdef  XSVF_SUPPORT_COMPRESSION
int xsvfDoXSETSDRMASKS( SXsvfInfo* pXsvfInfo )
{
	/* read the addressMask */
	readVal( &(pXsvfInfo->lvAddressMask), pXsvfInfo->sShiftLengthBytes );
	/* read the dataMask    */
	readVal( &(pXsvfInfo->lvDataMask), pXsvfInfo->sShiftLengthBytes );

	XSVFDBG_PRINTF( 4, "    Address Mask = " );
	XSVFDBG_PRINTLENVAL( 4, &(pXsvfInfo->lvAddressMask) );
	XSVFDBG_PRINTF( 4, "\n" );
	XSVFDBG_PRINTF( 4, "    Data Mask    = " );
	XSVFDBG_PRINTLENVAL( 4, &(pXsvfInfo->lvDataMask) );
	XSVFDBG_PRINTF( 4, "\n" );

	return( XSVF_ERROR_NONE );
}
#endif  /* XSVF_SUPPORT_COMPRESSION */

#ifdef  XSVF_SUPPORT_COMPRESSION
int xsvfDoXSDRINC( SXsvfInfo* pXsvfInfo )
{
	int             iErrorCode;
	int             iDataMaskLen;
	unsigned char   ucDataMask;
	unsigned char   ucNumTimes;
	unsigned char   i;

	readVal( &(pXsvfInfo->lvTdi), pXsvfInfo->sShiftLengthBytes );
	iErrorCode  = xsvfShift( &(pXsvfInfo->ucTapState), XTAPSTATE_SHIFTDR,
				 pXsvfInfo->lShiftLengthBits,
				 &(pXsvfInfo->lvTdi), &(pXsvfInfo->lvTdoCaptured),
				 &(pXsvfInfo->lvTdoExpected),
				 &(pXsvfInfo->lvTdoMask), pXsvfInfo->ucEndDR,
				 pXsvfInfo->lRunTestTime, pXsvfInfo->ucMaxRepeat );
	if ( !iErrorCode )
	{
		/* Calculate number of data mask bits */
		iDataMaskLen    = 0;
		for ( i = 0; i < pXsvfInfo->lvDataMask.len; ++i )
		{
			ucDataMask  = pXsvfInfo->lvDataMask.val[ i ];
			while ( ucDataMask )
			{
				iDataMaskLen    += ( ucDataMask & 1 );
				ucDataMask      >>= 1;
			}
		}

		/* Get the number of data pieces, i.e. number of times to shift */
		readByte( &ucNumTimes );

		/* For numTimes, get data, fix TDI, and shift */
		for ( i = 0; !iErrorCode && ( i < ucNumTimes ); ++i )
		{
			readVal( &(pXsvfInfo->lvNextData),
				 xsvfGetAsNumBytes( iDataMaskLen ) );
			xsvfDoSDRMasking( &(pXsvfInfo->lvTdi),
					  &(pXsvfInfo->lvNextData),
					  &(pXsvfInfo->lvAddressMask),
					  &(pXsvfInfo->lvDataMask) );
			iErrorCode  = xsvfShift( &(pXsvfInfo->ucTapState),
						 XTAPSTATE_SHIFTDR,
						 pXsvfInfo->lShiftLengthBits,
						 &(pXsvfInfo->lvTdi),
						 &(pXsvfInfo->lvTdoCaptured),
						 &(pXsvfInfo->lvTdoExpected),
						 &(pXsvfInfo->lvTdoMask),
						 pXsvfInfo->ucEndDR,
						 pXsvfInfo->lRunTestTime,
						 pXsvfInfo->ucMaxRepeat );
		}
	}
	if ( iErrorCode != XSVF_ERROR_NONE )
	{
		pXsvfInfo->iErrorCode   = iErrorCode;
	}
	return( iErrorCode );
}
#endif  /* XSVF_SUPPORT_COMPRESSION */

int xsvfDoXSDRBCE( SXsvfInfo* pXsvfInfo )
{
	unsigned char   ucEndDR;
	int             iErrorCode;
	ucEndDR = (unsigned char)(( pXsvfInfo->ucCommand == XSDRE ) ?
				  pXsvfInfo->ucEndDR : XTAPSTATE_SHIFTDR);
	iErrorCode  = xsvfBasicXSDRTDO( &(pXsvfInfo->ucTapState),
					pXsvfInfo->lShiftLengthBits,
					pXsvfInfo->sShiftLengthBytes,
					&(pXsvfInfo->lvTdi),
					/*plvTdoCaptured*/0, /*plvTdoExpected*/0,
					/*plvTdoMask*/0, ucEndDR,
					/*lRunTestTime*/0, /*ucMaxRepeat*/0 );
	if ( iErrorCode != XSVF_ERROR_NONE )
	{
		pXsvfInfo->iErrorCode   = iErrorCode;
	}
	return( iErrorCode );
}

int xsvfDoXSDRTDOBCE( SXsvfInfo* pXsvfInfo )
{
	unsigned char   ucEndDR;
	int             iErrorCode;
	ucEndDR = (unsigned char)(( pXsvfInfo->ucCommand == XSDRTDOE ) ?
				  pXsvfInfo->ucEndDR : XTAPSTATE_SHIFTDR);
	iErrorCode  = xsvfBasicXSDRTDO( &(pXsvfInfo->ucTapState),
					pXsvfInfo->lShiftLengthBits,
					pXsvfInfo->sShiftLengthBytes,
					&(pXsvfInfo->lvTdi),
					&(pXsvfInfo->lvTdoCaptured),
					&(pXsvfInfo->lvTdoExpected),
					/*plvTdoMask*/0, ucEndDR,
					/*lRunTestTime*/0, /*ucMaxRepeat*/0 );
	if ( iErrorCode != XSVF_ERROR_NONE )
	{
		pXsvfInfo->iErrorCode   = iErrorCode;
	}
	return( iErrorCode );
}

int xsvfDoXSTATE( SXsvfInfo* pXsvfInfo )
{
	unsigned char   ucNextState;
	int             iErrorCode;
	readByte( &ucNextState );
	iErrorCode  = xsvfGotoTapState( &(pXsvfInfo->ucTapState), ucNextState );
	if ( iErrorCode != XSVF_ERROR_NONE )
	{
		pXsvfInfo->iErrorCode   = iErrorCode;
	}
	return( iErrorCode );
}

int xsvfDoXENDXR( SXsvfInfo* pXsvfInfo )
{
	int             iErrorCode;
	unsigned char   ucEndState;

	iErrorCode  = XSVF_ERROR_NONE;
	readByte( &ucEndState );
	if ( ( ucEndState != XENDXR_RUNTEST ) && ( ucEndState != XENDXR_PAUSE ) )
	{
		iErrorCode  = XSVF_ERROR_ILLEGALSTATE;
	}
	else
	{

		if ( pXsvfInfo->ucCommand == XENDIR )
		{
			if ( ucEndState == XENDXR_RUNTEST )
			{
				pXsvfInfo->ucEndIR  = XTAPSTATE_RUNTEST;
			}
			else
			{
				pXsvfInfo->ucEndIR  = XTAPSTATE_PAUSEIR;
			}
			XSVFDBG_PRINTF1( 3, "   ENDIR State = %s\n",
					 xsvf_pzTapState[ pXsvfInfo->ucEndIR ] );
		}
		else    /* XENDDR */
		{
			if ( ucEndState == XENDXR_RUNTEST )
			{
				pXsvfInfo->ucEndDR  = XTAPSTATE_RUNTEST;
			}
			else
			{
				pXsvfInfo->ucEndDR  = XTAPSTATE_PAUSEDR;
			}
			XSVFDBG_PRINTF1( 3, "   ENDDR State = %s\n",
					 xsvf_pzTapState[ pXsvfInfo->ucEndDR ] );
		}
	}

	if ( iErrorCode != XSVF_ERROR_NONE )
	{
		pXsvfInfo->iErrorCode   = iErrorCode;
	}
	return( iErrorCode );
}

int xsvfDoXCOMMENT( SXsvfInfo* pXsvfInfo )
{
	/* Use the comment for debugging */
	/* Otherwise, read through the comment to the end '\0' and ignore */
	unsigned char   ucText;

	if ( xsvf_iDebugLevel > 0 )
	{
		putc( ' ' );
	}

	do
	{
		readByte( &ucText );
		if ( xsvf_iDebugLevel > 0 )
		{
			putc( ucText ? ucText : '\n' );
		}
	} while ( ucText );

	pXsvfInfo->iErrorCode   = XSVF_ERROR_NONE;

	return( pXsvfInfo->iErrorCode );
}

int xsvfDoXWAIT( SXsvfInfo* pXsvfInfo )
{
	unsigned char   ucWaitState;
	unsigned char   ucEndState;
	long            lWaitTime;

	/* Get Parameters */
	/* <wait_state> */
	readVal( &(pXsvfInfo->lvTdi), 1 );
	ucWaitState = pXsvfInfo->lvTdi.val[0];

	/* <end_state> */
	readVal( &(pXsvfInfo->lvTdi), 1 );
	ucEndState = pXsvfInfo->lvTdi.val[0];

	/* <wait_time> */
	readVal( &(pXsvfInfo->lvTdi), 4 );
	lWaitTime = value( &(pXsvfInfo->lvTdi) );
	XSVFDBG_PRINTF2( 3, "   XWAIT:  state = %s; time = %ld\n",
			 xsvf_pzTapState[ ucWaitState ], lWaitTime );

	/* If not already in <wait_state>, go to <wait_state> */
	if ( pXsvfInfo->ucTapState != ucWaitState )
	{
		xsvfGotoTapState( &(pXsvfInfo->ucTapState), ucWaitState );
	}

	/* Wait for <wait_time> microseconds */
	waitTime( lWaitTime );

	/* If not already in <end_state>, go to <end_state> */
	if ( pXsvfInfo->ucTapState != ucEndState )
	{
		xsvfGotoTapState( &(pXsvfInfo->ucTapState), ucEndState );
	}

	return( XSVF_ERROR_NONE );
}



int xsvfInitialize( SXsvfInfo* pXsvfInfo )
{
	/* Initialize values */
	pXsvfInfo->iErrorCode   = xsvfInfoInit( pXsvfInfo );

	if ( !pXsvfInfo->iErrorCode )
	{
		/* Initialize the TAPs */
		pXsvfInfo->iErrorCode   = xsvfGotoTapState( &(pXsvfInfo->ucTapState),
							    XTAPSTATE_RESET );
	}

	return( pXsvfInfo->iErrorCode );
}

int xsvfRun( SXsvfInfo* pXsvfInfo )
{
	/* Process the XSVF commands */
	if ( (!pXsvfInfo->iErrorCode) && (!pXsvfInfo->ucComplete) )
	{
		/* read 1 byte for the instruction */
		readByte( &(pXsvfInfo->ucCommand) );
		++(pXsvfInfo->lCommandCount);

		if ( pXsvfInfo->ucCommand < XLASTCMD )
		{
			/* Execute the command.  Func sets error code. */
			XSVFDBG_PRINTF1( 2, "  %s\n",
					 xsvf_pzCommandName[pXsvfInfo->ucCommand] );
			/* If your compiler cannot take this form,
			   then convert to a switch statement */
#if 0 /* test-only */
			xsvf_pfDoCmd[ pXsvfInfo->ucCommand ]( pXsvfInfo );
#else
			switch (pXsvfInfo->ucCommand) {
			case 0:
				xsvfDoXCOMPLETE(pXsvfInfo);        /*  0 */
				break;
			case 1:
				xsvfDoXTDOMASK(pXsvfInfo);         /*  1 */
				break;
			case 2:
				xsvfDoXSIR(pXsvfInfo);             /*  2 */
				break;
			case 3:
				xsvfDoXSDR(pXsvfInfo);             /*  3 */
				break;
			case 4:
				xsvfDoXRUNTEST(pXsvfInfo);         /*  4 */
				break;
			case 5:
				xsvfDoIllegalCmd(pXsvfInfo);       /*  5 */
				break;
			case 6:
				xsvfDoIllegalCmd(pXsvfInfo);       /*  6 */
				break;
			case 7:
				xsvfDoXREPEAT(pXsvfInfo);          /*  7 */
				break;
			case 8:
				xsvfDoXSDRSIZE(pXsvfInfo);         /*  8 */
				break;
			case 9:
				xsvfDoXSDRTDO(pXsvfInfo);          /*  9 */
				break;
#ifdef  XSVF_SUPPORT_COMPRESSION
			case 10:
				xsvfDoXSETSDRMASKS(pXsvfInfo);     /* 10 */
				break;
			case 11:
				xsvfDoXSDRINC(pXsvfInfo);          /* 11 */
				break;
#else
			case 10:
				xsvfDoIllegalCmd(pXsvfInfo);       /* 10 */
				break;
			case 11:
				xsvfDoIllegalCmd(pXsvfInfo);       /* 11 */
				break;
#endif  /* XSVF_SUPPORT_COMPRESSION */
			case 12:
				xsvfDoXSDRBCE(pXsvfInfo);          /* 12 */
				break;
			case 13:
				xsvfDoXSDRBCE(pXsvfInfo);          /* 13 */
				break;
			case 14:
				xsvfDoXSDRBCE(pXsvfInfo);          /* 14 */
				break;
			case 15:
				xsvfDoXSDRTDOBCE(pXsvfInfo);       /* 15 */
				break;
			case 16:
				xsvfDoXSDRTDOBCE(pXsvfInfo);       /* 16 */
				break;
			case 17:
				xsvfDoXSDRTDOBCE(pXsvfInfo);       /* 17 */
				break;
			case 18:
				xsvfDoXSTATE(pXsvfInfo);           /* 18 */
				break;
			case 19:
				xsvfDoXENDXR(pXsvfInfo);           /* 19 */
				break;
			case 20:
				xsvfDoXENDXR(pXsvfInfo);           /* 20 */
				break;
			case 21:
				xsvfDoXSIR2(pXsvfInfo);            /* 21 */
				break;
			case 22:
				xsvfDoXCOMMENT(pXsvfInfo);         /* 22 */
				break;
			case 23:
				xsvfDoXWAIT(pXsvfInfo);             /* 23 */
				break;
			}
#endif
		}
		else
		{
			/* Illegal command value.  Func sets error code. */
			xsvfDoIllegalCmd( pXsvfInfo );
		}
	}

	return( pXsvfInfo->iErrorCode );
}

void xsvfCleanup( SXsvfInfo* pXsvfInfo )
{
	xsvfInfoCleanup( pXsvfInfo );
}



int xsvfExecute(void)
{
	SXsvfInfo   xsvfInfo;

	xsvfInitialize( &xsvfInfo );

	while ( !xsvfInfo.iErrorCode && (!xsvfInfo.ucComplete) )
	{
		xsvfRun( &xsvfInfo );
	}

	if ( xsvfInfo.iErrorCode )
	{
		XSVFDBG_PRINTF1( 0, "%s\n", xsvf_pzErrorName[
					 ( xsvfInfo.iErrorCode < XSVF_ERROR_LAST )
					 ? xsvfInfo.iErrorCode : XSVF_ERROR_UNKNOWN ] );
		XSVFDBG_PRINTF2( 0, "ERROR at or near XSVF command #%ld.  See line #%ld in the XSVF ASCII file.\n",
				 xsvfInfo.lCommandCount, xsvfInfo.lCommandCount );
	}
	else
	{
		XSVFDBG_PRINTF( 0, "SUCCESS - Completed XSVF execution.\n" );
	}

	xsvfCleanup( &xsvfInfo );

	return( XSVF_ERRORCODE(xsvfInfo.iErrorCode) );
}


int do_cpld(cmd_tbl_t *cmdtp, int flag, int argc, char *argv[])
{
	int     iErrorCode;
	char*   pzXsvfFileName;
	unsigned long duration;
	unsigned long long startClock, endClock;

	if (argc == 2)
		xsvfdata = (unsigned char *)simple_strtoul(argv[1], NULL, 16);
	else {
#ifdef CONFIG_SYS_XSVF_DEFAULT_ADDR
		xsvfdata = (unsigned char *)CONFIG_SYS_XSVF_DEFAULT_ADDR;
#else
		printf("Usage:\ncpld %s\n", cmdtp->help);
		return -1;
#endif
	}

	iErrorCode          = XSVF_ERRORCODE( XSVF_ERROR_NONE );
	pzXsvfFileName      = 0;
	xsvf_iDebugLevel    = 0;

	printf("XSVF Player v%s, Xilinx, Inc.\n", XSVF_VERSION);
	printf("Reading XSVF data @ %p\n", xsvfdata);

	/* Initialize the I/O.  SetPort initializes I/O on first call */
	setPort( TMS, 1 );

	/* Execute the XSVF in the file */
	startClock  = get_ticks();
	iErrorCode  = xsvfExecute();
	endClock    = get_ticks();
	duration    = (unsigned long)(endClock - startClock);
	printf("\nExecution Time = %d seconds\n", (int)(duration/get_tbclk()));

	return( iErrorCode );
}
U_BOOT_CMD(
	cpld,	2,	1,	do_cpld,
	"program onboard CPLD",
	"<xsvf-addr>"
);
