#include "grover.h"

#include <cmath>

Grover::Grover(std::string name, int size) : QOp(name, size) {
}

QReg Grover::row(int i) {
  QReg row(this->name() + "[" + std::to_string(i) + "]", this->size());

  double denominator = this->size();

  for (int j = 0; j < this->size(); ++j) {
    row.cells[j] = 2 / denominator;
    if (i == j) {
      row.cells[j] -= 1;
    }
  }

  return row;
}

QReg Grover::col(int i) {
  return row(i);
}