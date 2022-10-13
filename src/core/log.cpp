#include "log.h"

#include <iostream>

std::string Log::to_string(std::complex<double> val) {
  std::string result;
  std::cout << val << std::endl;
  auto real = val.real();
  auto imag = val.imag();

  auto real_str = std::to_string(real);
  auto imag_str = std::to_string(imag);
  result += real_str;
  result += " ";
  result += imag_str;
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

std::string Log::join(std::string separator, std::vector<std::complex<double> > vals) {
  std::string result = to_string(vals[0]);
  for (int i = 1; i < vals.size(); ++i) {
    std::cout << i << " " << vals.size();
    result += separator;
    result += to_string(vals[i]);
  }
  return result;
}

void Log::print(std::complex<double> val) {
    std::cout << Log::to_string(val) << std::endl;
}

void Log::print(QReg reg) { std::cout << Log::to_string(reg) << std::endl; }

void Log::print(QOp *op) { std::cout << Log::to_string(op) << std::endl; }
