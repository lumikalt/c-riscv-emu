#include "../include/format.h"

typedef Emulator Emu;

Format get_format(u32_t instr) {
  u8_t opcode = instr & 0b1111111;
  u8_t funct7 = (instr >> 25) & 0b1111111;
  u8_t funct3 = (instr >> 12) & 0b111;

  switch (opcode) {
  case 0b0110111:
  case 0b0010111:
    return U_Type;

  case 0b0100011:
  case 0b0100111:
    return S_Type;

  case 0b1100011:
    return B_Type;

  case 0b1101111:
    return J_Type;

  case 0b0010011:
  case 0b0011011:
    // Shift instructions are I2.
    if (funct3 == 0b001 || funct3 == 0b101)
      return I2_Type;
  case 0b0000011: // Int Load
  case 0b0000111: // FP Load
    return I_Type;

  case 0b0110011: // 64b
  case 0b0111011: // 32b
  case 0b1010011: // FP
    return R_Type;

  case 0b1000011:
  case 0b1000111:
  case 0b1001111:
  case 0b1001011:
    return R4_Type;

  default:
    __builtin_unreachable();
  }
}

Args get_args(u32_t instr) {
  Args args = {
      .d = (instr >> 07) & 0b11111,
      .a = (instr >> 15) & 0b11111,
      .b = (instr >> 20) & 0b11111,
      .c = (instr >> 25) & 0b11111,
      .imm = 0,
  };

  bool sign = instr >> 31;

  switch (get_format(instr)) {
  case I_Type: {
    args.imm = instr >> 20;
    args.imm |= sign * 0xfffffffffffff000;
  } break;

  case I2_Type: {
    args.imm = (instr >> 20) & 0b111111;
    args.imm |= sign * 0xffffffffffffffc0;
  } break;

  case S_Type: {
    args.imm = ((instr >> 20) & 0b111111100000) | ((instr >> 7) & 0b11111);
    args.imm |= sign * 0xfffffffffffff800;
  } break;

  case B_Type: {
    args.imm = ((instr >> 31) << 12) | (((instr >> 25) & 0b111111) << 5) |
               (((instr >> 8) & 0b1111) << 1) | (((instr >> 7) & 0b1) << 11);
    args.imm |= sign * 0xffffffffffffe000;
  } break;

  case U_Type: {
    args.imm = instr & 0xfffff000;
    args.imm |= sign * 0xffffffff00000000;
  } break;

  case J_Type: {
    args.imm = ((instr >> 31) << 20) | (((instr >> 21) & 0b1111111111) << 1) |
               (((instr >> 20) & 0b1) << 11) |
               (((instr >> 12) & 0b11111111) << 12);
    args.imm |= sign * 0xfffffffffff00000;
  } break;

  default:
    break;
  }

  return args;
}

bool is_fp(u32_t instr) {
  u8_t opcode = instr & 0b1111111;

  switch (opcode) {
  case 0b0000111:
  case 0b0100111:
  case 0b1010011:
  case 0b1000011:
  case 0b1000111:
  case 0b1001111:
  case 0b1001011:
    return true;
  default:
    return false;
  }
}
