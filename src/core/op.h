#pragma once

#include "reg.h"

#include <complex>
#include <vector>

#include "base.h"

class QOp {
private:
  int _qubits;

protected:
  std::string _name;

public:
  QOp(std::string name, int qubits);
  std::string name();
  int qubits();
  int size();

  virtual Amplitudes row(int i) = 0;
  virtual Amplitudes col(int j) = 0;

  virtual void apply(QRegisters& target, const std::vector<int>& target_regs);
};
