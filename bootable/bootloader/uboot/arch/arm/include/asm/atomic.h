
#ifndef __ASM_ARM_ATOMIC_H
#define __ASM_ARM_ATOMIC_H

#include <linux/config.h>

#ifdef CONFIG_SMP
#error SMP not supported
#endif

typedef struct { volatile int counter; } atomic_t;

#define ATOMIC_INIT(i)	{ (i) }

#ifdef __KERNEL__
#include <asm/proc/system.h>

#define atomic_read(v)	((v)->counter)
#define atomic_set(v,i)	(((v)->counter) = (i))

static inline void atomic_add(int i, volatile atomic_t *v)
{
	unsigned long flags;

	local_irq_save(flags);
	v->counter += i;
	local_irq_restore(flags);
}

static inline void atomic_sub(int i, volatile atomic_t *v)
{
	unsigned long flags;

	local_irq_save(flags);
	v->counter -= i;
	local_irq_restore(flags);
}

static inline void atomic_inc(volatile atomic_t *v)
{
	unsigned long flags;

	local_irq_save(flags);
	v->counter += 1;
	local_irq_restore(flags);
}

static inline void atomic_dec(volatile atomic_t *v)
{
	unsigned long flags;

	local_irq_save(flags);
	v->counter -= 1;
	local_irq_restore(flags);
}

static inline int atomic_dec_and_test(volatile atomic_t *v)
{
	unsigned long flags;
	int val;

	local_irq_save(flags);
	val = v->counter;
	v->counter = val -= 1;
	local_irq_restore(flags);

	return val == 0;
}

static inline int atomic_add_negative(int i, volatile atomic_t *v)
{
	unsigned long flags;
	int val;

	local_irq_save(flags);
	val = v->counter;
	v->counter = val += i;
	local_irq_restore(flags);

	return val < 0;
}

static inline void atomic_clear_mask(unsigned long mask, unsigned long *addr)
{
	unsigned long flags;

	local_irq_save(flags);
	*addr &= ~mask;
	local_irq_restore(flags);
}

/* Atomic operations are already serializing on ARM */
#define smp_mb__before_atomic_dec()	barrier()
#define smp_mb__after_atomic_dec()	barrier()
#define smp_mb__before_atomic_inc()	barrier()
#define smp_mb__after_atomic_inc()	barrier()

#endif
#endif
