#include "sum.h"

#include <iostream>
#include <cmath>
#include <cassert>

#include "../core/log.h"

Sum::Sum(std::string name, int input_qubits, int output_qubits) :
  QOp(name, input_qubits + output_qubits) {
  this->input_qubits = input_qubits;
  this->output_qubits = output_qubits;

  this->input_size = 1 << input_qubits;
  this->output_size = 1 << output_qubits;
}

Amplitudes Sum::row(int i) {
  Amplitudes row(this->size());

  row[i] = 1.0;

  return row;
}

Amplitudes Sum::col(int i) {
  Amplitudes row(this->size());

  row[i] = 1.0;

  //TODO Ancilla bits.
  for (int j = input_size; j < input_size + output_size; ++j) {
    row[j] = 1.0;
  }

  return row;
}


void Sum::apply(QRegisters& target, const std::vector<int>& input_regs, const std::vector<int>& output_regs) {
  int input_reg_size = 1;
  for (int i = 0; i < input_regs.size(); ++i) {
    input_reg_size *= target.sizes[input_regs[i]];
  }
  int output_reg_size = 1;
  for (int i = 0; i < output_regs.size(); ++i) {
    output_reg_size *= target.sizes[output_regs[i]];
  }

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
    output_regs.begin(),
    output_regs.end()
  );

  this->apply(target, target_regs);
}

void Sum::apply(QRegisters& target, const std::vector<int>& target_regs) {

  Log::qubit_print(target.amplitudes, this->qubits());

  auto bit_mask_mapping = get_bit_mask_mapping(target, target_regs);
  auto qubit_mapping = get_qubit_mapping(bit_mask_mapping);

  int input_size = this->input_size;
  int output_size = this->output_size;

  int all_size = target.amplitudes.size();
  int affected_size = this->size();
  int upper_size = all_size / affected_size;

  Amplitudes reordered(all_size);

  for (int i = 0; i < reordered.size(); ++i) {
    reordered[qubit_mapping[i]] = target.amplitudes[i];
  }
  /*
  Log::print(target.amplitudes);
  Log::print(reordered);*/

  Amplitudes result_reordered(all_size);
  
  for (int upper = 0; upper < upper_size; ++upper) {
    for (int j = 0; j < input_size; ++j) {
      int count = this->count_set_bits(j);
      result_reordered[upper * affected_size + j] = reordered[upper * affected_size + j];
        
      result_reordered[upper * affected_size + input_size + count] += reordered[upper * affected_size + j];
    }
  }
 
  //Log::print(result_reordered);

  Amplitudes result(all_size);
  for (int i = 0; i < all_size; ++i) {
    result[i] = result_reordered[qubit_mapping[i]];
  }

  Log::qubit_print(result, this->qubits());

  target.amplitudes = result;
}