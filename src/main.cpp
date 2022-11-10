#include<iostream>
#include <string>

#include "core/log.h"
#include "core/amplitudes.h"
#include "core/reg.h"
#include "core/op.h"

#include "ops/hadamard.h"
#include "ops/grover.h"
#include "ops/sum.h"
#include "ops/transposed.h"

int main(int argc, char* argv[]) {
  auto regs = QRegisters();
  index sum_size = atoi(argv[1]);
  index size = 1 << (sum_size-1);
  std::cout<<"sum_size: "<<sum_size<<std::endl;
  std::cout<<"size: "<<size<<std::endl;

  auto op = Sum("OP", size, sum_size);

  regs.Add("input", size); // 0
  regs.Add("output", sum_size); // 1

  std::cout<<"regs.size: "<<regs.amplitudes.size()<<std::endl;

  for (int i = 0; i < 10; ++i) {
    op.apply(regs, { 0, 1 });
  }

  return 0;
}
