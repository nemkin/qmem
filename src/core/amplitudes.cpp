#include "amplitudes.h"

Amplitudes::Amplitudes(index size) {
  this->_size = size;
}

void Amplitudes::resize(index size) {
  if (size < _size) {
    for (auto it = this->begin(); it != this->end();) {
      if (size <= it->first) {
        it = this->erase(it);
      } else {
        it++;
      }
    }
  }
  _size = size;
}

index Amplitudes::size() { return _size; }
