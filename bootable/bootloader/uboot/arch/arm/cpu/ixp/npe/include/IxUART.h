



/* Defaults */


#define IX_UART_DEF_OPTS (CLOCAL | CS8)

#define IX_UART_DEF_XMIT 64

#define IX_UART_DEF_BAUD 9600

#define IX_UART_MIN_BAUD 9600

#define IX_UART_MAX_BAUD 926100

#define IX_UART_XTAL 14745600



/* IOCTL commands (Request codes) */



#define IX_BAUD_SET	0

#define IX_BAUD_GET	1

#define IX_MODE_SET	2

#define IX_MODE_GET	3

#define IX_OPTS_SET	4

#define IX_OPTS_GET	5

#define IX_STATS_GET	6


/* POSIX style ioctl arguments */



#ifdef CLOCAL
#undef CLOCAL
#endif
#define CLOCAL		0x1

#ifdef CREAD
#undef CREAD
#endif
#define CREAD		0x2

#ifdef CSIZE
#undef CSIZE
#endif
#define CSIZE		0xc

#ifdef CS5
#undef CS5
#endif
#define CS5		0x0

#ifdef CS6
#undef CS6
#endif
#define CS6		0x4

#ifdef CS7
#undef CS7
#endif
#define CS7		0x8

#ifdef CS8
#undef CS8
#endif
#define CS8		0xc

#define STOPB		0x20

#ifdef PARENB
#undef PARENB
#endif
#define PARENB		0x40

#ifdef PARODD
#undef PARODD
#endif
#define PARODD		0x80

typedef enum
{
    INTERRUPT=0,	/**< Interrupt mode */
    POLLED,		/**< Polled mode */
    LOOPBACK		/**< Loopback mode */
} ixUARTMode;

typedef struct
{
    UINT32  rxCount;
    UINT32  txCount;	
    UINT32  overrunErr;
    UINT32  parityErr;
    UINT32  framingErr;
    UINT32  breakErr;
} ixUARTStats;

typedef struct
{
    UINT8 *addr;	/**< device base address */
    ixUARTMode mode;	/**< interrupt, polled or loopback */
    int baudRate;	/**< baud rate */
    int freq;		/**< UART clock frequency */     
    int options;	/**< hardware options */
    int fifoSize;	/**< FIFO xmit size */

    ixUARTStats   stats;	/**< device statistics */
} ixUARTDev;

PUBLIC IX_STATUS ixUARTInit(ixUARTDev* pUART);

PUBLIC IX_STATUS ixUARTPollOutput(ixUARTDev* pUART, int outChar);

PUBLIC IX_STATUS ixUARTPollInput(ixUARTDev* pUART, char *inChar);

PUBLIC IX_STATUS ixUARTIoctl(ixUARTDev* pUART, int cmd, void* arg);

