#pragma once

#include "../core/op.h"

class Mcnot : public QOp {

private:
  int input_qubits;
  int output_qubits;

  int input_size;
  int output_size;

public:
  Mcnot(std::string name, int input_qubits);

  virtual Amplitudes row(int i);
  virtual Amplitudes col(int j);

  virtual void apply(QRegisters& target, const std::vector<int>& target_regs);
  virtual void apply(QRegisters& target, const std::vector<int>& input_regs, int output_reg);
};
