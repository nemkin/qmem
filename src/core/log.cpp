#include "log.h"

#include <iostream>

using namespace std;

std::string Log::to_string(std::complex<double> val) {
  string result;
  cout << val << endl;
  auto real = to_string(val.real());
  auto imag = to_string(val.imag());
  result += real;
  result += " ";
  result += imag;
  return result;
}

std::string Log::to_string(QReg reg) {
  std::string res = reg.name() + " = {" + Log::join(", ", reg.cells) + "}";
  return res;
}

std::string Log::to_string(QOp *op) {
  std::string res = op->name() + " = {\n";

  for (int i = 1; i < op->size(); ++i) {
    res += to_string(op->row(i));
  }

  res += "}";

  return res;
}

template <typename T>
std::string Log::join(std::string separator, std::vector<T> vals) {
  std::string result = to_string(vals[0]);
  for (int i = 1; i < vals.size(); ++i) {
    cout << i << " " << vals.size();
    result += separator;
    result += to_string(vals[i]);
  }
  return result;
}

void Log::print(std::complex<double> val) {
  cout << Log::to_string(val) << endl;
}

void Log::print(QReg reg) { cout << Log::to_string(reg) << endl; }

void Log::print(QOp *op) { cout << Log::to_string(op) << endl; }
