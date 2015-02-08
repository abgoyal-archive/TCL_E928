

#include <config.h>
#include <asm/processor.h>
#include <74xx_7xx.h>
#include <mpc106.h>
#include <version.h>

#include <ppc_asm.tmpl>
#include <ppc_defs.h>



.globl board_asm_init
board_asm_init:
    mflr    r25             /* save away link register */
    bl      get_lnk_reg     /* r3=addr of next instruction */
    subi    r4, r3, 8       /* r4=board_asm_init addr */
    addi    r13, r4, (MessageBlock-board_asm_init)
    mfspr   r3, HID0
    li      r4, HID0_DCE
    andc    r3, r3, r4
    mr      r2, r3
    ori     r3, r3, HID0_DCI
    sync
    mtspr   HID0, r3
    mtspr   HID0, r2
    isync
    sync
    mfspr   r3, HID0
    li      r4, 0
    ori     r4, r4, HID0_ICE
    andc    r3, r3, r4
    sync
    mtspr   HID0, r3
    ori     r3, r3, (HID0_ICE | HID0_ICFI | HID0_DCI | HID0_DCE)
    or      r4, r4, r3
    isync
    mtspr   HID0, r4
    andc    r4, r4, r3
    isync
    mtspr   HID0, r4
    isync
    mfspr   r3, HID0
    ori     r3, r3, (HID0_ICE | HID0_ICFI)
    sync
    mtspr   HID0, r3

    lis     r1, 0xfec0
    ori     r1, r1, 0x0cf8
    lis     r2, 0xfee0
    ori     r2, r2, 0xcfc

#ifdef CONFIG_SYS_ADDRESS_MAP_A
    lis     r3, MPC106_REG@h
    ori     r3, r3, PCI_PICR1
    stwbrx  r3, 0, r1
    sync
    lwbrx   r4, 0, r2
    sync
    lis     r0, PICR1_XIO_MODE@h
    ori     r0, r0, PICR1_XIO_MODE@l
    andc    r4, r4, r0
    lis     r0, PICR1_ADDRESS_MAP@h
    ori     r0, r0, PICR1_ADDRESS_MAP@l
    or      r4, r4, r0
    stwbrx  r4, 0, r2
    sync
#endif

    bl      .sioInit

    addi    r3, r13, (MinitLogo-MessageBlock)
    bl      Printf

    addi    r3, r13, (Mspd01-MessageBlock)
    bl      Printf
    li      r17, 0
    li      r18, 0
    li      r19, 0

    li      r3, 0x0002          /* get RAM type from spd for bank0/1 */
    bl      spdRead

    cmpi    0, 0, r3, -1        /* error ? */
    bne     noSpdError

    addi    r3, r13, (Mfail-MessageBlock)
    bl      Printf

    li      r6, 0xe0            /* error codes in r6 and r7  */
    li      r7, 0x00
    b       toggleError         /* fail - loop forever */

noSpdError:
    mr      r15, r3             /* save r3 */

    addi    r3, r13, (Mok-MessageBlock)
    bl      Printf

    cmpli   0, 0, r15, 0x0001   /* FPM ? */
    beq     configFPM
    cmpli   0, 0, r15, 0x0002   /* EDO ? */
    beq     configEDO
    cmpli   0, 0, r15, 0x0004   /* SDRAM ? */
    beq     configSDRAM

    li      r6, 0xe0            /* error codes in r6 and r7  */
    li      r7, 0x01
    b       toggleError         /* fail - loop forever */

configSDRAM:
    addi    r3, r13, (MsdRam-MessageBlock)
    bl      Printf
    li      r3, 0x001f          /* get bank size from spd bank0/1 */
    bl      spdRead

    andi.   r3, r3, 0x0038
    beq     SD16MB2B

    li      r3, 0x0011          /* get number of internal banks */
				/* from spd for bank0/1 */
    bl      spdRead

    cmpli   0, 0, r3, 0x02
    beq     SD64MB2B

    cmpli   0, 0, r3, 0x04
    beq     SD64MB4B

    li      r6, 0xe0            /* error codes in r6 and r7  */
    li      r7, 0x02
    b       toggleError         /* fail - loop forever */

SD64MB2B:
    li      r20, 0x0005         /* 64-Mbit SDRAM 2 banks */
    b       SDRow2nd

SD64MB4B:
    li      r20, 0x0000         /* 64-Mbit SDRAM 4 banks */
    b       SDRow2nd

SD16MB2B:
    li      r20, 0x000f         /* 16-Mbit SDRAM 2 banks */

SDRow2nd:
    li      r3, 0x0102          /* get RAM type spd for bank2/3 */
    bl      spdRead

    cmpli   0, 0, r3, 0x0004
    bne     S2D64MB4B           /* bank2/3 isn't present or no SDRAM */

    li      r3, 0x011f          /* get bank size from spd bank2/3 */
    bl      spdRead

    andi.   r3, r3, 0x0038
    beq     S2D16MB2B
    li      r3, 0x0111          /* get number of internal banks */
				/* from spd for bank2/3 */
    bl      spdRead

    cmpli   0, 0, r3, 0x02
    beq     S2D64MB2B

    cmpli   0, 0, r3, 0x04
    beq     S2D64MB4B

    li      r6, 0xe0            /* error codes in r6 and r7 */
    li      r7, 0x03
    b       toggleError         /* fail - loop forever */

S2D64MB2B:
    ori     r20, r20, 0x0050    /* 64-Mbit SDRAM 2 banks */
    b       S2D64MB4B

S2D16MB2B:
    ori     r20, r20, 0x00f0    /* 16-Mbit SDRAM 2 banks */

S2D64MB4B:
    lis     r21, 0x8630         /* BSTOPRE = 0x80, REFREC = 6, */
				/* RDLAT = 3 */

    lis     r22, 0x2430         /* PRETOACT = 2, ACTOPRE = 4, */
				/* WCBUF = 1, RCBUF = 1 */
    ori     r22, r22, 0x2220    /* SDMODE = 0x022, ACTORW = 2 */

    li      r3, 0x001f          /* get bank size from spd bank0/1 */
    bl      spdRead

    rlwinm  r16, r3, 2, 24, 29  /* calculate size in MByte */
				/* (128 MB max.) */

    li      r3, 0x0005          /* get number of banks from spd */
				/* for bank0/1 */
    bl      spdRead

    cmpi    0, 0, r3, 2         /* 2 banks ? */
    bne     SDRAMnobank1

    mr      r17, r16

SDRAMnobank1:
    addi    r3, r13, (Mspd23-MessageBlock)
    bl      Printf

    li      r3, 0x0102          /* get RAM type spd for bank2/3 */
    bl      spdRead

    cmpli   0, 0, r3, 0x0001    /* FPM ? */
    bne     noFPM23             /* handle as EDO */
    addi    r3, r13, (Mok-MessageBlock)
    bl      Printf
    addi    r3, r13, (MfpmRam-MessageBlock)
    bl      Printf
    b       configRAMcommon
noFPM23:
    cmpli   0, 0, r3, 0x0002    /* EDO ? */
    bne     noEDO23
    addi    r3, r13, (Mok-MessageBlock)
    bl      Printf
    addi    r3, r13, (MedoRam-MessageBlock)
    bl      Printf
    b       configRAMcommon
noEDO23:
    cmpli   0, 0, r3, 0x0004    /* SDRAM ? */
    bne    noSDRAM23
    addi    r3, r13, (Mok-MessageBlock)
    bl      Printf
    addi    r3, r13, (MsdRam-MessageBlock)
    bl      Printf
    b       configSDRAM23
noSDRAM23:
    addi    r3, r13, (Mna-MessageBlock)
    bl      Printf
    b       configRAMcommon     /* bank2/3 isn't present or no SDRAM */

configSDRAM23:
    li      r3, 0x011f          /* get bank size from spd bank2/3 */
    bl      spdRead

    rlwinm  r18, r3, 2, 24, 29  /* calculate size in MByte */
				/* (128 MB max.) */

    li      r3, 0x0105          /* get number of banks from */
				/* spd bank0/1 */
    bl      spdRead

    cmpi    0, 0, r3, 2         /* 2 banks ? */
    bne     SDRAMnobank3

    mr    r19, r18

SDRAMnobank3:
    b       configRAMcommon

configFPM:
    addi    r3, r13, (MfpmRam-MessageBlock)
    bl      Printf
    b       configEDO0
configEDO:
    addi    r3, r13, (MedoRam-MessageBlock)
    bl      Printf
configEDO0:
    lis     r20, MCCR1_TYPE_EDO@h

getSpdRowBank01:
    li      r3, 0x0003          /* get number of row bits from */
				/* spd from bank0/1 */
    bl      spdRead
    ori     r20, r20, (MCCR1_BK0_9BITS | MCCR1_BK1_9BITS)
    cmpli   0, 0, r3, 0x0009    /* bank0 -  9 row bits */
    beq     getSpdRowBank23

    ori     r20, r20, (MCCR1_BK0_10BITS | MCCR1_BK1_10BITS)
    cmpli   0, 0, r3, 0x000a    /* bank0 -  10 row bits */
    beq     getSpdRowBank23

    ori     r20, r20, (MCCR1_BK0_11BITS | MCCR1_BK1_11BITS)
    cmpli   0, 0, r3, 0x000b    /* bank0 -  11 row bits */
    beq     getSpdRowBank23

    ori     r20, r20, (MCCR1_BK0_12BITS | MCCR1_BK1_12BITS)
    cmpli   0, 0, r3, 0x000c    /* bank0 -  12 row bits */
    beq     getSpdRowBank23

    cmpli   0, 0, r3, 0x000d    /* bank0 -  13 row bits */
    beq     getSpdRowBank23

    li      r6, 0xe0            /* error codes in r6 and r7 */
    li      r7, 0x10
    b       toggleError         /* fail - loop forever */

getSpdRowBank23:
    li     r3, 0x0103           /* get number of row bits from */
				/* spd for bank2/3 */
    bl      spdRead

    ori     r20, r20, (MCCR1_BK2_9BITS | MCCR1_BK3_9BITS)
    cmpli   0, 0, r3, 0x0009    /* bank0 -  9 row bits */
    beq     writeRowBits

    ori     r20, r20, (MCCR1_BK2_10BITS | MCCR1_BK3_10BITS)
    cmpli   0, 0, r3, 0x000a    /* bank0 -  10 row bits */
    beq     writeRowBits

    ori     r20, r20, (MCCR1_BK2_11BITS | MCCR1_BK3_11BITS)
    cmpli   0, 0, r3, 0x000b    /* bank0 -  11 row bits */
    beq     writeRowBits

    ori     r20, r20, (MCCR1_BK2_12BITS | MCCR1_BK3_12BITS)

writeRowBits:
    lis     r21, 0x000a         /* CPX = 1, RAS6P = 4 */
    ori     r21, r21, 0x2293    /* CAS5 = 2, CP4 = 1, */
				/* CAS3 = 2, RCD2 = 2, RP = 3 */
    lis     r22, 0x0010         /* all SDRAM parameter 0, */
				/* WCBUF flow through, */
				/* RCBUF registered */
    li      r3, 0x0003          /* get row bits from spd  bank0/1 */
    bl      spdRead

    li      r16, 0              /* bank size is: */
				/* (8*2^row*2^column)/0x100000 MB */
    ori     r16, r16, 0x8000
    rlwnm   r16, r16, r3, 0, 31

    li      r3, 0x0004          /* get column bits from spd bank0/1 */
    bl      spdRead

    rlwnm   r16, r16, r3, 0, 31

    li      r3, 0x0005          /* get number of banks from */
				/* spd for bank0/1 */
    bl      spdRead

    cmpi    0, 0, r3, 2         /* 2 banks ? */
    bne     EDOnobank1

    mr      r17, r16

EDOnobank1:
    addi    r3, r13, (Mspd23-MessageBlock)
    bl      Printf

    li      r3, 0x0102          /* get RAM type spd for bank2/3 */
    bl      spdRead

    cmpli   0, 0, r3, 0x0001    /* FPM ? */
    bne     noFPM231            /* handle as EDO */
    addi    r3, r13, (Mok-MessageBlock)
    bl      Printf
    addi    r3, r13, (MfpmRam-MessageBlock)
    bl      Printf
    b       EDObank2
noFPM231:
    cmpli   0, 0, r3, 0x0002    /* EDO ? */
    bne     noEDO231
    addi    r3, r13, (Mok-MessageBlock)
    bl      Printf
    addi    r3, r13, (MedoRam-MessageBlock)
    bl      Printf
    b       EDObank2
noEDO231:
    cmpli   0, 0, r3, 0x0004    /* SDRAM ? */
    bne     noSDRAM231
    addi    r3, r13, (Mok-MessageBlock)
    bl      Printf
    addi    r3, r13, (MsdRam-MessageBlock)
    bl      Printf
    b       configRAMcommon
noSDRAM231:
    addi    r3, r13, (Mfail-MessageBlock)
    bl      Printf
    b       configRAMcommon     /* bank2/3 isn't present or no SDRAM */

EDObank2:
    li      r3, 0x0103          /* get row bits from spd for bank2/3 */
    bl      spdRead

    li      r18, 0              /* bank size is: */
				/* (8*2^row*2^column)/0x100000 MB */
    ori     r18, r18, 0x8000
    rlwnm   r18, r18, r3, 0, 31

    li      r3, 0x0104          /* get column bits from spd bank2/3 */
    bl      spdRead

    rlwnm   r18, r18, r3, 0, 31

    li      r3, 0x0105          /* get number of banks from */
				/* spd for bank2/3 */
    bl      spdRead

    cmpi    0, 0, r3, 2         /* 2 banks ? */
    bne     configRAMcommon

    mr      r19, r18

configRAMcommon:
    lis     r1, MPC106_REG_ADDR@h
    ori     r1, r1, MPC106_REG_ADDR@l
    lis     r2, MPC106_REG_DATA@h
    ori     r2, r2, MPC106_REG_DATA@l

    li      r0, 0

#ifdef IN_RAM
    lis     r4, MCCR1_MEMGO@h
    ori     r4, r4, MCCR1_MEMGO@l
    or      r20, r20, r4
#endif

    lis     r3, MPC106_REG@h        /* start building new reg number */
    ori     r3, r3, MPC106_MCCR1    /* register number 0xf0 */
    stwbrx  r3, r0, r1              /* write this value to CONFIG_ADDR */
    eieio                           /* make sure mem. access is complete */
    stwbrx  r20, r0, r2             /* write data to CONFIG_DATA */
    lis     r3, MPC106_REG@h        /* start building new reg number */
    ori     r3, r3, MPC106_MCCR3    /* register number 0xf8 */
    stwbrx  r3, r0, r1              /* write this value to CONFIG_ADDR */
    eieio                           /* make sure mem. access is complete */
    stwbrx    r21, r0, r2           /* write data to CONFIG_DATA */
    lis     r3, MPC106_REG@h        /* start building new reg number */
    ori     r3, r3, MPC106_MCCR4    /* register number 0xfc */
    stwbrx  r3, r0, r1              /* write this value to CONFIG_ADDR */
    eieio                           /* make sure mem. access is complete */
    stwbrx  r22, r0, r2             /* write data to CONFIG_DATA */
    li      r20, 0
    li      r23, 0
    li      r24, 0
    subi    r21, r16, 1         /* calculate end address bank0 */
    li      r22, (MBER_BANK0)

    cmpi    0, 0, r17, 0        /* bank1 present ? */
    beq     nobank1

    rlwinm  r3, r16, 8, 16, 23  /* calculate start address of bank1 */
    or      r20, r20, r3
    add     r16, r16, r17       /* add to total memory size */
    subi    r3, r16, 1          /* calculate end address of bank1 */
    rlwinm  r3, r3, 8, 16, 23
    or      r21, r21, r3
    ori     r22, r22, (MBER_BANK1)      /* enable bank1 */
    b       bank2

nobank1:
    ori     r23, r23, 0x0300    /* set bank1 start to unused area */
    ori     r24, r24, 0x0300    /* set bank1 end to unused area */

bank2:
    cmpi    0, 0, r18, 0        /* bank2 present ? */
    beq     nobank2

    andi.   r3, r16, 0x00ff     /* calculate start address of bank2 */
    andi.   r4, r16, 0x0300
    rlwinm  r3, r3, 16, 8, 15
    or      r20, r20, r3
    rlwinm  r3, r4, 8, 8, 15
    or      r23, r23, r3
    add     r16, r16, r18       /* add to total memory size */
    subi    r3, r16, 1          /* calculate end address of bank2 */
    andi.   r4, r3, 0x0300
    andi.   r3, r3, 0x00ff
    rlwinm  r3, r3, 16, 8, 15
    or      r21, r21, r3
    rlwinm  r3, r4, 8, 8, 15
    or      r24, r24, r3
    ori     r22, r22, (MBER_BANK2)    /* enable bank2 */
    b       bank3

nobank2:
    lis     r3, 0x0003
    or      r23, r23, r3        /* set bank2 start to unused area */
    or      r24, r24, r3        /* set bank2 end to unused area */

bank3:
    cmpi    0, 0, r19, 0        /* bank3 present ? */
    beq     nobank3

    andi.   r3, r16, 0x00ff     /* calculate start address of bank3 */
    andi.   r4, r16, 0x0300
    rlwinm  r3, r3, 24, 0, 7
    or      r20, r20, r3
    rlwinm  r3, r4, 16, 0, 7
    or      r23, r23, r3
    add     r16, r16, r19       /* add to total memory size */
    subi    r3, r16, 1          /* calculate end address of bank3 */
    andi.   r4, r3, 0x0300
    andi.   r3, r3, 0x00ff
    rlwinm  r3, r3, 24, 0, 7
    or      r21, r21, r3
    rlwinm  r3, r4, 16, 0, 7
    or      r24, r24, r3
    ori     r22, r22, (MBER_BANK3)    /* enable bank3 */
    b       writebound

nobank3:
    lis     r3, 0x0300
    or      r23, r23, r3        /* set bank3 start to unused area */
    or      r24, r24, r3        /* set bank3 end to unused area */

writebound:
    lis     r3, MPC106_REG@h    /* start building new reg number */
    ori     r3, r3, MPC106_MSAR1    /* register number 0x80 */
    stwbrx  r3, r0, r1          /* write this value to CONFIG_ADDR */
    eieio                       /* make sure mem. access is complete */
    stwbrx  r20, r0, r2         /* write data to CONFIG_DATA */

    lis     r3, MPC106_REG@h    /* start building new reg number */
    ori     r3, r3, MPC106_MEAR1    /* register number 0x90 */
    stwbrx  r3, r0, r1          /* write this value to CONFIG_ADDR */
    eieio                       /* make sure mem. access is complete */
    stwbrx  r21, r0, r2         /* write data to CONFIG_DATA */

    lis     r3, MPC106_REG@h    /* start building new reg number */
    ori     r3, r3, MPC106_EMSAR1    /* register number 0x88 */
    stwbrx  r3, r0, r1          /* write this value to CONFIG_ADDR */
    eieio                       /* make sure mem. access is complete */
    stwbrx  r23, r0, r2         /* write data to CONFIG_DATA */

    lis     r3, MPC106_REG@h    /* start building new reg number */
    ori     r3, r3, MPC106_EMEAR1    /* register number 0x98 */
    stwbrx  r3, r0, r1          /* write this value to CONFIG_ADDR */
    eieio                       /* make sure mem. access is complete */
    stwbrx  r24, r0, r2         /* write data to CONFIG_DATA */

    lis     r4, 0x0303
    ori     r4, r4, 0x0303      /* bank 4-7 start and end adresses */
    lis     r3, MPC106_REG@h    /* start building new reg number */
    ori     r3, r3, MPC106_EMSAR2    /* register number 0x8C */
    stwbrx  r3, r0, r1          /* write this value to CONFIG_ADDR */
    eieio                       /* make sure mem. access is complete */
    stwbrx  r4, r0, r2          /* write data to CONFIG_DATA */

    lis     r3, MPC106_REG@h    /* start building new reg number */
    ori     r3, r3, MPC106_EMEAR2    /* register number 0x9C */
    stwbrx  r3, r0, r1          /* write this value to CONFIG_ADDR */
    eieio                       /* make sure mem. access is complete */
    stwbrx  r4, r0, r2          /* write data to CONFIG_DATA */

    lis     r3, MPC106_REG@h    /* start building new reg number */
    ori     r3, r3, MPC106_MCCR2    /* register number 0xf4 */
    stwbrx  r3, r0, r1          /* write this value to CONFIG_ADDR */
    eieio                       /* make sure mem. access is complete */

    li      r3, 0x000c          /* get refresh from spd for bank0/1 */
    bl      spdRead

    cmpi    0, 0, r3, -1        /* error ? */
    bne     common1

    li      r6, 0xe0            /* error codes in r6 and r7  */
    li      r7, 0x20
    b       toggleError         /* fail - loop forever */

common1:
    andi.   r15, r3, 0x007f     /* mask selfrefresh bit */
    li      r3, 0x010c          /* get refresh from spd for bank2/3 */
    bl      spdRead

    cmpi    0, 0, r3, -1        /* error ? */
    beq     common2
    andi.   r3, r3, 0x007f      /* mask selfrefresh bit */
    cmp     0, 0, r3, r15       /* find the lower */
    blt     common3

common2:
    mr      r3, r15

common3:
    li      r4, 0x1010          /* refesh cycle 1028 clocks */
				/*  left shifted 2 */
    cmpli   0, 0, r3, 0x0000    /* 15.6 us ? */
    beq     writeRefresh

    li      r4, 0x0808          /* refesh cycle 514 clocks */
				/* left shifted 2 */
    cmpli   0, 0, r3, 0x0002    /* 7.8 us ? */
    beq     writeRefresh

    li      r4, 0x2020          /* refesh cycle 2056 clocks */
				/* left shifted 2 */
    cmpli   0, 0, r3, 0x0003    /* 31.3 us ? */
    beq     writeRefresh

    li      r4, 0x4040          /* refesh cycle 4112 clocks */
				/* left shifted 2 */
    cmpli   0, 0, r3, 0x0004    /* 62.5 us ? */
    beq     writeRefresh

    li      r4, 0
    ori     r4, r4, 0x8080      /* refesh cycle 8224 clocks */
				/* left shifted 2 */
    cmpli   0, 0, r3, 0x0005    /* 125 us ? */
    beq     writeRefresh

    li      r6, 0xe0            /* error codes in r6 and r7 */
    li      r7, 0x21
    b       toggleError         /* fail - loop forever */

writeRefresh:
    stwbrx  r4, r0, r2          /* write data to CONFIG_DATA */

    addi    r3, r13, (Mactivate-MessageBlock)
    bl      Printf
    mr      r3, r16
    bl      OutDec
    addi    r3, r13, (Mmbyte-MessageBlock)
    bl      Printf

    lis     r3, MPC106_REG@h    /* start building new reg number */
    ori     r3, r3, MPC106_MBER /* register number 0xa0 */
    stwbrx  r3, r0, r1          /* write this value to CONFIG_ADDR */
    eieio                       /* make sure mem. access is complete */
    stb     r22, 0(r2)          /* write data to CONFIG_DATA */
    li      r8, 0x63            /* PGMAX = 99 */
    stb     r8, 3(r2)           /* write data to CONFIG_DATA */

    li      r0, 0x7800
    mtctr   r0

wait200us:
    bdnz    wait200us

    lis     r3, MPC106_REG@h    /* start building new reg number */
    ori     r3, r3, MPC106_MCCR1    /* register number 0xf0 */
    stwbrx  r3, r0, r1          /* write this value to CONFIG_ADDR */
    eieio                       /* make sure mem. access is complete */

    lwbrx   r4, r0, r2          /* load r4 from CONFIG_DATA */

    lis     r0, MCCR1_MEMGO@h   /* MEMGO=1 */
    ori     r0, r0, MCCR1_MEMGO@l
    or      r4, r4, r0          /* set the MEMGO bit */
    stwbrx  r4, r0, r2          /* write mdfd data to CONFIG_DATA */

    li      r0, 0x7000
    mtctr   r0

wait8ref:
    bdnz    wait8ref

    addi    r3, r13, (Mok-MessageBlock)
    bl      Printf

    mtlr    r25
    blr

toggleError:
    li      r0, 0
    lis     r9, 127
    ori     r9, r9, 65535
toggleError1:
    addic   r0, r0, 1
    cmpw    cr1, r0, r9
    ble     cr1, toggleError1
    li      r0, 0
    lis     r9, 127
    ori     r9, r9, 65535
toggleError2:
    addic   r0, r0, 1
    cmpw    cr1, r0, r9
    ble     cr1, toggleError2
    b       toggleError


.set    SIO_LUNINDEX, 0x07      /* SIO LUN index register */
.set    SIO_CNFG1, 0x21         /* SIO configuration #1 register */
.set    SIO_PCSCI, 0x23         /* SIO PCS configuration index reg */
.set    SIO_PCSCD, 0x24         /* SIO PCS configuration data reg */
.set    SIO_ACTIVATE, 0x30      /* SIO activate register */
.set    SIO_IOBASEHI, 0x60      /* SIO I/O port base address, 15:8 */
.set    SIO_IOBASELO, 0x61      /* SIO I/O port base address, 7:0 */
.set    SIO_LUNENABLE, 0x01     /* SIO LUN enable */

.sioInit:
    mfspr   r7, 8               /* save link register */

.sioInit_87308:

    lis     r6, CONFIG_SYS_ISA_IO@h
    ori     r6, r6, CONFIG_SYS_ISA_IO@l

#if defined(CONFIG_SYS_NS87308_BADDR_0x)
    addi    r4, r0, 0x0279
#elif defined(CONFIG_SYS_NS87308_BADDR_10)
    addi    r4, r0, 0x015C
#elif defined(CONFIG_SYS_NS87308_BADDR_11)
    addi    r4, r0, 0x002E
#endif
    add     r6, r6, r4          /* add offset to base */
    or      r3, r6, r6          /* make a copy */

    addi    r4, r0, SIO_LUNINDEX    /* select PMC LUN */
    addi    r5, r0, 0x8
    bl      .sio_bw
    addi    r4, r0, SIO_IOBASEHI    /* initialize PMC address to 0x460 */
    addi    r5, r0, 0x04
    bl      .sio_bw
    addi    r4, r0, SIO_IOBASELO
    addi    r5, r0, 0x60
    bl      .sio_bw
    addi    r4, r0, SIO_ACTIVATE    /* enable PMC */
    addi    r5, r0, SIO_LUNENABLE
    bl      .sio_bw

    lis     r8, CONFIG_SYS_ISA_IO@h
    ori     r8, r8, 0x0460
    li      r9, 0x03
    stb     r9, 0(r8)               /* select PMC2 register */
    eieio
    li      r9, 0x00
    stb     r9, 1(r8)               /* SuperI/O clock src: 24MHz via X1 */
    eieio

    addi    r4, r0, SIO_LUNINDEX    /* select COM1 LUN */
    addi    r5, r0, 0x6
    bl      .sio_bw

    addi    r4, r0, SIO_IOBASEHI    /* initialize COM1 address to 0x3F8 */
    addi    r5, r0, 0x03
    bl      .sio_bw

    addi    r4, r0, SIO_IOBASELO
    addi    r5, r0, 0xF8
    bl      .sio_bw

    addi    r4, r0, SIO_ACTIVATE    /* enable COM1 */
    addi    r5, r0, SIO_LUNENABLE
    bl      .sio_bw

    lis     r8, CONFIG_SYS_ISA_IO@h
    ori     r8, r8, 0x03f8
    li      r9, 0x00
    stb     r9, 1(r8)           /* int disabled */
    eieio
    li      r9, 0x00
    stb     r9, 4(r8)           /* modem ctrl */
    eieio
    li      r9, 0x80
    stb     r9, 3(r8)           /* link ctrl, bank select */
    eieio
    li      r9, 115200/CONFIG_BAUDRATE
    stb     r9, 0(r8)           /* baud rate (LSB)*/
    eieio
    rotrwi  r9, r9, 8
    stb     r9, 1(r8)           /* baud rate (MSB) */
    eieio
    li      r9, 0x03
    stb     r9, 3(r8)           /* 8 data bits, 1 stop bit, */
				/* no parity */
    eieio
    li      r9, 0x0b
    stb     r9, 4(r8)           /* enable the receiver and transmitter */
    eieio

waitEmpty:
    lbz     r9, 5(r8)           /* transmit empty */
    andi.   r9, r9, 0x40
    beq     waitEmpty
    li      r9, 0x47
    stb     r9, 3(r8)           /* send break, 8 data bits, */
				/* 2 stop bits, no parity */
    eieio

    lis     r0, 0x0001
    mtctr   r0

waitCOM1:
    lwz     r0, 5(r8)           /* load from port for delay */
    bdnz    waitCOM1

waitEmpty1:
    lbz     r9, 5(r8)           /* transmit empty */
    andi.   r9, r9, 0x40
    beq     waitEmpty1
    li      r9, 0x07
    stb     r9, 3(r8)           /* 8 data bits, 2 stop bits, */
				/* no parity */
    eieio

    addi    r4, r0, SIO_LUNINDEX    /* select GPIO LUN */
    addi    r5, r0, 0x7
    bl      .sio_bw

    addi    r4, r0, SIO_IOBASEHI    /* initialize GPIO address to 0x220 */
    addi    r5, r0, 0x02
    bl      .sio_bw

    addi    r4, r0, SIO_IOBASELO
    addi    r5, r0, 0x20
    bl      .sio_bw

    addi    r4, r0, SIO_ACTIVATE    /* enable GPIO */
    addi    r5, r0, SIO_LUNENABLE
    bl      .sio_bw

.sioInit_done:

    lis     r3, CONFIG_SYS_ISA_IO@h
    ori     r3, r3, CONFIG_SYS_ISA_IO@l

    addi    r3, r3, 0x015C      /* adjust to superI/O 87308 base */
    or      r6, r3, r3          /* make a copy */
    addi    r4, r0, SIO_PCSCI   /* select PCSCIR */
    addi    r5, r0, 0x00
    bl      .sio_bw
    addi    r4, r0, SIO_PCSCD   /* select PCSCDR */
    addi    r5, r0, 0x00
    bl      .sio_bw
    addi    r4, r0, SIO_PCSCI   /* select PCSCIR */
    addi    r5, r0, 0x01
    bl      .sio_bw
    addi    r4, r0, SIO_PCSCD   /* select PCSCDR */
    addi    r5, r0, 0x76
    bl      .sio_bw
    addi    r4, r0, SIO_PCSCI   /* select PCSCIR */
    addi    r5, r0, 0x02
    bl      .sio_bw
    addi    r4, r0, SIO_PCSCD   /* select PCSCDR */
    addi    r5, r0, 0x40
    bl      .sio_bw
    addi    r4, r0, SIO_PCSCI   /* select PCSCIR */
    addi    r5, r0, 0x05
    bl      .sio_bw
    addi    r4, r0, SIO_PCSCD   /* select PCSCDR */
    addi    r5, r0, 0x00
    bl      .sio_bw
    addi    r4, r0, SIO_PCSCI   /* select PCSCIR */
    addi    r5, r0, 0x05
    bl      .sio_bw
    addi    r4, r0, SIO_PCSCD   /* select PCSCDR */
    addi    r5, r0, 0x70
    bl      .sio_bw
    addi    r4, r0, SIO_PCSCI   /* select PCSCIR */
    addi    r5, r0, 0x06
    bl      .sio_bw
    addi    r4, r0, SIO_PCSCD   /* select PCSCDR */
    addi    r5, r0, 0x1C
    bl      .sio_bw
    addi    r4, r0, SIO_PCSCI   /* select PCSCIR */
    addi    r5, r0, 0x08
    bl      .sio_bw
    addi    r4, r0, SIO_PCSCD   /* select PCSCDR */
    addi    r5, r0, 0x00
    bl      .sio_bw
    addi    r4, r0, SIO_PCSCI   /* select PCSCIR */
    addi    r5, r0, 0x09
    bl      .sio_bw
    addi    r4, r0, SIO_PCSCD   /* select PCSCDR */
    addi    r5, r0, 0x71
    bl      .sio_bw
    addi    r4, r0, SIO_PCSCI   /* select PCSCIR */
    addi    r5, r0, 0x0A
    bl      .sio_bw
    addi    r4, r0, SIO_PCSCD   /* select PCSCDR */
    addi    r5, r0, 0x1C
    bl      .sio_bw

    mtspr   8, r7               /* restore link register */
    bclr    20, 0               /* return to caller */

.sio_bw:
    stb     r4, 0(r3)           /* write index register with register offset */
    eieio
    sync
    stb     r5, 1(r3)           /* 1st write */
    eieio
    sync
    stb     r5, 1(r3)           /* 2nd write */
    eieio
    sync
    bclr    20, 0               /* return to caller */
.sio_br:
    stb     r4, 0(r3)           /* write index register with register offset */
    eieio
    sync
    lbz     r3, 1(r3)           /* retrieve specified reg offset contents */
    eieio
    sync
    bclr    20, 0               /* return to caller */

.globl Printf
Printf:
    lis     r10, CONFIG_SYS_ISA_IO@h   /* COM1 port */
    ori     r10, r10, 0x03f8

WaitChr:
    lbz     r0, 5(r10)          /* read link status */
    eieio
    andi.   r0, r0, 0x40        /* mask transmitter empty bit */
    beq     cr0, WaitChr        /* wait till empty */
    lbzx    r0, r0, r3          /* get char */
    stb     r0, 0(r10)          /* write to transmit reg */
    eieio
    addi    r3, r3, 1           /* next char */
    lbzx    r0, r0, r3          /* get char */
    cmpwi   cr1, r0, 0          /* end of string ? */
    bne     cr1, WaitChr
    blr

OutHex2:
    li      r9, 4               /* shift reg for 2 digits */
    b       OHstart
OutHex4:
    li      r9, 12              /* shift reg for 4 digits */
    b       OHstart
    .globl OutHex
OutHex:
    li      r9, 28              /* shift reg for 8 digits */
OHstart:
    lis     r10, CONFIG_SYS_ISA_IO@h   /* COM1 port */
    ori     r10, r10, 0x03f8
OutDig:
    lbz     r0, 5(r10)          /* read link status */
    eieio
    andi.   r0, r0, 0x40        /* mask transmitter empty bit */
    beq     cr0, OutDig
    sraw    r0, r3, r9
    clrlwi  r0, r0, 28
    cmpwi   cr1, r0, 9
    ble     cr1, digIsNum
    addic   r0, r0, 55
    b       nextDig
digIsNum:
    addic   r0, r0, 48
nextDig:
    stb     r0, 0(r10)          /* write to transmit reg */
    eieio
    addic.  r9, r9, -4
    bge     OutDig
    blr
.globl OutDec
OutDec:
    li      r6, 10
    divwu   r0, r3, r6          /* r0 = r3 / 10, r9 = r3 mod 10 */
    mullw   r10, r0, r6
    subf    r9, r10, r3

    mr      r3, r0
    divwu   r0, r3, r6          /* r0 = r3 / 10, r8 = r3 mod 10 */
    mullw   r10, r0, r6
    subf    r8, r10, r3

    mr      r3, r0
    divwu   r0, r3, r6          /* r0 = r3 / 10, r7 = r3 mod 10 */
    mullw   r10, r0, r6
    subf    r7, r10, r3

    lis     r10, CONFIG_SYS_ISA_IO@h   /* COM1 port */
    ori     r10, r10, 0x03f8

    or.     r7, r7, r7
    bne     noblank1
    li      r3, 0x20
    b       OutDec4

noblank1:
    addi    r3, r7, 48          /* convert to ASCII */

OutDec4:
    lbz     r0, 0(r13)          /* slow down dummy read */
    lbz     r0, 5(r10)          /* read link status */
    eieio
    andi.   r0, r0, 0x40        /* mask transmitter empty bit */
    beq     cr0, OutDec4
    stb     r3, 0(r10)          /* x00 to transmit */
    eieio

    or.     r7, r7, r8
    beq     OutDec5

    addi    r3, r8, 48          /* convert to ASCII */
OutDec5:
    lbz     r0, 0(r13)          /* slow down dummy read */
    lbz     r0, 5(r10)          /* read link status */
    eieio
    andi.   r0, r0, 0x40        /* mask transmitter empty bit */
    beq     cr0, OutDec5
    stb     r3, 0(r10)          /* x0  to transmit */
    eieio

    addi    r3, r9, 48          /* convert to ASCII */
OutDec6:
    lbz     r0, 0(r13)          /* slow down dummy read */
    lbz     r0, 5(r10)          /* read link status */
    eieio
    andi.   r0, r0, 0x40        /* mask transmitter empty bit */
    beq     cr0, OutDec6
    stb     r3, 0(r10)          /* x   to transmit */
    eieio
    blr
.globl    OutChr
OutChr:
    lis     r10, CONFIG_SYS_ISA_IO@h   /* COM1 port */
    ori     r10, r10, 0x03f8

OutChr1:
    lbz     r0, 5(r10)          /* read link status */
    eieio
    andi.   r0, r0, 0x40        /* mask transmitter empty bit */
    beq     cr0, OutChr1        /* wait till empty */
    stb     r3, 0(r10)          /* write to transmit reg */
    eieio
    blr
spdRead:
    mfspr   r26, 8              /* save link register */

    lis     r30, CONFIG_SYS_ISA_IO@h
    ori     r30, r30, 0x220     /* GPIO Port 1 */
    li      r7, 0x00
    li      r8, 0x100
    and.    r5, r3, r8
    beq     spdbank0
    li      r12, 0x08
    li      r4, 0x10
    li      r6, 0x18
    b       spdRead1

spdbank0:
    li      r12, 0x20           /* set I2C data */
    li      r4, 0x40            /* set I2C clock */
    li      r6, 0x60            /* set I2C clock and data */

spdRead1:
    li      r8, 0x80

    bl      spdStart            /* access I2C bus as master */
    li      r10, 0xa0           /* write to SPD */
    bl      spdWriteByte
    bl      spdReadAck          /* ACK returns in r10 */
    cmpw    cr0, r10, r7
    bne     AckErr              /* r10 must be 0, if ACK received */
    mr      r10, r3             /* adr to read */
    bl      spdWriteByte
    bl      spdReadAck
    cmpw    cr0, r10, r7
    bne     AckErr
    bl      spdStart
    li      r10, 0xa1           /* read from SPD */
    bl      spdWriteByte
    bl      spdReadAck
    cmpw    cr0, r10, r7
    bne     AckErr
    bl      spdReadByte         /* return val in r10 */
    bl      spdWriteAck
    bl      spdStop             /* release I2C bus */
    mr      r3, r10
    mtspr   8, r26              /* restore link register */
    blr
AckErr:
    bl      spdStop
    orc     r3, r0, r0          /* return -1 */
    mtspr   8, r26              /* restore link register */
    blr

waitSpd:
    li      r0, 0x1000
    mtctr   r0
wSpd:
    bdnz    wSpd
    bclr    20, 0               /* return to caller */

spdStart:
    mfspr   r27, 8              /* save link register */
    stb     r6, 0(r30)          /* set SDA and SCL */
    eieio
    stb     r6, 1(r30)          /* switch GPIO to output */
    eieio
    bl      waitSpd
    stb     r4, 0(r30)          /* reset SDA */
    eieio
    bl      waitSpd
    stb     r7, 0(r30)          /* reset SCL */
    eieio
    bl      waitSpd
    mtspr   8, r27
    bclr    20, 0               /* return to caller */

spdStop:
    mfspr   r27, 8              /* save link register */
    stb     r7, 0(r30)          /* reset SCL and SDA */
    eieio
    stb     r6, 1(r30)          /* switch GPIO to output */
    eieio
    bl      waitSpd
    stb     r4, 0(r30)          /* set SCL */
    eieio
    bl      waitSpd
    stb     r6, 0(r30)          /* set SDA and SCL */
    eieio
    bl      waitSpd
    stb     r7, 1(r30)          /* switch GPIO to input */
    eieio
    mtspr   8, r27
    bclr    20, 0               /* return to caller */

spdReadByte:
    mfspr   r27, 8
    stb     r4, 1(r30)          /* set GPIO for SCL output */
    eieio
    li      r9, 0x08
    li      r10, 0x00
loopRB:
    stb     r7, 0(r30)          /* reset SDA and SCL */
    eieio
    bl      waitSpd
    stb     r4, 0(r30)          /* set SCL */
    eieio
    bl      waitSpd
    lbz     r5, 0(r30)          /* read from GPIO Port1 */
    rlwinm  r10, r10, 1, 0, 31
    and.    r5, r5, r12
    beq     clearBit
    ori     r10, r10, 0x01      /* append _1_ */
clearBit:
    stb     r7, 0(r30)          /* reset SCL */
    eieio
    bl      waitSpd
    addic.  r9, r9, -1
    bne     loopRB
    mtspr   8, r27
    bclr    20, 0               /* return (r10) to caller */

spdWriteByte:
    mfspr   r27, 8              /* save link register */
    li      r9, 0x08            /* write octet */
    and.    r5, r10, r8
    bne     sWB1
    stb     r7, 0(r30)          /* set SDA to _0_ */
    eieio
    b       sWB2
sWB1:
    stb     r12, 0(r30)         /* set SDA to _1_ */
    eieio
sWB2:
    stb     r6, 1(r30)          /* set GPIO to output */
    eieio
loopWB:
    and.    r5, r10, r8
    bne     sWB3
    stb     r7, 0(r30)          /* set SDA to _0_ */
    eieio
    b       sWB4
sWB3:
    stb     r12, 0(r30)         /* set SDA to _1_ */
    eieio
sWB4:
    bl      waitSpd
    and.    r5, r10, r8
    bne     sWB5
    stb     r4, 0(r30)          /* set SDA to _0_ and SCL */
    eieio
    b       sWB6
sWB5:
    stb     r6, 0(r30)          /* set SDA to _1_ and SCL */
    eieio
sWB6:
    bl      waitSpd
    and.    r5, r10, r8
    bne     sWB7
    stb     r7, 0(r30)          /* set SDA to _0_ and reset SCL */
    eieio
    b       sWB8
sWB7:
    stb     r12, 0(r30)         /* set SDA to _1_ and reset SCL */
    eieio
sWB8:
    bl      waitSpd
    rlwinm  r10, r10, 1, 0, 31  /* next bit */
    addic.  r9, r9, -1
    bne     loopWB
    mtspr   8, r27
    bclr    20, 0               /* return to caller */

spdReadAck:
    mfspr   r27, 8              /* save link register */
    stb     r4, 1(r30)          /* set GPIO to output */
    eieio
    stb     r7, 0(r30)          /* reset SDA and SCL */
    eieio
    bl      waitSpd
    stb     r4, 0(r30)          /* set SCL */
    eieio
    bl      waitSpd
    lbz     r10, 0(r30)         /* read GPIO Port 1 and mask SDA */
    and     r10, r10, r12
    bl      waitSpd
    stb     r7, 0(r30)          /* reset SDA and SCL */
    eieio
    bl      waitSpd
    mtspr   8, r27
    bclr    20, 0               /* return (r10) to caller */

spdWriteAck:
    mfspr   r27, 8
    stb     r12, 0(r30)         /* set SCL */
    eieio
    stb     r6, 1(r30)          /* set GPIO to output */
    eieio
    bl      waitSpd
    stb     r6, 0(r30)          /* SDA and SCL */
    eieio
    bl      waitSpd
    stb     r12, 0(r30)         /* reset SCL */
    eieio
    bl      waitSpd
    mtspr   8, r27
    bclr    20, 0               /* return to caller */

get_lnk_reg:
    mflr    r3                  /* return link reg */
    blr

.globl MessageBlock
MessageBlock:
Mok:
    .ascii  "OK\015\012\000"
Mfail:
    .ascii  "FAILED\015\012\000"
Mna:
    .ascii  "NA\015\012\000"
MinitLogo:
    .ascii  "\015\012*** ELTEC Elektronik, Mainz ***\015\012"
    .ascii  "\015\012Initialising RAM\015\012\000"
Mspd01:
    .ascii  "       Reading SPD of bank0/1 ..... \000"
Mspd23:
    .ascii  "       Reading SPD of bank2/3 ..... \000"
MfpmRam:
    .ascii  "       RAM-Type: FPM \015\012\000"
MedoRam:
    .ascii  "       RAM-Type: EDO \015\012\000"
MsdRam:
    .ascii  "       RAM-Type: SDRAM \015\012\000"
Mactivate:
    .ascii  "       Activating \000"
Mmbyte:
    .ascii  " MB .......... \000"
    .align  4
