

#include <common.h>
#include <asm/io.h>
#include <asm/ptrace.h>
#include <asm/realmode.h>


#define REALMODE_BASE    ((char*)0x7c0)
#define REALMODE_MAILBOX ((char*)0xe00)


extern ulong _i386boot_realmode;
extern ulong _i386boot_realmode_size;
extern char realmode_enter;

int realmode_setup(void)
{
	ulong i386boot_realmode      = (ulong)&_i386boot_realmode + gd->reloc_off;
	ulong i386boot_realmode_size = (ulong)&_i386boot_realmode_size;

	/* copy the realmode switch code */
	if (i386boot_realmode_size > (REALMODE_MAILBOX-REALMODE_BASE)) {
		printf("realmode switch too large (%ld bytes, max is %d)\n",
		       i386boot_realmode_size, (REALMODE_MAILBOX-REALMODE_BASE));
		return -1;
	}

	memcpy(REALMODE_BASE, (void*)i386boot_realmode, i386boot_realmode_size);
	asm("wbinvd\n");

	return 0;
}

int enter_realmode(u16 seg, u16 off, struct pt_regs *in, struct pt_regs *out)
{

	/* setup out thin bios emulation */
	if (bios_setup()) {
		return -1;
	}

	if (realmode_setup()) {
		return -1;
	}

	in->eip = off;
	in->xcs = seg;
	if (3>(in->esp & 0xffff)) {
		printf("Warning: entering realmode with sp < 4 will fail\n");
	}

	memcpy(REALMODE_MAILBOX, in, sizeof(struct pt_regs));
	asm("wbinvd\n");

	__asm__ volatile (
		 "lcall $0x20,%0\n"  : :  "i" (&realmode_enter) );

	asm("wbinvd\n");
	memcpy(out, REALMODE_MAILBOX, sizeof(struct pt_regs));

	return out->eax;
}


int enter_realmode_int(u8 lvl, struct pt_regs *in, struct pt_regs *out)
{
	/* place two instructions at 0x700 */
	writeb(0xcd, 0x700);  /* int $lvl */
	writeb(lvl, 0x701);
	writeb(0xcb, 0x702);  /* lret */
	asm("wbinvd\n");

	enter_realmode(0x00, 0x700, in, out);

	return out->eflags&1;
}
