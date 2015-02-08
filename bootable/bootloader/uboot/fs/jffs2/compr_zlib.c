

#include <common.h>
#include <config.h>
#include <jffs2/jffs2.h>
#include <jffs2/mini_inflate.h>

long zlib_decompress(unsigned char *data_in, unsigned char *cpage_out,
		      __u32 srclen, __u32 destlen)
{
    return (decompress_block(cpage_out, data_in + 2, (void *) ldr_memcpy));

}
