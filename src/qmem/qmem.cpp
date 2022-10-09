#include "qmem.h"

std::string to_string(std::vector<int> v) {
  bool first = true;
  std::string res = "{";
  for (int i = 0; i < static_cast<int>(v.size()); i++) {
    if (!first) {
      res += ", ";
    }
    first = false;
    res += std::to_string(v[i]);
  }
  res += "}";
  return res;
}

std::string to_string(std::vector<std::complex<double>> v) {
  bool first = true;
  std::string res = "{";
  for (int i = 0; i < static_cast<int>(v.size()); i++) {
    if (!first) {
      res += ", ";
    }
    first = false;

    auto real = std::to_string(v[i].real());
    auto imag = std::to_string(v[i].imag());

    res += real;
    res += " ";
    res += imag;
  }
  res += "}";
  return res;
}

QRegister::QRegister(std::string name, int size) {
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

QOperation::QOperation(std::string name, int size) {
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

std::vector<std::complex<double>> QOperation::Row(int j) {
  std::vector<std::complex<double>> row;

  for (int i = 0; i < this->size; ++i) {
    auto selector = i & j;
    auto selectorBitCount = countSetBits(selector);
    bool isNegative = selectorBitCount % 2;

    std::cout << std::to_string(selector) << std::endl;
    std::cout << std::to_string(selectorBitCount) << std::endl;
    std::cout << std::to_string(isNegative) << std::endl;

    if (isNegative) {
      row.push_back(-1);
    } else {
      row.push_back(1);
    }
  }

  std::cout << to_string(row) << std::endl;
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
