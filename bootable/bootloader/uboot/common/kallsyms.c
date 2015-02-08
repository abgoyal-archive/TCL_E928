

#include <common.h>

/* We need the weak marking as this symbol is provided specially */
extern const char system_map[] __attribute__((weak));

const char *symbol_lookup(unsigned long addr, unsigned long *caddr)
{
	const char *sym, *csym;
	char *esym;
	unsigned long sym_addr;

	sym = system_map;
	csym = NULL;
	*caddr = 0;

	while (*sym) {
		sym_addr = simple_strtoul(sym, &esym, 16);
		sym = esym;
		if (sym_addr > addr)
			break;
		*caddr = sym_addr;
		csym = sym;
		sym += strlen(sym) + 1;
	}

	return csym;
}
