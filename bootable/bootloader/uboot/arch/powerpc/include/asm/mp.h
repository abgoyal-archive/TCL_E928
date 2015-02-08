

#ifndef _ASM_MP_H_
#define _ASM_MP_H_

#include <lmb.h>

void setup_mp(void);
void cpu_mp_lmb_reserve(struct lmb *lmb);
u32 determine_mp_bootpg(void);

#endif
