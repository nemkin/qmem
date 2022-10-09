#include "qmem.h"

QRegister::QRegister(string name, int size) {
  this->name = name;
  numbers.resize(size);
  for (int i = 0; i < size; ++i) {
    numbers[i] = 1;
  }
}

void QRegister::Print() {
  std::cout << this->name << " :";
  for (auto i : numbers) {
    std::cout << i << " ";
  }
  std::cout << std::endl;
}

QOperation::QOperation(string name, int size) {
  this->name = name;
  this->size = size;
  hadamard.resize(size);
  for (int i = 0; i < size; ++i) {
    hadamard[i].resize(size);
    for (int j = 0; j < size; ++j) {
      hadamard[i][j] = 2;
    }
  }
}

vector<complex<double>> QOperation::Row(int j) {
  vector<complex<double>> row;

  for (int i = 0; i < this->size; ++i) {
    auto selector = i & j;
    auto selectorBitCount = countSetBits(selector);
    bool isNegative = selectorBitCount % 2;

    debug(selector);
    debug(selectorBitCount);
    debug(isNegative);

    if (isNegative) {
      row.push_back(-1);
    } else {
      row.push_back(1);
    }
  }

  debug(row);
  return row;
}

int QOperation::countSetBits(int n) {
  int count = 0;
  while (n) {
    count += n & 1;
    n >>= 1;
  }
  return count;
}

QRegister QOperation::Apply(QRegister target) {
  QRegister result(target.name + " * " + this->name, target.numbers.size());

  for (int i = 0; i < hadamard.size(); ++i) {
    auto row = Row(i);
    for (int j = 0; j < hadamard[i].size(); ++j) {
      result.numbers[j] += target.numbers[i] * row[i];
    }
  }

  return result;
}

void QOperation::Print() {
  std::cout << this->name << ":" << std::endl;
  for (auto i : hadamard) {
    for (auto j : i) {
      std::cout << j << " ";
    }
    std::cout << std::endl;
  }
}
