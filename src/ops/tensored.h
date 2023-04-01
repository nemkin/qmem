#pragma once

#include "../core/op.h"

class Tensored : public QOp {
private:
  QOp* _left;
  QOp* _right;

public:
  Tensored(QOp* left, QOp* right);

  virtual Amplitudes row(index i);
  virtual Amplitudes col(index j);
};
