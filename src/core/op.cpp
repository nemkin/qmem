#include <bitset>
#include <iostream>

#include "amplitudes.h"
#include "log.h"
#include "op.h"

QOp::QOp(std::string name, index qubits) {
  this->_name = name;
  this->_qubits = qubits;
}

std::string QOp::name() { return this->_name; }

index QOp::qubits() { return this->_qubits; }

index QOp::size() { return ((index)1) << this->_qubits; }

index QOp::count_set_bits(index n) {
  index count = 0;
  while (n) {
    count += n & 1;
    n >>= 1;
  }
  return count;
}

std::vector<index> QOp::get_bit_mask_mapping(
    const QRegisters& target, const std::vector<index>& target_regs) {
  std::vector<index> bit_mask_mapping(target.total_qubits);

  index total_qubits = target.total_qubits;
  index affected_qubits = 0;
  for (index i = 0; i < target_regs.size(); ++i) {
    affected_qubits += target.qubits[target_regs[i]];
  }
  // std::cout << "total_qubits: " << total_qubits << std::endl;
  // std::cout << "affected_qubits: " << affected_qubits << std::endl;
  // std::cout << "target.total_size: " << target.total_size << std::endl;
  // std::cout << "target.total_registers: " << target.total_registers <<
  // std::endl;

  if (this->qubits() != affected_qubits) {
    throw std::invalid_argument(
        "Operation and target register sizes don't match!");
  }

  std::vector<bool> is_target_reg(target.total_registers);
  // Log::print(is_target_reg);
  for (index i = 0; i < target_regs.size(); ++i) {
    is_target_reg[target_regs[i]] = true;
  }

  // std::cout << "target.qubits" << std::endl;
  // Log::print(target.qubits);
  // std::cout << "target.sizes" << std::endl;
  // Log::print(target.sizes);
  // std::cout << "is_target_reg" << std::endl;
  // Log::print(is_target_reg);

  index current_bit = target.total_qubits - 1;
  index current_begin_bit = target.total_qubits - 1;
  index current_end_bit = affected_qubits - 1;
  for (index i = 0; i < target.total_registers; ++i) {
    for (index current_offset = 0; current_offset < target.qubits[i];
         ++current_offset) {
      //  std::cout << "curr_bit: " << current_bit << " "
      //  << "curr_beg_bit: " << current_begin_bit << " "
      //  << "curr_end_bit: " << current_end_bit << " "
      //  << "i: " << i << " "
      //  << "is_target_reg[i]: " << is_target_reg[i] << " "
      //  << "current_offset: " << current_offset << " "
      //  << std::endl;
      if (is_target_reg[i]) {
        bit_mask_mapping[current_bit] = current_end_bit--;
      } else {
        bit_mask_mapping[current_bit] = current_begin_bit--;
      }

      --current_bit;
    }
  }

  // Log::print(bit_mask_mapping);

  return bit_mask_mapping;
}

index QOp::get_qubit_mapping(
    const std::vector<index>& bit_mask_mapping, index i) {
  index n = ((index)1) << bit_mask_mapping.size();

  index mapped = 0;

  for (index j = 0; j < bit_mask_mapping.size(); ++j) {
    index frombit = ((index)1) << j;
    index tobit = ((index)1) << bit_mask_mapping[j];

    if (i & frombit) {
      mapped += tobit;
    }
  }

  // std::cout
  //   << std::bitset<10>(i) << " = " << i
  //   << " -> " << std::endl
  //   << std::bitset<10>(mapped) << " = " << mapped
  //   << std::endl << std::endl;

  // Log::print(qubit_mapping);

  return mapped;
}

void QOp::apply(QRegisters& target, const std::vector<index>& target_regs) {
  auto bit_mask_mapping = get_bit_mask_mapping(target, target_regs);

  index all_size = target.amplitudes.size();
  index affected_size = this->size();
  index upper_size = all_size / affected_size;

  Amplitudes reordered;
  reordered.resize(all_size);

  for (auto amp : reordered) {
    index i = amp.first;
    index mapped = get_qubit_mapping(bit_mask_mapping, i);
    reordered[mapped] = target.amplitudes[i];
  }
  /*
  Log::print(target.amplitudes);
  Log::print(reordered);*/

  Amplitudes result_reordered;
  result_reordered.resize(all_size);

  for (index upper = 0; upper < upper_size; ++upper) {
    for (index i = 0; i < affected_size; ++i) {
      auto row = this->row(i);
      for (index j = 0; j < affected_size; ++j) {
        auto curr = reordered.find(upper * affected_size + j);
        if (curr != reordered.end()) {
          result_reordered[upper * affected_size + i] +=
              (*curr).second * row[j];
        }
      }
    }
  }

  // Log::print(result_reordered);

  Amplitudes result;
  result.resize(all_size);

  for (index i = 0; i < all_size; ++i) {
    index mapped = get_qubit_mapping(bit_mask_mapping, i);
    auto curr = result_reordered.find(mapped);
    if (curr != result_reordered.end()) {
      result[i] = (*curr).second;
    }
  }

  std::cout << "Apply " << this->name() << std::endl;
  Log::qubit_print(result, target.total_qubits);

  target.amplitudes = result;
}
