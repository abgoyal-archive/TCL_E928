

#ifndef _LIBFDT_ENV_H
#define _LIBFDT_ENV_H

#include "compiler.h"

extern struct fdt_header *working_fdt;  /* Pointer to the working fdt */

#define fdt32_to_cpu(x)		be32_to_cpu(x)
#define cpu_to_fdt32(x)		cpu_to_be32(x)
#define fdt64_to_cpu(x)		be64_to_cpu(x)
#define cpu_to_fdt64(x)		cpu_to_be64(x)

#endif /* _LIBFDT_ENV_H */
