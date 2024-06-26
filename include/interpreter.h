#pragma once

#include "./util.h"

/// # Single-Stage Pipeline RISC-V CPU
///
/// (TODO pipelining/forwarding/hazard correction)
///
/// - 32 64b integer registers
/// - 32 64b floating-point registers
/// - memory of `16MB`:
///   - 0x000 - 0x1FF = Instructions
///   - 0x200 - 0x2FF = Globals
///   - 0xFF0 - (...) = Stack
/// - program counter
/// - instruction in each stage
typedef struct {
  u64_t *regs;
  f64_t *fregs;
  u8_t *mem;
  size_t pc;
} Emulator;

typedef union {
  u64_t i;
  f64_t f;
} ForI;

typedef struct {
  size_t d; // Optional, not used for S, B
  ForI a;
  ForI b; // Optional, used by R, I, I2 (+bellow)
  ForI c; // Optional, used by R4, S, B
} Fetched;

typedef enum { IF, ID, EX, MEM, WB } Stage;

/// Write `val` to the integer register `reg`, and returns the old value of
/// `reg`.
///
/// Note: Attempting to write to x0 is a noop.
u64_t write_reg(Emulator *, size_t reg, u64_t val);

/// Write `val` to the fp register `reg`, and returns the old value of
/// `reg`.
f64_t write_freg(Emulator *, size_t reg, f64_t val);

/// Get the value of the integer register `reg`.
u64_t read_reg(Emulator *, size_t reg);

/// Get the value of the fp register `reg`.
f64_t read_freg(Emulator *, size_t reg);

/// Init a new Emulator
Emulator *init_emulator();

/// Free the members of the Emulator.
void clean_emulator(Emulator *);

void next_cycle(Emulator *);
