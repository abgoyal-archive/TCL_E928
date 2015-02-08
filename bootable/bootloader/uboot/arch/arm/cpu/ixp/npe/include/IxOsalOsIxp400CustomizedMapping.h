

#ifndef IxOsalOsIxp400CustomizedMapping_H
#define IxOsalOsIxp400CustomizedMapping_H


#if defined (IX_OSAL_LINUX_BE)
#error Only include IxOsalOsIxp400CustomizedMapping.h in Little Endian
#endif

 /*
  * Components don't have to be in this list if
  * the default mapping is OK.
  */
#define ix_osal                1
#define ix_dmaAcc              2
#define ix_atmdAcc             3

#define ix_atmsch              5
#define ix_ethAcc              6
#define ix_npeMh               7
#define ix_qmgr                8
#define ix_npeDl               9
#define ix_atmm                10
#define ix_hssAcc              11
#define ix_ethDB               12
#define ix_ethMii              13
#define ix_timerCtrl           14
#define ix_adsl                15
#define ix_usb                 16
#define ix_uartAcc             17
#define ix_featureCtrl         18
#define ix_cryptoAcc           19
#define ix_unloadAcc           33
#define ix_perfProfAcc         34
#define ix_parityENAcc                 49
#define ix_sspAcc                      51
#define ix_timeSyncAcc                 52
#define ix_i2c                         53

#define ix_codelets_uartAcc    21
#define ix_codelets_timers     22
#define ix_codelets_atm        23
#define ix_codelets_ethAal5App 24
#define ix_codelets_demoUtils  26
#define ix_codelets_usb        27
#define ix_codelets_hssAcc     28
#define ix_codelets_dmaAcc         40
#define ix_codelets_cryptoAcc	   41
#define ix_codelets_perfProfAcc    42
#define ix_codelets_ethAcc         43
#define ix_codelets_parityENAcc        54
#define ix_codelets_timeSyncAcc        55


#endif /* IxOsalOsIxp400CustomizedMapping_H */


#if (IX_COMPONENT_NAME == ix_osal)

#define IX_OSAL_LE_AC_MAPPING

#endif /* osal */

#if (IX_COMPONENT_NAME == ix_dmaAcc)

#define IX_OSAL_LE_AC_MAPPING

#endif /* dmaAcc */

#if (IX_COMPONENT_NAME == ix_atmdAcc)

#define IX_OSAL_LE_AC_MAPPING

#endif /* atmdAcc */

#if (IX_COMPONENT_NAME == ix_atmsch)

#define IX_OSAL_LE_AC_MAPPING

#endif /* atmsch */

#if (IX_COMPONENT_NAME == ix_ethAcc)

#define IX_OSAL_LE_AC_MAPPING

#endif /* ethAcc */

#if (IX_COMPONENT_NAME == ix_npeMh)

#define IX_OSAL_LE_AC_MAPPING

#endif /* npeMh */

#if (IX_COMPONENT_NAME == ix_qmgr)

#define IX_OSAL_LE_DC_MAPPING

#endif /* qmgr */

#if (IX_COMPONENT_NAME == ix_npeDl)

#define IX_OSAL_LE_AC_MAPPING

#endif /* npeDl */

#if (IX_COMPONENT_NAME == ix_atmm)

#define IX_OSAL_LE_AC_MAPPING

#endif /* atmm */

#if (IX_COMPONENT_NAME == ix_ethMii)

#define IX_OSAL_LE_AC_MAPPING

#endif /* ethMii */


#if (IX_COMPONENT_NAME == ix_adsl)

#define IX_OSAL_LE_AC_MAPPING

#endif /* adsl */

#if (IX_COMPONENT_NAME == ix_usb)

#define IX_OSAL_LE_AC_MAPPING

#endif /* usb */

#if (IX_COMPONENT_NAME == ix_uartAcc)

#define IX_OSAL_LE_AC_MAPPING

#endif /* uartAcc */

#if (IX_COMPONENT_NAME == ix_featureCtrl)

#define IX_OSAL_LE_AC_MAPPING

#endif /* featureCtrl */

#if (IX_COMPONENT_NAME == ix_cryptoAcc)

#define IX_OSAL_LE_AC_MAPPING

#endif /* cryptoAcc */

#if (IX_COMPONENT_NAME == ix_codelets_usb)

#define IX_OSAL_LE_AC_MAPPING

#endif /* codelets_usb */


#if (IX_COMPONENT_NAME == ix_codelets_uartAcc)

#define IX_OSAL_LE_AC_MAPPING

#endif /* codelets_uartAcc */



#if (IX_COMPONENT_NAME == ix_codelets_timers)

#define IX_OSAL_LE_AC_MAPPING

#endif /* codelets_timers */

#if (IX_COMPONENT_NAME == ix_codelets_atm)

#define IX_OSAL_LE_AC_MAPPING

#endif /* codelets_atm */

#if (IX_COMPONENT_NAME == ix_codelets_ethAal5App)

#define IX_OSAL_LE_AC_MAPPING

#endif /* codelets_ethAal5App */

#if (IX_COMPONENT_NAME == ix_codelets_ethAcc)

#define IX_OSAL_LE_AC_MAPPING

#endif /* codelets_ethAcc */


#if (IX_COMPONENT_NAME == ix_codelets_demoUtils)

#define IX_OSAL_LE_AC_MAPPING

#endif /* codelets_demoUtils */



#if (IX_COMPONENT_NAME == ix_perfProfAcc)

#define IX_OSAL_LE_AC_MAPPING

#endif /* perfProfAcc */


#if (IX_COMPONENT_NAME == ix_unloadAcc)

#define IX_OSAL_LE_AC_MAPPING

#endif /* unloadAcc */





#if (IX_COMPONENT_NAME == ix_parityENAcc)

#define IX_OSAL_LE_AC_MAPPING

#endif /* parityENAcc */

#if (IX_COMPONENT_NAME == ix_codelets_parityENAcc)

#define IX_OSAL_LE_AC_MAPPING

#endif /* codelets_parityENAcc */




#if (IX_COMPONENT_NAME == ix_timeSyncAcc)

#define IX_OSAL_LE_AC_MAPPING

#endif /* timeSyncAcc */


#if (IX_COMPONENT_NAME == ix_codelets_timeSyncAcc)

#define IX_OSAL_LE_AC_MAPPING

#endif /* codelets_timeSyncAcc */




#if (IX_COMPONENT_NAME == ix_i2c)

#define IX_OSAL_LE_AC_MAPPING

#endif /* i2c */



#if (IX_COMPONENT_NAME == ix_sspAcc)

#define IX_OSAL_LE_AC_MAPPING

#endif /* sspAcc */


