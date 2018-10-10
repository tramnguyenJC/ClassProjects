//**************************************************************
//* This class stores the mapping between the registers and the
//* contents they store
#include <map>
#include <string>
#include "Converter.h"
#include "Memory.h"
#include <iostream>
#include <fstream>


using namespace std;

class RegisterMemory{
private:
	Memory myMemory;
	Converter converter;

	string registerOne;
	string registerTwo;

	string registerOneData;
	string registerTwoData;

	string writeRegister;

	string name;

public:
	RegisterMemory();
	RegisterMemory(RegisterMemory& ri);
	RegisterMemory(Memory& memory);

	~RegisterMemory();

	void setRegisterOne(string register1);
	void setRegisterTwo(string register2);

	string getRegisterOneData(){return registerOneData;}
	string getRegisterTwoData(){return registerTwoData;}

	void setWriteRegister(string registerX){writeRegister = registerX;}
	void writeData(string data);

	void setName(string name);
	string getName(){return name;}

	void printSystem();
	void printSystemToFile(string file1);

	void printMemory();
	void printMemoryToFile(string file1);

	string getData(string registerNum); // get data from a particular register

};