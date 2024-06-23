#pragma once

#include "./interpreter.h"
#include <stdbool.h>

/// Instruction Format
typedef enum {
  R_Type,
  R4_Type,
  I_Type,
  I2_Type,
  S_Type,
  B_Type,
  U_Type,
  J_Type,
} Format;

/// Returns the instruction's format.
Format get_format(u32_t);

/// Arguments in the instruction opcode.
///
/// **Note**: unused by the format = garbage data.
typedef struct {
  size_t d;
  size_t a;
  size_t b;
  size_t c;
  u64_t imm;
} Args;

/// Returns the instruction's encoded arguments.
///
/// Note: Caller must MSB-extend, if needed.
Args get_args(u32_t);

/// Is the instruction FP?
bool is_fp(u32_t);
