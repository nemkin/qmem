#include "core/log.h"
#include "core/reg.h"
#include "core/op.h"

#include "ops/hadamard.h"

int main() {
  int size = 1 << 3;
  //auto reg = QRegister("bemenet", size);
  auto h = Hadamard("hadamard", 8);

  Log::print(&h);

  //auto result = op.Apply(reg);

  return 0;
}
