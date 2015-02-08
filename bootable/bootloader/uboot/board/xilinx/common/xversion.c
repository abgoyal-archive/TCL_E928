

/***************************** Include Files *********************************/

#include "xbasic_types.h"
#include "xversion.h"

/************************** Constant Definitions *****************************/

#define XVE_MAJOR_SHIFT_VALUE       12
#define XVE_MINOR_ONLY_MASK         0x0FE0
#define XVE_MINOR_SHIFT_VALUE       5
#define XVE_COMP_ONLY_MASK          0x001F

#define XVE_MAJOR_CHAR      0	/* major revision 0 - 9 */
#define XVE_MINOR_TENS_CHAR 2	/* minor revision tens 0 - 9 */
#define XVE_MINOR_ONES_CHAR 3	/* minor revision ones 0 - 9 */
#define XVE_COMP_CHAR       4	/* compatability revision a - z */
#define XVE_END_STRING_CHAR 5

/**************************** Type Definitions *******************************/

/***************** Macros (Inline Functions) Definitions *********************/

/************************** Function Prototypes ******************************/

static u32 IsVersionStringValid(s8 * StringPtr);

void
XVersion_UnPack(XVersion * InstancePtr, u16 PackedVersion)
{
	/* not implemented yet since CROM related */
}

XStatus
XVersion_Pack(XVersion * InstancePtr, u16 * PackedVersionPtr)
{
	/* not implemented yet since CROM related */

	return XST_SUCCESS;
}

u32
XVersion_IsEqual(XVersion * InstancePtr, XVersion * VersionPtr)
{
	u8 *Version1 = (u8 *) InstancePtr;
	u8 *Version2 = (u8 *) VersionPtr;
	int Index;

	/* assert to verify input arguments */

	XASSERT_NONVOID(InstancePtr != NULL);
	XASSERT_NONVOID(VersionPtr != NULL);

	/* check each byte of the versions to see if they are the same,
	 * return at any point a byte differs between them
	 */
	for (Index = 0; Index < sizeof (XVersion); Index++) {
		if (Version1[Index] != Version2[Index]) {
			return FALSE;
		}
	}

	/* No byte was found to be different between the versions, so indicate
	 * the versions are equal
	 */
	return TRUE;
}

void
XVersion_ToString(XVersion * InstancePtr, s8 * StringPtr)
{
	/* assert to verify input arguments */

	XASSERT_VOID(InstancePtr != NULL);
	XASSERT_VOID(StringPtr != NULL);

	/* since version is implemented as a string, just copy the specified
	 * input into the specified output
	 */
	XVersion_Copy(InstancePtr, (XVersion *) StringPtr);
}

XStatus
XVersion_FromString(XVersion * InstancePtr, s8 * StringPtr)
{
	/* assert to verify input arguments */

	XASSERT_NONVOID(InstancePtr != NULL);
	XASSERT_NONVOID(StringPtr != NULL);

	/* if the version string specified is not valid, return an error */

	if (!IsVersionStringValid(StringPtr)) {
		return XST_INVALID_VERSION;
	}

	/* copy the specified string into the specified version and indicate the
	 * conversion was successful
	 */
	XVersion_Copy((XVersion *) StringPtr, InstancePtr);

	return XST_SUCCESS;
}

void
XVersion_Copy(XVersion * InstancePtr, XVersion * VersionPtr)
{
	u8 *Source = (u8 *) InstancePtr;
	u8 *Destination = (u8 *) VersionPtr;
	int Index;

	/* assert to verify input arguments */

	XASSERT_VOID(InstancePtr != NULL);
	XASSERT_VOID(VersionPtr != NULL);

	/* copy each byte of the source version to the destination version */

	for (Index = 0; Index < sizeof (XVersion); Index++) {
		Destination[Index] = Source[Index];
	}
}

static u32
IsVersionStringValid(s8 * StringPtr)
{
	/* if the input string is not a valid format, "X.YYZ" where X = 0 - 9,
	 * YY = 00 - 99, and Z = a - z, then indicate it's not valid
	 */
	if ((StringPtr[XVE_MAJOR_CHAR] < '0') ||
	    (StringPtr[XVE_MAJOR_CHAR] > '9') ||
	    (StringPtr[XVE_MINOR_TENS_CHAR] < '0') ||
	    (StringPtr[XVE_MINOR_TENS_CHAR] > '9') ||
	    (StringPtr[XVE_MINOR_ONES_CHAR] < '0') ||
	    (StringPtr[XVE_MINOR_ONES_CHAR] > '9') ||
	    (StringPtr[XVE_COMP_CHAR] < 'a') ||
	    (StringPtr[XVE_COMP_CHAR] > 'z')) {
		return FALSE;
	}

	return TRUE;
}
