

#include <common.h>

int raise (int signum)
{
	printf("raise: Signal # %d caught\n", signum);
	return 0;
}

/* Dummy function to avoid linker complaints */
void __aeabi_unwind_cpp_pr0(void)
{
};
