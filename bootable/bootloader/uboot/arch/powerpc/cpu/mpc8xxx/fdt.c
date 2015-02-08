

#include <common.h>
#include <libfdt.h>
#include <fdt_support.h>

void ft_fixup_num_cores(void *blob) {
	int off, num_cores, del_cores;

	del_cores = 0;
	num_cores = cpu_numcores();

	off = fdt_node_offset_by_prop_value(blob, -1, "device_type", "cpu", 4);
	while (off != -FDT_ERR_NOTFOUND) {
		u32 *reg = (u32 *)fdt_getprop(blob, off, "reg", 0);

		/* if we find a cpu node outside of what we expect delete it
		 * and reset the offset back to the start since we can't
		 * trust the offsets anymore
		 */
		if (*reg > num_cores-1) {
			fdt_del_node(blob, off);
			del_cores++;
			off = -1;
		}
		off = fdt_node_offset_by_prop_value(blob, off,
				"device_type", "cpu", 4);
	}
	debug ("%x core system found\n", num_cores);
	debug ("deleted %d extra core entry entries from device tree\n",
								del_cores);
}
