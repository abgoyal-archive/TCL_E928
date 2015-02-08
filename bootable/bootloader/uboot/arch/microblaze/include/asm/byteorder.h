

#ifndef __MICROBLAZE_BYTEORDER_H__
#define __MICROBLAZE_BYTEORDER_H__

#include <asm/types.h>

#ifdef __GNUC__



static __inline__ __u16 ___arch__swab16 (__u16 half_word)
{
	/* 32 bit temp to cast result, forcing clearing of high word */
	__u32 temp;

	temp = ((half_word & 0x00FFU) << 8) | ((half_word & 0xFF00U) >> 8);

	return (__u16) temp;
}

#define __arch__swab16(x) ___arch__swab16(x)

/* Microblaze has no arch-specific endian conversion insns */

#if !defined(__STRICT_ANSI__) || defined(__KERNEL__)
#  define __BYTEORDER_HAS_U64__
#  define __SWAB_64_THRU_32__
#endif

#endif /* __GNUC__ */

#include <linux/byteorder/big_endian.h>

#endif /* __MICROBLAZE_BYTEORDER_H__ */
