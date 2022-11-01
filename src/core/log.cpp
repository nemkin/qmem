#include "log.h"

#include <iostream>
#include <iomanip>
#include <sstream>
#include <bitset>


std::string Log::to_string(std::complex<double> val) {
  std::ostringstream ss;

  ss << std::fixed << std::setprecision(3);
  ss << std::setfill('x') << std::right;
  ss << std::setiosflags(std::ios::showpos);

  ss << std::setw(3) << val;

  auto result = ss.str();
  return result;
}


std::string Log::to_string(std::vector<int> vals) {
  std::ostringstream ss;

  ss << "{ ";
  ss << Log::join(", ", vals);
  ss << "}" << std::endl;

  auto result = ss.str();
  return result;
}


std::string Log::to_string(std::vector<bool> vals) {
  std::ostringstream ss;

  ss << "{ ";
  ss << Log::join(", ", vals);
  ss << "}" << std::endl;

  auto result = ss.str();
  return result;
}

std::string Log::to_string(std::vector<std::complex<double>> vals) {
  std::ostringstream ss;

  ss << "{ ";
  ss << Log::join(", ", vals);
  ss << "}" << std::endl;

  auto result = ss.str();
  return result;
}

std::string Log::to_string(QOp* op) {
  std::ostringstream ss;

  ss << op->name();
  ss << " = {" << std::endl;
  for (int i = 0; i < op->size(); ++i) {
    ss << Log::join(", ", op->row(i)) << std::endl;
  }
  ss << "}" << std::endl;

  auto result = ss.str();
  return result;
}

std::string Log::join(std::string separator, std::vector<int> vals) {
  std::ostringstream ss;

  for (int i = 0; i < vals.size(); ++i) {
    ss << vals[i];
    if (i != vals.size() - 1) {
      ss << separator;
    }
  }

  auto result = ss.str();
  return result;
}

std::string Log::join(std::string separator, std::vector<bool> vals) {
  std::ostringstream ss;

  for (int i = 0; i < vals.size(); ++i) {
    ss << vals[i];
    if (i != vals.size() - 1) {
      ss << separator;
    }
  }

  auto result = ss.str();
  return result;
}

std::string Log::join(std::string separator, std::vector<std::complex<double>> vals) {
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

void Log::print(std::vector<int> vals) {
  std::cout << Log::to_string(vals) << std::endl;
}

void Log::print(std::vector<bool> vals) {
  std::cout << Log::to_string(vals) << std::endl;
}

void Log::print(std::vector<std::complex<double>> vals) {
  std::cout << Log::to_string(vals) << std::endl;
}

void Log::qubit_print(std::vector<std::complex<double>> vals, int max_size) {
  for (int i = 0; i < vals.size(); ++i) {
    if (vals[i] == 0.0) {
      continue;
    }
    auto bits = std::bitset<8 * sizeof(i)>(i).to_string();
    auto remaining = bits.substr(bits.size() - max_size);
    reverse(remaining.begin(), remaining.end());
    std::cout << "|" << remaining << ">: " << Log::to_string(vals[i]) << std::endl;
  }
  std::cout << std::endl;
}

void Log::print(QOp* op) {
  std::cout << Log::to_string(op) << std::endl;
}
