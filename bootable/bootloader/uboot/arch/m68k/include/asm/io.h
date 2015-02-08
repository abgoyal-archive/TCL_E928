

#ifndef __ASM_M68K_IO_H__
#define __ASM_M68K_IO_H__

#include <asm/byteorder.h>

#ifndef _IO_BASE
#define _IO_BASE 0
#endif

#define __raw_readb(addr) (*(volatile u8 *)(addr))
#define __raw_readw(addr) (*(volatile u16 *)(addr))
#define __raw_readl(addr) (*(volatile u32 *)(addr))

#define __raw_writeb(b,addr) ((*(volatile u8 *) (addr)) = (b))
#define __raw_writew(w,addr) ((*(volatile u16 *) (addr)) = (w))
#define __raw_writel(l,addr) ((*(volatile u32 *) (addr)) = (l))

#define readb(addr)		in_8((volatile u8 *)(addr))
#define writeb(b,addr)		out_8((volatile u8 *)(addr), (b))
#if !defined(__BIG_ENDIAN)
#define readw(addr)		(*(volatile u16 *) (addr))
#define readl(addr)		(*(volatile u32 *) (addr))
#define writew(b,addr)		((*(volatile u16 *) (addr)) = (b))
#define writel(b,addr)		((*(volatile u32 *) (addr)) = (b))
#else
#define readw(addr)		in_le16((volatile u16 *)(addr))
#define readl(addr)		in_le32((volatile u32 *)(addr))
#define writew(b,addr)		out_le16((volatile u16 *)(addr),(b))
#define writel(b,addr)		out_le32((volatile u32 *)(addr),(b))
#endif

#define insb(port, buf, ns)	_insb((u8 *)((port)+_IO_BASE), (buf), (ns))
#define outsb(port, buf, ns)	_outsb((u8 *)((port)+_IO_BASE), (buf), (ns))
#define insw(port, buf, ns)	_insw_ns((u16 *)((port)+_IO_BASE), (buf), (ns))
#define outsw(port, buf, ns)	_outsw_ns((u16 *)((port)+_IO_BASE), (buf), (ns))
#define insl(port, buf, nl)	_insl_ns((u32 *)((port)+_IO_BASE), (buf), (nl))
#define outsl(port, buf, nl)	_outsl_ns((u32 *)((port)+_IO_BASE), (buf), (nl))

#define inb(port)		in_8((u8 *)((port)+_IO_BASE))
#define outb(val, port)		out_8((u8 *)((port)+_IO_BASE), (val))
#if !defined(__BIG_ENDIAN)
#define inw(port)		in_be16((u16 *)((port)+_IO_BASE))
#define outw(val, port)		out_be16((u16 *)((port)+_IO_BASE), (val))
#define inl(port)		in_be32((u32 *)((port)+_IO_BASE))
#define outl(val, port)		out_be32((u32 *)((port)+_IO_BASE), (val))
#else
#define inw(port)		in_le16((u16 *)((port)+_IO_BASE))
#define outw(val, port)		out_le16((u16 *)((port)+_IO_BASE), (val))
#define inl(port)		in_le32((u32 *)((port)+_IO_BASE))
#define outl(val, port)		out_le32((u32 *)((port)+_IO_BASE), (val))
#endif

extern inline void _insb(volatile u8 * port, void *buf, int ns)
{
	u8 *data = (u8 *) buf;
	while (ns--)
		*data++ = *port;
}

extern inline void _outsb(volatile u8 * port, const void *buf, int ns)
{
	u8 *data = (u8 *) buf;
	while (ns--)
		*port = *data++;
}

extern inline void _insw(volatile u16 * port, void *buf, int ns)
{
	u16 *data = (u16 *) buf;
	while (ns--)
		*data++ = __sw16(*port);
}

extern inline void _outsw(volatile u16 * port, const void *buf, int ns)
{
	u16 *data = (u16 *) buf;
	while (ns--) {
		*port = __sw16(*data);
		data++;
	}
}

extern inline void _insl(volatile u32 * port, void *buf, int nl)
{
	u32 *data = (u32 *) buf;
	while (nl--)
		*data++ = __sw32(*port);
}

extern inline void _outsl(volatile u32 * port, const void *buf, int nl)
{
	u32 *data = (u32 *) buf;
	while (nl--) {
		*port = __sw32(*data);
		data++;
	}
}

extern inline void _insw_ns(volatile u16 * port, void *buf, int ns)
{
	u16 *data = (u16 *) buf;
	while (ns--)
		*data++ = *port;
}

extern inline void _outsw_ns(volatile u16 * port, const void *buf, int ns)
{
	u16 *data = (u16 *) buf;
	while (ns--) {
		*port = *data++;
	}
}

extern inline void _insl_ns(volatile u32 * port, void *buf, int nl)
{
	u32 *data = (u32 *) buf;
	while (nl--)
		*data++ = *port;
}

extern inline void _outsl_ns(volatile u32 * port, const void *buf, int nl)
{
	u32 *data = (u32 *) buf;
	while (nl--) {
		*port = *data;
		data++;
	}
}

#define insw_ns(port, buf, ns)	_insw_ns((u16 *)((port)+_IO_BASE), (buf), (ns))
#define outsw_ns(port, buf, ns)	_outsw_ns((u16 *)((port)+_IO_BASE), (buf), (ns))
#define insl_ns(port, buf, nl)	_insl_ns((u32 *)((port)+_IO_BASE), (buf), (nl))
#define outsl_ns(port, buf, nl)	_outsl_ns((u32 *)((port)+_IO_BASE), (buf), (nl))

#define IO_SPACE_LIMIT ~0

extern inline int in_8(volatile u8 * addr)
{
	return (int)*addr;
}

extern inline void out_8(volatile u8 * addr, int val)
{
	*addr = (u8) val;
}

extern inline int in_le16(volatile u16 * addr)
{
	return __sw16(*addr);
}

extern inline int in_be16(volatile u16 * addr)
{
	return (*addr & 0xFFFF);
}

extern inline void out_le16(volatile u16 * addr, int val)
{
	*addr = __sw16(val);
}

extern inline void out_be16(volatile u16 * addr, int val)
{
	*addr = (u16) val;
}

extern inline unsigned in_le32(volatile u32 * addr)
{
	return __sw32(*addr);
}

extern inline unsigned in_be32(volatile u32 * addr)
{
	return (*addr);
}

extern inline void out_le32(volatile unsigned *addr, int val)
{
	*addr = __sw32(val);
}

extern inline void out_be32(volatile unsigned *addr, int val)
{
	*addr = val;
}

static inline void sync(void)
{
	/* This sync function is for PowerPC or other architecture instruction
	 * ColdFire does not have this instruction. Dummy function, added for
	 * compatibility (CFI driver)
	 */
}

#define MAP_NOCACHE	(0)
#define MAP_WRCOMBINE	(0)
#define MAP_WRBACK	(0)
#define MAP_WRTHROUGH	(0)

static inline void *map_physmem(phys_addr_t paddr, unsigned long len,
				unsigned long flags)
{
	return (void *)paddr;
}

static inline void unmap_physmem(void *vaddr, unsigned long flags)
{

}

static inline phys_addr_t virt_to_phys(void * vaddr)
{
	return (phys_addr_t)(vaddr);
}

#endif				/* __ASM_M68K_IO_H__ */
