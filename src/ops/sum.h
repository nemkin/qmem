#pragma once

#include "../core/op.h"

class Sum : public QOp {

private:
  int input_qubits;
  int output_qubits;

  int input_size;
  int output_size;

public:
  Sum(std::string name, int input_qubits, int output_qubits);

  virtual Amplitudes row(int i);
  virtual Amplitudes col(int j);

  virtual void apply(QRegisters& target, const std::vector<int>& target_regs);
  virtual void apply(QRegisters& target, const std::vector<int>& input_regs, const std::vector<int>& output_regs);
};
