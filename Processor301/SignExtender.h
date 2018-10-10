//*******************************************************
//* Thie class extends the sign of a given instruction to 
//* be 32-bit long
#include <string>
#include <iostream>
#include "Converter.h"
#include <fstream>

using namespace std;
class SignExtender{
private:
	string instruction;
	string extendedInstruction;
	string name;
	Converter converter;
public:
	SignExtender();
	SignExtender(SignExtender& signExtender);
	~SignExtender();

	void inputInstruction(string instruction); //sign extending occurs here
	string getInstruction();

	void setName(string name){this->name = name;}
	string getName(){return name;}

	void printToFile(string file1);
	void print();
};