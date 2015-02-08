

#ifndef _ASM_NIOS_BITOPS_H_
#define _ASM_NIOS_BITOPS_H_


extern void set_bit(int nr, volatile void * a);
extern void clear_bit(int nr, volatile void * a);
extern int test_and_clear_bit(int nr, volatile void * a);
extern void change_bit(unsigned long nr, volatile void *addr);
extern int test_and_set_bit(int nr, volatile void * a);
extern int test_and_change_bit(int nr, volatile void * addr);
extern int test_bit(int nr, volatile void * a);
extern int ffs(int i);
#define PLATFORM_FFS

#endif /* _ASM_NIOS_BITOPS_H */
