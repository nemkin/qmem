#include "op.h"

QOp::QOp(std::string name, int size) {
  this->_name = name;
  this->_size = size;
}

std::string QOp::name() { return this->_name; }

int QOp::size() { return this->_size; }
