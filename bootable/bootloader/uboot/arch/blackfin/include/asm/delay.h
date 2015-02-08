

#ifndef _BLACKFIN_DELAY_H
#define _BLACKFIN_DELAY_H


extern __inline__ void __delay(unsigned long loops)
{
	__asm__ __volatile__("1:\t%0 += -1;\n\t"
			     "cc = %0 == 0;\n\t"
			     "if ! cc jump 1b;\n":"=d"(loops)
			     :"0"(loops));
}

extern __inline__ void __udelay(unsigned long usecs)
{
	__delay(usecs);
}

#endif
