

#include <common.h>
#include <asm/arch/hardware.h>
#include <asm/io.h>


/* Works on Always On power domain only (no PD argument) */
void lpsc_on(unsigned int id)
{
	dv_reg_p mdstat, mdctl, ptstat, ptcmd;
#ifdef CONFIG_SOC_DA8XX
	struct davinci_psc_regs *psc_regs;
#endif

#ifndef CONFIG_SOC_DA8XX
	if (id >= DAVINCI_LPSC_GEM)
		return;			/* Don't work on DSP Power Domain */

	mdstat = REG_P(PSC_MDSTAT_BASE + (id * 4));
	mdctl = REG_P(PSC_MDCTL_BASE + (id * 4));
	ptstat = REG_P(PSC_PTSTAT);
	ptcmd = REG_P(PSC_PTCMD);
#else
	if (id < DAVINCI_LPSC_PSC1_BASE) {
		if (id >= PSC_PSC0_MODULE_ID_CNT)
			return;
		psc_regs = davinci_psc0_regs;
		mdstat = &psc_regs->psc0.mdstat[id];
		mdctl = &psc_regs->psc0.mdctl[id];
	} else {
		id -= DAVINCI_LPSC_PSC1_BASE;
		if (id >= PSC_PSC1_MODULE_ID_CNT)
			return;
		psc_regs = davinci_psc1_regs;
		mdstat = &psc_regs->psc1.mdstat[id];
		mdctl = &psc_regs->psc1.mdctl[id];
	}
	ptstat = &psc_regs->ptstat;
	ptcmd = &psc_regs->ptcmd;
#endif

	while (readl(ptstat) & 0x01)
		continue;

	if ((readl(mdstat) & 0x1f) == 0x03)
		return; /* Already on and enabled */

	writel(readl(mdctl) | 0x03, mdctl);

	switch (id) {
#ifdef CONFIG_SOC_DM644X
	/* Special treatment for some modules as for sprue14 p.7.4.2 */
	case DAVINCI_LPSC_VPSSSLV:
	case DAVINCI_LPSC_EMAC:
	case DAVINCI_LPSC_EMAC_WRAPPER:
	case DAVINCI_LPSC_MDIO:
	case DAVINCI_LPSC_USB:
	case DAVINCI_LPSC_ATA:
	case DAVINCI_LPSC_VLYNQ:
	case DAVINCI_LPSC_UHPI:
	case DAVINCI_LPSC_DDR_EMIF:
	case DAVINCI_LPSC_AEMIF:
	case DAVINCI_LPSC_MMC_SD:
	case DAVINCI_LPSC_MEMSTICK:
	case DAVINCI_LPSC_McBSP:
	case DAVINCI_LPSC_GPIO:
		writel(readl(mdctl) | 0x200, mdctl);
		break;
#endif
	}

	writel(0x01, ptcmd);

	while (readl(ptstat) & 0x01)
		continue;
	while ((readl(mdstat) & 0x1f) != 0x03)
		continue;
}

/* Not all DaVinci chips have a DSP power domain. */
#ifdef CONFIG_SOC_DM644X

/* If DSPLINK is used, we don't want U-Boot to power on the DSP. */
#if !defined(CONFIG_SYS_USE_DSPLINK)
void dsp_on(void)
{
	int i;

	if (REG(PSC_PDSTAT1) & 0x1f)
		return;			/* Already on */

	REG(PSC_GBLCTL) |= 0x01;
	REG(PSC_PDCTL1) |= 0x01;
	REG(PSC_PDCTL1) &= ~0x100;
	REG(PSC_MDCTL_BASE + (DAVINCI_LPSC_GEM * 4)) |= 0x03;
	REG(PSC_MDCTL_BASE + (DAVINCI_LPSC_GEM * 4)) &= 0xfffffeff;
	REG(PSC_MDCTL_BASE + (DAVINCI_LPSC_IMCOP * 4)) |= 0x03;
	REG(PSC_MDCTL_BASE + (DAVINCI_LPSC_IMCOP * 4)) &= 0xfffffeff;
	REG(PSC_PTCMD) = 0x02;

	for (i = 0; i < 100; i++) {
		if (REG(PSC_EPCPR) & 0x02)
			break;
	}

	REG(PSC_CHP_SHRTSW) = 0x01;
	REG(PSC_PDCTL1) |= 0x100;
	REG(PSC_EPCCR) = 0x02;

	for (i = 0; i < 100; i++) {
		if (!(REG(PSC_PTSTAT) & 0x02))
			break;
	}

	REG(PSC_GBLCTL) &= ~0x1f;
}
#endif /* CONFIG_SYS_USE_DSPLINK */

#endif /* have a DSP */
