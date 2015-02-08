
#include <common.h>


DECLARE_GLOBAL_DATA_PTR;

struct exception_table_entry
{
	unsigned long insn, fixup;
};

extern const struct exception_table_entry __start___ex_table[];
extern const struct exception_table_entry __stop___ex_table[];

static inline unsigned long
search_one_table(const struct exception_table_entry *first,
		 const struct exception_table_entry *last,
		 unsigned long value)
{
	long diff;
	while (first <= last) {
		diff = first->insn - value;
		if (diff == 0)
			return first->fixup;
		first++;
	}

	return 0;
}

int	ex_tab_message = 1;

unsigned long
search_exception_table(unsigned long addr)
{
	unsigned long ret;

	/* There is only the kernel to search.  */
	ret = search_one_table(__start___ex_table, __stop___ex_table-1, addr);
	/* if the serial port does not hang in exception, printf can be used */
#if !defined(CONFIG_SYS_SERIAL_HANG_IN_EXCEPTION)
	if (ex_tab_message)
		debug("Bus Fault @ 0x%08lx, fixup 0x%08lx\n", addr, ret);
#endif
	if (ret) return ret;

	return 0;
}
