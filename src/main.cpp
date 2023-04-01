#include<iostream>
#include <string>

#include "core/log.h"
#include "core/amplitudes.h"
#include "core/reg.h"
#include "core/op.h"

#include "ops/hadamard.h"
#include "ops/grover.h"
#include "ops/sum.h"
#include "ops/transposed.h"
#include "ops/tensored.h"
#include "ops/shift.h"
#include "ops/single.h"
#include "ops/added.h"

int main(int argc, char* argv[]) {
  auto regs = QRegisters();
 
  index pos_qubits = 3;
  index coin_qubits = 1;
  regs.Add("pos", pos_qubits, 0);
  regs.Add("coin", coin_qubits);

  auto right = Shift("R", pos_qubits, 1);
  auto left = Shift("L", pos_qubits, -1);

  auto coin_head = Single("H", coin_qubits, 0);
  auto coin_tails = Single("T", coin_qubits, 1);

  auto SL = Tensored(&left, &coin_head);
  auto SR = Tensored(&right, &coin_tails);

  auto S = Added({&SL, &SR});

  std::cout<<"regs.size: "<<regs.amplitudes.size()<<std::endl;

  Log::qubit_print(regs.amplitudes, pos_qubits + coin_qubits);


  std::cout<<"coin_head:"<<std::endl;
  for(int i=0; i<coin_head.size(); ++i) {
    Log::qubit_print(coin_head.row(i), coin_head.qubits());
  }

  std::cout<<"coin_tails:"<<std::endl;
  for(int i=0; i<coin_tails.size(); ++i) {
    Log::qubit_print(coin_tails.row(i), coin_tails.qubits());
  }

  std::cout<<"SL:"<<std::endl;
  for(int i=0; i<SL.size(); ++i) {
    Log::qubit_print(SL.row(i), SL.qubits());
  }

  std::cout<<"SR:"<<std::endl;
  for(int i=0; i<SR.size(); ++i) {
    Log::qubit_print(SR.row(i), SR.qubits());
  }

  std::cout<<"S:"<<std::endl;
  for(int i=0; i<S.size(); ++i) {
    Log::qubit_print(S.row(i), S.qubits());
  }
  
  return 0;
}
