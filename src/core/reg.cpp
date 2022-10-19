#include "reg.h"

#include <iostream>
#include <vector>



QRegisters::QRegisters() {

}

void QRegisters::Add(std::string name, int qubits) {

  auto size = 1 << qubits;

  auto new_size = this->amplitudes.size();
  if (new_size == 0) new_size = 1;
  new_size *= size;

  std::vector<std::complex<double>> new_amplitudes(new_size);

  for (int j = 0; j < this->amplitudes.size(); ++j) {
    auto i = 0;
    new_amplitudes[i * this->total_size + j] = amplitudes[j];
  }

  this->amplitudes = new_amplitudes;
  this->total_registers += 1;
  this->total_qubits += qubits;
  this->qubits.push_back(qubits);
  this->total_size = amplitudes.size();
  this->sizes.push_back(size);
  this->names.push_back(name);
}
