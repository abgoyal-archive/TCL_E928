

#ifndef _MD5_H
#define _MD5_H

#include "compiler.h"

struct MD5Context {
	__u32 buf[4];
	__u32 bits[2];
	unsigned char in[64];
};

void md5 (unsigned char *input, int len, unsigned char output[16]);

void md5_wd (unsigned char *input, int len, unsigned char output[16],
		unsigned int chunk_sz);

#endif /* _MD5_H */
