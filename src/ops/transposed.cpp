#include "transposed.h"

#include <cmath>

Transposed::Transposed(QOp* other) : QOp(other->name()+"_T", other->qubits()) {
  _inner = other;
}

Amplitudes Transposed::row(int i) {
  return _inner->col(i);
}

Amplitudes Transposed::col(int i) {
  return _inner->row(i);
}