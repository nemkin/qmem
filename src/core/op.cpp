#include "op.h"

#include <iostream>
#include <bitset>

#include "log.h"

QOp::QOp(std::string name, int qubits) {
  this->_name = name;
  this->_qubits = qubits;
}

std::string QOp::name() { return this->_name; }

int QOp::qubits() { return this->_qubits; }

int QOp::size() { return 1 << this->_qubits; }

int QOp::count_set_bits(int n) {
  int count = 0;
  while (n) {
    count += n & 1;
    n >>= 1;
  }
  return count;
}

std::vector<int> QOp::get_bit_mask_mapping(const QRegisters& target, const std::vector<int>& target_regs) {
  std::vector<int> bit_mask_mapping(target.total_qubits);

  int total_qubits = target.total_qubits;
  int affected_qubits = 0;
  for (int i = 0; i < target_regs.size(); ++i) {
    affected_qubits += target.qubits[target_regs[i]];
  }
  //std::cout << "total_qubits: " << total_qubits << std::endl;
  //std::cout << "affected_qubits: " << affected_qubits << std::endl;
  //std::cout << "target.total_size: " << target.total_size << std::endl;
  //std::cout << "target.total_registers: " << target.total_registers << std::endl;

  if (this->qubits() != affected_qubits) {
    throw std::invalid_argument(
      "Operation and target register sizes don't match!");
  }

  std::vector<bool> is_target_reg(target.total_registers);
  //Log::print(is_target_reg);
  for (int i = 0; i < target_regs.size(); ++i) {
    is_target_reg[target_regs[i]] = true;
  }

  //std::cout << "target.qubits" << std::endl;
  //Log::print(target.qubits);
  //std::cout << "target.sizes" << std::endl;
  //Log::print(target.sizes);
  //std::cout << "is_target_reg" << std::endl;
  //Log::print(is_target_reg);

  int current_bit = target.total_qubits - 1;
  int current_begin_bit = target.total_qubits - 1;
  int current_end_bit = affected_qubits - 1;
  for (int i = 0; i < target.total_registers; ++i) {
    for (int current_offset = 0; current_offset < target.qubits[i]; ++current_offset) {
      //  std::cout << "curr_bit: " << current_bit << " "
      //  << "curr_beg_bit: " << current_begin_bit << " "
      //  << "curr_end_bit: " << current_end_bit << " "
      //  << "i: " << i << " "
      //  << "is_target_reg[i]: " << is_target_reg[i] << " "
      //  << "current_offset: " << current_offset << " "
      //  << std::endl;
      if (is_target_reg[i]) {
        bit_mask_mapping[current_bit] = current_end_bit--;
      }
      else {
        bit_mask_mapping[current_bit] = current_begin_bit--;
      }

      --current_bit;
    }
  }

  //Log::print(bit_mask_mapping);

  return bit_mask_mapping;
}

std::vector<int> QOp::get_qubit_mapping(std::vector<int> bit_mask_mapping) {
  int n = 1 << bit_mask_mapping.size();
  std::vector<int> qubit_mapping(n);

  for (int i = 0; i < qubit_mapping.size(); ++i) {
    int mapped = 0;

    for (int j = 0; j < bit_mask_mapping.size(); ++j) {
      int frombit = 1 << j;
      int tobit = 1 << bit_mask_mapping[j];

      if (i & frombit) {
        mapped += tobit;
      }
    }

    qubit_mapping[i] = mapped;

    //std::cout
    //  << std::bitset<10>(i) << " = " << i
    //  << " -> " << std::endl
    //  << std::bitset<10>(mapped) << " = " << mapped
    //  << std::endl << std::endl;
  }

  //Log::print(qubit_mapping);

  return qubit_mapping;
}

void QOp::apply(QRegisters& target, const std::vector<int>& target_regs) {
  
  auto bit_mask_mapping = get_bit_mask_mapping(target, target_regs);
  auto qubit_mapping = get_qubit_mapping(bit_mask_mapping);
  
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
    for (int i = 0; i < affected_size; ++i) {
      auto row = this->row(i);
      for (int j = 0; j < affected_size; ++j) {
        result_reordered[upper * affected_size + i] += reordered[upper * affected_size + j] * row[j];
      }
    }
  }

  //Log::print(result_reordered);

  Amplitudes result(all_size);
  for (int i = 0; i < all_size; ++i) {
    result[i] = result_reordered[qubit_mapping[i]];
  }
  Log::print(result);

  target.amplitudes = result;

}