#include "./include/interpreter.h"
#include "./include/util.h"
#include <stdio.h>

int main(void) {
  Emulator *emu = init_emulator();
  // Load the program into memory
  ((u32_t *)emu->mem)[0] = 0b00000000000100000000000010010011; // addi x1, x0, 1

  // Execute the program
  // TODO

  printf("x1 = %lu\n", read_reg(emu, 1));

  clean_emulator(emu);
}
