#pragma once

#include "../core/op.h"

class Shift : public QOp {
  index _amount;
public:
  Shift(std::string name, index qubits, index amount);

  virtual Amplitudes row(index i);
  virtual Amplitudes col(index j);
};
