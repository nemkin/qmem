#pragma once

#include "../core/debug.h"

#include <bitset>
#include <complex>
#include <iostream>
#include <map>
#include <vector>

class QRegister {

private:
public:
  std::string name;
  std::vector<std::complex<double>> numbers;

  QRegister(std::string name, int size);
  void Print();
};

class QOperation {

private:
public:
  std::string name;
  int size;
  std::vector<std::vector<std::complex<double>>> hadamard;

  QOperation(std::string name, int size);
  std::vector<std::complex<double>> Row(int j);
  int countSetBits(int n);
  QRegister Apply(QRegister target);
  void Print();
};
