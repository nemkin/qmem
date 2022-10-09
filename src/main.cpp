#include "qmem/qmem.h"

int main() {
  int size = 1 << 2;
  auto reg = QRegister("bemenet", size);
  auto op = QOperation("hadamard", size);

  auto result = op.Apply(reg);

  reg.Print();
  op.Print();
  result.Print();

  return 0;
}
