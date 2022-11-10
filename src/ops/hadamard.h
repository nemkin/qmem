#pragma once

#include "../core/op.h"

class Hadamard : public QOp {

public:
  Hadamard(std::string name, index qubits);

  virtual Amplitudes row(index i);
  virtual Amplitudes col(index j);
};
