#include "reg.h"

#include <iostream>
#include <vector>

#include "amplitudes.h"

QRegisters::QRegisters() {
  amplitudes.resize(0);
}

void QRegisters::Add(std::string name, index qubits, index initial) {
  auto size = 1 << qubits;

  auto new_size = this->amplitudes.size();
  std::cout<<"old_size: "<<new_size<<std::endl;
  if (new_size == 0) new_size = 1;
  new_size *= size;
  std::cout<<"new_size: "<<new_size<<std::endl;

  Amplitudes new_amplitudes;
  new_amplitudes.resize(new_size);

  for (auto amp : this->amplitudes) {
    auto j = amp.first;
    new_amplitudes[initial * this->total_size + j] = amplitudes[j];
  }

  if (this->total_registers == 0) {
    new_amplitudes[initial] = 1;
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
