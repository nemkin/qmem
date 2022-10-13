#include "log.h"

#include <iostream>
#include <iomanip>
#include <sstream>

std::string Log::to_string(std::complex<double> val) {
  std::ostringstream ss;

  ss << std::fixed << std::setprecision(1);
  ss << std::setfill('x') << std::right;
  ss << std::setiosflags(std::ios::showpos);

  ss << std::setw(3) << val;

  auto result = ss.str();
  return result;
}

std::string Log::to_string(QReg reg) {
  std::ostringstream ss;

  ss << reg.name() << " = { ";
  ss << Log::join(", ", reg.cells);
  ss << "}";

  auto result = ss.str();
  return result;
}

std::string Log::to_string(QOp* op) {
  std::ostringstream ss;

  ss << op->name();
  ss << " = {" << std::endl;
  for (int i = 0; i < op->size(); ++i) {
    ss << to_string(op->row(i)) << std::endl;
  }
  ss << "}" << std::endl;

  auto result = ss.str();
  return result;
}

std::string Log::join(std::string separator, std::vector<std::complex<double> > vals) {
  std::ostringstream ss;

  for (int i = 0; i < vals.size(); ++i) {
    ss << to_string(vals[i]);
    if (i != vals.size() - 1) {
      ss << separator;
    }
  }

  auto result = ss.str();
  return result;
}

void Log::print(std::complex<double> val) {
  std::cout << Log::to_string(val) << std::endl;
}

void Log::print(QReg reg) {
  std::cout << Log::to_string(reg) << std::endl;
}

void Log::print(QOp* op) {
  std::cout << Log::to_string(op) << std::endl;
}
