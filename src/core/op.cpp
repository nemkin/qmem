#include "op.h"

#include<iostream>

#include "log.h"

QOp::QOp(std::string name, int qubits) {
  this->_name = name;
  this->_qubits = qubits;
}

std::string QOp::name() { return this->_name; }

int QOp::qubits() { return this->_qubits; }

int QOp::size() { return 1 << this->_qubits; }

void QOp::apply(QRegisters& target, const std::vector<int>& target_regs) {
  std::vector<int> bit_mask_map(target.total_qubits);
  std::vector<int> qubit_mapping(target.total_size);

  int total_qubits = target.total_qubits;
  int affected_qubits = 0;
  for (int i = 0; i < target_regs.size(); ++i) {
    affected_qubits += target.qubits[target_regs[i]];
  }
  std::cout << "total_qubits: " << total_qubits << std::endl;
  std::cout << "affected_qubits: " << affected_qubits << std::endl;
  std::cout << "target.total_size: " << target.total_size << std::endl;
  std::cout << "target.total_registers: " << target.total_registers << std::endl;

  std::vector<bool> is_target_reg(target.total_registers);
  Log::print(is_target_reg);
  for (int i = 0; i < target_regs.size(); ++i) {
    is_target_reg[target_regs[i]] = true;
  }
  std::cout << "target.qubits" << std::endl;
  Log::print(target.qubits);
  std::cout << "target.sizes" << std::endl;
  Log::print(target.sizes);
  std::cout << "is_target_reg" << std::endl;
  Log::print(is_target_reg);

  int current_bit = target.total_qubits - 1;
  int current_begin_bit = target.total_qubits - 1;
  int current_end_bit = affected_qubits-1;
  for (int i = 0; i < target.total_registers; ++i) {
    for (int current_offset = 0; current_offset < target.qubits[i]; ++current_offset) {
      std::cout << "curr_bit: " << current_bit << " "
        << "curr_beg_bit: " << current_begin_bit << " "
        << "curr_end_bit: " << current_end_bit << " "
        << "i: " << i << " "
        << "is_target_reg[i]: " << is_target_reg[i] << " "
        << "current_offset: " << current_offset << " "
        << std::endl;
      if (is_target_reg[i]) {
        bit_mask_map[current_bit] = current_end_bit--;
      }
      else {
        bit_mask_map[current_bit] = current_begin_bit--;
      }

      --current_bit;
    }
  }

  Log::print(bit_mask_map);

  //int n = target.sizes.size();

  //int offset = 1;
  //std::vector<int> offsets(n+1);
  //offsets[n] = 0;
  //for (int i = n-1; 0<=i; --i) {
  //  offset *= target.sizes[i];
  //  offsets[i] = offset;
  //}


  //int affected_size = 1;
  //for (int i = 0; i<target_regs.size(); ++i) {
  //  affected_size *= target.sizes[target_regs[i]];
  //}

  //if (this->size() != affected_size) {
  //  throw std::invalid_argument(
  //    "Operation and target register sizes don't match!");
  //}

  //Log::print(offsets);

  //for (int i = 0; i < this->size(); ++i) {
  //  auto row = this->row(i);
  //  for (int j = 0; j < row.cells.size(); ++j) {
  //    result.cells[i] += target.cells[j] * row.cells[j];
  //  }
  //}
}