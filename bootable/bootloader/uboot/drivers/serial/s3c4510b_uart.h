
#ifndef __UART_H
#define __UART_H


/* UART LINE CONTROL register */
typedef struct __BF_UART_LINE_CTRL {
	u32    wordLen: 2;
	u32      nStop: 1;
	u32     parity: 3;
	u32        clk: 1;
	u32  infra_red: 1;
	u32     unused:24;
} BF_UART_LINE_CTRL;

typedef union _UART_LINE_CTRL {
	u32               ui;
	BF_UART_LINE_CTRL bf;
} UART_LINE_CTRL;

/* UART CONTROL register */
typedef struct __BF_UART_CTRL {
	u32     rxMode: 2;
	u32      rxIrq: 1;
	u32     txMode: 2;
	u32        DSR: 1;
	u32  sendBreak: 1;
	u32   loopBack: 1;
	u32     unused:24;
} BF_UART_CTRL;

typedef union _UART_CTRL {
	u32            ui;
	BF_UART_CTRL   bf;
} UART_CTRL;

/* UART STATUS register */
typedef struct __BF_UART_STAT {
	u32      overrun: 1;
	u32       parity: 1;
	u32        frame: 1;
	u32     breakIrq: 1;
	u32          DTR: 1;
	u32      rxReady: 1;
	u32   txBufEmpty: 1;
	u32   txComplete: 1;
	u32       unused:24;
} BF_UART_STAT;

typedef union _UART_STAT {
	u32            ui;
	BF_UART_STAT   bf;
} UART_STAT;

/* UART BAUD_DIV register */
typedef struct __BF_UART_BAUD_DIV {
	u32      cnt1: 4;
	u32      cnt0:12;
	u32    unused:16;
} BF_UART_BAUD_DIV;

typedef union _UART_BAUD_DIV {
	u32                ui;
	BF_UART_BAUD_DIV   bf;
} UART_BAUD_DIV;

/* UART register block */
typedef struct __UART {
	volatile UART_LINE_CTRL  m_lineCtrl;
	volatile UART_CTRL           m_ctrl;
	volatile UART_STAT           m_stat;
	volatile u32                   m_tx;
	volatile u32                   m_rx;
	volatile UART_BAUD_DIV    m_baudDiv;
	volatile u32              m_baudCnt;
	volatile u32              m_baudClk;
} UART;

#define NL          0x0A
#define CR          0x0D
#define BSP         0x08
#define ESC         0x1B
#define CTRLZ       0x1A
#define RUBOUT      0x7F

#endif
