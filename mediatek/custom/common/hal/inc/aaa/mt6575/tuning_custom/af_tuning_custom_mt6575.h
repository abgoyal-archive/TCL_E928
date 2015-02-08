

#ifndef _AF_TUNING_CUSTOM_MT6575_H
#define _AF_TUNING_CUSTOM_MT6575_H

#include "../param/aaa_param_mt6575.h"

//____AF Algorithm Parameters____
static AF_PARAM_T g_rAFParam =
{
    15,
    0,   // AFS search step minimum enable bit: 0 or 1
    4,   // AFS search step minimum (for normal): 0 ~ normal idx
    4    // AFS search step minimum (for macro):0 ~ macro idx
}; 

//____AF Statistics Config____
static AF_STAT_CONFIG_T g_rAFStatConfig = 
{
	TRUE,	// enable AF
	TRUE,	// 0:SMD [0 1 -1], 1:TEN [1 2 1]

	{{
		{ 0,  0,  0,  0},
		{ 0,  0,  0,  0},
		{ 0,  0,  0,  0},
		{ 0,  0,  0,  0},
		{ 0,  0,  0,  0},		
		{ 0,  0,  0,  0},
		{ 0,  0,  0,  0},
		{ 0,  0,  0,  0},
		{ 0,  0,  0,  0}	
	}},
	
	{7, 5, 3, 2, 8}
};

#endif

