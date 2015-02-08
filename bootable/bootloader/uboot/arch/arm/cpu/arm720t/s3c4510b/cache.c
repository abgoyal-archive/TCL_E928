

#include <common.h>
#include <asm/hardware.h>

void icache_enable (void)
{
	s32 i;

	/* disable all cache bits */
	CLR_REG( REG_SYSCFG, 0x3F);

	/* 8KB cache, write enable */
	SET_REG( REG_SYSCFG, CACHE_WRITE_BUFF | CACHE_MODE_01);

	/* clear TAG RAM bits */
	for ( i = 0; i < 256; i++)
	  PUT_REG( CACHE_TAG_RAM + 4*i, 0x00000000);

	/* clear SET0 RAM */
	for(i=0; i < 1024; i++)
	  PUT_REG( CACHE_SET0_RAM + 4*i, 0x00000000);

	/* clear SET1 RAM */
	for(i=0; i < 1024; i++)
	  PUT_REG( CACHE_SET1_RAM + 4*i, 0x00000000);

	/* enable cache */
	SET_REG( REG_SYSCFG, CACHE_ENABLE);

}

void icache_disable (void)
{
	/* disable all cache bits */
	CLR_REG( REG_SYSCFG, 0x3F);
}

int icache_status (void)
{
	return GET_REG( REG_SYSCFG) & CACHE_ENABLE;
}

void dcache_enable (void)
{
	/* we don't have seperate instruction/data caches */
	icache_enable();
}

void dcache_disable (void)
{
	/* we don't have seperate instruction/data caches */
	icache_disable();
}

int dcache_status (void)
{
	/* we don't have seperate instruction/data caches */
	return icache_status();
}
