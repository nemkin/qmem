#pragma once

#include<vector>

#include "../core/op.h"

class Added : public QOp {
private:
  std::vector<QOp*> _ops;

public:
  Added(std::vector<QOp*> ops);

  virtual Amplitudes row(index i);
  virtual Amplitudes col(index j);
};
