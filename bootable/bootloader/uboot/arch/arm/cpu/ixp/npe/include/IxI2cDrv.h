

#ifndef IXI2CDRV_H
#define IXI2CDRV_H

#ifdef __ixp46X
#include "IxOsal.h"


#define IX_I2C_US_POLL_FOR_XFER_STATUS	20

#define IX_I2C_NUM_OF_TRIES_TO_CALL_CALLBACK_FUNC	10


#define IX_I2C_NUM_TO_POLL_IDBR_RX_FULL 0x100

#define IX_I2C_NUM_TO_POLL_IDBR_TX_EMPTY 0x100


typedef enum
{
    IX_I2C_MASTER_XFER_COMPLETE = IX_SUCCESS,
	IX_I2C_MASTER_XFER_BUS_ERROR,
	IX_I2C_MASTER_XFER_ARB_LOSS
} IxI2cMasterStatus;


typedef enum
{
	IX_I2C_SUCCESS = IX_SUCCESS, /**< Success status */
	IX_I2C_FAIL, /**< Fail status */
	IX_I2C_NOT_SUPPORTED, /**< hardware does not have dedicated I2C hardware */
	IX_I2C_NULL_POINTER, /**< parameter passed in is NULL */
	IX_I2C_INVALID_SPEED_MODE_ENUM_VALUE, /**< speed mode selected is invalid */
	IX_I2C_INVALID_FLOW_MODE_ENUM_VALUE, /**< flow mode selected is invalid */
	IX_I2C_SLAVE_ADDR_CB_MISSING, /**< slave callback is NULL */
	IX_I2C_GEN_CALL_CB_MISSING, /**< general callback is NULL */
	IX_I2C_INVALID_SLAVE_ADDR, /**< invalid slave address specified */
	IX_I2C_INT_BIND_FAIL, /**< interrupt bind fail */
	IX_I2C_INT_UNBIND_FAIL, /**< interrupt unbind fail */
	IX_I2C_NOT_INIT, /**< I2C is not initialized yet */
	IX_I2C_MASTER_BUS_BUSY, /**< master detected a I2C bus busy */
	IX_I2C_MASTER_ARB_LOSS, /**< master experienced arbitration loss */
	IX_I2C_MASTER_XFER_ERROR, /**< master experienced a transfer error */
	IX_I2C_MASTER_BUS_ERROR, /**< master detected a I2C bus error */
	IX_I2C_MASTER_NO_BUFFER, /**< no buffer provided for master transfer */
	IX_I2C_MASTER_INVALID_XFER_MODE, /**< xfer mode selected is invalid */
	IX_I2C_SLAVE_ADDR_NOT_DETECTED, /**< polled slave addr not detected */
	IX_I2C_GEN_CALL_ADDR_DETECTED, /**< polling detected general call */
	IX_I2C_SLAVE_READ_DETECTED, /**< polling detected slave read request */
	IX_I2C_SLAVE_WRITE_DETECTED, /**< polling detected slave write request */
	IX_I2C_SLAVE_NO_BUFFER, /**< no buffer provided for slave transfers */
	IX_I2C_DATA_SIZE_ZERO, /**< data size transfer is zero - invalid */
	IX_I2C_SLAVE_WRITE_BUFFER_EMPTY, /**< slave buffer is used till empty */
	IX_I2C_SLAVE_WRITE_ERROR, /**< slave write experienced an error */
	IX_I2C_SLAVE_OR_GEN_READ_BUFFER_FULL, /**< slave buffer is filled up */
	IX_I2C_SLAVE_OR_GEN_READ_ERROR /**< slave read experienced an error */
} IX_I2C_STATUS;

typedef enum
{
    IX_I2C_NORMAL_MODE = 0x0,
    IX_I2C_FAST_MODE
} IxI2cSpeedMode;

typedef enum
{
    IX_I2C_NORMAL = 0x0,
    IX_I2C_REPEATED_START
} IxI2cXferMode;

typedef enum
{
    IX_I2C_POLL_MODE = 0x0,
    IX_I2C_INTERRUPT_MODE
} IxI2cFlowMode;

typedef enum
{
    IX_I2C_LOOP_DELAY = 1,  /**< delay in microseconds */
    IX_I2C_SCHED_DELAY      /**< delay in miliseconds */
} IxI2cDelayMode;

typedef void (*IxI2cMasterReadCallbackP)(IxI2cMasterStatus, IxI2cXferMode, char*, UINT32);

typedef void (*IxI2cMasterWriteCallbackP)(IxI2cMasterStatus, IxI2cXferMode, char*, UINT32);

typedef void (*IxI2cSlaveReadCallbackP)(IX_I2C_STATUS, char*, UINT32, UINT32);

typedef void (*IxI2cSlaveWriteCallbackP)(IX_I2C_STATUS, char*, UINT32, UINT32);

typedef void (*IxI2cGenCallCallbackP)(IX_I2C_STATUS, char*, UINT32, UINT32);


typedef struct
{
	IxI2cSpeedMode I2cSpeedSelect;	/**<Select either normal (100kbps)
									or fast mode (400kbps)*/
	IxI2cFlowMode I2cFlowSelect;	/**<Select interrupt or poll mode*/	
	IxI2cMasterReadCallbackP MasterReadCBP;
									/**<The master read callback pointer */
	IxI2cMasterWriteCallbackP MasterWriteCBP;
									/**<The master write callback pointer */
	IxI2cSlaveReadCallbackP SlaveReadCBP;
									/**<The slave read callback pointer */
	IxI2cSlaveWriteCallbackP SlaveWriteCBP;
									/**<The slave write callback pointer */
	IxI2cGenCallCallbackP GenCallCBP;
									/**<The general call callback pointer */
	BOOL I2cGenCallResponseEnable;	/**<Enable/disable the unit to
									respond to generall calls.*/
	BOOL I2cSlaveAddrResponseEnable;/**<Enable/disable the unit to
									respond to the slave address set in
									ISAR*/
	BOOL SCLEnable;					/**<Enable/disable the unit from
									driving the SCL line during master
									mode operation*/
	UINT8 I2cHWAddr;				/**<The address the unit will
									response to as a slave device*/
} IxI2cInitVars;

typedef struct
{
	UINT32 ixI2cMasterXmitCounter;			/**<Total bytes transmitted as
											master.*/
	UINT32 ixI2cMasterFailedXmitCounter;	/**<Total bytes failed for
											transmission as master.*/
	UINT32 ixI2cMasterRcvCounter;			/**<Total bytes received as
											master.*/
	UINT32 ixI2cMasterFailedRcvCounter;		/**<Total bytes failed for
											receival as master.*/
	UINT32 ixI2cSlaveXmitCounter;			/**<Total bytes transmitted as
											slave.*/
	UINT32 ixI2cSlaveFailedXmitCounter;		/**<Total bytes failed for
											transmission as slave.*/
	UINT32 ixI2cSlaveRcvCounter;			/**<Total bytes received as
											slave.*/
	UINT32 ixI2cSlaveFailedRcvCounter;		/**<Total bytes failed for
											receival as slave.*/
	UINT32 ixI2cGenAddrCallSucceedCounter;	/**<Total bytes successfully
											transmitted for general address.*/
	UINT32 ixI2cGenAddrCallFailedCounter;	/**<Total bytes failed transmission
											for general address.*/
	UINT32 ixI2cArbLossCounter;				/**<Total instances of arbitration
											loss has occured.*/
} IxI2cStatsCounters;



PUBLIC IX_I2C_STATUS
ixI2cDrvInit(IxI2cInitVars *InitVarsSelected);

PUBLIC IX_I2C_STATUS
ixI2cDrvUninit(void);

PUBLIC IX_I2C_STATUS
ixI2cDrvSlaveAddrSet(UINT8 SlaveAddrSet);

PUBLIC IX_I2C_STATUS
ixI2cDrvBusScan(void);

PUBLIC IX_I2C_STATUS
ixI2cDrvWriteTransfer(
	UINT8 SlaveAddr,
	char *bufP,
	UINT32 dataSize,
	IxI2cXferMode XferModeSelect);

PUBLIC IX_I2C_STATUS
ixI2cDrvReadTransfer(
	UINT8 SlaveAddr,
	char *bufP,
	UINT32 dataSize,
	IxI2cXferMode XferModeSelect);

PUBLIC IX_I2C_STATUS
ixI2cDrvSlaveAddrAndGenCallDetectedCheck(void);

PUBLIC IX_I2C_STATUS
ixI2cDrvSlaveOrGenDataReceive(
	char *bufP,
	UINT32 bufSize,
	UINT32 *dataSizeRcvd);

PUBLIC IX_I2C_STATUS
ixI2cDrvSlaveDataTransmit(
	char *bufP,
	UINT32 dataSize,
	UINT32 *dataSizeXmtd);

PUBLIC void
ixI2cDrvSlaveOrGenCallBufReplenish(
	char *bufP,
	UINT32 bufSize);

PUBLIC IX_I2C_STATUS
ixI2cDrvStatsGet(IxI2cStatsCounters *I2cStats);

PUBLIC void
ixI2cDrvStatsReset(void);

PUBLIC IX_I2C_STATUS
ixI2cDrvShow(void);

PUBLIC void
ixI2cDrvDelayTypeSelect (IxI2cDelayMode delayTypeSelect);

#endif /* __ixp46X */
#endif /* IXI2CDRV_H */
