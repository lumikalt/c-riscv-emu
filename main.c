#include "./include/interpreter.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int main(void) {
  Interpreter interpreter = {
      .regs = calloc(32, sizeof(uint64_t)),
      .fregs = calloc(32, sizeof(double)),
      .stack = calloc(32, 32 * 1024),
      .pc = 0,
  };

  write_reg(&interpreter, 0, 1);
  printf("%lu\n", read_reg(&interpreter, 0));

  clean_interpreter(&interpreter);
}
