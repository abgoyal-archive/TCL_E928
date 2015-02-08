




#ifndef IXATMDACCCTRL_H
#define IXATMDACCCTRL_H

#include "IxAtmdAcc.h"


#define IX_ATMDACC_PORT_DISABLE_IN_PROGRESS 5

#define IX_ATMDACC_ALLPDUS 0xffffffff


typedef IX_STATUS (*IxAtmdAccRxDispatcher) (IxAtmRxQueueId rxQueueId,
                         unsigned int numberOfPdusToProcess,
                         unsigned int *reservedPtr);


typedef IX_STATUS (*IxAtmdAccTxDoneDispatcher) (unsigned int numberOfPdusToProcess,
                                                unsigned int *reservedPtr);

typedef void (*IxAtmdAccPortTxLowCallback) (IxAtmLogicalPort port,
                           unsigned int numberOfAvailableCells);

typedef IX_STATUS (*IxAtmdAccTxVcDemandUpdateCallback) (IxAtmLogicalPort port,
                        int vcId,
                        unsigned int numberOfCells);

typedef void (*IxAtmdAccTxVcDemandClearCallback) (IxAtmLogicalPort port,
                             int vcId);

typedef IX_STATUS (*IxAtmdAccTxSchVcIdGetCallback) (IxAtmLogicalPort port,
                               unsigned int vpi,
                               unsigned int vci,
                               IxAtmConnId connId,
                               int *vcId);


PUBLIC IX_STATUS ixAtmdAccRxDispatcherRegister (
                          IxAtmRxQueueId queueId,
                          IxAtmdAccRxDispatcher callback);

PUBLIC IX_STATUS ixAtmdAccRxDispatch (IxAtmRxQueueId rxQueueId,
    unsigned int numberOfPdusToProcess,
    unsigned int *numberOfPdusProcessedPtr);

PUBLIC IX_STATUS ixAtmdAccRxLevelQuery (IxAtmRxQueueId rxQueueId,
                     unsigned int *numberOfPdusPtr);

PUBLIC IX_STATUS ixAtmdAccRxQueueSizeQuery (IxAtmRxQueueId rxQueueId,
                     unsigned int *numberOfPdusPtr);


PUBLIC IX_STATUS ixAtmdAccPortTxFreeEntriesQuery (IxAtmLogicalPort port,
                         unsigned int *numberOfCellsPtr);

PUBLIC IX_STATUS ixAtmdAccPortTxCallbackRegister (IxAtmLogicalPort port,
                       unsigned int numberOfCells,
                       IxAtmdAccPortTxLowCallback callback);

PUBLIC IX_STATUS ixAtmdAccPortTxScheduledModeEnable (IxAtmLogicalPort port,
    IxAtmdAccTxVcDemandUpdateCallback vcDemandUpdateCallback,
    IxAtmdAccTxVcDemandClearCallback vcDemandClearCallback,
    IxAtmdAccTxSchVcIdGetCallback vcIdGetCallback);

PUBLIC IX_STATUS ixAtmdAccPortTxProcess (IxAtmLogicalPort port,
    IxAtmScheduleTable* scheduleTablePtr);

PUBLIC IX_STATUS
ixAtmdAccTxDoneDispatch (unsigned int numberOfPdusToProcess,
                unsigned int *numberOfPdusProcessedPtr);

PUBLIC IX_STATUS
ixAtmdAccTxDoneLevelQuery (unsigned int *numberOfPdusPtr);

PUBLIC IX_STATUS
ixAtmdAccTxDoneQueueSizeQuery (unsigned int *numberOfPdusPtr);

PUBLIC IX_STATUS ixAtmdAccTxDoneDispatcherRegister (unsigned int numberOfPdus,
   IxAtmdAccTxDoneDispatcher notificationCallback);



typedef struct
{
    /**
    * @ingroup IxAtmdAccUtopiaCtrlAPI
    * @struct UtTxConfig_
    * @brief Utopia Tx Config Register
    */
    struct UtTxConfig_
    {

    unsigned int reserved_1:1;  /**< [31] These bits are always 0.*/
    unsigned int txInterface:1;     /**< [30] Utopia Transmit Interface. The following encoding
                                   * is used to set the Utopia Transmit interface as ATM master
                                   * or PHY slave:
                                   * @li 1 - PHY
                                   * @li 0 - ATM
                                   */
    unsigned int txMode:1;      /**< [29] Utopia Transmit Mode. The following encoding is used
    *  to set the Utopia Transmit mode to SPHY or MPHY:
    *  @li 1 - SPHY
    *  @li 0 - MPHY
    */
    unsigned int txOctet:1;  /**< [28] Utopia Transmit cell transfer protocol. Used to set
    * the Utopia cell transfer protocol to Octet-level handshaking.
    * Note this is only applicable in SPHY mode.
    * @li 1 - Octet-handshaking enabled
    * @li 0 - Cell-handshaking enabled
    */
    unsigned int txParity:1;    /**< [27] Utopia Transmit parity enabled when set. TxEvenParity
    * defines the parity format odd/even.
    * @li 1 - Enable Parity generation.
    * @li 0 - ut_op_prty held low.
    */
    unsigned int txEvenParity:1; /**< [26] Utopia Transmit Parity Mode
    * @li 1 - Even Parity Generated.
    * @li 0 - Odd Parity Generated.
    */
    unsigned int txHEC:1; /**< [25] Header Error Check Insertion Mode. Specifies if the transmit
    * cell header check byte is calculated and inserted when set.
    * @li 1 - Generate HEC.
    * @li 0 - Disable HEC generation.
    */
    unsigned int txCOSET:1;    /**< [24] If enabled the HEC is Exclusive-ORÆed with the value 0x55 before
  * being presented on the Utopia bus.
  * @li 1 - Enable HEC ExOR with value 0x55
  * @li 0 - Use generated HEC value.
  */

    unsigned int reserved_2:1;    /**< [23] These bits are always 0
    */
    unsigned int txCellSize:7;    /**< [22:16] Transmit expected cell size. Configures the cell size
    * for the transmit module: Values between 52-64 are valid.
    */
    unsigned int reserved_3:3;  /**< [15:13] These bits are always 0 */
    unsigned int txAddrRange:5;       /**< [12:8] When configured as an ATM master in MPHY mode this
    * register specifies the upper limit of the PHY polling logical
    * range. The number of active PHYs are TxAddrRange + 1.
    */
    unsigned int reserved_4:3;      /**< [7:5] These bits are always 0 */
    unsigned int txPHYAddr:5;     /**< [4:0] When configured as a slave in an MPHY system this register
    * specifies the physical address of the PHY.
    */
    }

    utTxConfig;       /**< Tx config Utopia register */

   /**
    * @ingroup IxAtmdAccUtopiaCtrlAPI
   * @struct UtTxStatsConfig_
   * @brief Utopia Tx stats Register
    */
    struct UtTxStatsConfig_
    {

    unsigned int vpi:12;  /**< [31:20] ATM VPI [11:0] OR GFC [3:0] and VPI [7:0]
    @li Note: if VCStatsTxGFC is set to 0 the GFC field is ignored in test. */

    unsigned int vci:16;  /**< [19:4] ATM VCI [15:0] or PHY Address[4] */

    unsigned int pti:3;  /**< [3:1] ATM PTI [2:0] or PHY Address[3:1]
  @li Note: if VCStatsTxPTI is set to 0 the PTI field is ignored in test.
  @li Note: if VCStatsTxEnb is set to 0 only the transmit PHY port
  address as defined by this register is used for ATM statistics [4:0]. */

    unsigned int clp:1;  /**< [0] ATM CLP or PHY Address [0]
  @li Note: if VCStatsTxCLP is set to 0 the CLP field is ignored in test.
  @li Note: if VCStatsTxEnb is set to 0 only the transmit PHY port
  address as defined by this register is used for ATM statistics [4:0]. */
    }

    utTxStatsConfig;       /**< Tx stats config Utopia register */

       /**
    * @ingroup IxAtmdAccUtopiaCtrlAPI
       * @struct UtTxDefineIdle_
       * @brief Utopia Tx idle cells Register
    */
    struct UtTxDefineIdle_
    {

    unsigned int vpi:12;  /**< [31:20] ATM VPI [11:0] OR GFC [3:0] and VPI [7:0]
    @li Note: if VCIdleTxGFC is set to 0 the GFC field is ignored in test. */

    unsigned int vci:16;  /**< [19:4] ATM VCI [15:0] */

    unsigned int pti:3;  /**< [3:1] ATM PTI PTI [2:0]
  @li Note: if VCIdleTxPTI is set to 0 the PTI field is ignored in test.*/

    unsigned int clp:1;  /**< [0] ATM CLP [0]
  @li Note: if VCIdleTxCLP is set to 0 the CLP field is ignored in test.*/
    }

    utTxDefineIdle;      /**< Tx idle cell config Utopia register */

      /**
    * @ingroup IxAtmdAccUtopiaCtrlAPI
      * @struct UtTxEnableFields_
      * @brief Utopia Tx ienable fields Register
    */
    struct UtTxEnableFields_
    {

    unsigned int defineTxIdleGFC:1;    /**< [31] This register is used to include or exclude the GFC
    field of the ATM header when testing for Idle cells.
    @li 1 - GFC field is valid.
    @li 0 - GFC field ignored.*/

    unsigned int defineTxIdlePTI:1;    /**< [30] This register is used to include or exclude the PTI
    field of the ATM header when testing for Idle cells.
    @li 1 - PTI field is valid
    @li    0 - PTI field ignored.*/

    unsigned int defineTxIdleCLP:1;    /**< [29] This register is used to include or
    exclude the CLP field of the ATM header when testing for Idle cells.
    @li 1 - CLP field is valid.
    @li 0 - CLP field ignored. */

    unsigned int phyStatsTxEnb:1;    /**< [28] This register is used to enable or disable ATM
  statistics gathering based on the specified PHY address as defined
  in TxStatsConfig register.
  @li 1 - Enable statistics for specified transmit PHY address.
    @li 0 - Disable statistics for specified transmit PHY address. */

    unsigned int vcStatsTxEnb:1;  /**< [27] This register is used to change the ATM
      statistics-gathering mode from the specified logical PHY address
      to a specific VPI/VCI address.
      @li 1 - Enable statistics for specified VPI/VCI address.
      @li 0 - Disable statistics for specified VPI/VCI address */

    unsigned int vcStatsTxGFC:1;  /**< [26] This register is used to include or exclude the GFC
      field of the ATM header when ATM VPI/VCI statistics are enabled.
      GFC is only available at the UNI and uses the first 4-bits of
      the VPI field.
      @li 1 - GFC field is valid
      @li 0 - GFC field ignored.*/

    unsigned int vcStatsTxPTI:1;  /**< [25] This register is used to include or exclude the PTI
      field of the ATM header when ATM VPI/VCI statistics are enabled.
      @li 1 - PTI field is valid
      @li 0 - PTI field ignored.*/

    unsigned int vcStatsTxCLP:1;  /**< [24] This register is used to include or exclude the CLP
      field of the ATM header when ATM VPI/VCI statistics are enabled.
      @li 1 - CLP field is valid
      @li 0 - CLP field ignored. */

    unsigned int reserved_1:3;  /**< [23-21] These bits are always 0 */

    unsigned int txPollStsInt:1;    /**< [20] Enable the assertion of the ucp_tx_poll_sts condition
  where there is a change in polling status.
  @li 1 - ucp_tx_poll_sts asserted whenever there is a change in status
  @li    0 - ucp_tx_poll_sts asserted if ANY transmit PHY is available
  */
    unsigned int txCellOvrInt:1;    /**< [19] Enable TxCellCount overflow CBI Transmit Status condition
      assertion.
      @li 1 - If TxCellCountOvr is set assert the Transmit Status Condition.
      @li 0 - No CBI Transmit Status condition assertion */

    unsigned int txIdleCellOvrInt:1;  /**< [18] Enable TxIdleCellCount overflow Transmit Status Condition
    @li 1 - If TxIdleCellCountOvr is set assert the Transmit Status Condition
      @li 0 - No CBI Transmit Status condition assertion..*/

    unsigned int enbIdleCellCnt:1;    /**< [17] Enable Transmit Idle Cell Count.
    @li 1 - Enable count of Idle cells transmitted.
      @li 0 - No count is maintained. */

    unsigned int enbTxCellCnt:1;    /**< [16] Enable Transmit Valid Cell Count of non-idle/non-error cells
      @li 1 - Enable count of valid cells transmitted- non-idle/non-error
      @li 0 - No count is maintained.*/

    unsigned int reserved_2:16;   /**< [15:0] These bits are always 0 */
    } utTxEnableFields;  /**< Tx enable Utopia register */

    /**
    * @ingroup IxAtmdAccUtopiaCtrlAPI
    * @struct UtTxTransTable0_
    * @brief Utopia Tx translation table Register
    */
    struct UtTxTransTable0_
    {

    unsigned int phy0:5;  /**< [31-27] Tx Mapping value of logical phy 0 */

    unsigned int phy1:5;  /**< [26-22] Tx Mapping value of logical phy 1 */

    unsigned int phy2:5;  /**< [21-17] Tx Mapping value of logical phy 2 */

    unsigned int reserved_1:1;  /**< [16] These bits are always 0.*/

    unsigned int phy3:5;  /**< [15-11] Tx Mapping value of logical phy 3 */

    unsigned int phy4:5;  /**< [10-6] Tx Mapping value of logical phy 4 */

    unsigned int phy5:5;  /**< [5-1] Tx Mapping value of logical phy 5 */

    unsigned int reserved_2:1;  /**< [0] These bits are always 0 */
    } utTxTransTable0;  /**< Tx translation table */

  /**
    * @ingroup IxAtmdAccUtopiaCtrlAPI
  * @struct UtTxTransTable1_
  * @brief Utopia Tx translation table Register
    */
    struct UtTxTransTable1_
    {

    unsigned int phy6:5;  /**< [31-27] Tx Mapping value of logical phy 6 */

    unsigned int phy7:5;  /**< [26-22] Tx Mapping value of logical phy 7 */

    unsigned int phy8:5;  /**< [21-17] Tx Mapping value of logical phy 8 */

    unsigned int reserved_1:1; /**< [16-0] These bits are always 0 */

    unsigned int phy9:5;  /**< [15-11] Tx Mapping value of logical phy 3 */

    unsigned int phy10:5;   /**< [10-6] Tx Mapping value of logical phy 4 */

    unsigned int phy11:5;   /**< [5-1] Tx Mapping value of logical phy 5 */

    unsigned int reserved_2:1;  /**< [0] These bits are always 0 */
    } utTxTransTable1;  /**< Tx translation table */

    /**
    * @ingroup IxAtmdAccUtopiaCtrlAPI
    * @struct UtTxTransTable2_
    * @brief Utopia Tx translation table Register
    */
    struct UtTxTransTable2_
    {

    unsigned int phy12:5;   /**< [31-27] Tx Mapping value of logical phy 6 */

    unsigned int phy13:5;   /**< [26-22] Tx Mapping value of logical phy 7 */

    unsigned int phy14:5;   /**< [21-17] Tx Mapping value of logical phy 8 */

    unsigned int reserved_1:1; /**< [16-0] These bits are always 0 */

    unsigned int phy15:5;   /**< [15-11] Tx Mapping value of logical phy 3 */

    unsigned int phy16:5;   /**< [10-6] Tx Mapping value of logical phy 4 */

    unsigned int phy17:5;   /**< [5-1] Tx Mapping value of logical phy 5 */

    unsigned int reserved_2:1;  /**< [0] These bits are always 0 */
    } utTxTransTable2;    /**< Tx translation table */

    /**
    * @ingroup IxAtmdAccUtopiaCtrlAPI
    * @struct UtTxTransTable3_
    * @brief Utopia Tx translation table Register
    */
    struct UtTxTransTable3_
    {

    unsigned int phy18:5;   /**< [31-27] Tx Mapping value of logical phy 6 */

    unsigned int phy19:5;   /**< [26-22] Tx Mapping value of logical phy 7 */

    unsigned int phy20:5;   /**< [21-17] Tx Mapping value of logical phy 8 */

    unsigned int reserved_1:1; /**< [16-0] These bits are always 0 */

    unsigned int phy21:5;   /**< [15-11] Tx Mapping value of logical phy 3 */

    unsigned int phy22:5;   /**< [10-6] Tx Mapping value of logical phy 4 */

    unsigned int phy23:5;   /**< [5-1] Tx Mapping value of logical phy 5 */

    unsigned int reserved_2:1;  /**< [0] These bits are always 0 */
    } utTxTransTable3;  /**< Tx translation table */

    /**
    * @ingroup IxAtmdAccUtopiaCtrlAPI
    * @struct UtTxTransTable4_
    * @brief Utopia Tx translation table Register
    */
    struct UtTxTransTable4_
    {

    unsigned int phy24:5;   /**< [31-27] Tx Mapping value of logical phy 6 */

    unsigned int phy25:5;   /**< [26-22] Tx Mapping value of logical phy 7 */

    unsigned int phy26:5;   /**< [21-17] Tx Mapping value of logical phy 8 */

    unsigned int reserved_1:1; /**< [16-0] These bits are always 0 */

    unsigned int phy27:5;   /**< [15-11] Tx Mapping value of logical phy 3 */

    unsigned int phy28:5;   /**< [10-6] Tx Mapping value of logical phy 4 */

    unsigned int phy29:5;   /**< [5-1] Tx Mapping value of logical phy 5 */

    unsigned int reserved_2:1;  /**< [0] These bits are always 0 */
    } utTxTransTable4;  /**< Tx translation table */

    /**
    * @ingroup IxAtmdAccUtopiaCtrlAPI
    * @struct UtTxTransTable5_
    * @brief Utopia Tx translation table Register
    */
    struct UtTxTransTable5_
    {

    unsigned int phy30:5;   /**< [31-27] Tx Mapping value of logical phy 6 */

    unsigned int reserved_1:27;     /**< [26-0] These bits are always 0 */

    } utTxTransTable5;  /**< Tx translation table */

    /**
    * @ingroup IxAtmdAccUtopiaCtrlAPI
    * @struct UtRxConfig_
    * @brief Utopia Rx config Register
    */
    struct UtRxConfig_
    {

    unsigned int rxInterface:1;    /**< [31] Utopia Receive Interface. The following encoding is used
 to set the Utopia Receive interface as ATM master or PHY slave:
 @li 1 - PHY
    @li 0 - ATM */

    unsigned int rxMode:1;      /**< [30] Utopia Receive Mode. The following encoding is used to set
      the Utopia Receive mode to SPHY or MPHY:
      @li 1 - SPHY
    @li 0 - MPHY */

    unsigned int rxOctet:1;  /**< [29] Utopia Receive cell transfer protocol. Used to set the Utopia
  cell transfer protocol to Octet-level handshaking. Note this is only
  applicable in SPHY mode.
  @li 1 - Octet-handshaking enabled
    @li 0 - Cell-handshaking enabled */

    unsigned int rxParity:1;    /**< [28] Utopia Receive Parity Checking enable.
    @li 1 - Parity checking enabled
    @li 0 - Parity checking disabled */

    unsigned int rxEvenParity:1;/**< [27] Utopia Receive Parity Mode
    @li 1 - Check for Even Parity
    @li 0 - Check for Odd Parity.*/

    unsigned int rxHEC:1;    /**< [26] RxHEC    Header Error Check Mode. Enables/disables cell header
    error checking on the received cell header.
    @li 1 - HEC checking enabled
    @li 0 - HEC checking disabled */

    unsigned int rxCOSET:1;  /**< [25] If enabled the HEC is Exclusive-ORÆed with the value 0x55
  before being tested with the received HEC.
  @li 1 - Enable HEC ExOR with value 0x55.
    @li 0 - Use generated HEC value.*/

    unsigned int rxHECpass:1;    /**< [24] Specifies if the incoming cell HEC byte should be transferred
     after optional processing to the NPE2 Coprocessor Bus Interface or
     if it should be discarded.
     @li 1 - HEC maintained 53-byte/UDC cell sent to NPE2.
    @li 0 - HEC discarded 52-byte/UDC cell sent to NPE2 coprocessor.*/

    unsigned int reserved_1:1;    /**< [23] These bits are always 0 */

    unsigned int rxCellSize:7;    /**< [22:16] Receive cell size. Configures the receive cell size.
      Values between 52-64 are valid */

    unsigned int rxHashEnbGFC:1;      /**< [15] Specifies if the VPI field [11:8]/GFC field should be
      included in the Hash data input or if the bits should be padded
      with 1Æb0.
      @li 1 - VPI [11:8]/GFC field valid and used in Hash residue calculation.
      @li 0 - VPI [11:8]/GFC field padded with 1Æb0 */

    unsigned int rxPreHash:1; /**< [14] Enable Pre-hash value generation. Specifies if the
 incoming cell data should be pre-hashed to allow VPI/VCI header look-up
 in a hash table.
 @li 1 - Pre-hashing enabled
      @li 0 - Pre-hashing disabled */

    unsigned int reserved_2:1;    /**< [13] These bits are always 0 */

    unsigned int rxAddrRange:5;     /**< [12:8] In ATM master, MPHY mode,
     * this register specifies the upper
     * limit of the PHY polling logical range. The number of active PHYs are
     * RxAddrRange + 1.
     */
    unsigned int reserved_3:3;    /**< [7-5] These bits are always 0 .*/
    unsigned int rxPHYAddr:5;     /**< [4:0] When configured as a slave in an MPHY system this register
      * specifies the physical address of the PHY.
      */
    } utRxConfig;  /**< Rx config Utopia register */

      /**
    * @ingroup IxAtmdAccUtopiaCtrlAPI
      * @struct UtRxStatsConfig_
      * @brief Utopia Rx stats config Register
    */
    struct UtRxStatsConfig_
    {

    unsigned int vpi:12;  /**< [31:20] ATM VPI    VPI [11:0] OR GFC [3:0] and VPI [7:0]
    @li Note: if VCStatsRxGFC is set to 0 the GFC field is ignored in test. */

    unsigned int vci:16;  /**< [19:4] VCI [15:0] or PHY Address [4] */

    unsigned int pti:3;  /**< [3:1] PTI [2:0] or or PHY Address [3:1]
  @li Note: if VCStatsRxPTI is set to 0 the PTI field is ignored in test.
  @li Note: if VCStatsRxEnb is set to 0 only the PHY port address is used
  for statistics gathering.. */

    unsigned int clp:1;  /**< [0] CLP [0] or PHY Address [0]
  @li Note: if VCStatsRxCLP is set to 0 the CLP field is ignored in test.
  @li Note: if VCStatsRxEnb is set to 0 only the PHY port address is used
  for statistics gathering.. */
    } utRxStatsConfig;  /**< Rx stats config Utopia register */

  /**
    * @ingroup IxAtmdAccUtopiaCtrlAPI
  * @struct UtRxDefineIdle_
  * @brief Utopia Rx idle cells config Register
    */
    struct UtRxDefineIdle_
    {

    unsigned int vpi:12;  /**< [31:20] ATM VPI [11:0] OR GFC [3:0] and VPI [7:0]
    @li Note: if VCIdleRxGFC is set to 0 the GFC field is ignored in test. */

    unsigned int vci:16;  /**< [19:4] ATM VCI [15:0] */

    unsigned int pti:3;  /**< [3:1] ATM PTI PTI [2:0]
  @li Note: if VCIdleRxPTI is set to 0 the PTI field is ignored in test.*/

    unsigned int clp:1;  /**< [0] ATM CLP [0]
  @li Note: if VCIdleRxCLP is set to 0 the CLP field is ignored in test.*/
    } utRxDefineIdle;      /**< Rx idle cell config Utopia register */

      /**
    * @ingroup IxAtmdAccUtopiaCtrlAPI
      * @struct UtRxEnableFields_
      * @brief Utopia Rx enable Register
    */
    struct UtRxEnableFields_
    {

    unsigned int defineRxIdleGFC:1;/**< [31] This register is used to include or exclude the GFC
 field of the ATM header when testing for Idle cells.
 @li 1 - GFC field is valid.
    @li 0 - GFC field ignored.*/

    unsigned int defineRxIdlePTI:1;/**< [30] This register is used to include or exclude the PTI
 field of the ATM header when testing for Idle cells.
 @li 1 - PTI field is valid.
    @li 0 - PTI field ignored.*/

    unsigned int defineRxIdleCLP:1;/**< [29] This register is used to include or exclude the CLP
 field of the ATM header when testing for Idle cells.
 @li 1 - CLP field is valid.
    @li    0 - CLP field ignored.*/

    unsigned int phyStatsRxEnb:1;/**< [28] This register is used to enable or disable ATM statistics
     gathering based on the specified PHY address as defined in RxStatsConfig
     register.
     @li 1 - Enable statistics for specified receive PHY address.
    @li 0 - Disable statistics for specified receive PHY address.*/

    unsigned int vcStatsRxEnb:1;/**< [27] This register is used to enable or disable ATM statistics
    gathering based on a specific VPI/VCI address.
    @li 1 - Enable statistics for specified VPI/VCI address.
    @li 0 - Disable statistics for specified VPI/VCI address.*/

    unsigned int vcStatsRxGFC:1;/**< [26] This register is used to include or exclude the GFC field
    of the ATM header when ATM VPI/VCI statistics are enabled. GFC is only
    available at the UNI and uses the first 4-bits of the VPI field.
    @li 1 - GFC field is valid.
    @li 0 - GFC field ignored. */

    unsigned int vcStatsRxPTI:1;/**< [25] This register is used to include or exclude the PTI field
    of the ATM header when ATM VPI/VCI statistics are enabled.
    @li 1 - PTI field is valid.
    @li 0 - PTI field ignored.*/

    unsigned int vcStatsRxCLP:1;/**< [24] This register is used to include or exclude the CLP field
    of the ATM header when ATM VPI/VCI statistics are enabled.
    @li 1 - CLP field is valid.
    @li 0 - CLP field ignored. */

    unsigned int discardHecErr:1;/**< [23] Discard cells with an invalid HEC.
     @li 1 - Discard cells with HEC errors
    @li 0 - Cells with HEC errors are passed */

    unsigned int discardParErr:1;/**< [22] Discard cells containing parity errors.
     @li 1 - Discard cells with parity errors
    @li 0 - Cells with parity errors are passed */

    unsigned int discardIdle:1;    /**< [21] Discard Idle Cells based on DefineIdle register values
 @li    1 - Discard IDLE cells
    @li 0 - IDLE cells passed */

    unsigned int enbHecErrCnt:1;/**< [20] Enable Receive HEC Error Count.
    @li 1 - Enable count of received cells containing HEC errors
    @li 0 - No count is maintained. */

    unsigned int enbParErrCnt:1;/**< [19] Enable Parity Error Count
    @li    1 - Enable count of received cells containing Parity errors
    @li 0 - No count is maintained. */

    unsigned int enbIdleCellCnt:1;/**< [18] Enable Receive Idle Cell Count.
      @li 1 - Enable count of Idle cells received.
    @li 0 - No count is maintained.*/

    unsigned int enbSizeErrCnt:1;/**< [17] Enable Receive Size Error Count.
     @li 1 - Enable count of received cells of incorrect size
    @li    0 - No count is maintained. */

    unsigned int enbRxCellCnt:1;/**< [16] Enable Receive Valid Cell Count of non-idle/non-error cells.
    @li    1 - Enable count of valid cells received - non-idle/non-error
    @li 0 - No count is maintained. */

    unsigned int reserved_1:3;    /**< [15:13] These bits are always 0 */

    unsigned int rxCellOvrInt:1;      /**< [12] Enable CBI Utopia Receive Status Condition if the RxCellCount
      register overflows.
      @li 1 - CBI Receive Status asserted.
      @li    0 - No CBI Receive Status asserted.*/

    unsigned int invalidHecOvrInt:1;  /**< [11] Enable CBI Receive Status Condition if the InvalidHecCount
    register overflows.
    @li    1 - CBI Receive Condition asserted.
      @li 0 - No CBI Receive Condition asserted */

    unsigned int invalidParOvrInt:1;  /**< [10] Enable CBI Receive Status Condition if the InvalidParCount
    register overflows
    @li    1 - CBI Receive Condition asserted.
      @li 0 - No CBI Receive Condition asserted */

    unsigned int invalidSizeOvrInt:1;   /**< [9] Enable CBI Receive Status Condition if the InvalidSizeCount
     register overflows.
     @li 1 - CBI Receive Status Condition asserted.
      @li¸0 - No CBI Receive Status asserted */

    unsigned int rxIdleOvrInt:1;      /**< [8] Enable CBI Receive Status Condition if the RxIdleCount overflows.
      @li    1 - CBI Receive Condition asserted.
      @li 0 - No CBI Receive Condition asserted */

    unsigned int reserved_2:3;    /**< [7:5] These bits are always 0 */

    unsigned int rxAddrMask:5;    /**< [4:0] This register is used as a mask to allow the user to increase
    the PHY receive address range. The register should be programmed with
    the address-range limit, i.e. if set to 0x3 the address range increases
  to a maximum of 4 addresses. */
    } utRxEnableFields;      /**< Rx enable Utopia register */

      /**
    * @ingroup IxAtmdAccUtopiaCtrlAPI
      * @struct UtRxTransTable0_
      * @brief Utopia Rx translation table Register
    */
    struct UtRxTransTable0_
    {

    unsigned int phy0:5;  /**< [31-27] Rx Mapping value of logical phy 0 */

    unsigned int phy1:5;  /**< [26-22] Rx Mapping value of logical phy 1 */

    unsigned int phy2:5;  /**< [21-17] Rx Mapping value of logical phy 2 */

    unsigned int reserved_1:1;  /**< [16] These bits are always 0 */

    unsigned int phy3:5;  /**< [15-11] Rx Mapping value of logical phy 3 */

    unsigned int phy4:5;  /**< [10-6] Rx Mapping value of logical phy 4 */

    unsigned int phy5:5;  /**< [5-1] Rx Mapping value of logical phy 5 */

    unsigned int reserved_2:1;  /**< [0] These bits are always 0 */
    }

    utRxTransTable0;  /**< Rx translation table */

  /**
    * @ingroup IxAtmdAccUtopiaCtrlAPI
  * @struct UtRxTransTable1_
  * @brief Utopia Rx translation table Register
    */
    struct UtRxTransTable1_
    {

    unsigned int phy6:5;  /**< [31-27] Rx Mapping value of logical phy 6 */

    unsigned int phy7:5;  /**< [26-22] Rx Mapping value of logical phy 7 */

    unsigned int phy8:5;  /**< [21-17] Rx Mapping value of logical phy 8 */

    unsigned int reserved_1:1; /**< [16-0] These bits are always 0 */

    unsigned int phy9:5;  /**< [15-11] Rx Mapping value of logical phy 3 */

    unsigned int phy10:5;   /**< [10-6] Rx Mapping value of logical phy 4 */

    unsigned int phy11:5;   /**< [5-1] Rx Mapping value of logical phy 5 */

    unsigned int reserved_2:1;  /**< [0] These bits are always 0 */
    }

    utRxTransTable1;  /**< Rx translation table */

    /**
    * @ingroup IxAtmdAccUtopiaCtrlAPI
    * @struct UtRxTransTable2_
    * @brief Utopia Rx translation table Register
    */
    struct UtRxTransTable2_
    {

    unsigned int phy12:5;   /**< [31-27] Rx Mapping value of logical phy 6 */

    unsigned int phy13:5;   /**< [26-22] Rx Mapping value of logical phy 7 */

    unsigned int phy14:5;   /**< [21-17] Rx Mapping value of logical phy 8 */

    unsigned int reserved_1:1; /**< [16-0] These bits are always 0 */

    unsigned int phy15:5;   /**< [15-11] Rx Mapping value of logical phy 3 */

    unsigned int phy16:5;   /**< [10-6] Rx Mapping value of logical phy 4 */

    unsigned int phy17:5;   /**< [5-1] Rx Mapping value of logical phy 5 */

    unsigned int reserved_2:1;  /**< [0] These bits are always 0 */
    } utRxTransTable2;    /**< Rx translation table */

    /**
    * @ingroup IxAtmdAccUtopiaCtrlAPI
    * @struct UtRxTransTable3_
    * @brief Utopia Rx translation table Register
    */
    struct UtRxTransTable3_
    {

    unsigned int phy18:5;   /**< [31-27] Rx Mapping value of logical phy 6 */

    unsigned int phy19:5;   /**< [26-22] Rx Mapping value of logical phy 7 */

    unsigned int phy20:5;   /**< [21-17] Rx Mapping value of logical phy 8 */

    unsigned int reserved_1:1; /**< [16-0] These bits are always 0 */

    unsigned int phy21:5;   /**< [15-11] Rx Mapping value of logical phy 3 */

    unsigned int phy22:5;   /**< [10-6] Rx Mapping value of logical phy 4 */

    unsigned int phy23:5;   /**< [5-1] Rx Mapping value of logical phy 5 */

    unsigned int reserved_2:1;  /**< [0] These bits are always 0 */
    } utRxTransTable3;  /**< Rx translation table */

    /**
    * @ingroup IxAtmdAccUtopiaCtrlAPI
    * @struct UtRxTransTable4_
    * @brief Utopia Rx translation table Register
    */
    struct UtRxTransTable4_
    {

    unsigned int phy24:5;   /**< [31-27] Rx Mapping value of logical phy 6 */

    unsigned int phy25:5;   /**< [26-22] Rx Mapping value of logical phy 7 */

    unsigned int phy26:5;   /**< [21-17] Rx Mapping value of logical phy 8 */

    unsigned int reserved_1:1; /**< [16-0] These bits are always 0 */

    unsigned int phy27:5;   /**< [15-11] Rx Mapping value of logical phy 3 */

    unsigned int phy28:5;   /**< [10-6] Rx Mapping value of logical phy 4 */

    unsigned int phy29:5;   /**< [5-1] Rx Mapping value of logical phy 5 */

    unsigned int reserved_2:1;  /**< [0] These bits are always 0 */
    } utRxTransTable4;  /**< Rx translation table */

    /**
    * @ingroup IxAtmdAccUtopiaCtrlAPI
    * @struct UtRxTransTable5_
    * @brief Utopia Rx translation table Register
    */
    struct UtRxTransTable5_
    {

    unsigned int phy30:5;   /**< [31-27] Rx Mapping value of logical phy 6 */

    unsigned int reserved_1:27;     /**< [26-0] These bits are always 0 */

    } utRxTransTable5;  /**< Rx translation table */

    /**
    * @ingroup IxAtmdAccUtopiaCtrlAPI
    * @struct UtSysConfig_
    * @brief NPE setup Register
    */
    struct UtSysConfig_
    {

    unsigned int reserved_1:2;     /**< [31-30] These bits are always 0 */
    unsigned int txEnbFSM:1;    /**< [29] Enables the operation ofthe Utopia Transmit FSM
   * @li 1 - FSM enabled
   * @li 0 - FSM inactive
   */
    unsigned int rxEnbFSM:1;    /**< [28] Enables the operation ofthe Utopia Revieve FSM
   * @li 1 - FSM enabled
   * @li 0 - FSM inactive
   */
    unsigned int disablePins:1;    /**< [27] Disable Utopia interface I/O pins forcing the signals to an
   * inactive state.  Note that this bit is set on reset and must be
   * de-asserted
   * @li 0 - Normal data transfer
   * @li    1 - Utopia interface pins are forced inactive
    */
    unsigned int tstLoop:1;    /**< [26] Test Loop Back Enable.
    * @li Note: For loop back to function RxMode and Tx Mode must both be set
    * to single PHY mode.
    * @li 0 - Loop back
    * @li 1 - Normal operating mode
    */

    unsigned int txReset:1;   /**< [25] Resets the Utopia Coprocessor transmit module to a known state.
    * @li Note: All transmit configuration and status registers will be reset
    * to their reset values.
    * @li 0 - Normal operating mode¸
    * @li 1 - Reset transmit modules
    */

    unsigned int rxReset:1;   /**< [24] Resets the Utopia Coprocessor receive module to a known state.
    * @li Note: All receive configuration and status registers will be reset
    * to their reset values.
    * @li    0 - Normal operating mode
    * @li 1 - Reset receive modules
    */

    unsigned int reserved_2:24;     /**< [23-0] These bits are always 0 */
    } utSysConfig;  /**< NPE debug config */

}
IxAtmdAccUtopiaConfig;

typedef struct
{

    unsigned int utTxCellCount;  /**< count of cells transmitted */

    unsigned int utTxIdleCellCount;    /**< count of idle cells transmitted */

    /**
    * @ingroup IxAtmdAccUtopiaCtrlAPI
    * @struct UtTxCellConditionStatus_
    * @brief Utopia Tx Status Register
    */
    struct UtTxCellConditionStatus_
    {

    unsigned int reserved_1:2;   /**< [31:30] These bits are always 0 */
    unsigned int txFIFO2Underflow:1; /**< [29] This bit is set if 64-byte
                                     * Transmit FIFO2 indicates a FIFO underflow
                                     * error condition.
                                     */
    unsigned int txFIFO1Underflow:1; /**< [28] This bit is set if
                                     * 64-byte Transmit FIFO1 indicates a FIFO
                                     * underflow error condition.
                                     */
    unsigned int txFIFO2Overflow:1;  /**< [27] This bit is set if 64-byte
                                     * Transmit FIFO2 indicates a FIFO overflow
                                     * error condition.
                                     */
    unsigned int txFIFO1Overflow:1; /**< [26] This bit is set if 64-byte
                                    * Transmit FIFO1 indicates a FIFO overflow
                                    * error condition.
                                    */
    unsigned int txIdleCellCountOvr:1; /**< [25] This bit is set if the
                                       * TxIdleCellCount register overflows.
                                       */
    unsigned int txCellCountOvr:1; /**< [24] This bit is set if the
                                   * TxCellCount register overflows
                                   */
    unsigned int reserved_2:24;    /**< [23:0] These bits are always 0 */
    } utTxCellConditionStatus;    /**< Tx cells condition status */

    unsigned int utRxCellCount; /**< count of cell received */
    unsigned int utRxIdleCellCount;    /**< count of idle cell received */
    unsigned int utRxInvalidHECount;     /**< count of invalid cell
                                        * received because of HEC errors
                                        */
    unsigned int utRxInvalidParCount;  /**< count of invalid cell received
                                        * because of parity errors
                                        */
    unsigned int utRxInvalidSizeCount;  /**< count of invalid cell
                                        * received because of cell
                                        * size errors
                                        */

    /**
    * @ingroup IxAtmdAccUtopiaCtrlAPI
    * @struct UtRxCellConditionStatus_
    * @brief Utopia Rx Status Register
    */
    struct UtRxCellConditionStatus_
    {

    unsigned int reserved_1:3;  /**< [31:29] These bits are always 0.*/
    unsigned int rxCellCountOvr:1;      /**< [28] This bit is set if the RxCellCount register overflows. */
    unsigned int invalidHecCountOvr:1;    /**< [27] This bit is set if the InvalidHecCount register overflows.*/
    unsigned int invalidParCountOvr:1;    /**< [26] This bit is set if the InvalidParCount register overflows.*/
    unsigned int invalidSizeCountOvr:1;    /**< [25] This bit is set if the InvalidSizeCount register overflows.*/
    unsigned int rxIdleCountOvr:1;      /**< [24] This bit is set if the RxIdleCount register overflows.*/
    unsigned int reserved_2:4;  /**< [23:20] These bits are always 0 */
    unsigned int rxFIFO2Underflow:1;  /**< [19] This bit is set if 64-byte Receive FIFO2
                                      * indicates a FIFO underflow error condition.
                                      */
    unsigned int rxFIFO1Underflow:1;  /**< [18] This bit is set if 64-byte Receive
                                      * FIFO1 indicates a FIFO underflow error condition
                                    . */
    unsigned int rxFIFO2Overflow:1;    /**< [17] This bit is set if 64-byte Receive FIFO2
                                       * indicates a FIFO overflow error condition.
                                        */
    unsigned int rxFIFO1Overflow:1;    /**< [16] This bit is set if 64-byte Receive FIFO1
                                    * indicates a FIFO overflow error condition.
                                    */
    unsigned int reserved_3:16;      /**< [15:0] These bits are always 0. */
    } utRxCellConditionStatus;    /**< Rx cells condition status */

} IxAtmdAccUtopiaStatus;


 /**
 *
 * @ingroup IxAtmdAccCtrlAPI
 *
 * @fn ixAtmdAccUtopiaConfigSet (const IxAtmdAccUtopiaConfig *
                        ixAtmdAccUtopiaConfigPtr)
 *
 * @brief Send the configuration structure to the Utopia interface
 *
 * This function downloads the @a IxAtmdAccUtopiaConfig structure to
 * the Utopia and has the following effects
 *  @li setup the Utopia interface
 *  @li initialise the NPE
 *  @li reset the Utopia cell counters and status registers to known values
 *
 * This action has to be done once at initialisation. A lock is preventing
 * the concurrent use of @a ixAtmdAccUtopiaStatusGet() and
 * @A ixAtmdAccUtopiaConfigSet()
 *
 * @param *ixAtmdAccNPEConfigPtr @ref IxAtmdAccUtopiaConfig [in] - pointer to a structure to download to
 *  Utopia. This parameter cannot be a null pointer.
 *
 * @return @li IX_SUCCESS successful download
 * @return @li IX_FAIL error in the parameters, or configuration is not
 *         complete or failed
 *
 * @sa ixAtmdAccUtopiaStatusGet
 *
 */
PUBLIC IX_STATUS ixAtmdAccUtopiaConfigSet (const IxAtmdAccUtopiaConfig *
                        ixAtmdAccUtopiaConfigPtr);

PUBLIC IX_STATUS ixAtmdAccUtopiaStatusGet (IxAtmdAccUtopiaStatus *
                        ixAtmdAccUtopiaStatus);

PUBLIC IX_STATUS ixAtmdAccPortEnable (IxAtmLogicalPort port);

PUBLIC IX_STATUS ixAtmdAccPortDisable (IxAtmLogicalPort port);

PUBLIC BOOL ixAtmdAccPortDisableComplete (IxAtmLogicalPort port);

#endif /* IXATMDACCCTRL_H */



