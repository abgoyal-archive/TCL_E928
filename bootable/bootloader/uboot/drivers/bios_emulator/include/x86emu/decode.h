

#ifndef __X86EMU_DECODE_H
#define __X86EMU_DECODE_H

/*---------------------- Macros and type definitions ----------------------*/

/* Instruction Decoding Stuff */

#define FETCH_DECODE_MODRM(mod,rh,rl)   fetch_decode_modrm(&mod,&rh,&rl)
#define DECODE_RM_BYTE_REGISTER(r)      decode_rm_byte_register(r)
#define DECODE_RM_WORD_REGISTER(r)      decode_rm_word_register(r)
#define DECODE_RM_LONG_REGISTER(r)      decode_rm_long_register(r)
#define DECODE_CLEAR_SEGOVR()           M.x86.mode &= ~SYSMODE_CLRMASK

/*-------------------------- Function Prototypes --------------------------*/

#ifdef  __cplusplus
extern "C" {                        /* Use "C" linkage when in C++ mode */
#endif

void    x86emu_intr_raise (u8 type);
void    fetch_decode_modrm (int *mod,int *regh,int *regl);
u8      fetch_byte_imm (void);
u16     fetch_word_imm (void);
u32     fetch_long_imm (void);
u8      fetch_data_byte (uint offset);
u8      fetch_data_byte_abs (uint segment, uint offset);
u16     fetch_data_word (uint offset);
u16     fetch_data_word_abs (uint segment, uint offset);
u32     fetch_data_long (uint offset);
u32     fetch_data_long_abs (uint segment, uint offset);
void    store_data_byte (uint offset, u8 val);
void    store_data_byte_abs (uint segment, uint offset, u8 val);
void    store_data_word (uint offset, u16 val);
void    store_data_word_abs (uint segment, uint offset, u16 val);
void    store_data_long (uint offset, u32 val);
void    store_data_long_abs (uint segment, uint offset, u32 val);
u8*     decode_rm_byte_register(int reg);
u16*    decode_rm_word_register(int reg);
u32*    decode_rm_long_register(int reg);
u16*    decode_rm_seg_register(int reg);
unsigned decode_rm00_address(int rm);
unsigned decode_rm01_address(int rm);
unsigned decode_rm10_address(int rm);
unsigned decode_rmXX_address(int mod, int rm);

#ifdef  __cplusplus
}                                   /* End of "C" linkage for C++       */
#endif

#endif /* __X86EMU_DECODE_H */
