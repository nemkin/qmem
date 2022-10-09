#pragma once

#include "../core/debug.h"

#include <bitset>
#include <complex>
#include <iostream>
#include <map>
#include <vector>


#include "QMem.h"

class QRegister {

private:
public:
  std::string name;
  std::vector<std::complex<double>> numbers;

  QRegister(string name, int size);
  void Print();
};

class QOperation {

private:
public:
  string name;
  int size;
  std::vector<std::vector<std::complex<double>>> hadamard;

  QOperation(string name, int size);
  std::vector<std::complex<double>> Row(int j);
  int countSetBits(int n);
  QRegister Apply(QRegister target);
  void Print();
};
