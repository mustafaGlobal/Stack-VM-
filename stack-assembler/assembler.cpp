#include <iostream>
#include <string>
#include <fstream>

#include "lexer.hpp"

typedef uint32_t i32;

std::vector<i32> compileToInstructions(strings s);
bool isInteger(std::string s);
bool isPrimitive(std::string s);
i32 mapToNumber(std::string s);

int main(int argc, char const *argv[])
{
  // Check for wrong input
  if(argc != 2) {
    std::cout<<"Usage "<< argv[0] <<" <filename>" << std::endl;
    exit(1);
  }

  //Read asm file 
  std::ifstream infile;
  infile.open(argv[1]);
  if (!infile.is_open()) {
    std::cout<<"Error: could not open "<< argv[1]<<std::endl;
  }

  std::string line;
  std::string contents;
  while (getline(infile, line)) {
    contents += line + "\n";
  }
  infile.close();

  //Parse file 
  Lexer lexer;
  strings lexemes = lexer.lex(contents);

  //Compile to binary
  std::vector<i32> instructions = compileToInstructions(lexemes);

  //Write to binary file
  std::ofstream ofile;
  ofile.open("out.bin", std::ios::binary);
  for (i32 i=0; i < instructions.size(); i++) {
    ofile.write(reinterpret_cast<char *>(&instructions[i]), sizeof(i32));
  }
  ofile.close();


  return 0;
}


std::vector<i32> compileToInstructions(strings s) {
  std::vector<i32> instructions;
  for (i32 i = 0; i < s.size(); i++){
    if (isInteger(s[i])) {
      instructions.push_back(stoi(s[i]));
    } else {
      i32 instruction = mapToNumber(s[i]);  
      if(instruction != -1) {
        instructions.push_back(instruction);
      } else {
        std::cout<< "Error at line : " << s[i] << std::endl;
      }
    }
  }
  return instructions;
}

bool isInteger(std::string s) {
  for (i32 i = 0; i <s.length(); i++) {
    if(!isdigit(s[i])) {
      return false;
    }
  }
  return true;
}

i32 mapToNumber(std::string s) {
  if (s == "+")
    return 0x40000001;
  else if (s == "-") 
    return 0x40000002;
  else if (s == "*")
    return 0x40000003;
  else if (s == "/") 
    return 0x40000004;
  else 
    return -1;
}
