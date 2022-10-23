#pragma once

#include "../core/op.h"

class Hadamard : public QOp {

public:
  Hadamard(std::string name, int qubits);

  virtual Amplitudes row(int i);
  virtual Amplitudes col(int j);
};
