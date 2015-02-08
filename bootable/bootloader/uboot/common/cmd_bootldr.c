

#include <config.h>
#include <common.h>
#include <command.h>

#include <asm/blackfin.h>
#include <asm/mach-common/bits/bootrom.h>

static bool ldr_valid_signature(uint8_t *data)
{
#if defined(__ADSPBF561__)

	/* BF56x has a 4 byte global header */
	if (data[3] == 0xA0)
		return true;

#elif defined(__ADSPBF531__) || defined(__ADSPBF532__) || defined(__ADSPBF533__) || \
      defined(__ADSPBF534__) || defined(__ADSPBF536__) || defined(__ADSPBF537__) || \
      defined(__ADSPBF538__) || defined(__ADSPBF539__)

	/* all the BF53x should start at this address mask */
	uint32_t addr;
	memmove(&addr, data, sizeof(addr));
	if ((addr & 0xFF0FFF0F) == 0xFF000000)
		return true;
#else

	/* everything newer has a magic byte */
	uint32_t count;
	memmove(&count, data + 8, sizeof(count));
	if (data[3] == 0xAD && count == 0)
		return true;

#endif

	return false;
}

#define ZEROFILL  0x0001
#define RESVECT   0x0002
#define INIT      0x0008
#define IGNORE    0x0010
#define FINAL     0x8000
static void ldr_load(uint8_t *base_addr)
{
#if defined(__ADSPBF531__) || defined(__ADSPBF532__) || defined(__ADSPBF533__) || \
  /*defined(__ADSPBF534__) || defined(__ADSPBF536__) || defined(__ADSPBF537__) ||*/\
    defined(__ADSPBF538__) || defined(__ADSPBF539__) || defined(__ADSPBF561__)

	uint32_t addr;
	uint32_t count;
	uint16_t flags;

	/* the bf56x has a 4 byte global header ... but it is useless to
	 * us when booting an LDR from a memory address, so skip it
	 */
# ifdef __ADSPBF561__
	base_addr += 4;
# endif

	memmove(&flags, base_addr + 8, sizeof(flags));
	bfin_write_EVT1(flags & RESVECT ? 0xFFA00000 : 0xFFA08000);

	do {
		/* block header may not be aligned */
		memmove(&addr, base_addr, sizeof(addr));
		memmove(&count, base_addr+4, sizeof(count));
		memmove(&flags, base_addr+8, sizeof(flags));
		base_addr += sizeof(addr) + sizeof(count) + sizeof(flags);

		printf("loading to 0x%08x (0x%x bytes) flags: 0x%04x\n",
			addr, count, flags);

		if (!(flags & IGNORE)) {
			if (flags & ZEROFILL)
				memset((void *)addr, 0x00, count);
			else
				memcpy((void *)addr, base_addr, count);

			if (flags & INIT) {
				void (*init)(void) = (void *)addr;
				init();
			}
		}

		if (!(flags & ZEROFILL))
			base_addr += count;
	} while (!(flags & FINAL));

#endif
}

static void ldr_exec(void *addr)
{
#if defined(__ADSPBF534__) || defined(__ADSPBF536__) || defined(__ADSPBF537__)

	/* restore EVT1 to reset value as this is what the bootrom uses as
	 * the default entry point when booting the final block of LDRs
	 */
	bfin_write_EVT1(L1_INST_SRAM);
	__asm__("call (%0);" : : "a"(_BOOTROM_MEMBOOT), "q7"(addr) : "RETS", "memory");

#elif defined(__ADSPBF531__) || defined(__ADSPBF532__) || defined(__ADSPBF533__) || \
      defined(__ADSPBF538__) || defined(__ADSPBF539__) || defined(__ADSPBF561__)

	void (*ldr_entry)(void) = (void *)bfin_read_EVT1();
	ldr_entry();

#else

	int32_t (*BOOTROM_MEM)(void *, int32_t, int32_t, void *) = (void *)_BOOTROM_MEMBOOT;
	BOOTROM_MEM(addr, 0, 0, NULL);

#endif
}

int do_bootldr(cmd_tbl_t *cmdtp, int flag, int argc, char *argv[])
{
	void *addr;

	/* Get the address */
	if (argc < 2)
		addr = (void *)load_addr;
	else
		addr = (void *)simple_strtoul(argv[1], NULL, 16);

	/* Check if it is a LDR file */
	if (ldr_valid_signature(addr)) {
		printf("## Booting ldr image at 0x%p ...\n", addr);
		ldr_load(addr);

		icache_disable();
		dcache_disable();

		ldr_exec(addr);
	} else
		printf("## No ldr image at address 0x%p\n", addr);

	return 0;
}

U_BOOT_CMD(bootldr, 2, 0, do_bootldr,
	"boot ldr image from memory",
	"[addr]\n"
	""
);
