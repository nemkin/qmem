#include "added.h"

#include <cmath>

Added::Added(std::vector<QOp*> ops) : QOp("ADDED", ops[0]->qubits()) {
  _ops = ops;
}

Amplitudes Added::row(index i) {
  auto row = Amplitudes(this->size());
  for(index j = 0; j < _ops.size(); ++j) {
    auto op = _ops[j]->row(i);
    for(index k = 0; k < this->size(); ++ k) {
      row[k] += op[k];
    }
  }
  return row;
}

Amplitudes Added::col(index i) {
  auto col = Amplitudes(this->size());
  for(index j = 0; j < _ops.size(); ++j) {
    auto op = _ops[j]->col(i);
    for(index k = 0; k < this->size(); ++ k) {
      col[k] += op[k];
    }
  }
  return col;
}
