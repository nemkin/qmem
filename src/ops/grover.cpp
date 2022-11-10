#include "grover.h"

#include <cmath>

Grover::Grover(std::string name, index qubits) : QOp(name, qubits) {
}

Amplitudes Grover::row(index i) {
  Amplitudes row;
  row.resize(this->size());

  double denominator = this->size();

  for (index j = 0; j < this->size(); ++j) {
    row[j] = 2 / denominator;
    if (i == j) {
      row[j] -= 1;
    }
  }

  return row;
}

Amplitudes Grover::col(index i) {
  return row(i);
}