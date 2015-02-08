

#ifndef __BFIN_CDEF_ADSP_BF525_proc__
#define __BFIN_CDEF_ADSP_BF525_proc__

#include "../mach-common/ADSP-EDN-core_cdef.h"

#include "ADSP-EDN-BF52x-extended_cdef.h"

#define pPLL_CTL                       ((uint16_t volatile *)PLL_CTL) /* PLL Control Register */
#define bfin_read_PLL_CTL()            bfin_read16(PLL_CTL)
#define bfin_write_PLL_CTL(val)        bfin_write16(PLL_CTL, val)
#define pPLL_DIV                       ((uint16_t volatile *)PLL_DIV) /* PLL Divide Register */
#define bfin_read_PLL_DIV()            bfin_read16(PLL_DIV)
#define bfin_write_PLL_DIV(val)        bfin_write16(PLL_DIV, val)
#define pVR_CTL                        ((uint16_t volatile *)VR_CTL) /* Voltage Regulator Control Register */
#define bfin_read_VR_CTL()             bfin_read16(VR_CTL)
#define bfin_write_VR_CTL(val)         bfin_write16(VR_CTL, val)
#define pPLL_STAT                      ((uint16_t volatile *)PLL_STAT) /* PLL Status Register */
#define bfin_read_PLL_STAT()           bfin_read16(PLL_STAT)
#define bfin_write_PLL_STAT(val)       bfin_write16(PLL_STAT, val)
#define pPLL_LOCKCNT                   ((uint16_t volatile *)PLL_LOCKCNT) /* PLL Lock Count Register */
#define bfin_read_PLL_LOCKCNT()        bfin_read16(PLL_LOCKCNT)
#define bfin_write_PLL_LOCKCNT(val)    bfin_write16(PLL_LOCKCNT, val)
#define pCHIPID                        ((uint32_t volatile *)CHIPID)
#define bfin_read_CHIPID()             bfin_read32(CHIPID)
#define bfin_write_CHIPID(val)         bfin_write32(CHIPID, val)
#define pSWRST                         ((uint16_t volatile *)SWRST) /* Software Reset Register */
#define bfin_read_SWRST()              bfin_read16(SWRST)
#define bfin_write_SWRST(val)          bfin_write16(SWRST, val)
#define pSYSCR                         ((uint16_t volatile *)SYSCR) /* System Configuration register */
#define bfin_read_SYSCR()              bfin_read16(SYSCR)
#define bfin_write_SYSCR(val)          bfin_write16(SYSCR, val)
#define pSRAM_BASE_ADDR                ((void * volatile *)SRAM_BASE_ADDR) /* SRAM Base Address (Read Only) */
#define bfin_read_SRAM_BASE_ADDR()     bfin_readPTR(SRAM_BASE_ADDR)
#define bfin_write_SRAM_BASE_ADDR(val) bfin_writePTR(SRAM_BASE_ADDR, val)
#define pDMEM_CONTROL                  ((uint32_t volatile *)DMEM_CONTROL) /* Data memory control */
#define bfin_read_DMEM_CONTROL()       bfin_read32(DMEM_CONTROL)
#define bfin_write_DMEM_CONTROL(val)   bfin_write32(DMEM_CONTROL, val)
#define pDCPLB_STATUS                  ((uint32_t volatile *)DCPLB_STATUS) /* Data Cache Programmable Look-Aside Buffer Status */
#define bfin_read_DCPLB_STATUS()       bfin_read32(DCPLB_STATUS)
#define bfin_write_DCPLB_STATUS(val)   bfin_write32(DCPLB_STATUS, val)
#define pDCPLB_FAULT_ADDR              ((void * volatile *)DCPLB_FAULT_ADDR) /* Data Cache Programmable Look-Aside Buffer Fault Address */
#define bfin_read_DCPLB_FAULT_ADDR()   bfin_readPTR(DCPLB_FAULT_ADDR)
#define bfin_write_DCPLB_FAULT_ADDR(val) bfin_writePTR(DCPLB_FAULT_ADDR, val)
#define pDCPLB_ADDR0                   ((void * volatile *)DCPLB_ADDR0) /* Data Cache Protection Lookaside Buffer 0 */
#define bfin_read_DCPLB_ADDR0()        bfin_readPTR(DCPLB_ADDR0)
#define bfin_write_DCPLB_ADDR0(val)    bfin_writePTR(DCPLB_ADDR0, val)
#define pDCPLB_ADDR1                   ((void * volatile *)DCPLB_ADDR1) /* Data Cache Protection Lookaside Buffer 1 */
#define bfin_read_DCPLB_ADDR1()        bfin_readPTR(DCPLB_ADDR1)
#define bfin_write_DCPLB_ADDR1(val)    bfin_writePTR(DCPLB_ADDR1, val)
#define pDCPLB_ADDR2                   ((void * volatile *)DCPLB_ADDR2) /* Data Cache Protection Lookaside Buffer 2 */
#define bfin_read_DCPLB_ADDR2()        bfin_readPTR(DCPLB_ADDR2)
#define bfin_write_DCPLB_ADDR2(val)    bfin_writePTR(DCPLB_ADDR2, val)
#define pDCPLB_ADDR3                   ((void * volatile *)DCPLB_ADDR3) /* Data Cache Protection Lookaside Buffer 3 */
#define bfin_read_DCPLB_ADDR3()        bfin_readPTR(DCPLB_ADDR3)
#define bfin_write_DCPLB_ADDR3(val)    bfin_writePTR(DCPLB_ADDR3, val)
#define pDCPLB_ADDR4                   ((void * volatile *)DCPLB_ADDR4) /* Data Cache Protection Lookaside Buffer 4 */
#define bfin_read_DCPLB_ADDR4()        bfin_readPTR(DCPLB_ADDR4)
#define bfin_write_DCPLB_ADDR4(val)    bfin_writePTR(DCPLB_ADDR4, val)
#define pDCPLB_ADDR5                   ((void * volatile *)DCPLB_ADDR5) /* Data Cache Protection Lookaside Buffer 5 */
#define bfin_read_DCPLB_ADDR5()        bfin_readPTR(DCPLB_ADDR5)
#define bfin_write_DCPLB_ADDR5(val)    bfin_writePTR(DCPLB_ADDR5, val)
#define pDCPLB_ADDR6                   ((void * volatile *)DCPLB_ADDR6) /* Data Cache Protection Lookaside Buffer 6 */
#define bfin_read_DCPLB_ADDR6()        bfin_readPTR(DCPLB_ADDR6)
#define bfin_write_DCPLB_ADDR6(val)    bfin_writePTR(DCPLB_ADDR6, val)
#define pDCPLB_ADDR7                   ((void * volatile *)DCPLB_ADDR7) /* Data Cache Protection Lookaside Buffer 7 */
#define bfin_read_DCPLB_ADDR7()        bfin_readPTR(DCPLB_ADDR7)
#define bfin_write_DCPLB_ADDR7(val)    bfin_writePTR(DCPLB_ADDR7, val)
#define pDCPLB_ADDR8                   ((void * volatile *)DCPLB_ADDR8) /* Data Cache Protection Lookaside Buffer 8 */
#define bfin_read_DCPLB_ADDR8()        bfin_readPTR(DCPLB_ADDR8)
#define bfin_write_DCPLB_ADDR8(val)    bfin_writePTR(DCPLB_ADDR8, val)
#define pDCPLB_ADDR9                   ((void * volatile *)DCPLB_ADDR9) /* Data Cache Protection Lookaside Buffer 9 */
#define bfin_read_DCPLB_ADDR9()        bfin_readPTR(DCPLB_ADDR9)
#define bfin_write_DCPLB_ADDR9(val)    bfin_writePTR(DCPLB_ADDR9, val)
#define pDCPLB_ADDR10                  ((void * volatile *)DCPLB_ADDR10) /* Data Cache Protection Lookaside Buffer 10 */
#define bfin_read_DCPLB_ADDR10()       bfin_readPTR(DCPLB_ADDR10)
#define bfin_write_DCPLB_ADDR10(val)   bfin_writePTR(DCPLB_ADDR10, val)
#define pDCPLB_ADDR11                  ((void * volatile *)DCPLB_ADDR11) /* Data Cache Protection Lookaside Buffer 11 */
#define bfin_read_DCPLB_ADDR11()       bfin_readPTR(DCPLB_ADDR11)
#define bfin_write_DCPLB_ADDR11(val)   bfin_writePTR(DCPLB_ADDR11, val)
#define pDCPLB_ADDR12                  ((void * volatile *)DCPLB_ADDR12) /* Data Cache Protection Lookaside Buffer 12 */
#define bfin_read_DCPLB_ADDR12()       bfin_readPTR(DCPLB_ADDR12)
#define bfin_write_DCPLB_ADDR12(val)   bfin_writePTR(DCPLB_ADDR12, val)
#define pDCPLB_ADDR13                  ((void * volatile *)DCPLB_ADDR13) /* Data Cache Protection Lookaside Buffer 13 */
#define bfin_read_DCPLB_ADDR13()       bfin_readPTR(DCPLB_ADDR13)
#define bfin_write_DCPLB_ADDR13(val)   bfin_writePTR(DCPLB_ADDR13, val)
#define pDCPLB_ADDR14                  ((void * volatile *)DCPLB_ADDR14) /* Data Cache Protection Lookaside Buffer 14 */
#define bfin_read_DCPLB_ADDR14()       bfin_readPTR(DCPLB_ADDR14)
#define bfin_write_DCPLB_ADDR14(val)   bfin_writePTR(DCPLB_ADDR14, val)
#define pDCPLB_ADDR15                  ((void * volatile *)DCPLB_ADDR15) /* Data Cache Protection Lookaside Buffer 15 */
#define bfin_read_DCPLB_ADDR15()       bfin_readPTR(DCPLB_ADDR15)
#define bfin_write_DCPLB_ADDR15(val)   bfin_writePTR(DCPLB_ADDR15, val)
#define pDCPLB_DATA0                   ((uint32_t volatile *)DCPLB_DATA0) /* Data Cache 0 Status */
#define bfin_read_DCPLB_DATA0()        bfin_read32(DCPLB_DATA0)
#define bfin_write_DCPLB_DATA0(val)    bfin_write32(DCPLB_DATA0, val)
#define pDCPLB_DATA1                   ((uint32_t volatile *)DCPLB_DATA1) /* Data Cache 1 Status */
#define bfin_read_DCPLB_DATA1()        bfin_read32(DCPLB_DATA1)
#define bfin_write_DCPLB_DATA1(val)    bfin_write32(DCPLB_DATA1, val)
#define pDCPLB_DATA2                   ((uint32_t volatile *)DCPLB_DATA2) /* Data Cache 2 Status */
#define bfin_read_DCPLB_DATA2()        bfin_read32(DCPLB_DATA2)
#define bfin_write_DCPLB_DATA2(val)    bfin_write32(DCPLB_DATA2, val)
#define pDCPLB_DATA3                   ((uint32_t volatile *)DCPLB_DATA3) /* Data Cache 3 Status */
#define bfin_read_DCPLB_DATA3()        bfin_read32(DCPLB_DATA3)
#define bfin_write_DCPLB_DATA3(val)    bfin_write32(DCPLB_DATA3, val)
#define pDCPLB_DATA4                   ((uint32_t volatile *)DCPLB_DATA4) /* Data Cache 4 Status */
#define bfin_read_DCPLB_DATA4()        bfin_read32(DCPLB_DATA4)
#define bfin_write_DCPLB_DATA4(val)    bfin_write32(DCPLB_DATA4, val)
#define pDCPLB_DATA5                   ((uint32_t volatile *)DCPLB_DATA5) /* Data Cache 5 Status */
#define bfin_read_DCPLB_DATA5()        bfin_read32(DCPLB_DATA5)
#define bfin_write_DCPLB_DATA5(val)    bfin_write32(DCPLB_DATA5, val)
#define pDCPLB_DATA6                   ((uint32_t volatile *)DCPLB_DATA6) /* Data Cache 6 Status */
#define bfin_read_DCPLB_DATA6()        bfin_read32(DCPLB_DATA6)
#define bfin_write_DCPLB_DATA6(val)    bfin_write32(DCPLB_DATA6, val)
#define pDCPLB_DATA7                   ((uint32_t volatile *)DCPLB_DATA7) /* Data Cache 7 Status */
#define bfin_read_DCPLB_DATA7()        bfin_read32(DCPLB_DATA7)
#define bfin_write_DCPLB_DATA7(val)    bfin_write32(DCPLB_DATA7, val)
#define pDCPLB_DATA8                   ((uint32_t volatile *)DCPLB_DATA8) /* Data Cache 8 Status */
#define bfin_read_DCPLB_DATA8()        bfin_read32(DCPLB_DATA8)
#define bfin_write_DCPLB_DATA8(val)    bfin_write32(DCPLB_DATA8, val)
#define pDCPLB_DATA9                   ((uint32_t volatile *)DCPLB_DATA9) /* Data Cache 9 Status */
#define bfin_read_DCPLB_DATA9()        bfin_read32(DCPLB_DATA9)
#define bfin_write_DCPLB_DATA9(val)    bfin_write32(DCPLB_DATA9, val)
#define pDCPLB_DATA10                  ((uint32_t volatile *)DCPLB_DATA10) /* Data Cache 10 Status */
#define bfin_read_DCPLB_DATA10()       bfin_read32(DCPLB_DATA10)
#define bfin_write_DCPLB_DATA10(val)   bfin_write32(DCPLB_DATA10, val)
#define pDCPLB_DATA11                  ((uint32_t volatile *)DCPLB_DATA11) /* Data Cache 11 Status */
#define bfin_read_DCPLB_DATA11()       bfin_read32(DCPLB_DATA11)
#define bfin_write_DCPLB_DATA11(val)   bfin_write32(DCPLB_DATA11, val)
#define pDCPLB_DATA12                  ((uint32_t volatile *)DCPLB_DATA12) /* Data Cache 12 Status */
#define bfin_read_DCPLB_DATA12()       bfin_read32(DCPLB_DATA12)
#define bfin_write_DCPLB_DATA12(val)   bfin_write32(DCPLB_DATA12, val)
#define pDCPLB_DATA13                  ((uint32_t volatile *)DCPLB_DATA13) /* Data Cache 13 Status */
#define bfin_read_DCPLB_DATA13()       bfin_read32(DCPLB_DATA13)
#define bfin_write_DCPLB_DATA13(val)   bfin_write32(DCPLB_DATA13, val)
#define pDCPLB_DATA14                  ((uint32_t volatile *)DCPLB_DATA14) /* Data Cache 14 Status */
#define bfin_read_DCPLB_DATA14()       bfin_read32(DCPLB_DATA14)
#define bfin_write_DCPLB_DATA14(val)   bfin_write32(DCPLB_DATA14, val)
#define pDCPLB_DATA15                  ((uint32_t volatile *)DCPLB_DATA15) /* Data Cache 15 Status */
#define bfin_read_DCPLB_DATA15()       bfin_read32(DCPLB_DATA15)
#define bfin_write_DCPLB_DATA15(val)   bfin_write32(DCPLB_DATA15, val)
#define pDTEST_COMMAND                 ((uint32_t volatile *)DTEST_COMMAND) /* Data Test Command Register */
#define bfin_read_DTEST_COMMAND()      bfin_read32(DTEST_COMMAND)
#define bfin_write_DTEST_COMMAND(val)  bfin_write32(DTEST_COMMAND, val)
#define pDTEST_DATA0                   ((uint32_t volatile *)DTEST_DATA0) /* Data Test Data Register */
#define bfin_read_DTEST_DATA0()        bfin_read32(DTEST_DATA0)
#define bfin_write_DTEST_DATA0(val)    bfin_write32(DTEST_DATA0, val)
#define pDTEST_DATA1                   ((uint32_t volatile *)DTEST_DATA1) /* Data Test Data Register */
#define bfin_read_DTEST_DATA1()        bfin_read32(DTEST_DATA1)
#define bfin_write_DTEST_DATA1(val)    bfin_write32(DTEST_DATA1, val)
#define pIMEM_CONTROL                  ((uint32_t volatile *)IMEM_CONTROL) /* Instruction Memory Control */
#define bfin_read_IMEM_CONTROL()       bfin_read32(IMEM_CONTROL)
#define bfin_write_IMEM_CONTROL(val)   bfin_write32(IMEM_CONTROL, val)
#define pICPLB_STATUS                  ((uint32_t volatile *)ICPLB_STATUS) /* Instruction Cache Programmable Look-Aside Buffer Status */
#define bfin_read_ICPLB_STATUS()       bfin_read32(ICPLB_STATUS)
#define bfin_write_ICPLB_STATUS(val)   bfin_write32(ICPLB_STATUS, val)
#define pICPLB_FAULT_ADDR              ((void * volatile *)ICPLB_FAULT_ADDR) /* Instruction Cache Programmable Look-Aside Buffer Fault Address */
#define bfin_read_ICPLB_FAULT_ADDR()   bfin_readPTR(ICPLB_FAULT_ADDR)
#define bfin_write_ICPLB_FAULT_ADDR(val) bfin_writePTR(ICPLB_FAULT_ADDR, val)
#define pICPLB_ADDR0                   ((void * volatile *)ICPLB_ADDR0) /* Instruction Cacheability Protection Lookaside Buffer 0 */
#define bfin_read_ICPLB_ADDR0()        bfin_readPTR(ICPLB_ADDR0)
#define bfin_write_ICPLB_ADDR0(val)    bfin_writePTR(ICPLB_ADDR0, val)
#define pICPLB_ADDR1                   ((void * volatile *)ICPLB_ADDR1) /* Instruction Cacheability Protection Lookaside Buffer 1 */
#define bfin_read_ICPLB_ADDR1()        bfin_readPTR(ICPLB_ADDR1)
#define bfin_write_ICPLB_ADDR1(val)    bfin_writePTR(ICPLB_ADDR1, val)
#define pICPLB_ADDR2                   ((void * volatile *)ICPLB_ADDR2) /* Instruction Cacheability Protection Lookaside Buffer 2 */
#define bfin_read_ICPLB_ADDR2()        bfin_readPTR(ICPLB_ADDR2)
#define bfin_write_ICPLB_ADDR2(val)    bfin_writePTR(ICPLB_ADDR2, val)
#define pICPLB_ADDR3                   ((void * volatile *)ICPLB_ADDR3) /* Instruction Cacheability Protection Lookaside Buffer 3 */
#define bfin_read_ICPLB_ADDR3()        bfin_readPTR(ICPLB_ADDR3)
#define bfin_write_ICPLB_ADDR3(val)    bfin_writePTR(ICPLB_ADDR3, val)
#define pICPLB_ADDR4                   ((void * volatile *)ICPLB_ADDR4) /* Instruction Cacheability Protection Lookaside Buffer 4 */
#define bfin_read_ICPLB_ADDR4()        bfin_readPTR(ICPLB_ADDR4)
#define bfin_write_ICPLB_ADDR4(val)    bfin_writePTR(ICPLB_ADDR4, val)
#define pICPLB_ADDR5                   ((void * volatile *)ICPLB_ADDR5) /* Instruction Cacheability Protection Lookaside Buffer 5 */
#define bfin_read_ICPLB_ADDR5()        bfin_readPTR(ICPLB_ADDR5)
#define bfin_write_ICPLB_ADDR5(val)    bfin_writePTR(ICPLB_ADDR5, val)
#define pICPLB_ADDR6                   ((void * volatile *)ICPLB_ADDR6) /* Instruction Cacheability Protection Lookaside Buffer 6 */
#define bfin_read_ICPLB_ADDR6()        bfin_readPTR(ICPLB_ADDR6)
#define bfin_write_ICPLB_ADDR6(val)    bfin_writePTR(ICPLB_ADDR6, val)
#define pICPLB_ADDR7                   ((void * volatile *)ICPLB_ADDR7) /* Instruction Cacheability Protection Lookaside Buffer 7 */
#define bfin_read_ICPLB_ADDR7()        bfin_readPTR(ICPLB_ADDR7)
#define bfin_write_ICPLB_ADDR7(val)    bfin_writePTR(ICPLB_ADDR7, val)
#define pICPLB_ADDR8                   ((void * volatile *)ICPLB_ADDR8) /* Instruction Cacheability Protection Lookaside Buffer 8 */
#define bfin_read_ICPLB_ADDR8()        bfin_readPTR(ICPLB_ADDR8)
#define bfin_write_ICPLB_ADDR8(val)    bfin_writePTR(ICPLB_ADDR8, val)
#define pICPLB_ADDR9                   ((void * volatile *)ICPLB_ADDR9) /* Instruction Cacheability Protection Lookaside Buffer 9 */
#define bfin_read_ICPLB_ADDR9()        bfin_readPTR(ICPLB_ADDR9)
#define bfin_write_ICPLB_ADDR9(val)    bfin_writePTR(ICPLB_ADDR9, val)
#define pICPLB_ADDR10                  ((void * volatile *)ICPLB_ADDR10) /* Instruction Cacheability Protection Lookaside Buffer 10 */
#define bfin_read_ICPLB_ADDR10()       bfin_readPTR(ICPLB_ADDR10)
#define bfin_write_ICPLB_ADDR10(val)   bfin_writePTR(ICPLB_ADDR10, val)
#define pICPLB_ADDR11                  ((void * volatile *)ICPLB_ADDR11) /* Instruction Cacheability Protection Lookaside Buffer 11 */
#define bfin_read_ICPLB_ADDR11()       bfin_readPTR(ICPLB_ADDR11)
#define bfin_write_ICPLB_ADDR11(val)   bfin_writePTR(ICPLB_ADDR11, val)
#define pICPLB_ADDR12                  ((void * volatile *)ICPLB_ADDR12) /* Instruction Cacheability Protection Lookaside Buffer 12 */
#define bfin_read_ICPLB_ADDR12()       bfin_readPTR(ICPLB_ADDR12)
#define bfin_write_ICPLB_ADDR12(val)   bfin_writePTR(ICPLB_ADDR12, val)
#define pICPLB_ADDR13                  ((void * volatile *)ICPLB_ADDR13) /* Instruction Cacheability Protection Lookaside Buffer 13 */
#define bfin_read_ICPLB_ADDR13()       bfin_readPTR(ICPLB_ADDR13)
#define bfin_write_ICPLB_ADDR13(val)   bfin_writePTR(ICPLB_ADDR13, val)
#define pICPLB_ADDR14                  ((void * volatile *)ICPLB_ADDR14) /* Instruction Cacheability Protection Lookaside Buffer 14 */
#define bfin_read_ICPLB_ADDR14()       bfin_readPTR(ICPLB_ADDR14)
#define bfin_write_ICPLB_ADDR14(val)   bfin_writePTR(ICPLB_ADDR14, val)
#define pICPLB_ADDR15                  ((void * volatile *)ICPLB_ADDR15) /* Instruction Cacheability Protection Lookaside Buffer 15 */
#define bfin_read_ICPLB_ADDR15()       bfin_readPTR(ICPLB_ADDR15)
#define bfin_write_ICPLB_ADDR15(val)   bfin_writePTR(ICPLB_ADDR15, val)
#define pICPLB_DATA0                   ((uint32_t volatile *)ICPLB_DATA0) /* Instruction Cache 0 Status */
#define bfin_read_ICPLB_DATA0()        bfin_read32(ICPLB_DATA0)
#define bfin_write_ICPLB_DATA0(val)    bfin_write32(ICPLB_DATA0, val)
#define pICPLB_DATA1                   ((uint32_t volatile *)ICPLB_DATA1) /* Instruction Cache 1 Status */
#define bfin_read_ICPLB_DATA1()        bfin_read32(ICPLB_DATA1)
#define bfin_write_ICPLB_DATA1(val)    bfin_write32(ICPLB_DATA1, val)
#define pICPLB_DATA2                   ((uint32_t volatile *)ICPLB_DATA2) /* Instruction Cache 2 Status */
#define bfin_read_ICPLB_DATA2()        bfin_read32(ICPLB_DATA2)
#define bfin_write_ICPLB_DATA2(val)    bfin_write32(ICPLB_DATA2, val)
#define pICPLB_DATA3                   ((uint32_t volatile *)ICPLB_DATA3) /* Instruction Cache 3 Status */
#define bfin_read_ICPLB_DATA3()        bfin_read32(ICPLB_DATA3)
#define bfin_write_ICPLB_DATA3(val)    bfin_write32(ICPLB_DATA3, val)
#define pICPLB_DATA4                   ((uint32_t volatile *)ICPLB_DATA4) /* Instruction Cache 4 Status */
#define bfin_read_ICPLB_DATA4()        bfin_read32(ICPLB_DATA4)
#define bfin_write_ICPLB_DATA4(val)    bfin_write32(ICPLB_DATA4, val)
#define pICPLB_DATA5                   ((uint32_t volatile *)ICPLB_DATA5) /* Instruction Cache 5 Status */
#define bfin_read_ICPLB_DATA5()        bfin_read32(ICPLB_DATA5)
#define bfin_write_ICPLB_DATA5(val)    bfin_write32(ICPLB_DATA5, val)
#define pICPLB_DATA6                   ((uint32_t volatile *)ICPLB_DATA6) /* Instruction Cache 6 Status */
#define bfin_read_ICPLB_DATA6()        bfin_read32(ICPLB_DATA6)
#define bfin_write_ICPLB_DATA6(val)    bfin_write32(ICPLB_DATA6, val)
#define pICPLB_DATA7                   ((uint32_t volatile *)ICPLB_DATA7) /* Instruction Cache 7 Status */
#define bfin_read_ICPLB_DATA7()        bfin_read32(ICPLB_DATA7)
#define bfin_write_ICPLB_DATA7(val)    bfin_write32(ICPLB_DATA7, val)
#define pICPLB_DATA8                   ((uint32_t volatile *)ICPLB_DATA8) /* Instruction Cache 8 Status */
#define bfin_read_ICPLB_DATA8()        bfin_read32(ICPLB_DATA8)
#define bfin_write_ICPLB_DATA8(val)    bfin_write32(ICPLB_DATA8, val)
#define pICPLB_DATA9                   ((uint32_t volatile *)ICPLB_DATA9) /* Instruction Cache 9 Status */
#define bfin_read_ICPLB_DATA9()        bfin_read32(ICPLB_DATA9)
#define bfin_write_ICPLB_DATA9(val)    bfin_write32(ICPLB_DATA9, val)
#define pICPLB_DATA10                  ((uint32_t volatile *)ICPLB_DATA10) /* Instruction Cache 10 Status */
#define bfin_read_ICPLB_DATA10()       bfin_read32(ICPLB_DATA10)
#define bfin_write_ICPLB_DATA10(val)   bfin_write32(ICPLB_DATA10, val)
#define pICPLB_DATA11                  ((uint32_t volatile *)ICPLB_DATA11) /* Instruction Cache 11 Status */
#define bfin_read_ICPLB_DATA11()       bfin_read32(ICPLB_DATA11)
#define bfin_write_ICPLB_DATA11(val)   bfin_write32(ICPLB_DATA11, val)
#define pICPLB_DATA12                  ((uint32_t volatile *)ICPLB_DATA12) /* Instruction Cache 12 Status */
#define bfin_read_ICPLB_DATA12()       bfin_read32(ICPLB_DATA12)
#define bfin_write_ICPLB_DATA12(val)   bfin_write32(ICPLB_DATA12, val)
#define pICPLB_DATA13                  ((uint32_t volatile *)ICPLB_DATA13) /* Instruction Cache 13 Status */
#define bfin_read_ICPLB_DATA13()       bfin_read32(ICPLB_DATA13)
#define bfin_write_ICPLB_DATA13(val)   bfin_write32(ICPLB_DATA13, val)
#define pICPLB_DATA14                  ((uint32_t volatile *)ICPLB_DATA14) /* Instruction Cache 14 Status */
#define bfin_read_ICPLB_DATA14()       bfin_read32(ICPLB_DATA14)
#define bfin_write_ICPLB_DATA14(val)   bfin_write32(ICPLB_DATA14, val)
#define pICPLB_DATA15                  ((uint32_t volatile *)ICPLB_DATA15) /* Instruction Cache 15 Status */
#define bfin_read_ICPLB_DATA15()       bfin_read32(ICPLB_DATA15)
#define bfin_write_ICPLB_DATA15(val)   bfin_write32(ICPLB_DATA15, val)
#define pITEST_COMMAND                 ((uint32_t volatile *)ITEST_COMMAND) /* Instruction Test Command Register */
#define bfin_read_ITEST_COMMAND()      bfin_read32(ITEST_COMMAND)
#define bfin_write_ITEST_COMMAND(val)  bfin_write32(ITEST_COMMAND, val)
#define pITEST_DATA0                   ((uint32_t volatile *)ITEST_DATA0) /* Instruction Test Data Register */
#define bfin_read_ITEST_DATA0()        bfin_read32(ITEST_DATA0)
#define bfin_write_ITEST_DATA0(val)    bfin_write32(ITEST_DATA0, val)
#define pITEST_DATA1                   ((uint32_t volatile *)ITEST_DATA1) /* Instruction Test Data Register */
#define bfin_read_ITEST_DATA1()        bfin_read32(ITEST_DATA1)
#define bfin_write_ITEST_DATA1(val)    bfin_write32(ITEST_DATA1, val)
#define pEVT0                          ((void * volatile *)EVT0) /* Event Vector 0 ESR Address */
#define bfin_read_EVT0()               bfin_readPTR(EVT0)
#define bfin_write_EVT0(val)           bfin_writePTR(EVT0, val)
#define pEVT1                          ((void * volatile *)EVT1) /* Event Vector 1 ESR Address */
#define bfin_read_EVT1()               bfin_readPTR(EVT1)
#define bfin_write_EVT1(val)           bfin_writePTR(EVT1, val)
#define pEVT2                          ((void * volatile *)EVT2) /* Event Vector 2 ESR Address */
#define bfin_read_EVT2()               bfin_readPTR(EVT2)
#define bfin_write_EVT2(val)           bfin_writePTR(EVT2, val)
#define pEVT3                          ((void * volatile *)EVT3) /* Event Vector 3 ESR Address */
#define bfin_read_EVT3()               bfin_readPTR(EVT3)
#define bfin_write_EVT3(val)           bfin_writePTR(EVT3, val)
#define pEVT4                          ((void * volatile *)EVT4) /* Event Vector 4 ESR Address */
#define bfin_read_EVT4()               bfin_readPTR(EVT4)
#define bfin_write_EVT4(val)           bfin_writePTR(EVT4, val)
#define pEVT5                          ((void * volatile *)EVT5) /* Event Vector 5 ESR Address */
#define bfin_read_EVT5()               bfin_readPTR(EVT5)
#define bfin_write_EVT5(val)           bfin_writePTR(EVT5, val)
#define pEVT6                          ((void * volatile *)EVT6) /* Event Vector 6 ESR Address */
#define bfin_read_EVT6()               bfin_readPTR(EVT6)
#define bfin_write_EVT6(val)           bfin_writePTR(EVT6, val)
#define pEVT7                          ((void * volatile *)EVT7) /* Event Vector 7 ESR Address */
#define bfin_read_EVT7()               bfin_readPTR(EVT7)
#define bfin_write_EVT7(val)           bfin_writePTR(EVT7, val)
#define pEVT8                          ((void * volatile *)EVT8) /* Event Vector 8 ESR Address */
#define bfin_read_EVT8()               bfin_readPTR(EVT8)
#define bfin_write_EVT8(val)           bfin_writePTR(EVT8, val)
#define pEVT9                          ((void * volatile *)EVT9) /* Event Vector 9 ESR Address */
#define bfin_read_EVT9()               bfin_readPTR(EVT9)
#define bfin_write_EVT9(val)           bfin_writePTR(EVT9, val)
#define pEVT10                         ((void * volatile *)EVT10) /* Event Vector 10 ESR Address */
#define bfin_read_EVT10()              bfin_readPTR(EVT10)
#define bfin_write_EVT10(val)          bfin_writePTR(EVT10, val)
#define pEVT11                         ((void * volatile *)EVT11) /* Event Vector 11 ESR Address */
#define bfin_read_EVT11()              bfin_readPTR(EVT11)
#define bfin_write_EVT11(val)          bfin_writePTR(EVT11, val)
#define pEVT12                         ((void * volatile *)EVT12) /* Event Vector 12 ESR Address */
#define bfin_read_EVT12()              bfin_readPTR(EVT12)
#define bfin_write_EVT12(val)          bfin_writePTR(EVT12, val)
#define pEVT13                         ((void * volatile *)EVT13) /* Event Vector 13 ESR Address */
#define bfin_read_EVT13()              bfin_readPTR(EVT13)
#define bfin_write_EVT13(val)          bfin_writePTR(EVT13, val)
#define pEVT14                         ((void * volatile *)EVT14) /* Event Vector 14 ESR Address */
#define bfin_read_EVT14()              bfin_readPTR(EVT14)
#define bfin_write_EVT14(val)          bfin_writePTR(EVT14, val)
#define pEVT15                         ((void * volatile *)EVT15) /* Event Vector 15 ESR Address */
#define bfin_read_EVT15()              bfin_readPTR(EVT15)
#define bfin_write_EVT15(val)          bfin_writePTR(EVT15, val)
#define pILAT                          ((uint32_t volatile *)ILAT) /* Interrupt Latch Register */
#define bfin_read_ILAT()               bfin_read32(ILAT)
#define bfin_write_ILAT(val)           bfin_write32(ILAT, val)
#define pIMASK                         ((uint32_t volatile *)IMASK) /* Interrupt Mask Register */
#define bfin_read_IMASK()              bfin_read32(IMASK)
#define bfin_write_IMASK(val)          bfin_write32(IMASK, val)
#define pIPEND                         ((uint32_t volatile *)IPEND) /* Interrupt Pending Register */
#define bfin_read_IPEND()              bfin_read32(IPEND)
#define bfin_write_IPEND(val)          bfin_write32(IPEND, val)
#define pIPRIO                         ((uint32_t volatile *)IPRIO) /* Interrupt Priority Register */
#define bfin_read_IPRIO()              bfin_read32(IPRIO)
#define bfin_write_IPRIO(val)          bfin_write32(IPRIO, val)
#define pTCNTL                         ((uint32_t volatile *)TCNTL) /* Core Timer Control Register */
#define bfin_read_TCNTL()              bfin_read32(TCNTL)
#define bfin_write_TCNTL(val)          bfin_write32(TCNTL, val)
#define pTPERIOD                       ((uint32_t volatile *)TPERIOD) /* Core Timer Period Register */
#define bfin_read_TPERIOD()            bfin_read32(TPERIOD)
#define bfin_write_TPERIOD(val)        bfin_write32(TPERIOD, val)
#define pTSCALE                        ((uint32_t volatile *)TSCALE) /* Core Timer Scale Register */
#define bfin_read_TSCALE()             bfin_read32(TSCALE)
#define bfin_write_TSCALE(val)         bfin_write32(TSCALE, val)
#define pTCOUNT                        ((uint32_t volatile *)TCOUNT) /* Core Timer Count Register */
#define bfin_read_TCOUNT()             bfin_read32(TCOUNT)
#define bfin_write_TCOUNT(val)         bfin_write32(TCOUNT, val)
#define pUSB_FADDR                     ((uint16_t volatile *)USB_FADDR) /* Function address register */
#define bfin_read_USB_FADDR()          bfin_read16(USB_FADDR)
#define bfin_write_USB_FADDR(val)      bfin_write16(USB_FADDR, val)
#define pUSB_POWER                     ((uint16_t volatile *)USB_POWER) /* Power management register */
#define bfin_read_USB_POWER()          bfin_read16(USB_POWER)
#define bfin_write_USB_POWER(val)      bfin_write16(USB_POWER, val)
#define pUSB_INTRTX                    ((uint16_t volatile *)USB_INTRTX) /* Interrupt register for endpoint 0 and Tx endpoint 1 to 7 */
#define bfin_read_USB_INTRTX()         bfin_read16(USB_INTRTX)
#define bfin_write_USB_INTRTX(val)     bfin_write16(USB_INTRTX, val)
#define pUSB_INTRRX                    ((uint16_t volatile *)USB_INTRRX) /* Interrupt register for Rx endpoints 1 to 7 */
#define bfin_read_USB_INTRRX()         bfin_read16(USB_INTRRX)
#define bfin_write_USB_INTRRX(val)     bfin_write16(USB_INTRRX, val)
#define pUSB_INTRTXE                   ((uint16_t volatile *)USB_INTRTXE) /* Interrupt enable register for IntrTx */
#define bfin_read_USB_INTRTXE()        bfin_read16(USB_INTRTXE)
#define bfin_write_USB_INTRTXE(val)    bfin_write16(USB_INTRTXE, val)
#define pUSB_INTRRXE                   ((uint16_t volatile *)USB_INTRRXE) /* Interrupt enable register for IntrRx */
#define bfin_read_USB_INTRRXE()        bfin_read16(USB_INTRRXE)
#define bfin_write_USB_INTRRXE(val)    bfin_write16(USB_INTRRXE, val)
#define pUSB_INTRUSB                   ((uint16_t volatile *)USB_INTRUSB) /* Interrupt register for common USB interrupts */
#define bfin_read_USB_INTRUSB()        bfin_read16(USB_INTRUSB)
#define bfin_write_USB_INTRUSB(val)    bfin_write16(USB_INTRUSB, val)
#define pUSB_INTRUSBE                  ((uint16_t volatile *)USB_INTRUSBE) /* Interrupt enable register for IntrUSB */
#define bfin_read_USB_INTRUSBE()       bfin_read16(USB_INTRUSBE)
#define bfin_write_USB_INTRUSBE(val)   bfin_write16(USB_INTRUSBE, val)
#define pUSB_FRAME                     ((uint16_t volatile *)USB_FRAME) /* USB frame number */
#define bfin_read_USB_FRAME()          bfin_read16(USB_FRAME)
#define bfin_write_USB_FRAME(val)      bfin_write16(USB_FRAME, val)
#define pUSB_INDEX                     ((uint16_t volatile *)USB_INDEX) /* Index register for selecting the indexed endpoint registers */
#define bfin_read_USB_INDEX()          bfin_read16(USB_INDEX)
#define bfin_write_USB_INDEX(val)      bfin_write16(USB_INDEX, val)
#define pUSB_TESTMODE                  ((uint16_t volatile *)USB_TESTMODE) /* Enabled USB 20 test modes */
#define bfin_read_USB_TESTMODE()       bfin_read16(USB_TESTMODE)
#define bfin_write_USB_TESTMODE(val)   bfin_write16(USB_TESTMODE, val)
#define pUSB_GLOBINTR                  ((uint16_t volatile *)USB_GLOBINTR) /* Global Interrupt Mask register and Wakeup Exception Interrupt */
#define bfin_read_USB_GLOBINTR()       bfin_read16(USB_GLOBINTR)
#define bfin_write_USB_GLOBINTR(val)   bfin_write16(USB_GLOBINTR, val)
#define pUSB_GLOBAL_CTL                ((uint16_t volatile *)USB_GLOBAL_CTL) /* Global Clock Control for the core */
#define bfin_read_USB_GLOBAL_CTL()     bfin_read16(USB_GLOBAL_CTL)
#define bfin_write_USB_GLOBAL_CTL(val) bfin_write16(USB_GLOBAL_CTL, val)
#define pUSB_TX_MAX_PACKET             ((uint16_t volatile *)USB_TX_MAX_PACKET) /* Maximum packet size for Host Tx endpoint */
#define bfin_read_USB_TX_MAX_PACKET()  bfin_read16(USB_TX_MAX_PACKET)
#define bfin_write_USB_TX_MAX_PACKET(val) bfin_write16(USB_TX_MAX_PACKET, val)
#define pUSB_CSR0                      ((uint16_t volatile *)USB_CSR0) /* Control Status register for endpoint 0 and Control Status register for Host Tx endpoint */
#define bfin_read_USB_CSR0()           bfin_read16(USB_CSR0)
#define bfin_write_USB_CSR0(val)       bfin_write16(USB_CSR0, val)
#define pUSB_TXCSR                     ((uint16_t volatile *)USB_TXCSR) /* Control Status register for endpoint 0 and Control Status register for Host Tx endpoint */
#define bfin_read_USB_TXCSR()          bfin_read16(USB_TXCSR)
#define bfin_write_USB_TXCSR(val)      bfin_write16(USB_TXCSR, val)
#define pUSB_RX_MAX_PACKET             ((uint16_t volatile *)USB_RX_MAX_PACKET) /* Maximum packet size for Host Rx endpoint */
#define bfin_read_USB_RX_MAX_PACKET()  bfin_read16(USB_RX_MAX_PACKET)
#define bfin_write_USB_RX_MAX_PACKET(val) bfin_write16(USB_RX_MAX_PACKET, val)
#define pUSB_RXCSR                     ((uint16_t volatile *)USB_RXCSR) /* Control Status register for Host Rx endpoint */
#define bfin_read_USB_RXCSR()          bfin_read16(USB_RXCSR)
#define bfin_write_USB_RXCSR(val)      bfin_write16(USB_RXCSR, val)
#define pUSB_COUNT0                    ((uint16_t volatile *)USB_COUNT0) /* Number of bytes received in endpoint 0 FIFO and Number of bytes received in Host Tx endpoint */
#define bfin_read_USB_COUNT0()         bfin_read16(USB_COUNT0)
#define bfin_write_USB_COUNT0(val)     bfin_write16(USB_COUNT0, val)
#define pUSB_RXCOUNT                   ((uint16_t volatile *)USB_RXCOUNT) /* Number of bytes received in endpoint 0 FIFO and Number of bytes received in Host Tx endpoint */
#define bfin_read_USB_RXCOUNT()        bfin_read16(USB_RXCOUNT)
#define bfin_write_USB_RXCOUNT(val)    bfin_write16(USB_RXCOUNT, val)
#define pUSB_TXTYPE                    ((uint16_t volatile *)USB_TXTYPE) /* Sets the transaction protocol and peripheral endpoint number for the Host Tx endpoint */
#define bfin_read_USB_TXTYPE()         bfin_read16(USB_TXTYPE)
#define bfin_write_USB_TXTYPE(val)     bfin_write16(USB_TXTYPE, val)
#define pUSB_NAKLIMIT0                 ((uint16_t volatile *)USB_NAKLIMIT0) /* Sets the NAK response timeout on Endpoint 0 and on Bulk transfers for Host Tx endpoint */
#define bfin_read_USB_NAKLIMIT0()      bfin_read16(USB_NAKLIMIT0)
#define bfin_write_USB_NAKLIMIT0(val)  bfin_write16(USB_NAKLIMIT0, val)
#define pUSB_TXINTERVAL                ((uint16_t volatile *)USB_TXINTERVAL) /* Sets the NAK response timeout on Endpoint 0 and on Bulk transfers for Host Tx endpoint */
#define bfin_read_USB_TXINTERVAL()     bfin_read16(USB_TXINTERVAL)
#define bfin_write_USB_TXINTERVAL(val) bfin_write16(USB_TXINTERVAL, val)
#define pUSB_RXTYPE                    ((uint16_t volatile *)USB_RXTYPE) /* Sets the transaction protocol and peripheral endpoint number for the Host Rx endpoint */
#define bfin_read_USB_RXTYPE()         bfin_read16(USB_RXTYPE)
#define bfin_write_USB_RXTYPE(val)     bfin_write16(USB_RXTYPE, val)
#define pUSB_RXINTERVAL                ((uint16_t volatile *)USB_RXINTERVAL) /* Sets the polling interval for Interrupt and Isochronous transfers or the NAK response timeout on Bulk transfers */
#define bfin_read_USB_RXINTERVAL()     bfin_read16(USB_RXINTERVAL)
#define bfin_write_USB_RXINTERVAL(val) bfin_write16(USB_RXINTERVAL, val)
#define pUSB_TXCOUNT                   ((uint16_t volatile *)USB_TXCOUNT) /* Number of bytes to be written to the selected endpoint Tx FIFO */
#define bfin_read_USB_TXCOUNT()        bfin_read16(USB_TXCOUNT)
#define bfin_write_USB_TXCOUNT(val)    bfin_write16(USB_TXCOUNT, val)
#define pUSB_EP0_FIFO                  ((uint16_t volatile *)USB_EP0_FIFO) /* Endpoint 0 FIFO */
#define bfin_read_USB_EP0_FIFO()       bfin_read16(USB_EP0_FIFO)
#define bfin_write_USB_EP0_FIFO(val)   bfin_write16(USB_EP0_FIFO, val)
#define pUSB_EP1_FIFO                  ((uint16_t volatile *)USB_EP1_FIFO) /* Endpoint 1 FIFO */
#define bfin_read_USB_EP1_FIFO()       bfin_read16(USB_EP1_FIFO)
#define bfin_write_USB_EP1_FIFO(val)   bfin_write16(USB_EP1_FIFO, val)
#define pUSB_EP2_FIFO                  ((uint16_t volatile *)USB_EP2_FIFO) /* Endpoint 2 FIFO */
#define bfin_read_USB_EP2_FIFO()       bfin_read16(USB_EP2_FIFO)
#define bfin_write_USB_EP2_FIFO(val)   bfin_write16(USB_EP2_FIFO, val)
#define pUSB_EP3_FIFO                  ((uint16_t volatile *)USB_EP3_FIFO) /* Endpoint 3 FIFO */
#define bfin_read_USB_EP3_FIFO()       bfin_read16(USB_EP3_FIFO)
#define bfin_write_USB_EP3_FIFO(val)   bfin_write16(USB_EP3_FIFO, val)
#define pUSB_EP4_FIFO                  ((uint16_t volatile *)USB_EP4_FIFO) /* Endpoint 4 FIFO */
#define bfin_read_USB_EP4_FIFO()       bfin_read16(USB_EP4_FIFO)
#define bfin_write_USB_EP4_FIFO(val)   bfin_write16(USB_EP4_FIFO, val)
#define pUSB_EP5_FIFO                  ((uint16_t volatile *)USB_EP5_FIFO) /* Endpoint 5 FIFO */
#define bfin_read_USB_EP5_FIFO()       bfin_read16(USB_EP5_FIFO)
#define bfin_write_USB_EP5_FIFO(val)   bfin_write16(USB_EP5_FIFO, val)
#define pUSB_EP6_FIFO                  ((uint16_t volatile *)USB_EP6_FIFO) /* Endpoint 6 FIFO */
#define bfin_read_USB_EP6_FIFO()       bfin_read16(USB_EP6_FIFO)
#define bfin_write_USB_EP6_FIFO(val)   bfin_write16(USB_EP6_FIFO, val)
#define pUSB_EP7_FIFO                  ((uint16_t volatile *)USB_EP7_FIFO) /* Endpoint 7 FIFO */
#define bfin_read_USB_EP7_FIFO()       bfin_read16(USB_EP7_FIFO)
#define bfin_write_USB_EP7_FIFO(val)   bfin_write16(USB_EP7_FIFO, val)
#define pUSB_OTG_DEV_CTL               ((uint16_t volatile *)USB_OTG_DEV_CTL) /* OTG Device Control Register */
#define bfin_read_USB_OTG_DEV_CTL()    bfin_read16(USB_OTG_DEV_CTL)
#define bfin_write_USB_OTG_DEV_CTL(val) bfin_write16(USB_OTG_DEV_CTL, val)
#define pUSB_OTG_VBUS_IRQ              ((uint16_t volatile *)USB_OTG_VBUS_IRQ) /* OTG VBUS Control Interrupts */
#define bfin_read_USB_OTG_VBUS_IRQ()   bfin_read16(USB_OTG_VBUS_IRQ)
#define bfin_write_USB_OTG_VBUS_IRQ(val) bfin_write16(USB_OTG_VBUS_IRQ, val)
#define pUSB_OTG_VBUS_MASK             ((uint16_t volatile *)USB_OTG_VBUS_MASK) /* VBUS Control Interrupt Enable */
#define bfin_read_USB_OTG_VBUS_MASK()  bfin_read16(USB_OTG_VBUS_MASK)
#define bfin_write_USB_OTG_VBUS_MASK(val) bfin_write16(USB_OTG_VBUS_MASK, val)
#define pUSB_LINKINFO                  ((uint16_t volatile *)USB_LINKINFO) /* Enables programming of some PHY-side delays */
#define bfin_read_USB_LINKINFO()       bfin_read16(USB_LINKINFO)
#define bfin_write_USB_LINKINFO(val)   bfin_write16(USB_LINKINFO, val)
#define pUSB_VPLEN                     ((uint16_t volatile *)USB_VPLEN) /* Determines duration of VBUS pulse for VBUS charging */
#define bfin_read_USB_VPLEN()          bfin_read16(USB_VPLEN)
#define bfin_write_USB_VPLEN(val)      bfin_write16(USB_VPLEN, val)
#define pUSB_HS_EOF1                   ((uint16_t volatile *)USB_HS_EOF1) /* Time buffer for High-Speed transactions */
#define bfin_read_USB_HS_EOF1()        bfin_read16(USB_HS_EOF1)
#define bfin_write_USB_HS_EOF1(val)    bfin_write16(USB_HS_EOF1, val)
#define pUSB_FS_EOF1                   ((uint16_t volatile *)USB_FS_EOF1) /* Time buffer for Full-Speed transactions */
#define bfin_read_USB_FS_EOF1()        bfin_read16(USB_FS_EOF1)
#define bfin_write_USB_FS_EOF1(val)    bfin_write16(USB_FS_EOF1, val)
#define pUSB_LS_EOF1                   ((uint16_t volatile *)USB_LS_EOF1) /* Time buffer for Low-Speed transactions */
#define bfin_read_USB_LS_EOF1()        bfin_read16(USB_LS_EOF1)
#define bfin_write_USB_LS_EOF1(val)    bfin_write16(USB_LS_EOF1, val)
#define pUSB_APHY_CNTRL                ((uint16_t volatile *)USB_APHY_CNTRL) /* Register that increases visibility of Analog PHY */
#define bfin_read_USB_APHY_CNTRL()     bfin_read16(USB_APHY_CNTRL)
#define bfin_write_USB_APHY_CNTRL(val) bfin_write16(USB_APHY_CNTRL, val)
#define pUSB_APHY_CALIB                ((uint16_t volatile *)USB_APHY_CALIB) /* Register used to set some calibration values */
#define bfin_read_USB_APHY_CALIB()     bfin_read16(USB_APHY_CALIB)
#define bfin_write_USB_APHY_CALIB(val) bfin_write16(USB_APHY_CALIB, val)
#define pUSB_APHY_CNTRL2               ((uint16_t volatile *)USB_APHY_CNTRL2) /* Register used to prevent re-enumeration once Moab goes into hibernate mode */
#define bfin_read_USB_APHY_CNTRL2()    bfin_read16(USB_APHY_CNTRL2)
#define bfin_write_USB_APHY_CNTRL2(val) bfin_write16(USB_APHY_CNTRL2, val)
#define pUSB_PHY_TEST                  ((uint16_t volatile *)USB_PHY_TEST) /* Used for reducing simulation time and simplifies FIFO testability */
#define bfin_read_USB_PHY_TEST()       bfin_read16(USB_PHY_TEST)
#define bfin_write_USB_PHY_TEST(val)   bfin_write16(USB_PHY_TEST, val)
#define pUSB_PLLOSC_CTRL               ((uint16_t volatile *)USB_PLLOSC_CTRL) /* Used to program different parameters for USB PLL and Oscillator */
#define bfin_read_USB_PLLOSC_CTRL()    bfin_read16(USB_PLLOSC_CTRL)
#define bfin_write_USB_PLLOSC_CTRL(val) bfin_write16(USB_PLLOSC_CTRL, val)
#define pUSB_SRP_CLKDIV                ((uint16_t volatile *)USB_SRP_CLKDIV) /* Used to program clock divide value for the clock fed to the SRP detection logic */
#define bfin_read_USB_SRP_CLKDIV()     bfin_read16(USB_SRP_CLKDIV)
#define bfin_write_USB_SRP_CLKDIV(val) bfin_write16(USB_SRP_CLKDIV, val)
#define pUSB_EP_NI0_TXMAXP             ((uint16_t volatile *)USB_EP_NI0_TXMAXP) /* Maximum packet size for Host Tx endpoint0 */
#define bfin_read_USB_EP_NI0_TXMAXP()  bfin_read16(USB_EP_NI0_TXMAXP)
#define bfin_write_USB_EP_NI0_TXMAXP(val) bfin_write16(USB_EP_NI0_TXMAXP, val)
#define pUSB_EP_NI0_TXCSR              ((uint16_t volatile *)USB_EP_NI0_TXCSR) /* Control Status register for endpoint 0 */
#define bfin_read_USB_EP_NI0_TXCSR()   bfin_read16(USB_EP_NI0_TXCSR)
#define bfin_write_USB_EP_NI0_TXCSR(val) bfin_write16(USB_EP_NI0_TXCSR, val)
#define pUSB_EP_NI0_RXMAXP             ((uint16_t volatile *)USB_EP_NI0_RXMAXP) /* Maximum packet size for Host Rx endpoint0 */
#define bfin_read_USB_EP_NI0_RXMAXP()  bfin_read16(USB_EP_NI0_RXMAXP)
#define bfin_write_USB_EP_NI0_RXMAXP(val) bfin_write16(USB_EP_NI0_RXMAXP, val)
#define pUSB_EP_NI0_RXCSR              ((uint16_t volatile *)USB_EP_NI0_RXCSR) /* Control Status register for Host Rx endpoint0 */
#define bfin_read_USB_EP_NI0_RXCSR()   bfin_read16(USB_EP_NI0_RXCSR)
#define bfin_write_USB_EP_NI0_RXCSR(val) bfin_write16(USB_EP_NI0_RXCSR, val)
#define pUSB_EP_NI0_RXCOUNT            ((uint16_t volatile *)USB_EP_NI0_RXCOUNT) /* Number of bytes received in endpoint 0 FIFO */
#define bfin_read_USB_EP_NI0_RXCOUNT() bfin_read16(USB_EP_NI0_RXCOUNT)
#define bfin_write_USB_EP_NI0_RXCOUNT(val) bfin_write16(USB_EP_NI0_RXCOUNT, val)
#define pUSB_EP_NI0_TXTYPE             ((uint16_t volatile *)USB_EP_NI0_TXTYPE) /* Sets the transaction protocol and peripheral endpoint number for the Host Tx endpoint0 */
#define bfin_read_USB_EP_NI0_TXTYPE()  bfin_read16(USB_EP_NI0_TXTYPE)
#define bfin_write_USB_EP_NI0_TXTYPE(val) bfin_write16(USB_EP_NI0_TXTYPE, val)
#define pUSB_EP_NI0_TXINTERVAL         ((uint16_t volatile *)USB_EP_NI0_TXINTERVAL) /* Sets the NAK response timeout on Endpoint 0 */
#define bfin_read_USB_EP_NI0_TXINTERVAL() bfin_read16(USB_EP_NI0_TXINTERVAL)
#define bfin_write_USB_EP_NI0_TXINTERVAL(val) bfin_write16(USB_EP_NI0_TXINTERVAL, val)
#define pUSB_EP_NI0_RXTYPE             ((uint16_t volatile *)USB_EP_NI0_RXTYPE) /* Sets the transaction protocol and peripheral endpoint number for the Host Rx endpoint0 */
#define bfin_read_USB_EP_NI0_RXTYPE()  bfin_read16(USB_EP_NI0_RXTYPE)
#define bfin_write_USB_EP_NI0_RXTYPE(val) bfin_write16(USB_EP_NI0_RXTYPE, val)
#define pUSB_EP_NI0_RXINTERVAL         ((uint16_t volatile *)USB_EP_NI0_RXINTERVAL) /* Sets the polling interval for Interrupt/Isochronous transfers or the NAK response timeout on Bulk transfers for Host Rx endpoint0 */
#define bfin_read_USB_EP_NI0_RXINTERVAL() bfin_read16(USB_EP_NI0_RXINTERVAL)
#define bfin_write_USB_EP_NI0_RXINTERVAL(val) bfin_write16(USB_EP_NI0_RXINTERVAL, val)
#define pUSB_EP_NI0_TXCOUNT            ((uint16_t volatile *)USB_EP_NI0_TXCOUNT) /* Number of bytes to be written to the endpoint0 Tx FIFO */
#define bfin_read_USB_EP_NI0_TXCOUNT() bfin_read16(USB_EP_NI0_TXCOUNT)
#define bfin_write_USB_EP_NI0_TXCOUNT(val) bfin_write16(USB_EP_NI0_TXCOUNT, val)
#define pUSB_EP_NI1_TXMAXP             ((uint16_t volatile *)USB_EP_NI1_TXMAXP) /* Maximum packet size for Host Tx endpoint1 */
#define bfin_read_USB_EP_NI1_TXMAXP()  bfin_read16(USB_EP_NI1_TXMAXP)
#define bfin_write_USB_EP_NI1_TXMAXP(val) bfin_write16(USB_EP_NI1_TXMAXP, val)
#define pUSB_EP_NI1_TXCSR              ((uint16_t volatile *)USB_EP_NI1_TXCSR) /* Control Status register for endpoint1 */
#define bfin_read_USB_EP_NI1_TXCSR()   bfin_read16(USB_EP_NI1_TXCSR)
#define bfin_write_USB_EP_NI1_TXCSR(val) bfin_write16(USB_EP_NI1_TXCSR, val)
#define pUSB_EP_NI1_RXMAXP             ((uint16_t volatile *)USB_EP_NI1_RXMAXP) /* Maximum packet size for Host Rx endpoint1 */
#define bfin_read_USB_EP_NI1_RXMAXP()  bfin_read16(USB_EP_NI1_RXMAXP)
#define bfin_write_USB_EP_NI1_RXMAXP(val) bfin_write16(USB_EP_NI1_RXMAXP, val)
#define pUSB_EP_NI1_RXCSR              ((uint16_t volatile *)USB_EP_NI1_RXCSR) /* Control Status register for Host Rx endpoint1 */
#define bfin_read_USB_EP_NI1_RXCSR()   bfin_read16(USB_EP_NI1_RXCSR)
#define bfin_write_USB_EP_NI1_RXCSR(val) bfin_write16(USB_EP_NI1_RXCSR, val)
#define pUSB_EP_NI1_RXCOUNT            ((uint16_t volatile *)USB_EP_NI1_RXCOUNT) /* Number of bytes received in endpoint1 FIFO */
#define bfin_read_USB_EP_NI1_RXCOUNT() bfin_read16(USB_EP_NI1_RXCOUNT)
#define bfin_write_USB_EP_NI1_RXCOUNT(val) bfin_write16(USB_EP_NI1_RXCOUNT, val)
#define pUSB_EP_NI1_TXTYPE             ((uint16_t volatile *)USB_EP_NI1_TXTYPE) /* Sets the transaction protocol and peripheral endpoint number for the Host Tx endpoint1 */
#define bfin_read_USB_EP_NI1_TXTYPE()  bfin_read16(USB_EP_NI1_TXTYPE)
#define bfin_write_USB_EP_NI1_TXTYPE(val) bfin_write16(USB_EP_NI1_TXTYPE, val)
#define pUSB_EP_NI1_TXINTERVAL         ((uint16_t volatile *)USB_EP_NI1_TXINTERVAL) /* Sets the NAK response timeout on Endpoint1 */
#define bfin_read_USB_EP_NI1_TXINTERVAL() bfin_read16(USB_EP_NI1_TXINTERVAL)
#define bfin_write_USB_EP_NI1_TXINTERVAL(val) bfin_write16(USB_EP_NI1_TXINTERVAL, val)
#define pUSB_EP_NI1_RXTYPE             ((uint16_t volatile *)USB_EP_NI1_RXTYPE) /* Sets the transaction protocol and peripheral endpoint number for the Host Rx endpoint1 */
#define bfin_read_USB_EP_NI1_RXTYPE()  bfin_read16(USB_EP_NI1_RXTYPE)
#define bfin_write_USB_EP_NI1_RXTYPE(val) bfin_write16(USB_EP_NI1_RXTYPE, val)
#define pUSB_EP_NI1_RXINTERVAL         ((uint16_t volatile *)USB_EP_NI1_RXINTERVAL) /* Sets the polling interval for Interrupt/Isochronous transfers or the NAK response timeout on Bulk transfers for Host Rx endpoint1 */
#define bfin_read_USB_EP_NI1_RXINTERVAL() bfin_read16(USB_EP_NI1_RXINTERVAL)
#define bfin_write_USB_EP_NI1_RXINTERVAL(val) bfin_write16(USB_EP_NI1_RXINTERVAL, val)
#define pUSB_EP_NI1_TXCOUNT            ((uint16_t volatile *)USB_EP_NI1_TXCOUNT) /* Number of bytes to be written to the+H102 endpoint1 Tx FIFO */
#define bfin_read_USB_EP_NI1_TXCOUNT() bfin_read16(USB_EP_NI1_TXCOUNT)
#define bfin_write_USB_EP_NI1_TXCOUNT(val) bfin_write16(USB_EP_NI1_TXCOUNT, val)
#define pUSB_EP_NI2_TXMAXP             ((uint16_t volatile *)USB_EP_NI2_TXMAXP) /* Maximum packet size for Host Tx endpoint2 */
#define bfin_read_USB_EP_NI2_TXMAXP()  bfin_read16(USB_EP_NI2_TXMAXP)
#define bfin_write_USB_EP_NI2_TXMAXP(val) bfin_write16(USB_EP_NI2_TXMAXP, val)
#define pUSB_EP_NI2_TXCSR              ((uint16_t volatile *)USB_EP_NI2_TXCSR) /* Control Status register for endpoint2 */
#define bfin_read_USB_EP_NI2_TXCSR()   bfin_read16(USB_EP_NI2_TXCSR)
#define bfin_write_USB_EP_NI2_TXCSR(val) bfin_write16(USB_EP_NI2_TXCSR, val)
#define pUSB_EP_NI2_RXMAXP             ((uint16_t volatile *)USB_EP_NI2_RXMAXP) /* Maximum packet size for Host Rx endpoint2 */
#define bfin_read_USB_EP_NI2_RXMAXP()  bfin_read16(USB_EP_NI2_RXMAXP)
#define bfin_write_USB_EP_NI2_RXMAXP(val) bfin_write16(USB_EP_NI2_RXMAXP, val)
#define pUSB_EP_NI2_RXCSR              ((uint16_t volatile *)USB_EP_NI2_RXCSR) /* Control Status register for Host Rx endpoint2 */
#define bfin_read_USB_EP_NI2_RXCSR()   bfin_read16(USB_EP_NI2_RXCSR)
#define bfin_write_USB_EP_NI2_RXCSR(val) bfin_write16(USB_EP_NI2_RXCSR, val)
#define pUSB_EP_NI2_RXCOUNT            ((uint16_t volatile *)USB_EP_NI2_RXCOUNT) /* Number of bytes received in endpoint2 FIFO */
#define bfin_read_USB_EP_NI2_RXCOUNT() bfin_read16(USB_EP_NI2_RXCOUNT)
#define bfin_write_USB_EP_NI2_RXCOUNT(val) bfin_write16(USB_EP_NI2_RXCOUNT, val)
#define pUSB_EP_NI2_TXTYPE             ((uint16_t volatile *)USB_EP_NI2_TXTYPE) /* Sets the transaction protocol and peripheral endpoint number for the Host Tx endpoint2 */
#define bfin_read_USB_EP_NI2_TXTYPE()  bfin_read16(USB_EP_NI2_TXTYPE)
#define bfin_write_USB_EP_NI2_TXTYPE(val) bfin_write16(USB_EP_NI2_TXTYPE, val)
#define pUSB_EP_NI2_TXINTERVAL         ((uint16_t volatile *)USB_EP_NI2_TXINTERVAL) /* Sets the NAK response timeout on Endpoint2 */
#define bfin_read_USB_EP_NI2_TXINTERVAL() bfin_read16(USB_EP_NI2_TXINTERVAL)
#define bfin_write_USB_EP_NI2_TXINTERVAL(val) bfin_write16(USB_EP_NI2_TXINTERVAL, val)
#define pUSB_EP_NI2_RXTYPE             ((uint16_t volatile *)USB_EP_NI2_RXTYPE) /* Sets the transaction protocol and peripheral endpoint number for the Host Rx endpoint2 */
#define bfin_read_USB_EP_NI2_RXTYPE()  bfin_read16(USB_EP_NI2_RXTYPE)
#define bfin_write_USB_EP_NI2_RXTYPE(val) bfin_write16(USB_EP_NI2_RXTYPE, val)
#define pUSB_EP_NI2_RXINTERVAL         ((uint16_t volatile *)USB_EP_NI2_RXINTERVAL) /* Sets the polling interval for Interrupt/Isochronous transfers or the NAK response timeout on Bulk transfers for Host Rx endpoint2 */
#define bfin_read_USB_EP_NI2_RXINTERVAL() bfin_read16(USB_EP_NI2_RXINTERVAL)
#define bfin_write_USB_EP_NI2_RXINTERVAL(val) bfin_write16(USB_EP_NI2_RXINTERVAL, val)
#define pUSB_EP_NI2_TXCOUNT            ((uint16_t volatile *)USB_EP_NI2_TXCOUNT) /* Number of bytes to be written to the endpoint2 Tx FIFO */
#define bfin_read_USB_EP_NI2_TXCOUNT() bfin_read16(USB_EP_NI2_TXCOUNT)
#define bfin_write_USB_EP_NI2_TXCOUNT(val) bfin_write16(USB_EP_NI2_TXCOUNT, val)
#define pUSB_EP_NI3_TXMAXP             ((uint16_t volatile *)USB_EP_NI3_TXMAXP) /* Maximum packet size for Host Tx endpoint3 */
#define bfin_read_USB_EP_NI3_TXMAXP()  bfin_read16(USB_EP_NI3_TXMAXP)
#define bfin_write_USB_EP_NI3_TXMAXP(val) bfin_write16(USB_EP_NI3_TXMAXP, val)
#define pUSB_EP_NI3_TXCSR              ((uint16_t volatile *)USB_EP_NI3_TXCSR) /* Control Status register for endpoint3 */
#define bfin_read_USB_EP_NI3_TXCSR()   bfin_read16(USB_EP_NI3_TXCSR)
#define bfin_write_USB_EP_NI3_TXCSR(val) bfin_write16(USB_EP_NI3_TXCSR, val)
#define pUSB_EP_NI3_RXMAXP             ((uint16_t volatile *)USB_EP_NI3_RXMAXP) /* Maximum packet size for Host Rx endpoint3 */
#define bfin_read_USB_EP_NI3_RXMAXP()  bfin_read16(USB_EP_NI3_RXMAXP)
#define bfin_write_USB_EP_NI3_RXMAXP(val) bfin_write16(USB_EP_NI3_RXMAXP, val)
#define pUSB_EP_NI3_RXCSR              ((uint16_t volatile *)USB_EP_NI3_RXCSR) /* Control Status register for Host Rx endpoint3 */
#define bfin_read_USB_EP_NI3_RXCSR()   bfin_read16(USB_EP_NI3_RXCSR)
#define bfin_write_USB_EP_NI3_RXCSR(val) bfin_write16(USB_EP_NI3_RXCSR, val)
#define pUSB_EP_NI3_RXCOUNT            ((uint16_t volatile *)USB_EP_NI3_RXCOUNT) /* Number of bytes received in endpoint3 FIFO */
#define bfin_read_USB_EP_NI3_RXCOUNT() bfin_read16(USB_EP_NI3_RXCOUNT)
#define bfin_write_USB_EP_NI3_RXCOUNT(val) bfin_write16(USB_EP_NI3_RXCOUNT, val)
#define pUSB_EP_NI3_TXTYPE             ((uint16_t volatile *)USB_EP_NI3_TXTYPE) /* Sets the transaction protocol and peripheral endpoint number for the Host Tx endpoint3 */
#define bfin_read_USB_EP_NI3_TXTYPE()  bfin_read16(USB_EP_NI3_TXTYPE)
#define bfin_write_USB_EP_NI3_TXTYPE(val) bfin_write16(USB_EP_NI3_TXTYPE, val)
#define pUSB_EP_NI3_TXINTERVAL         ((uint16_t volatile *)USB_EP_NI3_TXINTERVAL) /* Sets the NAK response timeout on Endpoint3 */
#define bfin_read_USB_EP_NI3_TXINTERVAL() bfin_read16(USB_EP_NI3_TXINTERVAL)
#define bfin_write_USB_EP_NI3_TXINTERVAL(val) bfin_write16(USB_EP_NI3_TXINTERVAL, val)
#define pUSB_EP_NI3_RXTYPE             ((uint16_t volatile *)USB_EP_NI3_RXTYPE) /* Sets the transaction protocol and peripheral endpoint number for the Host Rx endpoint3 */
#define bfin_read_USB_EP_NI3_RXTYPE()  bfin_read16(USB_EP_NI3_RXTYPE)
#define bfin_write_USB_EP_NI3_RXTYPE(val) bfin_write16(USB_EP_NI3_RXTYPE, val)
#define pUSB_EP_NI3_RXINTERVAL         ((uint16_t volatile *)USB_EP_NI3_RXINTERVAL) /* Sets the polling interval for Interrupt/Isochronous transfers or the NAK response timeout on Bulk transfers for Host Rx endpoint3 */
#define bfin_read_USB_EP_NI3_RXINTERVAL() bfin_read16(USB_EP_NI3_RXINTERVAL)
#define bfin_write_USB_EP_NI3_RXINTERVAL(val) bfin_write16(USB_EP_NI3_RXINTERVAL, val)
#define pUSB_EP_NI3_TXCOUNT            ((uint16_t volatile *)USB_EP_NI3_TXCOUNT) /* Number of bytes to be written to the H124endpoint3 Tx FIFO */
#define bfin_read_USB_EP_NI3_TXCOUNT() bfin_read16(USB_EP_NI3_TXCOUNT)
#define bfin_write_USB_EP_NI3_TXCOUNT(val) bfin_write16(USB_EP_NI3_TXCOUNT, val)
#define pUSB_EP_NI4_TXMAXP             ((uint16_t volatile *)USB_EP_NI4_TXMAXP) /* Maximum packet size for Host Tx endpoint4 */
#define bfin_read_USB_EP_NI4_TXMAXP()  bfin_read16(USB_EP_NI4_TXMAXP)
#define bfin_write_USB_EP_NI4_TXMAXP(val) bfin_write16(USB_EP_NI4_TXMAXP, val)
#define pUSB_EP_NI4_TXCSR              ((uint16_t volatile *)USB_EP_NI4_TXCSR) /* Control Status register for endpoint4 */
#define bfin_read_USB_EP_NI4_TXCSR()   bfin_read16(USB_EP_NI4_TXCSR)
#define bfin_write_USB_EP_NI4_TXCSR(val) bfin_write16(USB_EP_NI4_TXCSR, val)
#define pUSB_EP_NI4_RXMAXP             ((uint16_t volatile *)USB_EP_NI4_RXMAXP) /* Maximum packet size for Host Rx endpoint4 */
#define bfin_read_USB_EP_NI4_RXMAXP()  bfin_read16(USB_EP_NI4_RXMAXP)
#define bfin_write_USB_EP_NI4_RXMAXP(val) bfin_write16(USB_EP_NI4_RXMAXP, val)
#define pUSB_EP_NI4_RXCSR              ((uint16_t volatile *)USB_EP_NI4_RXCSR) /* Control Status register for Host Rx endpoint4 */
#define bfin_read_USB_EP_NI4_RXCSR()   bfin_read16(USB_EP_NI4_RXCSR)
#define bfin_write_USB_EP_NI4_RXCSR(val) bfin_write16(USB_EP_NI4_RXCSR, val)
#define pUSB_EP_NI4_RXCOUNT            ((uint16_t volatile *)USB_EP_NI4_RXCOUNT) /* Number of bytes received in endpoint4 FIFO */
#define bfin_read_USB_EP_NI4_RXCOUNT() bfin_read16(USB_EP_NI4_RXCOUNT)
#define bfin_write_USB_EP_NI4_RXCOUNT(val) bfin_write16(USB_EP_NI4_RXCOUNT, val)
#define pUSB_EP_NI4_TXTYPE             ((uint16_t volatile *)USB_EP_NI4_TXTYPE) /* Sets the transaction protocol and peripheral endpoint number for the Host Tx endpoint4 */
#define bfin_read_USB_EP_NI4_TXTYPE()  bfin_read16(USB_EP_NI4_TXTYPE)
#define bfin_write_USB_EP_NI4_TXTYPE(val) bfin_write16(USB_EP_NI4_TXTYPE, val)
#define pUSB_EP_NI4_TXINTERVAL         ((uint16_t volatile *)USB_EP_NI4_TXINTERVAL) /* Sets the NAK response timeout on Endpoint4 */
#define bfin_read_USB_EP_NI4_TXINTERVAL() bfin_read16(USB_EP_NI4_TXINTERVAL)
#define bfin_write_USB_EP_NI4_TXINTERVAL(val) bfin_write16(USB_EP_NI4_TXINTERVAL, val)
#define pUSB_EP_NI4_RXTYPE             ((uint16_t volatile *)USB_EP_NI4_RXTYPE) /* Sets the transaction protocol and peripheral endpoint number for the Host Rx endpoint4 */
#define bfin_read_USB_EP_NI4_RXTYPE()  bfin_read16(USB_EP_NI4_RXTYPE)
#define bfin_write_USB_EP_NI4_RXTYPE(val) bfin_write16(USB_EP_NI4_RXTYPE, val)
#define pUSB_EP_NI4_RXINTERVAL         ((uint16_t volatile *)USB_EP_NI4_RXINTERVAL) /* Sets the polling interval for Interrupt/Isochronous transfers or the NAK response timeout on Bulk transfers for Host Rx endpoint4 */
#define bfin_read_USB_EP_NI4_RXINTERVAL() bfin_read16(USB_EP_NI4_RXINTERVAL)
#define bfin_write_USB_EP_NI4_RXINTERVAL(val) bfin_write16(USB_EP_NI4_RXINTERVAL, val)
#define pUSB_EP_NI4_TXCOUNT            ((uint16_t volatile *)USB_EP_NI4_TXCOUNT) /* Number of bytes to be written to the endpoint4 Tx FIFO */
#define bfin_read_USB_EP_NI4_TXCOUNT() bfin_read16(USB_EP_NI4_TXCOUNT)
#define bfin_write_USB_EP_NI4_TXCOUNT(val) bfin_write16(USB_EP_NI4_TXCOUNT, val)
#define pUSB_EP_NI5_TXMAXP             ((uint16_t volatile *)USB_EP_NI5_TXMAXP) /* Maximum packet size for Host Tx endpoint5 */
#define bfin_read_USB_EP_NI5_TXMAXP()  bfin_read16(USB_EP_NI5_TXMAXP)
#define bfin_write_USB_EP_NI5_TXMAXP(val) bfin_write16(USB_EP_NI5_TXMAXP, val)
#define pUSB_EP_NI5_TXCSR              ((uint16_t volatile *)USB_EP_NI5_TXCSR) /* Control Status register for endpoint5 */
#define bfin_read_USB_EP_NI5_TXCSR()   bfin_read16(USB_EP_NI5_TXCSR)
#define bfin_write_USB_EP_NI5_TXCSR(val) bfin_write16(USB_EP_NI5_TXCSR, val)
#define pUSB_EP_NI5_RXMAXP             ((uint16_t volatile *)USB_EP_NI5_RXMAXP) /* Maximum packet size for Host Rx endpoint5 */
#define bfin_read_USB_EP_NI5_RXMAXP()  bfin_read16(USB_EP_NI5_RXMAXP)
#define bfin_write_USB_EP_NI5_RXMAXP(val) bfin_write16(USB_EP_NI5_RXMAXP, val)
#define pUSB_EP_NI5_RXCSR              ((uint16_t volatile *)USB_EP_NI5_RXCSR) /* Control Status register for Host Rx endpoint5 */
#define bfin_read_USB_EP_NI5_RXCSR()   bfin_read16(USB_EP_NI5_RXCSR)
#define bfin_write_USB_EP_NI5_RXCSR(val) bfin_write16(USB_EP_NI5_RXCSR, val)
#define pUSB_EP_NI5_RXCOUNT            ((uint16_t volatile *)USB_EP_NI5_RXCOUNT) /* Number of bytes received in endpoint5 FIFO */
#define bfin_read_USB_EP_NI5_RXCOUNT() bfin_read16(USB_EP_NI5_RXCOUNT)
#define bfin_write_USB_EP_NI5_RXCOUNT(val) bfin_write16(USB_EP_NI5_RXCOUNT, val)
#define pUSB_EP_NI5_TXTYPE             ((uint16_t volatile *)USB_EP_NI5_TXTYPE) /* Sets the transaction protocol and peripheral endpoint number for the Host Tx endpoint5 */
#define bfin_read_USB_EP_NI5_TXTYPE()  bfin_read16(USB_EP_NI5_TXTYPE)
#define bfin_write_USB_EP_NI5_TXTYPE(val) bfin_write16(USB_EP_NI5_TXTYPE, val)
#define pUSB_EP_NI5_TXINTERVAL         ((uint16_t volatile *)USB_EP_NI5_TXINTERVAL) /* Sets the NAK response timeout on Endpoint5 */
#define bfin_read_USB_EP_NI5_TXINTERVAL() bfin_read16(USB_EP_NI5_TXINTERVAL)
#define bfin_write_USB_EP_NI5_TXINTERVAL(val) bfin_write16(USB_EP_NI5_TXINTERVAL, val)
#define pUSB_EP_NI5_RXTYPE             ((uint16_t volatile *)USB_EP_NI5_RXTYPE) /* Sets the transaction protocol and peripheral endpoint number for the Host Rx endpoint5 */
#define bfin_read_USB_EP_NI5_RXTYPE()  bfin_read16(USB_EP_NI5_RXTYPE)
#define bfin_write_USB_EP_NI5_RXTYPE(val) bfin_write16(USB_EP_NI5_RXTYPE, val)
#define pUSB_EP_NI5_RXINTERVAL         ((uint16_t volatile *)USB_EP_NI5_RXINTERVAL) /* Sets the polling interval for Interrupt/Isochronous transfers or the NAK response timeout on Bulk transfers for Host Rx endpoint5 */
#define bfin_read_USB_EP_NI5_RXINTERVAL() bfin_read16(USB_EP_NI5_RXINTERVAL)
#define bfin_write_USB_EP_NI5_RXINTERVAL(val) bfin_write16(USB_EP_NI5_RXINTERVAL, val)
#define pUSB_EP_NI5_TXCOUNT            ((uint16_t volatile *)USB_EP_NI5_TXCOUNT) /* Number of bytes to be written to the endpoint5 Tx FIFO */
#define bfin_read_USB_EP_NI5_TXCOUNT() bfin_read16(USB_EP_NI5_TXCOUNT)
#define bfin_write_USB_EP_NI5_TXCOUNT(val) bfin_write16(USB_EP_NI5_TXCOUNT, val)
#define pUSB_EP_NI6_TXMAXP             ((uint16_t volatile *)USB_EP_NI6_TXMAXP) /* Maximum packet size for Host Tx endpoint6 */
#define bfin_read_USB_EP_NI6_TXMAXP()  bfin_read16(USB_EP_NI6_TXMAXP)
#define bfin_write_USB_EP_NI6_TXMAXP(val) bfin_write16(USB_EP_NI6_TXMAXP, val)
#define pUSB_EP_NI6_TXCSR              ((uint16_t volatile *)USB_EP_NI6_TXCSR) /* Control Status register for endpoint6 */
#define bfin_read_USB_EP_NI6_TXCSR()   bfin_read16(USB_EP_NI6_TXCSR)
#define bfin_write_USB_EP_NI6_TXCSR(val) bfin_write16(USB_EP_NI6_TXCSR, val)
#define pUSB_EP_NI6_RXMAXP             ((uint16_t volatile *)USB_EP_NI6_RXMAXP) /* Maximum packet size for Host Rx endpoint6 */
#define bfin_read_USB_EP_NI6_RXMAXP()  bfin_read16(USB_EP_NI6_RXMAXP)
#define bfin_write_USB_EP_NI6_RXMAXP(val) bfin_write16(USB_EP_NI6_RXMAXP, val)
#define pUSB_EP_NI6_RXCSR              ((uint16_t volatile *)USB_EP_NI6_RXCSR) /* Control Status register for Host Rx endpoint6 */
#define bfin_read_USB_EP_NI6_RXCSR()   bfin_read16(USB_EP_NI6_RXCSR)
#define bfin_write_USB_EP_NI6_RXCSR(val) bfin_write16(USB_EP_NI6_RXCSR, val)
#define pUSB_EP_NI6_RXCOUNT            ((uint16_t volatile *)USB_EP_NI6_RXCOUNT) /* Number of bytes received in endpoint6 FIFO */
#define bfin_read_USB_EP_NI6_RXCOUNT() bfin_read16(USB_EP_NI6_RXCOUNT)
#define bfin_write_USB_EP_NI6_RXCOUNT(val) bfin_write16(USB_EP_NI6_RXCOUNT, val)
#define pUSB_EP_NI6_TXTYPE             ((uint16_t volatile *)USB_EP_NI6_TXTYPE) /* Sets the transaction protocol and peripheral endpoint number for the Host Tx endpoint6 */
#define bfin_read_USB_EP_NI6_TXTYPE()  bfin_read16(USB_EP_NI6_TXTYPE)
#define bfin_write_USB_EP_NI6_TXTYPE(val) bfin_write16(USB_EP_NI6_TXTYPE, val)
#define pUSB_EP_NI6_TXINTERVAL         ((uint16_t volatile *)USB_EP_NI6_TXINTERVAL) /* Sets the NAK response timeout on Endpoint6 */
#define bfin_read_USB_EP_NI6_TXINTERVAL() bfin_read16(USB_EP_NI6_TXINTERVAL)
#define bfin_write_USB_EP_NI6_TXINTERVAL(val) bfin_write16(USB_EP_NI6_TXINTERVAL, val)
#define pUSB_EP_NI6_RXTYPE             ((uint16_t volatile *)USB_EP_NI6_RXTYPE) /* Sets the transaction protocol and peripheral endpoint number for the Host Rx endpoint6 */
#define bfin_read_USB_EP_NI6_RXTYPE()  bfin_read16(USB_EP_NI6_RXTYPE)
#define bfin_write_USB_EP_NI6_RXTYPE(val) bfin_write16(USB_EP_NI6_RXTYPE, val)
#define pUSB_EP_NI6_RXINTERVAL         ((uint16_t volatile *)USB_EP_NI6_RXINTERVAL) /* Sets the polling interval for Interrupt/Isochronous transfers or the NAK response timeout on Bulk transfers for Host Rx endpoint6 */
#define bfin_read_USB_EP_NI6_RXINTERVAL() bfin_read16(USB_EP_NI6_RXINTERVAL)
#define bfin_write_USB_EP_NI6_RXINTERVAL(val) bfin_write16(USB_EP_NI6_RXINTERVAL, val)
#define pUSB_EP_NI6_TXCOUNT            ((uint16_t volatile *)USB_EP_NI6_TXCOUNT) /* Number of bytes to be written to the endpoint6 Tx FIFO */
#define bfin_read_USB_EP_NI6_TXCOUNT() bfin_read16(USB_EP_NI6_TXCOUNT)
#define bfin_write_USB_EP_NI6_TXCOUNT(val) bfin_write16(USB_EP_NI6_TXCOUNT, val)
#define pUSB_EP_NI7_TXMAXP             ((uint16_t volatile *)USB_EP_NI7_TXMAXP) /* Maximum packet size for Host Tx endpoint7 */
#define bfin_read_USB_EP_NI7_TXMAXP()  bfin_read16(USB_EP_NI7_TXMAXP)
#define bfin_write_USB_EP_NI7_TXMAXP(val) bfin_write16(USB_EP_NI7_TXMAXP, val)
#define pUSB_EP_NI7_TXCSR              ((uint16_t volatile *)USB_EP_NI7_TXCSR) /* Control Status register for endpoint7 */
#define bfin_read_USB_EP_NI7_TXCSR()   bfin_read16(USB_EP_NI7_TXCSR)
#define bfin_write_USB_EP_NI7_TXCSR(val) bfin_write16(USB_EP_NI7_TXCSR, val)
#define pUSB_EP_NI7_RXMAXP             ((uint16_t volatile *)USB_EP_NI7_RXMAXP) /* Maximum packet size for Host Rx endpoint7 */
#define bfin_read_USB_EP_NI7_RXMAXP()  bfin_read16(USB_EP_NI7_RXMAXP)
#define bfin_write_USB_EP_NI7_RXMAXP(val) bfin_write16(USB_EP_NI7_RXMAXP, val)
#define pUSB_EP_NI7_RXCSR              ((uint16_t volatile *)USB_EP_NI7_RXCSR) /* Control Status register for Host Rx endpoint7 */
#define bfin_read_USB_EP_NI7_RXCSR()   bfin_read16(USB_EP_NI7_RXCSR)
#define bfin_write_USB_EP_NI7_RXCSR(val) bfin_write16(USB_EP_NI7_RXCSR, val)
#define pUSB_EP_NI7_RXCOUNT            ((uint16_t volatile *)USB_EP_NI7_RXCOUNT) /* Number of bytes received in endpoint7 FIFO */
#define bfin_read_USB_EP_NI7_RXCOUNT() bfin_read16(USB_EP_NI7_RXCOUNT)
#define bfin_write_USB_EP_NI7_RXCOUNT(val) bfin_write16(USB_EP_NI7_RXCOUNT, val)
#define pUSB_EP_NI7_TXTYPE             ((uint16_t volatile *)USB_EP_NI7_TXTYPE) /* Sets the transaction protocol and peripheral endpoint number for the Host Tx endpoint7 */
#define bfin_read_USB_EP_NI7_TXTYPE()  bfin_read16(USB_EP_NI7_TXTYPE)
#define bfin_write_USB_EP_NI7_TXTYPE(val) bfin_write16(USB_EP_NI7_TXTYPE, val)
#define pUSB_EP_NI7_TXINTERVAL         ((uint16_t volatile *)USB_EP_NI7_TXINTERVAL) /* Sets the NAK response timeout on Endpoint7 */
#define bfin_read_USB_EP_NI7_TXINTERVAL() bfin_read16(USB_EP_NI7_TXINTERVAL)
#define bfin_write_USB_EP_NI7_TXINTERVAL(val) bfin_write16(USB_EP_NI7_TXINTERVAL, val)
#define pUSB_EP_NI7_RXTYPE             ((uint16_t volatile *)USB_EP_NI7_RXTYPE) /* Sets the transaction protocol and peripheral endpoint number for the Host Rx endpoint7 */
#define bfin_read_USB_EP_NI7_RXTYPE()  bfin_read16(USB_EP_NI7_RXTYPE)
#define bfin_write_USB_EP_NI7_RXTYPE(val) bfin_write16(USB_EP_NI7_RXTYPE, val)
#define pUSB_EP_NI7_RXINTERVAL         ((uint16_t volatile *)USB_EP_NI7_RXINTERVAL) /* Sets the polling interval for Interrupt/Isochronous transfers or the NAK response timeout on Bulk transfers for Host Rx endpoint7 */
#define bfin_read_USB_EP_NI7_RXINTERVAL() bfin_read16(USB_EP_NI7_RXINTERVAL)
#define bfin_write_USB_EP_NI7_RXINTERVAL(val) bfin_write16(USB_EP_NI7_RXINTERVAL, val)
#define pUSB_EP_NI7_TXCOUNT            ((uint16_t volatile *)USB_EP_NI7_TXCOUNT) /* Number of bytes to be written to the endpoint7 Tx FIFO */
#define bfin_read_USB_EP_NI7_TXCOUNT() bfin_read16(USB_EP_NI7_TXCOUNT)
#define bfin_write_USB_EP_NI7_TXCOUNT(val) bfin_write16(USB_EP_NI7_TXCOUNT, val)
#define pUSB_DMA_INTERRUPT             ((uint16_t volatile *)USB_DMA_INTERRUPT) /* Indicates pending interrupts for the DMA channels */
#define bfin_read_USB_DMA_INTERRUPT()  bfin_read16(USB_DMA_INTERRUPT)
#define bfin_write_USB_DMA_INTERRUPT(val) bfin_write16(USB_DMA_INTERRUPT, val)
#define pUSB_DMA0_CONTROL              ((uint16_t volatile *)USB_DMA0_CONTROL) /* DMA master channel 0 configuration */
#define bfin_read_USB_DMA0_CONTROL()   bfin_read16(USB_DMA0_CONTROL)
#define bfin_write_USB_DMA0_CONTROL(val) bfin_write16(USB_DMA0_CONTROL, val)
#define pUSB_DMA0_ADDRLOW              ((uint16_t volatile *)USB_DMA0_ADDRLOW) /* Lower 16-bits of memory source/destination address for DMA master channel 0 */
#define bfin_read_USB_DMA0_ADDRLOW()   bfin_read16(USB_DMA0_ADDRLOW)
#define bfin_write_USB_DMA0_ADDRLOW(val) bfin_write16(USB_DMA0_ADDRLOW, val)
#define pUSB_DMA0_ADDRHIGH             ((uint16_t volatile *)USB_DMA0_ADDRHIGH) /* Upper 16-bits of memory source/destination address for DMA master channel 0 */
#define bfin_read_USB_DMA0_ADDRHIGH()  bfin_read16(USB_DMA0_ADDRHIGH)
#define bfin_write_USB_DMA0_ADDRHIGH(val) bfin_write16(USB_DMA0_ADDRHIGH, val)
#define pUSB_DMA0_COUNTLOW             ((uint16_t volatile *)USB_DMA0_COUNTLOW) /* Lower 16-bits of byte count of DMA transfer for DMA master channel 0 */
#define bfin_read_USB_DMA0_COUNTLOW()  bfin_read16(USB_DMA0_COUNTLOW)
#define bfin_write_USB_DMA0_COUNTLOW(val) bfin_write16(USB_DMA0_COUNTLOW, val)
#define pUSB_DMA0_COUNTHIGH            ((uint16_t volatile *)USB_DMA0_COUNTHIGH) /* Upper 16-bits of byte count of DMA transfer for DMA master channel 0 */
#define bfin_read_USB_DMA0_COUNTHIGH() bfin_read16(USB_DMA0_COUNTHIGH)
#define bfin_write_USB_DMA0_COUNTHIGH(val) bfin_write16(USB_DMA0_COUNTHIGH, val)
#define pUSB_DMA1_CONTROL              ((uint16_t volatile *)USB_DMA1_CONTROL) /* DMA master channel 1 configuration */
#define bfin_read_USB_DMA1_CONTROL()   bfin_read16(USB_DMA1_CONTROL)
#define bfin_write_USB_DMA1_CONTROL(val) bfin_write16(USB_DMA1_CONTROL, val)
#define pUSB_DMA1_ADDRLOW              ((uint16_t volatile *)USB_DMA1_ADDRLOW) /* Lower 16-bits of memory source/destination address for DMA master channel 1 */
#define bfin_read_USB_DMA1_ADDRLOW()   bfin_read16(USB_DMA1_ADDRLOW)
#define bfin_write_USB_DMA1_ADDRLOW(val) bfin_write16(USB_DMA1_ADDRLOW, val)
#define pUSB_DMA1_ADDRHIGH             ((uint16_t volatile *)USB_DMA1_ADDRHIGH) /* Upper 16-bits of memory source/destination address for DMA master channel 1 */
#define bfin_read_USB_DMA1_ADDRHIGH()  bfin_read16(USB_DMA1_ADDRHIGH)
#define bfin_write_USB_DMA1_ADDRHIGH(val) bfin_write16(USB_DMA1_ADDRHIGH, val)
#define pUSB_DMA1_COUNTLOW             ((uint16_t volatile *)USB_DMA1_COUNTLOW) /* Lower 16-bits of byte count of DMA transfer for DMA master channel 1 */
#define bfin_read_USB_DMA1_COUNTLOW()  bfin_read16(USB_DMA1_COUNTLOW)
#define bfin_write_USB_DMA1_COUNTLOW(val) bfin_write16(USB_DMA1_COUNTLOW, val)
#define pUSB_DMA1_COUNTHIGH            ((uint16_t volatile *)USB_DMA1_COUNTHIGH) /* Upper 16-bits of byte count of DMA transfer for DMA master channel 1 */
#define bfin_read_USB_DMA1_COUNTHIGH() bfin_read16(USB_DMA1_COUNTHIGH)
#define bfin_write_USB_DMA1_COUNTHIGH(val) bfin_write16(USB_DMA1_COUNTHIGH, val)
#define pUSB_DMA2_CONTROL              ((uint16_t volatile *)USB_DMA2_CONTROL) /* DMA master channel 2 configuration */
#define bfin_read_USB_DMA2_CONTROL()   bfin_read16(USB_DMA2_CONTROL)
#define bfin_write_USB_DMA2_CONTROL(val) bfin_write16(USB_DMA2_CONTROL, val)
#define pUSB_DMA2_ADDRLOW              ((uint16_t volatile *)USB_DMA2_ADDRLOW) /* Lower 16-bits of memory source/destination address for DMA master channel 2 */
#define bfin_read_USB_DMA2_ADDRLOW()   bfin_read16(USB_DMA2_ADDRLOW)
#define bfin_write_USB_DMA2_ADDRLOW(val) bfin_write16(USB_DMA2_ADDRLOW, val)
#define pUSB_DMA2_ADDRHIGH             ((uint16_t volatile *)USB_DMA2_ADDRHIGH) /* Upper 16-bits of memory source/destination address for DMA master channel 2 */
#define bfin_read_USB_DMA2_ADDRHIGH()  bfin_read16(USB_DMA2_ADDRHIGH)
#define bfin_write_USB_DMA2_ADDRHIGH(val) bfin_write16(USB_DMA2_ADDRHIGH, val)
#define pUSB_DMA2_COUNTLOW             ((uint16_t volatile *)USB_DMA2_COUNTLOW) /* Lower 16-bits of byte count of DMA transfer for DMA master channel 2 */
#define bfin_read_USB_DMA2_COUNTLOW()  bfin_read16(USB_DMA2_COUNTLOW)
#define bfin_write_USB_DMA2_COUNTLOW(val) bfin_write16(USB_DMA2_COUNTLOW, val)
#define pUSB_DMA2_COUNTHIGH            ((uint16_t volatile *)USB_DMA2_COUNTHIGH) /* Upper 16-bits of byte count of DMA transfer for DMA master channel 2 */
#define bfin_read_USB_DMA2_COUNTHIGH() bfin_read16(USB_DMA2_COUNTHIGH)
#define bfin_write_USB_DMA2_COUNTHIGH(val) bfin_write16(USB_DMA2_COUNTHIGH, val)
#define pUSB_DMA3_CONTROL              ((uint16_t volatile *)USB_DMA3_CONTROL) /* DMA master channel 3 configuration */
#define bfin_read_USB_DMA3_CONTROL()   bfin_read16(USB_DMA3_CONTROL)
#define bfin_write_USB_DMA3_CONTROL(val) bfin_write16(USB_DMA3_CONTROL, val)
#define pUSB_DMA3_ADDRLOW              ((uint16_t volatile *)USB_DMA3_ADDRLOW) /* Lower 16-bits of memory source/destination address for DMA master channel 3 */
#define bfin_read_USB_DMA3_ADDRLOW()   bfin_read16(USB_DMA3_ADDRLOW)
#define bfin_write_USB_DMA3_ADDRLOW(val) bfin_write16(USB_DMA3_ADDRLOW, val)
#define pUSB_DMA3_ADDRHIGH             ((uint16_t volatile *)USB_DMA3_ADDRHIGH) /* Upper 16-bits of memory source/destination address for DMA master channel 3 */
#define bfin_read_USB_DMA3_ADDRHIGH()  bfin_read16(USB_DMA3_ADDRHIGH)
#define bfin_write_USB_DMA3_ADDRHIGH(val) bfin_write16(USB_DMA3_ADDRHIGH, val)
#define pUSB_DMA3_COUNTLOW             ((uint16_t volatile *)USB_DMA3_COUNTLOW) /* Lower 16-bits of byte count of DMA transfer for DMA master channel 3 */
#define bfin_read_USB_DMA3_COUNTLOW()  bfin_read16(USB_DMA3_COUNTLOW)
#define bfin_write_USB_DMA3_COUNTLOW(val) bfin_write16(USB_DMA3_COUNTLOW, val)
#define pUSB_DMA3_COUNTHIGH            ((uint16_t volatile *)USB_DMA3_COUNTHIGH) /* Upper 16-bits of byte count of DMA transfer for DMA master channel 3 */
#define bfin_read_USB_DMA3_COUNTHIGH() bfin_read16(USB_DMA3_COUNTHIGH)
#define bfin_write_USB_DMA3_COUNTHIGH(val) bfin_write16(USB_DMA3_COUNTHIGH, val)
#define pUSB_DMA4_CONTROL              ((uint16_t volatile *)USB_DMA4_CONTROL) /* DMA master channel 4 configuration */
#define bfin_read_USB_DMA4_CONTROL()   bfin_read16(USB_DMA4_CONTROL)
#define bfin_write_USB_DMA4_CONTROL(val) bfin_write16(USB_DMA4_CONTROL, val)
#define pUSB_DMA4_ADDRLOW              ((uint16_t volatile *)USB_DMA4_ADDRLOW) /* Lower 16-bits of memory source/destination address for DMA master channel 4 */
#define bfin_read_USB_DMA4_ADDRLOW()   bfin_read16(USB_DMA4_ADDRLOW)
#define bfin_write_USB_DMA4_ADDRLOW(val) bfin_write16(USB_DMA4_ADDRLOW, val)
#define pUSB_DMA4_ADDRHIGH             ((uint16_t volatile *)USB_DMA4_ADDRHIGH) /* Upper 16-bits of memory source/destination address for DMA master channel 4 */
#define bfin_read_USB_DMA4_ADDRHIGH()  bfin_read16(USB_DMA4_ADDRHIGH)
#define bfin_write_USB_DMA4_ADDRHIGH(val) bfin_write16(USB_DMA4_ADDRHIGH, val)
#define pUSB_DMA4_COUNTLOW             ((uint16_t volatile *)USB_DMA4_COUNTLOW) /* Lower 16-bits of byte count of DMA transfer for DMA master channel 4 */
#define bfin_read_USB_DMA4_COUNTLOW()  bfin_read16(USB_DMA4_COUNTLOW)
#define bfin_write_USB_DMA4_COUNTLOW(val) bfin_write16(USB_DMA4_COUNTLOW, val)
#define pUSB_DMA4_COUNTHIGH            ((uint16_t volatile *)USB_DMA4_COUNTHIGH) /* Upper 16-bits of byte count of DMA transfer for DMA master channel 4 */
#define bfin_read_USB_DMA4_COUNTHIGH() bfin_read16(USB_DMA4_COUNTHIGH)
#define bfin_write_USB_DMA4_COUNTHIGH(val) bfin_write16(USB_DMA4_COUNTHIGH, val)
#define pUSB_DMA5_CONTROL              ((uint16_t volatile *)USB_DMA5_CONTROL) /* DMA master channel 5 configuration */
#define bfin_read_USB_DMA5_CONTROL()   bfin_read16(USB_DMA5_CONTROL)
#define bfin_write_USB_DMA5_CONTROL(val) bfin_write16(USB_DMA5_CONTROL, val)
#define pUSB_DMA5_ADDRLOW              ((uint16_t volatile *)USB_DMA5_ADDRLOW) /* Lower 16-bits of memory source/destination address for DMA master channel 5 */
#define bfin_read_USB_DMA5_ADDRLOW()   bfin_read16(USB_DMA5_ADDRLOW)
#define bfin_write_USB_DMA5_ADDRLOW(val) bfin_write16(USB_DMA5_ADDRLOW, val)
#define pUSB_DMA5_ADDRHIGH             ((uint16_t volatile *)USB_DMA5_ADDRHIGH) /* Upper 16-bits of memory source/destination address for DMA master channel 5 */
#define bfin_read_USB_DMA5_ADDRHIGH()  bfin_read16(USB_DMA5_ADDRHIGH)
#define bfin_write_USB_DMA5_ADDRHIGH(val) bfin_write16(USB_DMA5_ADDRHIGH, val)
#define pUSB_DMA5_COUNTLOW             ((uint16_t volatile *)USB_DMA5_COUNTLOW) /* Lower 16-bits of byte count of DMA transfer for DMA master channel 5 */
#define bfin_read_USB_DMA5_COUNTLOW()  bfin_read16(USB_DMA5_COUNTLOW)
#define bfin_write_USB_DMA5_COUNTLOW(val) bfin_write16(USB_DMA5_COUNTLOW, val)
#define pUSB_DMA5_COUNTHIGH            ((uint16_t volatile *)USB_DMA5_COUNTHIGH) /* Upper 16-bits of byte count of DMA transfer for DMA master channel 5 */
#define bfin_read_USB_DMA5_COUNTHIGH() bfin_read16(USB_DMA5_COUNTHIGH)
#define bfin_write_USB_DMA5_COUNTHIGH(val) bfin_write16(USB_DMA5_COUNTHIGH, val)
#define pUSB_DMA6_CONTROL              ((uint16_t volatile *)USB_DMA6_CONTROL) /* DMA master channel 6 configuration */
#define bfin_read_USB_DMA6_CONTROL()   bfin_read16(USB_DMA6_CONTROL)
#define bfin_write_USB_DMA6_CONTROL(val) bfin_write16(USB_DMA6_CONTROL, val)
#define pUSB_DMA6_ADDRLOW              ((uint16_t volatile *)USB_DMA6_ADDRLOW) /* Lower 16-bits of memory source/destination address for DMA master channel 6 */
#define bfin_read_USB_DMA6_ADDRLOW()   bfin_read16(USB_DMA6_ADDRLOW)
#define bfin_write_USB_DMA6_ADDRLOW(val) bfin_write16(USB_DMA6_ADDRLOW, val)
#define pUSB_DMA6_ADDRHIGH             ((uint16_t volatile *)USB_DMA6_ADDRHIGH) /* Upper 16-bits of memory source/destination address for DMA master channel 6 */
#define bfin_read_USB_DMA6_ADDRHIGH()  bfin_read16(USB_DMA6_ADDRHIGH)
#define bfin_write_USB_DMA6_ADDRHIGH(val) bfin_write16(USB_DMA6_ADDRHIGH, val)
#define pUSB_DMA6_COUNTLOW             ((uint16_t volatile *)USB_DMA6_COUNTLOW) /* Lower 16-bits of byte count of DMA transfer for DMA master channel 6 */
#define bfin_read_USB_DMA6_COUNTLOW()  bfin_read16(USB_DMA6_COUNTLOW)
#define bfin_write_USB_DMA6_COUNTLOW(val) bfin_write16(USB_DMA6_COUNTLOW, val)
#define pUSB_DMA6_COUNTHIGH            ((uint16_t volatile *)USB_DMA6_COUNTHIGH) /* Upper 16-bits of byte count of DMA transfer for DMA master channel 6 */
#define bfin_read_USB_DMA6_COUNTHIGH() bfin_read16(USB_DMA6_COUNTHIGH)
#define bfin_write_USB_DMA6_COUNTHIGH(val) bfin_write16(USB_DMA6_COUNTHIGH, val)
#define pUSB_DMA7_CONTROL              ((uint16_t volatile *)USB_DMA7_CONTROL) /* DMA master channel 7 configuration */
#define bfin_read_USB_DMA7_CONTROL()   bfin_read16(USB_DMA7_CONTROL)
#define bfin_write_USB_DMA7_CONTROL(val) bfin_write16(USB_DMA7_CONTROL, val)
#define pUSB_DMA7_ADDRLOW              ((uint16_t volatile *)USB_DMA7_ADDRLOW) /* Lower 16-bits of memory source/destination address for DMA master channel 7 */
#define bfin_read_USB_DMA7_ADDRLOW()   bfin_read16(USB_DMA7_ADDRLOW)
#define bfin_write_USB_DMA7_ADDRLOW(val) bfin_write16(USB_DMA7_ADDRLOW, val)
#define pUSB_DMA7_ADDRHIGH             ((uint16_t volatile *)USB_DMA7_ADDRHIGH) /* Upper 16-bits of memory source/destination address for DMA master channel 7 */
#define bfin_read_USB_DMA7_ADDRHIGH()  bfin_read16(USB_DMA7_ADDRHIGH)
#define bfin_write_USB_DMA7_ADDRHIGH(val) bfin_write16(USB_DMA7_ADDRHIGH, val)
#define pUSB_DMA7_COUNTLOW             ((uint16_t volatile *)USB_DMA7_COUNTLOW) /* Lower 16-bits of byte count of DMA transfer for DMA master channel 7 */
#define bfin_read_USB_DMA7_COUNTLOW()  bfin_read16(USB_DMA7_COUNTLOW)
#define bfin_write_USB_DMA7_COUNTLOW(val) bfin_write16(USB_DMA7_COUNTLOW, val)
#define pUSB_DMA7_COUNTHIGH            ((uint16_t volatile *)USB_DMA7_COUNTHIGH) /* Upper 16-bits of byte count of DMA transfer for DMA master channel 7 */
#define bfin_read_USB_DMA7_COUNTHIGH() bfin_read16(USB_DMA7_COUNTHIGH)
#define bfin_write_USB_DMA7_COUNTHIGH(val) bfin_write16(USB_DMA7_COUNTHIGH, val)

#endif /* __BFIN_CDEF_ADSP_BF525_proc__ */