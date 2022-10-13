#include "op.h"

QOp::QOp(std::string name, int size) {
  this->_name = name;
  this->_size = size;
}

std::string QOp::name() { return this->_name; }

int QOp::size() { return this->_size; }


QReg QOp::apply(QReg target) {
  if (this->_size != target.cells.size()) {
    throw std::invalid_argument(
      "Operation and target register sizes don't match!");
  }

  auto result_name = target.name() + " * " + this->name();
  QReg result(result_name, target.cells.size());

  for (int i = 0; i < this->size(); ++i) {
    auto row = this->row(i);
    for (int j = 0; j < row.cells.size(); ++j) {
      result.cells[i] += target.cells[j] * row.cells[j];
    }
  }

  return result;
}