


#include <common.h>
#include <command.h>
#include <asm/interrupt.h>

int cpu_init_f(void)
{
	/* initialize FPU, reset EM, set MP and NE */
	asm ("fninit\n" \
	     "movl %cr0, %eax\n" \
	     "andl $~0x4, %eax\n" \
	     "orl  $0x22, %eax\n" \
	     "movl %eax, %cr0\n" );

	return 0;
}

int cpu_init_r(void)
{
	/* Initialize core interrupt and exception functionality of CPU */
	cpu_init_interrupts ();
	return 0;
}

int do_reset(cmd_tbl_t *cmdtp, int flag, int argc, char *argv[])
{
	printf ("resetting ...\n");
	udelay(50000);				/* wait 50 ms */
	disable_interrupts();
	reset_cpu(0);

	/*NOTREACHED*/
	return 0;
}

void  flush_cache (unsigned long dummy1, unsigned long dummy2)
{
	asm("wbinvd\n");
	return;
}

void __attribute__ ((regparm(0))) generate_gpf(void);

/* segment 0x70 is an arbitrary segment which does not exist */
asm(".globl generate_gpf\n"
    ".hidden generate_gpf\n"
    ".type generate_gpf, @function\n"
    "generate_gpf:\n"
    "ljmp   $0x70, $0x47114711\n");

void __reset_cpu(ulong addr)
{
	printf("Resetting using i386 Triple Fault\n");
	set_vector(13, generate_gpf);  /* general protection fault handler */
	set_vector(8, generate_gpf);   /* double fault handler */
	generate_gpf();                /* start the show */
}
void reset_cpu(ulong addr) __attribute__((weak, alias("__reset_cpu")));
