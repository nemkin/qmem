#include "reg.h"

#include <iostream>
#include <vector>



QRegisters::QRegisters() {

}

void QRegisters::Add(std::string name, int qubits, int initial) {
  auto size = 1 << qubits;

  auto new_size = this->amplitudes.size();
  if (new_size == 0) new_size = 1;
  new_size *= size;

  std::vector<std::complex<double>> new_amplitudes(new_size);

  for (int j = 0; j < this->amplitudes.size(); ++j) {
    new_amplitudes[initial * this->total_size + j] = amplitudes[j];
  }

  if (this->total_registers == 0) {
    new_amplitudes[0] = 1;
  }

  this->amplitudes.clear();
  this->amplitudes = new_amplitudes;
  this->total_registers += 1;
  this->total_qubits += qubits;
  this->qubits.push_back(qubits);
  this->total_size = amplitudes.size();
  this->sizes.push_back(size);
  this->names.push_back(name);
}
