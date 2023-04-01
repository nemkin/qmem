#pragma once

#include "../core/op.h"

class Single : public QOp {
  index _where;
public:
  Single(std::string name, index qubits, index where);

  virtual Amplitudes row(index i);
  virtual Amplitudes col(index j);
};
