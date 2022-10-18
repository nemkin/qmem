#include "transposed.h"

#include <cmath>

Transposed::Transposed(QOp* other) : QOp(other->name()+"_T", other->size()) {
}

QReg Transposed::row(int i) {
  return _inner->col(i);
}

QReg Transposed::col(int i) {
  return _inner->row(i);
}