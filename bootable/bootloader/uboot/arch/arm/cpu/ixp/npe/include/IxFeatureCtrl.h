

#ifndef IXFEATURECTRL_H
#define IXFEATURECTRL_H

#include "IxOsal.h"



#define  IX_FEATURE_CTRL_COMPONENT_DISABLED 0

#define  IX_FEATURE_CTRL_COMPONENT_ENABLED  1


#define IX_FEATURE_CTRL_SILICON_TYPE_A0   0

#define IX_FEATURE_CTRL_SILICON_TYPE_B0   1

#define IX_FEATURE_CTRL_SILICON_STEPPING_MASK  0xF 

#define IX_FEATURE_CTRL_DEVICE_TYPE_MASK  (0x7) 

#define IX_FEATURE_CTRL_DEVICE_TYPE_OFFSET  9


#define IX_FEATURE_CTRL_XSCALE_FREQ_533  ((0x1C)<<4)

#define IX_FEATURE_CTRL_XSCALE_FREQ_400  ((0x1D)<<4)

#define IX_FEATURE_CTRL_XSCALE_FREQ_266 ((0x1F)<<4)   

#define IX_FEATURE_CTRL_XSCALE_FREQ_MASK ((0xFF)<<4)  

#define IX_FEATURECTRL_REG_UTOPIA_32PHY  0x0

#define IX_FEATURECTRL_REG_UTOPIA_16PHY  0x1

#define IX_FEATURECTRL_REG_UTOPIA_8PHY   0x2

#define IX_FEATURECTRL_REG_UTOPIA_4PHY   0x3

#ifdef __ixp46X

#define IX_FEATURECTRL_REG_XSCALE_533FREQ   0x0

#define IX_FEATURECTRL_REG_XSCALE_667FREQ   0x1

#define IX_FEATURECTRL_REG_XSCALE_400FREQ   0x2

#define IX_FEATURECTRL_REG_XSCALE_266FREQ   0x3

#endif /* __ixp46X */

#define IX_FEATURECTRL_COMPONENT_NOT_AVAILABLE  0x0000

#define IX_FEATURECTRL_COMPONENT_ALWAYS_AVAILABLE  0xffff

#define IX_FEATURE_CTRL_SWCONFIG_DISABLED 0  

#define IX_FEATURE_CTRL_SWCONFIG_ENABLED 1  


typedef enum
{
    IX_FEATURE_CTRL_SW_BUILD_IXP42X = 0, /**<Build type is IXP42X */
    IX_FEATURE_CTRL_SW_BUILD_IXP46X      /**<Build type is IXP46X */
} IxFeatureCtrlBuildDevice;

typedef enum
{
    IX_FEATURECTRL_ETH_LEARNING = 0,       /**< EthDB Learning Feature */
    IX_FEATURECTRL_ORIGB0_DISPATCHER,  /**< IXP42X B0 and IXP46X dispatcher without 
                                            livelock prevention functionality Feature */
    IX_FEATURECTRL_SWCONFIG_MAX        /**< Maximum boudary for IxFeatureCtrlSwConfig  */
} IxFeatureCtrlSwConfig;


/*Section generic to both IXP42X and IXP46X*/

typedef enum
{
    IX_FEATURECTRL_RCOMP = 0, /**<bit location for RComp Circuitry*/
    IX_FEATURECTRL_USB,       /**<bit location for USB Controller*/
    IX_FEATURECTRL_HASH,      /**<bit location for Hashing Coprocessor*/
    IX_FEATURECTRL_AES,       /**<bit location for AES Coprocessor*/
    IX_FEATURECTRL_DES,       /**<bit location for DES Coprocessor*/
    IX_FEATURECTRL_HDLC,      /**<bit location for HDLC Coprocessor*/
    IX_FEATURECTRL_AAL,       /**<bit location for AAL Coprocessor*/
    IX_FEATURECTRL_HSS,       /**<bit location for HSS Coprocessor*/
    IX_FEATURECTRL_UTOPIA,    /**<bit location for UTOPIA Coprocessor*/
    IX_FEATURECTRL_ETH0,      /**<bit location for Ethernet 0 Coprocessor*/
    IX_FEATURECTRL_ETH1,      /**<bit location for Ethernet 1 Coprocessor*/
    IX_FEATURECTRL_NPEA,      /**<bit location for NPE A*/
    IX_FEATURECTRL_NPEB,      /**<bit location for NPE B*/
    IX_FEATURECTRL_NPEC,      /**<bit location for NPE C*/
    IX_FEATURECTRL_PCI,       /**<bit location for PCI Controller*/
    IX_FEATURECTRL_ECC_TIMESYNC,     /**<bit location for TimeSync Coprocessor*/
    IX_FEATURECTRL_UTOPIA_PHY_LIMIT, /**<bit location for Utopia PHY Limit Status*/
    IX_FEATURECTRL_UTOPIA_PHY_LIMIT_BIT2, /**<2nd bit of PHY limit status*/
    IX_FEATURECTRL_USB_HOST_CONTROLLER, /**<bit location for USB host controller*/
    IX_FEATURECTRL_NPEA_ETH,  /**<bit location for NPE-A Ethernet Disable*/
    IX_FEATURECTRL_NPEB_ETH,  /**<bit location for NPE-B Ethernet 1-3 Coprocessors Disable*/
    IX_FEATURECTRL_RSA,       /**<bit location for RSA Crypto block Coprocessors Disable*/
    IX_FEATURECTRL_XSCALE_MAX_FREQ, /**<bit location for XScale max frequency*/
    IX_FEATURECTRL_XSCALE_MAX_FREQ_BIT2, /**<2nd xscale max freq bit NOT TO BE USED */
    IX_FEATURECTRL_MAX_COMPONENTS
} IxFeatureCtrlComponentType;

typedef enum
{
    IX_FEATURE_CTRL_DEVICE_TYPE_IXP42X = 0, /**<Device type is IXP42X */
    IX_FEATURE_CTRL_DEVICE_TYPE_IXP46X, /**<Device type is IXP46X */
    IX_FEATURE_CTRL_DEVICE_TYPE_MAX /**<Max devices */
} IxFeatureCtrlDeviceId;




typedef UINT32 IxFeatureCtrlReg;

typedef UINT32 IxFeatureCtrlProductId;


PUBLIC IxFeatureCtrlReg
ixFeatureCtrlRead (void);

IxFeatureCtrlDeviceId
ixFeatureCtrlDeviceRead (void);

IxFeatureCtrlBuildDevice
ixFeatureCtrlSoftwareBuildGet (void);

PUBLIC IxFeatureCtrlReg
ixFeatureCtrlHwCapabilityRead (void);

PUBLIC void
ixFeatureCtrlWrite (IxFeatureCtrlReg expUnitReg);

PUBLIC IX_STATUS
ixFeatureCtrlComponentCheck (IxFeatureCtrlComponentType componentType);

PUBLIC IxFeatureCtrlProductId
ixFeatureCtrlProductIdRead (void) ;

PUBLIC IX_STATUS
ixFeatureCtrlSwConfigurationCheck (IxFeatureCtrlSwConfig swConfigType);

PUBLIC void
ixFeatureCtrlSwConfigurationWrite (IxFeatureCtrlSwConfig swConfigType, BOOL enabled);

PUBLIC void
ixFeatureCtrlIxp400SwVersionShow (void);

#endif /* IXFEATURECTRL_H */

