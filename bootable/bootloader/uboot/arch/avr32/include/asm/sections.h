
#ifndef __ASM_AVR32_SECTIONS_H
#define __ASM_AVR32_SECTIONS_H

/* References to section boundaries */

extern char _text[], _etext[];
extern char _data[], __data_lma[], _edata[], __edata_lma[];
extern char __got_start[], __got_lma[], __got_end[];
extern char _end[];

#endif /* __ASM_AVR32_SECTIONS_H */
