#pragma once

#include "../core/op.h"

class Hadamard : public QOp {
private:
  int count_set_bits(int n);

public:
  Hadamard(std::string name, int size);
  virtual QReg row(int j);
  virtual QReg apply(QReg target);
};
