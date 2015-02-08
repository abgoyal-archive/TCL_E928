


#ifndef IXNPEDL_H
#define IXNPEDL_H

#include "IxOsalTypes.h"
#include "IxNpeMicrocode.h"


#define IX_NPEDL_PARAM_ERR               2

#define IX_NPEDL_RESOURCE_ERR            3

#define IX_NPEDL_CRITICAL_NPE_ERR        4

#define IX_NPEDL_CRITICAL_MICROCODE_ERR  5

#define IX_NPEDL_DEVICE_ERR 6 


#define IX_NPEDL_NPEIMAGE_FIELD_MASK  0xff

#define IX_NPEDL_NPEIMAGE_NPEID_MASK  0xf

#define IX_NPEDL_NPEIMAGE_DEVICEID_MASK  0xf

#define IX_NPEDL_NPEIMAGE_BIT_LOC_NPEID  24

#define IX_NPEDL_NPEIMAGE_BIT_LOC_FUNCTIONALITYID  16

#define IX_NPEDL_NPEIMAGE_BIT_LOC_MAJOR  8

#define IX_NPEDL_NPEIMAGE_BIT_LOC_MINOR  0


#define ixNpeDlMicrocodeImageOverride(x) ixNpeDlMicrocodeImageLibraryOverride(x)

#define IxNpeDlVersionId IxNpeDlImageId

#define ixNpeDlVersionDownload(x,y) ixNpeDlImageDownload(x,y)

#define ixNpeDlAvailableVersionsCountGet(x) ixNpeDlAvailableImagesCountGet(x)

#define ixNpeDlAvailableVersionsListGet(x,y) ixNpeDlAvailableImagesListGet(x,y)

 /**
 * @def ixNpeDlLoadedVersionGet
 *
 * @brief  Map old terminology that uses term "version" to new term
 *        "image"
 *
 * @warning <b>THIS #define HAS BEEN DEPRECATED AND SHOULD NOT BE USED.</b>
 *       It will be removed in a future release.
 *       See @ref ixNpeDlNpeInitAndStart for more information.
 */
#define ixNpeDlLoadedVersionGet(x,y) ixNpeDlLoadedImageGet(x,y)

 /**
 * @def clientImage
 *
 * @brief  Map old terminology that uses term "image" to new term
 *        "image library"
 *
 * @warning <b>THIS #define HAS BEEN DEPRECATED AND SHOULD NOT BE USED.</b>
 *       It will be removed in a future release.
 *       See @ref ixNpeDlNpeInitAndStart for more information.
 */
#define clientImage clientImageLibrary

 /**
 * @def versionIdPtr
 *
 * @brief  Map old terminology that uses term "version" to new term
 *        "image"
 *
 * @warning <b>THIS #define HAS BEEN DEPRECATED AND SHOULD NOT BE USED.</b>
 *       It will be removed in a future release.
 *       See @ref ixNpeDlNpeInitAndStart for more information.
 */
#define versionIdPtr imageIdPtr

 /**
 * @def numVersionsPtr
 *
 * @brief  Map old terminology that uses term "version" to new term
 *        "image"
 *
 * @warning <b>THIS #define HAS BEEN DEPRECATED AND SHOULD NOT BE USED.</b>
 *       It will be removed in a future release.
 *       See @ref ixNpeDlNpeInitAndStart for more information.
 */
#define numVersionsPtr numImagesPtr

#define versionIdListPtr imageIdListPtr

#define IxNpeDlBuildId IxNpeDlFunctionalityId

#define buildId functionalityId

#define IX_NPEDL_MicrocodeImage IX_NPEDL_MicrocodeImageLibrary


typedef UINT8 IxNpeDlFunctionalityId;

typedef UINT8 IxNpeDlMajor;

typedef UINT8 IxNpeDlMinor;


typedef enum
{
  IX_NPEDL_NPEID_NPEA = 0,    /**< Identifies NPE A */
  IX_NPEDL_NPEID_NPEB,        /**< Identifies NPE B */
  IX_NPEDL_NPEID_NPEC,        /**< Identifies NPE C */
  IX_NPEDL_NPEID_MAX          /**< Total Number of NPEs */
} IxNpeDlNpeId;


typedef struct
{
    IxNpeDlNpeId   npeId;   /**< NPE ID */
    IxNpeDlFunctionalityId functionalityId; /**< Build ID indicates functionality of image */
    IxNpeDlMajor   major;   /**< Major Release Number */
    IxNpeDlMinor   minor;   /**< Minor Revision Number */
} IxNpeDlImageId;


PUBLIC IX_STATUS
ixNpeDlNpeInitAndStart (UINT32 npeImageId);

PUBLIC IX_STATUS
ixNpeDlCustomImageNpeInitAndStart (UINT32 *imageLibrary,
                    UINT32 npeImageId);


PUBLIC IX_STATUS
ixNpeDlLoadedImageFunctionalityGet (IxNpeDlNpeId npeId,
                                    UINT8 *functionalityId);


PUBLIC IX_STATUS
ixNpeDlMicrocodeImageLibraryOverride (UINT32 *clientImageLibrary);

PUBLIC IX_STATUS
ixNpeDlImageDownload (IxNpeDlImageId *imageIdPtr,
            BOOL verify);

PUBLIC IX_STATUS
ixNpeDlAvailableImagesCountGet (UINT32 *numImagesPtr);

PUBLIC IX_STATUS
ixNpeDlAvailableImagesListGet (IxNpeDlImageId *imageIdListPtr,
                 UINT32 *listSizePtr);

PUBLIC IX_STATUS
ixNpeDlLoadedImageGet (IxNpeDlNpeId npeId,
             IxNpeDlImageId *imageIdPtr);

PUBLIC IX_STATUS
ixNpeDlLatestImageGet (IxNpeDlNpeId npeId,
             IxNpeDlFunctionalityId functionalityId,
                    IxNpeDlImageId *imageIdPtr);

PUBLIC IX_STATUS
ixNpeDlNpeStopAndReset (IxNpeDlNpeId npeId);

PUBLIC IX_STATUS
ixNpeDlNpeExecutionStart (IxNpeDlNpeId npeId);

PUBLIC IX_STATUS
ixNpeDlNpeExecutionStop (IxNpeDlNpeId npeId);


PUBLIC IX_STATUS 
ixNpeDlUnload (void);

PUBLIC void
ixNpeDlStatsShow (void);

PUBLIC void
ixNpeDlStatsReset (void);

#endif /* IXNPEDL_H */



