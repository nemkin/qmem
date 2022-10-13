#include "core/log.h"
#include "core/reg.h"
#include "core/op.h"

#include "ops/hadamard.h"

int main() {
  int size = 1 << 3;
  auto reg = QReg("r", size);
  auto h = Hadamard("H", size);

  reg.cells[2] = 1.0;

  Log::print(&h);
  Log::print(reg);
  for (int i = 0; i < 10; ++i) {
    reg = h.apply(reg);
    Log::print(reg);
  }

  return 0;
}
