#include "transposed.h"

#include <cmath>

Transposed::Transposed(QOp* other) : QOp(other->name()+"_T", other->qubits()) {
  _inner = other;
}

Amplitudes Transposed::row(index i) {
  return _inner->col(i);
}

Amplitudes Transposed::col(index i) {
  return _inner->row(i);
}
