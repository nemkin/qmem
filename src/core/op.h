#pragma once

#include "reg.h"

#include <complex>
#include <vector>

class QOp {

protected:
  std::string _name;
  int _size;

public:
  QOp(std::string name, int size);
  std::string name();
  int size();

  virtual QReg row(int i) = 0;
  virtual QReg col(int j) = 0;

  virtual QReg apply(QReg target);
};
