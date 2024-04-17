#include "../include/interpreter.h"
#include <stdlib.h>

typedef Interpreter I;

uint64_t write_reg(I *interpreter, size_t reg, uint64_t val) {
  uint64_t temp = interpreter->regs[reg];
  if (reg != 0)
    interpreter->regs[reg] = val;
  return temp;
}

double write_freg(I *interpreter, size_t reg, double val) {
  double temp = interpreter->fregs[reg];
  interpreter->regs[reg] = val;
  return temp;
}

uint64_t read_reg(I *interpreter, size_t reg) { return interpreter->regs[reg]; }

double read_freg(I *interpreter, size_t reg) { return interpreter->fregs[reg]; }

void clean_interpreter(I *interpreter) {
  free(interpreter->regs);
  free(interpreter->fregs);
  free(interpreter->stack);
}
