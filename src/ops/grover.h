#pragma once

#include "../core/op.h"

class Grover : public QOp {
public:
  Grover(std::string name, int qubits);

  virtual Amplitudes row(int i);
  virtual Amplitudes col(int j);
};
