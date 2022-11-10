#pragma once

#include "../core/op.h"

class Grover : public QOp {
public:
  Grover(std::string name, index qubits);

  virtual Amplitudes row(index i);
  virtual Amplitudes col(index j);
};
