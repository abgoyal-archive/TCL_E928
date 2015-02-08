

#include <common.h>
#include <asm/io.h>
#include <asm/arch/AT91RM9200.h>
#include <asm/arch/hardware.h>

#include <nand.h>


#define MASK_ALE        (1 << 22)       /* our ALE is A22 */
#define MASK_CLE        (1 << 21)       /* our CLE is A21 */

#define KB9202_NAND_NCE (1 << 28) /* EN* on D28 */
#define KB9202_NAND_BUSY (1 << 29) /* RB* on D29 */

#define KB9202_SMC2_NWS (1 << 2)
#define KB9202_SMC2_TDF (1 << 8)
#define KB9202_SMC2_RWSETUP (1 << 24)
#define KB9202_SMC2_RWHOLD (1 << 29)

static void kb9202_nand_hwcontrol(struct mtd_info *mtd, int cmd, unsigned int ctrl)
{
	struct nand_chip *this = mtd->priv;

	if (ctrl & NAND_CTRL_CHANGE) {
		ulong IO_ADDR_W = (ulong) this->IO_ADDR_W;

		/* clear ALE and CLE bits */
		IO_ADDR_W &= ~(MASK_ALE | MASK_CLE);

		if (ctrl & NAND_CLE)
			IO_ADDR_W |= MASK_CLE;

		if (ctrl & NAND_ALE)
			IO_ADDR_W |= MASK_ALE;

		this->IO_ADDR_W = (void *) IO_ADDR_W;

		if (ctrl & NAND_NCE)
			writel(KB9202_NAND_NCE, AT91C_PIOC_CODR);
		else
			writel(KB9202_NAND_NCE, AT91C_PIOC_SODR);
	}

	if (cmd != NAND_CMD_NONE)
		writeb(cmd, this->IO_ADDR_W);
}


static int kb9202_nand_ready(struct mtd_info *mtd)
{
	return readl(AT91C_PIOC_PDSR) & KB9202_NAND_BUSY;
}


int board_nand_init(struct nand_chip *nand)
{
	unsigned int value;

	nand->ecc.mode = NAND_ECC_SOFT;
	nand->cmd_ctrl = kb9202_nand_hwcontrol;
	nand->dev_ready = kb9202_nand_ready;

	/* in case running outside of bootloader */
	writel(1 << AT91C_ID_PIOC, AT91C_PMC_PCER);

	/* setup nand flash access (allow ample margin) */
	/* 4 wait states, 1 setup, 1 hold, 1 float for 8-bit device */
	writel(AT91C_SMC2_WSEN | KB9202_SMC2_NWS | KB9202_SMC2_TDF |
		AT91C_SMC2_DBW_8 | KB9202_SMC2_RWSETUP | KB9202_SMC2_RWHOLD,
		AT91C_SMC_CSR3);

	/* enable internal NAND controller */
	value = readl(AT91C_EBI_CSA);
	value |= AT91C_EBI_CS3A_SMC_SmartMedia;
	writel(value, AT91C_EBI_CSA);

	/* enable SMOE/SMWE */
	writel(AT91C_PC1_BFRDY_SMOE | AT91C_PC3_BFBAA_SMWE, AT91C_PIOC_ASR);
	writel(AT91C_PC1_BFRDY_SMOE | AT91C_PC3_BFBAA_SMWE, AT91C_PIOC_PDR);
	writel(AT91C_PC1_BFRDY_SMOE | AT91C_PC3_BFBAA_SMWE, AT91C_PIOC_OER);

	/* set NCE to high */
	writel(KB9202_NAND_NCE, AT91C_PIOC_SODR);

	/* disable output on pin connected to the busy line of the NAND */
	writel(KB9202_NAND_BUSY, AT91C_PIOC_ODR);

	/* enable the PIO to control NCE and BUSY */
	writel(KB9202_NAND_NCE | KB9202_NAND_BUSY, AT91C_PIOC_PER);

	/* enable output for NCE */
	writel(KB9202_NAND_NCE, AT91C_PIOC_OER);

	return (0);
}
