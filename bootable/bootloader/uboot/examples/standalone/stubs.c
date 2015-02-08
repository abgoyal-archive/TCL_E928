
#include <exports.h>

#ifndef GCC_VERSION
#define GCC_VERSION (__GNUC__ * 1000 + __GNUC_MINOR__)
#endif /* GCC_VERSION */

#if defined(CONFIG_I386)
static void **jt;
gd_t *global_data;

#define EXPORT_FUNC(x) \
	asm volatile (			\
"	.globl " #x "\n"		\
#x ":\n"				\
"	movl	%0, %%eax\n"		\
"	movl	jt, %%ecx\n"		\
"	jmp	*(%%ecx, %%eax)\n"	\
	: : "i"(XF_ ## x * sizeof(void *)) : "eax", "ecx");
#elif defined(CONFIG_PPC)
#define EXPORT_FUNC(x) \
	asm volatile (			\
"	.globl " #x "\n"		\
#x ":\n"				\
"	lwz	%%r11, %0(%%r2)\n"	\
"	lwz	%%r11, %1(%%r11)\n"	\
"	mtctr	%%r11\n"		\
"	bctr\n"				\
	: : "i"(offsetof(gd_t, jt)), "i"(XF_ ## x * sizeof(void *)) : "r11");
#elif defined(CONFIG_ARM)
#define EXPORT_FUNC(x) \
	asm volatile (			\
"	.globl " #x "\n"		\
#x ":\n"				\
"	ldr	ip, [r8, %0]\n"		\
"	ldr	pc, [ip, %1]\n"		\
	: : "i"(offsetof(gd_t, jt)), "i"(XF_ ## x * sizeof(void *)) : "ip");
#elif defined(CONFIG_MIPS)
#define EXPORT_FUNC(x) \
	asm volatile (			\
"	.globl " #x "\n"		\
#x ":\n"				\
"	lw	$25, %0($26)\n"		\
"	lw	$25, %1($25)\n"		\
"	jr	$25\n"			\
	: : "i"(offsetof(gd_t, jt)), "i"(XF_ ## x * sizeof(void *)) : "t9");
#elif defined(CONFIG_NIOS)
#define EXPORT_FUNC(x) \
	asm volatile (			\
"	.globl " #x "\n"		\
#x ":\n"				\
"	pfx	%%hi(%0)\n"		\
"	movi	%%g0, %%lo(%0)\n"	\
"	add	%%g0, %%g7\n"		\
"	ld	%%g0, [%%g0]\n"		\
"	pfx	%1\n"			\
"	ld	%%g0, [%%g0]\n"		\
"	jmp	%%g0\n"			\
"	nop	\n"			\
	: : "i"(offsetof(gd_t, jt)), "i"(XF_ ## x) : "r0");
#elif defined(CONFIG_NIOS2)
#define EXPORT_FUNC(x) \
	asm volatile (			\
"	.globl " #x "\n"		\
#x ":\n"				\
"	movhi	r8, %%hi(%0)\n"		\
"	ori	r8, r0, %%lo(%0)\n"	\
"	add	r8, r8, r15\n"		\
"	ldw	r8, 0(r8)\n"		\
"	ldw	r8, %1(r8)\n"		\
"	jmp	r8\n"			\
	: : "i"(offsetof(gd_t, jt)), "i"(XF_ ## x * sizeof(void *)) : "r15");
#elif defined(CONFIG_M68K)
#define EXPORT_FUNC(x) \
	asm volatile (			\
"	.globl " #x "\n"		\
#x ":\n"				\
"	move.l	%%d7, %%a0\n"		\
"	adda.l	%0, %%a0\n"		\
"	move.l	(%%a0), %%a0\n"		\
"	adda.l	%1, %%a0\n"		\
"	move.l	(%%a0), %%a0\n"		\
"	jmp	(%%a0)\n"			\
	: : "i"(offsetof(gd_t, jt)), "i"(XF_ ## x * sizeof(void *)) : "a0");
#elif defined(CONFIG_MICROBLAZE)
#define EXPORT_FUNC(x)				\
	asm volatile (				\
"	.globl " #x "\n"			\
#x ":\n"					\
"	lwi	r5, r31, %0\n"			\
"	lwi	r5, r5, %1\n"			\
"	bra	r5\n"				\
	: : "i"(offsetof(gd_t, jt)), "i"(XF_ ## x * sizeof(void *)) : "r5");
#elif defined(CONFIG_BLACKFIN)
#define EXPORT_FUNC(x)			\
	asm volatile (			\
"	.globl _" #x "\n_"		\
#x ":\n"				\
"	P0 = [P3 + %0]\n"		\
"	P0 = [P0 + %1]\n"		\
"	JUMP (P0)\n"			\
	: : "i"(offsetof(gd_t, jt)), "i"(XF_ ## x * sizeof(void *)) : "P0");
#elif defined(CONFIG_AVR32)
#define EXPORT_FUNC(x)					\
	asm volatile(					\
		"	.globl\t" #x "\n"		\
		#x ":\n"				\
		"	ld.w	r8, r6[%0]\n"		\
		"	ld.w	pc, r8[%1]\n"		\
		:					\
		: "i"(offsetof(gd_t, jt)), "i"(XF_ ##x)	\
		: "r8");
#elif defined(CONFIG_SH)
#define EXPORT_FUNC(x)					\
	asm volatile (					\
		"	.align	2\n"			\
		"	.globl " #x "\n"		\
		#x ":\n"				\
		"	mov	r13, r1\n"		\
		"	add	%0, r1\n"		\
		"	mov.l @r1, r2\n"	\
		"	add	%1, r2\n"		\
		"	mov.l @r2, r1\n"	\
		"	jmp	@r1\n"			\
		"	nop\n"				\
		"	nop\n"				\
		: : "i"(offsetof(gd_t, jt)), "i"(XF_ ## x * sizeof(void *)) : "r1", "r2");
#elif defined(CONFIG_SPARC)
#define EXPORT_FUNC(x)					\
	asm volatile(					\
"	.globl\t" #x "\n"				\
#x ":\n"						\
"	set %0, %%g1\n"					\
"	or %%g1, %%g7, %%g1\n"				\
"	ld [%%g1], %%g1\n"				\
"	ld [%%g1 + %1], %%g1\n"				\
"	jmp %%g1\n"					\
"	nop\n"						\
	: : "i"(offsetof(gd_t, jt)), "i"(XF_ ## x * sizeof(void *)) : "g1" );

#else
#error stubs definition missing for this architecture
#endif

#if GCC_VERSION < 3004
static
#endif /* GCC_VERSION */
void __attribute__((unused)) dummy(void)
{
#include <_exports.h>
}

extern unsigned long __bss_start, _end;

void app_startup(char **argv)
{
	unsigned char * cp = (unsigned char *) &__bss_start;

	/* Zero out BSS */
	while (cp < (unsigned char *)&_end) {
		*cp++ = 0;
	}

#if defined(CONFIG_I386)
	/* x86 does not have a dedicated register for passing global_data */
	global_data = (gd_t *)argv[-1];
	jt = global_data->jt;
#endif
}

#undef EXPORT_FUNC
