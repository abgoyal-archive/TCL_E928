

#include <common.h>
#include <asm/io.h>
#include <asm/processor.h>

DECLARE_GLOBAL_DATA_PTR;

void cpu_init_f (volatile immap_t * im)
{
	u32 ips_div;

	/* Pointer is writable since we allocated a register for it */
	gd = (gd_t *) (CONFIG_SYS_INIT_RAM_ADDR + CONFIG_SYS_GBL_DATA_OFFSET);

	/* Clear initial global data */
	memset ((void *) gd, 0, sizeof (gd_t));

	/* system performance tweaking */

#ifdef CONFIG_SYS_ACR_PIPE_DEP
	/* Arbiter pipeline depth */
	out_be32(&im->arbiter.acr,
		(im->arbiter.acr & ~ACR_PIPE_DEP) |
		(CONFIG_SYS_ACR_PIPE_DEP << ACR_PIPE_DEP_SHIFT)
	);
#endif

#ifdef CONFIG_SYS_ACR_RPTCNT
	/* Arbiter repeat count */
	out_be32(im->arbiter.acr,
		(im->arbiter.acr & ~(ACR_RPTCNT)) |
		(CONFIG_SYS_ACR_RPTCNT << ACR_RPTCNT_SHIFT)
	);
#endif

	/* RSR - Reset Status Register - clear all status */
	gd->reset_status = im->reset.rsr;
	out_be32(&im->reset.rsr, ~RSR_RES);

	/*
	 * RMR - Reset Mode Register - enable checkstop reset
	 */
	out_be32(&im->reset.rmr, RMR_CSRE & (1 << RMR_CSRE_SHIFT));

	/* Set IPS-CSB divider: IPS = 1/2 CSB */
	ips_div = in_be32(&im->clk.scfr[0]);
	ips_div &= ~(SCFR1_IPS_DIV_MASK);
	ips_div |= SCFR1_IPS_DIV << SCFR1_IPS_DIV_SHIFT;
	out_be32(&im->clk.scfr[0], ips_div);

	/*
	 * Enable Time Base/Decrementer
	 *
	 * NOTICE: TB needs to be enabled as early as possible in order to
	 * have udelay() working; if not enabled, usually leads to a hang, like
	 * during FLASH chip identification etc.
	 */
	setbits_be32(&im->sysconf.spcr, SPCR_TBEN);
}

int cpu_init_r (void)
{
	return 0;
}
