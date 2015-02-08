


#ifndef IXNPEDLIMAGEMGR_P_H
#define IXNPEDLIMAGEMGR_P_H


#include "IxNpeDl.h"
#include "IxOsalTypes.h"



#define IX_NPEDL_IMAGEMGR_SIGNATURE      0xDEADBEEF

#define IX_NPEDL_IMAGEMGR_END_OF_HEADER  0xFFFFFFFF

#define IX_NPEDL_IMAGEID_NPEID_OFFSET      24

#define IX_NPEDL_IMAGEID_DEVICEID_OFFSET   28

#define IX_NPEDL_IMAGEID_FUNCTIONID_OFFSET 16

#define IX_NPEDL_IMAGEID_MAJOR_OFFSET      8

#define IX_NPEDL_IMAGEID_MINOR_OFFSET      0


#define IX_NPEDL_NPEID_FROM_IMAGEID_GET(imageId) \
    (((imageId) >> IX_NPEDL_IMAGEID_NPEID_OFFSET) & \
     IX_NPEDL_NPEIMAGE_NPEID_MASK)

#define IX_NPEDL_DEVICEID_FROM_IMAGEID_GET(imageId) \
    (((imageId) >> IX_NPEDL_IMAGEID_DEVICEID_OFFSET) & \
     IX_NPEDL_NPEIMAGE_DEVICEID_MASK)

#define IX_NPEDL_FUNCTIONID_FROM_IMAGEID_GET(imageId) \
    (((imageId) >> IX_NPEDL_IMAGEID_FUNCTIONID_OFFSET) & \
     IX_NPEDL_NPEIMAGE_FIELD_MASK)

#define IX_NPEDL_MAJOR_FROM_IMAGEID_GET(imageId) \
    (((imageId) >> IX_NPEDL_IMAGEID_MAJOR_OFFSET) & \
     IX_NPEDL_NPEIMAGE_FIELD_MASK)

#define IX_NPEDL_MINOR_FROM_IMAGEID_GET(imageId) \
    (((imageId) >> IX_NPEDL_IMAGEID_MINOR_OFFSET) & \
     IX_NPEDL_NPEIMAGE_FIELD_MASK)



IX_STATUS
ixNpeDlImageMgrMicrocodeImageLibraryOverride (UINT32 *clientImageLibrary);


IX_STATUS
ixNpeDlImageMgrImageListExtract (IxNpeDlImageId *imageListPtr,
				   UINT32 *numImages);


IX_STATUS
ixNpeDlImageMgrImageLocate (IxNpeDlImageId *imageId,
			      UINT32 **imagePtr,
			      UINT32 *imageSize);

IX_STATUS
ixNpeDlImageMgrLatestImageExtract (IxNpeDlImageId *imageId);

void
ixNpeDlImageMgrStatsShow (void);


void
ixNpeDlImageMgrStatsReset (void);


IX_STATUS
ixNpeDlImageMgrImageFind (UINT32 *imageLibrary,
                          UINT32 imageId,
			  UINT32 **imagePtr,
			  UINT32 *imageSize);


#endif /* IXNPEDLIMAGEMGR_P_H */

