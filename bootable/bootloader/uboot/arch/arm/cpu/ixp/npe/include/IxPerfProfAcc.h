

#ifndef IXPERFPROFACC_H
#define IXPERFPROFACC_H

#include "IxOsal.h"

#ifdef __linux
#include <linux/proc_fs.h>
#endif

#define IX_PERFPROF_ACC_XSCALE_PMU_MAX_PROFILE_SAMPLES	0xFFFF

#define IX_PERFPROF_ACC_BUS_PMU_MAX_PECS        7

#define IX_PERFPROF_ACC_XCYCLE_MAX_NUM_OF_MEASUREMENTS 600

#ifdef __linux
#define IX_PERFPROF_ACC_XSCALE_PMU_SYMBOL_ACCURACY 0xffff

#endif /*__linux*/

#ifndef NDEBUG
#define IX_PERFPROF_ACC_LOG(level, device, str, a, b, c, d, e, f)\
             (ixOsalLog (level, device, str, a, b, c, d, e, f))
#else /*do nothing*/
#define IX_PERFPROF_ACC_LOG(level, device, str, a, b, c, d, e, f) 
#endif /*ifdef NDEBUG */


typedef struct
{
	UINT32 programCounter;  /**<the program counter value of the sample*/
	UINT32 freq;		/**<the frequency of the occurence of the sample*/
} IxPerfProfAccXscalePmuSamplePcProfile;

typedef struct
{
    UINT32 lower32BitsEventCount; /**<lower 32bits value of the event counter*/        
    UINT32 upper32BitsEventCount; /**<upper 32bits value of the event counter*/
}   IxPerfProfAccXscalePmuEvtCnt;

typedef struct
{
    UINT32 clk_value;           /**<current value of clock counter*/                 
    UINT32 clk_samples;        /**<number of clock counter overflows*/
    UINT32 event1_value;        /**<current value of event 1 counter*/    
    UINT32 event1_samples;     /**<number of event 1 counter overflows*/
    UINT32 event2_value;        /**<current value of event 2 counter*/
    UINT32 event2_samples;     /**<number of event 2 counter overflows*/
    UINT32 event3_value;        /**<current value of event 3 counter*/
    UINT32 event3_samples;     /**<number of event 3 counter overflows*/
    UINT32 event4_value;        /**<current value of event 4 counter*/
    UINT32 event4_samples;     /**<number of event 4 counter overflows*/
} IxPerfProfAccXscalePmuResults;

typedef struct 
{
    float maxIdlePercentage; 		/**<maximum percentage of Idle cycles*/
    float minIdlePercentage; 		/**<minimum percentage of Idle cycles*/
    float aveIdlePercentage;		/**<average percentage of Idle cycles*/
    UINT32 totalMeasurements;		/**<total number of measurement made */
} IxPerfProfAccXcycleResults; 

typedef struct
{
    UINT32 statsToGetLower27Bit[IX_PERFPROF_ACC_BUS_PMU_MAX_PECS]; /**<Lower 27 Bit of counter value */
    UINT32 statsToGetUpper32Bit[IX_PERFPROF_ACC_BUS_PMU_MAX_PECS]; /**<Upper 32 Bit of counter value */
} IxPerfProfAccBusPmuResults;


typedef enum
{
	IX_PERFPROF_ACC_BUS_PMU_PEC1_NORTH_NPEA_GRANT_SELECT = 1, /**< Select North NPEA grant on PEC1*/
	IX_PERFPROF_ACC_BUS_PMU_PEC1_NORTH_NPEB_GRANT_SELECT, /**< Select North NPEB grant on PEC1*/
	IX_PERFPROF_ACC_BUS_PMU_PEC1_NORTH_NPEC_GRANT_SELECT, /**< Select North NPEC grant on PEC1*/
	IX_PERFPROF_ACC_BUS_PMU_PEC1_NORTH_BUS_IDLE_SELECT, /**< Select North bus idle on PEC1*/
	IX_PERFPROF_ACC_BUS_PMU_PEC1_NORTH_NPEA_REQ_SELECT, /**< Select North NPEA req on PEC1*/
	IX_PERFPROF_ACC_BUS_PMU_PEC1_NORTH_NPEB_REQ_SELECT, /**< Select North NPEB req on PEC1*/
	IX_PERFPROF_ACC_BUS_PMU_PEC1_NORTH_NPEC_REQ_SELECT, /**< Select North NPEC req on PEC1*/

	IX_PERFPROF_ACC_BUS_PMU_PEC1_SOUTH_GSKT_GRANT_SELECT, /**< Select south gasket grant on PEC1*/
	IX_PERFPROF_ACC_BUS_PMU_PEC1_SOUTH_ABB_GRANT_SELECT, /**< Select south abb grant on PEC1*/
	IX_PERFPROF_ACC_BUS_PMU_PEC1_SOUTH_PCI_GRANT_SELECT, /**< Select south pci grant on PEC1*/
	IX_PERFPROF_ACC_BUS_PMU_PEC1_SOUTH_APB_GRANT_SELECT, /**< Select south apb grant on PEC1*/
	IX_PERFPROF_ACC_BUS_PMU_PEC1_SOUTH_GSKT_REQ_SELECT, /**< Select south gasket request on PEC1*/
	IX_PERFPROF_ACC_BUS_PMU_PEC1_SOUTH_ABB_REQ_SELECT, /**< Select south abb request on PEC1*/
	IX_PERFPROF_ACC_BUS_PMU_PEC1_SOUTH_PCI_REQ_SELECT, /**< Select south pci request on PEC1*/
	IX_PERFPROF_ACC_BUS_PMU_PEC1_SOUTH_APB_REQ_SELECT, /**< Select south apb request on PEC1*/

	IX_PERFPROF_ACC_BUS_PMU_PEC1_SDR_0_HIT_SELECT, /**< Select sdram0 hit on PEC1*/
	IX_PERFPROF_ACC_BUS_PMU_PEC1_SDR_1_HIT_SELECT, /**< Select sdram1 hit on PEC1*/
	IX_PERFPROF_ACC_BUS_PMU_PEC1_SDR_2_HIT_SELECT, /**< Select sdram2 hit on PEC1*/
	IX_PERFPROF_ACC_BUS_PMU_PEC1_SDR_3_HIT_SELECT, /**< Select sdram3 hit on PEC1*/
	IX_PERFPROF_ACC_BUS_PMU_PEC1_SDR_4_MISS_SELECT, /**< Select sdram4 miss on PEC1*/
	IX_PERFPROF_ACC_BUS_PMU_PEC1_SDR_5_MISS_SELECT, /**< Select sdram5 miss on PEC1*/
	IX_PERFPROF_ACC_BUS_PMU_PEC1_SDR_6_MISS_SELECT, /**< Select sdram6 miss on PEC1*/
	IX_PERFPROF_ACC_BUS_PMU_PEC1_SDR_7_MISS_SELECT /**< Select sdram7 miss on PEC1*/
} IxPerfProfAccBusPmuEventCounters1;

typedef enum
{
	IX_PERFPROF_ACC_BUS_PMU_PEC2_NORTH_NPEA_XFER_SELECT = 24, /**< Select North NPEA transfer on PEC2*/
	IX_PERFPROF_ACC_BUS_PMU_PEC2_NORTH_NPEB_XFER_SELECT, /**< Select North NPEB transfer on PEC2*/
	IX_PERFPROF_ACC_BUS_PMU_PEC2_NORTH_NPEC_XFER_SELECT, /**< Select North NPEC transfer on PEC2*/
	IX_PERFPROF_ACC_BUS_PMU_PEC2_NORTH_BUS_WRITE_SELECT, /**< Select North bus write on PEC2*/
	IX_PERFPROF_ACC_BUS_PMU_PEC2_NORTH_NPEA_OWN_SELECT, /**< Select North NPEA own on PEC2*/
	IX_PERFPROF_ACC_BUS_PMU_PEC2_NORTH_NPEB_OWN_SELECT, /**< Select North NPEB own on PEC2*/
	IX_PERFPROF_ACC_BUS_PMU_PEC2_NORTH_NPEC_OWN_SELECT, /**< Select North NPEC own on PEC2*/

	IX_PERFPROF_ACC_BUS_PMU_PEC2_SOUTH_GSKT_XFER_SELECT, /**< Select South gasket transfer on PEC2*/
	IX_PERFPROF_ACC_BUS_PMU_PEC2_SOUTH_ABB_XFER_SELECT, /**< Select South abb transfer on PEC2*/
	IX_PERFPROF_ACC_BUS_PMU_PEC2_SOUTH_PCI_XFER_SELECT, /**< Select South pci transfer on PEC2*/
	IX_PERFPROF_ACC_BUS_PMU_PEC2_SOUTH_APB_XFER_SELECT, /**< Select South apb transfer on PEC2*/
	IX_PERFPROF_ACC_BUS_PMU_PEC2_SOUTH_GSKT_OWN_SELECT, /**< Select South gasket own on PEC2*/
	IX_PERFPROF_ACC_BUS_PMU_PEC2_SOUTH_ABB_OWN_SELECT, /**< Select South abb own on PEC2*/
	IX_PERFPROF_ACC_BUS_PMU_PEC2_SOUTH_PCI_OWN_SELECT, /**< Select South pci own on PEC2*/
	IX_PERFPROF_ACC_BUS_PMU_PEC2_SOUTH_APB_OWN_SELECT, /**< Select South apb own transfer on PEC2*/

	IX_PERFPROF_ACC_BUS_PMU_PEC2_SDR_1_HIT_SELECT, /**< Select sdram1 hit on PEC2*/
	IX_PERFPROF_ACC_BUS_PMU_PEC2_SDR_2_HIT_SELECT, /**< Select sdram2 hit on PEC2*/
	IX_PERFPROF_ACC_BUS_PMU_PEC2_SDR_3_HIT_SELECT, /**< Select sdram3 hit on PEC2*/
	IX_PERFPROF_ACC_BUS_PMU_PEC2_SDR_4_HIT_SELECT, /**< Select sdram4 hit on PEC2*/
	IX_PERFPROF_ACC_BUS_PMU_PEC2_SDR_5_MISS_SELECT, /**< Select sdram5 miss on PEC2*/
	IX_PERFPROF_ACC_BUS_PMU_PEC2_SDR_6_MISS_SELECT, /**< Select sdram6 miss on PEC2*/
	IX_PERFPROF_ACC_BUS_PMU_PEC2_SDR_7_MISS_SELECT, /**< Select sdram7 miss on PEC2*/
	IX_PERFPROF_ACC_BUS_PMU_PEC2_SDR_0_MISS_SELECT /**< Select sdram0 miss on PEC2*/
} IxPerfProfAccBusPmuEventCounters2;

typedef enum
{
	IX_PERFPROF_ACC_BUS_PMU_PEC3_NORTH_NPEA_RETRY_SELECT = 47, /**< Select north NPEA retry on PEC3*/
	IX_PERFPROF_ACC_BUS_PMU_PEC3_NORTH_NPEB_RETRY_SELECT, /**< Select north NPEB retry on PEC3*/
	IX_PERFPROF_ACC_BUS_PMU_PEC3_NORTH_NPEC_RETRY_SELECT, /**< Select north NPEC retry on PEC3*/
	IX_PERFPROF_ACC_BUS_PMU_PEC3_NORTH_BUS_READ_SELECT, /**< Select north bus read on PEC3*/
	IX_PERFPROF_ACC_BUS_PMU_PEC3_NORTH_NPEA_WRITE_SELECT, /**< Select north NPEA write on PEC3*/
	IX_PERFPROF_ACC_BUS_PMU_PEC3_NORTH_NPEB_WRITE_SELECT, /**< Select north NPEB write on PEC3*/
	IX_PERFPROF_ACC_BUS_PMU_PEC3_NORTH_NPEC_WRITE_SELECT, /**< Select north NPEC wirte on PEC3*/

	IX_PERFPROF_ACC_BUS_PMU_PEC3_SOUTH_GSKT_RETRY_SELECT, /**< Select south gasket retry on PEC3*/
	IX_PERFPROF_ACC_BUS_PMU_PEC3_SOUTH_ABB_RETRY_SELECT, /**< Select south abb retry on PEC3*/
	IX_PERFPROF_ACC_BUS_PMU_PEC3_SOUTH_PCI_RETRY_SELECT, /**< Select south pci retry on PEC3*/
	IX_PERFPROF_ACC_BUS_PMU_PEC3_SOUTH_APB_RETRY_SELECT, /**< Select south apb retry on PEC3*/
 	IX_PERFPROF_ACC_BUS_PMU_PEC3_SOUTH_GSKT_WRITE_SELECT, /**< Select south gasket write on PEC3*/
 	IX_PERFPROF_ACC_BUS_PMU_PEC3_SOUTH_ABB_WRITE_SELECT, /**< Select south abb write on PEC3*/
 	IX_PERFPROF_ACC_BUS_PMU_PEC3_SOUTH_PCI_WRITE_SELECT, /**< Select south pci write on PEC3*/
 	IX_PERFPROF_ACC_BUS_PMU_PEC3_SOUTH_APB_WRITE_SELECT, /**< Select south apb write on PEC3*/

 	IX_PERFPROF_ACC_BUS_PMU_PEC3_SDR_2_HIT_SELECT, /**< Select sdram2 hit on PEC3*/
 	IX_PERFPROF_ACC_BUS_PMU_PEC3_SDR_3_HIT_SELECT, /**< Select sdram3 hit on PEC3*/
 	IX_PERFPROF_ACC_BUS_PMU_PEC3_SDR_4_HIT_SELECT, /**< Select sdram4 hit on PEC3*/
 	IX_PERFPROF_ACC_BUS_PMU_PEC3_SDR_5_HIT_SELECT, /**< Select sdram5 hit on PEC3*/
 	IX_PERFPROF_ACC_BUS_PMU_PEC3_SDR_6_MISS_SELECT, /**< Select sdram6 miss on PEC3*/
 	IX_PERFPROF_ACC_BUS_PMU_PEC3_SDR_7_MISS_SELECT, /**< Select sdram7 miss on PEC3*/
 	IX_PERFPROF_ACC_BUS_PMU_PEC3_SDR_0_MISS_SELECT, /**< Select sdram0 miss on PEC3*/
 	IX_PERFPROF_ACC_BUS_PMU_PEC3_SDR_1_MISS_SELECT /**< Select sdram1 miss on PEC3*/
} IxPerfProfAccBusPmuEventCounters3;

typedef enum
{
 	IX_PERFPROF_ACC_BUS_PMU_PEC4_SOUTH_PCI_SPLIT_SELECT = 70, /**< Select south pci split on PEC4*/
 	IX_PERFPROF_ACC_BUS_PMU_PEC4_SOUTH_EXP_SPLIT_SELECT, /**< Select south expansion split on PEC4*/
 	IX_PERFPROF_ACC_BUS_PMU_PEC4_SOUTH_APB_GRANT_SELECT, /**< Select south apb grant on PEC4*/
 	IX_PERFPROF_ACC_BUS_PMU_PEC4_SOUTH_APB_XFER_SELECT, /**< Select south apb transfer on PEC4*/
 	IX_PERFPROF_ACC_BUS_PMU_PEC4_SOUTH_GSKT_READ_SELECT, /**< Select south gasket read on PEC4*/
 	IX_PERFPROF_ACC_BUS_PMU_PEC4_SOUTH_ABB_READ_SELECT, /**< Select south abb read on PEC4*/
 	IX_PERFPROF_ACC_BUS_PMU_PEC4_SOUTH_PCI_READ_SELECT, /**< Select south pci read on PEC4*/
 	IX_PERFPROF_ACC_BUS_PMU_PEC4_SOUTH_APB_READ_SELECT, /**< Select south apb read on PEC4*/

 	IX_PERFPROF_ACC_BUS_PMU_PEC4_NORTH_ABB_SPLIT_SELECT, /**< Select north abb split on PEC4*/
 	IX_PERFPROF_ACC_BUS_PMU_PEC4_NORTH_NPEA_REQ_SELECT, /**< Select north NPEA req on PEC4*/
 	IX_PERFPROF_ACC_BUS_PMU_PEC4_NORTH_NPEA_READ_SELECT, /**< Select north NPEA read on PEC4*/
 	IX_PERFPROF_ACC_BUS_PMU_PEC4_NORTH_NPEB_READ_SELECT, /**< Select north NPEB read on PEC4*/
 	IX_PERFPROF_ACC_BUS_PMU_PEC4_NORTH_NPEC_READ_SELECT, /**< Select north NPEC read on PEC4*/

 	IX_PERFPROF_ACC_BUS_PMU_PEC4_SDR_3_HIT_SELECT, /**< Select sdram3 hit on PEC4*/
 	IX_PERFPROF_ACC_BUS_PMU_PEC4_SDR_4_HIT_SELECT, /**< Select sdram4 hit on PEC4*/
 	IX_PERFPROF_ACC_BUS_PMU_PEC4_SDR_5_HIT_SELECT, /**< Select sdram5 hit on PEC4*/
 	IX_PERFPROF_ACC_BUS_PMU_PEC4_SDR_6_HIT_SELECT, /**< Select sdram6 hit on PEC4*/
 	IX_PERFPROF_ACC_BUS_PMU_PEC4_SDR_7_MISS_SELECT, /**< Select sdram7 miss on PEC4*/
 	IX_PERFPROF_ACC_BUS_PMU_PEC4_SDR_0_MISS_SELECT, /**< Select sdram0 miss on PEC4*/
 	IX_PERFPROF_ACC_BUS_PMU_PEC4_SDR_1_MISS_SELECT, /**< Select sdram1 miss on PEC4*/
 	IX_PERFPROF_ACC_BUS_PMU_PEC4_SDR_2_MISS_SELECT /**< Select sdram2 miss on PEC4*/
} IxPerfProfAccBusPmuEventCounters4;

typedef enum
{
 	IX_PERFPROF_ACC_BUS_PMU_PEC5_SOUTH_ABB_GRANT_SELECT = 91, /**< Select south abb grant on PEC5*/
 	IX_PERFPROF_ACC_BUS_PMU_PEC5_SOUTH_ABB_XFER_SELECT, /**< Select south abb transfer on PEC5*/
 	IX_PERFPROF_ACC_BUS_PMU_PEC5_SOUTH_ABB_RETRY_SELECT, /**< Select south abb retry on PEC5*/
 	IX_PERFPROF_ACC_BUS_PMU_PEC5_SOUTH_EXP_SPLIT_SELECT, /**< Select south expansion split on PEC5*/
 	IX_PERFPROF_ACC_BUS_PMU_PEC5_SOUTH_ABB_REQ_SELECT, /**< Select south abb request on PEC5*/
 	IX_PERFPROF_ACC_BUS_PMU_PEC5_SOUTH_ABB_OWN_SELECT, /**< Select south abb own on PEC5*/
 	IX_PERFPROF_ACC_BUS_PMU_PEC5_SOUTH_BUS_IDLE_SELECT, /**< Select south bus idle on PEC5*/

 	IX_PERFPROF_ACC_BUS_PMU_PEC5_NORTH_NPEB_GRANT_SELECT, /**< Select north NPEB grant on PEC5*/
 	IX_PERFPROF_ACC_BUS_PMU_PEC5_NORTH_NPEB_XFER_SELECT, /**< Select north NPEB transfer on PEC5*/
 	IX_PERFPROF_ACC_BUS_PMU_PEC5_NORTH_NPEB_RETRY_SELECT, /**< Select north NPEB retry on PEC5*/
 	IX_PERFPROF_ACC_BUS_PMU_PEC5_NORTH_NPEB_REQ_SELECT, /**< Select north NPEB request on PEC5*/
 	IX_PERFPROF_ACC_BUS_PMU_PEC5_NORTH_NPEB_OWN_SELECT, /**< Select north NPEB own on PEC5*/
 	IX_PERFPROF_ACC_BUS_PMU_PEC5_NORTH_NPEB_WRITE_SELECT, /**< Select north NPEB write on PEC5*/
 	IX_PERFPROF_ACC_BUS_PMU_PEC5_NORTH_NPEB_READ_SELECT, /**< Select north NPEB read on PEC5*/

 	IX_PERFPROF_ACC_BUS_PMU_PEC5_SDR_4_HIT_SELECT, /**< Select north sdram4 hit on PEC5*/
 	IX_PERFPROF_ACC_BUS_PMU_PEC5_SDR_5_HIT_SELECT, /**< Select north sdram5 hit on PEC5*/
 	IX_PERFPROF_ACC_BUS_PMU_PEC5_SDR_6_HIT_SELECT, /**< Select north sdram6 hit on PEC5*/
 	IX_PERFPROF_ACC_BUS_PMU_PEC5_SDR_7_HIT_SELECT, /**< Select north sdram7 hit on PEC5*/
 	IX_PERFPROF_ACC_BUS_PMU_PEC5_SDR_0_MISS_SELECT, /**< Select north sdram0 miss on PEC5*/
 	IX_PERFPROF_ACC_BUS_PMU_PEC5_SDR_1_MISS_SELECT, /**< Select north sdram1 miss on PEC5*/
 	IX_PERFPROF_ACC_BUS_PMU_PEC5_SDR_2_MISS_SELECT, /**< Select north sdram2 miss on PEC5*/
 	IX_PERFPROF_ACC_BUS_PMU_PEC5_SDR_3_MISS_SELECT /**< Select north sdram3 miss on PEC5*/
} IxPerfProfAccBusPmuEventCounters5;

typedef enum
{
	IX_PERFPROF_ACC_BUS_PMU_PEC6_SOUTH_PCI_GRANT_SELECT = 113, /**< Select south pci grant on PEC6*/
 	IX_PERFPROF_ACC_BUS_PMU_PEC6_SOUTH_PCI_XFER_SELECT, /**< Select south pci transfer on PEC6*/
 	IX_PERFPROF_ACC_BUS_PMU_PEC6_SOUTH_PCI_RETRY_SELECT, /**< Select south pci retry on PEC6*/
 	IX_PERFPROF_ACC_BUS_PMU_PEC6_SOUTH_PCI_SPLIT_SELECT, /**< Select south pci split on PEC6*/
 	IX_PERFPROF_ACC_BUS_PMU_PEC6_SOUTH_PCI_REQ_SELECT, /**< Select south pci request on PEC6*/
 	IX_PERFPROF_ACC_BUS_PMU_PEC6_SOUTH_PCI_OWN_SELECT, /**< Select south pci own on PEC6*/
 	IX_PERFPROF_ACC_BUS_PMU_PEC6_SOUTH_BUS_WRITE_SELECT, /**< Select south pci write on PEC6*/

 	IX_PERFPROF_ACC_BUS_PMU_PEC6_NORTH_NPEC_GRANT_SELECT, /**< Select north NPEC grant on PEC6*/
 	IX_PERFPROF_ACC_BUS_PMU_PEC6_NORTH_NPEC_XFER_SELECT, /**< Select north NPEC transfer on PEC6*/
 	IX_PERFPROF_ACC_BUS_PMU_PEC6_NORTH_NPEC_RETRY_SELECT, /**< Select north NPEC retry on PEC6*/
 	IX_PERFPROF_ACC_BUS_PMU_PEC6_NORTH_NPEC_REQ_SELECT, /**< Select north NPEC request on PEC6*/
 	IX_PERFPROF_ACC_BUS_PMU_PEC6_NORTH_NPEC_OWN_SELECT, /**< Select north NPEC own on PEC6*/
 	IX_PERFPROF_ACC_BUS_PMU_PEC6_NORTH_NPEB_WRITE_SELECT, /**< Select north NPEB write on PEC6*/
 	IX_PERFPROF_ACC_BUS_PMU_PEC6_NORTH_NPEC_READ_SELECT, /**< Select north NPEC read on PEC6*/

 	IX_PERFPROF_ACC_BUS_PMU_PEC6_SDR_5_HIT_SELECT, /**< Select sdram5 hit on PEC6*/
 	IX_PERFPROF_ACC_BUS_PMU_PEC6_SDR_6_HIT_SELECT, /**< Select sdram6 hit on PEC6*/
 	IX_PERFPROF_ACC_BUS_PMU_PEC6_SDR_7_HIT_SELECT, /**< Select sdram7 hit on PEC6*/
 	IX_PERFPROF_ACC_BUS_PMU_PEC6_SDR_0_HIT_SELECT, /**< Select sdram0 hit on PEC6*/
 	IX_PERFPROF_ACC_BUS_PMU_PEC6_SDR_1_MISS_SELECT, /**< Select sdram1 miss on PEC6*/
 	IX_PERFPROF_ACC_BUS_PMU_PEC6_SDR_2_MISS_SELECT, /**< Select sdram2 miss on PEC6*/
 	IX_PERFPROF_ACC_BUS_PMU_PEC6_SDR_3_MISS_SELECT, /**< Select sdram3 miss on PEC6*/
 	IX_PERFPROF_ACC_BUS_PMU_PEC6_SDR_4_MISS_SELECT /**< Select sdram4 miss on PEC6*/
} IxPerfProfAccBusPmuEventCounters6;

typedef enum
{
 	IX_PERFPROF_ACC_BUS_PMU_PEC7_SOUTH_APB_RETRY_SELECT = 135, /**< Select south apb retry on PEC7*/
 	IX_PERFPROF_ACC_BUS_PMU_PEC7_SOUTH_APB_REQ_SELECT, /**< Select south apb request on PEC7*/
 	IX_PERFPROF_ACC_BUS_PMU_PEC7_SOUTH_APB_OWN_SELECT, /**< Select south apb own on PEC7*/
 	IX_PERFPROF_ACC_BUS_PMU_PEC7_SOUTH_BUS_READ_SELECT, /**< Select south bus read on PEC7*/
 	IX_PERFPROF_ACC_BUS_PMU_PEC7_CYCLE_COUNT_SELECT /**< Select cycle count on PEC7*/
} IxPerfProfAccBusPmuEventCounters7;

typedef enum 
{
    IX_PERFPROF_ACC_XSCALE_PMU_EVENT_CACHE_MISS=0,      /**< cache miss*/ 
    IX_PERFPROF_ACC_XSCALE_PMU_EVENT_CACHE_INSTRUCTION,/**< cache instruction*/ 
    IX_PERFPROF_ACC_XSCALE_PMU_EVENT_STALL,     /**< event stall*/ 
    IX_PERFPROF_ACC_XSCALE_PMU_EVENT_INST_TLB_MISS, /**< instruction tlb miss*/ 
    IX_PERFPROF_ACC_XSCALE_PMU_EVENT_DATA_TLB_MISS, /**< data tlb miss*/ 
    IX_PERFPROF_ACC_XSCALE_PMU_EVENT_BRANCH_EXEC,   /**< branch executed*/ 
    IX_PERFPROF_ACC_XSCALE_PMU_EVENT_BRANCH_MISPREDICT, /**<branch mispredict*/ 
    IX_PERFPROF_ACC_XSCALE_PMU_EVENT_INST_EXEC, /**< instruction executed*/ 
    IX_PERFPROF_ACC_XSCALE_PMU_EVENT_FULL_EVERYCYCLE,   /**< 
                                                         *Stall - data cache 
                                                         *buffers are full. 
							 							 *This event occurs 
							 							 *every cycle where 
							 							 *condition present 
							 							 */ 
    IX_PERFPROF_ACC_XSCALE_PMU_EVENT_ONCE,    /**< 
                                               *Stall - data cache buffers are 
					       					   *full.This event occurs once 
					       					   *for each contiguous sequence 
					       					   */ 
    IX_PERFPROF_ACC_XSCALE_PMU_EVENT_DATA_CACHE_ACCESS, /**< data cache access*/ 
    IX_PERFPROF_ACC_XSCALE_PMU_EVENT_DATA_CACHE_MISS,   /**< data cache miss*/ 
    IX_PERFPROF_ACC_XSCALE_PMU_EVENT_DATA_CACHE_WRITEBACK,  /**<data cache 
                                                             *writeback 
						             						 */ 
    IX_PERFPROF_ACC_XSCALE_PMU_EVENT_SW_CHANGE_PC,  /**< sw change pc*/ 
    IX_PERFPROF_ACC_XSCALE_PMU_EVENT_MAX    /**< max value*/ 
} IxPerfProfAccXscalePmuEvent;

typedef enum
{
	IX_PERFPROF_ACC_STATUS_SUCCESS = IX_SUCCESS,    /**< success*/
	IX_PERFPROF_ACC_STATUS_FAIL = IX_FAIL,          /**< fail*/
	IX_PERFPROF_ACC_STATUS_ANOTHER_UTIL_IN_PROGRESS,/**<another utility in 
													 *progress
													 */ 
	IX_PERFPROF_ACC_STATUS_XCYCLE_MEASUREMENT_IN_PROGRESS, /**<measurement in
															*progress
															*/
	IX_PERFPROF_ACC_STATUS_XCYCLE_NO_BASELINE, /**<no baseline yet*/	 
	IX_PERFPROF_ACC_STATUS_XCYCLE_MEASUREMENT_REQUEST_OUT_OF_RANGE, /**< 
															* Measurement chosen 
															* is out of range
															*/
	IX_PERFPROF_ACC_STATUS_XCYCLE_PRIORITY_SET_FAIL,  /**<
	                                                     * Cannot set 
														 * task priority
	                                                     */
	IX_PERFPROF_ACC_STATUS_XCYCLE_THREAD_CREATE_FAIL, /**< 
	                                                     * Fail create thread
	                                                     */
	IX_PERFPROF_ACC_STATUS_XCYCLE_PRIORITY_RESTORE_FAIL,  /**<
	                                                         *cannot restore
	                                                         *priority
	                                                         */
	IX_PERFPROF_ACC_STATUS_XCYCLE_MEASUREMENT_NOT_RUNNING, /**< xcycle not running*/
   	IX_PERFPROF_ACC_STATUS_XSCALE_PMU_NUM_INVALID, /**< invalid number 
   	                                                *entered
   	                                                */
	IX_PERFPROF_ACC_STATUS_XSCALE_PMU_EVENT_INVALID, /**< invalid pmu event*/
	IX_PERFPROF_ACC_STATUS_XSCALE_PMU_START_NOT_CALLED, /**<a start process
							     						 *was not called 
							     						 *before attempting
							     						 *a stop or results
							     						 *get
							     						 */
	IX_PERFPROF_ACC_STATUS_BUS_PMU_MODE_ERROR,  /**< invalid mode*/
	IX_PERFPROF_ACC_STATUS_BUS_PMU_PEC1_ERROR,	/**< invalid pec1 entered*/
	IX_PERFPROF_ACC_STATUS_BUS_PMU_PEC2_ERROR,	/**< invalid pec2 entered*/
	IX_PERFPROF_ACC_STATUS_BUS_PMU_PEC3_ERROR,	/**< invalid pec3 entered*/
	IX_PERFPROF_ACC_STATUS_BUS_PMU_PEC4_ERROR,	/**< invalid pec4 entered*/
	IX_PERFPROF_ACC_STATUS_BUS_PMU_PEC5_ERROR,	/**< invalid pec5 entered*/
	IX_PERFPROF_ACC_STATUS_BUS_PMU_PEC6_ERROR,	/**< invalid pec6 entered*/
	IX_PERFPROF_ACC_STATUS_BUS_PMU_PEC7_ERROR,	/**< invalid pec7 entered*/
	IX_PERFPROF_ACC_STATUS_BUS_PMU_START_NOT_CALLED, /**<a start process
							     					 *was not called 
							     					 *before attempting
							     					 *a stop 
													 */
        IX_PERFPROF_ACC_STATUS_COMPONENT_NOT_SUPPORTED /**<Device or OS does not support component*/
} IxPerfProfAccStatus;

typedef enum
{
        IX_PERFPROF_ACC_BUS_PMU_MODE_HALT=0,   /**< halt state*/
        IX_PERFPROF_ACC_BUS_PMU_MODE_SOUTH,    /**< south state*/
        IX_PERFPROF_ACC_BUS_PMU_MODE_NORTH,    /**< north state*/
        IX_PERFPROF_ACC_BUS_PMU_MODE_SDRAM    /**< SDRAM state*/
} IxPerfProfAccBusPmuMode;


PUBLIC IxPerfProfAccStatus
ixPerfProfAccXscalePmuEventCountStart(
	BOOL clkCntDiv,
	UINT32 numEvents,
	IxPerfProfAccXscalePmuEvent pmuEvent1,
	IxPerfProfAccXscalePmuEvent pmuEvent2,
	IxPerfProfAccXscalePmuEvent pmuEvent3,
	IxPerfProfAccXscalePmuEvent pmuEvent4 );


PUBLIC IxPerfProfAccStatus 
ixPerfProfAccXscalePmuEventCountStop(
   IxPerfProfAccXscalePmuResults *eventCountStopResults); 

PUBLIC IxPerfProfAccStatus 
ixPerfProfAccXscalePmuTimeSampStart(
	UINT32 samplingRate, 
	BOOL clkCntDiv);

PUBLIC IxPerfProfAccStatus
ixPerfProfAccXscalePmuTimeSampStop(
	IxPerfProfAccXscalePmuEvtCnt *clkCount,
	IxPerfProfAccXscalePmuSamplePcProfile *timeProfile);

PUBLIC IxPerfProfAccStatus
ixPerfProfAccXscalePmuEventSampStart(
	UINT32 numEvents,
	IxPerfProfAccXscalePmuEvent pmuEvent1,
	UINT32 eventRate1,
    IxPerfProfAccXscalePmuEvent pmuEvent2,
    UINT32 eventRate2,
    IxPerfProfAccXscalePmuEvent pmuEvent3,
    UINT32 eventRate3,
    IxPerfProfAccXscalePmuEvent pmuEvent4,
    UINT32 eventRate4);

PUBLIC IxPerfProfAccStatus 
ixPerfProfAccXscalePmuEventSampStop(
    IxPerfProfAccXscalePmuSamplePcProfile *eventProfile1,
    IxPerfProfAccXscalePmuSamplePcProfile *eventProfile2,
    IxPerfProfAccXscalePmuSamplePcProfile *eventProfile3,
    IxPerfProfAccXscalePmuSamplePcProfile *eventProfile4);

PUBLIC void                                                     
ixPerfProfAccXscalePmuResultsGet(IxPerfProfAccXscalePmuResults *results);    

PUBLIC 
IxPerfProfAccStatus ixPerfProfAccBusPmuStart (
        IxPerfProfAccBusPmuMode mode, 
        IxPerfProfAccBusPmuEventCounters1 pecEvent1,
        IxPerfProfAccBusPmuEventCounters2 pecEvent2, 
        IxPerfProfAccBusPmuEventCounters3 pecEvent3, 
        IxPerfProfAccBusPmuEventCounters4 pecEvent4,
        IxPerfProfAccBusPmuEventCounters5 pecEvent5, 
        IxPerfProfAccBusPmuEventCounters6 pecEvent6, 
        IxPerfProfAccBusPmuEventCounters7 pecEvent7);

PUBLIC IxPerfProfAccStatus 
ixPerfProfAccBusPmuStop (void);

PUBLIC void
ixPerfProfAccBusPmuResultsGet (IxPerfProfAccBusPmuResults *BusPmuResults);

PUBLIC void
ixPerfProfAccBusPmuPMSRGet (
UINT32 *pmsrValue);



PUBLIC IxPerfProfAccStatus
ixPerfProfAccXcycleBaselineRun(
	UINT32 *numBaselineCycle); 

PUBLIC IxPerfProfAccStatus
ixPerfProfAccXcycleStart (
	UINT32 numMeasurementsRequested);  

PUBLIC IxPerfProfAccStatus
ixPerfProfAccXcycleStop(void); 

PUBLIC IxPerfProfAccStatus
ixPerfProfAccXcycleResultsGet (
    IxPerfProfAccXcycleResults *xcycleResult);  

PUBLIC BOOL
ixPerfProfAccXcycleInProgress(void); 

#ifdef __linux
int
ixPerfProfAccXscalePmuTimeSampCreateProcFile (char *buf, char **start, off_t offset,
                                      int count, int *eof, void *data);

int
ixPerfProfAccXscalePmuEventSampCreateProcFile (char *buf, char **start, off_t offset,
                                      int count, int *eof, void *data);


#endif /* ifdef __linux */

#endif /* ndef IXPERFPROFACC_H */



