

#ifndef __MICROBLAZE_STRING_H__
#define __MICROBLAZE_STRING_H__

#if 0
#define __HAVE_ARCH_BCOPY
#define __HAVE_ARCH_MEMCPY
#define __HAVE_ARCH_MEMSET
#define __HAVE_ARCH_MEMMOVE

extern void *memcpy (void *, const void *, __kernel_size_t);
extern void bcopy (const char *, char *, int);
extern void *memset (void *, int, __kernel_size_t);
extern void *memmove (void *, const void *, __kernel_size_t);
#endif

#endif /* __MICROBLAZE_STRING_H__ */
