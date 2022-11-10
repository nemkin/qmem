#pragma once

#include <complex>
#include <string>
#include <vector>

#include "op.h"
#include "reg.h"
#include "amplitudes.h"

class Log {
 public:
  static std::string to_string(index val);
  static std::string to_string(std::complex<double> val);
  static std::string to_string(std::vector<index> vals);
  static std::string to_string(std::vector<bool> vals);
  static std::string to_string(Amplitudes vals);
  static std::string to_string(QOp* op);

  static std::string join(std::string separator, std::vector<index> vals);
  static std::string join(std::string separator, std::vector<bool> vals);
  static std::string join(std::string separator, Amplitudes vals);

  static void print(std::complex<double> val);
  static void print(std::vector<index> vals);
  static void print(std::vector<bool> vals);
  static void print(Amplitudes vals);
  static void print(QOp* op);

  static void qubit_print(Amplitudes vals, index max_size);
};
