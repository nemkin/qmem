#include "reg.h"

#include <iostream>

QReg::QReg(std::string name, int size) {
  this->_name = name;
  cells.resize(size);
}

std::string QReg::name() {
  return this->_name;
}
