#include "mcnot.h"

#include <iostream>
#include <cmath>
#include <cassert>

#include "../core/log.h"

Mcnot::Mcnot(std::string name, int input_qubits) :
  QOp(name, input_qubits + output_qubits) {
  this->input_qubits = input_qubits;
  this->output_qubits = 1;

  this->input_size = 1 << input_qubits;
  this->output_size = 1 << 1;
}

Amplitudes Mcnot::row(int i) {
  Amplitudes row(this->size());

  row[i] = 1.0;

  return row;
}

Amplitudes Mcnot::col(int i) {
  Amplitudes row(this->size());

  row[i] = 1.0;

  //TODO Ancilla bits.
  for (int j = input_size; j < input_size + output_size; ++j) {
    row[j] = 1.0;
  }

  return row;
}


void Mcnot::apply(QRegisters& target, const std::vector<int>& input_regs, int output_reg) {
  int input_reg_size = 1;
  for (int i = 0; i < input_regs.size(); ++i) {
    input_reg_size *= target.sizes[input_regs[i]];
  }
  int output_reg_size = target.sizes[output_reg];

  assert(output_reg_size == 1);
  assert(input_reg_size == this->input_size);
  assert(output_reg_size == this->output_size);

  std::vector<int> target_regs;

  target_regs.insert(
    target_regs.end(),
    input_regs.begin(),
    input_regs.end()
  );

  target_regs.insert(
    target_regs.end(),
    output_reg
  );

  this->apply(target, target_regs);
}

void Mcnot::apply(QRegisters& target, const std::vector<int>& target_regs) {

  // Target regs are: input, then output

  auto bit_mask_mapping = get_bit_mask_mapping(target, target_regs);
  auto qubit_mapping = get_qubit_mapping(bit_mask_mapping);

  int input_size = this->input_size;
  int output_size = this->output_size;

  int all_size = target.amplitudes.size();
  int affected_size = this->size();
  int upper_size = all_size / affected_size;

  assert(upper_size == 2);

  Amplitudes reordered(all_size);

  for (int i = 0; i < reordered.size(); ++i) {
    reordered[qubit_mapping[i]] = target.amplitudes[i];
  }

  std::cout << "Initial of " << this->name() << std::endl;
  Log::qubit_print(target.amplitudes, target.total_qubits);

  std::cout << "Reordered initial of " << this->name() << std::endl;
  Log::qubit_print(reordered, target.total_qubits);

  Amplitudes result_reordered(all_size);

  for (int upper = 0; upper < upper_size; ++upper) {
    for (int j = 0; j < input_size; ++j) {
      int count = this->count_set_bits(j);
      if (count != 0) {
        result_reordered[(1-upper) * affected_size + j] = reordered[upper * affected_size + j];
      }
      else {
        result_reordered[upper * affected_size + j] = reordered[upper * affected_size + j];
      }
    }
  }

  std::cout << std::endl;

  std::cout << "Reordered result of " << this->name() << std::endl;
  Log::qubit_print(result_reordered, target.total_qubits);

  Amplitudes result(all_size);
  for (int i = 0; i < all_size; ++i) {
    result[i] = result_reordered[qubit_mapping[i]];
  }

  std::cout << "Apply " << this->name() << std::endl;
  Log::qubit_print(result, target.total_qubits);

  target.amplitudes = result;
}
