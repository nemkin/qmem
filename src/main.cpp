#include "core/log.h"
#include "core/reg.h"
#include "core/op.h"

#include "ops/hadamard.h"
#include "ops/grover.h"
#include "ops/sum.h"
#include "ops/transposed.h"

int main() {
  auto regs = QRegisters();

  regs.Add("r0", 2);
  regs.Add("r1", 2);

  auto op = Sum("SUM", 2, 2);

  op.apply(regs, { 0 }, { 1 });

  return 0;
}
