

#ifndef _SYS_PROTO_H_
#define _SYS_PROTO_H_

u32 get_cpu_rev(void);
#define is_soc_rev(rev)	((get_cpu_rev() & 0xFF) - rev)

#endif
