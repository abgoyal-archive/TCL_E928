

#ifdef CONFIG_S3C2400
	#include <asm/arch/s3c2400.h>
#elif defined CONFIG_S3C2410
	#include <asm/arch/s3c2410.h>
#else
	#error Please define the s3c24x0 cpu type
#endif
