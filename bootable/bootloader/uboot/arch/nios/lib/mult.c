


#include <common.h>

#if !defined(CONFIG_SYS_NIOS_MULT_HW) && !defined(CONFIG_SYS_NIOS_MULT_MSTEP)

#include "math.h"

USItype __mulsi3 (USItype a, USItype b)
{
	USItype c = 0;

	while (a != 0) {
		if (a & 1)
			c += b;
		a >>= 1;
		b <<= 1;
	}

	return c;
}


UHItype __mulhi3 (UHItype a, UHItype b)
{
	UHItype c = 0;

	while (a != 0) {
		if (a & 1)
			c += b;
		a >>= 1;
		b <<= 1;
	}

	return c;
}

#endif /*!defined(CONFIG_SYS_NIOS_MULT_HW) && !defined(CONFIG_SYS_NIOS_MULT_MSTEP) */
