#include "core/log.h"
#include "core/reg.h"
#include "core/op.h"

#include "ops/hadamard.h"
#include "ops/grover.h"
#include "ops/transposed.h"

int main() {
  auto regs = QRegisters();

  regs.Add("r1", 1);
  regs.Add("r2", 3);
  regs.Add("r3", 2);

  auto op = Hadamard("H", 3);

  op.apply(regs, { 0, 2 });

  return 0;
}
