//*******************************************************
//* This class shifts the instruction 2 bits to the left
#include <string>
#include "Converter.h"
#include <iostream>
#include <fstream>

using namespace std;

class Left2Shifter{
private:
	string instruction;
	string shiftedInstruction;
	string name;
	Converter converter;

public:
	Left2Shifter();
	Left2Shifter(Left2Shifter& left2Shifter);
	~Left2Shifter();

	void setName(string name){this->name = name;}
	string getName(){return name;}

	void inputInstruction(string instruction, int length); //shifts 2 bits to left upon input into object
	string getInstruction();

	void printToFile(string file1);
	void print();
};