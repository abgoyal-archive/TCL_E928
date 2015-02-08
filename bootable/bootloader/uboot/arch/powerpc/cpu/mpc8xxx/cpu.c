

#include <config.h>
#include <common.h>
#include <command.h>
#include <tsec.h>
#include <netdev.h>
#include <asm/cache.h>
#include <asm/io.h>

DECLARE_GLOBAL_DATA_PTR;

struct cpu_type cpu_type_list [] = {
#if defined(CONFIG_MPC85xx)
	CPU_TYPE_ENTRY(8533, 8533, 1),
	CPU_TYPE_ENTRY(8533, 8533_E, 1),
	CPU_TYPE_ENTRY(8535, 8535, 1),
	CPU_TYPE_ENTRY(8535, 8535_E, 1),
	CPU_TYPE_ENTRY(8536, 8536, 1),
	CPU_TYPE_ENTRY(8536, 8536_E, 1),
	CPU_TYPE_ENTRY(8540, 8540, 1),
	CPU_TYPE_ENTRY(8541, 8541, 1),
	CPU_TYPE_ENTRY(8541, 8541_E, 1),
	CPU_TYPE_ENTRY(8543, 8543, 1),
	CPU_TYPE_ENTRY(8543, 8543_E, 1),
	CPU_TYPE_ENTRY(8544, 8544, 1),
	CPU_TYPE_ENTRY(8544, 8544_E, 1),
	CPU_TYPE_ENTRY(8545, 8545, 1),
	CPU_TYPE_ENTRY(8545, 8545_E, 1),
	CPU_TYPE_ENTRY(8547, 8547_E, 1),
	CPU_TYPE_ENTRY(8548, 8548, 1),
	CPU_TYPE_ENTRY(8548, 8548_E, 1),
	CPU_TYPE_ENTRY(8555, 8555, 1),
	CPU_TYPE_ENTRY(8555, 8555_E, 1),
	CPU_TYPE_ENTRY(8560, 8560, 1),
	CPU_TYPE_ENTRY(8567, 8567, 1),
	CPU_TYPE_ENTRY(8567, 8567_E, 1),
	CPU_TYPE_ENTRY(8568, 8568, 1),
	CPU_TYPE_ENTRY(8568, 8568_E, 1),
	CPU_TYPE_ENTRY(8569, 8569, 1),
	CPU_TYPE_ENTRY(8569, 8569_E, 1),
	CPU_TYPE_ENTRY(8572, 8572, 2),
	CPU_TYPE_ENTRY(8572, 8572_E, 2),
	CPU_TYPE_ENTRY(P1011, P1011, 1),
	CPU_TYPE_ENTRY(P1011, P1011_E, 1),
	CPU_TYPE_ENTRY(P1012, P1012, 1),
	CPU_TYPE_ENTRY(P1012, P1012_E, 1),
	CPU_TYPE_ENTRY(P1013, P1013, 1),
	CPU_TYPE_ENTRY(P1013, P1013_E, 1),
	CPU_TYPE_ENTRY(P1020, P1020, 2),
	CPU_TYPE_ENTRY(P1020, P1020_E, 2),
	CPU_TYPE_ENTRY(P1021, P1021, 2),
	CPU_TYPE_ENTRY(P1021, P1021_E, 2),
	CPU_TYPE_ENTRY(P1022, P1022, 2),
	CPU_TYPE_ENTRY(P1022, P1022_E, 2),
	CPU_TYPE_ENTRY(P2010, P2010, 1),
	CPU_TYPE_ENTRY(P2010, P2010_E, 1),
	CPU_TYPE_ENTRY(P2020, P2020, 2),
	CPU_TYPE_ENTRY(P2020, P2020_E, 2),
	CPU_TYPE_ENTRY(P4040, P4040, 4),
	CPU_TYPE_ENTRY(P4040, P4040_E, 4),
	CPU_TYPE_ENTRY(P4080, P4080, 8),
	CPU_TYPE_ENTRY(P4080, P4080_E, 8),
#elif defined(CONFIG_MPC86xx)
	CPU_TYPE_ENTRY(8610, 8610, 1),
	CPU_TYPE_ENTRY(8641, 8641, 2),
	CPU_TYPE_ENTRY(8641D, 8641D, 2),
#endif
};

struct cpu_type cpu_type_unknown = CPU_TYPE_ENTRY(Unknown, Unknown, 1);

struct cpu_type *identify_cpu(u32 ver)
{
	int i;
	for (i = 0; i < ARRAY_SIZE(cpu_type_list); i++) {
		if (cpu_type_list[i].soc_ver == ver)
			return &cpu_type_list[i];
	}
	return &cpu_type_unknown;
}

int cpu_numcores() {
	struct cpu_type *cpu;
	cpu = gd->cpu;
	return cpu->num_cores;
}

int probecpu (void)
{
	uint svr;
	uint ver;

	svr = get_svr();
	ver = SVR_SOC_VER(svr);

	gd->cpu = identify_cpu(ver);

	return 0;
}

int cpu_eth_init(bd_t *bis)
{
#if defined(CONFIG_ETHER_ON_FCC)
	fec_initialize(bis);
#endif

#if defined(CONFIG_UEC_ETH)
	uec_standard_init(bis);
#endif

#if defined(CONFIG_TSEC_ENET) || defined(CONFIG_MPC85XX_FEC)
	tsec_standard_init(bis);
#endif

	return 0;
}
