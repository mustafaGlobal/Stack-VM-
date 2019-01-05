#ifndef STACK_VM_HPP
#define STACK_VM_HPP

#include <iostream>
#include <vector>

//type deffinitons
typedef int32_t i32;

class StackVM{
  private:

  i32 pc = 100; // program counter
  i32 sp = 0; // stack pointer
  std::vector<i32> memory;
  i32 typ = 0;
  i32 dat = 0;
  i32 running = 1;

  i32 getType(i32 instruction);
  i32 getData(i32 instruction);
  void fetch();
  void decode();
  void execute();
  void doPrimitive();

  public:
  StackVM();
  void run();
  void loadProgram(std::vector<i32>prog); 
};


#endif