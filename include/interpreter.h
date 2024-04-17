#pragma once

#include <stddef.h>
#include <stdint.h>

/// - 32 64b integer registers
/// - 32 64b floating-point registers
/// - stack of TODO bytes
/// - program counter
typedef struct {
  uint64_t *regs;
  double *fregs;
  uint64_t *stack;
  size_t pc;
} Interpreter;

/// Write `val` to the integer register `reg`, and returns the old value of
/// `reg`.
///
/// Note: Attempting to write to x0 is a noop.
uint64_t write_reg(Interpreter *, size_t reg, uint64_t val);

/// Write `val` to the fp register `reg`, and returns the old value of
/// `reg`.
double write_freg(Interpreter *, size_t reg, double val);

/// Get the value of the integer register `reg`.
uint64_t read_reg(Interpreter *, size_t reg);

/// Get the value of the fp register `reg`.
double read_freg(Interpreter *, size_t reg);

/// Free the members of the struct.
void clean_interpreter(Interpreter *);
