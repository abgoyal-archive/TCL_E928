

#include <config.h>
#include <common.h>
#include <asm/io.h>
#include <asm/errno.h>

int vsc7385_upload_firmware(void *firmware, unsigned int size)
{
	u8 *fw = firmware;
	unsigned int i;

	u32 *gloreset = (u32 *) (CONFIG_SYS_VSC7385_BASE + 0x1c050);
	u32 *icpu_ctrl = (u32 *) (CONFIG_SYS_VSC7385_BASE + 0x1c040);
	u32 *icpu_addr = (u32 *) (CONFIG_SYS_VSC7385_BASE + 0x1c044);
	u32 *icpu_data = (u32 *) (CONFIG_SYS_VSC7385_BASE + 0x1c048);
	u32 *icpu_rom_map = (u32 *) (CONFIG_SYS_VSC7385_BASE + 0x1c070);
#ifdef DEBUG
	u32 *chipid = (u32 *) (CONFIG_SYS_VSC7385_BASE + 0x1c060);
#endif

	out_be32(gloreset, 3);
	udelay(200);

	out_be32(icpu_ctrl, 0x8E);
	udelay(20);

	out_be32(icpu_rom_map, 1);
	udelay(20);

	/* Write the firmware to I-RAM */
	out_be32(icpu_addr, 0);
	udelay(20);

	for (i = 0; i < size; i++) {
		out_be32(icpu_data, fw[i]);
		udelay(20);
		if (ctrlc())
			return -EINTR;
	}

	/* Read back and compare */
	out_be32(icpu_addr, 0);
	udelay(20);

	for (i = 0; i < size; i++) {
		u8 value;

		value = (u8) in_be32(icpu_data);
		udelay(20);
		if (value != fw[i]) {
			debug("VSC7385: Upload mismatch: address 0x%x, "
			      "read value 0x%x, image value 0x%x\n",
			      i, value, fw[i]);

			return -EIO;
		}
		if (ctrlc())
			break;
	}

	out_be32(icpu_ctrl, 0x0B);
	udelay(20);

#ifdef DEBUG
	printf("VSC7385: Chip ID is %08x\n", in_be32(chipid));
	udelay(20);
#endif

	return 0;
}
