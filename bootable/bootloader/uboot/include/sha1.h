
#ifndef _SHA1_H
#define _SHA1_H

#ifdef __cplusplus
extern "C" {
#endif

#define SHA1_SUM_POS	-0x20
#define SHA1_SUM_LEN	20

typedef struct
{
    unsigned long total[2];	/*!< number of bytes processed	*/
    unsigned long state[5];	/*!< intermediate digest state	*/
    unsigned char buffer[64];	/*!< data block being processed */
}
sha1_context;

void sha1_starts( sha1_context *ctx );

void sha1_update( sha1_context *ctx, unsigned char *input, int ilen );

void sha1_finish( sha1_context *ctx, unsigned char output[20] );

void sha1_csum( unsigned char *input, int ilen,
		unsigned char output[20] );

void sha1_csum_wd (unsigned char *input, int ilen,
		unsigned char output[20], unsigned int chunk_sz);

int sha1_file( char *path, unsigned char output[20] );

void sha1_hmac( unsigned char *key, int keylen,
		unsigned char *input, int ilen,
		unsigned char output[20] );

int sha1_self_test( void );

#ifdef __cplusplus
}
#endif

#endif /* sha1.h */
