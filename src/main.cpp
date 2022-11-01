#include<iostream>
#include <string> 

#include "core/log.h"
#include "core/reg.h"
#include "core/op.h"

#include "ops/hadamard.h"
#include "ops/grover.h"
#include "ops/sum.h"
#include "ops/transposed.h"

int main() {
  auto regs = QRegisters();

  int oracle_size = 1;
  int size = 4;
  int sum_size = 3;

  auto h = Hadamard("H", oracle_size);
  auto sum = Sum("SUM", size, sum_size);

  regs.Add("oracle", oracle_size, 1); // 0
  regs.Add("cells", size); // 1
  regs.Add("sums", sum_size); // 2

  h.apply(regs, { 0 });
  sum.apply(regs, { 1 }, { 2 });

  return 0;
}
