#include "hadamard.h"

#include <cmath>

Hadamard::Hadamard(std::string name, index qubits) : QOp(name, qubits) {}

Amplitudes Hadamard::row(index i) {
  Amplitudes row;
  row.resize(this->size());

  double denominator = std::sqrt(1.0 * this->size());

  for (index j = 0; j < this->size(); ++j) {
    auto selector = i & j;
    auto selectorBitCount = this->count_set_bits(selector);
    bool isNegative = selectorBitCount % 2;
    row[j] = (isNegative ? -1 : 1) / denominator;
  }

  return row;
}

Amplitudes Hadamard::col(index i) {
  return row(i);
}
