#include "./include/emulator.h"
#include "./include/util.h"
#include "include/format.h"
#include <stdio.h>

int main(void) {
  Emulator *emu = init_emulator();
  // Load the program into memory
  ((u32_t *)emu->mem)[0] = 0b00000000010100000000000010010011; // addi x1, x0, 1

  // Execute the program
  // TODO
  u32_t instruction = ((u32_t *)emu->mem)[0];
  Format f = get_format(instruction);
  Args a = get_args(instruction);

  printf("Args: rd = %lu, ra = %lu, imm = %lu\n", a.d, a.a, a.imm);

  clean_emulator(emu);
}
