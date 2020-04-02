/*
This file is part of a disassembler for Andestech NDS32.

(c) 2019-2020 kitten_nb_five

THIS WORK COMES WITHOUT ANY WARRANTY and is released under the AGPL version 3 or later
*/

#ifndef __OPCODES32_H__
#define __OPCODES32_H__

#define OPC_ALU_1 0b100000 //has SUB
#define OPC_ADDI 0b101000
#define OPC_ANDI 0b101010
#define OPC_BR1 0b100110 //has SUB
#define OPC_BR2 0b100111 //has SUB
#define OPC_MISC 0b110010 //has SUB
#define OPC_ALU_2 0b100001 //has SUB
#define OPC_J 0b100100 //has SUB
#define OPC_JREG 0b100101 //has SUB
#define OPC_MEM 0b011100 //has SUB
#define OPC_LBI 0b000000
#define OPC_LBI_bi 0b000100
#define OPC_LBSI 0b010000
#define OPC_LBSI_bi 0b010100
#define OPC_LHI 0b000001
#define OPC_LHI_bi 0b000101
#define OPC_LHSI 0b010001
#define OPC_LHSI_bi 0b010101
#define OPC_LSMW 0b011101 //has SUB
#define OPC_LWI 0b000010
#define OPC_LWI_bi 0b000110
#define OPC_MOVI 0b100010
#define OPC_ORI 0b101100
#define OPC_SBI 0b001000
#define OPC_SBI_bi 0b001100
#define OPC_SETHI 0b100011
#define OPC_SHI 0b001001
#define OPC_SHI_bi 0b001101
#define OPC_SLTI 0b101110
#define OPC_SLTSI 0b101111
#define OPC_SUBRI 0b101001
#define OPC_SWI 0b001010
#define OPC_SWI_bi 0b001110
#define OPC_XORI 0b101011


#define SUB_ALU_1_ADD 0b00000
#define SUB_ALU_1_AND 0b00010
#define SUB_ALU_1_CMOVN 0b11011
#define SUB_ALU_1_CMOVZ 0b11010
#define SUB_ALU_1_NOP 0b01001
#define SUB_ALU_1_NOR 0b00101
#define SUB_ALU_1_OR 0b00100
#define SUB_ALU_1_ROTR 0b01111
#define SUB_ALU_1_ROTRI 0b01011
#define SUB_ALU_1_SEB 0b10000
#define SUB_ALU_1_SEH 0b10001
#define SUB_ALU_1_SLL 0b01100
#define SUB_ALU_1_SLLI 0b01000
#define SUB_ALU_1_SLT 0b00110
#define SUB_ALU_1_SLTS 0b00111
#define SUB_ALU_1_SRA 0b01110
#define SUB_ALU_1_SRAI 0b01010
#define SUB_ALU_1_SRL 0b01101
#define SUB_ALU_1_SRLI 0b01001
#define SUB_ALU_1_SUB 0b00001
#define SUB_ALU_1_SVA 0b11000
#define SUB_ALU_1_SVS 0b11001
#define SUB_ALU_1_WSBH 0b10100
#define SUB_ALU_1_XOR 0b00011
#define SUB_ALU_1_ZEH 0b10011

//hacked to 10 bits
#define SUB_ALU_2_DIV 0b0000101111
#define SUB_ALU_2_DIVS 0b0000101110
#define SUB_ALU_2_MADD32 0b0000110011
#define SUB_ALU_2_MADD64 0b0000101011
#define SUB_ALU_2_MADDS64 0b0000101010
#define SUB_ALU_2_MFUSR 0b0000100000
#define SUB_ALU_2_MSUB32 0b0000110101
#define SUB_ALU_2_MSUB64 0b0000101101
#define SUB_ALU_2_MSUBS64 0b0000101100
#define SUB_ALU_2_MTUSR 0b0000100001
#define SUB_ALU_2_MUL 0b0000100100
#define SUB_ALU_2_MULT32 0b0000110001
#define SUB_ALU_2_MULT64 0b0000101001
#define SUB_ALU_2_MULTS64 0b0000101000

//uses GPR
#define SUB_ALU_2_MADDR32 0b0001110011
#define SUB_ALU_2_MSUBR32 0b0001110101
#define SUB_ALU_2_MULR64 0b0001101001
#define SUB_ALU_2_MULSR64 0b0001101000


#define SUB_BR1_BEQ 0b0
#define SUB_BR1_BNE 0b1
#define SUB_BR2_BEQZ 0b0010
#define SUB_BR2_BGEZ 0b0100
#define SUB_BR2_BGEZAL 0b1100
#define SUB_BR2_BGTZ 0b0110
#define SUB_BR2_BLEZ 0b0111
#define SUB_BR2_BLTZ 0b0101
#define SUB_BR2_BLTZAL 0b1101
#define SUB_BR2_BNEZ 0b0011
#define SUB_MISC_BREAK 0b01010
#define SUB_MISC_CCTL 0b00001
#define SUB_MISC_DSB 0b01000
#define SUB_MISC_IRET 0b00100
#define SUB_MISC_ISB 0b01001
#define SUB_MISC_ISYNC 0b01101
#define SUB_MISC_MFSR 0b00010
#define SUB_MISC_MSYNC 0b01100
#define SUB_MISC_MTSR 0b00011
#define SUB_MISC_SETEND 0b00001
#define SUB_MISC_SETGIE 0b00010
#define SUB_MISC_STANDBY 0b00000
#define SUB_MISC_SYSCALL 0b01011
#define SUB_MISC_TEQZ 0b00110
#define SUB_MISC_TNEZ 0b00111
#define SUB_MISC_TLBOP 0b01110
#define SUB_MISC_TRAP 0b00101
#define SUB_MISC_MSYNC 0b01100
#define SUB_J_J 0b0
#define SUB_J_JAL 0b1
#define SUB_JREG_JR 0b000000
#define SUB_JREG_JRAL 0b000001
#define SUB_JREG_RET 0b100000
#define SUB_MEM_DPREF 0b00010011
#define SUB_MEM_LB 0b00000000
#define SUB_MEM_LB_bi 0b00000100
#define SUB_MEM_LBS 0b00010000
#define SUB_MEM_LBS_bi 0b00010100
#define SUB_MEM_LH 0b00000001
#define SUB_MEM_LH_bi 0b00000101
#define SUB_MEM_LHS 0b00010001
#define SUB_MEM_LHS_bi 0b00010101
#define SUB_MEM_LLW 0b00011000
#define SUB_MEM_LW 0b00000010
#define SUB_MEM_LW_bi 0b00000110
#define SUB_MEM_LWUP 0b00100010
#define SUB_MEM_SB 0b00001000
#define SUB_MEM_SB_bi 0b00001100
#define SUB_MEM_SCW 0b00011001
#define SUB_MEM_SH 0b00001001
#define SUB_MEM_SH_bi 0b00001101
#define SUB_MEM_SW 0b00001010
#define SUB_MEM_SW_bi 0b00001110
#define SUB_MEM_SWUP 0b00101010
#define SUB_LSMW_LMW_ai 0b010000
#define SUB_LSMW_LMW_bi 0b000000
#define SUB_LSMW_LMW_ad 0b011000
#define SUB_LSMW_LMW_bd 0b001000
#define SUB_LSMW_LMW_aim 0b010100
#define SUB_LSMW_LMW_bim 0b000100
#define SUB_LSMW_LMW_adm 0b011100
#define SUB_LSMW_LMW_bdm 0b001100
#define SUB_LSMW_SMW_ai 0b110000
#define SUB_LSMW_SMW_bi 0b100000
#define SUB_LSMW_SMW_ad 0b111000
#define SUB_LSMW_SMW_bd 0b101000
#define SUB_LSMW_SMW_aim 0b110100
#define SUB_LSMW_SMW_bim 0b100100
#define SUB_LSMW_SMW_adm 0b111100
#define SUB_LSMW_SMW_bdm 0b101100

#define SUB_LSMW_SMWA_adm 0b111101
#define SUB_LSMW_SMWA_bdm 0b101101

#define SUB_LSMW_LMWA_bim 0b000101

#define SUB_ALU_2_BSET 0b001000
#define SUB_ALU_2_BTST 0b001011
#define SUB_ALU_2_MIN 0b000001
#define SUB_ALU_2_BSP 0b001101
#define SUB_ALU_2_ABS 0b000011
#define SUB_ALU_2_MAX 0b000000

#define SUB_ALU_1_DIVR 0b10111
#define SUB_ALU_1_DIVSR 0b10110

#endif
