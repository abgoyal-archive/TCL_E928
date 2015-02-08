

#include <common.h>
#include <config.h>
#include <mpc8xx.h>

/* ------------------------------------------------------------------------- */

#define	_NOT_USED_	0xFFFFFFFF

const uint edo_60ns[] =
{ 0x8ffbec24, 0x0ff3ec04, 0x0cf3ec04, 0x00f3ec04,
  0x00f3ec00, 0x37f7ec47, _NOT_USED_, _NOT_USED_,
  0x8fffec24, 0x0ffbec04, 0x08f3ec04, 0x07f3ec08,
  0x08f3ec04, 0x07f3ec48, 0x08f3ec04, 0x07f3ec48,
  0x08f3ec04, 0x07f3ec48, 0x1ff7ec47, _NOT_USED_,
  _NOT_USED_, _NOT_USED_, _NOT_USED_, _NOT_USED_,
  0x8fffcc24, 0x0fefcc04, 0x0cafcc00, 0x11bfcc47,
  _NOT_USED_, _NOT_USED_, _NOT_USED_, _NOT_USED_,
  0x8fffcc24, 0x0fefcc04, 0x0cafcc00, 0x03afcc4c,
  0x0cafcc00, 0x03afcc4c, 0x0cafcc00, 0x03afcc4c,
  0x0cafcc00, 0x33bfcc4f, _NOT_USED_, _NOT_USED_,
  _NOT_USED_, _NOT_USED_, _NOT_USED_, _NOT_USED_,
  0xc0ffcc84, 0x00ffcc04, 0x07ffcc04, 0x3fffcc06,
  0xffffcc85, 0xffffcc05, _NOT_USED_, _NOT_USED_,
  _NOT_USED_, _NOT_USED_, _NOT_USED_, _NOT_USED_,
  0x33ffcc07, _NOT_USED_, _NOT_USED_, _NOT_USED_ };

/* ------------------------------------------------------------------------- */


int checkboard (void)
{
	puts ("Board: AMX860\n");
	return 0;
}

/* ------------------------------------------------------------------------- */

phys_size_t initdram (int board_type)
{

	volatile immap_t     *immap = (immap_t *)CONFIG_SYS_IMMR;
	volatile memctl8xx_t *memctl = &immap->im_memctl;

	/* AMX860: has 4 Mb of 60ns EDO DRAM, so start DRAM at 0 */

	upmconfig(UPMA, (uint *) edo_60ns, sizeof(edo_60ns)/sizeof(uint));

#ifndef CONFIG_AMX_RAM_EXT
	memctl->memc_mptpr = 0x0400; /* divide by 16 */
#else
	memctl->memc_mptpr = 0x0200;
#endif

	memctl->memc_mamr = 0x30a21114;
	memctl->memc_or2 = 0xffc00800;
#ifndef CONFIG_AMX_RAM_EXT
	memctl->memc_br2 = 0x81;

	return (4 << 20);
#else
	memctl->memc_or1 = 0xff000800;
	memctl->memc_br1 = 0x00000081;
	memctl->memc_br2 = 0x01000081;

	return (20 << 20);
#endif
}
