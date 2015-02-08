


#include <config.h>
#include <common.h>
#include <mpc86xx.h>
#include <asm/mmu.h>
#include <asm/fsl_law.h>
#include <asm/mp.h>

void setup_bats(void);

DECLARE_GLOBAL_DATA_PTR;


void cpu_init_f(void)
{
	volatile immap_t    *immap = (immap_t *)CONFIG_SYS_IMMR;
	volatile ccsr_lbc_t *memctl = &immap->im_lbc;

	/* Pointer is writable since we allocated a register for it */
	gd = (gd_t *) (CONFIG_SYS_INIT_RAM_ADDR + CONFIG_SYS_GBL_DATA_OFFSET);

	/* Clear initial global data */
	memset ((void *) gd, 0, sizeof (gd_t));

#ifdef CONFIG_FSL_LAW
	init_laws();
#endif

	setup_bats();

	/* Map banks 0 and 1 to the FLASH banks 0 and 1 at preliminary
	 * addresses - these have to be modified later when FLASH size
	 * has been determined
	 */

#if defined(CONFIG_SYS_OR0_REMAP)
	memctl->or0 = CONFIG_SYS_OR0_REMAP;
#endif
#if defined(CONFIG_SYS_OR1_REMAP)
	memctl->or1 = CONFIG_SYS_OR1_REMAP;
#endif

	/* now restrict to preliminary range */
#if defined(CONFIG_SYS_BR0_PRELIM) && defined(CONFIG_SYS_OR0_PRELIM)
	memctl->br0 = CONFIG_SYS_BR0_PRELIM;
	memctl->or0 = CONFIG_SYS_OR0_PRELIM;
#endif

#if defined(CONFIG_SYS_BR1_PRELIM) && defined(CONFIG_SYS_OR1_PRELIM)
	memctl->or1 = CONFIG_SYS_OR1_PRELIM;
	memctl->br1 = CONFIG_SYS_BR1_PRELIM;
#endif

#if defined(CONFIG_SYS_BR2_PRELIM) && defined(CONFIG_SYS_OR2_PRELIM)
	memctl->or2 = CONFIG_SYS_OR2_PRELIM;
	memctl->br2 = CONFIG_SYS_BR2_PRELIM;
#endif

#if defined(CONFIG_SYS_BR3_PRELIM) && defined(CONFIG_SYS_OR3_PRELIM)
	memctl->or3 = CONFIG_SYS_OR3_PRELIM;
	memctl->br3 = CONFIG_SYS_BR3_PRELIM;
#endif

#if defined(CONFIG_SYS_BR4_PRELIM) && defined(CONFIG_SYS_OR4_PRELIM)
	memctl->or4 = CONFIG_SYS_OR4_PRELIM;
	memctl->br4 = CONFIG_SYS_BR4_PRELIM;
#endif

#if defined(CONFIG_SYS_BR5_PRELIM) && defined(CONFIG_SYS_OR5_PRELIM)
	memctl->or5 = CONFIG_SYS_OR5_PRELIM;
	memctl->br5 = CONFIG_SYS_BR5_PRELIM;
#endif

#if defined(CONFIG_SYS_BR6_PRELIM) && defined(CONFIG_SYS_OR6_PRELIM)
	memctl->or6 = CONFIG_SYS_OR6_PRELIM;
	memctl->br6 = CONFIG_SYS_BR6_PRELIM;
#endif

#if defined(CONFIG_SYS_BR7_PRELIM) && defined(CONFIG_SYS_OR7_PRELIM)
	memctl->or7 = CONFIG_SYS_OR7_PRELIM;
	memctl->br7 = CONFIG_SYS_BR7_PRELIM;
#endif
#if defined(CONFIG_FSL_DMA)
	dma_init();
#endif

	/* enable the timebase bit in HID0 */
	set_hid0(get_hid0() | 0x4000000);

	/* enable EMCP, SYNCBE | ABE bits in HID1 */
	set_hid1(get_hid1() | 0x80000C00);
}

int cpu_init_r(void)
{
#if defined(CONFIG_MP)
	setup_mp();
#endif
	return 0;
}

/* Set up BAT registers */
void setup_bats(void)
{
#if defined(CONFIG_SYS_DBAT0U) && defined(CONFIG_SYS_DBAT0L)
	write_bat(DBAT0, CONFIG_SYS_DBAT0U, CONFIG_SYS_DBAT0L);
#endif
#if defined(CONFIG_SYS_IBAT0U) && defined(CONFIG_SYS_IBAT0L)
	write_bat(IBAT0, CONFIG_SYS_IBAT0U, CONFIG_SYS_IBAT0L);
#endif
	write_bat(DBAT1, CONFIG_SYS_DBAT1U, CONFIG_SYS_DBAT1L);
	write_bat(IBAT1, CONFIG_SYS_IBAT1U, CONFIG_SYS_IBAT1L);
	write_bat(DBAT2, CONFIG_SYS_DBAT2U, CONFIG_SYS_DBAT2L);
	write_bat(IBAT2, CONFIG_SYS_IBAT2U, CONFIG_SYS_IBAT2L);
	write_bat(DBAT3, CONFIG_SYS_DBAT3U, CONFIG_SYS_DBAT3L);
	write_bat(IBAT3, CONFIG_SYS_IBAT3U, CONFIG_SYS_IBAT3L);
	write_bat(DBAT4, CONFIG_SYS_DBAT4U, CONFIG_SYS_DBAT4L);
	write_bat(IBAT4, CONFIG_SYS_IBAT4U, CONFIG_SYS_IBAT4L);
	write_bat(DBAT5, CONFIG_SYS_DBAT5U, CONFIG_SYS_DBAT5L);
	write_bat(IBAT5, CONFIG_SYS_IBAT5U, CONFIG_SYS_IBAT5L);
	write_bat(DBAT6, CONFIG_SYS_DBAT6U, CONFIG_SYS_DBAT6L);
	write_bat(IBAT6, CONFIG_SYS_IBAT6U, CONFIG_SYS_IBAT6L);
	write_bat(DBAT7, CONFIG_SYS_DBAT7U, CONFIG_SYS_DBAT7L);
	write_bat(IBAT7, CONFIG_SYS_IBAT7U, CONFIG_SYS_IBAT7L);

	return;
}

#ifdef CONFIG_ADDR_MAP
/* Initialize address mapping array */
void init_addr_map(void)
{
	int i;
	ppc_bat_t bat = DBAT0;
	phys_size_t size;
	unsigned long upper, lower;

	for (i = 0; i < CONFIG_SYS_NUM_ADDR_MAP; i++, bat++) {
		if (read_bat(bat, &upper, &lower) != -1) {
			if (!BATU_VALID(upper))
				size = 0;
			else
				size = BATU_SIZE(upper);
			addrmap_set_entry(BATU_VADDR(upper), BATL_PADDR(lower),
					  size, i);
		}
#ifdef CONFIG_HIGH_BATS
		/* High bats are not contiguous with low BAT numbers */
		if (bat == DBAT3)
			bat = DBAT4 - 1;
#endif
	}
}
#endif
