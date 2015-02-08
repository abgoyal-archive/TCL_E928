

#ifndef IxOsServicesComponents_H
#define IxOsServicesComponents_H

#include "IxOsalBackward.h"
 * codelets_parityENAcc
 * timeSyncAcc
 * parityENAcc
 * sspAcc
 * i2c
 * integration_sspAcc
 * integration_i2c
#define ix_timeSyncAcc         36
#define ix_parityENAcc         37
#define ix_codelets_parityENAcc     38
#define ix_sspAcc              39
#define ix_i2c                 40
#define ix_integration_sspAcc  41
#define ix_integration_i2c     42
#define ix_osal		       43
#define ix_integration_parityENAcc  44
#define ix_integration_timeSyncAcc  45

#if (IX_COMPONENT_NAME == ix_timeSyncAcc)

#if defined (IX_OSSERV_VXWORKS_LE)

#define CSR_LE_DATA_COHERENT_MAPPING

#endif /* IX_OSSERV_VXWORKS_LE */

#endif /* timeSyncAcc */

#if (IX_COMPONENT_NAME == ix_parityENAcc)

#if defined (IX_OSSERV_VXWORKS_LE)

#define CSR_LE_DATA_COHERENT_MAPPING

#endif /* IX_OSSERV_VXWORKS_LE */

#endif /* parityENAcc */

#if (IX_COMPONENT_NAME == ix_codelets_parityENAcc)

#if defined (IX_OSSERV_VXWORKS_LE)

#define CSR_LE_DATA_COHERENT_MAPPING

#endif /* IX_OSSERV_VXWORKS_LE */

#endif /* codelets_parityENAcc */

#endif /* IxOsServicesComponents_H */

#if (IX_COMPONENT_NAME == ix_integration_timeSyncAcc)

#if defined (IX_OSSERV_VXWORKS_LE)

#define CSR_LE_DATA_COHERENT_MAPPING

#endif /* IX_OSSERV_VXWORKS_LE */

#endif /* integration_timeSyncAcc */

#if (IX_COMPONENT_NAME == ix_integration_parityENAcc)

#if defined (IX_OSSERV_VXWORKS_LE)

#define CSR_LE_DATA_COHERENT_MAPPING

#endif /* IX_OSSERV_VXWORKS_LE */

#endif /* integration_parityENAcc */
