#pragma once

#include<unordered_map>
#include<complex>
#include<vector>

typedef int64_t index;
typedef std::complex<double> amplitude;
typedef std::unordered_map<index, amplitude> base;

class Amplitudes : public base {
  index _size;
public:
  Amplitudes(index size);

  Amplitudes() = default;
  Amplitudes(const Amplitudes&) = default;
  Amplitudes(Amplitudes&&) = default;

  Amplitudes& operator=(const Amplitudes&) = default;
  Amplitudes& operator=(Amplitudes&&) = default;

  void resize(index size);
  index size();
};
