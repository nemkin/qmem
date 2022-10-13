#include "core/log.h"
#include "core/reg.h"
#include "core/op.h"

#include "ops/hadamard.h"
#include "ops/grover.h"

int main() {
  int size = 1 << 3;
  auto reg = QReg("r", size);
  auto h = Grover("H", size);
  auto g = Grover("G", size);

  reg.cells[2] = 1.0;

  Log::print(&g);
  Log::print(reg);
  for (int i = 0; i < 10; ++i) {
    reg = g.apply(reg);
    Log::print(reg);
  }

  for (int i = 0; i < size; ++i) {
    auto res = g.apply(g.col(i));
    Log::print(res);
  }



  return 0;
}
