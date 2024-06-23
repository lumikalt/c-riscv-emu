#include "../include/interpreter.h"
#include "../include/instructions.h"
#include <stdlib.h>

typedef Emulator Emu;

u64_t write_reg(Emu *emu, size_t reg, uint64_t val) {
  uint64_t temp = emu->regs[reg];
  if (reg != 0)
    emu->regs[reg] = val;
  return temp;
}

f64_t write_freg(Emu *emu, size_t reg, double val) {
  double temp = emu->fregs[reg];
  emu->regs[reg] = val;
  return temp;
}

u64_t read_reg(Emu *emu, size_t reg) { return emu->regs[reg]; }

f64_t read_freg(Emu *emu, size_t reg) { return emu->fregs[reg]; }

Emu *init_emulator() {
  static Emulator emu;

  emu.regs = calloc(32, sizeof(u64_t));
  emu.fregs = calloc(32, sizeof(f64_t));
  emu.mem = malloc(16 * 1024 * 1024); // (2^8)^3 aka 3 bytes indexing
  emu.pc = 0;

  write_reg(&emu, 2, 0xFF0); // Stack Pointer
  write_reg(&emu, 3, 0x200); // Global Pointer

  return &emu;
}

void clean_emulator(Emu *emu) {
  free(emu->regs);
  free(emu->fregs);
  free(emu->mem);
}

void next_cycle(Emu *emu) {
  /* Instruction Fetch */

  size_t prev_pc = emu->pc;
  emu->pc += 4;
  u32_t instr = ((u32_t *)emu->mem)[prev_pc / 4];

  /* Instruction Decode */

  // Also useful to know dependencies for the pipeline.
  Args args = get_args(instr);

  if (!is_fp(instr)) {
    u64_t d = read_reg(emu, args.d);
    u64_t a = read_reg(emu, args.a);
    u64_t b = read_reg(emu, args.b);
    u64_t c = read_reg(emu, args.c);
    u64_t imm = args.imm;
  } else {
    f64_t d = read_freg(emu, args.d);
    f64_t a = read_freg(emu, args.a);
    f64_t b = read_freg(emu, args.b);
    f64_t c = read_freg(emu, args.c);
  }
}
