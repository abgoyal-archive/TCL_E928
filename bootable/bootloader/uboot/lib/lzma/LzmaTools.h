

#ifndef __LZMA_TOOL_H__
#define __LZMA_TOOL_H__

#include <lzma/LzmaTypes.h>

extern int lzmaBuffToBuffDecompress (unsigned char *outStream, SizeT *uncompressedSize,
			      unsigned char *inStream,  SizeT  length);
#endif
