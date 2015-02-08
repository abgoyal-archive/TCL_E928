

#include <common.h>


#include <post.h>
#include "cpu_asm.h"

#if CONFIG_POST & CONFIG_SYS_POST_CPU

extern void cpu_post_exec_02 (ulong *code, ulong op1, ulong op2);

int cpu_post_test_multi (void)
{
    int ret = 0;
    unsigned int i;
    int flag = disable_interrupts();

    if (ret == 0)
    {
	ulong src [26], dst [26];

	ulong code[] =
	{
	    ASM_LMW(5, 3, 0),
	    ASM_STMW(5, 4, 0),
	    ASM_BLR,
	};

	for (i = 0; i < sizeof(src) / sizeof(src[0]); i ++)
	{
	    src[i] = i;
	    dst[i] = 0;
	}

	cpu_post_exec_02(code, (ulong)src, (ulong)dst);

	ret = memcmp(src, dst, sizeof(dst)) == 0 ? 0 : -1;
    }

    if (ret != 0)
    {
	post_log ("Error at multi test !\n");
    }

    if (flag)
	enable_interrupts();

    return ret;
}

#endif
