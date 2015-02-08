

#include <common.h>


/* #ifdef CONFIG_POST */

#include <post.h>
#include <watchdog.h>

/* #if CONFIG_POST & CONFIG_SYS_POST_MEMORY */

#undef  INJECT_DATA_ERRORS
#undef  INJECT_ADDRESS_ERRORS

#ifdef INJECT_DATA_ERRORS
#warning "Injecting data line errors for testing purposes"
#endif

#ifdef INJECT_ADDRESS_ERRORS
#warning "Injecting address line errors for testing purposes"
#endif


static void move64(const unsigned long long *src, unsigned long long *dest)
{
#if defined(CONFIG_MPC8260) || defined(CONFIG_MPC824X)
	asm ("lfd  0, 0(3)\n\t" /* fpr0	  =  *scr	*/
	 "stfd 0, 0(4)"		/* *dest  =  fpr0	*/
	 : : : "fr0" );		/* Clobbers fr0		*/
    return;
#else
	*dest = *src;
#endif
}

const static unsigned long long pattern[] = {
	0xaaaaaaaaaaaaaaaaULL,
	0xccccccccccccccccULL,
	0xf0f0f0f0f0f0f0f0ULL,
	0xff00ff00ff00ff00ULL,
	0xffff0000ffff0000ULL,
	0xffffffff00000000ULL,
	0x00000000ffffffffULL,
	0x0000ffff0000ffffULL,
	0x00ff00ff00ff00ffULL,
	0x0f0f0f0f0f0f0f0fULL,
	0x3333333333333333ULL,
	0x5555555555555555ULL,
};
const unsigned long long otherpattern = 0x0123456789abcdefULL;


static int memory_post_dataline(unsigned long long * pmem)
{
	unsigned long long temp64;
	int num_patterns = sizeof(pattern)/ sizeof(pattern[0]);
	int i;
	unsigned int hi, lo, pathi, patlo;
	int ret = 0;

	for ( i = 0; i < num_patterns; i++) {
		move64(&(pattern[i]), pmem++);
		/*
		 * Put a different pattern on the data lines: otherwise they
		 * may float long enough to read back what we wrote.
		 */
		move64(&otherpattern, pmem--);
		move64(pmem, &temp64);

#ifdef INJECT_DATA_ERRORS
		temp64 ^= 0x00008000;
#endif

		if (temp64 != pattern[i]){
			pathi = (pattern[i]>>32) & 0xffffffff;
			patlo = pattern[i] & 0xffffffff;

			hi = (temp64>>32) & 0xffffffff;
			lo = temp64 & 0xffffffff;

			printf ("Memory (date line) error at %08lx, "
				  "wrote %08x%08x, read %08x%08x !\n",
					  (ulong)pmem, pathi, patlo, hi, lo);
			ret = -1;
		}
	}
	return ret;
}

static int memory_post_addrline(ulong *testaddr, ulong *base, ulong size)
{
	ulong *target;
	ulong *end;
	ulong readback;
	ulong xor;
	int   ret = 0;

	end = (ulong *)((ulong)base + size);	/* pointer arith! */
	xor = 0;
	for(xor = sizeof(ulong); xor > 0; xor <<= 1) {
		target = (ulong *)((ulong)testaddr ^ xor);
		if((target >= base) && (target < end)) {
			*testaddr = ~*target;
			readback  = *target;

#ifdef INJECT_ADDRESS_ERRORS
			if(xor == 0x00008000) {
				readback = *testaddr;
			}
#endif
			if(readback == *testaddr) {
				printf ("Memory (address line) error at %08lx<->%08lx, "
					"XOR value %08lx !\n",
					(ulong)testaddr, (ulong)target,
					xor);
				ret = -1;
			}
		}
	}
	return ret;
}

static int memory_post_test1 (unsigned long start,
			      unsigned long size,
			      unsigned long val)
{
	unsigned long i;
	ulong *mem = (ulong *) start;
	ulong readback;
	int ret = 0;

	for (i = 0; i < size / sizeof (ulong); i++) {
		mem[i] = val;
		if (i % 1024 == 0)
			WATCHDOG_RESET ();
	}

	for (i = 0; i < size / sizeof (ulong) && ret == 0; i++) {
		readback = mem[i];
		if (readback != val) {
			printf ("Memory error at %08lx, "
				  "wrote %08lx, read %08lx !\n",
					  (ulong)(mem + i), val, readback);

			ret = -1;
			break;
		}
		if (i % 1024 == 0)
			WATCHDOG_RESET ();
	}

	return ret;
}

static int memory_post_test2 (unsigned long start, unsigned long size)
{
	unsigned long i;
	ulong *mem = (ulong *) start;
	ulong readback;
	int ret = 0;

	for (i = 0; i < size / sizeof (ulong); i++) {
		mem[i] = 1 << (i % 32);
		if (i % 1024 == 0)
			WATCHDOG_RESET ();
	}

	for (i = 0; i < size / sizeof (ulong) && ret == 0; i++) {
		readback = mem[i];
		if (readback != (1 << (i % 32))) {
			printf ("Memory error at %08lx, "
				  "wrote %08x, read %08lx !\n",
					  (ulong)(mem + i), 1 << (i % 32), readback);

			ret = -1;
			break;
		}
		if (i % 1024 == 0)
			WATCHDOG_RESET ();
	}

	return ret;
}

static int memory_post_test3 (unsigned long start, unsigned long size)
{
	unsigned long i;
	ulong *mem = (ulong *) start;
	ulong readback;
	int ret = 0;

	for (i = 0; i < size / sizeof (ulong); i++) {
		mem[i] = i;
		if (i % 1024 == 0)
			WATCHDOG_RESET ();
	}

	for (i = 0; i < size / sizeof (ulong) && ret == 0; i++) {
		readback = mem[i];
		if (readback != i) {
			printf ("Memory error at %08lx, "
				  "wrote %08lx, read %08lx !\n",
					  (ulong)(mem + i), i, readback);

			ret = -1;
			break;
		}
		if (i % 1024 == 0)
			WATCHDOG_RESET ();
	}

	return ret;
}

static int memory_post_test4 (unsigned long start, unsigned long size)
{
	unsigned long i;
	ulong *mem = (ulong *) start;
	ulong readback;
	int ret = 0;

	for (i = 0; i < size / sizeof (ulong); i++) {
		mem[i] = ~i;
		if (i % 1024 == 0)
			WATCHDOG_RESET ();
	}

	for (i = 0; i < size / sizeof (ulong) && ret == 0; i++) {
		readback = mem[i];
		if (readback != ~i) {
			printf ("Memory error at %08lx, "
				  "wrote %08lx, read %08lx !\n",
					  (ulong)(mem + i), ~i, readback);

			ret = -1;
			break;
		}
		if (i % 1024 == 0)
			WATCHDOG_RESET ();
	}

	return ret;
}

int memory_post_tests (unsigned long start, unsigned long size)
{
	int ret = 0;

	if (ret == 0)
		ret = memory_post_dataline ((unsigned long long *)start);
	WATCHDOG_RESET ();
	if (ret == 0)
		ret = memory_post_addrline ((ulong *)start, (ulong *)start, size);
	WATCHDOG_RESET ();
	if (ret == 0)
		ret = memory_post_addrline ((ulong *)(start + size - 8),
					    (ulong *)start, size);
	WATCHDOG_RESET ();
	if (ret == 0)
		ret = memory_post_test1 (start, size, 0x00000000);
	WATCHDOG_RESET ();
	if (ret == 0)
		ret = memory_post_test1 (start, size, 0xffffffff);
	WATCHDOG_RESET ();
	if (ret == 0)
		ret = memory_post_test1 (start, size, 0x55555555);
	WATCHDOG_RESET ();
	if (ret == 0)
		ret = memory_post_test1 (start, size, 0xaaaaaaaa);
	WATCHDOG_RESET ();
	if (ret == 0)
		ret = memory_post_test2 (start, size);
	WATCHDOG_RESET ();
	if (ret == 0)
		ret = memory_post_test3 (start, size);
	WATCHDOG_RESET ();
	if (ret == 0)
		ret = memory_post_test4 (start, size);
	WATCHDOG_RESET ();

	return ret;
}

#if 0
DECLARE_GLOBAL_DATA_PTR;

int memory_post_test (int flags)
{
	int ret = 0;
	bd_t *bd = gd->bd;
	phys_size_t memsize = (bd->bi_memsize >= 256 << 20 ?
				 256 << 20 : bd->bi_memsize) - (1 << 20);


	if (flags & POST_SLOWTEST) {
		ret = memory_post_tests (CONFIG_SYS_SDRAM_BASE, memsize);
	} else {			/* POST_NORMAL */

		unsigned long i;

		for (i = 0; i < (memsize >> 20) && ret == 0; i++) {
			if (ret == 0)
				ret = memory_post_tests (i << 20, 0x800);
			if (ret == 0)
				ret = memory_post_tests ((i << 20) + 0xff800, 0x800);
		}
	}

	return ret;
}
#endif /* 0 */

/* #endif */ /* CONFIG_POST & CONFIG_SYS_POST_MEMORY */
/* #endif */ /* CONFIG_POST */
