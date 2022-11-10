#include "sum.h"

#include <iostream>
#include <cmath>
#include <cassert>

#include "../core/log.h"

Sum::Sum(std::string name, index input_qubits, index output_qubits) :
  QOp(name, input_qubits + output_qubits) {
  this->input_qubits = input_qubits;
  this->output_qubits = output_qubits;

  this->input_size = 1 << input_qubits;
  this->output_size = 1 << output_qubits;
}

Amplitudes Sum::row(index i) {
  Amplitudes row;
  row.resize(this->size());

  row[i] = 1.0;

  return row;
}

Amplitudes Sum::col(index i) {
  Amplitudes col;
  col.resize(this->size());

  col[i] = 1.0;

  //TODO Ancilla bits.
  for (index j = input_size; j < input_size + output_size; ++j) {
    col[j] = 1.0;
  }

  return col;
}


void Sum::apply(QRegisters& target, const std::vector<index>& input_regs, const std::vector<index>& output_regs) {
  index input_reg_size = 1;
  for (index i = 0; i < input_regs.size(); ++i) {
    input_reg_size *= target.sizes[input_regs[i]];
  }
  index output_reg_size = 1;
  for (index i = 0; i < output_regs.size(); ++i) {
    output_reg_size *= target.sizes[output_regs[i]];
  }

  assert(input_reg_size == this->input_size);
  assert(output_reg_size == this->output_size);

  std::vector<index> target_regs;

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

void Sum::apply(QRegisters& target, const std::vector<index>& target_regs) {

  // Target regs are: input, then output

  auto bit_mask_mapping = get_bit_mask_mapping(target, target_regs);
  auto qubit_mapping = get_qubit_mapping(bit_mask_mapping);

  int input_size = this->input_size;
  int output_size = this->output_size;

  int all_size = target.amplitudes.size();
  int affected_size = this->size();
  int upper_size = all_size / affected_size;

  Amplitudes reordered;
  reordered.resize(all_size);

  for (auto amp: target.amplitudes) {
    index i = amp.first;
    reordered[qubit_mapping[i]] = target.amplitudes[i];
  }

  //std::cout << "Initial of " << this->name() << std::endl;
  //Log::qubit_print(target.amplitudes, target.total_qubits);

  //std::cout << "Reordered initial of " << this->name() << std::endl;
  //Log::qubit_print(reordered, target.total_qubits);

  Amplitudes result_reordered;
  result_reordered.resize(all_size);
  
  for (int upper = 0; upper < upper_size; ++upper) {
    for (int j = 0; j < input_size; ++j) {
      auto curr = reordered.find(upper * affected_size + j);
      if(curr == reordered.end()) {
        continue;
      }

      int count = this->count_set_bits(j);
      if (reordered[upper * affected_size + j] != 0.0) { // TODO always true
        std::cout << count << " ";
      }
      //result_reordered[upper * affected_size + j] = reordered[upper * affected_size + j];
      
      result_reordered[upper * affected_size + count * input_size + j] += (*curr).second;
    }
  }

  //std::cout << std::endl;

  //std::cout << "Reordered result of " << this->name() << std::endl;
  //Log::qubit_print(result_reordered, target.total_qubits);

  Amplitudes result;
  result.resize(all_size);

  for (index i = 0; i < all_size; ++i) {
    auto curr = result_reordered.find(qubit_mapping[i]);
    if(curr == result_reordered.end()) {
      continue;
    }
    result[i] = (*curr).second;
  }

  //std::cout << "Apply " << this->name() << std::endl;
  //Log::qubit_print(result, target.total_qubits);

  target.amplitudes = result;
}