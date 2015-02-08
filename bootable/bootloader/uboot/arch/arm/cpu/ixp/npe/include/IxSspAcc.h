

#ifndef IXSSPACC_H
#define IXSSPACC_H

#ifdef __ixp46X

#include "IxOsal.h"

typedef enum
{
	DATA_SIZE_TOO_SMALL = 0x2,
	DATA_SIZE_4 = 0x3,
	DATA_SIZE_5,
	DATA_SIZE_6,
	DATA_SIZE_7,
	DATA_SIZE_8,
	DATA_SIZE_9,
	DATA_SIZE_10,
	DATA_SIZE_11,
	DATA_SIZE_12,
	DATA_SIZE_13,
	DATA_SIZE_14,
	DATA_SIZE_15,
	DATA_SIZE_16,
	DATA_SIZE_TOO_BIG
} IxSspAccDataSize;

typedef enum
{
	SSP_PORT_DISABLE = 0x0,
	SSP_PORT_ENABLE,
	INVALID_SSP_PORT_STATUS
} IxSspAccPortStatus;

typedef enum
{
	SPI_FORMAT = 0x0,
	SSP_FORMAT,
	MICROWIRE_FORMAT,
	INVALID_FORMAT
} IxSspAccFrameFormat;

typedef enum
{
	ON_CHIP_CLK = 0x0,
	EXTERNAL_CLK,
	INVALID_CLK_SOURCE
} IxSspAccClkSource;

typedef enum
{
	START_ONE_END_HALF = 0x0,
	START_HALF_END_ONE,
	INVALID_SPI_PHASE
} IxSspAccSpiSclkPhase;

typedef enum
{
	SPI_POLARITY_LOW = 0x0,
	SPI_POLARITY_HIGH,
	INVALID_SPI_POLARITY
} IxSspAccSpiSclkPolarity;

typedef enum
{
	MICROWIRE_8_BIT = 0x0,
	MICROWIRE_16_BIT,
	INVALID_MICROWIRE_CTL_WORD
} IxSspAccMicrowireCtlWord;

typedef enum
{
	FIFO_TSHLD_1 =	0x0,
	FIFO_TSHLD_2,
	FIFO_TSHLD_3,
	FIFO_TSHLD_4,
	FIFO_TSHLD_5,
	FIFO_TSHLD_6,
	FIFO_TSHLD_7,
	FIFO_TSHLD_8,
	FIFO_TSHLD_9,
	FIFO_TSHLD_10,
	FIFO_TSHLD_11,
	FIFO_TSHLD_12,
	FIFO_TSHLD_13,
	FIFO_TSHLD_14,
	FIFO_TSHLD_15,
	FIFO_TSHLD_16,
	INVALID_FIFO_TSHLD
} IxSspAccFifoThreshold;

typedef enum
{
	IX_SSP_SUCCESS = IX_SUCCESS, /**< Success status */
	IX_SSP_FAIL, /**< Fail status */
	IX_SSP_RX_FIFO_OVERRUN_HANDLER_MISSING, /**<
						Rx FIFO Overrun handler is NULL. */
	IX_SSP_RX_FIFO_HANDLER_MISSING, /**<
					Rx FIFO threshold hit or above handler is NULL
					*/
	IX_SSP_TX_FIFO_HANDLER_MISSING, /**<
					Tx FIFO threshold hit or below handler is NULL
					*/
	IX_SSP_FIFO_NOT_EMPTY_FOR_SETTING_CTL_CMD, /**<
					Tx FIFO not empty and therefore microwire
					control command size setting is not allowed.	*/
	IX_SSP_INVALID_FRAME_FORMAT_ENUM_VALUE, /**<
					frame format selected is invalid. */
	IX_SSP_INVALID_DATA_SIZE_ENUM_VALUE, /**<
					data size selected is invalid. */
	IX_SSP_INVALID_CLOCK_SOURCE_ENUM_VALUE, /**<
					source clock selected is invalid. */
	IX_SSP_INVALID_TX_FIFO_THRESHOLD_ENUM_VALUE, /**<
					Tx FIFO threshold selected is invalid. */
	IX_SSP_INVALID_RX_FIFO_THRESHOLD_ENUM_VALUE, /**<
					Rx FIFO threshold selected is invalid. */
	IX_SSP_INVALID_SPI_PHASE_ENUM_VALUE, /**<
					SPI phase selected is invalid. */
	IX_SSP_INVALID_SPI_POLARITY_ENUM_VALUE, /**<
					SPI polarity selected is invalid. */
	IX_SSP_INVALID_MICROWIRE_CTL_CMD_ENUM_VALUE, /**<
					Microwire control command selected is invalid
					*/
	IX_SSP_INT_UNBIND_FAIL, /**< Interrupt unbind fail to unbind SSP
	                interrupt */
	IX_SSP_INT_BIND_FAIL, /**< Interrupt bind fail during init */
	IX_SSP_RX_FIFO_NOT_EMPTY, /**<
					Rx FIFO not empty while trying to change data
					size. */
	IX_SSP_TX_FIFO_NOT_EMPTY, /**<
					Rx FIFO not empty while trying to change data
					size or microwire control command size.	*/
	IX_SSP_POLL_MODE_BLOCKING, /**<
					poll mode selected blocks interrupt mode from
					being selected.	*/
	IX_SSP_TX_FIFO_HIT_BELOW_THRESHOLD, /**<
					Tx FIFO level hit or below threshold. */
	IX_SSP_TX_FIFO_EXCEED_THRESHOLD, /**<
					Tx FIFO level exceeded threshold. */
	IX_SSP_RX_FIFO_HIT_ABOVE_THRESHOLD, /**<
					Rx FIFO level hit or exceeded threshold. */
	IX_SSP_RX_FIFO_BELOW_THRESHOLD, /**<
					Rx FIFO level below threshold. */
	IX_SSP_BUSY, /**< SSP is busy. */
	IX_SSP_IDLE, /**< SSP is idle. */
	IX_SSP_OVERRUN_OCCURRED, /**<
					SSP has experienced an overrun. */
	IX_SSP_NO_OVERRUN, /**<
					SSP did not experience an overrun. */
	IX_SSP_NOT_SUPORTED, /**< hardware does not support SSP */
	IX_SSP_NOT_INIT, /**< SSP Access not intialized */
	IX_SSP_NULL_POINTER /**< parameter passed in is NULL */
} IX_SSP_STATUS;

typedef void (*RxFIFOOverrunHandler)(void);

typedef void (*RxFIFOThresholdHandler)(void);

typedef void (*TxFIFOThresholdHandler)(void);


typedef struct
{
	IxSspAccFrameFormat FrameFormatSelected;/**<Select between SPI, SSP and
												Microwire. */
	IxSspAccDataSize DataSizeSelected;		/**<Select between 4 and 16. */
	IxSspAccClkSource ClkSourceSelected;	/**<Select clock source to be
												on-chip or external. */
	IxSspAccFifoThreshold TxFIFOThresholdSelected;
											/**<Select Tx FIFO threshold
												between 1 to 16. */
	IxSspAccFifoThreshold RxFIFOThresholdSelected;
											/**<Select Rx FIFO threshold
												between 1 to 16. */
	BOOL RxFIFOIntrEnable;					/**<Enable/disable Rx FIFO
												threshold interrupt. Disabling
												this interrupt will require
												the use of the polling function
												RxFIFOExceedThresholdCheck. */
	BOOL TxFIFOIntrEnable;					/**<Enable/disable Tx FIFO
												threshold interrupt. Disabling
												this interrupt will require
												the use of the polling function
												TxFIFOExceedThresholdCheck. */
	RxFIFOThresholdHandler RxFIFOThsldHdlr;	/**<Pointer to function to handle
												a Rx FIFO interrupt. */
	TxFIFOThresholdHandler TxFIFOThsldHdlr;	/**<Pointer to function to handle
												a Tx FIFO interrupt. */
	RxFIFOOverrunHandler RxFIFOOverrunHdlr;	/**<Pointer to function to handle
												a Rx FIFO overrun interrupt. */
	BOOL LoopbackEnable;					/**<Select operation mode to be
												normal or loopback mode. */
	IxSspAccSpiSclkPhase SpiSclkPhaseSelected;
											/**<Select SPI SCLK phase to start
												with one inactive cycle and end
												with 1/2 inactive cycle or
												start with 1/2 inactive cycle
												and end with one inactive
												cycle. (Only used in
												SPI format). */
	IxSspAccSpiSclkPolarity SpiSclkPolaritySelected;
											/**<Select SPI SCLK idle state
												to be low or high. (Only used in
												SPI format). */
	IxSspAccMicrowireCtlWord MicrowireCtlWordSelected;
											/**<Select Microwire control
												format to be 8 or 16-bit. (Only
												used in Microwire format). */
	UINT8 SerialClkRateSelected;			/**<Select between 0 (1.8432Mbps)
												and 255 (7.2Kbps). The
												formula used is	Bit rate = 
												3.6864x10^6 / 
												(2 x (SerialClkRateSelect + 1))
												*/
} IxSspInitVars;

typedef struct
{
	UINT32 ixSspRcvCounter;		/**<Total frames received. */
	UINT32 ixSspXmitCounter;	/**<Total frames transmitted. */
	UINT32 ixSspOverflowCounter;/**<Total occurrences of overflow. */
} IxSspAccStatsCounters;



PUBLIC IX_SSP_STATUS
ixSspAccInit (IxSspInitVars *initVarsSelected);

PUBLIC IX_SSP_STATUS
ixSspAccUninit (void);

PUBLIC IX_SSP_STATUS
ixSspAccFIFODataSubmit (
	UINT16* data,
	UINT32 amtOfData);

PUBLIC IX_SSP_STATUS
ixSspAccFIFODataReceive (
	UINT16* data,
	UINT32 amtOfData);



PUBLIC IX_SSP_STATUS
ixSspAccTxFIFOHitOrBelowThresholdCheck (
	void);

PUBLIC IX_SSP_STATUS
ixSspAccRxFIFOHitOrAboveThresholdCheck (
	void);



PUBLIC IX_SSP_STATUS
ixSspAccSSPPortStatusSet (
	IxSspAccPortStatus portStatusSelected);

PUBLIC IX_SSP_STATUS
ixSspAccFrameFormatSelect (
	IxSspAccFrameFormat frameFormatSelected);

PUBLIC IX_SSP_STATUS
ixSspAccDataSizeSelect (
	IxSspAccDataSize dataSizeSelected);

PUBLIC IX_SSP_STATUS
ixSspAccClockSourceSelect (
	IxSspAccClkSource clkSourceSelected);

PUBLIC IX_SSP_STATUS
ixSspAccSerialClockRateConfigure (
	UINT8 serialClockRateSelected);

PUBLIC IX_SSP_STATUS
ixSspAccRxFIFOIntEnable (
	RxFIFOThresholdHandler rxFIFOIntrHandler);

PUBLIC IX_SSP_STATUS
ixSspAccRxFIFOIntDisable (
	void);

PUBLIC IX_SSP_STATUS
ixSspAccTxFIFOIntEnable (
	TxFIFOThresholdHandler txFIFOIntrHandler);

PUBLIC IX_SSP_STATUS
ixSspAccTxFIFOIntDisable (
	void);

PUBLIC IX_SSP_STATUS
ixSspAccLoopbackEnable (
	BOOL loopbackEnable);

PUBLIC IX_SSP_STATUS
ixSspAccSpiSclkPolaritySet (
	IxSspAccSpiSclkPolarity spiSclkPolaritySelected);

PUBLIC IX_SSP_STATUS
ixSspAccSpiSclkPhaseSet (
	IxSspAccSpiSclkPhase spiSclkPhaseSelected);

PUBLIC IX_SSP_STATUS
ixSspAccMicrowireControlWordSet (
	IxSspAccMicrowireCtlWord microwireCtlWordSelected);

PUBLIC IX_SSP_STATUS
ixSspAccTxFIFOThresholdSet (
	IxSspAccFifoThreshold txFIFOThresholdSelected);

PUBLIC IX_SSP_STATUS
ixSspAccRxFIFOThresholdSet (
	IxSspAccFifoThreshold rxFIFOThresholdSelected);



PUBLIC IX_SSP_STATUS
ixSspAccStatsGet (
	IxSspAccStatsCounters *sspStats);

PUBLIC void
ixSspAccStatsReset (
	void);

PUBLIC IX_SSP_STATUS
ixSspAccShow (
	void);

PUBLIC IX_SSP_STATUS
ixSspAccSSPBusyCheck (
	void);

PUBLIC UINT8
ixSspAccTxFIFOLevelGet (
	void);

PUBLIC UINT8
ixSspAccRxFIFOLevelGet (
	void);

PUBLIC IX_SSP_STATUS
ixSspAccRxFIFOOverrunCheck (
	void);

#endif /* __ixp46X */
#endif /* IXSSPACC_H */
