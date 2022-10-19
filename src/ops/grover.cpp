#include "grover.h"

#include <cmath>

Grover::Grover(std::string name, int qubits) : QOp(name, qubits) {
}

Amplitudes Grover::row(int i) {
  Amplitudes row(this->size());

  double denominator = this->size();

  for (int j = 0; j < this->size(); ++j) {
    row[j] = 2 / denominator;
    if (i == j) {
      row[j] -= 1;
    }
  }

  return row;
}

Amplitudes Grover::col(int i) {
  return row(i);
}