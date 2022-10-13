#pragma once

#include "../core/op.h"

class Grover : public QOp {
public:
  Grover(std::string name, int size);

  virtual QReg row(int i);
  virtual QReg col(int j);
};
