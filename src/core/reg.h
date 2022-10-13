#pragma once

#include <complex>
#include <vector>

class QReg {

private:
  std::string _name;

public:
  std::vector<std::complex<double>> cells;

  QReg(std::string name, int size);
  std::string name();
};