


#include <common.h>
#include <74xx_7xx.h>

void
cpu_init_f (void)
{
	switch (get_cpu_type()) {
	case CPU_7450:
	case CPU_7455:
	case CPU_7457:
	case CPU_7447A:
	case CPU_7448:
		/* enable the timebase bit in HID0 */
		set_hid0(get_hid0() | 0x4000000);
		break;
	default:
		/* do nothing */
		break;
	}
}

int cpu_init_r (void)
{
	return (0);
}
