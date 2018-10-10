//***************************************************************
//* This class provides a mapping between the instructions and their
//* memory addresses. It allows access to the binary representation
//* of the instruction.
#include <string>
#include "ASMParser.h"
#include "Converter.h"
#include <iostream>
#include <fstream>
using namespace std;

class InstructionMemory{
private:
	string myAddress;
	string myInstruction; //binary representation of instruction
	ASMParser myParser;
	Converter converter;
	std::map<std::string,std::string> myMap; // map of address to instruction
	string name;

public:
	InstructionMemory();
	InstructionMemory(InstructionMemory& im);
	InstructionMemory(ASMParser& parser);

	~InstructionMemory();

	void findInstruction(string address); //find instruction at the given address
	void print();	// Print out contents of the memory to terminal
	void printToFile(string file1);
	string getInstruction() { return myInstruction; } // Get full instruction
	string getInstruction_25_0();  // Goes to left2shifter for jump
	string getInstruction_31_26(); //goes to control unit
	string getInstruction_25_21(); //goes to register - read register 1
	string getInstruction_20_16(); //goes to register - read register 2 or MUX 1
	string getInstruction_15_11(); //goes to MUX 1
	string getInstruction_15_0(); //goes to sign extender
	string getInstruction_5_0(); //goes to ALU control

	void setName(string name){this->name = name;}
	string getName(){return name;}

};