
#ifndef _ASM_SYSTEM_H
#define _ASM_SYSTEM_H

#include <linux/config.h>
#include <asm/sgidefs.h>
#include <asm/ptrace.h>
#if 0
#include <linux/kernel.h>
#endif

extern __inline__ void
__sti(void)
{
	__asm__ __volatile__(
		".set\tpush\n\t"
		".set\treorder\n\t"
		".set\tnoat\n\t"
		"mfc0\t$1,$12\n\t"
		"ori\t$1,0x1f\n\t"
		"xori\t$1,0x1e\n\t"
		"mtc0\t$1,$12\n\t"
		".set\tpop\n\t"
		: /* no outputs */
		: /* no inputs */
		: "$1", "memory");
}

extern __inline__ void
__cli(void)
{
	__asm__ __volatile__(
		".set\tpush\n\t"
		".set\treorder\n\t"
		".set\tnoat\n\t"
		"mfc0\t$1,$12\n\t"
		"ori\t$1,1\n\t"
		"xori\t$1,1\n\t"
		".set\tnoreorder\n\t"
		"mtc0\t$1,$12\n\t"
		"nop\n\t"
		"nop\n\t"
		"nop\n\t"
		".set\tpop\n\t"
		: /* no outputs */
		: /* no inputs */
		: "$1", "memory");
}

#define __save_flags(x)							\
__asm__ __volatile__(							\
	".set\tpush\n\t"						\
	".set\treorder\n\t"						\
	"mfc0\t%0,$12\n\t"						\
	".set\tpop\n\t"							\
	: "=r" (x))

#define __save_and_cli(x)						\
__asm__ __volatile__(							\
	".set\tpush\n\t"						\
	".set\treorder\n\t"						\
	".set\tnoat\n\t"						\
	"mfc0\t%0,$12\n\t"						\
	"ori\t$1,%0,1\n\t"						\
	"xori\t$1,1\n\t"						\
	".set\tnoreorder\n\t"						\
	"mtc0\t$1,$12\n\t"						\
	"nop\n\t"							\
	"nop\n\t"							\
	"nop\n\t"							\
	".set\tpop\n\t"							\
	: "=r" (x)							\
	: /* no inputs */						\
	: "$1", "memory")

#define __restore_flags(flags)						\
do {									\
	unsigned long __tmp1;						\
									\
	__asm__ __volatile__(						\
		".set\tnoreorder\t\t\t# __restore_flags\n\t"		\
		".set\tnoat\n\t"					\
		"mfc0\t$1, $12\n\t"					\
		"andi\t%0, 1\n\t"					\
		"ori\t$1, 1\n\t"					\
		"xori\t$1, 1\n\t"					\
		"or\t%0, $1\n\t"					\
		"mtc0\t%0, $12\n\t"					\
		"nop\n\t"						\
		"nop\n\t"						\
		"nop\n\t"						\
		".set\tat\n\t"						\
		".set\treorder"						\
		: "=r" (__tmp1)						\
		: "0" (flags)						\
		: "$1", "memory");					\
} while(0)

#ifdef CONFIG_SMP

extern void __global_sti(void);
extern void __global_cli(void);
extern unsigned long __global_save_flags(void);
extern void __global_restore_flags(unsigned long);
#  define sti() __global_sti()
#  define cli() __global_cli()
#  define save_flags(x) do { x = __global_save_flags(); } while (0)
#  define restore_flags(x) __global_restore_flags(x)
#  define save_and_cli(x) do { save_flags(x); cli(); } while(0)

#else /* Single processor */

#  define sti() __sti()
#  define cli() __cli()
#  define save_flags(x) __save_flags(x)
#  define save_and_cli(x) __save_and_cli(x)
#  define restore_flags(x) __restore_flags(x)

#endif /* SMP */

/* For spinlocks etc */
#define local_irq_save(x)	__save_and_cli(x);
#define local_irq_restore(x)	__restore_flags(x);
#define local_irq_disable()	__cli();
#define local_irq_enable()	__sti();

#ifdef CONFIG_CPU_HAS_WB

#include <asm/wbflush.h>
#define rmb()	do { } while(0)
#define wmb()	wbflush()
#define mb()	wbflush()

#else /* CONFIG_CPU_HAS_WB  */

#define mb()						\
__asm__ __volatile__(					\
	"# prevent instructions being moved around\n\t"	\
	".set\tnoreorder\n\t"				\
	"# 8 nops to fool the R4400 pipeline\n\t"	\
	"nop;nop;nop;nop;nop;nop;nop;nop\n\t"		\
	".set\treorder"					\
	: /* no output */				\
	: /* no input */				\
	: "memory")
#define rmb() mb()
#define wmb() mb()

#endif /* CONFIG_CPU_HAS_WB  */

#ifdef CONFIG_SMP
#define smp_mb()	mb()
#define smp_rmb()	rmb()
#define smp_wmb()	wmb()
#else
#define smp_mb()	barrier()
#define smp_rmb()	barrier()
#define smp_wmb()	barrier()
#endif

#define set_mb(var, value) \
do { var = value; mb(); } while (0)

#define set_wmb(var, value) \
do { var = value; wmb(); } while (0)

#if !defined (_LANGUAGE_ASSEMBLY)
#if 0
extern asmlinkage void *resume(void *last, void *next);
#endif
#endif /* !defined (_LANGUAGE_ASSEMBLY) */

#define prepare_to_switch()	do { } while(0)
#define switch_to(prev,next,last) \
do { \
	(last) = resume(prev, next); \
} while(0)

extern __inline__ unsigned long xchg_u32(volatile int * m, unsigned long val)
{
#ifdef CONFIG_CPU_HAS_LLSC
	unsigned long dummy;

	__asm__ __volatile__(
		".set\tnoreorder\t\t\t# xchg_u32\n\t"
		".set\tnoat\n\t"
		"ll\t%0, %3\n"
		"1:\tmove\t$1, %2\n\t"
		"sc\t$1, %1\n\t"
		"beqzl\t$1, 1b\n\t"
		" ll\t%0, %3\n\t"
		".set\tat\n\t"
		".set\treorder"
		: "=r" (val), "=o" (*m), "=r" (dummy)
		: "o" (*m), "2" (val)
		: "memory");

	return val;
#else
	unsigned long flags, retval;

	save_flags(flags);
	cli();
	retval = *m;
	*m = val;
	restore_flags(flags);
	return retval;
#endif /* Processor-dependent optimization */
}

#define xchg(ptr,x) ((__typeof__(*(ptr)))__xchg((unsigned long)(x),(ptr),sizeof(*(ptr))))
#define tas(ptr) (xchg((ptr),1))

static __inline__ unsigned long
__xchg(unsigned long x, volatile void * ptr, int size)
{
	switch (size) {
		case 4:
			return xchg_u32(ptr, x);
	}
	return x;
}

extern void *set_except_vector(int n, void *addr);

extern void __die(const char *, struct pt_regs *, const char *where,
	unsigned long line) __attribute__((noreturn));
extern void __die_if_kernel(const char *, struct pt_regs *, const char *where,
	unsigned long line);

#define die(msg, regs)							\
	__die(msg, regs, __FILE__ ":"__FUNCTION__, __LINE__)
#define die_if_kernel(msg, regs)					\
	__die_if_kernel(msg, regs, __FILE__ ":"__FUNCTION__, __LINE__)

#endif /* _ASM_SYSTEM_H */
