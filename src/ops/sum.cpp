#include "sum.h"

#include <cmath>

Sum::Sum(std::string name, int input_qubits, int output_qubits) :
  QOp(name, input_qubits + output_qubits) {
  this->input_qubits = input_qubits;
  this->output_qubits = output_qubits;

  this->input_size = 1 << input_qubits;
  this->output_size = 1 << output_qubits;
}

Amplitudes Sum::row(int i) {
  Amplitudes row(this->size());

  row[i] = 1.0;

  return row;
}

Amplitudes Sum::col(int i) {
  Amplitudes row(this->size());

  row[i] = 1.0;

  //TODO Ancilla bits.
  for (int j = input_size; j < input_size + output_size; ++j) {
    row[j] = 1.0;
  }

  return row;
}
