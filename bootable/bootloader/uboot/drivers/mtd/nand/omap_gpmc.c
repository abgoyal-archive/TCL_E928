

#include <common.h>
#include <asm/io.h>
#include <asm/errno.h>
#include <asm/arch/mem.h>
#include <asm/arch/omap_gpmc.h>
#include <linux/mtd/nand_ecc.h>
#include <nand.h>

static uint8_t cs;
static struct nand_ecclayout hw_nand_oob = GPMC_NAND_HW_ECC_LAYOUT;

static void omap_nand_hwcontrol(struct mtd_info *mtd, int32_t cmd,
				uint32_t ctrl)
{
	register struct nand_chip *this = mtd->priv;

	/*
	 * Point the IO_ADDR to DATA and ADDRESS registers instead
	 * of chip address
	 */
	switch (ctrl) {
	case NAND_CTRL_CHANGE | NAND_CTRL_CLE:
		this->IO_ADDR_W = (void __iomem *)&gpmc_cfg->cs[cs].nand_cmd;
		break;
	case NAND_CTRL_CHANGE | NAND_CTRL_ALE:
		this->IO_ADDR_W = (void __iomem *)&gpmc_cfg->cs[cs].nand_adr;
		break;
	case NAND_CTRL_CHANGE | NAND_NCE:
		this->IO_ADDR_W = (void __iomem *)&gpmc_cfg->cs[cs].nand_dat;
		break;
	}

	if (cmd != NAND_CMD_NONE)
		writeb(cmd, this->IO_ADDR_W);
}

static void omap_hwecc_init(struct nand_chip *chip)
{
	/*
	 * Init ECC Control Register
	 * Clear all ECC | Enable Reg1
	 */
	writel(ECCCLEAR | ECCRESULTREG1, &gpmc_cfg->ecc_control);
	writel(ECCSIZE1 | ECCSIZE0 | ECCSIZE0SEL, &gpmc_cfg->ecc_size_config);
}

static uint32_t gen_true_ecc(uint8_t *ecc_buf)
{
	return ecc_buf[0] | (ecc_buf[1] << 16) | ((ecc_buf[2] & 0xF0) << 20) |
		((ecc_buf[2] & 0x0F) << 8);
}

static int omap_correct_data(struct mtd_info *mtd, uint8_t *dat,
				uint8_t *read_ecc, uint8_t *calc_ecc)
{
	uint32_t orig_ecc, new_ecc, res, hm;
	uint16_t parity_bits, byte;
	uint8_t bit;

	/* Regenerate the orginal ECC */
	orig_ecc = gen_true_ecc(read_ecc);
	new_ecc = gen_true_ecc(calc_ecc);
	/* Get the XOR of real ecc */
	res = orig_ecc ^ new_ecc;
	if (res) {
		/* Get the hamming width */
		hm = hweight32(res);
		/* Single bit errors can be corrected! */
		if (hm == 12) {
			/* Correctable data! */
			parity_bits = res >> 16;
			bit = (parity_bits & 0x7);
			byte = (parity_bits >> 3) & 0x1FF;
			/* Flip the bit to correct */
			dat[byte] ^= (0x1 << bit);
		} else if (hm == 1) {
			printf("Error: Ecc is wrong\n");
			/* ECC itself is corrupted */
			return 2;
		} else {
			/*
			 * hm distance != parity pairs OR one, could mean 2 bit
			 * error OR potentially be on a blank page..
			 * orig_ecc: contains spare area data from nand flash.
			 * new_ecc: generated ecc while reading data area.
			 * Note: if the ecc = 0, all data bits from which it was
			 * generated are 0xFF.
			 * The 3 byte(24 bits) ecc is generated per 512byte
			 * chunk of a page. If orig_ecc(from spare area)
			 * is 0xFF && new_ecc(computed now from data area)=0x0,
			 * this means that data area is 0xFF and spare area is
			 * 0xFF. A sure sign of a erased page!
			 */
			if ((orig_ecc == 0x0FFF0FFF) && (new_ecc == 0x00000000))
				return 0;
			printf("Error: Bad compare! failed\n");
			/* detected 2 bit error */
			return -1;
		}
	}
	return 0;
}

static int omap_calculate_ecc(struct mtd_info *mtd, const uint8_t *dat,
				uint8_t *ecc_code)
{
	u_int32_t val;

	/* Start Reading from HW ECC1_Result = 0x200 */
	val = readl(&gpmc_cfg->ecc1_result);

	ecc_code[0] = val & 0xFF;
	ecc_code[1] = (val >> 16) & 0xFF;
	ecc_code[2] = ((val >> 8) & 0x0F) | ((val >> 20) & 0xF0);

	/*
	 * Stop reading anymore ECC vals and clear old results
	 * enable will be called if more reads are required
	 */
	writel(0x000, &gpmc_cfg->ecc_config);

	return 0;
}

static void omap_enable_hwecc(struct mtd_info *mtd, int32_t mode)
{
	struct nand_chip *chip = mtd->priv;
	uint32_t val, dev_width = (chip->options & NAND_BUSWIDTH_16) >> 1;

	switch (mode) {
	case NAND_ECC_READ:
	case NAND_ECC_WRITE:
		/* Clear the ecc result registers, select ecc reg as 1 */
		writel(ECCCLEAR | ECCRESULTREG1, &gpmc_cfg->ecc_control);

		/*
		 * Size 0 = 0xFF, Size1 is 0xFF - both are 512 bytes
		 * tell all regs to generate size0 sized regs
		 * we just have a single ECC engine for all CS
		 */
		writel(ECCSIZE1 | ECCSIZE0 | ECCSIZE0SEL,
			&gpmc_cfg->ecc_size_config);
		val = (dev_width << 7) | (cs << 1) | (0x1);
		writel(val, &gpmc_cfg->ecc_config);
		break;
	default:
		printf("Error: Unrecognized Mode[%d]!\n", mode);
		break;
	}
}

void omap_nand_switch_ecc(int32_t hardware)
{
	struct nand_chip *nand;
	struct mtd_info *mtd;

	if (nand_curr_device < 0 ||
	    nand_curr_device >= CONFIG_SYS_MAX_NAND_DEVICE ||
	    !nand_info[nand_curr_device].name) {
		printf("Error: Can't switch ecc, no devices available\n");
		return;
	}

	mtd = &nand_info[nand_curr_device];
	nand = mtd->priv;

	nand->options |= NAND_OWN_BUFFERS;

	/* Reset ecc interface */
	nand->ecc.read_page = NULL;
	nand->ecc.write_page = NULL;
	nand->ecc.read_oob = NULL;
	nand->ecc.write_oob = NULL;
	nand->ecc.hwctl = NULL;
	nand->ecc.correct = NULL;
	nand->ecc.calculate = NULL;

	/* Setup the ecc configurations again */
	if (hardware) {
		nand->ecc.mode = NAND_ECC_HW;
		nand->ecc.layout = &hw_nand_oob;
		nand->ecc.size = 512;
		nand->ecc.bytes = 3;
		nand->ecc.hwctl = omap_enable_hwecc;
		nand->ecc.correct = omap_correct_data;
		nand->ecc.calculate = omap_calculate_ecc;
		omap_hwecc_init(nand);
		printf("HW ECC selected\n");
	} else {
		nand->ecc.mode = NAND_ECC_SOFT;
		/* Use mtd default settings */
		nand->ecc.layout = NULL;
		printf("SW ECC selected\n");
	}

	/* Update NAND handling after ECC mode switch */
	nand_scan_tail(mtd);

	nand->options &= ~NAND_OWN_BUFFERS;
}

int board_nand_init(struct nand_chip *nand)
{
	int32_t gpmc_config = 0;
	cs = 0;

	/*
	 * xloader/Uboot's gpmc configuration would have configured GPMC for
	 * nand type of memory. The following logic scans and latches on to the
	 * first CS with NAND type memory.
	 * TBD: need to make this logic generic to handle multiple CS NAND
	 * devices.
	 */
	while (cs < GPMC_MAX_CS) {
		/* Check if NAND type is set */
		if ((readl(&gpmc_cfg->cs[cs].config1) & 0xC00) == 0x800) {
			/* Found it!! */
			break;
		}
		cs++;
	}
	if (cs >= GPMC_MAX_CS) {
		printf("NAND: Unable to find NAND settings in "
			"GPMC Configuration - quitting\n");
		return -ENODEV;
	}

	gpmc_config = readl(&gpmc_cfg->config);
	/* Disable Write protect */
	gpmc_config |= 0x10;
	writel(gpmc_config, &gpmc_cfg->config);

	nand->IO_ADDR_R = (void __iomem *)&gpmc_cfg->cs[cs].nand_dat;
	nand->IO_ADDR_W = (void __iomem *)&gpmc_cfg->cs[cs].nand_cmd;

	nand->cmd_ctrl = omap_nand_hwcontrol;
	nand->options = NAND_NO_PADDING | NAND_CACHEPRG | NAND_NO_AUTOINCR;
	/* If we are 16 bit dev, our gpmc config tells us that */
	if ((readl(&gpmc_cfg->cs[cs].config1) & 0x3000) == 0x1000)
		nand->options |= NAND_BUSWIDTH_16;

	nand->chip_delay = 100;
	/* Default ECC mode */
	nand->ecc.mode = NAND_ECC_SOFT;

	return 0;
}
