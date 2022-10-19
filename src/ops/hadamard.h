#pragma once

#include "../core/op.h"

class Hadamard : public QOp {
private:
  int count_set_bits(int n);

public:
  Hadamard(std::string name, int qubits);

  virtual Amplitudes row(int i);
  virtual Amplitudes col(int j);
};
