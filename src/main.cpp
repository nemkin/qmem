#include "core/log.h"
#include "core/reg.h"
#include "core/op.h"

#include "ops/hadamard.h"
#include "ops/grover.h"
#include "ops/transposed.h"

int main() {
  auto regs = QRegisters();

  regs.Add("r0", 1);
  regs.Add("r1", 1);
  regs.Add("r2", 1);
  regs.Add("r3", 1);

  auto op = Hadamard("H", 1);

  op.apply(regs, { 0 });
  op.apply(regs, { 1 });
  op.apply(regs, { 2 });
  op.apply(regs, { 3 });

  return 0;
}
