
#ifndef __ASM_PROC_DOMAIN_H
#define __ASM_PROC_DOMAIN_H

#define DOMAIN_USER	0
#define DOMAIN_KERNEL	1
#define DOMAIN_TABLE	1
#define DOMAIN_IO	2

#define DOMAIN_NOACCESS	0
#define DOMAIN_CLIENT	1
#define DOMAIN_MANAGER	3

#define domain_val(dom,type)	((type) << 2*(dom))

#define set_domain(x)					\
	do {						\
	__asm__ __volatile__(				\
	"mcr	p15, 0, %0, c3, c0	@ set domain"	\
	  : : "r" (x));					\
	} while (0)

#define modify_domain(dom,type)				\
	do {						\
	unsigned int domain = current->thread.domain;	\
	domain &= ~domain_val(dom, DOMAIN_MANAGER);	\
	domain |= domain_val(dom, type);		\
	current->thread.domain = domain;		\
	set_domain(current->thread.domain);		\
	} while (0)

#endif
