#include "hadamard.h"

Hadamard::Hadamard(std::string name, int size) : QOp(name, size) {}

int Hadamard::count_set_bits(int n) {
  int count = 0;
  while (n) {
    count += n & 1;
    n >>= 1;
  }
  return count;
}

QReg Hadamard::row(int i) {
  QReg row(this->name() + "[" + std::to_string(i) + "]", this->size());

  for (int j = 0; j < this->size(); ++j) {
    auto selector = i & j;
    auto selectorBitCount = this->count_set_bits(selector);
    bool isNegative = selectorBitCount % 2;
    row.cells[i] = isNegative ? -1 : 1;
  }

  return row;
}

QReg Hadamard::apply(QReg target) {
  if (this->_size != target.cells.size()) {
    throw std::invalid_argument(
      "Operation and target register sizes don't match!");
  }

  auto result_name = target.name() + " * " + this->name();
  QReg result(result_name, target.cells.size());

  for (int i = 0; i < this->size(); ++i) {
    auto row = this->row(i);
    for (int j = 0; j < row.cells.size(); ++j) {
      result.cells[j] += target.cells[i] * row.cells[i];
    }
  }

  return result;
}
