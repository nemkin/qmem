#include "shift.h"

#include <cmath>

Shift::Shift(std::string name, index qubits, index amount) : QOp(name, qubits) {
  _amount = amount;
}

Amplitudes Shift::row(index i) {
  auto size = this->size();
  Amplitudes row(size);

  for (index j = 0; j < size; ++j) {
      row[j] = (i == ((j + _amount) % size + size) % size);
  }
  return row;
}

Amplitudes Shift::col(index i) {
  auto size = this->size();
  Amplitudes col(size);

  for (index j = 0; j < size; ++j) {
      col[j] = (j == ((i + _amount) % size + size) % size);
  }
  return col;
}