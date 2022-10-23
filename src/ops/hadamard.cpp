#include "hadamard.h"

#include <cmath>

Hadamard::Hadamard(std::string name, int qubits) : QOp(name, qubits) {}

Amplitudes Hadamard::row(int i) {
  Amplitudes row(this->size());

  double denominator = std::sqrt(1.0 * this->size());

  for (int j = 0; j < this->size(); ++j) {
    auto selector = i & j;
    auto selectorBitCount = this->count_set_bits(selector);
    bool isNegative = selectorBitCount % 2;
    row[j] = (isNegative ? -1 : 1) / denominator;
  }

  return row;
}

Amplitudes Hadamard::col(int i) {
  return row(i);
}
