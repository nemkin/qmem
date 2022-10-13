#pragma once

#include <complex>
#include <string>
#include <vector>

#include "op.h"
#include "reg.h"

class Log {

public:
  static std::string to_string(std::complex<double> val);
  static std::string to_string(QReg reg);
  static std::string to_string(QOp* op);

  template <typename T>
  static std::string join(std::string separator, std::vector<T> vals);

  static void print(std::complex<double> val);
  static void print(QReg reg);
  static void print(QOp* op);
};
