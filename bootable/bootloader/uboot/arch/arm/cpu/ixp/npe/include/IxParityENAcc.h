


#ifndef IXPARITYENACC_H
#define IXPARITYENACC_H

#ifdef __ixp46X

#include "IxOsal.h"


typedef enum /**< IxParityENAccStatus */
{
  IX_PARITYENACC_SUCCESS = IX_SUCCESS, /**< The request is successful */
  IX_PARITYENACC_INVALID_PARAMETERS,   /**< Invalid or NULL parameters passed */
  IX_PARITYENACC_NOT_INITIALISED,      /**< Access layer has not been initialised before accessing the APIs */
  IX_PARITYENACC_ALREADY_INITIALISED,  /**< Access layer has already been initialised */ 
  IX_PARITYENACC_OPERATION_FAILED,     /**< Operation did not succeed due to hardware failure */
  IX_PARITYENACC_NO_PARITY             /**< No parity condition exits or has already been cleared */
} IxParityENAccStatus;

typedef enum  /**< IxParityENAccParityType */
{
  IX_PARITYENACC_EVEN_PARITY,    /**< Even Parity */
  IX_PARITYENACC_ODD_PARITY      /**< Odd Parity */
} IxParityENAccParityType;

typedef enum /**< IxParityENAccConfigOption */
{
  IX_PARITYENACC_DISABLE,       /**< Disable parity error detection */
  IX_PARITYENACC_ENABLE         /**< Enable parity error detection */
} IxParityENAccConfigOption;

typedef struct /**< IxParityENAccNpeConfig */
{
  IxParityENAccConfigOption ideEnabled; /**< NPE IMem, DMem and External */
  IxParityENAccParityType parityOddEven; /**< Parity - Odd or Even */
} IxParityENAccNpeConfig ;


typedef struct /**< IxParityENAccMcuConfig */ 
{
  IxParityENAccConfigOption singlebitDetectEnabled;      /**< Single-bit parity error detection */
  IxParityENAccConfigOption singlebitCorrectionEnabled;  /**< Single-bit parity error correction */
  IxParityENAccConfigOption multibitDetectionEnabled;    /**< Multi-bit  parity error detection */
} IxParityENAccMcuConfig ;


typedef struct /**< IxParityENAccEbcConfig */
{
  IxParityENAccConfigOption ebcCs0Enabled;    /**< Expansion Bus Controller - Chip Select 0 */
  IxParityENAccConfigOption ebcCs1Enabled;    /**< Expansion Bus Controller - Chip Select 1 */
  IxParityENAccConfigOption ebcCs2Enabled;    /**< Expansion Bus Controller - Chip Select 2 */
  IxParityENAccConfigOption ebcCs3Enabled;    /**< Expansion Bus Controller - Chip Select 3 */
  IxParityENAccConfigOption ebcCs4Enabled;    /**< Expansion Bus Controller - Chip Select 4 */
  IxParityENAccConfigOption ebcCs5Enabled;    /**< Expansion Bus Controller - Chip Select 5 */
  IxParityENAccConfigOption ebcCs6Enabled;    /**< Expansion Bus Controller - Chip Select 6 */
  IxParityENAccConfigOption ebcCs7Enabled;    /**< Expansion Bus Controller - Chip Select 7 */
  IxParityENAccConfigOption ebcExtMstEnabled; /**< External Master on Expansion bus */
  IxParityENAccParityType parityOddEven;      /**< Parity - Odd or Even */
} IxParityENAccEbcConfig ;

typedef struct /**< IxParityENAccHWParityConfig */
{ 
  IxParityENAccNpeConfig npeAConfig;     /**< NPE A parity detection is to be enabled/disabled */
  IxParityENAccNpeConfig npeBConfig;     /**< NPE B parity detection is to be enabled/disabled */
  IxParityENAccNpeConfig npeCConfig;     /**< NPE C parity detection is to be enabled/disabled */
  IxParityENAccMcuConfig mcuConfig;      /**< MCU pairty detection is to be enabled/disabled */
  IxParityENAccConfigOption swcpEnabled; /**< SWCP parity detection is to be enabled */
  IxParityENAccConfigOption aqmEnabled;  /**< AQM parity detection is to be enabled */
  IxParityENAccEbcConfig ebcConfig;      /**< Expansion Bus Controller parity detection is to be enabled/disabled */
} IxParityENAccHWParityConfig;


typedef struct  /* IxParityENAccNpeParityErrorStats */
{
  UINT32 parityErrorsIMem;         /**< Parity errors in Instruction Memory */
  UINT32 parityErrorsDMem;         /**< Parity errors in Data Memory */
  UINT32 parityErrorsExternal;     /**< Parity errors in NPE External Entities */
} IxParityENAccNpeParityErrorStats;

typedef struct  /* IxParityENAccMcuParityErrorStats */
{
  UINT32 parityErrorsSingleBit;    /**< Parity errors of the type Single-Bit */
  UINT32 parityErrorsMultiBit;     /**< Parity errors of the type Multi-Bit */
  UINT32 parityErrorsOverflow;     /**< Parity errors when more than two parity errors occured */
} IxParityENAccMcuParityErrorStats;

typedef struct  /* IxParityENAccEbcParityErrorStats */
{
  UINT32 parityErrorsInbound;      /**< Odd bit parity errors on inbound transfers */
  UINT32 parityErrorsOutbound;     /**< Odd bit parity errors on outbound transfers */
} IxParityENAccEbcParityErrorStats;


typedef struct  /**< IxParityENAccParityErrorStats */
{
  IxParityENAccNpeParityErrorStats  npeStats;  /**< NPE parity error statistics */
  IxParityENAccMcuParityErrorStats  mcuStats;  /**< MCU parity error statistics */
  IxParityENAccEbcParityErrorStats  ebcStats;  /**< EBC parity error statistics */
  UINT32                            swcpStats; /**< SWCP parity error statistics */
  UINT32                            aqmStats;  /**< AQM parity error statistics */
} IxParityENAccParityErrorStats;


typedef enum  /**< IxParityENAccParityErrorSource  */
{
  IX_PARITYENACC_NPE_A_IMEM,     /**< NPE A - Instruction memory */
  IX_PARITYENACC_NPE_A_DMEM,     /**< NPE A - Data memory */
  IX_PARITYENACC_NPE_A_EXT,      /**< NPE A - External Entity*/
  IX_PARITYENACC_NPE_B_IMEM,     /**< NPE B - Instruction memory */
  IX_PARITYENACC_NPE_B_DMEM,     /**< NPE B - Data memory */
  IX_PARITYENACC_NPE_B_EXT,      /**< NPE B - External Entity*/
  IX_PARITYENACC_NPE_C_IMEM,     /**< NPE C - Instruction memory */
  IX_PARITYENACC_NPE_C_DMEM,     /**< NPE C - Data memory */
  IX_PARITYENACC_NPE_C_EXT,      /**< NPE C - External Entity*/
  IX_PARITYENACC_SWCP,           /**< SWCP */
  IX_PARITYENACC_AQM,            /**< AQM */
  IX_PARITYENACC_MCU_SBIT,       /**< DDR Memory Controller Unit - Single bit parity */
  IX_PARITYENACC_MCU_MBIT,       /**< DDR Memory Controller Unit - Multi bit parity */
  IX_PARITYENACC_MCU_OVERFLOW,   /**< DDR Memory Controller Unit - Parity errors in excess of two */
  IX_PARITYENACC_EBC_CS,         /**< Expansion Bus Controller - Chip Select */
  IX_PARITYENACC_EBC_EXTMST      /**< Expansion Bus Controller - External Master */
} IxParityENAccParityErrorSource;

typedef enum  /**< IxParityENAccParityErrorAccess  */
{
  IX_PARITYENACC_READ,   /**< Read Access  */
  IX_PARITYENACC_WRITE   /**< Write Access */
} IxParityENAccParityErrorAccess;

typedef UINT32 IxParityENAccParityErrorAddress;

typedef UINT32 IxParityENAccParityErrorData;

typedef enum  /**< IxParityENAccParityErrorRequester  */
{
  IX_PARITYENACC_MPI,     /**< Direct Memory Port Interface  */
  IX_PARITYENACC_AHB_BUS  /**< South or North AHB Bus */
} IxParityENAccParityErrorRequester;

typedef enum  /**< IxParityENAccAHBErrorMaster */
{
  IX_PARITYENACC_AHBN_MST_NPE_A,       /**< NPE - A */
  IX_PARITYENACC_AHBN_MST_NPE_B,       /**< NPE - B */
  IX_PARITYENACC_AHBN_MST_NPE_C,       /**< NPE - C */
  IX_PARITYENACC_AHBS_MST_XSCALE,      /**< XScale Bus Interface Unit */
  IX_PARITYENACC_AHBS_MST_PBC,         /**< PCI Bus Controller */
  IX_PARITYENACC_AHBS_MST_EBC,         /**< Expansion Bus Controller */
  IX_PARITYENACC_AHBS_MST_AHB_BRIDGE,  /**< AHB Bridge */
  IX_PARITYENACC_AHBS_MST_USBH         /**< USB Host Controller */
} IxParityENAccAHBErrorMaster;

typedef enum  /**< IxParityENAccAHBErrorSlave */
{
  IX_PARITYENACC_AHBN_SLV_MCU,         /**< Memory Control Unit */
  IX_PARITYENACC_AHBN_SLV_AHB_BRIDGE,  /**< AHB Bridge */
  IX_PARITYENACC_AHBS_SLV_MCU,         /**< XScale Bus Interface Unit */
  IX_PARITYENACC_AHBS_SLV_APB_BRIDGE,  /**< APB Bridge */
  IX_PARITYENACC_AHBS_SLV_AQM,         /**< AQM */
  IX_PARITYENACC_AHBS_SLV_RSA,         /**< RSA (Crypto Bus) */
  IX_PARITYENACC_AHBS_SLV_PBC,         /**< PCI Bus Controller */
  IX_PARITYENACC_AHBS_SLV_EBC,         /**< Expansion Bus Controller */
  IX_PARITYENACC_AHBS_SLV_USBH         /**< USB Host Controller */
} IxParityENAccAHBErrorSlave;

typedef struct  /**< IxParityENAccAHBErrorTransaction  */
{
  IxParityENAccAHBErrorMaster  ahbErrorMaster; /**< Master on AHB bus */
  IxParityENAccAHBErrorSlave   ahbErrorSlave;  /**< Slave  on AHB bus */
} IxParityENAccAHBErrorTransaction;

typedef struct /**< IxParityENAccParityErrorContextMessage */
{
  IxParityENAccParityErrorSource     pecParitySource; /**< Source info of parity error */
  IxParityENAccParityErrorAccess     pecAccessType;   /**< Read or Write Access
                                                           Read  - NPE, SWCP, AQM, DDR MCU,
                                                                   Exp Bus Ctrlr (Outbound)
                                                           Write - DDR MCU,
                                                                   Exp Bus Ctrlr (Inbound 
                                                                   i.e., External Master) */
  IxParityENAccParityErrorAddress    pecAddress;      /**< Address faulty location
                                                           Valid only for AQM, DDR MCU, 
                                                           Exp Bus Ctrlr */
  IxParityENAccParityErrorData       pecData;         /**< Data read from the faulty location
                                                           Valid only for AQM and DDR MCU
                                                           For DDR MCU it is the bit location
                                                           of the Single-bit parity */
  IxParityENAccParityErrorRequester  pecRequester;    /**< Requester of SDRAM memory access
                                                           Valid only for the DDR MCU */
  IxParityENAccAHBErrorTransaction   ahbErrorTran;    /**< Master and Slave information on the
                                                           last AHB Error Transaction */
} IxParityENAccParityErrorContextMessage;

typedef void (*IxParityENAccCallback) (void);




PUBLIC IxParityENAccStatus ixParityENAccInit(void);


PUBLIC IxParityENAccStatus ixParityENAccCallbackRegister (
           IxParityENAccCallback parityErrNfyCallBack);


PUBLIC IxParityENAccStatus ixParityENAccParityDetectionConfigure (
           const IxParityENAccHWParityConfig *hwParityConfig);


PUBLIC IxParityENAccStatus ixParityENAccParityDetectionQuery(
           IxParityENAccHWParityConfig * const hwParityConfig);


PUBLIC IxParityENAccStatus ixParityENAccParityErrorContextGet( 
           IxParityENAccParityErrorContextMessage * const pecMessage);


PUBLIC IxParityENAccStatus ixParityENAccParityErrorInterruptClear (
          const IxParityENAccParityErrorContextMessage *pecMessage);


PUBLIC IxParityENAccStatus ixParityENAccStatsGet (
            IxParityENAccParityErrorStats * const ixParityErrorStats);


PUBLIC IxParityENAccStatus ixParityENAccStatsShow (void);


PUBLIC IxParityENAccStatus ixParityENAccStatsReset (void);

#endif /* IXPARITYENACC_H */
#endif /* __ixp46X */


