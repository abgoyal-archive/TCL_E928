

#ifndef __FSL_NFC_H
#define __FSL_NFC_H

#if defined(CONFIG_MX31) || defined(CONFIG_MX27)
#define MXC_NFC_V1
#elif defined(CONFIG_MX25)
#define MXC_NFC_V1_1
#else
#warning "MXC NFC version not defined"
#endif

#if defined(MXC_NFC_V1)
#define NAND_MXC_NR_BUFS		4
#define NAND_MXC_SPARE_BUF_SIZE		16
#define NAND_MXC_REG_OFFSET		0xe00
#define NAND_MXC_2K_MULTI_CYCLE		1
#elif defined(MXC_NFC_V1_1)
#define NAND_MXC_NR_BUFS		8
#define NAND_MXC_SPARE_BUF_SIZE		64
#define NAND_MXC_REG_OFFSET		0x1e00
#else
#error "define CONFIG_NAND_MXC_VXXX to use the mxc spl_nand driver"
#endif

struct fsl_nfc_regs {
	u32 main_area[NAND_MXC_NR_BUFS][512/4];
	u32 spare_area[NAND_MXC_NR_BUFS][NAND_MXC_SPARE_BUF_SIZE/4];
	/*
	 * reserved size is offset of nfc registers
	 * minus total main and spare sizes
	 */
	u8 reserved1[NAND_MXC_REG_OFFSET
		- NAND_MXC_NR_BUFS * (512 + NAND_MXC_SPARE_BUF_SIZE)];
#if defined(MXC_NFC_V1)
	u16 bufsiz;
	u16 reserved2;
	u16 buffer_address;
	u16 flash_add;
	u16 flash_cmd;
	u16 configuration;
	u16 ecc_status_result;
	u16 ecc_rslt_main_area;
	u16 ecc_rslt_spare_area;
	u16 nf_wr_prot;
	u16 unlock_start_blk_add;
	u16 unlock_end_blk_add;
	u16 nand_flash_wr_pr_st;
	u16 nand_flash_config1;
	u16 nand_flash_config2;
#elif defined(MXC_NFC_V1_1)
	u16 reserved2[2];
	u16 buffer_address;
	u16 flash_add;
	u16 flash_cmd;
	u16 configuration;
	u16 ecc_status_result;
	u16 ecc_status_result2;
	u16 spare_area_size;
	u16 nf_wr_prot;
	u16 reserved3[2];
	u16 nand_flash_wr_pr_st;
	u16 nand_flash_config1;
	u16 nand_flash_config2;
	u16 reserved4;
	u16 unlock_start_blk_add0;
	u16 unlock_end_blk_add0;
	u16 unlock_start_blk_add1;
	u16 unlock_end_blk_add1;
	u16 unlock_start_blk_add2;
	u16 unlock_end_blk_add2;
	u16 unlock_start_blk_add3;
	u16 unlock_end_blk_add3;
#endif
};

#define NFC_CMD		0x1

#define NFC_ADDR	0x2

#define NFC_INPUT	0x4

#define NFC_OUTPUT	0x8

#define NFC_ID		0x10

#define NFC_STATUS	0x20

#define NFC_INT		0x8000

#ifdef MXC_NFC_V1_1
#define NFC_4_8N_ECC	(1 << 0)
#endif
#define NFC_SP_EN	(1 << 2)
#define NFC_ECC_EN	(1 << 3)
#define NFC_INT_MSK	(1 << 4)
#define NFC_BIG		(1 << 5)
#define NFC_RST		(1 << 6)
#define NFC_CE		(1 << 7)
#define NFC_ONE_CYCLE	(1 << 8)

#endif /* __FSL_NFC_H */
