#include "tensored.h"

#include <cmath>

Tensored::Tensored(QOp* left, QOp* right) : 
  QOp(left->name()+" OX "+right->name(), left->qubits() + right->qubits()) {
  _left = left;
  _right = right;
}

Amplitudes Tensored::row(index i) {
  auto mod = _left->size();
  auto left_i = i / mod;
  auto right_i = i % mod;

  auto left_row = _left->row(left_i);
  auto right_row = _right->row(right_i);

  auto row = new Amplitudes(this->size());
  for(index j = 0; j < _left->size(); ++j) {
    for(index k = 0; k < _right->size(); ++k) {
      row[j * mod + k] = left_row[j] * right_row[k];
    }
  }

  return _left->row(i) ;
}

Amplitudes Tensored::col(index i) {
  return _inner->row(i);
}
