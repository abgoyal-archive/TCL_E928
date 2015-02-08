

#include <config.h>
#include <jffs2/jffs2.h>

void rtime_decompress(unsigned char *data_in, unsigned char *cpage_out,
		      u32 srclen, u32 destlen)
{
	int positions[256];
	int outpos;
	int pos;
	int i;

	outpos = pos = 0;

	for (i = 0; i < 256; positions[i++] = 0);

	while (outpos<destlen) {
		unsigned char value;
		int backoffs;
		int repeat;

		value = data_in[pos++];
		cpage_out[outpos++] = value; /* first the verbatim copied byte */
		repeat = data_in[pos++];
		backoffs = positions[value];

		positions[value]=outpos;
		if (repeat) {
			if (backoffs + repeat >= outpos) {
				while(repeat) {
					cpage_out[outpos++] = cpage_out[backoffs++];
					repeat--;
				}
			} else {
				for (i = 0; i < repeat; i++)
					*(cpage_out + outpos + i) = *(cpage_out + backoffs + i);
				outpos+=repeat;
			}
		}
	}
}
