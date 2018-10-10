//***************************************************************
//* This Multiplexor class allows the output to be chosen between
//* the two inputs by the control signal
#include <string>
#include <iostream>
#include <fstream>
#include "Converter.h"

using namespace std;

class Multiplexor{
private:
	string myInput1;
	string myInput2;
	bool myControl;
	string name;
	Converter converter;

public:
	Multiplexor();
	Multiplexor(Multiplexor& multiplexor);
	~Multiplexor();

	void setControl(bool controlInput);
	bool getControl();

	void setName(string name){this->name = name;}
	string getName(){return name;}

	void setInputOne(string input);
	void setInputTwo(string input);
	void setInputs(string input1, string input2);

	string getOutput();

	void printToFile(string file1);
	void print();
};