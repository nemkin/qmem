#include "single.h"

#include <cmath>

Single::Single(std::string name, index qubits, index where) : QOp(name, qubits) {
  _where = where;
}

Amplitudes Single::row(index i) {
  auto size = this->size();
  Amplitudes row(size);

  for (index j = 0; j < size; ++j) {
      row[j] = (_where == i && i == j);
  }
  return row;
}

Amplitudes Single::col(index i) {
  return row(i);
}