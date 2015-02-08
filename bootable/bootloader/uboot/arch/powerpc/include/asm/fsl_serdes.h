

#ifndef __FSL_SERDES_H
#define __FSL_SERDES_H

#include <config.h>

enum srds_prtcl {
	NONE = 0,
	PCIE1,
	PCIE2,
	PCIE3,
	PCIE4,
	SATA1,
	SATA2,
	SRIO1,
	SRIO2,
	SGMII_FM1,
	SGMII_FM2,
	SGMII_TSEC1,
	SGMII_TSEC2,
	SGMII_TSEC3,
	SGMII_TSEC4,
	XAUI_FM1,
	XAUI_FM2,
	AURORA,
};

int is_serdes_configured(enum srds_prtcl device);

#endif /* __FSL_SERDES_H */
