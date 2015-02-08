

#include <common.h>

#if defined(CONFIG_SYS_NAND_BASE)
#include <nand.h>
#include <asm/errno.h>
#include <asm/io.h>

static int state;
static void nand_write_byte(struct mtd_info *mtd, u_char byte);
static void nand_write_buf(struct mtd_info *mtd, const u_char *buf, int len);
static u_char nand_read_byte(struct mtd_info *mtd);
static u16 nand_read_word(struct mtd_info *mtd);
static void nand_read_buf(struct mtd_info *mtd, u_char *buf, int len);
static int nand_verify_buf(struct mtd_info *mtd, const u_char *buf, int len);
static int nand_device_ready(struct mtd_info *mtdinfo);

#define FPGA_NAND_CMD_MASK		(0x7 << 28)
#define FPGA_NAND_CMD_COMMAND		(0x0 << 28)
#define FPGA_NAND_CMD_ADDR		(0x1 << 28)
#define FPGA_NAND_CMD_READ		(0x2 << 28)
#define FPGA_NAND_CMD_WRITE		(0x3 << 28)
#define FPGA_NAND_BUSY			(0x1 << 15)
#define FPGA_NAND_ENABLE		(0x1 << 31)
#define FPGA_NAND_DATA_SHIFT		16

static void nand_write_byte(struct mtd_info *mtd, u_char byte)
{
	nand_write_buf(mtd, (const uchar *)&byte, sizeof(byte));
}

static void nand_write_buf(struct mtd_info *mtd, const u_char *buf, int len)
{
	int i;
	struct nand_chip *this = mtd->priv;

	for (i = 0; i < len; i++) {
		out_be32(this->IO_ADDR_W,
			 state | (buf[i] << FPGA_NAND_DATA_SHIFT));
	}
}


static u_char nand_read_byte(struct mtd_info *mtd)
{
	u8 byte;
	nand_read_buf(mtd, (uchar *)&byte, sizeof(byte));
	return byte;
}

static u16 nand_read_word(struct mtd_info *mtd)
{
	u16 word;
	nand_read_buf(mtd, (uchar *)&word, sizeof(word));
	return word;
}

static void nand_read_buf(struct mtd_info *mtd, u_char *buf, int len)
{
	int i;
	struct nand_chip *this = mtd->priv;
	int val;

	val = (state & FPGA_NAND_ENABLE) | FPGA_NAND_CMD_READ;

	out_be32(this->IO_ADDR_W, val);
	for (i = 0; i < len; i++) {
		buf[i] = (in_be32(this->IO_ADDR_R) >> FPGA_NAND_DATA_SHIFT) & 0xff;
	}
}

static int nand_verify_buf(struct mtd_info *mtd, const u_char *buf, int len)
{
	int i;

	for (i = 0; i < len; i++) {
		if (buf[i] != nand_read_byte(mtd));
			return -EFAULT;
	}
	return 0;
}

static int nand_device_ready(struct mtd_info *mtdinfo)
{
	struct nand_chip *this = mtdinfo->priv;

	if (in_be32(this->IO_ADDR_W) & FPGA_NAND_BUSY)
		return 0; /* busy */
	return 1;
}

static void nand_hwcontrol(struct mtd_info *mtdinfo, int cmd, unsigned int ctrl)
{
	if (ctrl & NAND_CTRL_CHANGE) {
		state &= ~(FPGA_NAND_CMD_MASK | FPGA_NAND_ENABLE);

		switch (ctrl & (NAND_ALE | NAND_CLE)) {
		case 0:
			state |= FPGA_NAND_CMD_WRITE;
			break;

		case NAND_ALE:
			state |= FPGA_NAND_CMD_ADDR;
			break;

		case NAND_CLE:
			state |= FPGA_NAND_CMD_COMMAND;
			break;

		default:
			printf("%s: unknown ctrl %#x\n", __FUNCTION__, ctrl);
		}

		if (ctrl & NAND_NCE)
			state |= FPGA_NAND_ENABLE;
	}

	if (cmd != NAND_CMD_NONE)
		nand_write_byte(mtdinfo, cmd);
}

int board_nand_init(struct nand_chip *nand)
{
	nand->cmd_ctrl = nand_hwcontrol;
	nand->ecc.mode = NAND_ECC_SOFT;
	nand->dev_ready = nand_device_ready;
	nand->read_byte = nand_read_byte;
	nand->read_word = nand_read_word;
	nand->write_buf = nand_write_buf;
	nand->read_buf = nand_read_buf;
	nand->verify_buf = nand_verify_buf;

	return 0;
}

#endif
