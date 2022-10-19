#pragma once

#include <complex>
#include <string>
#include <vector>

#include "op.h"
#include "reg.h"

class Log {

public:
  static std::string to_string(std::complex<double> val);
  static std::string to_string(std::vector<int> vals);
  static std::string to_string(std::vector<bool> vals);
  static std::string to_string(std::vector<std::complex<double>> vals);
  static std::string to_string(QOp* op);

  static std::string join(std::string separator, std::vector<int> vals);
  static std::string join(std::string separator, std::vector<bool> vals);
  static std::string join(std::string separator, std::vector<std::complex<double>> vals);

  static void print(std::complex<double> val);
  static void print(std::vector<int> vals);
  static void print(std::vector<bool> vals);
  static void print(std::vector<std::complex<double>> vals);
  static void print(QOp* op);
};
