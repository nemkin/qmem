#pragma once

#include "../core/op.h"

class Transposed : public QOp {
private:
  QOp* _inner;

public:
  Transposed(QOp* other);

  virtual QReg row(int i);
  virtual QReg col(int j);
};
