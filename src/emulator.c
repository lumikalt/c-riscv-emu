#include "../include/emulator.h"
#include "../include/format.h"

#include <stdlib.h>

typedef Emulator Emu;

u64_t write_reg(Emu *emu, reg rd, uint64_t val) {
  uint64_t temp = emu->regs[rd];
  if (rd != 0)
    emu->regs[rd] = val;
  return temp;
}

f64_t write_freg(Emu *emu, reg fd, double val) {
  double temp = emu->fregs[fd];
  emu->regs[fd] = val;
  return temp;
}

u64_t read_reg(Emu *emu, reg ra) { return emu->regs[ra]; }

f64_t read_freg(Emu *emu, reg ra) { return emu->fregs[ra]; }

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

Fetched op_fetch(Emu *emu, Args args, Format format, bool fp) {
  Fetched f;

  if (!fp)
    switch (format) {
    case R4_Type:
      __builtin_unreachable();
    case S_Type:
    case B_Type:
      f.c.i = args.imm;
    case R_Type:
    case I_Type:
    case I2_Type:
      if (format == I_Type || format == I2_Type)
        f.b.i = args.imm;
      else
        f.b.i = read_reg(emu, args.b);
    default:
      if (format == U_Type || format == J_Type)
        f.a.i = args.imm;
      else
        f.a.i = read_reg(emu, args.a);
    }
  else
    switch (format) {
    case B_Type:
    case I2_Type:
    case U_Type:
    case J_Type:
      __builtin_unreachable();
    case R4_Type:
    case S_Type:
      if (format == R4_Type)
        f.c.f = read_freg(emu, args.c);
      else
        f.c.f = args.imm;
    default:
      if (format == I_Type)
        f.b.f = args.imm;
      else
        f.b.f = read_freg(emu, args.b);

      f.a.f = read_freg(emu, args.a);
    }

  return f;
}

void next_cycle(Emu *emu) {
  /* Instruction Fetch */

  size_t prev_pc = emu->pc;
  emu->pc += 4; // Rollback on jump
  u32_t instr = ((u32_t *)emu->mem)[prev_pc / 4];

  /* Instruction Decode */

  Format format = get_format(instr);
  Args args = get_args(instr);
  bool fp = is_fp(instr);

  /* Operand Fetch */

  Fetched fetched = op_fetch(emu, args, format, fp);

  /* Execute */

  /* Memory */

  /* Write-Back */
}
