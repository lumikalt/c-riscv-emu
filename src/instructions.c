#include "../include/instructions.h"
#include <stdbool.h>
#include <stdint.h>

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
  };

  switch (get_format(instr)) {
  case I_Type: {
    args.imm = instr >> 20;
  } break;
  case I2_Type: {
    args.imm = (instr >> 20) & 0b111111;
  } break;
  case S_Type: {
    args.imm = ((instr >> 20) & 0b111111100000) | ((instr >> 7) & 0b11111);
  } break;
  case B_Type: {
    args.imm = ((instr >> 31) << 12) | (((instr >> 25) & 0b111111) << 5) | ();
  } break;
  case U_Type: {
  } break;
  case J_Type: {
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
