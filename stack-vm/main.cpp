#include <iostream>
#include <vector>
#include "stack-vm.hpp"


int main(int argc, char const *argv[]) {
  StackVM vm;
  std::vector<i32>prog{3, 4, 0x40000002, 0x40000000};
  vm.loadProgram(prog);
  vm.run();
  return 0;
}
