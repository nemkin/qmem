#pragma once

#include "../core/op.h"

class Transposed : public QOp {
private:
  QOp* _inner;

public:
  Transposed(QOp* other);

  virtual Amplitudes row(index i);
  virtual Amplitudes col(index j);
};
